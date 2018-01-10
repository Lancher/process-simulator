#include <stdio.h> 
#include <stdlib.h> 

#include "Other.h"
#include "ALU_ins.h"
#include "DATA_ins.h"
#include "Branch_ins.h"




unsigned int ins_judgement(unsigned char*target){
         
         unsigned int re_val = 0;
         
         if (inner_bit(target,31,26)==56){
            //ADD
            if (inner_bit(target,25,21)==4){
               re_val = 1;
               return re_val;                                
            }                                 
            //ADDI
            if (inner_bit(target,25,21)==20){
               re_val = 2;
               return re_val;                                
            }                                 
            //SUB
            if (inner_bit(target,25,21)==2){
               re_val = 3;
               return re_val;                                
            }                                 
            //SUBI
            if (inner_bit(target,25,21)==18){
               re_val = 4;
               return re_val;                                
            }                                 
            //AND
            if (inner_bit(target,25,21)==0){
               re_val = 5;
               return re_val;                                
            }                                 
            //ANDI
            if (inner_bit(target,25,21)==16){
               re_val = 6;
               return re_val;                                
            }                                 
            //MVN
            if (inner_bit(target,25,21)==15){
               re_val = 7;
               return re_val;                                
            }                                 
            //MVNI
            if (inner_bit(target,25,21)==31){
               re_val = 8;
               return re_val;                                
            }                                 
            //ORR
            if (inner_bit(target,25,21)==12){
               re_val = 9;
               return re_val;                                
            }                                 
            //ORRI
            if (inner_bit(target,25,21)==28){
               re_val = 10;
               return re_val;                                
            }                                 
            //EOR
            if (inner_bit(target,25,21)==1){
               re_val = 11;
               return re_val;                                
            }                                 
            //EORI
            if (inner_bit(target,25,21)==17){
               re_val = 12;
               return re_val;                                
            }                                 
            //MOV
            if (inner_bit(target,25,21)==13){
               re_val = 13;
               return re_val;                                
            }                      
                      
         }
         
         if (inner_bit(target,31,26)==56 || inner_bit(target,31,26)==57){
            if (inner_bit(target,31,26)==57){
               //LDR
               if (inner_bit(target,22,20)==1){
                  re_val = 14;
                  return re_val;                                
               }
               //STR
               if (inner_bit(target,22,20)==0){
                  re_val = 15;
                  return re_val;                                
               }
               //LDRB
               if (inner_bit(target,22,20)==5){
                  re_val = 19;
                  return re_val;                                
               }
               //STRB
               if (inner_bit(target,22,20)==4){
                  re_val = 21;
                  return re_val;                                
               }
            }
            
            if (inner_bit(target,31,26)==56){
               //STRH
               if (inner_bit(target,22,20)==4 && inner_bit(target,7,4)==11){
                  re_val = 18;
                  return re_val;                                
               }
               //LDRH
               if (inner_bit(target,22,20)==5 && inner_bit(target,7,4)==11){
                  re_val = 16;
                  return re_val;                                
               }
               //LDRH
               if (inner_bit(target,22,20)==5 && inner_bit(target,7,4)==15){
                  re_val = 17;
                  return re_val;                                
               }
               //LDRH
               if (inner_bit(target,22,20)==5 && inner_bit(target,7,4)==13){
                  re_val = 20;
                  return re_val;                                
               }
               
            }                                
         }
         
         //B
         if (inner_bit(target,31,24)==234){
             re_val = 22;
             return re_val;                         
         }
         //BL
         if (inner_bit(target,31,24)==235){
             re_val = 23;
             return re_val;                         
         }
         //BEQ
         if (inner_bit(target,31,24)==10){
             re_val = 24;
             return re_val;                         
         }
         //BNE
         if (inner_bit(target,31,24)==26){
             re_val = 25;
             return re_val;                         
         }
         //BLT
         if (inner_bit(target,31,24)==186){
             re_val = 26;
             return re_val;                         
         }
         //BLE
         if (inner_bit(target,31,24)==218){
             re_val = 27;
             return re_val;                         
         }
         //BGT
         if (inner_bit(target,31,24)==202){
             re_val = 28;
             return re_val;                         
         }
         //BGE
         if (inner_bit(target,31,24)==170){
             re_val = 29;
             return re_val;                         
         }
         //BLO
         if (inner_bit(target,31,24)==58){
             re_val = 30;
             return re_val;                         
         }
         //BLS
         if (inner_bit(target,31,24)==154){
             re_val = 31;
             return re_val;                         
         }
         //BHI
         if (inner_bit(target,31,24)==138){
             re_val = 32;
             return re_val;                         
         }
         //BHS
         if (inner_bit(target,31,24)==42){
             re_val = 33;
             return re_val;                         
         }
         //BVS
         if (inner_bit(target,31,24)==106){
             re_val = 34;
             return re_val;                         
         }
         //BVC
         if (inner_bit(target,31,24)==122){
             re_val = 35;
             return re_val;                         
         }
         //BMI
         if (inner_bit(target,31,24)==74){
             re_val = 36;
             return re_val;                         
         }
         //BPL
         if (inner_bit(target,31,24)==90){
             re_val = 37;
             return re_val;                         
         }
         
         
                     //CMP
         if (inner_bit(target,31,26)==56 && inner_bit(target,25,21)==10){
            re_val = 38;
            return re_val;                                
         }
         
         return re_val; 
}




