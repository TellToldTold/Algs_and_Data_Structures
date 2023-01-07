#include "graphUtils.h"
#include "queuePublic.h"

typedef struct und_edge_s und_edge_t;
//typedef struct und_vertex_s und_vertex_t;

struct und_edge_s {
    int color;
    vertex_t *src;
    edge_t *edge;
    und_edge_t *next;
};
/*
struct und_vertex_s {
    und_edge_t *head;
    und_vertex_t *next;
    vertex_t *vertex;
};
*/
int hamiltons_cycle_r (vertex_t *, vertex_t *, const int, int);
//und_edge_t *eulers_cycle_r (vertex_t *, und_vertex_t *, const int, int);
und_edge_t *eulers_cycle_r (vertex_t *, vertex_t *, const int, int);


void hamiltons_cycle (graph_t *g, vertex_t *n) {

    int found = hamiltons_cycle_r(n, n, g->nv, 0);

    if (found) {
        printf("\n\nHamilton's Cycle: ");
        vertex_t *s = n;
        printf("%d, ", s->id);
        s = s->pred;
        while(s->id != n->id) {
            printf("%d, ", s->id);
            s = s->pred;
        }
    }
}

int hamiltons_cycle_r (vertex_t *start, vertex_t *curr, const int tot, int c) {
    edge_t *e;
    vertex_t *tmp;

    curr->color = BLACK;

    e = curr->head;
    while (e != NULL) {
        tmp = e->dst;
        if (tmp == start && c == tot - 1) {      // if I have completed the cycle
            curr->pred = start;
            return 1;
        }

        if (tmp->color == WHITE) {
             if (hamiltons_cycle_r (start, tmp, tot, c + 1) == 1) {
                 curr->pred = tmp;
                 return 1;
             }
        }

        e = e->next;
    }

    curr->color = WHITE;

    return 0;
}

/*
void eulers_cycle (graph_t *g, vertex_t *n) {
    int n_edges = 0;
    int i;
    edge_t *e;

    und_vertex_t *v;
    und_vertex_t *prev = NULL;
    und_edge_t *ue;
    und_edge_t *prev_ue = NULL;

    und_vertex_t *tmp;

    for (; n != NULL; n = n->next) {
        v = (und_vertex_t *) util_malloc(sizeof(und_vertex_t));
        v->vertex = n;
        v->next = prev;
        prev = v;

        e = n->head;
        while (e != NULL) {
            i = e->dst->id;

            tmp = v->next;
            while (tmp != NULL) {
                if (tmp->vertex->id == i) {
                    tmp
                }
                tmp = tmp->next;
            }
            if (ue == NULL) {
                ue = (und_edge_t *) util_malloc(sizeof(und_edge_t));
                ue->edge = e;
                ue->src = v;
                ue->color = WHITE;
            }

            ue->next = prev_ue;
            prev_ue = ue;
            e = e->next;
        }

        v->head = ue;
    }


    und_edge_t *sol = eulers_cycle_r(n, v, n_edges, 0);

    if (sol != NULL) {
        printf("\n\nEuler's Cycle: ");
        und_edge_t *s = sol;
        while(s->next != NULL) {
            printf(" (%d, %d) ", s->src->id, s->edge->dst->id);
            s = s->next;
        }
    }
}*/

void eulers_cycle (graph_t *g, vertex_t *n) {
    int n_edges = 0;
    int i;
    edge_t *e;
    vertex_t *v = g->g;

    for (; v != NULL; v = v->next) {

        e = v->head;
        while (e != NULL) {
            if (e->color == WHITE) {
                e->color = GREY;
                n_edges++;
            }
            e = e->next;
        }
    }


    und_edge_t *sol = eulers_cycle_r(n, n, n_edges/2, 0);

    if (sol != NULL) {
        printf("\n\nEuler's Cycle: ");
        und_edge_t *s = sol;
        while(s != NULL) {
            printf(" (%d, %d) ", s->src->id, s->edge->dst->id);
            s = s->next;
        }
    }
}

und_edge_t *eulers_cycle_r (vertex_t *start, vertex_t *curr, const int tot_edges, int c) {
    int crossed;
    edge_t *e;
    edge_t *tmp;
    und_edge_t *f = NULL;
    und_edge_t *f_next = NULL;

    e = curr->head;
    while (e != NULL) {
        crossed = 0;

        tmp = e->dst->head;
        while(tmp != NULL) {
            if (tmp->dst == curr && tmp->color == BLACK) {
                crossed = 1;
            }
            tmp = tmp->next;
        }

        if (crossed == 0) {
            if (e->dst == start && c == tot_edges - 1) {      // if I have completed the cycle and went through al edges
                curr->pred = start;
                f = (und_edge_t *) util_malloc (1 * sizeof(und_edge_t));
                f->src = curr;
                f->edge = e;
                f->next = NULL;
                return f;
            }

            if (e->color == GREY) {
                e->color = BLACK;

                f_next = eulers_cycle_r(start, e->dst, tot_edges, c + 1);
                if (f_next != NULL) {                           // if a solution has been found
                    f = (und_edge_t *) util_malloc (1 * sizeof(und_edge_t));
                    f->src = curr;
                    f->edge = e;
                    f->next = f_next;
                    return f;
                }

                e->color = GREY;                                // reset the edge since if I got here it is not the solution
            }
        }

        e = e->next;
    }

    return f;
}