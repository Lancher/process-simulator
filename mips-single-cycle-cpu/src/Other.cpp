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

int get_rs (unsigned char *target){
    
    unsigned char div1,div2;
    div1=target[0]<<6;
    div1=div1>>3;
    div2=target[1]>>5;
    
    return div1+div2; 
    
}


int get_rt (unsigned char *target){
    
    unsigned char div2;
    div2=target[1]<<3;
    div2=div2>>3;
    
    return div2; 
    
}


int get_rd (unsigned char *target){
    
    unsigned char div3;
    div3=target[2]>>3;
    
    return div3; 
    
}


int get_shamt (unsigned char *target){
    
    unsigned char div3,div4;
    div3=target[2]<<5;
    div3=div3>>3;
    div4=target[3]>>6;
    
    return div3+div4; 
    
}

void print_snapshot( FILE *pOut, int pc ,int cycle,unsigned char *reg)
{
    int i;
    fprintf( pOut, "cycle %d\n", cycle );
    for( i = 0; i < 32; ++i ) {
        fprintf( pOut, "$%02d: 0x%02X%02X%02X%02X\n", i, reg[i*4],reg[i*4+1],reg[i*4+2],reg[i*4+3] );
    }
    fprintf( pOut, "PC: 0x%08X\n\n\n", pc );
}
