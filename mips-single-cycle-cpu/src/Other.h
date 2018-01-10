#ifndef Other
#define Other

#include <stdio.h>

extern int judge_add(int add);
extern void reverse(unsigned char* target);

extern int get_rs(unsigned char *target);
extern int get_rt(unsigned char *target);
extern int get_rd(unsigned char *target);
extern int get_shamt(unsigned char *target);

extern void print_snapshot( FILE *pOut, int pc ,int cycle,unsigned char *reg);

#endif
