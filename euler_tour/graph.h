#ifndef _GRAPH_
#define _GRAPH_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct UNSIGNED_PAIR {
  unsigned fst;
  unsigned snd;
};
typedef struct UNSIGNED_PAIR upair;

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

struct ULIST_NODE {
  unsigned elem;
  struct ULIST_NODE* prev;
  struct ULIST_NODE* next;
};
typedef struct ULIST_NODE unode;

struct ULIST {
  unsigned size;
  unode* head;
  unode* last;
};
typedef struct ULIST ulist;

ulist* init_ulist();
unsigned ulist_head(ulist*);
void ulist_remove_head(ulist*);
bool is_empty_ulist(ulist*);
unode* ulist_search(ulist*, const unsigned);
void ulist_insert(ulist*, const unsigned);
void ulist_insert_sub(ulist*, unode*);
void ulist_delete(ulist*, const unsigned);
void ulist_delete_sub(ulist*, unode*);
void ulist_clear(ulist*);
void ulist_print(ulist*);

ulist* init_ulist() {
  ulist* ul = (ulist*)calloc(1, sizeof(ulist));
  ul->head = NULL, ul->last = NULL;
  return ul;
}

unsigned ulist_head(ulist* ul) {
  return ul->head->elem;
}

void ulist_remove_head(ulist* ul) {
  ulist_delete_sub(ul, ul->head);
}

bool is_empty_ulist(ulist* ul) { return (0 == ul->size); }

unode* ulist_search(ulist* ul, const unsigned u) {
  unode* x = ul->head;
  while (NULL != x && u != x->elem) x = x->next;
  return x;
}

void ulist_insert(ulist* ul, const unsigned u) {
  unode* new = (unode*)calloc(1, sizeof(unode));
  ul->size += 1;
  new->elem = u;
  ulist_insert_sub(ul, new);
}

void ulist_insert_sub(ulist* ul, unode* x) {
  x -> next = ul->head;
  if (NULL != ul->head) ul->head->prev = x;
  else ul->last = x;
  ul->head = x;
  x->prev = NULL;
}

void ulist_delete(ulist* ul, const unsigned u) {
  unode* x = ulist_search(ul, u);
  if (NULL != x) ulist_delete_sub(ul, x);
}

void ulist_delete_sub(ulist* ul, unode* x) {
  ul->size -= 1;
  if (NULL != x->prev) x->prev->next = x->next;
  else ul->head = x->next;
  if (NULL != x->next) x->next->prev = x->prev;
  else ul->last = x->prev;
}

void ulist_clear(ulist* ul) {
  unode *p, *q;
  for (p = ul->head; NULL != p; ) {
    q = p;
    p = p->next;
    free(q);
  }
}

void ulist_print(ulist* ul) {
  unode* p = ul->head;
  if (NULL != p) {
    printf("%u", p->elem);
    for (p = p->next; NULL != p; p = p->next) printf(", %u", p->elem);
  }
}


struct UP_LIST_NODE {
  upair elem;
  struct UP_LIST_NODE* prev;
  struct UP_LIST_NODE* next;
};
typedef struct UP_LIST_NODE upnode;

// list of unsigned pairs
struct UPLIST {
  unsigned size;
  upnode* head;
  upnode* last;
};
typedef struct UPLIST uplist;

uplist* init_uplist();
upair uplist_head(uplist*);
void uplist_remove_head(uplist*);
bool is_empty_uplist(uplist*);
upnode* uplist_search0(uplist*, const unsigned, const unsigned);
upnode* uplist_search(uplist*, const upair);
void uplist_insert0(uplist*, const unsigned, const unsigned);
void uplist_insert(uplist*, upair);
void uplist_insert_sub(uplist*, upnode*);
void uplist_delete0(uplist*, const unsigned, const unsigned);
void uplist_delete(uplist*, upair);
void uplist_delete_sub(uplist*, upnode*);
void uplist_clear(uplist*);
void uplist_print(uplist*);

uplist* init_uplist() {
  uplist* ul = (uplist*)calloc(1, sizeof(uplist));
  ul->head = NULL, ul->last = NULL;
  return ul;
}

upair uplist_head(uplist* ul) {
  upnode* ptr = ul->head;
  upair p = { ptr->elem.fst, ptr->elem.snd };
  return p;
}

