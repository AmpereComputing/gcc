/* { dg-do run } */
/* { dg-options  "-w -fipa-dead-field-elimination -flto -flto-partition=none -fipa-sizeof" } */

struct a
{
};
b (struct a c) {}
main () {}
