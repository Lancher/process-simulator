#include "R_Type.h"
#include "I_Type.h"
#include "J_Type.h"
#include "Other.h"

#include <stdio.h> 
#include <stdlib.h> 

int main()
{   
    int i=0, j=0;
    /* Declare Register & Memory */
    unsigned char *reg = (unsigned char*)malloc(sizeof(char)*4*32);  // register
    unsigned int  *pc= (unsigned int*)malloc(sizeof(int));  // program counter
	unsigned char *start = (unsigned char*)malloc(sizeof(char)*4);   // the start address of instruction memory
    unsigned char *num_wd_I = (unsigned char*)malloc(sizeof(char)*4);   // number of words of I_memory
    unsigned char *ins = (unsigned char*)malloc(sizeof(char)*4*2048); // instruction memory 
    unsigned char *sp = (unsigned char*)malloc(sizeof(char)*4); // stack pointer
    unsigned char *num_wd_D = (unsigned char*)malloc(sizeof(char)*4); // number of words of D_memory
    unsigned char *data = (unsigned char*)malloc(sizeof(char)*4*2048); // data memory
    int cycle=0;

    unsigned int pc_bytes[5]; // pc[0]~ pc[3] are pc byte by byte, pc[4] is the total pc address of pc in decimimal
    /* Initialization */
    for (i=0;i<32*4;i++){
        reg[i]=0;                
    }
    for (i=0;i<4*2048;i++){
        ins[i]=0;
        data[i]=0;                
    }
    for (i=0;i<5;i++){
        pc_bytes[i]=0;
    }
    for (i=0;i<4;i++){
        start[i]=0;
        num_wd_I[i]=0;
        sp[i]=0;
        num_wd_D[i]=0;
    }
    *pc=0;   
    
    /* Declare file variables. */
	FILE *ii; // iimage.bin
	FILE *id; // dimage.bin
	FILE *snp; // snapshot.rpt
	
    ii = fopen("iimage.bin", "rb");
    id = fopen("dimage.bin", "rb");	
    snp = fopen( "snapshot.rpt", "w" );
    
    if (ii!=NULL&&id!=NULL){
        
       /***********PC****************/
       for (i=0;i<4;i++){
           fread((start+i),1,1,ii);  // write 1 byte each segment and 1 time from ii to (start+i)
       }
       reverse(start);  // reverse to fit the problem of Endian
       for ( i=0;i<4;i++){
          pc_bytes[i]=start[i];
          pc_bytes[i]=pc_bytes[i]<<24;
          pc_bytes[i]=pc_bytes[i]>>i*8;
          pc_bytes[4]=pc_bytes[4]+ pc_bytes[i];    
       }
       *pc=pc_bytes[4];
       
       /***********Setup I_Memory*************/
       /*words in I memory*/
       for (i=0;i<4;i++){
           fread((num_wd_I+i),1,1,ii);
       }
       reverse(num_wd_I);            
       /* num_wd_I  in decimal*/
       int conts_I = 256*256*256*(*(num_wd_I))+256*256*(*(num_wd_I+1))+256*(*(num_wd_I+2))+1*(*(num_wd_I+3));
       /*load instructions to I memory*/
       for (i=pc_bytes[4];i<pc_bytes[4]+conts_I*4;i++){
           fread(&ins[i],1,1,ii);
       }
       for (i=pc_bytes[4];i<pc_bytes[4]+conts_I*4;i=i+4){  // reverse need to do 32-bytes in one time, so i=i+4
           reverse(&ins[i]);
       }
       
       /****************SP*******************/
       for (i=0;i<4;i++){
           fread((sp+i),1,1,id);
       }
       reverse(sp);
       for (i=0;i<4;i++){
           reg[29*4+i]=sp[i];
       }
       
        /***********Setup D_Memory*************/
       /*words in D memory*/
       for (i=0;i<4;i++){
           fread((num_wd_D+i),1,1,id);
       }
       reverse(num_wd_D);       
       /* num_wd_D  in decimal*/
       int conts_D = 256*256*256*(*(num_wd_D))+256*256*(*(num_wd_D+1))+256*(*(num_wd_D+2))+1*(*(num_wd_D+3));
       /*load datas to D memory*/
       for (i=0;i<conts_D;i++){
           for (j=0;j<4;j++){
               fread(&data[i*4+j],1,1,id);
            }
       }
       for (i=0;i<conts_D;i++){
           reverse(&data[i*4]);
       }  
                    
                             
       /***** Simulate Start *****/
       unsigned char opcode;
       unsigned char funct;
       opcode=ins[*pc]>>2;  // becasue ins[*pc] have 8-bit, so shift right 2-bit to get the opcode(6-bit leftmost)
              
       while (1){
           func_zero (reg);
           print_snapshot(snp, *pc, cycle++, reg);
           if (opcode==63){
              break;
           }
           switch (opcode){
                /***** R TYPE ****************/
                case 0 :
                    funct=ins[*pc+3]<<2;                          
                    funct=funct>>2;
                    switch (funct){
                        case 32 :
                            func_add (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc]));   
                            *pc=*pc+4; 
                            break;
                        case 34 :
                            func_sub (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc]));
                            *pc=*pc+4;                                             
                            break;
                        case 36 :
                            func_and (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc])); 
                            *pc=*pc+4; 
                            break;                                            
                        case 37 :
                            func_or (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc]));      
                            *pc=*pc+4; 
                            break;
                        case 38 :
                            func_xor (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc])); 
                            *pc=*pc+4; 
                            break;
                        case 39 :
                            func_nor (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc]));     
                            *pc=*pc+4; 
                            break;
                        case 40 :
                            func_nand (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc]));    
                            *pc=*pc+4; 
                            break;
                        case 42 :
                            func_slt(reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),get_rd(&ins[*pc])); 
                            *pc=*pc+4; 
                            break;
                        case 0 :
                            func_sll (reg,get_rt(&ins[*pc]),get_rd(&ins[*pc]),get_shamt(&ins[*pc]));
                            *pc=*pc+4; 
                            break;
                        case 2 :
                            func_srl (reg,get_rt(&ins[*pc]),get_rd(&ins[*pc]),get_shamt(&ins[*pc]));
                            *pc=*pc+4; 
                            break;
                        case 3 :
                            func_sra (reg,get_rt(&ins[*pc]),get_rd(&ins[*pc]),get_shamt(&ins[*pc]));
                            *pc=*pc+4; 
                            break;
                        case 8 :
                            func_jr(reg,pc,get_rs(&ins[*pc]));   
                            break;
                        default :
                            printf("There are some error in the switch - funct");
                            exit(1);
                        }
                    break;                  
                /***** I TYPE ****************/
                case 8 :
                    func_addi (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc]);
                    *pc=*pc+4; 
                    break;
                case 35 :
                    func_lw (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 33 :
                    func_lh (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 37 :
                    func_lhu (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 32 :
                    func_lb (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 36 :
                    func_lbu (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 43 :
                    func_sw (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 41 :
                    func_sh (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 40 :
                    func_sb (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 15 :
                    func_lui (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],data);
                    *pc=*pc+4; 
                    break;             
                case 12 :
                    func_andi (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc]);
                    *pc=*pc+4; 
                    break;             
                case 13 :
                    func_ori (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc]);
                    *pc=*pc+4; 
                    break;             
                case 14 :
                    func_nori (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc]);
                    *pc=*pc+4; 
                    break;             
                case 10 :
                    func_slti (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc]);
                    *pc=*pc+4; 
                    break;             
                case 4 :
                    func_beq (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],pc);
                    break;             
                case 5 :
                    func_bne (reg,get_rs(&ins[*pc]),get_rt(&ins[*pc]),&ins[*pc],pc);
                    break;
                /***** J TYPE ****************/             
                case 2 :
                    func_j ( pc,&ins[*pc]);
                    break;             
                case 3 :
                    func_jal(pc,&ins[*pc],reg);
                    break;
                /***** S TYPE ****************/             
                case 63 :
                    func_halt ();
                default :             
                    printf("There are some error in the switch - opcode");
                    exit(1);
           } // end of switch(opcode)
           
           opcode=ins[*pc]>>2;
        } // end of while(1)
        free(reg);
        free(ins);
        free(data);
        free(pc);
        free(start);
        free(num_wd_I);
        free(num_wd_D);
    } // end of   if (ii!=NULL&&id!=NULL)
    
    fclose(ii);
    fclose(id);
    return 0;
}
