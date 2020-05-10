PRINT "input 'y' ,run debug k.exe"
PRINT "input 'n' ,continue"
10 a$ = INKEY$
IF a$ = "y" THEN SHELL "debug k.exe": SYSTEM
IF a$ = "n" THEN SYSTEM
IF a$ = CHR$(13) THEN SYSTEM
GOTO 10

