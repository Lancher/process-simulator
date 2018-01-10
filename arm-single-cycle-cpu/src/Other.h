#ifndef Other
#define Other

#include <stdio.h>

extern int judge_add(int add);
extern void reverse( unsigned char* target);
extern unsigned int get_decimal(unsigned char*target);
extern unsigned int inner_bit(unsigned char*target,unsigned int left_index ,unsigned int right_index);
extern void write_method(unsigned char *target,unsigned int write_back_val);
extern void print_snapshot( FILE *pOut,int cycle,unsigned char *reg);

#endif
