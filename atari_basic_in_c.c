RAM Table Pointers

0000 = 0080           ORG       ZPG1
0080              LOMEM                    ; LOW MEMORY POINTER
0080              ARGSTK
0080 = 0002       OUTBUFF   DS     2       ; SYNTAX OUTPUT BUFFER
0082 = 0002       VNTP      DS     2       ; VARIABLE NAME POINTER
0084 = 0002       VNTD      DS     2       ; VARIABLE NAME TABLE DUMMY END    \\explow
0086 = 0002       VVTP      DS     2       ; VARIABLE VALUE TABLE POINTER           \\explow
0088              ENDVVT                   ; END VARIABLE VALUE TABLE
0088 = 0002       STMTAB    DS     2       ; STATEMENT TABLE [PROGRAM] ;         \\explow
008A = 0002       STMCUR    DS     2       ; CURRENT PGM PTR                               \\explow
008C = 0002       STARP     DS     2       ; STRING/ARRAY TABLE POINTER         \\explow
008E              ENDSTAR                  ; END STRING/ARRAY SPACE                       \\expand
008E = 0002       RUNSTK    DS     2       ; RUN TIME STACK
0090              TOPRSTK                  ; END RUN TIME STACK         \\explow   --runtime stack'ı expand etmek için..
0090 = 0002       MEMTOP    DS     2       ; TOP OF USED MEMORY
0092 = 0001       MEOLFLG   DS     1       ; MODIFIED EOL FLAG
0093 = 0001                 DS     1       ; ::SPARE::



char cix, cox; //current input and output buffer pointers..
char six, sox;
int  cpc,spc; //these show the line of the syntax table we are in..
char *scradr; //contains the address, minus 1, of the current 
              //statement's AMBL instructions in the syntax tables..
char code, code1, code2;
char stklvl;

