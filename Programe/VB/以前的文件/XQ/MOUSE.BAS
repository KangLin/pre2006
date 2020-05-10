DECLARE SUB mouse (ax!, bx!, cx!, dx!)
10 CALL mouse(3, a, x, y)
PRINT a
IF a = 1 THEN END
PRINT x, y
GOTO 10
mouseda:
DATA &H50, &H53, &H51, &H52, &H56, &HBE, &H0, &H0, &H2E, &H8B, &H4, &HCD, &H33, &H2E, &H89, &H4
DATA &H83,&Hc6,&H02,&H2e,&H89,&H1c,&H83,&Hc6,&H02,&H2e,&H89,&H0c,&H83,&Hc6,&H02,&H2e
DATA &H89,&H14,&H5e,&H5a,&H59,&H5B,&H58,&HCB

SUB mouse (ax, bx, cx, dx)
DIM a%(50)
a%(43) = ax: a%(44) = bx: a%(45) = cx: a%(46) = dx
DEF SEG = VARSEG(a%(0))
RESTORE mouseda
FOR I% = 0 TO 39
    READ D%
    IF I% = 6 THEN
       D% = VARPTR(a%(43)) MOD 256
    ELSEIF I% = 7 THEN
       D% = VARPTR(a%(43)) / 256
    END IF
    POKE VARPTR(a%(0)) + I%, D%
NEXT I%

CALL ABSOLUTE(VARPTR(a%(0)))
DEF SEG
ax = a%(43): bx = a%(44): cx = a%(45): dx = a%(46)
IF a%(43) = 0 THEN SHELL "C:\MASM\BIN\MOUSE" '√ª”– Û±Í"

END SUB

