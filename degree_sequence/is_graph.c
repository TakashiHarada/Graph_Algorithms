#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define bufsize 10000
#define max_vsize 5000 /* number of vertices */
char buf[bufsize];
char num[bufsize/2];
int a[max_vsize];

void print_sequence_i(const int*, const unsigned);
bool decide_sequence(int*, const unsigned);

int comp(const void* x, const void* y) {
  int xx = *(int*)x;
  int yy = *(int*)y;
  return yy - xx;
}

int main()
{
  /* Input is an monotonic non-increasing number sequence. */
  fgets(buf,bufsize,stdin);

  register int f, j, p, l = 0;

  if ('\n' != buf[strlen(buf)-1]) {
    fprintf(stderr, "Input line way too long.\n");
    return 1;
  }
  if ('(' != buf[0] || ')' != buf[strlen(buf)-2]) {
    fprintf(stderr, "Illegal input.\n");
    exit (1);
  }
  for (p = 1; p < strlen(buf)-2; ) {
    if (!isdigit(buf[p]) && ',' != buf[p] && isspace(buf[p])) {
      fprintf(stderr, "Illegal input.\n");
      exit (1);
    }
    f = -1;
    for (j = 0; !isspace(buf[p+j]) && ',' != buf[p+j]; ++j) {
      if (',' == buf[p+j] && -1 == f) {
	fprintf(stderr, "Illegal input.\n");
	exit (1);
      }
      f = 1;
      num[j] = buf[p+j];
    }
    num[j] = '\0';
    sscanf(num, "%d", &(a[l]));
    if (l > 0 && a[l] > a[l-1]) {
      fprintf(stderr, "Input sequence is not a monotonic non-increasing order.\n");
      exit (1);
    }
    ++l;
    for (p += j+1; isspace(buf[p]); ++p)
      ;
  }
  if (decide_sequence(a,l))
    printf("Input sequence is the degree sequence for some graph.\n");
  else
    printf("Input sequence is not a degree sequence.\n");
  
  return 0;
}

void print_sequence_i(const int* seq, const unsigned l) {
  if (0 == l)
    return;
  printf("(%d", seq[0]);
  unsigned i;
  for (i = 1; i < l; ++i)
    printf(", %d", seq[i]);
  printf(")\n");
}

bool decide_sequence(int* a, const unsigned n) {
  print_sequence_i(a, n);
  register unsigned i, s = 0;
  for (i = 0; i < n; ++i) {
    if (0 > a[i])
      return false;
    s += a[i];
  }
  if (s%2)
    return false;

  if (0 == s)
    return true;

  s = a[0];
  for (i = 1; i < n; ++i) {
    a[i-1] = a[i];
    if (i <= s)
      --(a[i-1]);
  }
  qsort(a, n-1, sizeof(int), comp);
  return decide_sequence(a, n-1);
}
