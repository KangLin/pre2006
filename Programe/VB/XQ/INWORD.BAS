DECLARE SUB readword (x!, y!, col1!, dis!)
DECLARE SUB wordp (x!, y!, col!, col1!, dis!)
DECLARE SUB mkhz (x!, y!, definex!, definey!, col!, col1!, dis!)
DECLARE SUB current (x!, y!, definex!, definey!, col1!, col!, dis!)
DECLARE SUB paining (x!, y!, col!, col1!, col3, dis)
DECLARE SUB iinword (a!, b!, c!)
DECLARE SUB inword ()
DECLARE SUB rword (a!, b!, flag!)
DECLARE SUB word (x!, y!, col!, gcol!)
DIM SHARED a(16, 16)
CLS
'GOSUB eeoo
'END
input200:
x = 160: y = 80: dis = 20: col = 2: col1 = 12
CALL wordp(x, y, col1, col, dis)
'GOSUB puword
'END
LOCATE 24, 25
PRINT "                                   "
LOCATE 24, 25
COLOR 15
INPUT "您要造的字:", wword$
IF LEN(wword$) <> 2 THEN LOCATE 25, 25: COLOR 14: PRINT "请输入一个汉字": GOTO input200
LOCATE 25, 25: COLOR 14: PRINT "              "
CALL mkhz(x + dis * .5, y + dis * .5, x + dis * .5, y + dis * .5, col, col1, dis)
CALL readword(170, 90, 12, dis)
GOSUB puword
returnn:
a$ = INKEY$
SELECT CASE a$
       CASE "r"
       GOTO input200
       CASE CHR$(27)
       SYSTEM
       CASE "R"
       GOTO input200
       CASE ELSE
       GOTO returnn
END SELECT
errr1:
GOTO input200
RESTORE qi
'FOR i = 0 TO 15
'    FOR j = 0 TO 15
'       READ a(i, j)
'    NEXT j
'NEXT i
puword:
OPEN "kkkkkkk.bas" FOR APPEND AS #1
        PRINT #1, wword$
        CALL inword
CLOSE
RETURN
eeoo:
SCREEN 13
OPEN "kkkkkk.bas" FOR INPUT AS #1
100
INPUT #1, a$
'IF a$ <> cc$ THEN 100
   CALL word(100, 100, 12, 15)
CLOSE
RETURN
END

inworddat:
DATA &h50,&h53,&h51,&h56,&hBE,&h00,&h00,&h2E,&h8B,&h04,&h2E,&h8B,&h5C,&h02,&h2E
DATA &h8B,&h4C,&h04,&h3D,&h01,&h00,&h74,&h09,&hF7,&hD1,&h23,&hD9,&hF7,&hD1,&hEB
DATA &h03,&h90,&h0B,&hD9,&hD1,&HE1,&h2E,&H89,&h5C,&H02,&h2E,&h89,&H4C,&h04,&h5E
DATA &h59,&h5B,&h58,&hCB

dsk2:
'DATA 康,
DATA 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0
DATA 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0
DATA 0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0
DATA 0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0
DATA 0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,0
DATA 0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0
DATA 0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0
DATA 0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0
DATA 0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0
DATA 0,0,1,0,0,0,0,1,0,1,0,1,0,0,0,0
DATA 0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0
DATA 1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0
DATA 1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0
DATA 1,0,0,1,0,0,1,1,0,1,0,0,0,0,1,0
'DATA1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1
dsk1:
'DATA "林",
DATA 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0
DATA 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0
DATA 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0
DATA 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0
DATA 0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0
DATA 0,0,0,1,1,1,0,0,1,0,1,0,1,0,0,0
DATA 0,0,1,0,1,1,0,0,1,0,1,0,1,0,0,0
DATA 0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0
DATA 0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0
DATA 0,0,1,0,1,0,1,1,0,0,1,0,0,1,0,0
DATA 0,1,0,0,1,0,1,1,0,0,1,0,0,1,0,0
DATA 0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0
DATA 1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0
DATA 1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0
DATA 0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0
'DATA 0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1

rworddat:
DATA &h50,&h53,&h51,&h52,&h56,&hbe,&h00,&h00,&h2e,&h8b,&h04,&h2e,&h8b,&h5c,&h02
DATA &h8b,&hc8,&hf7,&hd1,&h85,&hcb,&h74,&h09,&h2e,&hc7,&h44,&h04,&h00,&h00,&heb
DATA &h07,&h90,&h2e,&hc7,&h44,&h04,&h01,&h00,&Hd1,&He3,&H2e,&H89,&H5c,&H02,&h5e
DATA &h5a,&h59,&h5b,&h58,&hcb

