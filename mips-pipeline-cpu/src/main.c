#include "R_Type.h"
#include "I_Type.h"
#include "J_Type.h"
#include "Other.h"

#include <stdio.h> 
#include <stdlib.h>






void check(int opcode , int funct){
           
                         
           switch (opcode){
                  /***** R TYPE ****************/
                  case 0 :
                                
                                
                                switch (funct){
                                       case 32 :
                                            printf("add");
                                            
                                            break;
                                       case 34 :
                                            printf("sub");
                                                                                       
                                            break;
                                       case 36 :
                                            printf("and");
                                             
                                            break;                                            
                                       case 37 :
                                            printf("or");
                                             
                                            break;
                                       case 38 :
                                            printf("xor");     
                                            
                                            break;
                                       case 39 :
                                            printf("nor");
                                            
                                            break;
                                       case 40 :
                                            printf("nand"); 
                                             
                                            break;
                                       case 42 :
                                            printf("slt");     
                                            
                                            break;
                                       case 0 :
                                            printf("sll");     
                                            
                                            break;
                                       case 2 :
                                            printf("srl");     
                                            
                                            break;
                                       case 3 :
                                            printf("sra");     
                                             
                                            break;
                                       case 8 :
                                            printf("jr");
                                               
                                            break;
                                       default :
                                            printf("ZZZZZZZZ");   
                                               
                                }
                       
                       break;                  
                  /***** I TYPE ****************/
                  case 8 :
                       printf("addi");
                       
                       break;             
                  case 35 :
                       printf("lw");
                       
                       break;             
                  case 33 :
                       printf("lh");
                       
                       break;             
                  case 37 :
                       printf("lhu");
                       
                       break;             
                  case 32 :
                       printf("lb");
                        
                       break;             
                  case 36 :
                       printf("lbu");
                       
                       break;             
                  case 43 :
                       printf("sw");
                       
                       break;             
                  case 41 :
                       printf("sh");
                       
                       break;             
                  case 40 :
                       printf("sb");
                       
                       break;             
                  case 15 :
                       printf("lui");
                       
                       break;             
                  case 12 :
                       printf("andi");
                      
                       break;             
                  case 13 :
                       printf("ori");
                       
                       break;             
                  case 14 :
                       printf("nori");
                      
                       break;             
                  case 10 :
                       printf("slti");
                      
                       break;             
                  case 4 :
                       printf("beq");
                       
                       break;             
                  case 5 :
                       printf("bne");
                       
                       break;
                  /***** J TYPE ****************/             
                  case 2 :
                       printf("j");
                       
                       break;             
                  case 3 :
                       
                       printf("jal");
                       break;
                  /***** S TYPE ****************/             
                  case 63 :
                       printf("halt");
                       break;
                  /***** S TYPE ****************/              
                  default :             
                       printf("XXXXX");
           }
            
           
       
}

void state_IF(unsigned char *ins,unsigned int *pc,unsigned char  *IF_ID,unsigned char  *IF_ID_nt,int *signal,int *flush){
     
     
     if ((ins[*pc]==0)&&(ins[*pc+1]==0)&&(ins[*pc+2]==0)&&(ins[*pc+3]==0)){
        IF_ID_nt[4]=1;
        printf("IF: NOP\n");                
     }
     else {
           int i = 0;
           /* next_state */
           for (i=0;i<4;i++){
               IF_ID_nt[i] = ins[*pc+i] ;     
           }
           printf("IF: ");
           for (i=0;i<4;i++){
               printf("%02X",ins[*pc+i]) ;     
           }
     }
     
     
     if (signal[0]==1){
        printf("IF: to_be_stalled\n");
        return;                  
     }    

}
void flushz(unsigned char*catch_up,unsigned char*IF_ID_nt){
     int i;
     
     for (i=0;i<4;i++)
         IF_ID_nt[i]=catch_up[i];
     
     
}



