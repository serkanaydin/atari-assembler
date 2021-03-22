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
        cox=0;
        direct_statement=0;
        skblank();
        getlnum();   //sets binint
        setcode(NULL);
        if (binint<0)
            direct_statement = 1;
        skblank();
        if (inbuff[cix]=='\n') {           //boş satır.
            if (direct_statement == 1) //if no line number
                continue;
            else
                goto sdel;
            do{
                stmlbd=cox;
                setcode(NULL);
                skblank();
                sntabseatch()  //sets stenum
                setcode();
                skblank();
                if (!synent()){                         <==================syntaxer entry
                    \\error processing.. okunmadı..
                }
                outbuff[stmstart]=cox; //set statement length byte. if not a carriage return,
                while (inbuff[cix-1]!='\n')  //end of line?
                    outbuff[2]=cox; //set the line length
            }
            //devamı var.
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



        srcont() {	//search operation name table. this is reserved name search..
            skpblank();
            if (cix==svontx)      //svontx sadece burada kullanılıyor. svontx'in ne olduğunu anlayamadım??????
                goto sont1;  //eğer bu rutine bir önce girildiğinden beri cix ilerlememişse sont1'e atlıyor.
            svontx=cix;
            if (search(opntab,0))     //opntab = operator name table
                goto sonf   //not found.. search() returns 1 if not found
            svontl = ix //ix points to the next character after the token in inbuff. ix is set by search()
            svontc = stenum + 0x10; //svontc is the token number..
            sont1	if (*cpc==svontc)
                goto sont2;
            if (*cpc==#CNFNP) //#CNFNP=0x44. NFNP means numeric function numeric parameter, like sin(), cos() etc..
            goto sontf   //token and syntax table element does not match, but does the  syntax table requires a nfnp
            if (*cpc<=svontc) //tokens for nfnp's are larger or equal then 0x44, see opntab for this..
                goto sont2;
            sontf	return(1)  //failure -- token bulduk ama syntax table ile uyuşmadı
            sont2	setcode(svontc); //update outbuff
            cix=svontl; //update inbuff
            return(0); //success -- token bulduk
            sonf	svontc=0;
            return(1);   //failure -- token bulamadık..
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


//reads a string constant..
//copy it to outbuff..
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

			
			

	
		
		
		
		