xian:
DATA 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0
DATA 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
DATA 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0
DATA 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1
DATA 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1
DATA 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0
DATA 0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,0
DATA 0,1,1,1,0,0,1,1,1,0,0,0,1,0,0,0
DATA 0,0,0,0,0,1,0,1,1,0,0,1,0,0,0,0
DATA 0,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0
DATA 0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0
DATA 0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0
DATA 0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0
DATA 0,1,1,0,0,1,1,0,1,0,0,0,0,1,0,0
'DATA 1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1
qi:
'DATA 0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0
DATA 0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0
DATA 0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0
DATA 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0
DATA 0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0
DATA 0,0,0,1,1,1,0,0,1,1,1,1,1,0,0,0
DATA 0,0,1,0,1,1,0,0,1,0,0,0,1,0,0,0
DATA 0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0
DATA 0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0
DATA 0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0
DATA 0,1,0,0,1,0,1,0,1,0,0,0,1,0,0,0
DATA 0,1,0,0,1,0,0,1,1,0,0,0,1,0,0,0
DATA 1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1
DATA 1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0
DATA 0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0
DATA 0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1

SUB current (x, y, definex, definey, col1, col, dis)
col = 15
col1 = POINT(definex + dis * .3, definey)
    LINE (definex - dis * .2, definey - dis * .2)-(definex + dis * .2, definey - dis * .2), col1
    LINE -(definex + dis * .2, definey + dis * .2), col1
    LINE -(definex - dis * .2, definey + dis * .2), col1
    LINE -(definex - dis * .2, definey - dis * .2), col1
    PAINT (definex, definey), col1
    LINE (x - dis * .2, y - dis * .2)-(x + dis * .2, y - dis * .2), col
    LINE -(x + dis * .2, y + dis * .2), col
    LINE -(x - dis * .2, y + dis * .2), col
    LINE -(x - dis * .2, y - dis * .2), col
    PAINT (x, y), col
END SUB

SUB iinword (a, b, c)
'见SUB rword
'code            segment                    ;造汉字程序
'                org     100h
'                assume  cs:code,ds:code,es:code,ss:code
'start:
'                push    ax
'                push    bx
'                push    cx
'                push    si
'                mov     si,0
'
'                mov     ax,word ptr cs:[si]
'                mov     bx,word ptr cs:[si+2]
'                mov     cx,word ptr cs:[si+4]
'                cmp     ax,1
'                je      Exit1                
'                not cx
'                and bx,cx
'                not cx
'                jmp     exit
'exit1:      
'                or bx,cx
'Exit:
'                sal     cx,1
'                mov     word ptr cs:[si+2],bx
'                mov     word ptr cs:[si+4],cx
'                pop     si
'                pop     cx
'                pop     bx
'                pop     ax
'                retf
'code            ends
'                end     start

DIM a%(60)
    a%(53) = a: a%(54) = b: a%(55) = c
DEF SEG = VARSEG(a%(0))
RESTORE inworddat
FOR i% = 0 TO 48
    READ D%
    IF i% = 5 THEN    '给SI赋值
       D% = VARPTR(a%(53)) MOD 256
    ELSEIF i% = 6 THEN
       D% = VARPTR(a%(53)) / 256
    END IF
    POKE VARPTR(a%(0)) + i%, D%
NEXT i%

CALL ABSOLUTE(VARPTR(a%(0)))
DEF SEG
b = a%(54): c = a%(55)
END SUB

SUB inword
    FOR i = 0 TO 15
        c = 1
        FOR j = 0 TO 15
            CALL iinword(a(i, j), b, c)
        NEXT j
'        PRINT
'PUT #1, , b
       PRINT #1, b
    NEXT i

END SUB