void ID_harzard(int opcode,int funct,int rs,int rt,unsigned char*IF_ID,unsigned char*ID_EX,unsigned char*EX_DM,unsigned char*DM_WB,unsigned char*tmp_2,int *signal,unsigned int *pc,unsigned char* catch_up,unsigned char *pc_tmp,unsigned char*ID_EX_nt){
    
    
    int i;
    /*R type*/
    if (opcode==0){
       /* d = s + t */
       if ((funct==32)||(funct==34)||(funct==36)||(funct==37)||(funct==38)||(funct==39)||(funct==40)||(funct==42)){
          if ((IF_ID[0]==35)||(IF_ID[0]==33)||(IF_ID[0]=37)||(IF_ID[0]=32)||(IF_ID[0]=36)){
              if (rs==ID_EX[0]||rs==ID_EX[5]||rt==ID_EX[0]||rt==ID_EX[5]){
                 signal[0]=1;
                 ID_EX_nt[20]=1;
                 *pc = *pc -4;
              }
          }      
       }
       /* d =  t */
       else if (funct==0||funct==2||funct==3){
            if ((IF_ID[0]==35)||(IF_ID[0]==33)||(IF_ID[0]=37)||(IF_ID[0]=32)||(IF_ID[0]=36)){
               if (rt==ID_EX[0]||rt==ID_EX[5]){
                  signal[0]=1;
                  ID_EX[20]=1;
                  *pc = *pc -4;               
               }                                           
            }
       }
       /* pc = s */
       else{
           if ((IF_ID[0]==35)||(IF_ID[0]==33)||(IF_ID[0]=37)||(IF_ID[0]=32)||(IF_ID[0]=36)){
              if (rs==ID_EX[0]||rs==ID_EX[5]){
                 signal[0]=1;
                 ID_EX[20]=1;
                 *pc = *pc -4;               
              }
          } 
       }  
    }
    /*I type*/
    else if(opcode==8||opcode==35||opcode==33||opcode==37||opcode==32||opcode==36||opcode==43||opcode==41||opcode==40||opcode==15||opcode==12||
         opcode==13||opcode==14||opcode==10||opcode==4||opcode==5){
         /*do nothing*/
         if (opcode==43||opcode==41||opcode==40||opcode==15){
            
         }
         /* s , t */
         else if (opcode==4||opcode==5){
                 if (rs==ID_EX[2]||rt==ID_EX[7]){
                    signal[0]=1;
                    ID_EX[20]=1;
                    for (i=0;i<4;i++)
                        catch_up[i]=IF_ID[i];
                    *pc_tmp = *pc;  
                    printf("to_be_stalled");
                 }
                 else if (rs==ID_EX[2]||rt==ID_EX[7]){
                      signal[0]=1;
                      ID_EX[20]=1;
                      for (i=0;i<4;i++)
                        catch_up[i]=IF_ID[i];
                     *pc_tmp = *pc;  
                    printf("to_be_stalled");   
                 }
                 
                 /*R  I type  need be forwarding*/
                 if (rs==EX_DM[15] && EX_DM[15]!=0){
                    if (EX_DM[15]==EX_DM[0]){
                       for (i=0;i<4;i++){
                           ID_EX[3+i]=EX_DM[1+i];    
                       }                         
                    }
                    if (EX_DM[15]==EX_DM[5]){
                       for (i=0;i<4;i++){
                           ID_EX[3+i]=EX_DM[6+i];    
                       }                         
                    }                 
                 }
                 if (rt==EX_DM[15] && EX_DM[15]!=0){
                    if (EX_DM[15]==EX_DM[0]){
                       for (i=0;i<4;i++){
                           ID_EX[8+i]=EX_DM[1+i];    
                       }                         
                    }
                    if (EX_DM[15]==EX_DM[5]){
                       for (i=0;i<4;i++){
                           ID_EX[8+i]=EX_DM[6+i];    
                       }                         
                    }                 
                 }
                 
                 if (opcode==4){
                    int count;
                    for (i=0;i<4;i++){
                        int count = 0;
                        if (IF_ID[3+i]==IF_ID[8+i])
                            count++;
                        if (count==4){
                             for(i=0;i<4;i++)
                             catch_up[i]=0;
                             *pc_tmp = *pc;        
                        }           
                    }           
                 }                 
                 if (opcode==5){
                    int count;
                    for (i=0;i<4;i++){
                        int count = 0;
                        if (IF_ID[3+i]==IF_ID[8+i])
                            count++;
                        if (count!=4){
                            for(i=0;i<4;i++)
                             catch_up[i]=0;
                             //*pc_tmp = *pc;           
                        }           
                    }           
                 }                 
                                        
         }
         else{
                   
         }
    }
    /* J jal do nothing*/
    else{
         
    }
    
}

