#include <stdio.h>
#include "euler_tour.h"

int main()
{
  graph* G = read_graph();
  ulist** al = make_adjacency_list(G);

  uplist* et = make_euler_tour(al, 0);
  uplist_print(et);
  
  uplist_clear(et); et = NULL;
  delete_adjacency_list(al, G->N); al = NULL;
  delete_graph(G); free(G), G = NULL;
  return 0;
}
