#include "J_Type.h"
#include "Other.h"
#include <stdlib.h>

/********************* J tYPE  ********************/
void func_j ( unsigned int *pc,unsigned char *ins){
         
         unsigned int c0,c1,c2,c3,cc;
         c0=ins[1];
         c0=c0<<24;
         c0=c0>>8;
         c1=ins[2];
         c1=c1<<24;
         c1=c1>>16;
         c2=ins[3];
         c2=c2<<24;
         c2=c2>>24;
         cc=c0+c1+c2;

         *pc=cc*4;
         
                                 
}
void func_jal( unsigned int *pc,unsigned char *ins,unsigned char *reg){
         
         int i,j;
         unsigned int tmp=*pc+4;
         unsigned int dd,d=tmp;
         
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[31*4+i]=dd;
         }
         unsigned int c0,c1,c2,c3,cc;
         
         c0=ins[1];
         c0=c0<<24;
         c0=c0>>8;
         c1=ins[2];
         c1=c1<<24;
         c1=c1>>16;
         c2=ins[3];
         c2=c2<<24;
         c2=c2>>24;
         cc=c0+c1+c2;
         *pc=cc*4;
}

/********************* S tYPE  ********************/
void func_halt (){
          exit(1);
}


void func_zero (unsigned char *reg){
          int i;
          for (i=0;i<4;i++){
              reg[i]=0;                                        
          }                           
}
