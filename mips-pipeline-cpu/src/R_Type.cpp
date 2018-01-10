#include "R_Type.h"
#include "Other.h"

/********************* R tYPE  ********************/

void func_add (unsigned char *reg,int rs,int rt,int rd){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         unsigned int d,dd;
         
         s0= reg[rs*4];
         s0=s0<<24;
         s1= reg[rs*4+1];
         s1=s1<<24;
         s1=s1>>8;
         s2= reg[rs*4+2];
         s2=s2<<24;
         s2=s2>>16;
         s3= reg[rs*4+3];
         s3=s3<<24;
         s3=s3>>24;
         ss=s0+s1+s2+s3;

         t0= reg[rt*4];
         t0=t0<<24;
         t1= reg[rt*4+1];
         t1=t1<<24;
         t1=t1>>8;
         t2= reg[rt*4+2];
         t2=t2<<24;
         t2=t2>>16;
         t3= reg[rt*4+3];
         t3=t3<<24;
         t3=t3>>24;
         tt=t0+t1+t2+t3;

         d=ss+tt;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rd*4+i]=dd;
         }
                                
}

void func_sub (unsigned char *reg,int rs,int rt,int rd){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         unsigned int d,dd;
         
         s0= reg[rs*4];
         s0=s0<<24;
         s1= reg[rs*4+1];
         s1=s1<<24;
         s1=s1>>8;
         s2= reg[rs*4+2];
         s2=s2<<24;
         s2=s2>>16;
         s3= reg[rs*4+3];
         s3=s3<<24;
         s3=s3>>24;
         ss=s0+s1+s2+s3;

         t0= reg[rt*4];
         t0=t0<<24;
         t1= reg[rt*4+1];
         t1=t1<<24;
         t1=t1>>8;
         t2= reg[rt*4+2];
         t2=t2<<24;
         t2=t2>>16;
         t3= reg[rt*4+3];
         t3=t3<<24;
         t3=t3>>24;
         tt=t0+t1+t2+t3;

         d=ss-tt;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rd*4+i]=dd;
         }
                                 
}                           
                                   


void func_and (unsigned char *reg,int rs,int rt,int rd){
                  
         int i;
         for (i=0;i<4;i++){
             reg[rd*4+i]=reg[rs*4+i]&reg[rt*4+i];   
         }                                    
}

void func_or (unsigned char *reg,int rs,int rt,int rd){
                  
         int i;
         for (i=0;i<4;i++){
             reg[rd*4+i]=reg[rs*4+i]|reg[rt*4+i];   
         }                                    
}
void func_xor (unsigned char *reg,int rs,int rt,int rd){
                  
         int i;
         for (i=0;i<4;i++){
             reg[rd*4+i]=reg[rs*4+i]^reg[rt*4+i]; 
         }                                    
}
void func_nor (unsigned char *reg,int rs,int rt,int rd){
                  
         int i;
         for (i=0;i<4;i++){
             reg[rd*4+i]=~(reg[rs*4+i]|reg[rt*4+i]);   
         }                                    
}

void func_nand (unsigned char *reg,int rs,int rt,int rd){
                  
         int i;
         for (i=0;i<4;i++){
             reg[rd*4+i]=~(reg[rs*4+i]&reg[rt*4+i]);   
         }                                    
}

void func_slt (unsigned char *reg,int rs,int rt,int rd){
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         
         
         unsigned int d,dd;
         
         s0= reg[rs*4];
         s0=s0<<24;
         s1= reg[rs*4+1];
         s1=s1<<24;
         s1=s1>>8;
         s2= reg[rs*4+2];
         s2=s2<<24;
         s2=s2>>16;
         s3= reg[rs*4+3];
         s3=s3<<24;
         s3=s3>>24;
         ss=s0+s1+s2+s3;


         t0= reg[rt*4];
         t0=t0<<24;
         t1= reg[rt*4+1];
         t1=t1<<24;
         t1=t1>>8;
         t2= reg[rt*4+2];
         t2=t2<<24;
         t2=t2>>16;
         t3= reg[rt*4+3];
         t3=t3<<24;
         t3=t3>>24;
         tt=t0+t1+t2+t3;

         
         if (ss<tt){
            d=1;       
         }
         else {
              d=0;     
         }
         dd=d;
         
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rd*4+i]=dd;
         }
}

void func_sll (unsigned char *reg,int rt,int rd,int shamt){
         
         int i;

         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         unsigned int d,dd;
         
         t0= reg[rt*4];
         t0=t0<<24;
         t1= reg[rt*4+1];
         t1=t1<<24;
         t1=t1>>8;
         t2= reg[rt*4+2];
         t2=t2<<24;
         t2=t2>>16;
         t3= reg[rt*4+3];
         t3=t3<<24;
         t3=t3>>24;
         tt=t0+t1+t2+t3;
         
         d=tt<<shamt;
         dd=d;

         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rd*4+i]=dd;
         }
}

void func_srl (unsigned char *reg,int rt,int rd,int shamt){
         
         int i;

         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         unsigned int d,dd;
         
         t0= reg[rt*4];
         t0=t0<<24;
         t1= reg[rt*4+1];
         t1=t1<<24;
         t1=t1>>8;
         t2= reg[rt*4+2];
         t2=t2<<24;
         t2=t2>>16;
         t3= reg[rt*4+3];
         t3=t3<<24;
         t3=t3>>24;
         tt=t0+t1+t2+t3;

         d=tt;
         d=d>>shamt;
         dd=d;

         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rd*4+i]=dd;
         }
}  

void func_sra (unsigned char *reg,int rt,int rd,int shamt){
         
         int i;

         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         unsigned int d,dd;
         
         t0= reg[rt*4];
         t0=t0<<24;
         t1= reg[rt*4+1];
         t1=t1<<24;
         t1=t1>>8;
         t2= reg[rt*4+2];
         t2=t2<<24;
         t2=t2>>16;
         t3= reg[rt*4+3];
         t3=t3<<24;
         t3=t3>>24;
         tt=t0+t1+t2+t3;
         
         d=tt>>shamt;
         dd=d;

         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rd*4+i]=dd;
         }
}

 void func_jr (unsigned char *reg,unsigned int *pc,int rs){
        
         unsigned int s0,s1,s2,s3,ss;
         s0= reg[rs*4];
         s0=s0<<24;
         s1= reg[rs*4+1];
         s1=s1<<24;
         s1=s1>>8;
         s2= reg[rs*4+2];
         s2=s2<<24;
         s2=s2>>16;
         s3= reg[rs*4+3];
         s3=s3<<24;
         s3=s3>>24;
         ss=s0+s1+s2+s3;
         *pc=ss;           
                                   
}
