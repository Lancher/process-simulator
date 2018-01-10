#include "Other.h"


int judge_add(int add){
    int x=0,y=0,z=0;
    
    x=add/4;
    y=add%4;
    z=3-y;
    
    return (x*4+z);    
}
void reverse( unsigned char* target){
     
     int i=0;
     char temp[4];
     for (i=0;i<4;i++){
         temp[i]=target[3-i];
     }
     for (i=0;i<4;i++){
         target[i]=temp[i];
     }
}

unsigned int get_decimal(unsigned char*target){
         
         unsigned int re_val = 0;
         re_val = 256*256*256*target[0]+256*256*target[1]+256*target[2]+target[3];
         return re_val; 
}

unsigned int inner_bit(unsigned char*target,unsigned int left_index ,unsigned int right_index){
         
         unsigned int re_val = 0;         
         unsigned int tmp = 0;
         unsigned int bits = 0;
         
         tmp = get_decimal(target);
         bits = left_index - right_index + 1;
         tmp = tmp << (31 - left_index);
         tmp = tmp >>(32 - bits) ;
         
         re_val = tmp;
         return re_val;
}
void write_method(unsigned char *target,unsigned int write_back_val){

     int i;
     unsigned int tmp;
     for (i=0;i<4;i++){
         tmp = write_back_val << (i*8);
         tmp = tmp >> 24;
         target[i] = tmp;
     }
}


void print_snapshot( FILE *pOut ,int cycle,unsigned char *reg){
    int i;
    fprintf( pOut, "cycle %d\n", cycle );
    for( i = 0; i < 16; ++i ) {
        fprintf( pOut, "$%02d: 0x%02X%02X%02X%02X\n", i, reg[i*4],reg[i*4+1],reg[i*4+2],reg[i*4+3] );
    }
    fprintf(pOut,"\n\n");
}



