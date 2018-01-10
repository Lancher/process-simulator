#include "ALU_ins.h"
#include "Other.h"
#include <stdlib.h>


unsigned int operand_type1(unsigned char *target,unsigned char *reg){
     
     int i;
     unsigned int SH = inner_bit(target,6,5);
     unsigned int shift_bits = inner_bit(target,11,7);
     unsigned int Rm = inner_bit(target,3,0);
     unsigned int Rm_val = get_decimal(&reg[Rm*4]);
     unsigned int re_val;

     switch(SH) {
            case 0://LSL
                 re_val = Rm_val << shift_bits;
                 break;
            case 1://LSR
                 re_val = Rm_val >> shift_bits;
                 break;
            case 2://ASR
                 int tmp;
                 tmp = Rm_val;
                 re_val = tmp >> shift_bits;
                 break;
            case 3://ROR
                 
                 unsigned int tmpp = Rm_val; 
                 for (i=0;i<shift_bits;i++){
                     tmpp = (tmpp>>1)|(tmpp<<31);
                     
                 }
                 printf("ROR END\n");
                 re_val = tmpp;
                 break;
                
     }
             
     return re_val;
     
}

unsigned int operand_type2(unsigned char *target,unsigned char *reg){

     int i;
     unsigned int SH = inner_bit(target,6,5);
     unsigned int Rm = inner_bit(target,3,0);
     unsigned int Rm_val = get_decimal(&reg[Rm*4]);
     unsigned int Rs = inner_bit(target,11,8);
     unsigned int Rs_val = get_decimal(&reg[Rs*4]);
     unsigned int re_val; 
     
     switch(SH) {
            case 0://LSL
                 re_val = Rm_val << Rs_val;
                 break;
            case 1://LSR
                 re_val = Rm_val >> Rs_val;
                 break;
            case 2://ASR
                 int tmp;
                 tmp = Rm_val;
                 re_val = tmp >> Rs_val;
                 break;
            case 3://ROR
                 unsigned int tmpp = Rm_val;
                  
                 for (i=0;i<Rs_val;i++){
                     tmpp = (tmpp>>1)|(tmpp<<31);
                 }
                 
                 re_val = tmpp;
                 break;
     }     
     
     return re_val;
             
}

unsigned int operand_type3(unsigned char *target){
     
     int i;                
     unsigned int rt_imm = inner_bit(target,11,8)*2;
     unsigned int imm = inner_bit(target,7,0);
     unsigned int re_val ;
     
     
     unsigned int tmp = imm;
     for (i=0;i<rt_imm;i++){
         tmp = (tmp>>1)|(tmp<<31);     
     }
     re_val = tmp;
     
     return re_val;
}


void func_ADD(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //write back to register
     write_back_val = Rn_val + op_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        flags[2] = carryfrom( Rn_val, op_val);   
        //V
        flags[3] = oveflow(Rn_val,op_val,0); 
     }
}

void func_ADDI(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     op_val = operand_type3(target);           
     
     //write back to register
     write_back_val = Rn_val + op_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        flags[2] = carryfrom( Rn_val, op_val);   
        //V
        flags[3] = oveflow(Rn_val,op_val,0); 
     }
}

void func_SUB(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //write back to register
     write_back_val = Rn_val - op_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        flags[2] = not_borrow (Rn_val,op_val);    
        //V
        flags[3] = oveflow(Rn_val,op_val,1); 
     }
}

void func_SUBI(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     op_val = operand_type3(target);           
     
     //write back to register
     write_back_val =  Rn_val - op_val ;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        flags[2] = not_borrow (Rn_val,op_val);    
        //V
        flags[3] = oveflow(Rn_val,op_val,1); 
     }
}

void func_AND(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //write back to register
     write_back_val = op_val & Rn_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (L_bit==0){
           if (shifter_carryout_type1(target,reg)!=2)
              flags[2]= shifter_carryout_type1(target,reg);           
        }
        else {
           if (shifter_carryout_type2(target,reg)!=2)
              flags[2]= shifter_carryout_type2(target,reg);           
        }
        //V unaffected
         
     }
}


void func_ANDI(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     op_val = operand_type3(target);           
     
     //write back to register
     write_back_val = op_val & Rn_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (shifter_carryout_type3(target)!=2)
           flags[2] = shifter_carryout_type3(target);   
           
        //V unaffected
         
     }
}

void func_MVN(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //write back to register
     write_back_val = ~ op_val ;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (L_bit==0){
           if (shifter_carryout_type1(target,reg)!=2)
              flags[2] = shifter_carryout_type1(target,reg);           
        }
        else {
           if (shifter_carryout_type2(target,reg)!=2)
              flags[2] = shifter_carryout_type2(target,reg);           
        }
           
        //V unaffected
         
     }
}

