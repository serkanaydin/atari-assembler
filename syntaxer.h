#include <stdio.h>
#include <ctype.h>
int nxsc() {
    return program[++cpc];    //cpc points to the syntax_table[]
}

int erem(){
    return 0;
}

int edata(){
    return 0;
}

int eif(){
    return 0;
}

int echng(){
    outbuff[cox-1] = (char)(program[cpc++]&0x00ff); //outbuff is a char arr but program short arr
    return(1);
}

void fail(){

}

int tncon(){

}

int srcont(){
    skblank();
    char temp=cix;
    if(temp != svontx){
        svontx= temp;
        if(search(OPNTAB_STRING)){                     //STENUMU AYARLIYOR
            svontc =0;
            return 1;
        }
        svontl = bufferIndex;
        temp = OPNTAB[stenum].val.num;                   //
        svontc = temp;
    }
    temp = program[cpc];
    if(svontc == temp){
        setcode(temp);
        cix = svontl;
        return 1;
    }
    else if(temp >= 0x44) {
        setcode(svontc);
        cix = svontl;
        return 1; }
    else{
        svontc='\0';
        return 0;
    }
}

tvar (int tvtype){   // tvtype=0x0 means numeric, tvtype=0x80 means string.
    int tvscix;

    skblank();
    tvscix=cix;
    if (isalpha(inbuff[cix])){     //is the first character alphabetic?
        srcont();   //is it a reserved word?
        if ( svontc == 0  || (svontc==1)&&(inbuff[svontl]>=0x30 )){  //not reserved word, or it is
            do                                                  //a non-reserved word whose prefix
                cix++;		                            //is a reserved word..
            while ( isalpha(inbuff[cix]) | !isdigit(inbuff[cix]) );

            if (tvtype == 0x80 )
                if ( inbuff[cix] == '$')
                    cix++;      //skip over $
                else
                    return 1;
            else if ( tvtype == 0x0 )
                if ( inbuff[ cix ] == '(' ) {
                    cix++;      //skip over (
                    tvtype += 0x40;
                }
                else
                    return 1; //reserved word.

//******search the variable in variable name table (vntp) to see if this variable is already used..
            char temp=cix;
            cix=tvscix;    //search expects the string to be searched pointed by cix.
            tvscix=temp;  //variable string'in sonunu tvscix'e attık.. search
            char result = search(&vntp,0, 0); //bu variable name daha önce kullanılmış mı? vntp'yi search et..
            while ( result==0 )           //found in table
                if ( regx == tvscix ) //if the variables are the same length
                    break;            //must not be just a prefix of an another variable in vntp table..
                else
                    result = search(&vntp,0, regy);  //is there an another version??
            //search'ın içindeki bütün variable'lerin korunduğunu varsayıyoruz..


//*****variable name not found in the vntp table.. Go expand vntp table and write the new variable name into it..
            if (result == 1){
                cix=tvscix-cix;	 // variable length; current value of cix is in tvscix
                explow(&vntd, cix); //vntd tablosunda variable length kadar yer aç..
                pty=cix-1;   //why -1 ????
                ptx=tvscix-1;	//and tvscix points to the character just after the variable..
                do
                    *(*svesa+pty)=*(lbuff+ptx);
                ptx--;
                pty--;
                while (pty>0)
                    pty=cix-1;
                *(*svesa+pty)=*(*svesa+pty) | 0x80; //turn on the msb bit of the last character of the string

//*******Go expand vvt table by 8 bytes and fill the last 6 locations with zeros*********************
                explow(&stmtab, 8);  //stmtab tablosundan itibaren 8 byte aşağı it.
                svvvte++;    // Pre-compiler increments this value every time it adds a variable to the
                // Variable Value Table . If a syntax error is detected, this number
                //is multiplied by eight (the number of bytes in each entry on the
                //Variable Value Table) to get the number of bytes to remove...

//************ zero out the working area****************
//*************orijinal programda tvtype+2 adresinde başlayan bayağı büyük bir boşluk var..
//*************Orayı “karalama alanı gibi kullanıyor.. o detay bu programda skip edildi.
                for (yy=0 ; yy<8 ; yy++)
                    *(*svesa+yy) = 0;
            }

//******eğer variable numeric arry'sa cix'i bir adım geriye alıyor. Bunu büyük olasılıkla syntaxer "("ı görmek isteyeceği için yapıyor..
            if (tvtype==0x40)
                --tvscix;    //???????????????

//******update outbuff
            cix=tvscix;   //update
            if (stenum>0x7f)    //stenum is the table entry number.
                goto  errvsf; //if entry number is greater than 0x7f, this means that the table is full..
            setcode(stenum | 0x80) //put the token number corresponding to the variable into the outbuff..
            //turn the msb bit on..
            return(0);
        }
    }



int tnvar(){
    return 0;
}

int tsvar(){
    return 0;
}

