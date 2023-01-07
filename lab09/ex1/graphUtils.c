#include "graphUtils.h"
#include "queuePublic.h"

int graph_dfs_r_type(graph_t *g, vertex_t *n, int currTime, int t[4]);
int graph_dfs_r_depth(graph_t *g, vertex_t *n, int currTime, int *depth);


int graph_bfs_count (graph_t *g, vertex_t *n) {
    queue_t *qp;
    vertex_t *d;
    edge_t *e;

    int count = 0;
    qp = queue_init (g->nv);
    n->color = GREY;
    n->dist = 0;
    n->pred = NULL;
    queue_put (qp, (void *)n);

    while (!queue_empty_m (qp)) {
        queue_get (qp, (void **)&n);
        e = n->head;
        while (e != NULL) {
            d = e->dst;
            if (d->color == WHITE) {
                count++;
                d->color = GREY;
                d->dist = n->dist + 1;
                d->pred = n;
                queue_put (qp, (void *)d);
            }
            e = e->next;
        }
        n->color = BLACK;
    }
    queue_dispose (qp, NULL);

    return count;
}


int graph_bfs_distance (graph_t *g, vertex_t *n) {
    queue_t *qp;
    vertex_t *d;
    edge_t *e;

    int dist = 0;
    qp = queue_init (g->nv);
    n->color = GREY;
    n->dist = 0;
    n->pred = NULL;
    queue_put (qp, (void *)n);

    while (!queue_empty_m (qp)) {
        queue_get (qp, (void **)&n);
        e = n->head;
        while (e != NULL) {
            d = e->dst;
            if (d->color == WHITE) {
                d->color = GREY;
                d->dist = n->dist + 1;
                if (d->dist > dist) {
                    dist = d->dist;
                }
                d->pred = n;
                queue_put (qp, (void *)d);
            }
            e = e->next;
        }
        n->color = BLACK;
    }
    queue_dispose (qp, NULL);

    return dist;
}


void graph_dfs_type (graph_t *g, vertex_t *n, int **types) {
    int currTime=0;
    vertex_t *tmp, *tmp2;
    int t[4];
    t[0] = 0;
    t[1] = 0;
    t[2] = 0;
    t[3] = 0;
    *types = &(t[0]);

    printf("List of edges:\n");
    currTime = graph_dfs_r_type (g, n, currTime, t);
    for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
        if (tmp->color == WHITE) {
            currTime = graph_dfs_r_type (g, tmp, currTime, t);
        }
    }

    printf("List of vertices:\n");
    for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
        tmp2 = tmp->pred;
        printf("%2d: %2d/%2d (%d)\n",
               tmp->id, tmp->disc_time, tmp->endp_time,
               (tmp2!=NULL) ? tmp->pred->id : -1);
    }
}

int graph_dfs_r_type(graph_t *g, vertex_t *n, int currTime, int t[4]) {
    edge_t *e;
    vertex_t *tmp;

    n->color = GREY;
    n->disc_time = ++currTime;
    e = n->head;
    while (e != NULL) {
        tmp = e->dst;
        switch (tmp->color) {
            case WHITE:
                printf("%d -> %d : T\n", n->id, tmp->id);
                t[0]++;
                break;
            case GREY :
                printf("%d -> %d : B\n", n->id, tmp->id);
                t[2]++;
                break;
            case BLACK:
                if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                    t[1]++;
                } else {
                    printf("%d -> %d : 4\n", n->id, tmp->id);
                    t[0]++;
                }
        }

        if (tmp->color == WHITE) {
            tmp->pred = n;
            currTime = graph_dfs_r_type (g, tmp, currTime, t);
        }
        e = e->next;
    }
    n->color = BLACK;
    n->endp_time = ++currTime;

    return currTime;
}


int graph_dfs_depth (graph_t *g, vertex_t *n) {
    int currTime=0;
    vertex_t *tmp, *tmp2;

    int depth = 0;
    printf("List of edges:\n");
    currTime = graph_dfs_r_depth (g, n, currTime, &depth);
    /*for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
        if (tmp->color == WHITE) {
            currTime = graph_dfs_r_depth (g, tmp, currTime);
        }
    }*/

    printf("List of vertices:\n");
    for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
        tmp2 = tmp->pred;
        printf("%2d: %2d/%2d (%d)\n",
               tmp->id, tmp->disc_time, tmp->endp_time,
               (tmp2!=NULL) ? tmp->pred->id : -1);
    }

    printf("\nMax depth: %d \n", depth-1);
}

int graph_dfs_r_depth(graph_t *g, vertex_t *n, int currTime, int *depth) {
    edge_t *e;
    vertex_t *tmp;

    n->color = GREY;
    n->disc_time = ++currTime;
    e = n->head;
    int d = 0;
    while (e != NULL) {
        tmp = e->dst;
        switch (tmp->color) {
            case WHITE: printf("%d -> %d : T\n", n->id, tmp->id); break;
            case GREY : printf("%d -> %d : B\n", n->id, tmp->id); break;
            case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                }
        }
        if (tmp->color == WHITE) {
            tmp->pred = n;
            int p;
            currTime = graph_dfs_r_depth (g, tmp, currTime, &p);
            if (p > d) {
                d = p;
            }
        }
        e = e->next;
    }
    n->color = BLACK;
    n->endp_time = ++currTime;

    *depth = d + 1;
    return currTime;
}


int graph_dfs_r_max_path(graph_t *g, vertex_t *n) {
    edge_t *e;
    vertex_t *tmp;

    n->color = GREY;
    //n->disc_time = ++currTime;
    e = n->head;
    int max_weight = 0;
    while (e != NULL) {
        tmp = e->dst;         // the destination of this edge
        /*switch (tmp->color) {
            case WHITE: printf("%d -> %d : T\n", n->id, tmp->id); break;
            case GREY : printf("%d -> %d : B\n", n->id, tmp->id); break;
            case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                }
        }*/
        if (tmp->color == WHITE) {          // I should only do something if the node is WHITE because I can visit them only once
            tmp->pred = n;
            int weight = e->weight + graph_dfs_r_max_path(g, tmp);
            if (weight > max_weight) {
                max_weight = weight;
            }
            //currTime = graph_dfs_r_max_path (g, tmp, currTime);
        }
        e = e->next;            // go to next edge
    }
    n->color = WHITE;
    //n->endp_time = ++currTime;

    return max_weight;
}
