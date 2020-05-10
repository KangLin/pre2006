DECLARE SUB load (ab!, x!, y!, p, definex, definey)
DECLARE SUB loadqi ()
DECLARE SUB start ()
DECLARE SUB word (x!, y!, bai, col!, gcol!)
DECLARE SUB rword (a!, b!, flag!)
DECLARE SUB hzout (a$, x, y, bai, col!, gcol!)
DECLARE SUB dsk ()
DECLARE SUB savemem (n$)
DECLARE SUB pass (pa$)
DECLARE SUB help ()
DECLARE SUB save ()
DECLARE SUB meundisp1 (flag!)
DECLARE SUB meundisp ()
DECLARE SUB meundis (flag!)
DECLARE SUB muen (a$)
DECLARE SUB time ()
DECLARE SUB mouse (ax!, bx!, cx!, dx!)
CALL mouse(a, 0, 0, 0)
IF a = 0 THEN SHELL "C:\MASM\BIN\MOUSE" '没有鼠标"
DIM SHARED errcode
DIM SHARED meun$(13)
meun$(0) = "meun:F1"
meun$(1) = "restart:"
meun$(2) = "INSERT"
meun$(3) = "play"
meun$(4) = "chinese"
meun$(5) = "chess:"
meun$(6) = "ENTER"
meun$(7) = "play"
meun$(8) = "repent"
meun$(9) = "DELETE"
meun$(10) = "save"
meun$(11) = "help"
meun$(12) = "load:F2"
meun$(13) = "exit:ESC"
DIM SHARED name$
name$ = "xq.dat"
TYPE MEMAB
    flag AS INTEGER
    ab AS INTEGER
    x AS INTEGER
    y AS INTEGER
    p AS INTEGER
END TYPE
DIM SHARED meab(10) AS MEMAB
DIM SHARED mem
SCREEN 12
qix = 138: qiy = 19: qidis = 45
DIM MouseMove
MouseMove = 5
qpcolor = 10
GOSUB initsystem
'CALL start
'2 IF a$ = INKEY$ THEN GOTO 2
10 SCREEN 13: CLS
CALL meundisp 'show meun
20 p = 1 'pang duang tiao jian
   DIM ab(10, 11) 'qi zhi   定义棋子
   FOR i = 0 TO 10: REM qipang       定义棋盘
       FOR j = 0 TO 11
          ab(i, j) = 0
       NEXT j
   NEXT i
   DIM n(4, 10)
   FOR i = 0 TO 4
       FOR j = 0 TO 10
           n(i, j) = 0
       NEXT j
   NEXT i
   qz = 0
   qix = 88: qiy = 9: qidis = 18
   qicolor = 1: qicolor1 = 12: qpcolor = 14: curcolor = 15
   shaix = 88 + 18 * 4: shaiy = 9    '为判断将是否对面而记下将的上一次位置
   ynes1 = 1                        '为判断是否吃将而记下的标志 ynes1=1时提示
                                                         'ynes1=-1时确定吃
GOSUB initsystem
98 x = 88: y = 9
RESTORE 121
100 FOR i = 1 TO 9                           '上底子 车马象士将
110 READ a
    ab = a: GOSUB 3000: ab((x - 88) / 18, (y - 9) / 18) = a
    x = x + 18
120 NEXT i
121 DATA 6,7,5,4,3,4,5,7,6                : REM   '绿子
122 x = 88: y = 9 + 180
123 FOR i = 1 TO 9
126 READ a
    ab = -ABS(a): GOSUB 3000: ab((x - 88) / 18, (y - 9) / 18) = a
    x = x + 18: y = 9 + 180
128 NEXT i
129 DATA -6,-7,-5,-4,-3,-4,-5,-7,-6        :  ' 红子
130 x = 88: y = 9 + 18 * 3
134 FOR i = 1 TO 5                           '兵
140 READ a
    ab = ABS(a): GOSUB 3000: ab((x - 88) / 18, (y - 9) / 18) = a
    x = x + 36: y = 9 + 18 * 3
150 NEXT i
151 DATA 1,1,1,1,1
156 x = 88 + 18: y = 9 + 18 * 2              '炮
160 FOR i = 1 TO 2
170 READ a
    ab = ABS(a): GOSUB 3000: ab((x - 88) / 18, (y - 9) / 18) = a
    x = x + 18 * 6: y = 9 + 18 * 2
180 NEXT i
181 DATA 2,2
184 x = 88: y = 9 + 18 * 7
190 FOR i = 1 TO 5
200 READ a
    ab = -ABS(a): GOSUB 3000: ab((x - 88) / 18, (y - 9) / 18) = a
    x = x + 36: y = 9 + 18 * 7
210 NEXT i
211 DATA -1,-1,-1,-1,-1
216 x = 88 + 18: y = 9 + 18 * 8
220 FOR i = 1 TO 2
230 READ a
    ab = -ABS(a): GOSUB 3000: ab((x - 88) / 18, (y - 9) / 18) = a
    x = x + 18 * 6: y = 9 + 18 * 8
231 DATA -2,-2
240 NEXT i
    x = 160: y = 99           'currer start locate   开始光标定位
    GOSUB 5000
    CIRCLE (310, 160), 9, qicolor1
    LOCATE 23, 33: PRINT "red walk": PAINT (310, 160), qicolor1
'CALL mouse(1, 0, 0, 0)

260 a$ = INKEY$               'recieve key   接收键盘输入
ON ERROR GOTO err1
'    IF a$ = CHR$(0) + CHR$(60) THEN GOSUB loadload: GOTO 260
    IF RIGHT$(a$, 1) = CHR$(59) THEN CALL muen(a$)
    'IF RIGHT$(a$, 1) = CHR$(82) THEN GOTO 10 '当按下INSERT键时重新开始
270 IF a$ = CHR$(27) THEN KILL name$: SYSTEM    'end when recieveed ESC 当接收到ESC时结束
    'chicke limit      检察光标是否在棋盘内
280 IF RIGHT$(a$, 1) = CHR$(72) THEN y = y - 18: b = y + 18: a = x: GOSUB bian
290 IF RIGHT$(a$, 1) = CHR$(75) THEN x = x - 18: a = x + 18: b = y: GOSUB bian
300 IF RIGHT$(a$, 1) = CHR$(77) THEN x = x + 18: a = x - 18: b = y: GOSUB bian
310 IF RIGHT$(a$, 1) = CHR$(80) THEN y = y + 18: b = y - 18: a = x: GOSUB bian
' 检察鼠标是否在棋盘内
CALL mouse(11, 0, bx, cx)
   IF bx > MouseMove THEN x = x + 18: a = x - 18: b = y: GOSUB bian
   IF bx < -MouseMove THEN x = x - 18: a = x + 18: b = y:  GOSUB bian
   IF cx > MouseMove THEN y = y + 18: b = y - 18: a = x:  GOSUB bian
   IF cx < -MouseMove THEN y = y - 18: b = y + 18: a = x:  GOSUB bian
   IF RIGHT$(a$, 1) = CHR$(82) THEN  '当按下INSERT键时重新开始
      mem = 0: flagmem = 0: KILL name$
      GOTO 10
   END IF
   IF RIGHT$(a$, 1) = CHR$(83) THEN GOSUB cancel         '悔棋delete键
