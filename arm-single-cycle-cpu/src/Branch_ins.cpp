#include "Branch_ins.h"
#include "Other.h"
#include <stdlib.h>


void func_B(unsigned char *target,unsigned char *reg){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     pc = pc + 8 + 4*offset;
     
     //write to register $15
     write_method(&reg[15*4],pc);     
     
}

void func_BL(unsigned char *target,unsigned char *reg){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     unsigned int R_14 = pc + 4;
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     
     pc = pc + 8 + 4*offset;
     //write to register $15
     write_method(&reg[15*4],pc);     
     //write to register $14
     write_method(&reg[14*4],R_14);
}

void func_BEQ(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     
     //write to register $15
     if (flags[1]==1){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}

//0001
void func_BNE(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[1]==0){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}

//0010
void func_BHS(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[2]==1){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}

//0011
void func_BLO(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[2]==0){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}

//0100
void func_BMI(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[0]==1){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}


//0101
void func_BPL(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[0]==0){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
     
}



//0110
void func_BVS(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[3]==1){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}


//0111
void func_BVC(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[3]==0){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}


//1000
void func_BHI(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[1]==0 && flags[2]==1){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}

//1001
void func_BLS(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[1]==1 ^ flags[2]==0){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}
//1010
void func_BGE(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[0]==flags[3]){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}
//1011
void func_BLT(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if (flags[0]!=flags[3]){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}
//1100
void func_BGT(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if ((flags[0]==flags[3]) && (flags[1]==0)){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}

//1101
void func_BLE(unsigned char *target,unsigned char *reg,unsigned char *flags){

     unsigned int offset = inner_bit(target,23,0);
     unsigned int pc = get_decimal(&reg[15*4]);
     //sigened extension 
     if (target[1]>=128){
        offset = offset | 0xFF000000 ;                   
     }
     else {
          offset = offset | 0 ;
     }     
     
     //write to register $15
     if ( (flags[0]!=flags[3]) ^ (flags[1]==1)){
        pc = pc + 8 + 4*offset;
        write_method(&reg[15*4],pc);     
     }
     else {
        pc = pc + 4;
        write_method(&reg[15*4],pc);     
     }
     
}

