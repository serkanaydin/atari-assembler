// to compile, gcc assembler.c -o assembler
// No error check is provided.
// Variable names cannot start with numeric characters, ie, with 0-9.
// hexadecimals are twos complement.
// first address of the code section is zero, and the data section follows the code section in memory.
// four tables are formed: jump table, ldi table, label table and variable table.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Converts a hexadecimal string to integer.
int hex2int( char* hex)
{
    int result=0;

    while ((*hex)!='\0')
    {
        if (('0'<=(*hex))&&((*hex)<='9'))
            result = result*16 + (*hex) -'0';
        else if (('a'<=(*hex))&&((*hex)<='f'))
            result = result*16 + (*hex) -'a'+10;
        else if (('A'<=(*hex))&&((*hex)<='F'))
            result = result*16 + (*hex) -'A'+10;
        hex++;
    }
    return(result);
}


main()
{
    FILE *fp;
    char line[100];
    char *token = NULL;
    char *op1, *op2, *op3, *label;
    char ch;
    int  chch;

    int program[10000];
    int counter=0;  //holds the address of the machine code instruction


    struct label_or_variable
    {
        int location;
        char *name;
    };
   char opntableName[60][10];
   int opntableValue[60];
// A label is a symbol which mark a location within the code section. In the example 
// program above, the strings "lpp", "loop" and "lp1" are labels. 
// In reptile, labels are used by jump, jz and ldi instructions.  
    struct label_or_variable labeltable[500]; //there can be 50 labels at most in our programs
    int nooflabels = 0;                       //number of labels encountered during assembly.

    // A variable is a symbol which mark a location within the data section. In the example
// program above, the strings "", "" and "" are variables.
// In reptile, variables are used by ldi instructions.
    struct label_or_variable variabletable[500]; // The list of variables in .data section and their locations.
    int noofvariables = 0;    //number of jumps encountered during assembly. 

// Jump instructions cannot be assembled readily because we may not know the value of 
// the label when we encountered a jump instruction. This happens if the label used by
// that jump instruction appear below that jump instruction. This is the situation 
// with the label "loop" in the example program above. Hence, the location of jump 
// instructions must be stored.
    struct label_or_variable jumptable[1000]; //There can be at most 100 jumps
    int noofjumps=0;                        //number of jump instructions encountered during assembly.    


//Variables and labels are used by ldi instructions.
//The memory for the variables are traditionally allocated at the end of the code section.
//Hence their addresses are not known when we assemble a ldi instruction. Also, the value of 
//a label may not be known when we encounter a ldi instruction which uses that label.
//Hence, the location of the ldi instructions must be kept, and these instructions must be 
//modified when we discover the address of the label or variable that it uses.
    struct label_or_variable lditable[100];
    int noofldis=0;



    fp = fopen("input.txt","r");

    if (fp != NULL)
    {
        while(fgets(line,sizeof line,fp)!= NULL)  //skip till .code section
        {
            token=strtok(line,"\n\t\r ");
            if (strcmp(token,".code")==0 )
                break;
        }
        while(fgets(line,sizeof line,fp)!= NULL)
        {
            token=strtok(line,"\n\t\r ");  //get the instruction mnemonic or label

//========================================   FIRST PASS  ======================================================
            while (token)
            {

                 if (strcmp(token,"call")==0)  //-------------- JUMP and CALL -----------------------------
                {
                    op1 = strtok(NULL,"\n\t\r ");            //read the label string
                    jumptable[noofjumps].location = counter;    //write the jz instruction's location into the jumptable
                    op2=(char*)malloc(sizeof(op1));         //allocate space for the label
                    strcpy(op2,op1);                //copy the label into the allocated space
                    jumptable[noofjumps].name=op2;            //point to the label from the jumptable
                    noofjumps++;//skip to the next empty location in jumptable
                        program[counter]=0xa000; //write the incomplete instruction (just opcode) to memory
                    counter++;                    //skip to the next empty location in memory.
                }
                 else if(strcmp(token,"or")==0)  //-------------- JUMP and CALL -----------------------------
                 {
                     program[counter]=0x0002;
                     counter++;
                 }
                 else if(strcmp(token,"ret")==0)  //-------------- JUMP and CALL -----------------------------
                 {
                     program[counter]=0x0003;
                     counter++;
                 }
                 else if(strcmp(token,"CHNG")==0)  //-------------- JUMP and CALL -----------------------------
                 {
                     program[counter]=0x000F;
                     counter++;
                 }
                 else if(token[0]=='C' ){                                                               //in this case, the 2nd 16-bits of the ldi instruction cannot be generated.
                    lditable[noofldis].location = counter;                 //record the location of this 2nd 16-bit
                    //in the lditable array.
                     char* temp=(char*)malloc(sizeof(token));
                     strcpy(temp,token);
                    lditable[noofldis].name= temp;
                    noofldis++;
                    counter++;
                }
                 else //------WHAT IS ENCOUNTERED IS NOT AN INSTRUCTION BUT A LABEL. UPDATE THE LABEL TABLE--------
                {
                    labeltable[nooflabels].location = counter;  //read the label and update labeltable.
                    op1=(char*)malloc(sizeof(token));
                    strcpy(op1,token);
                    labeltable[nooflabels].name=op1;
                    nooflabels++;
                }
                token = strtok(NULL,",\n\t\r ");  // if what is read before is an instruction, this will be NULL
                //if what is read before is an label, this will be an opcode.
            }
        }


//================================= SECOND PASS ==============================

//supply the address fields of the jump and jz instructions by matching jumptable and labeltable
        int i,j;
        for (i=0; i<noofjumps;i++)   //for all jump/jz instructions encountered
        {
            j=0;
            while ((j<nooflabels)&&( strcmp(jumptable[i].name , labeltable[j].name ) != 0 ))  //if the label for this jump/jz does not match with the 
                j++;                                            // jth label in the labeltable, check the next label..
            program[jumptable[i].location] +=(labeltable[j].location-jumptable[i].location-1)&0x0fff;       //copy the jump address into memory.
        }


//search for the start of the .data segment
        rewind(fp);
        while(fgets(line,sizeof line,fp)!= NULL)  //skip till .data, if no .data, also ok.
        {
            token=strtok(line,"\n\t\r ");
            if (strcmp(token,".data")==0 )
                break;

        }

// process the .data segment and generate the variabletable[] array.
        int dataarea=0;
        while(fgets(line,sizeof line,fp)!= NULL)
        {
            token=strtok(line,"\n\t\r ");
            if (strcmp(token,".code")==0 )  //go till the .code segment
                break;
            else if (token[strlen(token)-1]==':')
            {
                token[strlen(token)-1]='\0';  //will not cause memory leak, as we do not do malloc
                variabletable[noofvariables].location=counter+dataarea;
                op1=(char*)malloc(sizeof(token));
                strcpy(op1,token);
                variabletable[noofvariables].name=op1;
                token = strtok(NULL,",\n\t\r ");
                if (token==NULL)
                    program[counter+dataarea]=0;
                else if (strcmp(token, ".space")==0)
                {
                    token=strtok(NULL,"\n\t\r ");
                    dataarea+=atoi(token);
                }
                else if((token[0]=='0')&&(token[1]=='x'))
                    program[counter+dataarea]=hex2int(token+2)&0xffff;
                else if ((  (token[0])=='-') || ('0'<=(token[0])&&(token[0]<='9'))  )
                    program[counter+dataarea]=atoi(token)&0xffff;
                noofvariables++;
                dataarea++;
            }
        }

// supply the address fields for the ldi instructions from the variable table
        for( i=0; i<noofldis;i++)
        {
            j=0;
            while ((j<noofvariables)&&( strcmp( lditable[i].name , variabletable[j].name)!=0 ))
                j++;
            if (j<noofvariables)
                program[lditable[i].location] = program[variabletable[j].location];
        }


// supply the address fields for the ldi instructions from the label table
        for( i=0; i<noofldis;i++)
        {
            j=0;
            while ((j<nooflabels)&&( strcmp( lditable[i].name , labeltable[j].name)!=0 ))
                j++;
            if (j<nooflabels){
                program[lditable[i].location] = (labeltable[j].location)&0x0fff;
                printf("%d %d %d\n", i, j, (labeltable[j].location));
            }
        }


//display the resulting tables
        printf("LABEL TABLE\n");
        for (i=0;i<nooflabels;i++)
            printf("%d %s\n", labeltable[i].location, labeltable[i].name);
        printf("\n");
        printf("JUMP TABLE\n");
        for (i=0;i<noofjumps;i++)
            printf("%d %s\n", jumptable[i].location, jumptable[i].name);
        printf("\n");
        printf("VARIABLE TABLE\n");
        for (i=0;i<noofvariables;i++)
            printf("%d %s\n", variabletable[i].location, variabletable[i].name);
        printf("\n");
        printf("LDI INSTRUCTIONS\n");
        for (i=0;i<noofldis;i++)
            printf("%d %s\n", lditable[i].location, lditable[i].name);
        printf("\n");
        fclose(fp);
        fp = fopen("RAM","w");
        fprintf(fp,"v2.0 raw\n");
        for (i=0;i<counter+dataarea;i++)
            fprintf(fp,"%04x\n",program[i]);
    }
}