CALL mouse(3, bx, 0, 0)     '检察鼠标是否按下左键
   IF bx = 1 THEN
      a$ = CHR$(13)
      CALL time
   END IF
   IF bx = 2 THEN a$ = CHR$(27)
   IF a$ = CHR$(27) THEN KILL name$: SYSTEM    'end when recieveed ESC 当接收到ESC时结束
   IF a$ <> CHR$(13) THEN GOTO 260      'chr$(13)是enter键
    '当enter键按下并且光标定位在红子上时,定义此子
    'define this chass when ENTER key was chicked and this chass is red
320 IF a$ = CHR$(13) AND p = 1 AND ab((x - 88) / 18, (y - 9) / 18) < 0 THEN
       GOSUB define: GOTO 260
    END IF
    '当enter键按下并且光标定位在非红子上时,定义此子
    'define this chass when ENTER key was chicked and this chass is not red
330 IF a$ = CHR$(13) AND p = 2 AND (NOT (ab((x - 88) / 18, (y - 9) / 18) < 0)) THEN
       GOSUB eat: GOTO 260
    END IF
    '当enter键按下并且光标定位在绿子上时,定义此子
    'define this chass when ENTER key was chicked and this chass is green
    IF a$ = CHR$(13) AND p = 3 AND ab((x - 88) / 18, (y - 9) / 18) > 0 THEN
       GOSUB define: GOTO 260
    END IF
    '当enter键按下并且光标定位在非绿子上时,定义此子
    'define this chass when ENTER key was chicked and this chass is not green
    IF a$ = CHR$(13) AND p = 4 AND (NOT (ab((x - 88) / 18, (y - 9) / 18) > 0)) THEN
       GOSUB eat
       GOTO 260
    END IF
    BEEP
    GOTO 260

1000 CIRCLE (x, y), 9, col: PAINT (x, y), col: REM house    马
     LINE (x - 3, y - 4)-(x + 3, y - 4), col1
     LINE -(x + 3, y - 1), col1
     LINE (x - 2, y - 4)-(x - 2, y), col1
     LINE -(x + 4, y), col1
     LINE -(x + 4, y + 5), col1
     LINE -(x + 3, y + 4), col1
     LINE (x - 5, y + 3)-(x + 3, y + 3), col1
    RETURN
1800 CIRCLE (x, y), 9, col: PAINT (x, y), col: REM bus        车
     LINE (x - 3, y - 4)-(x + 3, y - 4), col1
     LINE (x - 2, y - 2)-(x + 2, y - 2), col1
     LINE -(x + 2, y + 2), col1
     LINE -(x - 2, y + 2), col1
     LINE -(x - 2, y - 2), col1
     LINE (x - 2, y)-(x + 2, y), col1
     LINE (x - 5, y + 4)-(x + 5, y + 4), col1
     LINE (x, y - 6)-(x, y + 8), col1
    RETURN
2200 CIRCLE (x, y), 9, col: PAINT (x, y), col: REM xi           象                                      : CIRCLE (x, y), 9, 1: PAINT (x, y), 1
     LINE (x - 4, y - 3)-(x - 1, y - 3), col1
     LINE (x - 2, y - 6)-(x - 2, y + 6), col1
     LINE (x - 2, y - 5)-(x - 5, y + 4), col1
     LINE (x - 2, y)-(x - 1, y + 2), col1
     LINE (x + 1, y - 4)-(x + 4, y - 4), col1
     LINE -(x + 4, y + 4), col1
     LINE -(x + 1, y + 4), col1
     LINE -(x + 1, y - 4), col1
     LINE (x + 1, y - 1)-(x + 4, y - 1), col1
     LINE (x + 1, y + 1)-(x + 4, y + 1), col1
     RETURN
2300 CIRCLE (x, y), 9, col: PAINT (x, y), col: REM shi        士                                        : CIRCLE (x, y), 9, 1: PAINT (x, y), 1
     LINE (x - 6, y)-(x + 6, y), col1
     LINE (x - 3, y + 4)-(x + 3, y + 4), col1
     LINE (x, y - 4)-(x, y + 4), col1: RETURN
2400 CIRCLE (x, y), 9, col: PAINT (x, y), col: REM shuai    将
     LINE (x - 4, y - 3)-(x - 4, y), col1
     LINE (x - 2, y - 6)-(x - 2, y + 2), col1
     LINE -(x - 4, y + 5), col1
     LINE (x, y + 2)-(x, y - 3), col1
     LINE -(x + 4, y - 3), col1
     LINE -(x + 4, y + 3), col1
     LINE -(x + 3, y + 2), col1
     LINE (x + 2, y - 7)-(x + 2, y + 7), col1
    RETURN
2500 CIRCLE (x, y), 9, col: PAINT (x, y), col: REM pao       炮                                       : CIRCLE (x, y), 9, 1: PAINT (x, y), 1
     LINE (x - 4, y - 3)-(x - 4, y), col1
     LINE (x - 2, y - 6)-(x - 2, y + 2), col1
     LINE -(x - 4, y + 5), col1
     LINE (x, y - 4)-(x - 2, y), col1
     LINE (x - 2, y + 1)-(x, y + 5), col1
     LINE (x + 2, y - 6)-(x + 1, y - 1), col1
     LINE (x + 2, y - 4)-(x + 6, y - 4), col1
     LINE -(x + 6, y + 4), col1
     LINE -(x + 4, y + 2), col1
     LINE (x + 2, y - 1)-(x + 4, y - 1), col1
     LINE -(x + 4, y + 3), col1
     LINE -(x + 2, y + 3), col1
     LINE (x + 2, y - 1)-(x + 2, y + 5), col1
     LINE -(x + 7, y + 5), col1
     LINE -(x + 7, y + 4), col1
    RETURN
2600 CIRCLE (x, y), 9, col: PAINT (x, y), col: REM bing       兵
    LINE (x + 1, y - 4)-(x - 2, y - 3), col1
    LINE -(x - 2, y + 1), col1
    LINE (x - 2, y - 2)-(x + 3, y - 2), col1
    LINE (x + 1, y - 2)-(x + 1, y + 1), col1
    LINE (x - 4, y + 1)-(x + 4, y + 1), col1
    LINE (x - 1, y + 2)-(x - 4, y + 4), col1
    LINE (x + 1, y + 2)-(x + 4, y + 4), col1
   RETURN
3000 IF ab = 1 THEN col = qicolor: col1 = qicolor1: GOSUB 2600  'xiao zhi 下子
     IF ab = 2 THEN col = qicolor: col1 = qicolor1: GOSUB 2500
     IF ab = 3 THEN col = qicolor: col1 = qicolor1: GOSUB 2400
     IF ab = 4 THEN col = qicolor: col1 = qicolor1: GOSUB 2300
     IF ab = 5 THEN col = qicolor: col1 = qicolor1: GOSUB 2200
     IF ab = 6 THEN col = qicolor: col1 = qicolor1: GOSUB 1800
     IF ab = 7 THEN col = qicolor: col1 = qicolor1: GOSUB 1000
     IF ab = -1 THEN col = qicolor1: col1 = qicolor: GOSUB 2600
     IF ab = -2 THEN col = qicolor1: col1 = qicolor: GOSUB 2500
     IF ab = -3 THEN col = qicolor1: col1 = qicolor: GOSUB 2400
     IF ab = -4 THEN col = qicolor1: col1 = qicolor: GOSUB 2300
     IF ab = -5 THEN col = qicolor1: col1 = qicolor: GOSUB 2200
     IF ab = -6 THEN col = qicolor1: col1 = qicolor: GOSUB 1800
     IF ab = -7 THEN col = qicolor1: col1 = qicolor: GOSUB 1000
    RETURN
