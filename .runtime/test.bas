10 FOR I=0 TO 31
20 PAPER I
30 PRINT " "
40 NEXT I
50 PAPER 0
60 PRINTL
70 PRINTL
80 PRINTL "REBASIC TEST PROGRAM"
90 PRINTL
100 PRINT "ENTER TEXT: "
110 A$=INPUT()
120 PRINTL
130 FOR I=0 TO 31
140 PEN 31 - I
150 PAPER I
160 PRINT A$ + " "
170 NEXT I
180 PRINTL
190 PRINTL
200 A$=INPUT()