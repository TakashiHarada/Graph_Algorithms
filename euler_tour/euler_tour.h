#ifndef _EULER_
#define _EULER_

#ifndef _GRAPH_
#include "graph.h"
#endif

uplist* make_euler_tour(ulist**, const vertex);
uplist* make_euler_tour_sub(ulist**, const vertex, uplist*, uplist*);
  
uplist* make_euler_tour(ulist** al, const vertex s) {
  uplist* L = init_uplist();
  uplist* S = init_uplist();

  make_euler_tour_sub(al, s, S, L);
  
  uplist_clear(S); S = NULL;
  return L;
}

uplist* make_euler_tour_sub(ulist** al, const vertex v, uplist* S, uplist* L) {
  if (is_empty_ulist(al[v])) {
    if (is_empty_uplist(S)) return L;
    upair up = { S->head->elem.fst, S->head->elem.snd };
    uplist_remove_head(S);
    uplist_insert(L, up);
    return make_euler_tour_sub(al, up.fst, S, L);
  }
  else {
    unsigned u = ulist_head(al[v]);
    ulist_delete(al[v], u);
    uplist_insert0(S, v, u);
    return make_euler_tour_sub(al, u, S, L);
  }
}

#endif
