#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ms_vertex_t
{
    char *value;
    unsigned int edge_count;
    struct ms_vertex_t **edges;
};

typedef struct ms_vertex_t *ms_vertex;

ms_vertex ms_vertex_init()
{
    ms_vertex v = (ms_vertex)malloc(sizeof(ms_vertex));
    v->edge_count = 0;
    v->value = NULL;
    v->edges = NULL;
    return v;
}

ms_vertex ms_vertex_bind_value(ms_vertex v, const char *value)
{
    v->value = (char *)malloc(sizeof(char) * strlen(value));
    strcpy(v->value, value);
    return v;
}

ms_vertex ms_vertex_bind_edge(ms_vertex v, ms_vertex w)
{
    v->edge_count = v->edge_count + 1;
    if (v->edge_count == 1)
    {
        v->edges = (ms_vertex *)malloc(sizeof(ms_vertex) * v->edge_count);
    }
    else
    {
        v->edges = (ms_vertex *)realloc(v->edges, sizeof(ms_vertex) * v->edge_count);
    }
    printf("EDGEC = %d\n", v->edge_count - 1);
    v->edges[v->edge_count - 1] = w;
    return v;
}

ms_vertex ms_vertex_reset_value(ms_vertex v)
{
    v->value = NULL;
    return v;
}

char *ms_vertex_print(ms_vertex v)
{
    char *buf = malloc(sizeof(char) * 64);
    sprintf(buf, "{ addr: %p, value: %s, count: %d }", v, v->value, v->edge_count);
    return buf;
}