5000 FOR i = -5 TO 5: REM currse    光标
         PSET (x + i, y - 5), curcolor
         PSET (x - 5, y + i), curcolor
         PSET (x + i, y + 5), curcolor
         PSET (x + 5, y + i), curcolor
     NEXT i
    RETURN
5100 FOR i = -5 TO 5: REM cls_currse   1 清除光标
         PSET (a + i, b - 5), n(1, 5 + i)
         PSET (a + i, b + 5), n(2, i + 5)
         PSET (a - 5, b + i), n(3, i + 5)
         PSET (a + 5, b + i), n(4, i + 5)
     NEXT i
    RETURN
redcurrse:
5300 FOR i = -5 TO 5: REM read_currse   1记录当前光标
         n(1, i + 5) = POINT(x + i, y - 5)
         n(2, i + 5) = POINT(x + i, y + 5)
         n(3, i + 5) = POINT(x - 5, y + i)
         n(4, i + 5) = POINT(x + 5, y + i)
     NEXT i
    RETURN

bian:              '显示光标
'7000 IF x < 88 OR x > 232 OR y < 9 OR y > 189 THEN BEEP: x = a: y = b: RETURN ELSE 7010
7000 IF (x < 88 OR x > 232 OR y < 9 OR y > 189) AND NOT (a$ = "" AND x > 232) THEN
                             BEEP: x = a: y = b: RETURN
     ELSE '7010
     END IF
IF x > 232 AND a$ = "" THEN CALL muen(a$): x = 232
7010 IF y = 99 AND RIGHT$(a$, 1) = CHR$(72) THEN y = y - 18
     IF y = 99 AND RIGHT$(a$, 1) = CHR$(80) THEN y = y + 18
     CALL mouse(11, 0, mousex, mousey)
     IF y = 99 AND mousey < 0 THEN y = y - 18
     IF y = 99 AND mousey > 0 THEN y = y + 18

currst:
7100 GOSUB 5100: GOSUB 5300: GOSUB 5000
RETURN

define:     '确定棋子
ab = ab((x - 88) / 18, (y - 9) / 18): definex = x: definey = y: GOSUB tishi
IF mem < 0 THEN mem = 0
meab(mem).flag = 1: meab(mem).ab = ab: meab(mem).x = x: meab(mem).y = y
meab(mem).p = p
IF mem = 9 THEN
   OPEN name$ FOR APPEND AS #1
   FOR i = 0 TO 9
       PRINT #1, meab(i).flag
       PRINT #1, meab(i).ab
       PRINT #1, meab(i).x
       PRINT #1, meab(i).y
       PRINT #1, meab(i).p
   NEXT i
   CLOSE #1
   flagmem = 1
END IF
mem = (mem + 1) MOD 10: p = p + 1
'mem(qz).x1 = (x - 88) / 18: mem(qz).y1 = (y - 9) / 18: mem(qz).ab1 = ab: qz = qz + 1: LOCATE 1, 1: PRINT mem(qz).x1; " "; mem(qz).y1; " "; mem(qz).ab1
RETURN

eat:                         '吃子
GOSUB just                   '判断能否吃子
IF y = 99 THEN BEEP: GOTO 7220
7200  IF flag = 0 THEN BEEP: GOTO 7220    '如果标志为0,则返回
IF mem < 0 THEN mem = 0
meab(mem).p = p: meab(mem).flag = 0
meab(mem).ab = ab((x - 88) / 18, (y - 9) / 18)
meab(mem).x = x: meab(mem).y = y
IF mem = 9 THEN
   OPEN name$ FOR RANDOM AS #1 LEN = LEN(MEMAB)
   FOR i = 0 TO 9
       PRINT #1, meab(i).flag
       PRINT #1, meab(i).ab
       PRINT #1, meab(i).x
       PRINT #1, meab(i).y
       PRINT #1, meab(i).p
   NEXT i
   CLOSE #1
flagmem = 1': PRINT meab(mem).ab: PRINT meab(mem).x: PRINT meab(mem).y
END IF
mem = (mem + 1) MOD 10
REM bx(bx) = ab((definex - 88) / 18, (definey - 9) / 18) * 10000 + (definex - 88) / 18 * 100 + (definey - 9) / 18 + ab((x - 88), (y - 9) / 18) / 10: bx = bx + 1
eatx = x: eaty = y: x = definex: y = definey  '否则吃子
CIRCLE (x, y), 9, 0: PAINT (x, y), 0: REM cls       '清除定义位上的子
GOSUB agineline: ab((x - 88) / 18, (y - 9) / 18) = 0
x = eatx: y = eaty         '吃子
CIRCLE (x, y), 9, 0: PAINT (x, y), 0: GOSUB 3000: GOSUB 5300: GOSUB 5000
ab((x - 88) / 18, (y - 9) / 18) = ab: GOSUB tishi
'mem(qz).x1 = x: mem(qz).y1 = y: mem(qz).ab1 = ab: qz = qz + 1: LOCATE 1, 1: PRINT mem(qz).x1; " "; mem(qz).y1; " "; mem(qz).ab1
p = p + 1: IF p = 5 THEN p = 1
  '给判断象标志赋值
  IF ABS(ab((x - 88) / 18, (y - 9) / 18)) = 3 THEN
     shaix = x: shaiy = y
  END IF

7220 RETURN

just:   '判断能否吃子
IF ABS(ab) = 6 THEN GOSUB justbus
IF ABS(ab) = 2 THEN GOSUB justbao
IF ABS(ab) = 3 THEN GOSUB justshuai
IF ABS(ab) = 4 THEN GOSUB justshi
IF ABS(ab) = 5 THEN GOSUB justxian
IF ABS(ab) = 7 THEN GOSUB justhouse
IF ABS(ab) = 1 THEN GOSUB justbin
IF flag = 0 THEN RETURN
GOSUB jushd   '判断将是否对面
GOSUB ynes    '判断是否吃将
RETURN

jushd:      '判断将对面的情况
IF x = definex THEN flag = 1: RETURN
IF ab((shaix - 88) / 18, (shaiy - 9) / 18) = 3 THEN
   FOR i = 1 TO 10                       '将对面
   IF ((shaiy - 9) + i * 18) / 18 > 11 THEN i = i - 1: GOTO cancels
   IF shaiy + i * 18 = y AND shaix = x THEN RETURN
     IF shaix = definex AND shaiy + i * 18 = definey THEN i = i + 1
       IF ab((shaix - 88) / 18, ((shaiy - 9) + i * 18) / 18) <> 0 THEN
          GOTO cancels
       END IF
      NEXT i
cancels: IF ((shaiy - 9) + i * 18) / 18 > 11 THEN i = i - 1
         IF ab((shaix - 88) / 18, ((shaiy - 9) + i * 18) / 18) <> -3 THEN
              RETURN
         ELSE
              flag = 0
         END IF
