Attribute VB_Name = "ZouFai"
Option Explicit

Public Const s横座标 = "横座标:"
Public Const s纵座标 = "纵座标:"
Const s已输 = "已输,是重新开始，还是结束？如果重、新开始请按是（Y），否则，按否（N）"
Const s被将军 = "被将军"
Const s帅将对面 = "'帅'与'将'对面"
Const s不符合棋子走法 = "非法位置"
Const s兵不符合棋子走法 = "不符合棋子走法"

Public Const s叫将 = "叫将"
Private Enum Enum_Walk_Val
        被将 = False
        未叫将 = 1
        叫将 = 2
End Enum

Public Enum Enum_QiJuBianMa_Flag
       进行编码
       进行解码
End Enum

Public Type Type_XinShiFenXiBiao
       XinShi As Integer '形势值,在于0为被甲方控制
                         '小于0为被乙方控制
       jF_eControl() As Integer '甲方控制此位置的棋
       yF_eControl() As Integer '乙方控制此位置的棋
       End Type
'Public tXinShiFenXiBiao(9, 10) As Type_XinShiFenXiBiao

Public bJiaoJian As Boolean '是否提示叫将

'判断是叫将还是被将
'被将返回0,叫将还回1,如果将被吃返回
Public Function JianJun(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer, Optional Show As Boolean = True) As Boolean
Dim K As Integer, L As Integer, X As Integer, Y As Integer
Dim fQJ(9, 10) As Integer, exi As Integer
'1.建一个已走棋局,并初始化
For K = 0 To 9
    For L = 0 To 10
        fQJ(K, L) = iQiJu(K, L)
    Next L
Next K
fQJ(I, j) = fQJ(Di, Dj) '走子
fQJ(Di, Dj) = 0
'2.找到走方的将
For K = 1 To 9
    For L = 1 To 10
        If fQJ(K, L) = Sgn(iQiJu(Di, Dj)) * Enum_QZ.Shuai Then
           X = K: Y = L '将的位置
           Exit For
        End If
    Next L
Next K
'3.判断是否被吃,
'如果是被吃,则返回Enum_Walk_Val.被将,
'并提示被将和退出,否则继续第4.步
If bShuaiBeiChi(X, Y, fQJ) Then
   JianJun = Enum_Walk_Val.被将
   If Show Then MsgBox s被将军, vbCritical
   Exit Function
End If
'4.找到未走方帅,如果找不到,则结束这盘棋unload form1
For K = 1 To 9
    For L = 1 To 10
        If fQJ(K, L) = -Sgn(iQiJu(Di, Dj)) * Enum_QZ.Shuai Then
           X = K: Y = L '将的位置
           Exit For
        End If
    Next L
Next K
'如果找不到,则结束这盘棋unload form1
If K > 10 And L > 11 Then
   If Show Then
      If Sgn(iQiJu(Di, Dj)) = Sgn(Enum_QiZhi.jShuai) Then
         exi = MsgBox(Form1.LabYF.Caption & s已输, vbQuestion + vbYesNo)
      Else
         exi = MsgBox(Form1.LabJF.Caption & s已输, vbQuestion + vbYesNo)
      End If
      If exi = vbYes Then
         Form1.mnuFileReStart_Click
         Exit Function
      Else
         Unload Form1
      End If
    End If
End If
'5.判断是否被叫吃,
'如果是则返回Enum_Walk_Val.叫吃
'否则返回Enum_Walk_Val.未叫将
If bShuaiBeiChi(X, Y, fQJ) Then
   If bQiJuEnd(X, Y, fQJ) Then '判断是否将死
      If Show Then
         If Sgn(iQiJu(Di, Dj)) = Sgn(Enum_QiZhi.jShuai) Then
            exi = MsgBox(Form1.LabYF.Caption & s已输, vbQuestion + vbYesNo)
         Else
            exi = MsgBox(Form1.LabJF.Caption & s已输, vbQuestion + vbYesNo)
         End If
         If exi = vbYes Then
            Form1.mnuFileReStart_Click
            Exit Function
         Else
            Unload Form1
         End If
      End If
   Else
      JianJun = Enum_Walk_Val.叫将
      bJiaoJian = True
      '提示在form1.Walk中
   End If
