#include "kruskal.h"
#include <stdio.h>

int main()
{
  wgraph* G = read_wgraph();
  bool* mst = kruskal(G);

  unsigned i, sum = 0;
  for (i = 0; i < G->M; ++i)
    if (mst[i]) {
      printf("(%d, %d)\n", G->E[i].end1, G->E[i].end2);
      sum += G->E[i].w;
    }
  printf("The weight of MST is %u\n", sum);
  
  free(mst); mst = NULL;
  delete_wgraph(G); free(G); G = NULL;
  return 0;
}