END IF
IF ab((shaix - 88) / 18, (shaiy - 9) / 18) = -3 THEN
   FOR i = 1 TO 10
     IF ((shaiy - 9) - i * 18) / 18 < 0 THEN i = i - 1: GOTO cancelsh
     IF shaiy - i * 18 = y AND shaix = x THEN RETURN
     IF shaix = x AND shaiy - i * 18 = definey THEN i = i + 1
     IF ab((shaix - 88) / 18, ((shaiy - 9) - i * 18) / 18) <> 0 THEN
          'LOCATE 1, 1: PRINT shaix; shaiy; definex; definey; shaiy - i * 18
          GOTO cancelsh
     END IF
   NEXT i
cancelsh:  IF ((shaiy - 9) - i * 18) / 18 < 0 THEN i = i - 1
        IF (ab((shaix - 88) / 18, ((shaiy - 9) - i * 18) / 18)) <> 3 THEN
           RETURN
        ELSE
           flag = 0
       END IF
END IF
RETURN

ynes:
  IF ABS(ab((definex - 88) / 18, (definey - 9) / 18)) = 3 THEN RETURN
  IF ABS(ab((x - 88) / 18, (y - 9) / 18)) = 3 AND ynes1 = 1 THEN
     flag = 0: ynes1 = ynes1 * (-1)
   
    tishix = x: tishiy = y: tishiab = ab
    x = 10: y = 9 + 18 * 8: ab = ab((tishix - 88) / 18, (tishiy - 9) / 18): GOSUB 3000
    x = tishix: y = tishiy: ab = tishiab
    LOCATE 23, 1: PRINT "eat "

     RETURN
  END IF
  IF ynes1 = -1 THEN
     IF ABS(ab((x - 88) / 18, (y - 9) / 18)) = 3 AND ynes1 = -1 THEN
     flag = 1
     END IF
     ynes1 = ynes1 * (-1)
     CIRCLE (10, 9 + 18 * 8), 9, 0: PAINT (10, 9 + 18 * 8), 0
     LOCATE 23, 1: PRINT "    "
     RETURN
  END IF

RETURN

agineline: 'clease qi pang line  '清除棋盘线
LINE (x - 9, y)-(x + 9, y), qpcolor: LINE (x, y - 9)-(x, y + 9), qpcolor
IF x = 88 THEN LINE (x - 9, y)-(x - 1, y), 0
IF y = 9 THEN LINE (x, y - 1)-(x, y - 9), 0
IF x = 232 THEN LINE (x + 1, y)-(x + 9, y), 0
IF y = 189 THEN LINE (x, y + 1)-(x, y + 9), 0
  '边界条件
IF y = 81 AND x <> 88 AND x <> 232 THEN LINE (x, y + 1)-(x, y + 9), 0
IF y = 117 AND x <> 88 AND x <> 232 THEN LINE (x, y - 1)-(x, y - 9), 0
IF (y = 63 OR y = 135) AND (x = 124 OR x = 160 OR x = 196) OR (x = 106 AND (y = 153 OR y = 45)) OR (x = 214 AND (y = 153 OR y = 45)) THEN GOSUB xiwei
IF x = 232 AND (y = 63 OR y = 135) THEN LINE (x - 2, y + 2)-(x - 2, y + 4), qpcolor: LINE (x - 2, y - 2)-(x - 2, y - 4), qpcolor: LINE (x - 2, y - 2)-(x - 4, y - 2), qpcolor: LINE (x - 4, y + 2)-(x - 2, y + 2), qpcolor
IF x = 88 AND (y = 63 OR y = 135) THEN LINE (x + 2, y + 2)-(x + 2, y + 4), qpcolor: LINE (x + 2, y - 2)-(x + 2, y - 4), qpcolor: LINE (x + 2, y + 2)-(x + 4, y + 2), qpcolor: LINE (x + 2, y - 2)-(x + 4, y - 2), qpcolor
IF x = 160 AND (y = 27 OR y = 171) THEN LINE (x - 9, y - 9)-(x + 9, y + 9), qpcolor: LINE (x - 9, y + 9)-(x + 9, y - 9), qpcolor
IF x = 142 AND (y = 9 OR y = 153) THEN LINE (x, y)-(x + 9, y + 9), qpcolor
IF x = 178 AND (y = 9 OR y = 153) THEN LINE (x, y)-(x - 9, y + 9), qpcolor
IF x = 142 AND (y = 45 OR y = 189) THEN LINE (x, y)-(x + 9, y - 9), qpcolor
IF x = 178 AND (y = 45 OR y = 189) THEN LINE (x, y)-(x - 9, y - 9), qpcolor

RETURN
xiwei:
LINE (x + 2, y + 2)-(x + 2, y + 4), qpcolor: LINE (x + 2, y - 2)-(x + 2, y - 4), qpcolor: LINE (x - 2, y - 2)-(x - 2, y - 4), qpcolor: LINE (x - 2, y + 2)-(x - 2, y + 4), qpcolor
LINE (x + 2, y + 2)-(x + 4, y + 2), qpcolor: LINE (x + 2, y - 2)-(x + 4, y - 2), qpcolor: LINE (x - 2, y + 2)-(x - 4, y + 2), qpcolor: LINE (x - 2, y - 2)-(x - 4, y - 2), qpcolor
RETURN

justbus:   '车的走法
8000 IF x <> definex AND y <> definey THEN    '不在一条线上
       flag = 0: RETURN
     ELSE
       IF x <> definex THEN                                    'x不同时
          FOR i = 1 TO ABS(x - definex) / 18 - 1        '判断中间是否有子
                                                         ' 无子则标志为0
              IF ab((x - 88 + SGN(definex - x) * i * 18) / 18, (y - 9) / 18) <> 0 THEN
                 flag = 0: RETURN
              END IF
          NEXT i
       IF x = definex THEN flag = 0: RETURN    '同一位置时
       END IF
       IF y <> definey THEN     'y不同时
          FOR i = 1 TO ABS(y - definey) / 18 - 1    '判断中间是否有子
                                                       '无子则标志为0
              IF ab((x - 88) / 18, (y + SGN(definey - y) * i * 18 - 9) / 18) <> 0 THEN
                 flag = 0: RETURN
              END IF
          NEXT i
       IF y = definey THEN falg = 0: RETURN   ' 同一位置时
       END IF
     END IF
     flag = 1
     RETURN
justbao:     '炮的走法
8100 IF x <> definex AND y <> definey THEN   ' 不在一条线时
       flag = 0: RETURN
     ELSE
       IF x <> definex THEN
          FOR i = 1 TO ABS(x - definex) / 18 - 1
              IF ab((x - 88 + SGN(definex - x) * i * 18) / 18, (y - 9) / 18) <> 0 THEN
                 flagbao = flagbao + 1
              END IF
              IF flagbao > 1 THEN flagbao = 0: flag = 0: RETURN
          NEXT i
          IF flagbao = 1 AND ab((x - 88) / 18, (y - 9) / 18) = 0 THEN flagbao = 0: flag = 0: RETURN
       IF x = definex THEN flag = 0: RETURN
       END IF
       IF y <> definey THEN
          FOR i = 1 TO ABS(y - definey) / 18 - 1
              IF ab((x - 88) / 18, (y + SGN(definey - y) * i * 18 - 9) / 18) <> 0 THEN
                 flagbao = flagbao + 1
              END IF
              IF flagbao > 1 THEN flagbao = 0: flag = 0: RETURN
          NEXT i
          IF flagbao = 1 AND ab((x - 88) / 18, (y - 9) / 18) = 0 THEN flagbao = 0: flag = 0: RETURN
       IF y = definey THEN falg = 0: RETURN
       END IF
     END IF
     IF flagbao = 0 AND ab((x - 88) / 18, (y - 9) / 18) <> 0 THEN flag = 0: RETURN
     flag = 1
     RETURN

