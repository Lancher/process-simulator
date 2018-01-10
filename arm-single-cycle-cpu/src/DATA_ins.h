#ifndef DATA_ins
#define DATA_ins

#include <stdio.h>

extern void func_LDR(unsigned char *target,unsigned char *reg,unsigned char *data);
extern void func_LDRH(unsigned char *target,unsigned char *reg,unsigned char *data);
extern void func_LDRSH(unsigned char *target,unsigned char *reg,unsigned char *data);
extern void func_LDRB(unsigned char *target,unsigned char *reg,unsigned char *data);
extern void func_LDRSB(unsigned char *target,unsigned char *reg,unsigned char *data);
extern void func_STR(unsigned char *target,unsigned char *reg,unsigned char *data);
extern void func_STRH(unsigned char *target,unsigned char *reg,unsigned char *data);
extern void func_STRB(unsigned char *target,unsigned char *reg,unsigned char *data);
#endif
