#ifndef ALU_ins
#define ALU_ins

#include <stdio.h>


extern unsigned int operand_type1(unsigned char *target,unsigned char *reg);
extern unsigned int operand_type2(unsigned char *target,unsigned char *reg);
extern unsigned int operand_type3(unsigned char *target);
extern void func_ADD(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_ADDI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_SUB(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_SUBI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_AND(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_ANDI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_MVN(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_MVNI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_ORR(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_ORRI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_EOR(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_EORI(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_MOV(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern void func_CMP(unsigned char *target,unsigned char *reg,unsigned char *flags);
extern unsigned int oveflow(unsigned int Rn_val,unsigned int op_val,unsigned int operation);
extern unsigned int carryfrom(unsigned int Rn_val,unsigned int op_val);
extern unsigned int not_borrow (unsigned int Rn_val,unsigned int op_val);
extern unsigned int shifter_carryout_type1(unsigned char *target,unsigned char *reg);
extern unsigned int shifter_carryout_type2(unsigned char *target,unsigned char *reg);
extern unsigned int shifter_carryout_type3(unsigned char *target);

#endif