===================================EDITOR====================================================================
main() { //editor loop
syntax:
	//--skipped--restore stack. Each time Atari BASIC prepares to get a new line from the user, 
	//it restarts its entire logical process.
	intlbuff(); //initializes line buffer into input buffer, ie, sets INBUFF := LBUFF
	prompt = '?';
	glgo(); //read a line. The line is put into the variable inbuff[].
	cix=0;  //index of inbuff
	maxcix=0;
	cox=0;  //index of outbuff
	dirflg=0; //if the line has a line no and if compiler found an error. 0 means has line number and no error.
                  //we will replace this by the variables direct_statement and syntax_error
	svontx=0;
	svontc=0;
	svvte=0;  //Pre-compiler increments svvte every time it adds a variable to the Variable Value Table . If a syntax 
                  //error is detected, this number is multiplied by eight (the number of bytes in each entry on the
                  //Variable Value Table) to get the number of bytes to remove
	svvntp = vntd; //vntd is the current top of the variable table.	


	skblank(); //increment cix to skip blanks in INBUFF
	getlnum(); //The floating point package is called to determine if a line number is  present, and, if so, to 
                   //convert the ATASCII line number to a floating point number. The floating point number is  
                   //converted to an integer, saved in TSLNUM for later use, and 
                   //stored in the tokenized line in the output buffer (OUTBUFF).
                   //getlnum()'un cix'i arttırıyor olması lazım?????
                   //eğer line mumber yoksa o zaman direct statement, TSLNUM'u 0x8000 yapıyor.
	setcode(NULL);  //setcode is the routine used to store contents of A register into OUTBUFF. When SETCODE stores a 
                   //byte into OUTBUFF, it also increments COX. The byte after the line number in OUTBUFF is reserved so 
                   //that the line length The byte after the line number in OUTBUFF is reserved so that the line length
                   //(actually the displacement to the next line) can be inserted later. Here, the routine 
                   //SETCODE is called to reserve the byte by incrementing (COX) to indicate the next byte.
	direct_statement=0;
	if (binint<0)  //binint galiba line number'ı tutuyor..
		direct_statement=1; //If the input line does not start with a line number, the line is 
                                    //considered to be a direct 
                          //statement. DIRFLG is set to $80 so that the editor can remember this fact. The line number 
                          //is set to 32768 ($8000). This is one larger than the largest line number a user is allowed to 
                          //enter. BASIC later makes use of this fact in processing the direct statement.
	skblank();  //if no line number, will it return directly??????
	stmstart=cix; //stmstart is used only if there is a syntax error, so that all the characters in the erroneous 
                      //line can be moved into the tokenized line buffer and from there into the Statement Table.
                      //There are advantages to saving an erroneous line in the Statement Table, because you 
                      //can LIST the error line later.
	if (inbuff[cix]=='\n') {    //boş satır.
		if (direct_statement == 1) //if no line number
			goto syntax;   //start all over..
		else
			goto sdel //if there is line number, delete it from the statement table.. The deletion is
                                  //done by pointing to the line in the Statement Table, getting its length, 
                                  //and calling CONTRACT.    SDEL returns to ?????
syn1:
	stmlbd=cox;
	setcode(); // A byte is reserved in OUTBUFF by the routine :SETCODE. Later, the value in STMLBD 
                   //will be used to access this byte, and the statement length (the displacement to the next 
                   //statement) will be stored here. (note that line length and statement length are different)
	skblank(); //???????????
	search(&sntab, 2);           <========================  finds the statement name
                           //;searches for the statement name in the statement table. 
                           //SEARCH saves the table entry number of this name into location STENUM. for use by the 
                           //pre-compiler. Also sets SCRADR, which is the address, minus 1 
                           //of the current statement's AMBL instructions in the syntax tables.	
	setcode(); //The entry number is also the Statement Name Token value,
                   //and it is stored into the tokenized output buffer (OUTBUFF) as such by setcode(). 
		   //If the first word in the statement was not found in the Statement Name Table, the 
		   //editor assumes that the statement is an implied LET, and the appropriate token is stored.
	skblank();
	if (!synent()){                         <==================syntaxer entry
		\\error processing.. okunmadı..
	}
	outbuff[stmstart]=cox; //set statement length byte..
        if (inbuff[cix-1]!='\n')  //end of line?
		goto syn1; //if not a carriage return (indicating end of the line), 
                           //then the statement processing is repeated.
	outbuff[2]=cox; //set the line length
	//The final tokenized form of the line exists in OUTBUFF at this point. The editor's task now is to insert this 
	//line into the statement table..
	if (getstmt()==0) { //The Program Editor first needs to create the correct size hole in the Statement Table.
		            //The editor calls the getstmt() to find the address where this line should go
		            //in the Statement Table. If a line with the same line number already exists, the routine returns 0,
		            //with the address in STMCUR. Otherwise, the routine puts the address where the new line should be 
                             //inserted in the Statement Table into STMCUR and returns 1.
		linelength=getll();  //line with the same line number exists, hence find its length..
	else
		linelength=0;
	if (linelength<cox) {     //cox is the length of the line to be inserted..
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
		goto execnl;    <==================executor
	else
		goto syntax;  <========= editor infinite loop

sdel: \\error processing	
}


getlnum() {
	cvafp();  \\sets not_a_number variable
	if (not_a_number){
		cix=0;  
		tslnum = 0x8000;
 	}
	else {
		cvfpi(); //convert fp returned by cvafp() into int. Puts the result into binint
		if (binint<0){  //eğer line number eksiyse not a number gibi davranıyor..
			cix=0;  
			tslnum = 0x8000;
		}
		else
			tslnum=binint;
	}
	setcode(&tslnum); //writes tslnum into the first two bytes of outbuff..
                          //aslında tslnum 16-bit olduğu için iki tane setcode() kullanılıyor..
}




====================================SYNENT = SYNTAXER=================================================================

//ANTV : 00, absolute non-terminal. 00 followed by the non-terminal's definition within the Syntax Table. The address is two bytes long, with the least significant byte first.
//ESRT: 01, followed by the address, minus 1, of a 6502 machine language routine.
//OR: 02
//RETURN: 03
//VEXP: 0E expression non-terminal. A call to <exp>
//CHNG 0F: change last token
//OPERATOR 10-7F
//RNTV: RELATIVE NON_TERMINAL: 80-BF (plus), C0-FF (minus)

//we have..
// 1. keywords (if, then, goto...) 
// 2. numeric constants (tncon)
// 3. string constants  (tscon)
// 4. numeric variables and numeric arrays (tnvar)
// 5. string variables (tsvar)
// 6. operators (+, -, AND, OR, *, ...) (srcont)
// 7. functions (sin, cos, exp, ....) (galiba gine srcont)

//syntaxer only checks if these things come in correct sequence and order... If so, it generates a tokenized line at outbuff..
void synent( ) {
        cpc=spc=*(srcadr+1); //SRCADR is the address, minus 1,  of the current statement's AMBL instructions in the syntax tables.
                             //it is set by the call search(&sntab, 2) in the editor..	
	stklvl = 0;
	six=cix;
	sox=cox; 

next:
	nxsc(&code);	     //get next syntax instruction pointed by cpc, cpc++.
	if (signed code<0) { //erntv  -- relative non-terminal value.. note that the type char is normally not signed.
		goto erntv;
	if (code==0)
		goto getaddr; //abs non-terminal
	if (code>1)
		goto tstsuc  //chng ya da operator (10-7f)
	if getaddr();	//esrt (code=1). success if it returns 1. 
		goto next;
	goto fail;            //getaddr() 0 dönerse fail'e gidiyor..

tstsuc: if (code<5)           //code=2,3,4. 2,3 is "return", 4 is "accept up to this point"
		goto pop;
	if(termtst())        // larger then 4.. 
		goto next;
	goto fail;
	
	
erntv:   //buradaki kod tam anlaşılamadı
	code1=...
	code2=
        goto push;


getaddr: //buraya code 0 veya 1 se geliyor.. 0'sa ANTV (absolute non-terminal), 1 se ESRT (external subroutine)
	nxsc(&code1);
	nxsc(&code2);
	if (code==0)  //ANTV
		goto push;  //push if ANTV
	int xxxx = code1<<8 + code2;  //sıradan emin değilim.. code2<<8 + code1 olabilir;
	goto xxxx;  //goto external subroutine...


push: 	//buraya sadece relative ve absolute non-terminallerde geliyor..
	if (stklvl+4==0)
		goto erltl; //syntax stack too big
	stklvl+=4;
	*(stklevel+&six)=cix;    //note: in the code, the variables six, sox and spc are just above the stack..     
	*(stklevel+&sox)=cox;    //hence their addresses can be used as stack addresses...
	*(stklevel+&spc)=cpc;
	cpc=code1<<8 + code2;	
	goto next;


pop:
	if (stklvl==0)
		return;  //main exit of syntaxer..
	cpc = *(stklvl+&spc);
	stklvl-=4;
	if (stklvl<0)
		goto fail;
	goto next;

fail: //terminal failed...
	nxsc(code)  //read next codeword


} //synent



void inccpc() {
	cpc++;
}	


void nxsc(char *ch) {
	inccpc();
	ch = *cpc;    //cpc points to the syntax_table[]
}

		
	
//the variable "code" is 4 or larger	
//terminaller burada process ediliyor.
int termtst() {
	if (code==0x0f) 
		goto echng; // Change last token
	if (code>0x0f)
		goto srcont; //Can only be  $10-$7F, which are Operator tokens.

        pla;  //code=0x0E = VEXP
        pla;  //we do double pull because we do not want to return to the calee address. 
              //note that these are machine code instructions and do not have any place in C code..

	code1 =  #:EXP-1&255    //exp address for the special EXP ANTV call ????
	code2 =  #:EXP/256  // code=0E  Top non-terminal vector. same as an ANTV call to <expression> at $A60D.
	goto push;
	
echng: 	inccpc(); //go to next token in syntax table
	temp1 = *cpc; //get the syntax code;
	outbuff[cox-1] = temp1; //replace the last token in outbuff.
	return(1)

		

================================SETCODE===========================================
setcode(char *a){
	outbuff[cox++]=*a;
	if (cox==0)
		goto reltl //line too long error	


================================SRCONT==============================================
srcont:	//search operation name table. this is reserved name search..
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
	


===================================TNVAR, TSVAR==========================================
//read a variable name. detect if it is used previously..
//These routines are called from ambl, ie, from the syntax tables..
//tnvar reads numeric variables and arrays, tsvar reads strings..
//string variables end vith a $. A particular element can be reached by (), ie, like ali$(5).
//numeric array names finish with (.
tnvar	tvtype=0x0;
	goto tvar;

tsvar	tvtype=0x80;
	goto tvar;

//***skip the blanks till finding the start of the variable.. record this start at the variable tvscix.
tvar: 	skpblank(); //increments cix to the start of variable name..
	tvscix=cix;

//***check if the variable is legal.. The first character must be alphabetic (ie, not numeric) and it must not be a reserved name..
	if (tstalph()) //check if the character pointed by cix is alphabetic?
		goto tvfail;
	srcont();  //search the operation name table to see if this is a reserved name. returns its result in variables svontc and svontl.
	if (svontc==0)  //no token found, the variable name is ok..
		goto tv1;
	if (*(inbuff+svontl)<0x30)   //next character after the reserved word is not alarm?-numeric?????????
		goto tvfail          //????????

//***scan through the variable till the end, ie, till finding a non alpha-numeric variable..
tv1	cix++;	
	if (tstalph()==0)  //tstalph() returns zero if the character at cix is alphabetic
		goto tv1;
	if (tstnum()==0)   //tstnum() returns zero if the character at cix is numeric
		goto tv1;

//***try to determine the type of variable by testing the last character read.. 
//***if the last caracter is $, it is string, if (, numeric array, else numeric variable..
//***also check if this ending is compliant with call type, ie, the variable tvtype..
	if (*(inbuff+cix)=='$')  //if the offending character is a '$'. string variable. 
		goto tvstr;
	if (tvtype==0x0)  //numeric variable search
		goto tvok  
tvfail	return(1);  //fail
tvstr	if (tvtype!=0x80)
		goto tvfail;   
	cix++;     //increment over $
	goto tvok2;
tvok	if (*(inbuff+cix)!='(')  //if the offending character is a '('	
		goto tvok2;	
        cix++;	//increment over (
	tvtype+=0x40;  //or-in array code to tvtype..


//******search the variable in variable name table (vntp) to see if this variable is already used..
tvok2	temp=cix;
	cix=tvscix;  //cix' e search() etmek istediğimiz variable name'in start'ını koyduk.. 
	tvscix=temp; //variable string'in sonunu tvscix'e attık.. search() variable name'in startını cix'te istiyor..
	result = search(&vntp,0); //bu variable name daha önce kullanılmış mı? vntp'yi search et..
tvrs	if (result==1)
		goto tvs0;  //not found..
	if (ix==tvscix) //are the variables same length? ie, the variable we are searching 
		goto tvsuc; //must not be just a prefix of an another variable in vntp table..
	srcnext(); //search'ın içindeki bütün variable'lerin korunduğunu varsayıyoruz..
	goto tvrs;

//*****variable name not found in the vntp table.. Go expand vntp table and write the new variable name into it..
tvs0	cix=tvscix-cix; // variable length;
	explow(&vntd, cix); //vntd tablosunda variable length kadar yer aç.. vntd=variable name table dummy end...	
	pty=cix-1;      //recall that at tvok2 we exchanged cix and tvscix, hence now cix points o the start of the variable 
	ptx=tvscix-1;	//and tvscix points to the character just after the variable.. 
tvs1	*(*svesa+pty)=*(lbuff+ptx);
	ptx--;
	pty--;
	if (pty>0)
		goto tvs1;
	pty=cix-1;
	*(*svesa+pty)=*(*svesa+pty) | 0x80; //turn on the msb bit of the last character of the string

//*******Go expand vvt table by 8 bytes and fill the last 6 locations with zeros*********************
	explow(&stmtab, 8);  //neden stmtab da endvvt değil?????
        svvvte++;            // Pre-compiler increments this value every time it adds a variable to the
                             // Variable Value Table . If a syntax error is detected, this number
                             //is multiplied by eight (the number of bytes in each entry on the
                             //Variable Value Table) to get the number of bytes to remove...
//******önce tvtype+2 adresinden başlayarak 8 tane 0 oluşturuyor, sonra bu 8 0'ı tek tek vvt tablosunda svesa ile point edilen yere kopya ediyor..
//******not: tvtype+2 adresinde başlayan bayağı büyük bir boşluk var.. Orayı “karalama alanı gibi kullanıyor..
	yy=2;
tvs1a:	*(tvtype+yy)=0;
	yy++;
	if (yy<8)
		goto tvs1a;
	yy--;
tvs2:	*(*svesa+yy)=*(tvtype+yy);
	yy--;
	if (0<yy)
		goto tvs2;

//******eğer variable numeric arry'sa cix'i bir adım geriye alıyor. Bunu büyük olasılıkla syntaxer "("ı görmek isteyeceği için yapıyor..
tvsuc:	if (tvtype==0x40)
		--tvscix;

//******update outbuff
tvnp:	cix=tvscix;   //update 
	if (stenum>0x7f)    //stenum is the table entry number.
		goto  tvfull; //if entry number is greater than 0x7f, this means that the table is full..
	setcode(stenum | 0x80) //put the token number corresponding to the variable into the outbuff..
                               //turn the msb bit on..
	return(0);
       
tvfull:	goto errvsf;	
	
	
====================================TNCON==================================================
//is called by the ambl ESRT instruction. Its purpose is to examine the current source symbol for a numeric constant,
//using the floating point package . If the symbol is not a numeric constant, the routine returns fail.
//If the symbol is a numeric constant, the floating point package has converted it to a floating point number. The
//resulting six-byte constant is placed in the output buffer preceded by the $OE numeric constant token. The routine then
//exits with pass indicated.
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


===========================TSCON============================================
//reads a string constant..
tscon(){
	skblank();
	if *(*inbuff+cix) != '"'; //is the character read a double quote
		return(1); //fail, carry=1
	setcode(0x0f);  //set sconcode
	tscox=cox;
	setcode(); //open a space in outbuff for string length..
tsc2:	cix++;
	ch = *(*inbuff+cix);
	if (ch == '\n')
		goto tsc4;
	if (ch == '"')
		goto tsc3;
	setcode(ch);
	goto tsc2;
tsc3	cix++;  //increment over double quote,
tsc4	*(outbuff+tscox)=cox-tscox; //set string length
	return(0); //success, carry=0
}
		
	
	

	


=====================================SEARCH==============================================
//this routine tries to find a token in a table. a token is a character string..
//The table to be searched is assumed to have entries which consist of a fixed length part (whose 
//length varies from table to table, it is 0 to 255 bytes long.) 
// followed by a variable length ATASCII part. The last character of the ATASCII part is assumed to 
// have the most significant bit ($80) on. Thelast table 
// entry is assumed to have the first  ATASCII character as $00.
//------during entry------
//
//------during exit-------
//returns 0 if the string is foun, 1 if the string is not found. 
//srcadr is pointer to the matched table entry
//stenum is the matched entry number.
//ix-1 points to the token's end at inbuff..
int search(int srcskip, char *srcadr) {  //srcadr is the address of the table, srcskip is the skip factor..
	char ix, ch1, ch2;

	stenum=-1;

src1	iy=0;
	stenum++;
	ix=cix;
	ch1=*(iy+srcskp); //get the first character of the stenum'th entry from the table
	if (ch1==0)           //end of table
		goto scrnf;
	result=0;
src2:	ch2 = *(lbuff+ix)&(0x7f);  //get the first character of the token from the lbuff.. turn off 8th bit?????? ..
	if (ch2 =='.')  //if input character is wild card (wild card'ı anlamadım?????)j
		goto src5;
src2a:	ch3=ch1^ch2;	//exor. if ch1=ch2 the result is either 0 or (for end of entry) 128.
	res1 = ch3 & 0x80   //eğer sonuç 0 değilse syntax table ile input birbirini tutmadı..
	if (ch3 & 0x7f==0) 
		goto src3;  //syntax table'deki token bitmedi..
	result = 1;
src3 	ix++;
	iy++;
	if (res1==0)   //go till you discover the end of the token in the syntax table..
		goto src2;
	if (result==0) 
		goto srcfnd;

srcnxt	srcaddr+=iy;   //srcaddr ve iy global olmalı...
	goto src1;

srcfnd: return(0);   //found;

srcnf:	return(1);   //not found;

src5: //wildcardlar anlaşılamadı.
}


================================EXPAND=================================================
expand(ecsize, expadr) {  //expaddr points to a table pointer..	
	if (*memtop+ecsize>himem)	
		goto memfull;

	mvlng = *memtop-*expadr;   //memtop and expadr are zero page pointers to basic tables..

	mvfa[L] = *expadr[L]       //mvfa = move from address
	mvfa[H] = *expadr[H] + mvlng[H] //[H] ve [L] high byte ve low byte manasına geliyorlar..

	svsea = *expadr         //the address from where expansion begins.. this is the address of the empty space which will subsequently 
                               //be filled.

	mvta = *expadr+expsize;  //low and high bytes
	mvta[H] = mvta[H]+ecsize[H]  //only the high byte

//**************update zero page pointers, set aphm*******************************
exp3:	*expadr  +=  ecsize;
	expadr+=2;
	if (expadr<memtop+2)
		goto exp3;
	aphm = *memtop; // memtop pointer, aphm pointer değil...

//*****************shift data in 256 byte blocks****************************
	mvlng[H]++;
	if (mvlng[L] != 0) 
		goto exp6;
	else
		goto exp7;
exp4:	mvleng[L]--;  //will roll back to 255
	mvfa[H]--;
	mvta[H]--;
exp5:	*mvta+mvlng[L]=*mvfa+mvlng[L];
exp6:	mvlng[L]--;
	if (mvlng[L]!=0)
		goto exp5;
	*mvta+mvlng[L]=*mvfa+mvlng[L];
exp7:	mvlen[H]--;
	if (mvlen[H]!=0)
		goto exp4;
	return();
}

======================================CONTRACT===================================
\\yazılmadı


======================= EXECNL=Execute next line=================================

execnl(){
	setln1()  //SET UP LIN & NXT STMT
execns:
	llngth = nxstd;
	nxstd = 
	
	

	









	
