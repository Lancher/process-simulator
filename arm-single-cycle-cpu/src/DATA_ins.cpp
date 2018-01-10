#include "Other.h"

#include "DATA_ins.h"
#include <stdlib.h>
void func_LDR(unsigned char *target,unsigned char *reg,unsigned char *data){
     
     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int offset = inner_bit(target,11,0);
     unsigned int location = 0;
     
     if (U_bit==1){
        location = Rn_val + offset;              
     }
     else {
          location = Rn_val - offset;     
     }
     printf("location :%d\n",location);
     
     //write back
     for (i=0;i<4;i++){
         reg[Rd*4+3-i] = data[judge_add(location+i)];
     }
     
     printf("$%d %02X%02X%02X%02X\n",Rd,reg[Rd*4],reg[Rd*4+1],reg[Rd*4+2],reg[Rd*4+3]);
}

void func_LDRH(unsigned char *target,unsigned char *reg,unsigned char *data){
     
     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int immH = inner_bit(target,11,8);
     unsigned int immL = inner_bit(target,3,0);
     unsigned int offset_8 = immH*16 + immL;
     unsigned int location = 0;
     
     if (U_bit==1){
        location = Rn_val + offset_8;              
     }
     else {
          location = Rn_val - offset_8;     
     }
     printf("location :%d\n",location);
     
     //write back
     for (i=0;i<2;i++){
         reg[Rd*4+3-i] = data[judge_add(location+i)];
     }
     reg[Rd*4+1] = 0;
     reg[Rd*4] = 0;
     
     
     printf("$%d %02X%02X%02X%02X\n",Rd,reg[Rd*4],reg[Rd*4+1],reg[Rd*4+2],reg[Rd*4+3]);
}


void func_LDRSH(unsigned char *target,unsigned char *reg,unsigned char *data){
     
     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int immH = inner_bit(target,11,8);
     unsigned int immL = inner_bit(target,3,0);
     unsigned int offset_8 = immH*16 + immL;
     unsigned int location = 0;
     
     if (U_bit==1){
        location = Rn_val + offset_8;              
     }
     else {
          location = Rn_val - offset_8;     
     }
     printf("location :%d\n",location);
     
     //write back
     for (i=0;i<2;i++){
         reg[Rd*4+3-i] = data[judge_add(location+i)];
     }
     if (data[judge_add(location+1)]>=128){
         reg[Rd*4+1]=255;//right
         reg[Rd*4]=255;//left
     }
     else {
         reg[Rd*4+1]=0;//right
         reg[Rd*4]=0;//left
     }
     
     
     printf("$%d %02X%02X%02X%02X\n",Rd,reg[Rd*4],reg[Rd*4+1],reg[Rd*4+2],reg[Rd*4+3]);
}

void func_LDRB(unsigned char *target,unsigned char *reg,unsigned char *data){
     
     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int offset = inner_bit(target,11,0);
     unsigned int location = 0;
     
     if (U_bit==1){
        location = Rn_val + offset;              
     }
     else {
          location = Rn_val - offset;     
     }
     printf("location :%d\n",location);
     
     //write back
     for (i=0;i<1;i++){
         reg[Rd*4+3-i] = data[judge_add(location+i)];
     }
     reg[Rd*4+2]=0;//right
     reg[Rd*4+1]=0;
     reg[Rd*4]=0;//left
     
     printf("$%d %02X%02X%02X%02X\n",Rd,reg[Rd*4],reg[Rd*4+1],reg[Rd*4+2],reg[Rd*4+3]);
}


void func_LDRSB(unsigned char *target,unsigned char *reg,unsigned char *data){
     
     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int immH = inner_bit(target,11,8);
     unsigned int immL = inner_bit(target,3,0);
     unsigned int offset_8 = immH*16 + immL;
     unsigned int location = 0;
     
     printf("U_bit =%d\n",U_bit);
     
     if (U_bit==1){
        location = Rn_val + offset_8;              
     }
     else {
          location = Rn_val - offset_8;     
     }
     printf("location :%d\n",location);
     
     //write back
     for (i=0;i<1;i++){
         reg[Rd*4+3-i] = data[judge_add(location+i)];
     }
     if (data[judge_add(location)]>=128){
         reg[Rd*4+2]=255;//right
         reg[Rd*4+1]=255;
         reg[Rd*4]=255;//left
     }
     else {
         reg[Rd*4+2]=0;//right
         reg[Rd*4+1]=0;
         reg[Rd*4]=0;//left
     }
     
     
     printf("$%d %02X%02X%02X%02X\n",Rd,reg[Rd*4],reg[Rd*4+1],reg[Rd*4+2],reg[Rd*4+3]);
}


void func_STR(unsigned char *target,unsigned char *reg,unsigned char *data){
     
     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int offset = inner_bit(target,11,0);
     unsigned int location = 0;
     
     if (U_bit==1){
        location = Rn_val + offset;              
     }
     else {
          location = Rn_val - offset;     
     }
     
     //write to memory
     for (i=0;i<4;i++){
         data[judge_add(location+i)] = reg[Rd*4+3-i];
     }
     
}
void func_STRH(unsigned char *target,unsigned char *reg,unsigned char *data){

     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int immH = inner_bit(target,11,8);
     unsigned int immL = inner_bit(target,3,0);
     unsigned int offset_8 = immH*16 + immL;
     unsigned int location = 0;
     
     if (U_bit==1){
        location = Rn_val + offset_8;              
     }
     else {
          location = Rn_val - offset_8;     
     }
     printf("location :%d\n",location);
     
     //write to memory
     for (i=0;i<2;i++){
         data[judge_add(location+i)] = reg[Rd*4+3-i];
     }
     
     
}
void func_STRB(unsigned char *target,unsigned char *reg,unsigned char *data){
 
     int i;
     unsigned int U_bit = inner_bit(target,23,23);
     unsigned int Rn = inner_bit(target,19,16);
     unsigned int Rn_val = get_decimal(&reg[Rn*4]);
     unsigned int Rd = inner_bit(target,15,12);     
     unsigned int offset = inner_bit(target,11,0);
     unsigned int location = 0;
     
     if (U_bit==1){
        location = Rn_val + offset;              
     }
     else {
          location = Rn_val - offset;     
     }
     printf("location :%d\n",location);
     
     //write to memory
     for (i=0;i<1;i++){
         data[judge_add(location+i)] = reg[Rd*4+3-i];
     }
     
         
}
