justshuai:        '将的走法
IF ab > 0 THEN
   IF x < 142 THEN flag = 0: RETURN
   IF x > 178 THEN flag = 0: RETURN
   IF y > 45 THEN flag = 0: RETURN
   IF x <> definex AND y <> definey THEN flag = 0: RETURN
FOR i = 1 TO 10                       '将对面
       IF ((y - 9) + i * 18) / 18 > 11 THEN i = i - 1: GOTO 8200 '限制ab()出界
       IF ab((x - 88) / 18, ((y - 9) + i * 18) / 18) <> 0 THEN
          GOTO 8200
       END IF
   NEXT i
   i = i - 1
8200   IF ab((x - 88) / 18, ((y - 9) + i * 18) / 18) <> -3 THEN
           flagshai = 1
        ELSE
           flagshai = 0
       END IF
   IF (ABS(x - definex) / 18 = 1 OR ABS((y - definey) / 18) = 1) AND flagshai = 1 THEN
      flag = 1: RETURN
   END IF
END IF

IF ab < 0 THEN
   IF x < 142 THEN flag = 0: RETURN
   IF x > 178 THEN flag = 0: RETURN
   IF y < 153 THEN flag = 0: RETURN
   IF x <> definex AND y <> definey THEN flag = 0: RETURN
   FOR i = 1 TO 10
      IF ((y - 9) - i * 18) / 18 < 0 THEN i = i - 1: GOTO 8300
      IF ab((x - 88) / 18, ((y - 9) - i * 18) / 18) <> 0 THEN
          GOTO 8300
       END IF
   NEXT i
   i = i - 1
8300 ' LOCATE 1, 1: PRINT i
IF ab((x - 88) / 18, ((y - 9) - i * 18) / 18) <> 3 THEN
           flagshai = 1
        ELSE
           flagshai = 0
       END IF
8301
   IF (ABS(x - definex) / 18 = 1 OR ABS((y - definey) / 18) = 1) AND flagshai = 1 THEN
   flag = 1: RETURN
   END IF
END IF
   flag = 0
RETURN

justshi:      '士的走法
IF ab > 0 THEN
   IF x < 142 THEN flag = 0: RETURN
   IF x > 178 THEN flag = 0: RETURN
   IF y > 45 THEN flag = 0: RETURN
   IF ABS(x - definex) / 18 = 1 AND ABS((y - definey) / 18) = 1 THEN
   flag = 1: RETURN
   END IF
END IF
IF ab < 0 THEN
   IF x < 142 THEN flag = 0: RETURN
   IF x > 178 THEN flag = 0: RETURN
   IF y < 153 THEN flag = 0: RETURN
   IF ABS(x - definex) / 18 = 1 AND ABS((y - definey) / 18) = 1 THEN
   flag = 1: RETURN
   END IF
END IF
   flag = 0

RETURN

justxian:     '象的走法
IF ab > 0 THEN
   IF NOT ((x = 124 AND (y = 9 OR y = 81)) OR (x = 196 AND (y = 9 OR y = 81)) OR ((x = 160 OR x = 9 OR x = 232) AND y = 45)) THEN
   flag = 0: RETURN
   END IF
END IF
IF ab < 0 THEN
   IF NOT ((x = 124 AND (y = 117 OR y = 189)) OR (x = 196 AND (y = 117 OR y = 189)) OR ((x = 88 OR x = 160 OR x = 232) AND y = 153)) THEN
   flag = 0: RETURN
   END IF
END IF
IF NOT ((ABS(x - definex) / 18 = 2 AND ABS(y - definey) / 18 = 2)) THEN flag = 0: RETURN
IF ab((definex + (x - definex) / 2 - 88) / 18, (definey + (y - definey) / 2 - 9) / 18) <> 0 THEN flag = 0: RETURN
flag = 1
RETURN

justhouse:   '马的走法
IF (y = 81 AND definey = 117) OR (y = 117 AND definey = 81) THEN
 IF ABS(x - definex) / 18 = 2 AND ABS(y - definey) / 18 = 2 THEN
    IF ab((definex + (x - definex) / 2 - 88) / 18, (definey - 9) / 18) = 0 THEN
    flag = 1: RETURN
    END IF
 END IF
 flag = 0
 RETURN
END IF
IF (y = 81 - 18 AND definey = 117) OR (y = 117 + 18 AND definey = 81) THEN
 IF ABS(x - definex) / 18 = 1 AND ABS(y - definey) / 18 = 3 THEN
    IF ab((definex - 88) / 18, (definey + (y - definey) / 2 - 9) / 18) = 0 THEN
    flag = 1: RETURN
    END IF
 END IF
 flag = 0
 RETURN
END IF

IF ABS(x - definex) / 18 = 2 AND ABS(y - definey) / 18 = 1 THEN
   IF ab((definex + (x - definex) / 2 - 88) / 18, (definey - 9) / 18) = 0 THEN
   flag = 1: RETURN
   END IF
END IF
IF ABS(x - definex) / 18 = 1 AND ABS(y - definey) / 18 = 2 THEN
   IF ab((definex - 88) / 18, (definey + (y - definey) / 2 - 9) / 18) = 0 THEN
   flag = 1: RETURN
   END IF
END IF
flag = 0
RETURN

justbin:   '兵的走法
IF ab > 0 THEN
   IF y < 81 THEN
   flag = 0: RETURN
   ELSE
   IF y = 81 AND definex <> x THEN flag = 0: RETURN
   IF definex <> x AND definey <> y THEN flag = 0: RETURN
   IF y = 117 AND y - definey = 36 THEN flag = 1: RETURN
   IF (y - definey = 18 OR ABS(x - definex) = 18) THEN flag = 1: RETURN
   END IF
END IF
IF ab < 0 THEN
   IF y > 117 THEN
   flag = 0: RETURN
   ELSE
   IF y = 117 AND definex <> x THEN flag = 0: RETURN
   IF definex <> x AND definey <> y THEN flag = 0: RETURN
   IF y = 81 AND y - definey = -36 THEN flag = 1: RETURN
   IF (y - definey = -18 OR ABS(x - definex) = 18) THEN flag = 1: RETURN
   END IF
END IF
flag = 0
RETURN


tishi:    '提示
          '绿棋定义
IF p = 3 THEN
CIRCLE (10, 10), 9, 1: PAINT (10, 10), 1: tishix = x: tishiy = y
x = 10: y = 10: GOSUB 3000: x = tishix: y = tishiy
LOCATE 4, 1: PRINT "selected "
CIRCLE (310, 160), 9, 0: PAINT (310, 160), 0
LOCATE 23, 33: PRINT "        "
END IF
           '红棋吃子