void uplist_remove_head(uplist* ul) {
  uplist_delete_sub(ul, ul->head);
}

bool is_empty_uplist(uplist* ul) { return (0 == ul->size); }

upnode* uplist_search0(uplist* ul, const unsigned f, const unsigned s) {
  upnode* x = ul->head;
  while (NULL != x && (f != x->elem.fst || s != x->elem.snd)) x = x->next;
  return x;
}

upnode* uplist_search(uplist* ul, const upair up) {
  upnode* x = ul->head;
  while (NULL != x && (up.fst != x->elem.fst || up.snd != x->elem.snd)) x = x->next;
  return x;
}

void uplist_insert0(uplist* ul, const unsigned f, const unsigned s) {
  upnode* new = (upnode*)calloc(1, sizeof(upnode));
  ul->size += 1;
  new->elem.fst = f;
  new->elem.snd = s;
  uplist_insert_sub(ul, new);
}

void uplist_insert(uplist* ul, const upair up) {
  upnode* new = (upnode*)calloc(1, sizeof(upnode));
  ul->size += 1;
  new->elem.fst = up.fst;
  new->elem.snd = up.snd;
  uplist_insert_sub(ul, new);
}

void uplist_insert_sub(uplist* ul, upnode* x) {
  x -> next = ul->head;
  if (NULL != ul->head) ul->head->prev = x;
  else ul->last = x;
  ul->head = x;
  x->prev = NULL;
}

void uplist_delete0(uplist* ul, const unsigned f, const unsigned s) {
  upnode* x = uplist_search0(ul, f, s);
  if (NULL != x) uplist_delete_sub(ul, x);
}

void uplist_delete(uplist* ul, const upair up) {
  upnode* x = uplist_search0(ul, up.fst, up.snd);
  if (NULL != x) uplist_delete_sub(ul, x);
}

void uplist_delete_sub(uplist* ul, upnode* x) {
  ul->size -= 1;
  if (NULL != x->prev) x->prev->next = x->next;
  else ul->head = x->next;
  if (NULL != x->next) x->next->prev = x->prev;
  else ul->last = x->prev;
}

void uplist_clear(uplist* ul) {
  upnode *p, *q;
  for (p = ul->head; NULL != p; ) {
    q = p;
    p = p->next;
    free(q);
  }
}

void uplist_print(uplist* ul) {
  upnode* p = ul->head;
  if (NULL != p) {
    printf("(%u, %u)", p->elem.fst, p->elem.snd);
    for (p = p->next; NULL != p; p = p->next)
      printf(", (%u, %u)", p->elem.fst, p->elem.snd);
  }
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

graph* read_graph();
void delete_graph();

graph* read_graph() {
  graph* G = (graph*)calloc(1, sizeof(graph));
  
  fscanf(stdin, "%u %u", &(G->N), &(G->M));
  G->E = (edge*)calloc(G->M, sizeof(edge));
  
  unsigned i;
  for (i = 0; i < G->M; ++i) {
    vertex u, v;
    fscanf(stdin, "%u %u", &u, &v);
    G->E[i].end1 = u; G->E[i].end2 = v;
  }
  
  return G;
}

void delete_graph(graph* G) {
  free(G->E); G->E = NULL;
}

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


// Adjacency list
ulist** make_adjacency_list(graph*);
void print_adjacency_list(ulist**, const unsigned);
void delete_adjacency_list(ulist**, const unsigned);

ulist** make_adjacency_list(graph* G) {
  ulist** al = (ulist**)calloc(G->N, sizeof(ulist*));
  unsigned i;
  for (i = 0; i < G->N; ++i) al[i] = (ulist*)calloc(1, sizeof(ulist));
  for (i = 0; i < G->M; ++i) {
    ulist_insert(al[G->E[i].end1], G->E[i].end2);
    ulist_insert(al[G->E[i].end2], G->E[i].end1);
  }
  return al;
}

void print_adjacency_list(ulist** al, const unsigned n) {
  unsigned i;
  for (i = 0; i < n; ++i) {
    printf("%u: ", i);
    ulist_print(al[i]);
    putchar('\n');
  }
}

void delete_adjacency_list(ulist** al, const unsigned n) {
  unsigned i;
  for (i = 0; i < n; ++i) ulist_clear(al[i]), free(al[i]), al[i] = NULL;
  free(al);
}

#endif
