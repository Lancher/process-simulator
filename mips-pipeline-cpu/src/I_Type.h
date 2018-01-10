#ifndef I_TYPE
#define I_TYPE

/********************* I tYPE  ********************/

extern void func_addi (unsigned char *reg,int rs,int rt,unsigned char *ins);

extern void func_lw (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_lh (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_lhu(unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_lb (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_lbu(unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_sw (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_sh (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_sb (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);
extern void func_lui(unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned char *data);

extern void func_andi(unsigned char *reg, int rs, int rt, unsigned char *ins);
extern void func_ori (unsigned char *reg, int rs, int rt, unsigned char *ins);
extern void func_nori(unsigned char *reg, int rs, int rt, unsigned char *ins);

extern void func_slti(unsigned char *reg, int rs, int rt, unsigned char *ins);

extern void func_beq (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned int *pc);
extern void func_bne (unsigned char *reg, int rs, int rt, unsigned char *ins, unsigned int *pc);

#endif