void state_ID( unsigned char  *IF_ID ,unsigned char *ID_EX,unsigned char *EX_DM,unsigned char *DM_WB,
               unsigned char  *IF_ID_nt ,unsigned char *ID_EX_nt,unsigned char *EX_DM_nt,unsigned char *DM_WB_nt,
               unsigned char *reg,unsigned int *pc,int cycle,int *signal,int *flush,unsigned char *tmp_2,unsigned char *catch_up,unsigned char *pc_tmp)
               {
     
     
     /*
     if (signal[0]==1){
        printf("ID: to_be_stalled\n");
        return;                  
     }
     if (IF_ID[4]==1){
        ID_EX[20]=1;
        printf("ID: nop\n");
        return;      
     }
     else{
        ID_EX[20]=0;  
     }
     */
     if (IF_ID[4]==1){
        IF_ID_nt[4]=0;
        ID_EX_nt[20]=1;
        printf("ID: NOP\n");
             
     }
     else{      

           /*variable*/
           unsigned char opcode;
           unsigned char funct;
           int rs ,rt ,rd ,shamt=-1;
           int i,j;
           int tmp=0;
           
           opcode=IF_ID[0]>>2;
           ID_EX_nt[0]=opcode;


           switch (opcode){
                  /***** R TYPE ****************/
                  case 0 :
                                funct=IF_ID[3]<<2;                              
                                funct=funct>>2;
                                ID_EX_nt[1]=funct; 
                                
                                switch (funct){
                                       case 32 :
     
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            break;
                                       case 34 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            
                                            break;
                                       case 36 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            
                                            break;                                            
                                       case 37 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            
                                            break;
                                       case 38 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            
                                            break;
                                       case 39 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            
                                            break;
                                       case 40 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            
                                            break;
                                       case 42 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rs=get_rs(IF_ID);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            
                                            ID_EX_nt[2]=rs;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;
                                            
                                           
                                            
                                            break;
                                       case 0 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            shamt=get_shamt(IF_ID);
                                            
                                            ID_EX_nt[2]='N';
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            ID_EX_nt[17]=shamt;
                                            
                                            *pc = *pc +4;
                                            ID_EX_nt[21]=rd;       
                                            
                                            
                                            
                                            break;
                                       case 2 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            shamt=get_shamt(IF_ID);
                                            
                                            ID_EX_nt[2]='N';
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            ID_EX_nt[17]=shamt;
                                            
                                            *pc = *pc +4;   
                                            ID_EX_nt[21]=rd;    
                                            
                                           
                                            
                                            break;
                                       case 3 :
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            rt=get_rt(IF_ID);
                                            rd=get_rd(IF_ID);
                                            shamt=get_shamt(IF_ID);
                                            
                                            ID_EX_nt[2]='N';
                                            ID_EX_nt[7]=rt;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[8+i] = reg[rt*4+i];    
                                            }
                                            ID_EX_nt[12]=rd;
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[13+i] = reg[rd*4+i];    
                                            }
                                            ID_EX_nt[17]=shamt;
                                            
                                            *pc = *pc +4;   
                                            ID_EX_nt[21]=rd;    
                                            
                                            
                                            
                                            break;
                                       case 8 :
                                            
                                            ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                                            ID_EX_nt[2]=rs;
                                            ID_EX_nt[7]='N';
                                            ID_EX_nt[12]='N';
                                            
                                            for (i=0;i<4;i++){
                                                ID_EX_nt[3+i] = reg[rs*4+i];    
                                            }
                                            ID_EX_nt[21]=rd;
                                            
                                            
                                            
                                            break;
                                       default :
                                            printf("There are some error in the switch - funct");
                                            exit(1);
                                               
                                }
                       
                       break;                  
                  /***** I TYPE ****************/
                  ID_EX[1]=0;
                  
                  case 8 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 35 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       
                       ID_EX_nt[21]=rt;
                       
                       
                       break;             
                  case 33 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       
                       ID_EX_nt[21]=rt;
                       
                       
                       break;             
                  case 37 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 32 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                      
                       
                       break;             
                  case 36 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 43 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 41 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 40 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 15 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rt=get_rt(IF_ID);
                       
                       ID_EX_nt[2]='N';
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       
                       ID_EX_nt[21]=rt;
                       
                       
                       break;             
                  case 12 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       
                       ID_EX_nt[21]=rt;
                       
                       
                       break;             
                  case 13 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 14 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 10 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;             
                  case 4 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       
                       ID_EX_nt[21]=rt;
                       
                       
                       break;             
                  case 5 :
                       ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       rs=get_rs(IF_ID);
                       rt=get_rt(IF_ID);
                       
                                            
                       ID_EX_nt[2]=rs;
                       for (i=0;i<4;i++){
                           ID_EX_nt[3+i] = reg[rs*4+i];    
                       }
                       ID_EX_nt[7]=rt;
                       for (i=0;i<4;i++){
                           ID_EX_nt[8+i] = reg[rt*4+i];    
                       }
                       ID_EX_nt[12]='N';
                       
                       ID_EX_nt[18]=IF_ID[2];
                       ID_EX_nt[19]=IF_ID[3];
                       
                       *pc = *pc +4; 
                       ID_EX_nt[21]=rt;
                       
                       
                       
                       break;
                  /***** J TYPE ****************/             
                  case 2 :
                  ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       
                       func_j ( pc,IF_ID);
                       
                       
                       break;             
                  case 3 :
                      ID_harzard(opcode,funct, rs, rt,IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc, catch_up,pc_tmp,ID_EX_nt);
                       func_jal( pc,IF_ID,ID_EX);
                       
                       
                       break;
                  /***** S TYPE ****************/             
                  case 63 :
                        *pc=*pc+4;  
                       break;
                  /***** S TYPE ****************/              
                  default :             
                       printf("There are some error in the switch - funct");
                        exit(1);
                       
           }
            /*
            printf("In State ID >> ID_EX[0] %d\n",ID_EX[0]);
            printf("In State ID >> ID_EX[1] %d\n",ID_EX[1]);
            printf("In State ID >> opcode %d\n",opcode);
            printf("In State ID >> funct %d\n",funct);
            */
            printf("ID: ");
            check(opcode,funct);
            printf("\n");
            
}
}


