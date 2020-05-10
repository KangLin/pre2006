DECLARE SUB rword (a!, b!, flag!)
DECLARE SUB word (x!, y!, col!, gcol!, a$)
SCREEN 13
CALL word(100, 100, 12, 15, "ÖÐ")
rworddat:
DATA &h50,&h53,&h51,&h52,&h56,&hbe,&h00,&h00,&h2e,&h8b,&h04,&h2e,&h8b,&h5c,&h02
DATA &h8b,&hc8,&hf7,&hd1,&h85,&hcb,&h74,&h09,&h2e,&hc7,&h44,&h04,&h00,&h00,&heb
DATA &h07,&h09,&h2e,&hc7,&h44,&h04,&h01,&h00,&Hd1,&He3,&H2e,&H89,&H5c,&H02,&h5e
DATA &h5a,&h59,&h5b,&h58,&hcb

SUB rword (a, b, flag)
DIM a%(60)
    a%(52) = a: a%(53) = b: a%(54) = flag
DEF SEG = VARSEG(a%(0))
RESTORE rworddat
FOR i% = 0 TO 49
    READ D%
    IF i% = 6 THEN    '¸øSI¸³Öµ
       D% = VARPTR(a%(52)) MOD 256
    ELSEIF i% = 7 THEN
       D% = VARPTR(a%(52)) / 256
    END IF
    POKE VARPTR(a%(0)) + i%, D%
NEXT i%

CALL ABSOLUTE(VARPTR(a%(0)))
DEF SEG
b = a%(53): flag = a%(54)
END SUB

SUB word (x, y, col, gcol, a$)
OPEN "c:\ucdos\hzk16" FOR RANDOM AS #1
    point1 = ASC(RIGHT$(a$, 2))
    point2 = ASC(RIGHT$(a$, 1))
    PRINT point1; point2
    point3 = (point1 - 1) * 94 + (point2 - 1) * 72 + 1
    apoint = point3 * 32
FOR j = 0 TO 15
    b = 1
    GET #1, apoint + j, a
    FOR i = 0 TO 15
        CALL rword(a, b, flag)
        IF flag = 1 THEN
           PSET (x + i, y + j), col
        ELSE
           PSET (x + i, y + j), gcol
        END IF
    NEXT i
NEXT j
END SUB

