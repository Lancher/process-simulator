#ifndef R_TYPE
#define R_TYPE

/********************* R tYPE  ********************/
extern void func_add (unsigned char * ,int , int , int);
extern void func_sub (unsigned char * ,int , int , int);

extern void func_and (unsigned char * ,int , int , int);
extern void func_or  (unsigned char * ,int , int , int);
extern void func_xor (unsigned char * ,int , int , int);
extern void func_nor (unsigned char * ,int , int , int);
extern void func_nand(unsigned char * ,int , int , int);

extern void func_slt (unsigned char * ,int , int , int);

extern void func_sll (unsigned char *reg, int rt, int rd, int shamt);
extern void func_srl (unsigned char *reg, int rt, int rd, int shamt);
extern void func_sra (unsigned char *reg, int rt, int rd, int shamt);

extern void func_jr (unsigned char *reg, unsigned int *pc, int rs);

#endif