void EX_harzard (int opcode,int funct,int rs,int rt,unsigned char*IF_ID,unsigned char*ID_EX,unsigned char*EX_DM,unsigned char*DM_WB,unsigned char*tmp_2,int *signal,unsigned int *pc){

     int i;
     
     
     /*self !!*/
     if (opcode==0){
        if (rs==DM_WB[2] && rs!=EX_DM[15] && DM_WB[2]!=0 ){
            for (i=0;i<4;i++)
                ID_EX[3+i]= DM_WB[3+i];           
        }
        else if (rs==EX_DM[15] && EX_DM[15]!=0 ){
            for (i=0;i<4;i++)
                ID_EX[3+i]= EX_DM[6+i]; 
        }
        
        if (rt==DM_WB[2] && rt!=EX_DM[15] && DM_WB[2]!=0 ){
            for (i=0;i<4;i++)
                ID_EX[8+i]= DM_WB[3+i];           
        }
        else if (rt==EX_DM[15] && EX_DM[15]!=0 ){
            if(EX_DM[15]==EX_DM[0])
                for (i=0;i<4;i++)   ID_EX[8+i]= EX_DM[1+i]; 
            else if(EX_DM[15]==EX_DM[5])
                for (i=0;i<4;i++)   ID_EX[8+i]= EX_DM[6+i]; 
        }
     }
     
    else if (opcode!=0 && opcode!=2 && opcode!=3){
       if (rs==DM_WB[2] && rs!=EX_DM[15] && DM_WB[2]!=0 ){
            for (i=0;i<4;i++)
                ID_EX[3+i]= DM_WB[3+i];           
        }
        else if (rs==EX_DM[15] && EX_DM[15]!=0 ){
           if(EX_DM[15]==EX_DM[0])
                for (i=0;i<4;i++)   ID_EX[8+i]= EX_DM[1+i]; 
            else if(EX_DM[15]==EX_DM[5])
                for (i=0;i<4;i++)   ID_EX[8+i]= EX_DM[6+i]; 
        }
    }
     
     else {
          if (opcode!=15 && opcode!=4 &&opcode!=5){
             if (rs!=DM_WB[2] && rs!=0){
                if (rs==tmp_2[0]){
                   ID_EX[3+i] = tmp_2[1+i];
                   printf("IF: DM_WB rs $(%d) >>EX\n",rs);                                 
                }
             } 
             if (rs==DM_WB[2] && rs!=0){
                ID_EX[3+i] = tmp_2[1+i];
                printf("IF: EX_DM rs $(%d) >>EX\n",rs);                                 
             }                  
          }
     }
     
}