void func_MVNI(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     op_val = operand_type3(target);           
     
     //write back to register
     write_back_val = ~ op_val ;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (shifter_carryout_type3(target)!=2)
           flags[2] = shifter_carryout_type3(target);   
           
        //V unaffected
         
     }
}

void func_ORR(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //write back to register
     write_back_val = op_val | Rn_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (L_bit==0){
           if (shifter_carryout_type1(target,reg)!=2)
              flags[2] = shifter_carryout_type1(target,reg);           
        }
        else {
           if (shifter_carryout_type2(target,reg)!=2)
              flags[2] = shifter_carryout_type2(target,reg);           
        }
          
        //V unaffected 
         
     }
}


void func_ORRI(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     op_val = operand_type3(target);           
     
     //write back to register
     write_back_val = op_val | Rn_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (shifter_carryout_type3(target)!=2)
           flags[2] = shifter_carryout_type3(target);   
           
        //V unaffected
         
     }
}




void func_EOR(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //write back to register
     write_back_val = op_val ^ Rn_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (L_bit==0){
           if (shifter_carryout_type1(target,reg)!=2)
              flags[2] = shifter_carryout_type1(target,reg);           
        }
        else {
           if (shifter_carryout_type2(target,reg)!=2)
              flags[2] = shifter_carryout_type2(target,reg);           
        }
           
        //V unaffected
         
     }
}


void func_EORI(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     op_val = operand_type3(target);           
     
     //write back to register
     write_back_val = op_val ^ Rn_val;
     write_method(&reg[Rd*4],write_back_val);
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (shifter_carryout_type3(target)!=2)
           flags[2] = shifter_carryout_type3(target);   
        //V unaffected
         
     }
}


void func_MOV(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rd = inner_bit(target,15,12);
     unsigned int op_val = 0;     
     unsigned int write_back_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //write back to register
     write_back_val = op_val ;
     write_method(&reg[Rd*4],write_back_val);
     
     
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = inner_bit(&reg[Rd*4],31,31);
        //Z
        if (write_back_val==0){
           flags[1]=1;                      
        }
        else {
           flags[1]=0;  
        }  
        //C
        if (L_bit==0){
           if (shifter_carryout_type1(target,reg)!=2)
              flags[2] = shifter_carryout_type1(target,reg);           
        }
        else {
           if (shifter_carryout_type2(target,reg)!=2)
              flags[2] = shifter_carryout_type2(target,reg);           
        }
        //V unaffected
         
     }
}


void func_CMP(unsigned char *target,unsigned char *reg,unsigned char *flags){
     
     int i,j;
     unsigned int S_bit = inner_bit(target,20,20);
     unsigned int L_bit = inner_bit(target,4,4);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int op_val = 0;     
     unsigned int condition_val = 0;
     
     if (L_bit==0){
         op_val = operand_type1(target,reg);           
     }
     else {
          op_val = operand_type2(target,reg);           
     }
     
     //for condition flags
     condition_val = Rn_val - op_val;
     
     
     //update condition flags
     if (S_bit==1){
        
        //N
        flags[0] = condition_val >> 31;
        //Z
        if (condition_val==0){
           flags[1] = 1;                      
        }
        else {
           flags[1] = 0;  
        }  
        //C
        flags[2] = not_borrow (Rn_val,op_val);  
        //V
        flags[3] = oveflow(Rn_val,op_val,1);
         
     }
}

//operation 0>>+  1>>-
unsigned int oveflow(unsigned int Rn_val,unsigned int op_val,unsigned int operation){
           
           unsigned int left_bit = Rn_val >> 31;
           unsigned int right_bit = op_val >> 31;
           unsigned int answer_bit = 0;
           
           if (operation==0){
              answer_bit = (Rn_val + op_val) >> 31; 
           }           
           else{
                answer_bit = (Rn_val - op_val) >> 31;
           }
           //*OVER* 0+0=1 (adding two positives should be positive)         
           if (left_bit==0 && operation==0 && right_bit==0 && answer_bit==1)
              return 1;
           // *OVER* 0-1=1 (subtracting a negative is the same as adding a positive)        
           if (left_bit==0 && operation==1 && right_bit==1 && answer_bit==1)
              return 1;
           // *OVER* 1+1=0 (adding two negatives should be negative)     
           if (left_bit==1 && operation==0 && right_bit==1 && answer_bit==0)
              return 1;
           // *OVER* 1-0=0 (subtracting a positive is the same as adding a negative)        
           if (left_bit==1 && operation==1 && right_bit==0 && answer_bit==1)
              return 1;
          
           //no overfolw
           return 0;       
              
}

