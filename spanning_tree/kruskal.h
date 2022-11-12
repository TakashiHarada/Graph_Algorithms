#ifndef _KRUSKAL_
#define _KRUSKAL_

#ifndef _GRAPH_
#include "graph.h"
#endif

#include <stdbool.h>

void swap(unsigned*, const unsigned, const unsigned);
void heapsort_with_edge_weight(unsigned*, const int, unsigned*);
void heapify_with_edge_weight(unsigned*, const int, unsigned*);
void downmax_with_edge_weight(const int, unsigned*, const int, unsigned*);
unsigned deletemax_with_edge_weight(unsigned*, const int, unsigned*);
unsigned* sort_edges(wgraph*);

unsigned deletemax_with_edge_weight(unsigned* A, const int n, unsigned* w) {
  unsigned max = A[0];
  A[0] = A[n-1];
  downmax_with_edge_weight(0, A, n-1, w);
  return max;
}

void swap(unsigned* A, const unsigned i, const unsigned j) {
  unsigned tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}

void downmax_with_edge_weight(const int i, unsigned* A, const int n, unsigned* w) {
  int j;
  j = 2*i+1; // left child
  if (j >= n) return;
  if (j+1 < n && w[A[j]] < w[A[j+1]]) j = j+1; // right child is hevier than left
  if (w[A[i]] < w[A[j]]) {
    swap(A, i, j);
    downmax_with_edge_weight(j, A, n, w);
  }
}

void heapify_with_edge_weight(unsigned* A, const int n, unsigned* w) {
  int i;
  for (i = n/2-1; i >= 0; --i) downmax_with_edge_weight(i, A, n, w);
}

void heapsort_with_edge_weight(unsigned* A, const int n, unsigned* w) {
  heapify_with_edge_weight(A, n, w);
  int i;
  for (i = n-1; i >= 0; --i) A[i] = deletemax_with_edge_weight(A, i+1, w);
}

unsigned* sort_edges(wgraph* G) {
  unsigned* order = (unsigned*)calloc(G->M, sizeof(unsigned));

  unsigned i;
  for (i = 0; i < G->M; ++i) order[i] = i;

  unsigned* w = (unsigned*)calloc(G->M, sizeof(unsigned));
  for (i = 0; i < G->M; ++i) w[i] = G->E[i].w;
  
  heapsort_with_edge_weight(order, (int)G->M, w);

  free(w); w = NULL;
  
  return order;
}

bool* kruskal(wgraph* G) {
  bool* mst = (bool*)calloc(G->M, sizeof(bool));

  set s;
  init_set(&s, G->M, G->M);

  int j;
  for (j = 0; j < (int)G->M; ++j) {
    s.size[j] = 1;
    s.root[j] = j;
    s.parent[j] = -(j+1);
  }

  unsigned* order = sort_edges(G);
  
  unsigned i;  
  for (i = 0; i < G->M; ++i) {
    vertex u, v;
    u = G->E[order[i]].end1, v = G->E[order[i]].end2;
    int su = tree_find((int)u, &s), sv = tree_find((int)v, &s);
    if (su != sv) {
      mst[order[i]] = true;
      tree_merge(su, sv, &s);
    }
  }
  
  free(order); order = NULL;
  delete_set(&s);
  
  return mst;
}

#endif
