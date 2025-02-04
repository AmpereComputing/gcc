/* { dg-do compile } */
/* { dg-options "-O3 -ftree-mem-gathering -fdump-tree-mgo-details" } */

/* { dg-final { scan-tree-dump "Address computation stmts" "mgo" } } */

/* { dg-final { scan-tree-dump "Create field: .*L3" "mgo" } } */

#include "stdlib.h"
#include "../mgo-common.h"

/* Handle complex address computations */

void bar(int *);

int
foo (int n, signed m, L1 *array)
{
  int sum = 0;
  int *local_array = (int *) calloc(m, sizeof(int));
  bar(local_array);

  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
	{
	  L2 *l2p = array[j].l1_l2p;
	  int tmp = l2p->l2_i2;
	  sum += local_array[tmp + 3];
	}
    }

  return sum;
}
