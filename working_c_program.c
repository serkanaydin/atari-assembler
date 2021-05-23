char inbuf[255], outbuf[255];
int cix, cox;
int stenum;
int direct_statement;
int stack[200];

getlnum() {

}

setcode(char *a) {
    outbuff[cox++]=*a;
    if (cox==0)
        goto reltl //line too long error
}

skblank(){
    int i;

    while (inbuf[cix]==' ')
        cix++;
}



main() {
    while(){
        scanf("%s", inbuf);
        cix=0;
        maxcix=0; //This byte ($9F) is maintained in case the line contains
        //a syntax error. It indicates the displacement into LBUFF of the
        //error. The character at this location will then be displayed in inverse video.
        cox=0;
        direct_statement=0;
        svontx=0;
        svontc=0;
        svvvte=0;
        svvntp = &vntd  //vntd = current top of the variable name table pointer.
        //is saved as SVVNTP (SAD) so that if there is a
        //syntax error in this line, any variables that were added can be removed.
        skblank();
        getlnum();   //sets binint
        setcode(NULL);
        direct_statement=0;
        if (binint<0)   //binint görünüşe göre line number tutuyor ve getlnum tarafından set ediliyor.
            direct_statement = 1;
        skblank();
        stmstart=cix; //stmstart is used only if there is a syntax error,
        //so that all the characters in the erroneous
        //line can be moved into the tokenized line buffer and from there into the Statement Table.
        //There are advantages to saving an erroneous line in the Statement Table, because you
        //can LIST the error line later.
        if (inbuff[cix]=='\n') {           //boş satır.
            if (direct_statement == 1) //if no line number
                continue;
            else
                goto sdel;  //if there is line number, delete it from the statement table.
            do
                stmlbd=cox;
            setcode(NULL); //A byte is reserved in OUTBUFF by the routine :SETCODE. Later, the value in STMLBD
            //will be used to access this byte, and the statement
            //length (the displacement to the next statement) will be stored here.
            skblank();
            search(&sntab, 2, 0)  //sets stenum. also sets regx, which point to the next char after the token.
            cix = regx;
            setcode(stenum);
            skblank();
            if (!synent()){                         <==================syntaxer entry
                \\error processing.. okunmadı..
            }
            outbuff[stmstart]=cox; //set statement length byte. if not a carriage return,
            while (inbuff[cix-1]!='\n')  //if not a carriage return (indicating end of the line),
                //then the statement processing is repeated.
                outbuff[2]=cox; //set the line length
        }
//********The final tokenized form of the line exists in OUTBUFF at this point. The editor's task now is to insert this
//********line into the statement table..
        if (getstmt()==0) { //The Program Editor first needs to create the correct size hole in the Statement Table.
            //The editor calls the getstmt() to find the address where this line should go
            //in the Statement Table. If a line with the same line number already exists, the routine returns 0,
            //with the address in STMCUR. Otherwise, the routine puts the address where the new line should be
            //inserted in the Statement Table into STMCUR and returns 1.
            linelength=getll();  //line with the same line number exists, hence find its length..
            else
            linelength=0;
            if (linelength<cox) {     //cox is now the length of the line to be inserted..
                explow(stmcur, linelength-cox); //expands memory. First parameter is from where to expand, second parameter is
                //how many bytes to expand.
                stmcur = svesa; //svesa is "save expand start address". It is set by explow() and becomes the current address.
                //????????????bne anlaşılamadı....
            } else if (linelength > cox) {
                *stmcur = cox-linelength;  //stmcur points to the start address of contraction
                contlow(stmcur, cox-linelength);
            }
            //a hole of desired size is opened.. copy the outbuff..
            for (i=cox; i>=0; i--)
                *(stmcur+i)=outbuff[i];
            if (syntax_error)
            {
                //error correction
            }
            if (direct_statement)
                goto execnl;    <==================executor    //goto ları yoket.
            else
            goto syntax;  <========= editor infinite loop

            sdel: \\error processing
        }

    }


    int nxsc() {
        cpc++;
        return syntaxtable[cpc];    //cpc points to the syntax_table[]
    }



    synent(){
        int cpc, spc, six, sox, stklvl;

        cpc=assembly[srcadr];
        spc=assembly[srcadr];

        stklvl = 0;
        six=cix;
        sox=cox;

        while(){
            code=nxsc();

            if (code == 5)
                if (!tnvar())  //returns 1 if succesful.
                    goto fail;
                else if (code == 7 )
                    if (!tsvar())
                        goto fail;
                    else if (code == 4)
                        if (!tncon())
                            goto fail;
                        else if (code ==6)
                            if (!tscon())
                                goto fail;
                            else if (code == 10)
                                if (!eif())
                                    goto fail;
                                else if (code==8)
                                    if (!edata())
                                        goto fail;
                                    else if (code==9)
                                        if (!elem())
                                            goto fail;
                                        else if (code==0){              //call
                                            code=nxsc();
                                            if (stklvl+4 == 0)
                                                goto erltl;
                                            stklvl+=4;
                                            stack[stklvl+1]=cix;
                                            stack[stklvl+2]=cox;
                                            stack[stklvl+3]=cpc;
                                            cpc = code;
                                        }
                                        else if (code == ){            //or veya return
                                            if (stklvl == 0)
                                                return;     <======== main exit of syntaxer
                                            cpc = stack[stklvl+3];
                                            stklvl-=4;
                                            if (stklvl<0)
                                                goto fail;
                                        }
                                        else if (code==)
                                            echng();
                                        else if ((code>=16)&&(code<=127))
                                            if(!srcont())
                                                goto fail;
                                            else
                                                printf("unrecognized code in syntax table\n");
        }
    }


    int echng(){
        inccpc(); //go to next token in syntax table
        outbuff[cox-1] = *cpc; ///get the syntax code; replace the last token in outbuff with it.
        return(1)
    }



//Handles Operator Token Instructions ($10-$7F)
    srcont() {
        skpblank();
        if (cix!=svontx) {   //bir sürü farklı cpc için aynı cix'i deneyebilir.
            svontx=cix;
            if (search(opntab,0)) {
                svontc=0;
                return(1);
            }
            svontl = regx;
            svontc = stenum + 0x10;
        }
        if ( (*cpc == svontc) || (cpc == #CNFNP )&&( #CNFNP <= svontc) ){
            setcode(svontc);
            cix=svontl;
            return(0);
        }
        else {
            svontc=0;
            return(1);
        }
    }



    tvar (int tvtype){   // tvtype=0x0 means numeric, tvtype=0x80 means string.
        int tvscix;

        skpblank();
        tvscix=cix;
        if (tstalph()){     //is the first character alphabetic?
            srcont();   //is it a reserved word?
            if ( svontc == 0 ) || (svontc==1)&&(inbuff[svontl]>=0x30 ){  //not reserved word, or it is
                do                                                  //a non-reserved word whose prefix
                    cix++		                            //is a reserved word..
                while ( !tsalph() | !isnum() );

                if (tvtype == 0x80 )
                    if ( inbuff[cix] == '$')
                        cix++;      //skip over $
                    else
                        tvfail();
                else if ( tvtype == 0x0 )
                    if ( inbuff[ cix ] == '(' ) {
                        cix++;      //skip over (
                        tvtype += 0x40;
                    }
                    else
                        tvfail();  //reserved word.

//******search the variable in variable name table (vntp) to see if this variable is already used..
                temp=cix;
                cix=tvscix;    //search expects the string to be searched pointed by cix.
                tvscix=temp;  //variable string'in sonunu tvscix'e attık.. search
                result = search(&vntp,0, 0); //bu variable name daha önce kullanılmış mı? vntp'yi search et..
                while ( result==0 )           //found in table
                    if ( regx == tvscix ) //if the variables are the same length
                        break;            //must not be just a prefix of an another variable in vntp table..
                    else
                        result = search(&vntp,0, regy);  //is there an another version??
                //search'ın içindeki bütün variable'lerin korunduğunu varsayıyoruz..


//*****variable name not found in the vntp table.. Go expand vntp table and write the new variable name into it..
                if (result == 1){
                    cix=tvscix-cix;	 // variable length; current value of cix is in tvscix                              //SBC: tvscix-cix-C
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




        tncon(){
            skblank();
            tvscix=cix;
            if (!cvafp())   //carry 0 sa sayı buldu, tncl'ye gidiyor. cvafp() string'i float'a dönüştürüyor..
                goto tnc1; //cvafp() ürettiği sayıyı FR0'dan başlayan adrese koyuyor...
            cix=tvscix; //sayı bulamadı. hata dönüyor..
            return(1); //hata carry set edilerek bildiriliyor

            tnc1:	setcode(0x03E)	//sayı bulundu. cvafp()'nin ürettiği sayıyı FR0'dan outbuff'a çekiyor.
            xx=0;
            tnc2:	*(*outbuff+cox)=*(FR0+xx)
            cox++;
            xx++;
            if (xx<6)
                goto tnc2;
            return(0);
        }


//reads a string constant and copies it to outbuff..
        tscon(){
            skblank;
            if inbuff[cix] != '"'; //is the character read a double quote
            return(1); //fail, carry=1
            setcode(0x0f);  //set sconcode
            tscox=cox;
            setcode(); //open a space in outbuff for string length..
            do
                cix++;
            ch = inbuff[cix];
            setcode(ch);
            while (!((ch=='\n')||(ch == '"')))
                if (ch == '"')
                    cix++;  //increment over double quote,
            outbuff[tscox]=cox-tscox; //set string length
            return(0); //success, carry=0
        }


        int srcadr, stenum, regx, regy;

        int search(int srcskip, char *srcadr, int xx) {
            char regx, regy;

            if (xx==0)
                stenum = -1;     //no. of matched entry
            srcadr += xx;

            while (*(srcadr+srcskip) != 0){    //if not end of table
                stenum++;
                regx = cix;      //buffers the buffer position
                regy = srcskip;  //buffers the table position
                error=0;
                do
                    if ( *(srcaddr+regy) & 0x7f != lbuff[regx] & 0x7f )
                        error=1;
                regx++;
                regy++;
                while ( *(srcaddr +regy) & 0x80 != 0 )
                    if (error == 0)
                        return(0)  //found //cix=regx
                srcadr += regy;
            }
            return(1);
        }


//The purpose of this routine is to find the address of the statement whose line number is contained in TSLNUM.
//If the line number is found, the STMCUR  contains the address of the statement
//and returns 0 (clear). If the line number does not exist, STMCUR contains
//the address where a statement with that line number should be, and returns 1 (set).
        getstmt() {
            savcur = stmcur;   //??????? savcur u nerede kullanıyor ??
            stmcur = &stmtab;  //start from the top of the table.

            while ( *stmcur < tslnum ) {
                getnxtl( getll() )
            }
            if ( *stmcur == tslnum )
                return(0);
            else
                return(1)  //boşa kaçabilir mi? galiba kaçamaz çünkü en sonda direct line var. ???????
        }

//This routine gets the next line in the statement table and makes it the current line.
//Entry parameters: STMCUR contains the address of the current
//Exit parameters: STMCUR contains the address of the next line.
        gnxtl( int length ) {
            stmcur += length;
        }


//returns line length of the line pointed by stmcur.