IF p = 2 THEN
CIRCLE (10, 10), 9, 1: PAINT (10, 10), 0: CIRCLE (10, 10), 9, qicolor: PAINT (10, 10), qicolor
LOCATE 4, 1: PRINT "blue walk"
CIRCLE (310, 160), 9, 0: PAINT (310, 160), 0
LOCATE 23, 33: PRINT "        "
END IF
           '红棋定义
IF p = 1 THEN
CIRCLE (310, 160), 9, 2: PAINT (310, 160), 2: tishix = x: tishiy = y
x = 310: y = 160: GOSUB 3000: x = tishix: y = tishiy
LOCATE 23, 33: PRINT "selected"
CIRCLE (10, 10), 9, 0: PAINT (10, 10), 0
LOCATE 4, 1: PRINT "         "
END IF
            '绿棋吃子
IF p = 4 THEN
CIRCLE (310, 160), 9, 2: PAINT (310, 160), 0: CIRCLE (310, 160), 9, qicolor1: PAINT (310, 160), qicolor1
LOCATE 23, 33: PRINT "red walk"
CIRCLE (10, 10), 9, 0: PAINT (10, 10), 0
LOCATE 4, 1: PRINT "          "
END IF
RETURN

mouseda:
DATA &H50, &H53, &H51, &H52, &H56, &HBE, &H0, &H0, &H2E, &H8B, &H4, &HCD, &H33, &H2E, &H89, &H4
DATA &H83,&Hc6,&H02,&H2e,&H89,&H1c,&H83,&Hc6,&H02,&H2e,&H89,&H0c,&H83,&Hc6,&H02,&H2e
DATA &H89,&H14,&H5e,&H5a,&H59,&H5B,&H58,&HCB

cancel:       '悔棋
mem = mem - 1
IF mem < 0 AND flagmem = 0 THEN mem = 0: BEEP: RETURN
IF mem < 0 THEN
mem = 9': BEEP: RETURN
END IF
     IF meab(mem).flag THEN
        GOSUB cancel1
        ab = ab((x - 88) / 18, (y - 9) / 18): GOSUB 3000 '光标所在处
           ab = meab(mem).ab: x = meab(mem).x: y = meab(mem).y
           GOSUB cancel2': LOCATE 11, 1: PRINT P
     ELSE
        GOSUB cancel1
        ab = ab((x - 88) / 18, (y - 9) / 18): GOSUB 3000 '光标所在处
          ab = meab(mem).ab: x = meab(mem).x: y = meab(mem).y
           ab((x - 88) / 18, (y - 9) / 18) = ab
          GOSUB cancel3': LOCATE 11, 1: PRINT p
              mem = mem - 1
              ab = meab(mem).ab: x = meab(mem).x: y = meab(mem).y
              GOSUB cancel2
     END IF
RETURN
cancel1:
CIRCLE (x, y), 9, 0: PAINT (x, y), 0: REM cls       '清除定义位上的子
GOSUB agineline
RETURN

cancel2:
CIRCLE (x, y), 9, 0: PAINT (x, y), 0: GOSUB 3000: GOSUB 5300: GOSUB 5000
ab((x - 88) / 18, (y - 9) / 18) = ab
p = meab(mem).p: p = p - 1: IF p = 0 THEN p = 4
GOSUB tishi': LOCATE 11, 1: PRINT P
p = meab(mem).p
RETURN

cancel3:
CIRCLE (x, y), 9, 0: PAINT (x, y), 0
GOSUB agineline: GOSUB 3000
RETURN

errsub:
errcode = ERR
RESUME NEXT

err1:
RESUME NEXT

dskl:
DATA 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0
DATA 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0
DATA 0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0
DATA 0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0
DATA 0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0
DATA 0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0
DATA 0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0
DATA 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0
DATA 0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0
DATA 0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0
DATA 0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0
DATA 0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0
DATA 1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0
DATA 1,0,1,1,0,0,1,1,0,1,0,0,0,0,1,0,0
DATA 1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1

DATA 0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0
DATA 0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0
DATA 0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0
DATA 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
DATA 0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0
DATA 0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0
DATA 0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,0,0
DATA 0,0,0,1,0,1,1,0,0,1,0,1,0,1,0,0,0
DATA 0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0
DATA 0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0
DATA 0,0,0,1,0,1,0,1,1,0,0,1,0,0,1,0,0
DATA 0,0,1,0,0,1,0,1,1,0,0,1,0,0,1,0,0
DATA 0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0
DATA 0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0
DATA 0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0
DATA 1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0
DATA 1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1

initsystem:
25 LINE (qix + qidis * 3, qiy)-(qix + qidis * 5, qiy + qidis * 2), qpcolor
26 LINE (qix + qidis * 5, qiy)-(qix + qidis * 3, qiy + qidis * 2), qpcolor
27 LINE (qix + qidis * 5, qiy + qidis * 10)-(qix + qidis * 3, qiy + qidis * 8), qpcolor
28 LINE (qix + qidis * 3, qiy + qidis * 10)-(qix + qidis * 5, qiy + qidis * 8), qpcolor
30 FOR i = 1 TO 11: IF i = 6 THEN 50
40 LINE (qix, qiy + qidis * (i - 1))-(qix + 8 * qidis, qiy + qidis * (i - 1)), qpcolor
50 NEXT i
60 FOR i = 1 TO 9
70 LINE (qix + qidis * (i - 1), qiy)-(qidis * (i - 1) + qix, qiy + qidis * 4), qpcolor
80 LINE (qix + (i - 1) * qidis, qiy + qidis * 6)-(qix + qidis * (i - 1), qiy + qidis * 6 + qidis * 4), qpcolor
90 NEXT i
95 LINE (qix, qiy)-(qix, qiy + qidis * 10), qpcolor: LINE (qix + qidis * 8, qiy)-(qix + qidis * 8, qiy + qidis * 10), qpcolor
RETURN

rworddat:
DATA &h50,&h53,&h51,&h52,&h56,&hbe,&h00,&h00,&h2e,&h8b,&h04,&h2e,&h8b,&h5c,&h02
DATA &h8b,&hc8,&hf7,&hd1,&h85,&hcb,&h74,&h09,&h2e,&hc7,&h44,&h04,&h00,&h00,&heb
DATA &h07,&h90,&h2e,&hc7,&h44,&h04,&h01,&h00,&Hd1,&He3,&H2e,&H89,&H5c,&H02,&h5e
DATA &h5a,&h59,&h5b,&h58,&hcb

hzklab:
IF ERR = 53 THEN
   CLS : LOCATE 12, 30
   PRINT "Illegal user"
ELSE
   PRINT "no this word"
END IF
SYSTEM

loadload:
        IF loadflag = 0 THEN CALL loadqi: loadflag = 1
        CALL load(ab, x, y, p, definex, definey)
        IF p MOD 2 = 0 THEN
           GOSUB eat
        ELSE
          ' GOSUB define
        END IF
     '   GOTO 260
        'a$ = CHR$(13)
    'END IF

RETURN

SUB dsk
'SCREEN 13
col = 12
x = 140: y = 55
'OPEN "kangling" FOR RANDOM AS #1
'   FOR kkl = 1 TO 2
'   FOR i = 0 TO 16
'       FOR j = 0 TO 16
'           k = k + 1
'           GET #1, k, a$
'           IF a$ = "1" THEN PSET (x + j, y + i), col
'           NEXT j
'           NEXT i
'           x = x + 17
'           NEXT kkl
'CLOSE
   FOR kkl = 1 TO 2
   FOR i = 0 TO 16
       FOR j = 0 TO 16
