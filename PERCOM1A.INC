
; Includedatei fuer PERCOM.ACT
;---

PROC hsiov ()
 [$6C hsioadr]
RETURN

PROC siov=$E459 ()

BYTE FUNC Sio (BYTE num,comnd,stats,tim,CARD buf,byt,sec)

BYTE ddevic=$300,
     dunit=$301,
     dcomnd=$302,
     dstats=$303,
     dtimlo=$306

CARD dbuf=$304,
     dbyt=$308,
     daux=$30A

ddevic=$31
dunit=num
dcomnd=comnd
dstats=stats
dtimlo=tim
dbuf=buf
dbyt=byt
daux=sec

 IF hsio_ok=1 THEN
  hsiov ()
 ELSE
  siov () ; ansprung der sioroutine
 FI

RETURN (dstats)

;---

PROC C_On ()

BYTE crsin=752

crsin=0

RETURN

PROC C_Off ()

BYTE crsin=752

crsin=1

RETURN

BYTE FUNC Inkey ()

BYTE atascii

 Close (2)
 Open (2,"K:",4,0)
 atascii=GetD(2)
 Close(2)

RETURN (atascii)

PROC Pause (CARD times)

BYTE wsync=$14,q
CARD u

FOR u=1 TO times
DO
  FOR q=1 TO 200
  DO
   wsync=q
  OD
OD

RETURN

PROC Beep (BYTE times)

BYTE u

FOR u= 1 TO times
DO
  PutD (0,253)
  Pause (10)
OD

RETURN

PROC Getin (BYTE ARRAY text,BYTE len)

  BYTE ascii,pos,u,inv,ch=764

  C_On ()
  ch=$FF

  pos=text(0)+1
  inv=0

  IF text(0)#0 THEN
   Print (text)
  FI

  DO
   ascii=Inkey ()

   IF ascii=129 THEN
    inv==!$80
   FI
   IF ascii=$1E AND pos>1 THEN
    pos==-1
    PutD (0,$1E)
   FI
   IF ascii=$7E AND pos>1 THEN
    pos==-1
    PutD (0,$7E)
   FI
   IF ascii=$1F AND pos#len+1 THEN
    pos==+1
    PutD (0,$1F)
   FI
   IF ascii>26 AND ascii<32 THEN
    ascii=128
   FI
   IF pos#len+1 AND ascii<$7E THEN
    ascii==+inv
    PutD (0,ascii)
    text(pos)=ascii
    pos==+1
   FI
   text(0)=pos-1
  UNTIL ascii=$9B
  OD

  C_Off ()
  Put (31)
RETURN

PROC Write (BYTE x,y,BYTE ARRAY string)

  BYTE u,chr
  CARD savmsc=$58
  BYTE POINTER adr

  adr=savmsc+y*40+x

  FOR u=1 TO string(0)
  DO
   chr=string(u)
   IF chr>=0 AND chr<32 THEN
    chr==+64
   ELSEIF chr>31 AND chr<95 THEN
    chr==-32
   ELSEIF chr>127 AND chr<160 THEN
    chr==+64
   ELSEiF chr>159 AND chr<224 THEN
    chr==-32
   FI
   adr^=chr
   adr==+1
  OD
RETURN

;-----------------------------------

PROC ErrMess (BYTE err)

 Write (10,20,"Status - ")
 StrB(err,txt)
 Write (20,20,"   ")
 Write (20,20,txt)
 IF err>$7F THEN
  Write (25,20,"†≈““œ“†")
 ELSE
  Write (25,20,"OK     ")
 FI
RETURN