Else
   JianJun = Enum_Walk_Val.未叫将
End If
End Function

'判断将被吃
'参数(X,Y)为将的位置,iQiJu为棋局
'返回值:如果将被吃,返回True
'       否则返回False
Private Function bShuaiBeiChi(X As Integer, Y As Integer, iQiJu() As Integer) As Boolean
Dim I As Integer, bPao As Integer
bPao = 0
For I = 1 To 10 '向上扫描
    If Y - I < 1 Then Exit For '超出边界
    If bPao > 1 Then Exit For
    If iQiJu(X, Y - I) <> Enum_QiZhi.NoZhi Then '有子
       '是对方子时
       If Sgn(iQiJu(X, Y - I)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X, Y - I))
                 Case Enum_QZ.Che '1.被车吃
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.被兵吃
                      If bPao = 0 And Abs(Y - I) = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.被炮吃
                      If bPao = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
          End Select
       End If
       bPao = bPao + 1
    End If
Next I

bPao = 0
For I = 1 To 10 '向下扫描
    If Y + I > 10 Then Exit For '超出边界
    If bPao > 1 Then Exit For
    If iQiJu(X, Y + I) <> Enum_QiZhi.NoZhi Then '有子
       '是对方子时
       If Sgn(iQiJu(X, Y + I)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X, Y + I))
                 Case Enum_QZ.Che '1.被车吃
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.被兵吃
                      If bPao = 0 And I = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.被炮吃
                      If bPao = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
          End Select
       End If
       bPao = bPao + 1
    End If
Next I

bPao = 0
For I = 1 To 9 '向左扫描
    If X - I < 1 Then Exit For '超出边界
    If bPao > 1 Then Exit For
    If iQiJu(X - I, Y) <> Enum_QiZhi.NoZhi Then '有子
       '是对方子时
       If Sgn(iQiJu(X - I, Y)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X - I, Y))
                 Case Enum_QZ.Che '1.被车吃
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.被兵吃
                      If bPao = 0 And Abs(X - I) = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.被炮吃
                      If bPao = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
          End Select
       End If
       bPao = bPao + 1
    End If
Next I

bPao = 0
For I = 1 To 9 '向右扫描
    If X + I > 9 Then Exit For '超出边界
    If bPao > 1 Then Exit For
    If iQiJu(X + I, Y) <> Enum_QiZhi.NoZhi Then '有子
       '是对方子时
       If Sgn(iQiJu(X + I, Y)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X + I, Y))
                 Case Enum_QZ.Che '1.被车吃
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.被兵吃
                      If bPao = 0 And Abs(X - I) = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.被炮吃
                      If bPao = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
          End Select
       End If
       bPao = bPao + 1
    End If
Next I

