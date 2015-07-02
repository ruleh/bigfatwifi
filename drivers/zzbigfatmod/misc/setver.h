/*simply set your kernel version here...*/
/*it is like this 3.15.0 --> 3150*/
/*3.0.101 --> 3001*/
/*more generally a.b.c --> a.bb.c*/
/*actually this needs refinement but it works for now so I leave it.*/
#if (CONFIG_3_15_COMPAT)
#define KERNVER 3150
#else
#define KERNVER 3000
#endif