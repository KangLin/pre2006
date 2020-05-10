DECLARE SUB sstring ()
DIM SHARED a1, a1$
DECLARE SUB presser (a$, a)
 'CALL presser(a$, a)
 CALL sstring
20 PRINT a, a1$

SUB presser (a$, a)
10 a$ = INKEY$
   SELECT CASE a$
       CASE "0" TO "9"
            PRINT a$;
            a = ASC(a$) - 48
            a1 = a1 * 10 + a
            a = a1
       CASE IS = CHR$(13)
       GOTO pt20
       CASE ""
       GOTO 10
       CASE ELSE
       PRINT "error"
   END SELECT
GOTO 10
pt20:

END SUB

SUB sstring
string1:
       a$ = INKEY$
       SELECT CASE a$
              CASE "a" TO "z"
                   a1$ = a1$ + a$
                   PRINT a$;
              CASE " "
                   flag = 1
              CASE IS = CHR$(13)
                   GOTO sstring1
              CASE ""
                   GOTO string1

              CASE ELSE
                   PRINT "eeror"
       END SELECT
       GOTO string1
sstring1:
END SUB