void state_EX( unsigned char  *IF_ID ,unsigned char *ID_EX,unsigned char *EX_DM,unsigned char *DM_WB,
               unsigned char  *IF_ID_nt ,unsigned char *ID_EX_nt,unsigned char *EX_DM_nt,unsigned char *DM_WB_nt,
               unsigned char *reg,unsigned int *pc,int cycle,int *signal,int *flush,unsigned char *tmp_2)
               {
     /*      
     if (ID_EX[20]==1){
        EX_DM[14]=1;
        printf("EX: nop\n");
        return;      
     }
     else{
       EX_DM[14]=0;   
     }
     */
     if (ID_EX[20]==1){
        ID_EX_nt[20]=1;
        EX_DM_nt[14]=1;
        printf("EX: NOP\n");
     }
     else{
     
     
           int i;
           EX_DM_nt[10]=ID_EX[0];
           EX_DM_nt[11]=ID_EX[1];
           switch (ID_EX[0]){
                  /***** R TYPE ****************/
                  case 0 :
                                
                                switch (ID_EX[1]){
                                       case 32 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_add(ID_EX,3,8,ID_EX[12],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 34 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_sub(ID_EX,3,8,ID_EX[12],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            
                                            break;
                                       case 36 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_and(ID_EX,3,8,ID_EX[12],EX_DM_nt); 
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;                                            
                                       case 37 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_or(ID_EX,3,8,ID_EX[12],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 38 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_xor(ID_EX,3,8,ID_EX[12],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 39 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_nor(ID_EX,3,8,ID_EX[12],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 40 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_nand(ID_EX,3,8,ID_EX[12],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 42 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_slt(ID_EX,3,8,ID_EX[12],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 0 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_sll(ID_EX,8,ID_EX[12],ID_EX[17],EX_DM_nt);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 2 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_srl(ID_EX,8,ID_EX[12],ID_EX[17],EX_DM_nt);     
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 3 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            func_sra(ID_EX,8,ID_EX[12],ID_EX[17],EX_DM_nt);     
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       case 8 :
                                            
                                            EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                                            EX_DM_nt[15]=ID_EX[21];
                                            break;
                                       default :
                                            printf("There are some error in the switch - funct");
                                            
                                               
                                }
                       
                       break;                  
                  /***** I TYPE ****************/
                  case 8 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       func_addi(ID_EX,3,ID_EX[7],&ID_EX[18],EX_DM_nt);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 35 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 33 :
                      
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 37 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 32 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 36 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 43 :
                      
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 41 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 40 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                      
                       EX_DM_nt[0]=ID_EX[7];
                       for (i=0;i<4;i++){
                           EX_DM_nt[1+i]=ID_EX[8+i];                                       
                       }
                       EX_DM_nt[5]=ID_EX[2];
                       for (i=0;i<4;i++){
                           EX_DM_nt[6+i]=ID_EX[3+i];                                       
                       }
                       EX_DM_nt[12]=ID_EX[18];
                       EX_DM_nt[13]=ID_EX[19];
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 15 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       func_lui(ID_EX,8,ID_EX[7],&ID_EX[18],EX_DM_nt);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 12 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       func_andi(ID_EX,3,ID_EX[7],&ID_EX[18],EX_DM_nt);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 13 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       func_ori(ID_EX,3,ID_EX[7],&ID_EX[18],EX_DM_nt);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 14 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc); 
                       func_nori(ID_EX,3,ID_EX[7],&ID_EX[18],EX_DM_nt);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 10 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       func_slti(ID_EX,3,ID_EX[7],&ID_EX[18],EX_DM_nt);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 4 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 5 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       EX_DM_nt[15]=ID_EX[21];
                       break;
                  /***** J TYPE ****************/             
                  case 2 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       EX_DM_nt[15]=ID_EX[21];
                       break;             
                  case 3 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       EX_DM_nt[15]=ID_EX[21];
                       break;
                  /***** S TYPE ****************/             
                  case 63 :
                       
                       EX_harzard (ID_EX[0],ID_EX[1],ID_EX[2],ID_EX[7],IF_ID,ID_EX,EX_DM,DM_WB,tmp_2,signal,pc);
                       EX_DM_nt[15]=ID_EX[21];
                       break;
                  /***** S TYPE ****************/              
                  default :             
                       printf("There are some error in the switch - funct");
                       
           }
            printf("EX: ");
            check(ID_EX[0],ID_EX[1]);
            printf("\n");
            
}
}


void state_DM( unsigned char  *IF_ID ,unsigned char *ID_EX,unsigned char *EX_DM,unsigned char *DM_WB,
               unsigned char  *IF_ID_nt ,unsigned char *ID_EX_nt,unsigned char *EX_DM_nt,unsigned char *DM_WB_nt,
               unsigned char *reg,unsigned int *pc,int cycle,int *signal,int *flush,unsigned char *data)
               {
     
     int i;
     
     
     if (EX_DM[14]==1){
        DM_WB_nt[7]=1;
        EX_DM_nt[14]=0;
        printf("DM: NOP\n");
     }
     else{
           
    
     
     
     

     
     DM_WB_nt[0]=EX_DM[10];
     DM_WB_nt[1]=EX_DM[11];
     
     if (EX_DM[10]==0){
        if (EX_DM[11]!=8){
           DM_WB_nt[2]=EX_DM[5];
           for (i=0;i<4;i++){
               DM_WB_nt[3+i]=EX_DM[6+i];    
           }                        
        }                                  
     }     
     
     if (EX_DM[10]==8 |EX_DM[10]==15|EX_DM[10]==12|EX_DM[10]==13|EX_DM[10]==14|EX_DM[10]==10|EX_DM[10]==3 ){
        DM_WB[2]=EX_DM[0];
        for (i=0;i<4;i++){
            DM_WB_nt[3+i]=EX_DM[1+i];    
        }                        
     }     
     
     if (EX_DM[10]==35){
        func_lw (EX_DM,6,EX_DM[0],&EX_DM[12],data,DM_WB_nt);
     }
     if (EX_DM[10]==33){
        func_lh (EX_DM,6,EX_DM[0],&EX_DM[12],data,DM_WB_nt);
        
     }
     if (EX_DM[10]==37){
        func_lhu (EX_DM,6,EX_DM[0],&EX_DM[12],data,DM_WB_nt);
     }
     if (EX_DM[10]==32){
        func_lb (EX_DM,6,EX_DM[0],&EX_DM[12],data,DM_WB_nt);
     }
     if (EX_DM[10]==36){
        func_lbu (EX_DM,6,EX_DM[0],&EX_DM[12],data,DM_WB_nt);
     }
     
     
     if (EX_DM[10]==43){
        func_sw(EX_DM,6,1,&EX_DM[12],data); 
     }
     if (EX_DM[10]==41){
        func_sh(EX_DM,6,1,&EX_DM[12],data);
     }
     if (EX_DM[10]==40){
        func_sb(EX_DM,6,1,&EX_DM[12],data);
     }
     
     printf("DM: ");
     check(EX_DM[10],EX_DM[11]);
     printf("\n");
     
}     
}

void state_WB(unsigned char *reg,unsigned char *DM_WB,unsigned char *DM_WB_nt,int cycle){
     
     
     if (DM_WB[7]==1){
        DM_WB_nt[7]=0;
        printf("WB: NOP\n");
            
     }
     else{     
     
     int i;
     
     if (DM_WB[0]==0){
        if (DM_WB[1]!=8){
           for (i=0;i<4;i++){
               reg[DM_WB[2]*4+i]=DM_WB[3+i];    
           }
        }                                  
     }         


     if (DM_WB[0]==8|DM_WB[0]==35|DM_WB[0]==33|DM_WB[0]==37|DM_WB[0]==32|DM_WB[0]==36|
        DM_WB[0]==15|DM_WB[0]==12|DM_WB[0]==13|DM_WB[0]==14|DM_WB[0]==10)
     {
           for (i=0;i<4;i++){
               reg[DM_WB[2]*4+i]=DM_WB[3+i];    
           }
                                 
     }         
     printf("WB: ");
     check(DM_WB[0],DM_WB[1]);
     printf("\n");
}   
}

 

int main(){
    
    int i=0, j=0;
    	    
    /* Declare Register */
    unsigned char *reg = (unsigned char*)malloc(sizeof(char)*4*32);
    unsigned int  *pc= (unsigned int*)malloc(sizeof(int));
	unsigned char  *start = (unsigned char*)malloc(sizeof(char)*4);
    unsigned char  *num_wd_I = (unsigned char*)malloc(sizeof(char)*4);   
    unsigned char  *ins = (unsigned char*)malloc(sizeof(char)*4*2048);
    unsigned char  *sp = (unsigned char*)malloc(sizeof(char)*4);
    unsigned char  *num_wd_D = (unsigned char*)malloc(sizeof(char)*4);
    unsigned char  *data = (unsigned char*)malloc(sizeof(char)*4*2048);
    
    unsigned char  *IF_ID = (unsigned char*)malloc(sizeof(char)*5);
    unsigned char  *ID_EX = (unsigned char*)malloc(sizeof(char)*22);
    unsigned char *EX_DM = (unsigned char*)malloc(sizeof(char)*16);
    unsigned char *DM_WB = (unsigned char*)malloc(sizeof(char)*8);
    unsigned int  *tmp_pc= (unsigned int*)malloc(sizeof(int));
    unsigned char  *tmp_2= (unsigned char*)malloc(sizeof(char)*7);

    /*temp part2*/
    unsigned char  *IF_ID_nt = (unsigned char*)malloc(sizeof(char)*5);
    unsigned char  *ID_EX_nt = (unsigned char*)malloc(sizeof(char)*22);
    unsigned char *EX_DM_nt = (unsigned char*)malloc(sizeof(char)*16);
    unsigned char *DM_WB_nt = (unsigned char*)malloc(sizeof(char)*8);
    
    unsigned char *catch_up =(unsigned char*)malloc(sizeof(char)*4);
    unsigned char *pc_tmp;



    for (i=0;i<5;i++){
        IF_ID[i]=0;
        IF_ID_nt[i]=0;
    }
    for (i=0;i<21;i++){
        ID_EX[i]=0;
        ID_EX_nt[i]=0;
    }
    for (i=0;i<15;i++){
        EX_DM[i]=0;
        EX_DM_nt[i]=0;
    }
    for (i=0;i<8;i++){
        DM_WB[i]=0;
        DM_WB_nt[i]=0;
    }
    
    
    
    int cycle=0;
    int starting[5] = {0};
    int signal = 0;
    int flush=0;
    int enable=0;
    
    
    unsigned int pc_bytes[5];
    
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
	FILE *ii;
	FILE *id;
	FILE *snp;
	
    ii = fopen("iimage.bin", "rb");
    id = fopen("dimage.bin", "rb");	
    snp = fopen( "snapshot.txt", "w" );
    
    if (ii!=NULL&&id!=NULL){
       /*PC*/
       for (i=0;i<4;i++){
           fread((start+i),1,1,ii);
       }
       reverse(start);
       /*
       for (i=0;i<4;i++){
           printf("%02X",*(start+i));     
       }
       printf("\n");
       */
       
       for ( i=0;i<4;i++){
          pc_bytes[i]=start[i];
          pc_bytes[i]=pc_bytes[i]<<24;
          pc_bytes[i]=pc_bytes[i]>>i*8;
          pc_bytes[4]=pc_bytes[4]+ pc_bytes[i];    
       }
       printf("pc_bytes=%d\n",pc_bytes[4]);
       
       *pc=pc_bytes[4];
       
       /*words in I memory*/
       for (i=0;i<4;i++){
           fread((num_wd_I+i),1,1,ii);
       }
       reverse(num_wd_I);
       /*
       for (i=0;i<4;i++){
           printf("%02X",*(num_wd_I+i));     
       }
       printf("\n");
       */
       
       
       /* num_wd_I  in decimal*/
       int conts_I = 256*256*256*(*(num_wd_I))+256*256*(*(num_wd_I+1))+256*(*(num_wd_I+2))+1*(*(num_wd_I+3));
       /*
       printf("%d",conts_I);
       printf("\n");       
       */
       /*load instructions to I memory*/
       for (i=pc_bytes[4];i<pc_bytes[4]+conts_I*4;i++){
           fread(&ins[i],1,1,ii);
       }

       for (i=pc_bytes[4];i<pc_bytes[4]+conts_I*4;i=i+4){
           reverse(&ins[i]);
       }
       
       
       printf("*********************   I Memory    ***********************************\n");
       for (i=pc_bytes[4];i<pc_bytes[4]+conts_I*4;i=i+4){
              printf("%3d   %02X%02X%02X%02X\n",i,ins[i],ins[i+1],ins[i+2],ins[i+3]);                      
       }  
       
       printf("\n");  
       printf("*********************   D Memory    ***********************************\n");
       printf("\n");       
       /**********************************************************************************************/       
       /*SP*/
       for (i=0;i<4;i++){
           fread((sp+i),1,1,id);
       }
       reverse(sp);
       for (i=0;i<4;i++){
           reg[29*4+i]=sp[i];
       }
       
       
       /*
       for (i=0;i<4;i++){
           printf("%02X",*(sp+i));     
       }
       printf("\n");
       */
       
       
       /*words in D memory*/
       for (i=0;i<4;i++){
           fread((num_wd_D+i),1,1,id);
       }
       reverse(num_wd_D);
       /*
       for (i=0;i<4;i++){
           printf("%02X",*(num_wd_D+i));     
       }
       printf("\n");
       */
       /* num_wd_D  in decimal*/
       int conts_D = 256*256*256*(*(num_wd_D))+256*256*(*(num_wd_D+1))+256*(*(num_wd_D+2))+1*(*(num_wd_D+3));
       
       /*
       printf("%d",conts_D);
       printf("\n");       
       */
       /*data~*/
       for (i=0;i<conts_D;i++){
           for (j=0;j<4;j++){
               fread(&data[i*4+j],1,1,id);
               /*fread(data+i*4+j,1,1,id);*/
           }
       }
       
       for (i=0;i<conts_D;i++){
           reverse(&data[i*4]);
       }  
       
       for (i=0;i<conts_D;i++){
           for (j=0;j<4;j++){
               printf("%02X",data[i*4+j]);
           }
           printf("\n");
       }
       
       printf("%d\n",conts_I);
       
       printf("************ test Start***************\n\n");
       
       int count = 0;
       int cycle = 0;
       
       for (i=0;i<conts_I;i++){
           
           if (count<=4){
              starting[count++]=1;
           }
           printf("------------cycle :%d\n",cycle);
           
           if (starting[4])
              state_WB(reg,DM_WB,DM_WB_nt, cycle);
           else{
                printf("WB: nop\n");     
           }
           if (starting[3])
              state_DM(IF_ID ,ID_EX,EX_DM,DM_WB,IF_ID_nt ,ID_EX_nt,EX_DM_nt,DM_WB_nt,reg,pc,cycle,&signal,&flush,data);
           else{
                printf("DM: nop\n");     
           }
           if (starting[2])
              state_EX(IF_ID ,ID_EX,EX_DM,DM_WB,IF_ID_nt ,ID_EX_nt,EX_DM_nt,DM_WB_nt,reg,pc,cycle,&signal,&flush,tmp_2);
           else{
                printf("EX: nop\n");     
           }
           if (starting[1]){
              state_ID(IF_ID ,ID_EX,EX_DM,DM_WB,IF_ID_nt ,ID_EX_nt,EX_DM_nt,DM_WB_nt,reg,pc,cycle,&signal,&flush,tmp_2,catch_up,pc_tmp);
           }
           else{
                printf("ID: nop\n");     
           }
           if (starting[0])
              state_IF(ins,pc,IF_ID,IF_ID_nt,&signal,&flush);
           else{
                printf("IF: nop\n");     
           }
           
           if (enable){
              flushz(catch_up,IF_ID_nt);        
           }
           
           printf("\n%d\n",*pc);
           
           /*renew!!!*/
           signal=0;
           flush=0;
           signal=0;
           for (j=0;j<6;j++){
               tmp_2[j]=0;    
           }
           for (j=0;j<5;j++){
               IF_ID[j]=IF_ID_nt[j];    
           }
           for (j=0;j<21;j++){
               ID_EX[j]=ID_EX_nt[j];    
           }
           for (j=0;j<15;j++){
               EX_DM[j]=EX_DM_nt[j];    
           }
           for (j=0;j<8;j++){
               EX_DM[j]=EX_DM_nt[j];    
           }
           
           
           cycle++;
           printf("\n");
       }
       
       printf("************test End ***************\n\n");
       
   
       
       
                
    } 
    free(reg);
    free(ins);
    free(data);
    free(pc);
    free(start);
    free(num_wd_I);
    free(num_wd_D);
    
    
    
    fclose(ii);
    fclose(id);
    
    system("PAUSE");
    

    return 0;
}
