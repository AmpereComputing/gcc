/* { dg-do link } */
/* { dg-options "-O2 -flto -fipa-type-escape-analysis -fno-strict-aliasing -fdump-tree-fre5 -fmem-layout-trans -fdump-ipa-type-escape-analysis-details" } */

#include <stdlib.h>
#include <stdio.h>

/* Accessing differrent field in array. */

struct A
{
  int f1;
  int f2;
};

struct A *arrA;
struct A *arrB;

__attribute_noinline__ int
foo (int i)
{
  // no alias
  arrA[0].f2 = i * i;
  arrB[7].f1 = i + i;
  
  if (arrA[0].f2 != i * i)
    return 999;

  return arrB[5].f1;
}

int
main (void)
{
  struct A *arr = malloc (sizeof (struct A) * 20);
  arrA = arr;
  arrB = arr + 1;
  printf ("%d\n", foo (20));
  arrB = arr;
  arrA = arr + 7;
  printf ("%d\n", foo (8));
  arrB = arr + 3;
  printf ("%d\n", foo (7));
  return 0;
}

/* { dg-final { scan-wpa-ipa-dump "struct A as non-escaping" "type-escape-analysis" } } */
/* { dg-final { scan-ltrans-tree-dump-not "999" "fre5" } } */