unsigned int carryfrom(unsigned int Rn_val,unsigned int op_val){
           
           unsigned int left_bit = Rn_val >> 31;
           unsigned int right_bit = op_val >> 31;
           unsigned int answer_bit = 0;
           
           
              answer_bit = (Rn_val + op_val) >> 31; 
           
           // *carryfrom* 0+1=0          
           if (left_bit==0 && right_bit==1 && answer_bit==0)
              return 1;
           // *carryfrom* 1+0=0        
           if (left_bit==1 && right_bit==0 && answer_bit==0)
              return 1;
           // *carryfrom* 1+1 must ocurr carryfrom   
           if (left_bit==1 && right_bit==1 )
              return 1;
          
           //no carryfrom
           return 0;       
              
}

unsigned int not_borrow (unsigned int Rn_val,unsigned int op_val){

         if (Rn_val>=op_val){
            return 1 ;
         }
         else{
              return 0;     
         }
}




unsigned int shifter_carryout_type1(unsigned char *target,unsigned char *reg){
     
     int i;
     unsigned int SH = inner_bit(target,6,5);
     unsigned int shift_bits = inner_bit(target,11,7);
     unsigned int Rm = inner_bit(target,3,0);
     unsigned int Rm_val = get_decimal(&reg[Rm*4]);
     unsigned int carry_out = 0;
     unsigned int tmp_u = 0;
     int tmp_s = 0;
     unsigned int re_val;
     
     //no shift no change
     if (shift_bits==0){
        return 2;                   
     }
     
     switch(SH) {
            case 0://LSL
                 tmp_u = Rm_val;
                 for (i=0;i<shift_bits;i++){
                     carry_out = tmp_u >> 31; 
                     tmp_u = tmp_u << 1;          
                 }
                 re_val = carry_out;
                 break;
            case 1://LSR
                 tmp_u = Rm_val;
                 for (i=0;i<shift_bits;i++){
                     carry_out = (tmp_u << 31) >> 31; 
                     tmp_u = tmp_u >>1 ;          
                 }
                 re_val = carry_out;
                 break;
            case 2://ASR
                 tmp_s = Rm_val;
                 for (i=0;i<shift_bits;i++){
                     tmp_u = tmp_s;
                     carry_out = (tmp_u << 31) >> 31; 
                     tmp_s = tmp_s >> 1;    
                 }
                 re_val = carry_out;
                 break;
            case 3://ROR
                 tmp_u = Rm_val; 
                 for (i=0;i<shift_bits;i++){
                     tmp_u = (tmp_u >> 1) | (tmp_u << 31);
                     carry_out = tmp_u >> 31;
                 }
                 re_val = carry_out;
                 break;
                
     }
             
     return re_val;
     
}

unsigned int shifter_carryout_type2(unsigned char *target,unsigned char *reg){

     int i;
     unsigned int SH = inner_bit(target,6,5);
     unsigned int Rm = inner_bit(target,3,0);
     unsigned int Rm_val = get_decimal(&reg[Rm*4]);
     unsigned int Rs = inner_bit(target,11,8);
     unsigned int Rs_val = get_decimal(&reg[Rs*4]);
     unsigned int carry_out = 0;
     unsigned int tmp_u = 0;
     int tmp_s = 0;
     unsigned int re_val; 
     
     //no shift no change
     if (Rs_val==0){
        return 2;                   
     }
     
     switch(SH) {
            case 0://LSL
                 tmp_u = Rm_val;
                 for (i=0;i<Rs_val;i++){
                     carry_out = tmp_u >> 31; 
                     tmp_u = tmp_u << 1;          
                 }
                 re_val = carry_out;
                 break;
            case 1://LSR
                 tmp_u = Rm_val;
                 for (i=0;i<Rs_val;i++){
                     carry_out = (tmp_u << 31) >> 31; 
                     tmp_u = tmp_u >>1 ;          
                 }
                 re_val = carry_out;
                 break;
            case 2://ASR
                 tmp_s = Rm_val;
                 for (i=0;i<Rs_val;i++){
                     tmp_u = tmp_s;
                     carry_out = (tmp_u << 31) >> 31; 
                     tmp_s = tmp_s >> 1;    
                 }
                 re_val = carry_out;
                 break;
            case 3://ROR
                 tmp_u = Rm_val; 
                 for (i=0;i<Rs_val;i++){
                     tmp_u = (tmp_u >> 1) | (tmp_u << 31);
                     carry_out = tmp_u >> 31;
                 }
                 re_val = carry_out;
                 break;
                
     }
             
     return re_val;
     
}

unsigned int shifter_carryout_type3(unsigned char *target){
     
     int i;                
     unsigned int rt_imm = inner_bit(target,11,8)*2;
     unsigned int imm = inner_bit(target,7,0);
     unsigned int carry_out = 0;
     unsigned int re_val ;
     unsigned int tmp_u = imm;
     
     //no shift no change
     if (rt_imm==0)
        return 2;
     
     for (i=0;i<rt_imm;i++){
         tmp_u = (tmp_u>>1) | (tmp_u<<31);
         carry_out = tmp_u >> 31;     
     }
     re_val = carry_out;
     
     return re_val;
}







