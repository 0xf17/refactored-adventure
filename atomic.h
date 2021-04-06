#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifndef _MS_ATOMIC_H_
#define _MS_ATOMIC_H_

#define MS_ATOM_DEFAULT_SIZE 16
#define MS_DEFAULT_PTR_SIZE 8

struct ms_atom_t
{
    int nucleus;
    unsigned int level;
    void **cloud;
};

typedef struct ms_atom_t *ms_atom;

ms_atom ms_atom_init_default()
{
    ms_atom a = (ms_atom)malloc(MS_DEFAULT_PTR_SIZE);
    a->nucleus = 0;
    a->level = 1;
    a->cloud = (ms_atom **)malloc(MS_DEFAULT_PTR_SIZE);
    a->cloud[0] = NULL;

    return a;
}

unsigned long ms_atom_size(ms_atom a)
{
    return sizeof(a->nucleus) + sizeof(a->level) + sizeof(a->cloud);
}

void ms_atom_test_init_default()
{
    ms_atom a = ms_atom_init_default();
    assert(ms_atom_size(a) == 16);
    assert(a->nucleus == 0);
    assert(a->level == 1);
    assert(sizeof(a->cloud) == MS_DEFAULT_PTR_SIZE);
    assert(a->cloud[0] == NULL);
}

ms_atom ms_atom_set(ms_atom a, int value)
{
    a->nucleus = value;
    return a;
}

ms_atom ms_atom_level_up(ms_atom a)
{
    a = (ms_atom)realloc(a, MS_ATOM_DEFAULT_SIZE + MS_DEFAULT_PTR_SIZE * (a->level + 1));
    a->level = a->level + 1;
    a->cloud = (struct ms_atom_t **)realloc(a->cloud, MS_DEFAULT_PTR_SIZE * (a->level));
    return a;
}

ms_atom ms_atom_level_down(ms_atom a)
{
    a = (ms_atom)realloc(a, MS_ATOM_DEFAULT_SIZE + MS_DEFAULT_PTR_SIZE * (a->level - 1));
    a->level = a->level - 1;
    a->cloud = (struct ms_atom_t **)realloc(a->cloud, MS_DEFAULT_PTR_SIZE * (a->level));
    return a;
}

ms_atom ms_atom_add(ms_atom a, ms_atom b)
{
    unsigned long i = 0;

    while (i < a->level)
    {
        if (a->cloud[i] == b)
        {
            // Bond already exists
            return a;
        }
        i++;
    }

    ms_atom_level_up(a);
    a->cloud[a->level - 1] = b;

    return a;
}

ms_atom ms_atom_remove(ms_atom a, ms_atom b)
{
    unsigned long i = 0;

    while (i < a->level)
    {
        if (a->cloud[i] == b)
        {
            a->cloud[i] = NULL;
            break;
        }
        i++;
    }

    if (i == a->level)
    {
        return a;
    }

    while ((i < a->level) && (i + 1 < a->level))
    {
        a->cloud[i] = a->cloud[i + 1];
    }

    ms_atom_level_down(a);

    return a;
}

char *ms_atom_cloud(ms_atom a)
{
    unsigned int i = 0;
    char *buf = (char *)malloc(512);

    while (i < a->level)
    {
        sprintf(buf, "%s %p", buf, a->cloud[i]);
        i++;
    }

    sprintf(buf, "%s\n", buf);

    return buf;
}

#endif
