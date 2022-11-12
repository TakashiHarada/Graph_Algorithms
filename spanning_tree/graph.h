#ifndef _GRAPH_
#define _GRAPH_

#include <stdlib.h>
#include <stdio.h>

struct SET {
  unsigned* size;
  int* root;
  int* parent;
};
typedef struct SET set;

void init_set(set* s, const unsigned M, const unsigned N) {
  s->size = (unsigned*)calloc(M, sizeof(unsigned));
  s->root = (int*)calloc(M, sizeof(int));
  s->parent = (int*)calloc(N, sizeof(int));
}

void delete_set(set* s) {
  free(s->size); s->size = NULL;
  free(s->root); s->root = NULL;
  free(s->parent); s->parent = NULL;
}

// Merge s_i and s_k
void tree_merge(const unsigned i, const unsigned k, set* s) {
  unsigned j, small = i, large = k;
  if (s->size[i] > s->size[k]) small = k, large = i;

  // s_small is an empty set
  if (0 == s->size[small]) return;
  
  j = s->root[small];
  
  s->parent[j] = s->root[large];
  s->size[large] += s->size[small];
  s->size[small] = 0;
  s->root[small] = -1;
}

int tree_find(const unsigned j, set* s) {
  int i, k, tmp;
  
  // traverse to the root of s containing j
  k = j;
  while (k >= 0) k = s->parent[k]; 
  i = -k-1;

  // compress paths
  k = j;
  while (k >= 0) {
    tmp = s->parent[k];
    if (tmp >= 0) s->parent[k] = s->root[i]; // 
    k = tmp;
  }
  return i;
}


#define vertex unsigned

struct EDGE {
  vertex end1; // end point
  vertex end2; // end point
};
typedef struct EDGE edge;

struct GRAPH {
  vertex* V;  // set of vertices
  edge* E;
  unsigned N; // number of vertices
  unsigned M; // number of edges
};
typedef struct GRAPH graph;

struct WEIGHTED_EDGE {
  vertex end1;
  vertex end2;
  vertex w;    // weight
};
typedef struct WEIGHTED_EDGE wedge;

struct WEIGHTED_GRAPH {
  vertex* V;
  wedge* E;
  unsigned N;
  unsigned M;
};
typedef struct WEIGHTED_GRAPH wgraph;

struct ARC {
  vertex head;
  vertex tail;
};
typedef struct ARC arc;

struct DIGRAPH {
  vertex* V;
  arc* A;
  unsigned N;
  unsigned M;
};
typedef struct DIGRAPH digraph;

struct WEIGHTED_ARC {
  vertex head;
  vertex tail;
  vertex w;
};
typedef struct WEIGHTED_ARC warc;

struct WEIGHTED_DIGRAPH {
  /* vertex* V; */
  warc* A;
  unsigned N;
  unsigned M;
};
typedef struct WEIGHTED_DIGRAPH wdigraph;

wgraph* read_wgraph();
void delete_wgraph(wgraph*);

wdigraph* read_wdigraph();
void delete_wdigraph(wdigraph*);

wgraph* read_wgraph() {
  wgraph* G = (wgraph*)calloc(1, sizeof(wgraph));
  
  fscanf(stdin, "%u %u", &(G->N), &(G->M));
  G->E = (wedge*)calloc(G->M, sizeof(wedge));
  
  unsigned i;
  for (i = 0; i < G->M; ++i) {
    vertex u, v, w;
    fscanf(stdin, "%u %u %u", &u, &v, &w);
    G->E[i].end1 = u; G->E[i].end2 = v; G->E[i].w = w;
  }
  
  return G;
}

void delete_wgraph(wgraph* G) {
  free(G->E); G->E = NULL;
}

wdigraph* read_wdigraph() {
  wdigraph* D = (wdigraph*)calloc(1, sizeof(wdigraph));
  
  fscanf(stdin, "%u %u", &(D->N), &(D->M));
  /* printf("N = %u, M = %u\n", D->N, D->M); */
  D->A = (warc*)calloc(D->M, sizeof(warc));
  
  unsigned i;
  for (i = 0; i < D->M; ++i) {
    vertex u, v, w;
    fscanf(stdin, "%u %u %u", &u, &v, &w);
    D->A[0].head = u; D->A[0].tail = v; D->A[0].w = w;
  }
  
  return D;
}

void delete_wdigraph(wdigraph* D) {
  free(D->A); D->A = NULL;
}


#endif