int main(){   
    
    int i=0, j=0;
    	    
    //16 rigster
    unsigned char reg [4*16] = {0};
    //I memory
    unsigned char ins [4*2048] = {0};
    //D memory
    unsigned char data [4*2048] = {0};
    //pc
    unsigned int pc = 0;
    //flag
    unsigned char flags [4] = {0};
    
    //for getting numbers of instructions
    unsigned char num_ins [4] = {0};
    unsigned int val_ins = 0;
    //for getting numbers of data memory
    unsigned char num_data [4] = {0};
    unsigned int val_data = 0;
    
    // Declare file variables.
	FILE *ii;
	FILE *id;
	FILE *snp;
	//open file~
    ii = fopen("iimage.bin", "rb");
    id = fopen("dimage.bin", "rb");	
    snp = fopen( "snapshot.rpt", "w" );
    
    //if the two file is not exist
    if (ii==NULL || id==NULL)
       return 0;
       
    //get pc into $r15
    for (i=0;i<4;i++){
        fread(&reg[4*15+i],1,1,ii);
    }
    reverse(&reg[4*15]);
    pc = get_decimal(&reg[4*15]);
    printf("$r15 =  %02X%02X%02X%02X\n",reg[4*15],reg[4*15+1],reg[4*15+2],reg[4*15+3]);    
    printf("pc = %d\n",pc);    
    
    
    //numbers of instructions in I memory
    for (i=0;i<4;i++){
        fread(&num_ins[i],1,1,ii);
    }
    reverse(num_ins);
    val_ins = get_decimal(num_ins);
    printf("num_ins =  %02X%02X%02X%02X\n",num_ins[0],num_ins[1],num_ins[2],num_ins[3]);    
    printf("val_ins = %d\n",val_ins);
    
    //get LR into $r13
    for (i=0;i<4;i++){
        fread(&reg[4*13+i],1,1,id);
    }
    reverse(&reg[4*13]);
    printf("$r13 =  %02X%02X%02X%02X\n",reg[4*13],reg[4*13+1],reg[4*13+2],reg[4*13+3]);    
    
    //numbers of data in D memory
    for (i=0;i<4;i++){
        fread(&num_data[i],1,1,id);
    }
    reverse(num_data);
    val_data = get_decimal(num_data);
    printf("num_data =  %02X%02X%02X%02X\n",num_data[0],num_data[1],num_data[2],num_data[3]);    
    printf("val_data = %d\n",val_data);
    
    
    //get all instructions
    for (i=pc ;i<pc+val_ins*4;i++){
        fread(&ins[i],1,1,ii);   
    }
    for (i=pc ;i<pc+val_ins*4;i=i+4){
           reverse(&ins[i]);
    }
    printf("*********************   I Memory    ***********************************\n");
    for (i=pc ;i<pc+val_ins*4;i=i+4){
        printf("%3d   %02X%02X%02X%02X   %02X\n",i,ins[i],ins[i+1],ins[i+2],ins[i+3],i);                      
    }  
    
    //get all data
    for (i=0 ;i<val_data*4;i++){
        fread(&data[i],1,1,id);   
    }
    for (i=0 ;i<val_data*4;i=i+4){
           reverse(&data[i]);
    }
    printf("*********************   D Memory    ***********************************\n");
    for (i=0 ;i<val_data*4;i=i+4){
        printf("%3d   %02X%02X%02X%02X\n",i,data[i],data[i+1],data[i+2],data[i+3]);                      
    }  
       
    
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");          
    //instruction judge
    
    
    for (i=pc;i<pc+val_ins*4;i=i+4){
        printf("%d\n",ins_judgement(&ins[i]));    
    }        
    
    int cycle = 0 ;
    int count =0 ;
    
        
    
    while(1) {
             
             //snapshot
             print_snapshot(snp,cycle++,reg);  
             
             pc = get_decimal(&reg[15*4]);
             printf("cycle :%d | pc = :%d\n",cycle,pc);
             //HALT detect
             if ( inner_bit(&ins[pc],31,28) == 15)
                break;
             switch (ins_judgement(&ins[pc])){
                     case 1:
                          func_ADD(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 2:
                          func_ADDI(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 3:
                          func_SUB(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 4:
                          func_SUBI(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 5:
                          func_AND(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 6:
                          func_ANDI(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 7:
                          func_MVN(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 8:
                          func_MVNI(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 9:
                          func_ORR(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 10:
                          func_ORRI(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 11:
                          func_EOR(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 12:
                          func_EORI(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 13:
                          func_MOV(&ins[pc],reg,flags);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 14:
                          func_LDR(&ins[pc],reg,data);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 15:
                          func_STR(&ins[pc],reg,data);
                          pc = pc + 4;
                          write_method(&reg[15*4],pc);
                          break;
                     case 16:
                          func_LDRH(&ins[pc],reg,data);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 17:
                          func_LDRSH(&ins[pc],reg,data);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 18:
                          func_STRH(&ins[pc],reg,data);
                          pc = pc + 4;
                          write_method(&reg[15*4],pc);
                          break;
                     case 19:
                          func_LDRB(&ins[pc],reg,data);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 20:
                          func_LDRSB(&ins[pc],reg,data);
                          //if rd ==15 do not add 4 to pc
                          if  ( inner_bit(&ins[pc],15,12)!=15 ){
                              pc = pc + 4;
                              write_method(&reg[15*4],pc);
                          }
                          break;
                     case 21:
                          func_STRB(&ins[pc],reg,data);
                          pc = pc + 4;
                          write_method(&reg[15*4],pc);
                          break;
                     case 22:
                          func_B(&ins[pc],reg);
                          break;
                     case 23:
                          func_BL(&ins[pc],reg);
                          break;
                     case 24:
                          func_BEQ(&ins[pc],reg,flags);
                          break;
                     case 25:
                          func_BNE(&ins[pc],reg,flags);
                          break;
                     case 26:
                          func_BLT(&ins[pc],reg,flags);
                          break;
                     case 27:
                          func_BLE(&ins[pc],reg,flags);
                          break;
                     case 28:
                          func_BGT(&ins[pc],reg,flags);
                          break;
                     case 29:
                          func_BGE(&ins[pc],reg,flags);
                          break;
                     case 30:
                          func_BLO(&ins[pc],reg,flags);
                          break;
                     case 31:
                          func_BLS(&ins[pc],reg,flags);
                          break;
                     case 32:
                          func_BHI(&ins[pc],reg,flags);
                          break;
                     case 33:
                          func_BHS(&ins[pc],reg,flags);
                          break;
                     case 34:
                          func_BVS(&ins[pc],reg,flags);
                          break;
                     case 35:
                          func_BVC(&ins[pc],reg,flags);
                          break;
                     case 36:
                          func_BMI(&ins[pc],reg,flags);
                          break;
                     case 37:
                          func_BPL(&ins[pc],reg,flags);
                          break;
                     case 38:
                          func_CMP(&ins[pc],reg,flags);
                          pc = pc + 4;
                          write_method(&reg[15*4],pc);
                          break;
             }    
             
             count++;                                
    }
    printf("*********************   D Memory    ***********************************\n");
    for (i=0 ;i<val_data*4;i=i+4){
        printf("%3d   %02X%02X%02X%02X\n",i,data[i],data[i+1],data[i+2],data[i+3]);                      
    }  
       
    
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");          
    


    fclose(ii);
    fclose(id);
    fclose(snp);
    	
    	
   	system("PAUSE");
	return 0;
}
