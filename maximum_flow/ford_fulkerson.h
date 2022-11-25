#ifndef _FORD_FULKERSON_
#define _FORD_FULKERSON_

#ifndef _GRAPH_
#include "graph.h"
#endif

struct FLOW_ARC {
  unsigned head;
  unsigned tail;
  unsigned cap; // capacity
  unsigned flow; // flow
};
typedef struct FLOW_ARC farc;

struct FLOW_NETWORK {
  unsigned N;
  unsigned M;
  farc* A;
  ulist** il; // incidence list
};
typedef struct FLOW_NETWORK fnet;

fnet* read_flow_network();
void print_flow_network(fnet*, bool);
void print_flow_network_edges(fnet*, bool);
void delete_flow_network(fnet*);
void max_flow(fnet*);
ulist* augmenting_path(fnet*);
void dfs(fnet*, bool*, vertex, ulist*);
bool is_augmenting_path(fnet*, ulist*);
void update_flow_and_residual_graph(fnet*, ulist*);

fnet* read_flow_network() {
  fnet* D = (fnet*)calloc(1, sizeof(fnet));

  fscanf(stdin, "%u %u", &(D->N), &(D->M));

  D->A = (farc*)calloc(2*(D->M), sizeof(farc));

  D->il = (ulist**)calloc(D->N, sizeof(ulist*));
  unsigned i;
  for (i = 0; i < D->N; ++i) D->il[i] = init_ulist();
  
  for (i = 0; i < D->M; ++i) {
    vertex u, v;
    unsigned c;
    fscanf(stdin, "%u %u %u", &u, &v, &c);
    D->A[2*i].head = u, D->A[2*i].tail = v, D->A[2*i].cap = c, D->A[2*i].flow = 0;
    D->A[2*i+1].head = v, D->A[2*i+1].tail = u, D->A[2*i+1].cap = 0, D->A[2*i+1].flow = 0; // ood number arc is a reverse arc

    ulist_insert(D->il[u], 2*i);
    ulist_insert(D->il[v], 2*i+1);
  }
  
  return D;
}

// print incidence list
void print_flow_network(fnet* D, bool flag) {
  unsigned i;
  for (i = 0; i < D->N; ++i) {
    printf("%u : ", i);
    unode* p = D->il[i]->head;
    if (NULL != p) {
      printf("%u", D->A[p->elem].tail);
      for (p = p->next; NULL != p; p = p->next) {
	printf(", %u", D->A[p->elem].tail);
      }
    }
    putchar('\n');
  }
}

void print_flow_network_edges(fnet* D, bool flag) {
  unsigned i;
  if (flag)
    for (i = 0; i < 2*(D->M); ++i) printf("(%u, %u) : c = %u, f = %u\n", D->A[i].head, D->A[i].tail, D->A[i].cap, D->A[i].flow);
  else
    for (i = 0; i < D->M; ++i) printf("(%u, %u) : c = %u, f = %u\n", D->A[2*i].head, D->A[2*i].tail, D->A[2*i].cap, D->A[2*i].flow);
}

void delete_flow_network(fnet* D) {
  unsigned i;
  for (i = 0; i < D->N; ++i) ulist_clear(D->il[i]), D->il[i] = NULL;
  free(D->il); D->il = NULL;
  free(D->A); D->A = NULL;
  free(D);
}

void max_flow(fnet* D) {
  ulist* path = augmenting_path(D);
  while (NULL != path) {
    update_flow_and_residual_graph(D, path);
    ulist_clear(path), path = NULL;
    path = augmenting_path(D);
  }
  if (NULL != path) ulist_clear(path), path = NULL;
}

// consisting of arcs numbers
ulist* augmenting_path(fnet* D) {
  ulist* path = init_ulist();
  bool* marked = (bool*)calloc(D->N, sizeof(bool));

  vertex s = 0;
  dfs(D, marked, s, path);

  free(marked), marked = NULL;
  if (is_empty_ulist(path) || !is_augmenting_path(D, path)) ulist_clear(path), path = NULL;

  return path;
}

void dfs(fnet* D, bool* marked, vertex u, ulist* path) {
  if (marked[(D->N)-1]) return;
    
  unode* p;
  for (p = D->il[u]->head; NULL != p && !marked[(D->N)-1]; p = p->next) {
    farc e = D->A[p->elem];
    if (!marked[e.tail] && e.cap > 0) {
      marked[e.tail] = true;
      ulist_insert(path, p->elem);
      dfs(D, marked, e.tail, path);
      if (!marked[(D->N)-1]) ulist_remove_head(path);
    }
  }
}

bool is_augmenting_path(fnet* D, ulist* path) {
  vertex t = (D->N)-1;
  vertex v = (D->A[ulist_head(path)]).tail;
  return (t == v);
}

void update_flow_and_residual_graph(fnet* D, ulist* path) {
    unode* p = path->head;
    farc e = D->A[p->elem];
    unsigned min = e.cap;
    for (p = p->next; NULL != p; p = p->next) {
      e = D->A[p->elem];
      if (e.cap < min) min = e.cap;
    }
    
    for (p = path->head; NULL != p; p = p->next) {
      e = D->A[p->elem];
      D->A[p->elem].cap -= min;
      if (!(p->elem % 2)) {
	D->A[p->elem].flow += min;
	D->A[(p->elem)+1].cap += min;
      }
      else {
	D->A[(p->elem)-1].flow -= min;
	D->A[(p->elem)-1].cap += min;
      }
    }
}

#endif