'           k = k + 1
'           GET #1, k, a$
READ a$
           IF a$ = "1" THEN PSET (x + j, y + i), col
           NEXT j
           NEXT i
           x = x + 17
           NEXT kkl
END SUB

SUB help
DIM n(300, 52)
col = 3: x = 10: y = 52
    FOR i = 0 TO 300
        FOR j = 0 TO 52
            n(i, j) = POINT(x + i, y + j)
        NEXT j
    NEXT i
    LINE (x, y)-(x + 300, y), col
    LINE -(x + 300, y + 52), col
    LINE -(x, y + 52), col
    LINE -(x, y), col
    PAINT (x + 1, y + 1), col
COLOR 15
LOCATE 8, 3: PRINT "Desiger:";
COLOR 12
CALL pass(ps$)
PRINT ps$;
COLOR 15
PRINT "       ";
PRINT "Year:2000-2001 "
LOCATE 9, 3: PRINT "Verson :2000          ";
PRINT "exit";
COLOR 2
PRINT ": ESC      "; ""
COLOR 15
LOCATE 10, 3
PRINT "use current key or mouse to move     "
LOCATE 11, 3
PRINT "current,press mouse's right butten to"
LOCATE 12, 3
PRINT "exit.press mouse's left butten to    "
LOCATE 13, 3
PRINT "sure chess.                          "
CALL dsk
help10:
a$ = INKEY$
IF a$ = CHR$(27) THEN
  ELSE
     GOTO help10
END IF

    FOR i = 0 TO 300
        FOR j = 0 TO 52
              PSET (x + i, y + j), n(i, j)
        NEXT j
    NEXT i
END SUB

SUB hzout (a$, x, y, bai, col, gcol)
'a$是输入字符
'x,y是字符座标bai是放大倍数
'由start调用
ON ERROR GOTO hzklab
    OPEN "kkkkkkk.bas" FOR INPUT AS #1
'SCREEN 12
hzkout:
    INPUT #1, b$
    IF b$ <> a$ THEN GOTO hzkout
    CALL word(x, y, bai, col, gcol)
CLOSE
END SUB

SUB infile

   OPEN name$ FOR OUTPUT AS #2
   INPUT #1, meab(0).flag
   INPUT #1, meab(0).ab
   INPUT #1, meab(0).x
   INPUT #1, meab(0).y
   INPUT #1, meab(0).p
   CLOSE #2

END SUB

SUB load (ab, x, y, p, definex, definey)
    ON ERROR GOTO errsub
                INPUT #100, flag
           IF errcode = 62 THEN errcode = 0: CLOSE #100: GOTO ssav11  'input pase end of file
                INPUT #100, ab
                INPUT #100, x
                INPUT #100, y
                INPUT #100, p
'                IF p MOD 2 <> 0 THEN
'                  definex = xx: definey = yy
'                ELSE
'                   x = xx: y = yy
'                END IF
ssav11:
END SUB

SUB loadqi
    ON ERROR GOTO errsub
DIM n(200, 20)
col = 3: x = 50: y = 85
    GOSUB ssavemeun   '显示对话框
    LOCATE 12, 10
    PRINT "input file name"
    LOCATE 13, 10
    INPUT na$
    IF na$ = "" THEN GOTO ssav1
    OPEN na$ FOR INPUT AS #100                         'not find file
    IF errcorde = 52 OR errcode = 53 THEN errcode = 0: GOTO ssav1
ssav1:
    GOSUB ssav          '清除对话框
    GOTO ssaveend       '退出此子程序
ssav:
    FOR i = 0 TO 200
        FOR j = 0 TO 20
              PSET (x + i, y + j), n(i, j)
        NEXT j
    NEXT i
RETURN
ssavemeun:
    FOR i = 0 TO 200
        FOR j = 0 TO 20
            n(i, j) = POINT(x + i, y + j)
        NEXT j
    NEXT i
    LINE (x, y)-(x + 200, y), col
    LINE -(x + 200, y + 20), col
    LINE -(x, y + 20), col
    LINE -(x, y), col
    PAINT (x + 1, y + 1), col
RETURN
ssaveend:
END SUB

SUB meundisp
COLOR 15
LOCATE 1, 33: PRINT meun$(0)
LOCATE 2, 33: PRINT meun$(1)
LOCATE 3, 33: PRINT meun$(2)
LOCATE 4, 33: PRINT meun$(3)
LOCATE 5, 33: PRINT meun$(4)
LOCATE 6, 33: PRINT meun$(5)
LOCATE 7, 33: PRINT meun$(6)
LOCATE 8, 33: PRINT meun$(7)
LOCATE 9, 33: PRINT meun$(8)
LOCATE 10, 33: PRINT meun$(5)
LOCATE 11, 33: PRINT meun$(9)
LOCATE 12, 33: PRINT meun$(10)
LOCATE 13, 33: PRINT meun$(11)
LOCATE 14, 33: PRINT meun$(12)
LOCATE 15, 33: PRINT meun$(13)
END SUB

SUB meundisp1 (flag)
SELECT CASE flag
       CASE 0
            CALL meundisp
            COLOR 2
            LOCATE 1, 33: PRINT meun$(0)
       CASE 1
            CALL meundisp
            COLOR 2
            LOCATE 2, 33: PRINT meun$(1)
            LOCATE 3, 33: PRINT meun$(2)
       CASE 2
            CALL meundisp
            COLOR 2
            LOCATE 4, 33: PRINT meun$(3)
            LOCATE 5, 33: PRINT meun$(4)
            LOCATE 6, 33: PRINT meun$(5)
            LOCATE 7, 33: PRINT meun$(6)
       CASE 3
            CALL meundisp
            COLOR 2
            LOCATE 8, 33: PRINT meun$(7)
       CASE 4
            CALL meundisp
            COLOR 2
            LOCATE 9, 33: PRINT meun$(8)
            LOCATE 10, 33: PRINT meun$(5)
            LOCATE 11, 33: PRINT meun$(9)
       CASE 5
            CALL meundisp
            COLOR 2
            LOCATE 12, 33: PRINT meun$(10)
       CASE 6
            CALL meundisp
            COLOR 2
            LOCATE 13, 33: PRINT meun$(11)
       CASE 7
            CALL meundisp
            COLOR 2
            LOCATE 14, 33: PRINT meun$(12)
       CASE 8
            CALL meundisp
            COLOR 2
            LOCATE 14, 33: PRINT meun$(12)
END SELECT
END SUB

SUB mouse (ax, bx, cx, dx)
DIM a%(50)
a%(43) = ax: a%(44) = bx: a%(45) = cx: a%(46) = dx
DEF SEG = VARSEG(a%(0))
RESTORE mouseda
FOR i% = 0 TO 39
    READ d%
    IF i% = 6 THEN
       d% = VARPTR(a%(43)) MOD 256
    ELSEIF i% = 7 THEN
       d% = VARPTR(a%(43)) / 256
    END IF
    POKE VARPTR(a%(0)) + i%, d%
NEXT i%
CALL ABSOLUTE(VARPTR(a%(0)))
DEF SEG
ax = a%(43): bx = a%(44): cx = a%(45): dx = a%(46)
END SUB

