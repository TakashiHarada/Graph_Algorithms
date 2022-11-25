#include "ford_fulkerson.h"

int main()
{
  fnet* D = read_flow_network();

  unsigned i;
  unsigned* CAPACITY = (unsigned*)calloc(D->M, sizeof(unsigned));
  for (i = 0; i < D->M; ++i)
    CAPACITY[i] = D->A[2*i].cap;

  max_flow(D);
  
  for (i = 0; i < D->M; ++i)
    printf("(%2u, %2u) : %2u/%2u\n", D->A[2*i].head, D->A[2*i].tail, D->A[2*i].flow, CAPACITY[i]);
  
  free(CAPACITY), CAPACITY = NULL;
  delete_flow_network(D); D = NULL;
  
  return 0;
}