SUB mkhz (x, y, definex, definey, col, col1, dis)
CALL current(x, y, definex, definey, col, col1, dis)
COLOR 15
LOCATE 3, 21
PRINT "保存按"; : COLOR 14: PRINT "'S'"; : COLOR 15: PRINT "键;按";
COLOR 14: PRINT "'R'"; : COLOR 15: PRINT "键重新开始;退出按";
COLOR 14: PRINT "'ESC'"; : COLOR 15: PRINT "键"
LOCATE 4, 22
PRINT "按光标键移动光标,按ENTER键确定或消除点"
sx = x: sy = y
ex = x + dis * 15: ey = y + dis * 15
'col = 10': col1 = 11
'dis = 20
mkhz1:
a$ = INKEY$
SELECT CASE a$
       CASE CHR$(0) + CHR$(72)'up
            definey = y: definex = x
            y = y - dis
            IF y < sy THEN y = sy: definey = y
            CALL current(x, y, definex, definey, col, col1, dis)
       CASE CHR$(0) + CHR$(75)'left
            definex = x: definey = y
            x = x - dis
            IF x < sx THEN x = sx: definex = x
            CALL current(x, y, definex, definey, col, col1, dis)
       CASE CHR$(0) + CHR$(80)'down
            definey = y: definex = x
            y = y + dis
            IF y > ey THEN y = ey: definey = y
            CALL current(x, y, definex, definey, col, col1, dis)
       CASE CHR$(0) + CHR$(77)'rghit
            definex = x: definey = y
            x = x + dis
            IF x > ex THEN x = ex: definex = x
            CALL current(x, y, definex, definey, col, col1, dis)
       CASE CHR$(13) 'enter
            CALL paining(x, y, 15, col1, 2, dis)
       CASE CHR$(27)
            SYSTEM
       CASE "s"
            GOTO mkhz2
       CASE "S"
            GOTO mkhz2
       CASE "r"
            ON ERROR GOTO errr1
            RUN "inword.bas"
END SELECT
            GOTO mkhz1
mkhz2:
END SUB

SUB paining (x, y, col, col1, col3, dis)
col2 = 12
'col3 = 2
'dis = 20
    IF POINT(x, y) = col THEN
       PAINT (x, y), col3
    ELSE
    LINE (x - dis * .5, y - dis * .5)-(x + dis * .5, y - dis * .5), col2
    LINE -(x + dis * .5, y + dis * .5), col2
    LINE -(x - dis * .5, y + dis * .5), col2
    LINE -(x - dis * .5, y - dis * .5), col2
       PAINT (x, y), col2
    LINE (x - dis * .5, y - dis * .5)-(x + dis * .5, y - dis * .5), col3
    LINE -(x + dis * .5, y + dis * .5), col3
    LINE -(x - dis * .5, y + dis * .5), col3
    LINE -(x - dis * .5, y - dis * .5), col3
    END IF
END SUB

SUB readword (x, y, col1, dis)
    FOR i = 0 TO 15
        FOR j = 0 TO 15
            IF POINT(x + j * dis, y + i * dis) = 2 THEN
               a(i, j) = 1
            ELSE
               a(i, j) = 0
            END IF
        NEXT j
    NEXT i
END SUB

SUB rword (a, b, flag)
';               在 Quick BASIC中运行了显示汉字程序
';编译过程:
';       TASM    TXBASIC
';       TLINK   /t/x            TXBASIC
';       REN     TESTTX.COM      TXBASIC.BIN
' txbasic.asm
'code            segment                    ;显示汉字程序
'                org     100h
'                assume  cs:code,ds:code,es:code,ss:code
'start:
'                push    ax
'                push    bx
'                push    cx
'                push    dx
'                push    si
'                mov     si,0        ;此值由qbasic赋给
'
'                mov     ax,word ptr cs:[si]
'                mov     bx,word ptr cs:[si+2]
'                mov     cx,ax
'                not     cx
'                test    cx,bx
'                je      Exit1                 
'                mov     word ptr cs:[si+4],0     ;返回flag=0
'                jmp     exit
'exit1:          mov     word ptr cs:[si+4],1     ;返回flag=1
'             
'Exit:
'                sal     bx,1
'                mov     word ptr cs:[si+2],bx    ;返回b
'                pop     si
'                pop     dx
'                pop     cx
'                pop     bx
'                pop     ax
'                retf
'code            ends
'                end     start

DIM a%(60)
    a%(52) = a: a%(53) = b: a%(54) = flag
DEF SEG = VARSEG(a%(0))
RESTORE rworddat
FOR i% = 0 TO 49
    READ D%
    IF i% = 6 THEN    '给SI赋值
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

SUB word (x, y, col, gcol)
FOR j = 0 TO 15
    b = 1
INPUT #1, a
'GET #1, , a
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

SUB wordp (x, y, col, col1, dis)
SCREEN 12
   LINE (x, y)-(x + dis * 16, y), col
   LINE -(x + dis * 16, y + dis * 16), col
   LINE -(x, y + dis * 16), col
   LINE -(x, y), col
   PAINT (x + dis, y + dis), col
   FOR i = 1 TO 15
       LINE (x + i * dis, y)-(x + i * dis, y + 16 * dis), col1
       LINE (x, y + i * dis)-(x + 16 * dis, y + i * dis), col1
   NEXT i
   LINE (x, y)-(x + dis * 16, y), col1
   LINE -(x + dis * 16, y + dis * 16), col1
   LINE -(x, y + dis * 16), col1
   LINE -(x, y), col1
END SUB