SUB muen (b$)
'当增加菜单时改flag值和case值和meundisp和meundisp1两子程序,还要改主程序中的
'数组meun$
CALL meundisp1(flag)
meun10:
a$ = INKEY$
CALL mouse(3, bx, 0, 0)     '检察鼠标是否按下左键
   IF bx = 1 THEN
      a$ = CHR$(13)
      CALL time
   END IF
   IF bx = 2 THEN a$ = CHR$(27)
IF a$ = CHR$(27) THEN KILL name$: SYSTEM
CALL mouse(11, 0, bx, cx)
   IF ABS(bx) > 10 THEN GOTO meunend
   SELECT CASE cx
          CASE IS > 0
               a$ = CHR$(80)'flag = flag + 1
          CASE IS < 0
               a$ = CHR$(72)'flag = flag - 1
   END SELECT
SELECT CASE RIGHT$(a$, 1)
       CASE CHR$(72)  'up
            flag = flag - 1
            IF flag < 0 THEN flag = 8    '当增加菜单时改flag值
            CALL meundisp1(flag)
       CASE CHR$(80)
            flag = flag + 1
            IF flag = 9 THEN flag = 0    '当增加菜单时改flag值
            CALL meundisp1(flag)
END SELECT
IF a$ = CHR$(13) THEN
   SELECT CASE flag
          CASE 0
          CASE 1              'restart
              b$ = CHR$(82)
              GOTO meunend
          CASE 2
              b$ = CHR$(13)   'enter
              GOTO meunend
          CASE 3
              GOTO meunend
          CASE 4
              b$ = CHR$(83)   'delete
              GOTO meunend
          CASE 5
              CALL save
          CASE 6              'hlep
              CALL help
          CASE 7
              CALL loadqi      'load F2:CHR$(60)
              GOTO meunend
          CASE 8                         '当增加菜单时改此值
              b$ = CHR$(27)   'esc
              GOTO meunend
   END SELECT
END IF
GOTO meun10
meunend:
CALL meundisp
END SUB

SUB pass (pa$)
DIM a(6)
a(1) = 150
a(2) = 194
a(3) = 220
a(4) = 206
a(5) = 152
a(6) = 210
FOR i = 1 TO 6
  pa$ = pa$ + CHR$(a(i) / 2)
NEXT i
pa$ = pa$ + CHR$(a(3) / 2)
END SUB

SUB rword (a, b, flag)
'由word调用
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
    READ d%
    IF i% = 6 THEN                    '给SI赋值
       d% = VARPTR(a%(52)) MOD 256    ' ......
    ELSEIF i% = 7 THEN                ' ......
       d% = VARPTR(a%(52)) / 256      ' ......
    END IF                            ' ......
    POKE VARPTR(a%(0)) + i%, d%       ' ......
NEXT i%

CALL ABSOLUTE(VARPTR(a%(0)))
DEF SEG
b = a%(53): flag = a%(54)
END SUB

SUB save    '棋子存盘
    ON ERROR GOTO errsub
DIM n(200, 20)
col = 3: x = 50: y = 85
    GOSUB savemeun   '显示对话框
    LOCATE 12, 10
    PRINT "input file name"
    LOCATE 13, 10
    INPUT na$
    IF na$ = "" THEN GOTO sav1
    IF mem >= 0 THEN CALL savemem(na$)      '保存数组中棋子
    OPEN name$ FOR INPUT AS #1              '保存数据文件中棋子
    IF errcorde = 52 OR errcode = 53 THEN errcode = 0: GOTO sav1'bad file name or
    OPEN na$ FOR APPEND AS #2                         'not find file
    IF errcorde = 52 OR errcode = 53 THEN errcode = 0: GOTO sav1
    WHILE (1)
    INPUT #1, aaa$
    IF errcode = 62 THEN errcode = 0: GOTO sav1   'input pase end of file
    PRINT #2, aaa$
    WEND
sav1:
    CLOSE
    GOSUB sav          '清除对话框
    GOTO saveend       '退出此子程序
sav:
    FOR i = 0 TO 200
        FOR j = 0 TO 20
              PSET (x + i, y + j), n(i, j)
        NEXT j
    NEXT i
RETURN
savemeun:
    FOR i = 0 TO 200
        FOR j = 0 TO 20
            n(i, j) = POINT(x + i, y + j)
        NEXT j
    NEXT i
    LINE (x, y)-(x + 200, y), col
    LINE -(x + 200, y + 20), col
    LINE -(x, y + 20), col
    LINE -(x, y), col
    PAINT (x + 1, y + 1), col
RETURN
saveend:
END SUB

SUB savemem (n$)
mem = mem - 1
savemem10:
OPEN n$ FOR OUTPUT AS #1
 PRINT #1, meab(mem).flag
 PRINT #1, meab(mem).ab
 PRINT #1, meab(mem).x
 PRINT #1, meab(mem).y
 PRINT #1, meab(mem).p
IF mem < 0 THEN
ELSE
mem = mem - 1
GOTO savemem10
END IF
CLOSE
'mem = 0
END SUB

SUB start
'call hzout("",x,y,,bai,col,gxol)
CALL hzout("象", 100, 60, 10, 12, 0)
CALL hzout("棋", 400, 60, 10, 12, 0)
CALL hzout("设", 100, 250, 2, 14, 0)
CALL hzout("计", 140, 250, 2, 14, 0)
CALL hzout(":", 180, 250, 2, 14, 0)
CALL hzout("康", 218, 300, 6, 15, 0)
CALL hzout("林", 318, 300, 6, 15, 0)
y = 400: x = 205
CALL hzout("按", x, y, 2, 12, 1) '
x = x + 2 * 16 + 5
CALL hzout("任", x, y, 2, 12, 1)
x = x + 2 * 16 + 5
CALL hzout("意", x, y, 2, 12, 1)
x = x + 2 * 16 + 5
CALL hzout("键", x, y, 2, 12, 1)
x = x + 2 * 16 + 5
CALL hzout("继", x, y, 2, 12, 1)
x = x + 2 * 16 + 5
CALL hzout("续", x, y, 2, 12, 1)
LOCATE 28, 15
COLOR 14
PRINT "Verson:2000"
LOCATE 28, 55
PRINT "Year:2000-2001"
END SUB

SUB time
   timee$ = TIME$
   time1$ = RIGHT$(timee$, 1)
timelop:
   timee$ = TIME$
   time2$ = RIGHT$(timee$, 1)
   b = ASC(time2$) - ASC(time1$)
   IF ABS(b) >= .2 THEN GOTO timelop1
   GOTO timelop
timelop1:
END SUB

SUB word (x, y, bai, col, gcol)
'由hzout调用
'调用rword子程序读字库
'bai 是放大倍数
'col 是当前颜色gcol是背景色
FOR j = 0 TO 15
    b = 1
INPUT #1, a
    FOR i = 0 TO 15
        CALL rword(a, b, flag)
           FOR jj = 0 TO bai
            FOR ii = 0 TO bai
             IF flag = 1 THEN
                PSET (x + i * bai + jj, y + bai * j + ii), col
             ELSE
                IF gcol <> 0 THEN
                    PSET (x + i * bai + jj, y + bai * j + ii), gcol
                END IF
             END IF
            NEXT ii
           NEXT jj
    NEXT i
NEXT j
END SUB

