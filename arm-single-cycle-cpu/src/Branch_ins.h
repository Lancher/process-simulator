#ifndef Branch_ins
#define Branch_ins

#include <stdio.h>

extern void func_B(unsigned char *target,unsigned char *reg);
extern void func_BL(unsigned char *target,unsigned char *reg);
extern void func_BEQ(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BNE(unsigned char *target,unsigned char *reg,unsigned char *flags);

extern void func_BHS(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BLO(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BMI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BPL(unsigned char *target,unsigned char *reg,unsigned char *flags);

extern void func_BVS(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BVC(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BHI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BLS(unsigned char *target,unsigned char *reg,unsigned char *flags);

extern void func_BGE(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BLT(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BGT(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_BLE(unsigned char *target,unsigned char *reg,unsigned char *flags);

#endif