'4.被马吃
Dim b As Boolean
If Y - 1 > 0 Then
   '当为对方马时
   If X - 2 > 0 Then
   If iQiJu(X - 2, Y - 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
       If bMaWalk(X - 2, Y - 1, X, Y, iQiJu) Then
          bShuaiBeiChi = True
          Exit Function
       End If
   End If
   End If
   '当为对方马时
   If X + 2 < 10 Then
   If iQiJu(X + 2, Y - 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
      If bMaWalk(X + 2, Y - 1, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
If Y - 2 > 0 Then
   '当为对方马时
   If X - 1 > 0 Then
   If iQiJu(X - 1, Y - 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
      If bMaWalk(X - 1, Y - 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
   '当为对方马时
   If X + 1 < 10 Then
   If iQiJu(X + 1, Y - 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
      If bMaWalk(X + 1, Y - 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
If Y + 1 < 11 Then
   '当为对方马时
   If X - 2 > 0 Then
   If iQiJu(X - 2, Y + 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
      If bMaWalk(X - 2, Y + 1, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
   '当为对方马时
   If X + 2 < 10 Then
   If iQiJu(X + 2, Y + 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
      If bMaWalk(X + 2, Y + 1, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
If Y + 2 < 11 Then
   '当为对方马时
   If X - 1 > 0 Then
   If iQiJu(X - 1, Y + 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
      If bMaWalk(X - 1, Y + 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
   '当为对方马时
   If X + 1 < 10 Then
   If iQiJu(X + 1, Y + 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '判断是否能吃
      If bMaWalk(X + 1, Y + 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
bShuaiBeiChi = False
End Function

'判断是否将死
Public Function bQiJuEnd(I As Integer, j As Integer, iQiJu() As Integer) As Boolean
Dim K As Integer, L As Integer, QZ() As Integer
'找出将军的棋,如果将军的棋超过一个,则直接到第3步

'2.判断对方叫将子是否能被吃

'3.如果对方棋子不能被吃,则判断是否能被拦截

'4.如果上两都不成功,则判断将是否能移动
'  a.向上
'  b.向下
'  c.向在
'  d.向右

End Function

'-------------------------------------------------------------------------------------------------------------------
'以下为找出控制点（I，J）棋的子

'以上为找出控制点（I，J）棋的子
'-------------------------------------------------------------------------------------------------------------------

'-------------------------------------------------------------------------------------------------------------------
'以下为棋子的走法，即从点（DI，DJ）到点（I，J）是否能走
'不考虑点(I,J)是否是是自己的子
Public Function bQiZhi_eWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
'1.判各子断能否走
Select Case Abs(iQiJu(Di, Dj))
       Case Enum_QZ.Bing
            bQiZhi_eWalk = bBingWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Che
            bQiZhi_eWalk = bCheWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Ma
            bQiZhi_eWalk = bMaWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Pao
            bQiZhi_eWalk = bPaoWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Shi
            bQiZhi_eWalk = bShiWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Shuai
            bQiZhi_eWalk = bShuaiWalk(Di, Dj, I, j, iQiJu)
            bQiZhi_eWalk = Not bShuaiDuaiMei(Di, Dj, I, j, iQiJu, True)
            GoTo bQiZhi_eWalkLoop
       Case Enum_QZ.Xiang
            bQiZhi_eWalk = bXiangWalk(Di, Dj, I, j, iQiJu)
End Select

If bQiZhi_eWalk Then
   '2.判断将对面
   bQiZhi_eWalk = Not bShuaiDuaiMei(Di, Dj, I, j, iQiJu, , False)
End If
'注意位置不能动位置
bQiZhi_eWalkLoop:
If bQiZhi_eWalk Then
   '3.判断是否将军,包括叫将与被将.
   '  叫将返回Enum_Walk_Val.叫将(真值)
   '  被将返回Enum_Walk_Val.被将(假值)
    bQiZhi_eWalk = JianJun(Di, Dj, I, j, iQiJu, False)
End If

End Function

'兵的走法
Public Function bBingWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If (Di - I) > 1 Or (Dj - j) > 1 Then '不合兵的走法
   bBingWalk = False
Else '符合兵的走法
   Select Case iQiJu(Di, Dj)
          Case Is = Enum_QiZhi.jBing '甲方
               If j < Dj Then '往后走
                  bBingWalk = False
               ElseIf (Dj <= 5 And Di = I And j - Dj = 1) Then '未过河
                     bBingWalk = True
               ElseIf (Dj > 5 And (Abs(Di - I) = 1 Or _
                   Abs(Dj - j) = 1) And Abs(Di - I) <> Abs(Dj - j)) Then
                   '已过河
                   bBingWalk = True
               Else
                   bBingWalk = False
               End If
          Case Is = Enum_QiZhi.yBing '乙方
               If j > Dj Then '往后走
                  bBingWalk = False
               ElseIf (Dj > 5 And Di = I And Dj - j = 1) Then '未过河
                   bBingWalk = True
               ElseIf (Dj <= 5 And (Abs(Di - I) = 1 Or _
                   Abs(Dj - j) = 1) And Abs(Di - I) <> Abs(Dj - j)) Then
                   '已过河
                   bBingWalk = True
               Else
                   bBingWalk = False
               End If
   End Select
End If
End Function

'炮的走法
Public Function bPaoWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
Dim K As Long, FlagPao As Long
FlagPao = 0
If Di <> I And Dj <> j Then ' 不在一条线时
   bPaoWalk = False: Exit Function
Else
   If Di <> I Then
      For K = 1 To Abs(Di - I) - 1
          If iQiJu(Di + Sgn(I - Di) * K, Dj) <> Enum_QiZhi.NoZhi Then
             FlagPao = FlagPao + 1
          End If
          If FlagPao > 1 Then '中间有两子以上时
             bPaoWalk = False
             Exit Function
          End If
      Next K
      '中间有子且（I,J）处无子
      If FlagPao = 1 And iQiJu(I, j) = Enum_QiZhi.NoZhi Then
         bPaoWalk = False
         Exit Function
      End If
      '中间有子且（I,J）处有子
      If FlagPao = 1 And iQiJu(I, j) <> Enum_QiZhi.NoZhi Then
         bPaoWalk = True
         Exit Function
      End If
      '中间无子且（I,J）处无子
      If FlagPao = 0 And iQiJu(I, j) = Enum_QiZhi.NoZhi Then
         bPaoWalk = True
         Exit Function
      End If
    End If
    If j <> Dj Then
       For K = 1 To Abs(Dj - j) - 1
           If iQiJu(Di, Dj + K * Sgn(j - Dj)) <> Enum_QiZhi.NoZhi Then
             FlagPao = FlagPao + 1
           End If
           If FlagPao > 1 Then
             bPaoWalk = False
             Exit Function
           End If
      Next K
      '中间有子且（I,J）处无子
      If FlagPao = 1 And iQiJu(I, j) = Enum_QiZhi.NoZhi Then
         bPaoWalk = False
         Exit Function
      End If
      '中间有子且（I,J）处有子
      If FlagPao = 1 And iQiJu(I, j) <> Enum_QiZhi.NoZhi Then
         bPaoWalk = True
         Exit Function
      End If
      '中间无子且（I,J）处无子
      If FlagPao = 0 And iQiJu(I, j) = Enum_QiZhi.NoZhi Then
         bPaoWalk = True
         Exit Function
      End If
    End If
End If
bPaoWalk = False
End Function

'车的走法
Public Function bCheWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
Dim K As Integer
If Di <> I And Dj <> j Then '如果不在一条直线上
   bCheWalk = False
   Exit Function
Else
  If Di <> I Then '在同一条竖线上
     For K = 1 To Abs(I - Di) - 1 '确定中则没有棋
         If iQiJu(Di + Sgn(I - Di) * K, Dj) <> Enum_QiZhi.NoZhi Then
            bCheWalk = False
            Exit Function
         End If
     Next K
  End If
        
  If j <> Dj Then '在同一水平线上
     For K = 1 To Abs(j - Dj) - 1 '确定中间没有棋
         If iQiJu(Di, Sgn(j - Dj) * K + Dj) <> Enum_QiZhi.NoZhi Then
            bCheWalk = False
            Exit Function
         End If
     Next K
  End If
  bCheWalk = True
End If
End Function

'马的走法
Public Function bMaWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If Abs(Di - I) = 2 And Abs(Dj - j) = 1 Then
   If iQiJu((Di + I) / 2, Dj) = Enum_QiZhi.NoZhi Then    '马拐脚
           bMaWalk = True: Exit Function
   End If
End If
If Abs(Di - I) = 1 And Abs(Dj - j) = 2 Then
   If iQiJu(Di, (Dj + j) / 2) = Enum_QiZhi.NoZhi Then  '马拐脚
      bMaWalk = True: Exit Function
   End If
End If
bMaWalk = False
End Function

'相的走法
Public Function bXiangWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
'象走田
If Not ((Abs(Di - I) = 2 And Abs(Dj - j) = 2)) Then
   bXiangWalk = False
   Exit Function
End If
If iQiJu((Di + I) / 2, (Dj + j) / 2) <> Enum_QiZhi.NoZhi Then '象心有子
   bXiangWalk = False
   Exit Function
End If
Select Case iQiJu(Di, Dj)
       Case Is = Enum_QiZhi.jXiang
            If Not ((j = 1 And (I = 3 Or I = 7)) Or _
                    (j = 3 And (I = 1 Or I = 5 Or I = 9)) Or _
                    (j = 5 And (I = 3 Or I = 7))) Then
                    bXiangWalk = False
                    Exit Function
            'ElseIf Sgn(iQiJu(I, J)) = Sgn(Enum_QiZhi.jXiang) Then
                    '是一方的子
            '        bXiangWalk = False
            '        Exit Function
            End If
       Case Is = Enum_QiZhi.yXiang
            If Not ((j = 10 And (I = 3 Or I = 7)) Or _
                    (j = 8 And (I = 1 Or I = 5 Or I = 9)) Or _
                    (j = 6 And (I = 3 Or I = 7))) Then
                    bXiangWalk = False
                    Exit Function
            'ElseIf Sgn(iQiJu(I, J)) = Sgn(Enum_QiZhi.yXiang) Then
                    '是一方的子
            '        bXiangWalk = False
            '        Exit Function
            End If
End Select
bXiangWalk = True
End Function

'士的走法
Public Function bShiWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If I < 4 Or I > 6 Then '不在田字内
   bShiWalk = False
ElseIf Abs(I - Di) = 1 And Abs(j - Dj) = 1 Then '满足走斜线
    Select Case iQiJu(Di, Dj)
           Case Is = Enum_QiZhi.jShi
                If j <= 3 Then ' And Sgn(iQiJu(I, J)) _
                  <> Sgn(Enum_QiZhi.jShi) Then '确定在田字内
                   bShiWalk = True
                Else
                   bShiWalk = False
                End If
           Case Is = Enum_QiZhi.yShi
                If j >= 8 Then ' And Sgn(iQiJu(I, J)) _
                  <> Sgn(Enum_QiZhi.yShi) Then  '确定在田字内
                   bShiWalk = True
                Else
                   bShiWalk = False
                End If
   End Select
Else
   bShiWalk = False
End If
End Function

'将的走法
Public Function bShuaiWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If I < 4 Or I > 6 Then '不在田字内
   bShuaiWalk = False
ElseIf (Abs(I - Di) = 1 And Abs(j - Dj) = 0) _
    Or (Abs(I - Di) = 0 And Abs(j - Dj) = 1) Then '满足走棋条件
    Select Case iQiJu(Di, Dj)
           Case Is = Enum_QiZhi.jShuai
                If j <= 3 Then ' And Sgn(iQiJu(I, J)) _
                <> Sgn(Enum_QiZhi.jShuai) Then  '确定在田字内
                   bShuaiWalk = True
                Else
                   bShuaiWalk = False
                End If
           Case Is = Enum_QiZhi.yShuai
                If j >= 8 Then ' And Sgn(iQiJu(I, J)) _
                <> Sgn(Enum_QiZhi.yShuai) Then   '确定在田字内
                   bShuaiWalk = True
                Else
                   bShuaiWalk = False
                End If
   End Select
Else
   bShuaiWalk = False
End If
End Function

'判断将是否对面
'（Di，Dj）表示要判断的点，Flag=True表示从将走时的判断,
'Show表示是否显示提示True时显示提示
Public Function bShuaiDuaiMei(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer, Optional Flag As Boolean = False, Optional Show As Boolean = True) As Boolean
Dim K As Long
If Di < 4 Or Di > 6 Or (Di = I And Not Flag) Then  '不在田字上,和在Y上走
   bShuaiDuaiMei = False: Exit Function
End If
If Flag Then '从将走时的判断
   Select Case iQiJu(Di, Dj)
          Case Is = Enum_QiZhi.jShuai
               '移开的位置
               For K = 1 To 9 '向下扫描找将
                   If Dj + K = j Then K = K + 1 '自己走动后的位置
                   '超过边界,则说明将不在此线上,则退出,并返回False
                   If Dj + K > 10 Then Exit For
                   '如果有子,且此子不为将,则说明中间有子,则退出,并返回False
                   If iQiJu(Di, Dj + K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(Di, Dj + K)) <> Enum_QZ.Shuai Then
                      Exit For
                   End If
                   If Abs(iQiJu(Di, Dj + K)) = Enum_QZ.Shuai Then
                      '找到将,则跳出此循环,并向上扫描找将
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s帅将对面, vbCritical
                      Exit Function
                   End If
               Next K
               If Dj <> j Then
                  bShuaiDuaiMei = False
                  Exit Function
               End If
               '要走的位置
               For K = 1 To 9 '向下扫描找将
                   '超过边界,则说明将不在此线上,则退出,并返回False
                   If j + K > 10 Then bShuaiDuaiMei = False: Exit Function
                   '如果有子,且此子不为将,则说明中间有子,则退出,并返回False
                   If iQiJu(I, j + K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(I, j + K)) <> Enum_QZ.Shuai Then
                      bShuaiDuaiMei = False: Exit Function
                   End If
                   If Abs(iQiJu(I, j + K)) = Enum_QZ.Shuai Then
                      '找到将,则跳出此循环,并向上扫描找将
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s帅将对面, vbCritical
                      Exit Function
                   End If
               Next K
          Case Is = Enum_QiZhi.yShuai
               '移开的位置
               For K = 1 To 9 '向上扫描找将
                   If Dj - K = j Then K = K + 1 '自己走动后的位置
                   '超过边界,则说明将不在此线上,则退出,并返回False
                   If Dj - K < 1 Then Exit For
                   '如果有子,且此子不为将,则说明中间有子,则退出,并返回False
                   If iQiJu(Di, Dj - K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(Di, Dj - K)) <> Enum_QZ.Shuai Then
                      Exit For
                   End If
                   If Abs(iQiJu(Di, Dj - K)) = Enum_QZ.Shuai Then
                      '找到将,则将对面
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s帅将对面, vbCritical
                      Exit Function
                   End If
               Next K
               If Dj <> j Then
                  bShuaiDuaiMei = False
                  Exit Function
               End If
               '要走的位置
               For K = 1 To 9 '向上扫描找将
                   '超过边界,则说明将不在此线上,则退出,并返回False
                   If j - K < 1 Then bShuaiDuaiMei = False: Exit Function
                   '如果有子,且此子不为将,则说明中间有子,则退出,并返回False
                   If iQiJu(I, j - K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(I, j - K)) <> Enum_QZ.Shuai Then
                      bShuaiDuaiMei = False: Exit Function
                   End If
                   If Abs(iQiJu(I, j - K)) = Enum_QZ.Shuai Then
                      '找到将,则将对面
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s帅将对面, vbCritical
                      Exit Function
                   End If
               Next K
   End Select
Else '不是从将走时的判断
     For K = 1 To 9 '向下扫描找将
         '超过边界,则说明将不在此线上,则退出,并返回False
         If Dj + K > 10 Then bShuaiDuaiMei = False: Exit Function
         '如果有子,且此子不为将,则说明中间有子,则退出,并返回False
         If iQiJu(Di, Dj + K) <> Enum_QiZhi.NoZhi _
            And Abs(iQiJu(Di, Dj + K)) <> Enum_QZ.Shuai Then
              bShuaiDuaiMei = False: Exit Function
         End If
         If Abs(iQiJu(Di, Dj + K)) = Enum_QZ.Shuai Then
            '找到将,则跳出此循环,并向上扫描找将
             Exit For
         End If
     Next K
     For K = 1 To 9 '向上扫描找将
         '超过边界,则说明将不在此线上,则退出,并返回False
         If Dj - K < 1 Then bShuaiDuaiMei = False: Exit Function
         '如果有子,且此子不为将,则说明中间有子,则退出,并返回False
         If iQiJu(Di, Dj - K) <> Enum_QiZhi.NoZhi _
            And Abs(iQiJu(Di, Dj - K)) <> Enum_QZ.Shuai Then
            bShuaiDuaiMei = False: Exit Function
         End If
         If Abs(iQiJu(Di, Dj - K)) = Enum_QZ.Shuai Then
            '找到将,则将对面
            bShuaiDuaiMei = True
            If Show Then MsgBox s帅将对面, vbCritical
            Exit Function
         End If
     Next K
End If
End Function

'以上为棋子的走法，即从点（DI，DJ）到点（I，J）是否能走
'不考虑点(I,J)是否是对方的子
'----------------------------------------------------------------------------------------

'----------------------------------------------------------------------------------------
'布局时棋子是否符合走法
Public Function bBuJu_eWalk_fa(I As Integer, j As Integer, Source As Object) As Boolean
Dim X As Single, Y As Single, Di As Integer, Dj As Integer
Select Case Sgn(Source.Tag) * (Abs(Source.Tag) Mod 10)
       Case Enum_QiZhi.jBing
            If j < 4 Or ((j = 5 Or j = 4) And _
             (I Mod 2 = 0)) Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
             '未过河时，两兵不能在一条坚线上相邻
            If j = 5 Or j = 4 Then '未过河时，两兵不能在一条竖线上相邻
               If Abs(Source.Tag) \ 10 Mod 10 = 0 Then '在棋盘上移动时
                  '是移动自己时
                  Form1.ZhouBiao_eTranslate Source.Left, Source.Top, Di, Dj
                  If Di = I Then
                     GoTo bBuJu_eWalk_Fa_Loop
                  End If
               End If
               '从别的竖线上或从棋盘外移入
               If j = 5 Then
                  j = 4
               Else
                  j = 5
               End If
               Form1.ZhouBiao_eTranslate X, Y, I, j, 把棋局座标转换为棋盘上的座标
               If Form1.QiJu_eArrary(X, Y) = Enum_QiZhi.jBing Then
                  bBuJu_eWalk_fa = False
                  MsgBox s兵不符合棋子走法, vbCritical
                  Exit Function
               End If
            End If
       Case Enum_QiZhi.yBing
            If j > 7 Or ((j = 6 Or j = 7) And _
             (I Mod 2 = 0)) Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
             '未过河时，两兵不能在一条坚线上相邻
            If j = 6 Or j = 7 Then '未过河时，两兵不能在一条坚线上相邻
               If Abs(Source.Tag) \ 10 Mod 10 = 0 Then '在棋盘上移动时
                  '是移动自己时
                  Form1.ZhouBiao_eTranslate Source.Left, Source.Top, Di, Dj
                  If Di = I Then
                     GoTo bBuJu_eWalk_Fa_Loop
                  End If
               End If
               '从别的竖线上或从棋盘外移入
               If j = 6 Then
                  j = 7
               Else
                  j = 6
               End If
               Form1.ZhouBiao_eTranslate X, Y, I, j, 把棋局座标转换为棋盘上的座标
               If Form1.QiJu_eArrary(X, Y) = Enum_QiZhi.yBing Then
                  bBuJu_eWalk_fa = False
                  MsgBox s兵不符合棋子走法, vbCritical
                  Exit Function
               End If
            End If
       Case Enum_QiZhi.jXiang
            If Not ((j = 1 And (I = 3 Or I = 7)) Or _
                    (j = 3 And (I = 1 Or I = 5 Or I = 9)) Or _
                    (j = 5 And (I = 3 Or I = 7))) Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.yXiang
            If Not ((j = 10 And (I = 3 Or I = 7)) Or _
                    (j = 8 And (I = 1 Or I = 5 Or I = 9)) Or _
                    (j = 6 And (I = 3 Or I = 7))) Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.jShi
            If Not ((I = 4 And (j = 1 Or j = 3)) Or _
                   (I = 5 And j = 2) Or _
                   (I = 6 And (j = 1 Or j = 3))) Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.yShi
            If Not ((I = 4 And (j = 10 Or j = 8)) Or _
                   (I = 5 And j = 9) Or _
                   (I = 6 And (j = 10 Or j = 8))) Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.jShuai
            If I < 4 Or I > 6 Or j > 3 Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.yShuai
            If I < 4 Or I > 6 Or j < 8 Then
               bBuJu_eWalk_fa = False
               MsgBox s不符合棋子走法, vbCritical
               Exit Function
            End If
End Select
bBuJu_eWalk_Fa_Loop:
bBuJu_eWalk_fa = True
End Function

'------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
'棋局编码和解码
'参数：(I,J)是棋局上的位置,QiZhi在编码时是棋子的代码,在解码时是要进行解码的代码
'返回值:当是编码时,是编好的代码
'       当是解码时,是棋子的代码
Public Function QiJuBianMa(I As Integer, j As Integer, Optional QiZhi As Integer = Enum_QiZhi.NoZhi, Optional Flag As Enum_QiJuBianMa_Flag = Enum_QiJuBianMa_Flag.进行编码) As Integer
Select Case Flag
       Case 进行编码
            If QiZhi = Enum_QiZhi.NoZhi Then
               QiJuBianMa = j + I * 100
            Else
               QiJuBianMa = Sgn(QiZhi) * (j + I * 100 + Abs(QiZhi * 1000))
            End If
       Case 进行解码
            I = Abs(QiZhi) \ 100 Mod 10
            j = Abs(QiZhi) Mod 100
            QiJuBianMa = QiZhi \ 1000
End Select
End Function

'把棋子代码翻译成棋子
Public Function Read_QiZhi(QiZhi As Integer) As String
Select Case QiZhi
       Case Enum_QiZhi.NoZhi
            Read_QiZhi = "无棋"
       Case Enum_QiZhi.jChe
            Read_QiZhi = "甲车"
       Case Enum_QiZhi.jBing
            Read_QiZhi = "甲兵"
       Case Enum_QiZhi.jMa
            Read_QiZhi = "甲马"
       Case Enum_QiZhi.jPao
            Read_QiZhi = "甲炮"
       Case Enum_QiZhi.jShi
            Read_QiZhi = "甲仕"
       Case Enum_QiZhi.jShuai
            Read_QiZhi = "甲帅"
       Case Enum_QiZhi.jXiang
            Read_QiZhi = "甲相"
       Case Enum_QiZhi.yBing
            Read_QiZhi = "乙卒"
       Case Enum_QiZhi.yChe
            Read_QiZhi = "乙车"
       Case Enum_QiZhi.yMa
            Read_QiZhi = "乙马"
       Case Enum_QiZhi.yPao
            Read_QiZhi = "乙炮"
       Case Enum_QiZhi.yShi
            Read_QiZhi = "乙士"
       Case Enum_QiZhi.yShuai
            Read_QiZhi = "乙将"
       Case Enum_QiZhi.yXiang
            Read_QiZhi = "乙象"
End Select
End Function

'----------------------------------------------------------------------------------------------------------------------------
'把形势值翻译成文字
Public Function Read_Controled(XinShi As Integer) As String
Select Case XinShi
       Case 0
            Read_Controled = "无"
       Case Is > 0
            Read_Controled = "被甲方"
       Case Is < 0
            Read_Controled = "被乙方"
End Select
End Function

'形势分析
Public Function XinShiFenXi(iQiJu() As Integer, XinShiBiao() As Type_XinShiFenXiBiao, jFQi() As Integer, yFQi() As Integer)
Dim I As Integer, j As Integer, K As Long, Di As Integer, Dj As Integer

'1.扫描棋盘上的棋子,并记录棋子
ReDim jFQi(0): ReDim yFQi(0)
For j = 1 To 10
    For I = 1 To 9
        If iQiJu(I, j) <> Enum_QiZhi.NoZhi Then
           If Sgn(iQiJu(I, j)) = Sgn(Enum_QZ.jFan) Then
              ReDim Preserve jFQi(UBound(jFQi) + 1)
              jFQi(UBound(jFQi)) = QiJuBianMa(I, j, iQiJu(I, j))
           Else
              ReDim Preserve yFQi(UBound(yFQi) + 1)
              yFQi(UBound(yFQi)) = QiJuBianMa(I, j, iQiJu(I, j))
           End If
        End If
    Next I
Next j
'2.确定各棋子之间的关系,并记录各棋子的被哪方控制,
'并计算出代数值.
'并加上相应的权值,计算出是否能够攻击或保护
For I = 1 To 9
    For j = 1 To 10
        With XinShiBiao(I, j)
                K = 1
                ReDim .jF_eControl(0)
                While (K <= UBound(jFQi)) '扫描被甲方控制情况
                      Call QiJuBianMa(Di, Dj, jFQi(K), 进行解码)
                      If bQiZhi_eWalk(Di, Dj, I, j, iQiJu) Then
                         ReDim Preserve .jF_eControl _
                           (UBound(.jF_eControl) + 1)
                         .jF_eControl(UBound(.jF_eControl)) = jFQi(K)
                      End If
                      K = K + 1
                Wend
                K = 1
                ReDim .yF_eControl(0)
                While (K <= UBound(jFQi)) '扫描被乙方控制情况
                      Call QiJuBianMa(Di, Dj, yFQi(K), 进行解码)
                      If bQiZhi_eWalk(Di, Dj, I, j, iQiJu) Then
                         ReDim Preserve .yF_eControl _
                            (UBound(.yF_eControl) + 1)
                         .yF_eControl(UBound(.yF_eControl)) = yFQi(K)
                      End If
                      K = K + 1
                Wend
                .XinShi = UBound(.jF_eControl) - UBound(.yF_eControl)
        End With
    Next j
Next I
'3.统计棋盘上各位置的被甲方子或被乙方子控制,并计算代数和,以确定
'被哪方控制

End Function
