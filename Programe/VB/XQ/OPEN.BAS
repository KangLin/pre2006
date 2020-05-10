    name$ = "c:\ucdos\hzk16": k = 1
    CLS
    a$ = "жа"
    a = ASC(a$)
    b = ((a / 100) - 1) * 94 + (a MOD 100) - 1
    c = b * 16
    TYPE Record
        Score AS INTEGER
    END TYPE
    DIM Myrecord AS Record
    OPEN name$ FOR RANDOM AS #1 LEN = LEN(Myrecord)
    GET #1, c, Myrecord
    'PRINT Myrecord.Score
    SELECT CASE Myrecord.Score AND k * 2
           CASE 0
                PAINT (x + i, y), col

    CLOSE #1
   

