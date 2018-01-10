#include "I_Type.h"
#include "Other.h"

/********************* I tYPE  ********************/

void func_addi (unsigned char *reg,int rs,int rt,unsigned char *ins){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int c0;
         unsigned int c1;
         int cc=0;
         
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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

         d=ss+cc;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
                                  
}

void func_lw (unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         
         unsigned int st0;
         unsigned int st1,st2;
         int st3;
         int stst=0;
         
         unsigned int d,dd;
         
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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
         
         st0= data[judge_add(ss+cc)];
         st0=st0<<24;
         st0=st0>>24;
         st1= data[judge_add(ss+cc+1)];
         st1=st1<<24;
         st1=st1>>16;
         st2= data[judge_add(ss+cc+2)];
         st2=st2<<24;
         st2=st2>>8;
         st3= data[judge_add(ss+cc+3)];
         st3=st3<<24;
         stst=st0+st1+st2+st3;

         d=stst;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
 

}
void func_lh(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         
         unsigned int st0;
         int st1;

         int stst=0;
         
         unsigned int d,dd;
         
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
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

         
         st0= data[judge_add(ss+cc)];
         st0=st0<<24;
         st0=st0>>24;
         st1= data[judge_add(ss+cc+1)];
         st1=st1<<24;
         st1=st1>>16;
         stst=st0+st1;

         d=stst;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
 

}

void func_lhu(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         
         unsigned int st0;
         unsigned int st1;

         int stst=0;
         
         unsigned int d,dd;
         
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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


         st0= data[judge_add(ss+cc)];
         st0=st0<<24;
         st0=st0>>24;
         st1= data[judge_add(ss+cc+1)];
         st1=st1<<24;
         st1=st1>>16;
         stst=st0+st1;

         d=stst;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
 

}

void func_lb(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         
         int st0;
         int stst=0;
         
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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

         st0= data[judge_add(ss+cc)];
         st0=st0<<24;
         st0=st0>>24;

         stst=st0;

         d=stst;
         dd=d;
         
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
 

}


void func_lbu(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         
         unsigned int st0;
         

         int stst=0;
         
         unsigned int d,dd;
         
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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

         st0= data[judge_add(ss+cc)];
         st0=st0<<24;
         st0=st0>>24;
         stst=st0;

         d=stst;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
}
void func_sw(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int c0;
         unsigned int c1;
         int cc=0;
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         int st0;
         int stst=0;
         unsigned int d,dd;
         
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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
               
         d=tt;
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<24-8*i;
             dd=dd>>24;
             data[judge_add(ss+cc+i)]=dd;
         }
 

}

void func_sh(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int c0;
         unsigned int c1;
         int cc=0;
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         int st0;
         int stst=0;
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
         
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
                 
         d=tt&0x0000FFFF;
         dd=d;
         for (i=0;i<2;i++){
             dd=d<<24-8*i;
             dd=dd>>24;
             data[judge_add(ss+cc+i)]=dd;
         }
 

}
void func_sb(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int c0;
         unsigned int c1;
         int cc=0;
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         
         int st0;
         
         int stst=0;
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
         
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
              
         d=tt&0x000000FF;
         dd=d;
         for (i=0;i<1;i++){
             dd=d<<24-8*i;
             dd=dd>>24;
             data[judge_add(ss+cc+i)]=dd;
         }
 

}
void func_lui(unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned char *data){
         
         int i;

         int c0;
         unsigned int c1;
         int cc=0;
         
         
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         
         int st0;
         int stst=0;
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
         
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
                
         d=cc;
         d=d<<16;
         dd=d;
         
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
 

}

void func_andi (unsigned char *reg,int rs,int rt,unsigned char *ins){

         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
         
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
         
         d=ss&cc;
         dd=d;
         
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
         
                                     
        
}

void func_ori (unsigned char *reg,int rs,int rt,unsigned char *ins){
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
         
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
         
         d=ss|cc;
         dd=d;
         
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
                    
}
void func_nori (unsigned char *reg,int rs,int rt,unsigned char *ins){
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         unsigned int c0;
         unsigned int c1;
         int cc=0;
         
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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

         d=~(ss|cc);
         dd=d;
         
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
                    
}
void func_slti (unsigned char *reg,int rs,int rt,unsigned char *ins){
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int c0;
         unsigned int c1;
         int cc=0;
         
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;

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

         if (ss<cc){
            d=1;       
         }
         else{
              d=0;
         }
         dd=d;
         for (i=0;i<4;i++){
             dd=d<<(i*8);
             dd=dd>>24;
             reg[rt*4+i]=dd;
         }
         
                                 
}
void func_beq (unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned int *pc){
         
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         

         int c0;
         unsigned int c1;
         int cc=0;
         
         
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
         
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

         if (ss==tt){
            *pc=*pc+4+4*cc;
         }
         else{
              *pc=*pc+4;
         }

}


void func_bne (unsigned char *reg,int rs,int rt,unsigned char *ins,unsigned int *pc){
         
         
         int i;
         int s0;
         unsigned int s1,s2,s3;
         int ss=0;
         
         int t0;
         unsigned int t1,t2,t3;
         int tt=0;
         
         int c0;
         unsigned int c1;
         int cc=0;
         unsigned int d,dd;
         
         c0=ins[2];
         c0=c0<<24;
         c0=c0>>16;
         c1=ins[3];
         c1=c1<<24;
         c1=c1>>24;
         cc=c0+c1;
         
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

         
         
         if (ss!=tt){
            *pc=*pc+4+4*cc;
         }
         else{
              *pc=*pc+4;
         }

}
