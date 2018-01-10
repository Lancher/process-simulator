#ifndef J_TYPE
#define J_TYPE

/********************* J tYPE  ********************/
extern void func_j ( unsigned int *pc, unsigned char *ins);
extern void func_jal(unsigned int *pc, unsigned char *ins, unsigned char *reg);


/********************* S tYPE  ********************/
extern void func_halt();


extern void func_zero(unsigned char *reg);

#endif
