'COMMON a
    'Calls routine for printing the screen to a local printer.

    DEF SEG = &H9FE0
    'FOR i% = 0 TO 2
     '  READ d%
      ' POKE VARPTR(a%(0)) + i%, d%
    'NEXT i%
    'DATA 205, 5, 203  : ' int 5  retf  'Machine-language code
                                       'for printing screen.
a% = 0
    CALL ABSOLUTE(a$, a%)
    DEF SEG
    PRINT a$



