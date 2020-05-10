PRINT "input 'y' ,open k.lst"
PRINT "input 'n' ,continue"
10 a$ = INKEY$
11    IF a$ = "k" THEN SHELL "edit k.asm": GOTO 12

  IF a$ = "y" THEN
       SHELL "edit k.lst"
12     PRINT "input 'y' ,masm k.asm"
     PRINT "input 'n' ,continue"
20   a$ = INKEY$
    IF a$ = "k" THEN SHELL "edit k.asm": GOTO 12

       IF a$ = "y" THEN
'           shell "copy data+disp+line+weiqi+mouse+key+contr+main k.asm"
           SHELL "masm k.asm<kl"
PRINT "input 'y' ,open k.lst"
PRINT "input 'n' ,continue"

22         a$ = INKEY$
IF a$ = "k" THEN SHELL "edit k.asm": GOTO 12
               IF a$ = "y" THEN GOTO 11
               IF a$ = "n" THEN SYSTEM
               IF a$ = CHR$(13) THEN SYSTEM
           GOTO 22
       END IF
       IF a$ = "n" THEN SYSTEM
       IF a$ = CHR$(13) THEN SYSTEM
     GOTO 20
   END IF
   
IF a$ = "n" THEN SYSTEM
IF a$ = CHR$(13) THEN SYSTEM
GOTO 10

