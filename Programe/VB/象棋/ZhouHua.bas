Attribute VB_Name = "ZouFai"
Option Explicit

Public Const s������ = "������:"
Public Const s������ = "������:"
Const s���� = "����,�����¿�ʼ�����ǽ���������ء��¿�ʼ�밴�ǣ�Y�������򣬰���N��"
Const s������ = "������"
Const s˧������ = "'˧'��'��'����"
Const s�����������߷� = "�Ƿ�λ��"
Const s�������������߷� = "�����������߷�"

Public Const s�н� = "�н�"
Private Enum Enum_Walk_Val
        ���� = False
        δ�н� = 1
        �н� = 2
End Enum

Public Enum Enum_QiJuBianMa_Flag
       ���б���
       ���н���
End Enum

Public Type Type_XinShiFenXiBiao
       XinShi As Integer '����ֵ,����0Ϊ���׷�����
                         'С��0Ϊ���ҷ�����
       jF_eControl() As Integer '�׷����ƴ�λ�õ���
       yF_eControl() As Integer '�ҷ����ƴ�λ�õ���
       End Type
'Public tXinShiFenXiBiao(9, 10) As Type_XinShiFenXiBiao

Public bJiaoJian As Boolean '�Ƿ���ʾ�н�

'�ж��ǽн����Ǳ���
'��������0,�н�����1,��������Է���
Public Function JianJun(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer, Optional Show As Boolean = True) As Boolean
Dim K As Integer, L As Integer, X As Integer, Y As Integer
Dim fQJ(9, 10) As Integer, exi As Integer
'1.��һ���������,����ʼ��
For K = 0 To 9
    For L = 0 To 10
        fQJ(K, L) = iQiJu(K, L)
    Next L
Next K
fQJ(I, j) = fQJ(Di, Dj) '����
fQJ(Di, Dj) = 0
'2.�ҵ��߷��Ľ�
For K = 1 To 9
    For L = 1 To 10
        If fQJ(K, L) = Sgn(iQiJu(Di, Dj)) * Enum_QZ.Shuai Then
           X = K: Y = L '����λ��
           Exit For
        End If
    Next L
Next K
'3.�ж��Ƿ񱻳�,
'����Ǳ���,�򷵻�Enum_Walk_Val.����,
'����ʾ�������˳�,���������4.��
If bShuaiBeiChi(X, Y, fQJ) Then
   JianJun = Enum_Walk_Val.����
   If Show Then MsgBox s������, vbCritical
   Exit Function
End If
'4.�ҵ�δ�߷�˧,����Ҳ���,�����������unload form1
For K = 1 To 9
    For L = 1 To 10
        If fQJ(K, L) = -Sgn(iQiJu(Di, Dj)) * Enum_QZ.Shuai Then
           X = K: Y = L '����λ��
           Exit For
        End If
    Next L
Next K
'����Ҳ���,�����������unload form1
If K > 10 And L > 11 Then
   If Show Then
      If Sgn(iQiJu(Di, Dj)) = Sgn(Enum_QiZhi.jShuai) Then
         exi = MsgBox(Form1.LabYF.Caption & s����, vbQuestion + vbYesNo)
      Else
         exi = MsgBox(Form1.LabJF.Caption & s����, vbQuestion + vbYesNo)
      End If
      If exi = vbYes Then
         Form1.mnuFileReStart_Click
         Exit Function
      Else
         Unload Form1
      End If
    End If
End If
'5.�ж��Ƿ񱻽г�,
'������򷵻�Enum_Walk_Val.�г�
'���򷵻�Enum_Walk_Val.δ�н�
If bShuaiBeiChi(X, Y, fQJ) Then
   If bQiJuEnd(X, Y, fQJ) Then '�ж��Ƿ���
      If Show Then
         If Sgn(iQiJu(Di, Dj)) = Sgn(Enum_QiZhi.jShuai) Then
            exi = MsgBox(Form1.LabYF.Caption & s����, vbQuestion + vbYesNo)
         Else
            exi = MsgBox(Form1.LabJF.Caption & s����, vbQuestion + vbYesNo)
         End If
         If exi = vbYes Then
            Form1.mnuFileReStart_Click
            Exit Function
         Else
            Unload Form1
         End If
      End If
   Else
      JianJun = Enum_Walk_Val.�н�
      bJiaoJian = True
      '��ʾ��form1.Walk��
   End If
Else
   JianJun = Enum_Walk_Val.δ�н�
End If
End Function

'�жϽ�����
'����(X,Y)Ϊ����λ��,iQiJuΪ���
'����ֵ:���������,����True
'       ���򷵻�False
Private Function bShuaiBeiChi(X As Integer, Y As Integer, iQiJu() As Integer) As Boolean
Dim I As Integer, bPao As Integer
bPao = 0
For I = 1 To 10 '����ɨ��
    If Y - I < 1 Then Exit For '�����߽�
    If bPao > 1 Then Exit For
    If iQiJu(X, Y - I) <> Enum_QiZhi.NoZhi Then '����
       '�ǶԷ���ʱ
       If Sgn(iQiJu(X, Y - I)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X, Y - I))
                 Case Enum_QZ.Che '1.������
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.������
                      If bPao = 0 And Abs(Y - I) = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.���ڳ�
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
For I = 1 To 10 '����ɨ��
    If Y + I > 10 Then Exit For '�����߽�
    If bPao > 1 Then Exit For
    If iQiJu(X, Y + I) <> Enum_QiZhi.NoZhi Then '����
       '�ǶԷ���ʱ
       If Sgn(iQiJu(X, Y + I)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X, Y + I))
                 Case Enum_QZ.Che '1.������
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.������
                      If bPao = 0 And I = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.���ڳ�
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
For I = 1 To 9 '����ɨ��
    If X - I < 1 Then Exit For '�����߽�
    If bPao > 1 Then Exit For
    If iQiJu(X - I, Y) <> Enum_QiZhi.NoZhi Then '����
       '�ǶԷ���ʱ
       If Sgn(iQiJu(X - I, Y)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X - I, Y))
                 Case Enum_QZ.Che '1.������
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.������
                      If bPao = 0 And Abs(X - I) = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.���ڳ�
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
For I = 1 To 9 '����ɨ��
    If X + I > 9 Then Exit For '�����߽�
    If bPao > 1 Then Exit For
    If iQiJu(X + I, Y) <> Enum_QiZhi.NoZhi Then '����
       '�ǶԷ���ʱ
       If Sgn(iQiJu(X + I, Y)) <> Sgn(iQiJu(X, Y)) Then
          Select Case Abs(iQiJu(X + I, Y))
                 Case Enum_QZ.Che '1.������
                      If bPao = 0 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Bing '3.������
                      If bPao = 0 And Abs(X - I) = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
                 Case Enum_QZ.Pao '2.���ڳ�
                      If bPao = 1 Then
                         bShuaiBeiChi = True
                         Exit Function
                      End If
          End Select
       End If
       bPao = bPao + 1
    End If
Next I

'4.�����
Dim b As Boolean
If Y - 1 > 0 Then
   '��Ϊ�Է���ʱ
   If X - 2 > 0 Then
   If iQiJu(X - 2, Y - 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
       If bMaWalk(X - 2, Y - 1, X, Y, iQiJu) Then
          bShuaiBeiChi = True
          Exit Function
       End If
   End If
   End If
   '��Ϊ�Է���ʱ
   If X + 2 < 10 Then
   If iQiJu(X + 2, Y - 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
      If bMaWalk(X + 2, Y - 1, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
If Y - 2 > 0 Then
   '��Ϊ�Է���ʱ
   If X - 1 > 0 Then
   If iQiJu(X - 1, Y - 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
      If bMaWalk(X - 1, Y - 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
   '��Ϊ�Է���ʱ
   If X + 1 < 10 Then
   If iQiJu(X + 1, Y - 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
      If bMaWalk(X + 1, Y - 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
If Y + 1 < 11 Then
   '��Ϊ�Է���ʱ
   If X - 2 > 0 Then
   If iQiJu(X - 2, Y + 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
      If bMaWalk(X - 2, Y + 1, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
   '��Ϊ�Է���ʱ
   If X + 2 < 10 Then
   If iQiJu(X + 2, Y + 1) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
      If bMaWalk(X + 2, Y + 1, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
If Y + 2 < 11 Then
   '��Ϊ�Է���ʱ
   If X - 1 > 0 Then
   If iQiJu(X - 1, Y + 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
      If bMaWalk(X - 1, Y + 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
   '��Ϊ�Է���ʱ
   If X + 1 < 10 Then
   If iQiJu(X + 1, Y + 2) = -Sgn(iQiJu(X, Y)) * Enum_QZ.Ma Then
      '�ж��Ƿ��ܳ�
      If bMaWalk(X + 1, Y + 2, X, Y, iQiJu) Then
         bShuaiBeiChi = True
         Exit Function
      End If
   End If
   End If
End If
bShuaiBeiChi = False
End Function

'�ж��Ƿ���
Public Function bQiJuEnd(I As Integer, j As Integer, iQiJu() As Integer) As Boolean
Dim K As Integer, L As Integer, QZ() As Integer
'�ҳ���������,����������峬��һ��,��ֱ�ӵ���3��

'2.�ж϶Է��н����Ƿ��ܱ���

'3.����Է����Ӳ��ܱ���,���ж��Ƿ��ܱ�����

'4.������������ɹ�,���жϽ��Ƿ����ƶ�
'  a.����
'  b.����
'  c.����
'  d.����

End Function

'-------------------------------------------------------------------------------------------------------------------
'����Ϊ�ҳ����Ƶ㣨I��J�������

'����Ϊ�ҳ����Ƶ㣨I��J�������
'-------------------------------------------------------------------------------------------------------------------

'-------------------------------------------------------------------------------------------------------------------
'����Ϊ���ӵ��߷������ӵ㣨DI��DJ�����㣨I��J���Ƿ�����
'�����ǵ�(I,J)�Ƿ������Լ�����
Public Function bQiZhi_eWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
'1.�и��Ӷ��ܷ���
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
   '2.�жϽ�����
   bQiZhi_eWalk = Not bShuaiDuaiMei(Di, Dj, I, j, iQiJu, , False)
End If
'ע��λ�ò��ܶ�λ��
bQiZhi_eWalkLoop:
If bQiZhi_eWalk Then
   '3.�ж��Ƿ񽫾�,�����н��뱻��.
   '  �н�����Enum_Walk_Val.�н�(��ֵ)
   '  ��������Enum_Walk_Val.����(��ֵ)
    bQiZhi_eWalk = JianJun(Di, Dj, I, j, iQiJu, False)
End If

End Function

'�����߷�
Public Function bBingWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If (Di - I) > 1 Or (Dj - j) > 1 Then '���ϱ����߷�
   bBingWalk = False
Else '���ϱ����߷�
   Select Case iQiJu(Di, Dj)
          Case Is = Enum_QiZhi.jBing '�׷�
               If j < Dj Then '������
                  bBingWalk = False
               ElseIf (Dj <= 5 And Di = I And j - Dj = 1) Then 'δ����
                     bBingWalk = True
               ElseIf (Dj > 5 And (Abs(Di - I) = 1 Or _
                   Abs(Dj - j) = 1) And Abs(Di - I) <> Abs(Dj - j)) Then
                   '�ѹ���
                   bBingWalk = True
               Else
                   bBingWalk = False
               End If
          Case Is = Enum_QiZhi.yBing '�ҷ�
               If j > Dj Then '������
                  bBingWalk = False
               ElseIf (Dj > 5 And Di = I And Dj - j = 1) Then 'δ����
                   bBingWalk = True
               ElseIf (Dj <= 5 And (Abs(Di - I) = 1 Or _
                   Abs(Dj - j) = 1) And Abs(Di - I) <> Abs(Dj - j)) Then
                   '�ѹ���
                   bBingWalk = True
               Else
                   bBingWalk = False
               End If
   End Select
End If
End Function

'�ڵ��߷�
Public Function bPaoWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
Dim K As Long, FlagPao As Long
FlagPao = 0
If Di <> I And Dj <> j Then ' ����һ����ʱ
   bPaoWalk = False: Exit Function
Else
   If Di <> I Then
      For K = 1 To Abs(Di - I) - 1
          If iQiJu(Di + Sgn(I - Di) * K, Dj) <> Enum_QiZhi.NoZhi Then
             FlagPao = FlagPao + 1
          End If
          If FlagPao > 1 Then '�м�����������ʱ
             bPaoWalk = False
             Exit Function
          End If
      Next K
      '�м������ң�I,J��������
      If FlagPao = 1 And iQiJu(I, j) = Enum_QiZhi.NoZhi Then
         bPaoWalk = False
         Exit Function
      End If
      '�м������ң�I,J��������
      If FlagPao = 1 And iQiJu(I, j) <> Enum_QiZhi.NoZhi Then
         bPaoWalk = True
         Exit Function
      End If
      '�м������ң�I,J��������
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
      '�м������ң�I,J��������
      If FlagPao = 1 And iQiJu(I, j) = Enum_QiZhi.NoZhi Then
         bPaoWalk = False
         Exit Function
      End If
      '�м������ң�I,J��������
      If FlagPao = 1 And iQiJu(I, j) <> Enum_QiZhi.NoZhi Then
         bPaoWalk = True
         Exit Function
      End If
      '�м������ң�I,J��������
      If FlagPao = 0 And iQiJu(I, j) = Enum_QiZhi.NoZhi Then
         bPaoWalk = True
         Exit Function
      End If
    End If
End If
bPaoWalk = False
End Function

'�����߷�
Public Function bCheWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
Dim K As Integer
If Di <> I And Dj <> j Then '�������һ��ֱ����
   bCheWalk = False
   Exit Function
Else
  If Di <> I Then '��ͬһ��������
     For K = 1 To Abs(I - Di) - 1 'ȷ������û����
         If iQiJu(Di + Sgn(I - Di) * K, Dj) <> Enum_QiZhi.NoZhi Then
            bCheWalk = False
            Exit Function
         End If
     Next K
  End If
        
  If j <> Dj Then '��ͬһˮƽ����
     For K = 1 To Abs(j - Dj) - 1 'ȷ���м�û����
         If iQiJu(Di, Sgn(j - Dj) * K + Dj) <> Enum_QiZhi.NoZhi Then
            bCheWalk = False
            Exit Function
         End If
     Next K
  End If
  bCheWalk = True
End If
End Function

'����߷�
Public Function bMaWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If Abs(Di - I) = 2 And Abs(Dj - j) = 1 Then
   If iQiJu((Di + I) / 2, Dj) = Enum_QiZhi.NoZhi Then    '��ս�
           bMaWalk = True: Exit Function
   End If
End If
If Abs(Di - I) = 1 And Abs(Dj - j) = 2 Then
   If iQiJu(Di, (Dj + j) / 2) = Enum_QiZhi.NoZhi Then  '��ս�
      bMaWalk = True: Exit Function
   End If
End If
bMaWalk = False
End Function

'����߷�
Public Function bXiangWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
'������
If Not ((Abs(Di - I) = 2 And Abs(Dj - j) = 2)) Then
   bXiangWalk = False
   Exit Function
End If
If iQiJu((Di + I) / 2, (Dj + j) / 2) <> Enum_QiZhi.NoZhi Then '��������
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
                    '��һ������
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
                    '��һ������
            '        bXiangWalk = False
            '        Exit Function
            End If
End Select
bXiangWalk = True
End Function

'ʿ���߷�
Public Function bShiWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If I < 4 Or I > 6 Then '����������
   bShiWalk = False
ElseIf Abs(I - Di) = 1 And Abs(j - Dj) = 1 Then '������б��
    Select Case iQiJu(Di, Dj)
           Case Is = Enum_QiZhi.jShi
                If j <= 3 Then ' And Sgn(iQiJu(I, J)) _
                  <> Sgn(Enum_QiZhi.jShi) Then 'ȷ����������
                   bShiWalk = True
                Else
                   bShiWalk = False
                End If
           Case Is = Enum_QiZhi.yShi
                If j >= 8 Then ' And Sgn(iQiJu(I, J)) _
                  <> Sgn(Enum_QiZhi.yShi) Then  'ȷ����������
                   bShiWalk = True
                Else
                   bShiWalk = False
                End If
   End Select
Else
   bShiWalk = False
End If
End Function

'�����߷�
Public Function bShuaiWalk(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer) As Boolean
If I < 4 Or I > 6 Then '����������
   bShuaiWalk = False
ElseIf (Abs(I - Di) = 1 And Abs(j - Dj) = 0) _
    Or (Abs(I - Di) = 0 And Abs(j - Dj) = 1) Then '������������
    Select Case iQiJu(Di, Dj)
           Case Is = Enum_QiZhi.jShuai
                If j <= 3 Then ' And Sgn(iQiJu(I, J)) _
                <> Sgn(Enum_QiZhi.jShuai) Then  'ȷ����������
                   bShuaiWalk = True
                Else
                   bShuaiWalk = False
                End If
           Case Is = Enum_QiZhi.yShuai
                If j >= 8 Then ' And Sgn(iQiJu(I, J)) _
                <> Sgn(Enum_QiZhi.yShuai) Then   'ȷ����������
                   bShuaiWalk = True
                Else
                   bShuaiWalk = False
                End If
   End Select
Else
   bShuaiWalk = False
End If
End Function

'�жϽ��Ƿ����
'��Di��Dj����ʾҪ�жϵĵ㣬Flag=True��ʾ�ӽ���ʱ���ж�,
'Show��ʾ�Ƿ���ʾ��ʾTrueʱ��ʾ��ʾ
Public Function bShuaiDuaiMei(Di As Integer, Dj As Integer, I As Integer, j As Integer, iQiJu() As Integer, Optional Flag As Boolean = False, Optional Show As Boolean = True) As Boolean
Dim K As Long
If Di < 4 Or Di > 6 Or (Di = I And Not Flag) Then  '����������,����Y����
   bShuaiDuaiMei = False: Exit Function
End If
If Flag Then '�ӽ���ʱ���ж�
   Select Case iQiJu(Di, Dj)
          Case Is = Enum_QiZhi.jShuai
               '�ƿ���λ��
               For K = 1 To 9 '����ɨ���ҽ�
                   If Dj + K = j Then K = K + 1 '�Լ��߶����λ��
                   '�����߽�,��˵�������ڴ�����,���˳�,������False
                   If Dj + K > 10 Then Exit For
                   '�������,�Ҵ��Ӳ�Ϊ��,��˵���м�����,���˳�,������False
                   If iQiJu(Di, Dj + K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(Di, Dj + K)) <> Enum_QZ.Shuai Then
                      Exit For
                   End If
                   If Abs(iQiJu(Di, Dj + K)) = Enum_QZ.Shuai Then
                      '�ҵ���,��������ѭ��,������ɨ���ҽ�
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s˧������, vbCritical
                      Exit Function
                   End If
               Next K
               If Dj <> j Then
                  bShuaiDuaiMei = False
                  Exit Function
               End If
               'Ҫ�ߵ�λ��
               For K = 1 To 9 '����ɨ���ҽ�
                   '�����߽�,��˵�������ڴ�����,���˳�,������False
                   If j + K > 10 Then bShuaiDuaiMei = False: Exit Function
                   '�������,�Ҵ��Ӳ�Ϊ��,��˵���м�����,���˳�,������False
                   If iQiJu(I, j + K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(I, j + K)) <> Enum_QZ.Shuai Then
                      bShuaiDuaiMei = False: Exit Function
                   End If
                   If Abs(iQiJu(I, j + K)) = Enum_QZ.Shuai Then
                      '�ҵ���,��������ѭ��,������ɨ���ҽ�
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s˧������, vbCritical
                      Exit Function
                   End If
               Next K
          Case Is = Enum_QiZhi.yShuai
               '�ƿ���λ��
               For K = 1 To 9 '����ɨ���ҽ�
                   If Dj - K = j Then K = K + 1 '�Լ��߶����λ��
                   '�����߽�,��˵�������ڴ�����,���˳�,������False
                   If Dj - K < 1 Then Exit For
                   '�������,�Ҵ��Ӳ�Ϊ��,��˵���м�����,���˳�,������False
                   If iQiJu(Di, Dj - K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(Di, Dj - K)) <> Enum_QZ.Shuai Then
                      Exit For
                   End If
                   If Abs(iQiJu(Di, Dj - K)) = Enum_QZ.Shuai Then
                      '�ҵ���,�򽫶���
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s˧������, vbCritical
                      Exit Function
                   End If
               Next K
               If Dj <> j Then
                  bShuaiDuaiMei = False
                  Exit Function
               End If
               'Ҫ�ߵ�λ��
               For K = 1 To 9 '����ɨ���ҽ�
                   '�����߽�,��˵�������ڴ�����,���˳�,������False
                   If j - K < 1 Then bShuaiDuaiMei = False: Exit Function
                   '�������,�Ҵ��Ӳ�Ϊ��,��˵���м�����,���˳�,������False
                   If iQiJu(I, j - K) <> Enum_QiZhi.NoZhi _
                      And Abs(iQiJu(I, j - K)) <> Enum_QZ.Shuai Then
                      bShuaiDuaiMei = False: Exit Function
                   End If
                   If Abs(iQiJu(I, j - K)) = Enum_QZ.Shuai Then
                      '�ҵ���,�򽫶���
                      bShuaiDuaiMei = True
                      If Show Then MsgBox s˧������, vbCritical
                      Exit Function
                   End If
               Next K
   End Select
Else '���Ǵӽ���ʱ���ж�
     For K = 1 To 9 '����ɨ���ҽ�
         '�����߽�,��˵�������ڴ�����,���˳�,������False
         If Dj + K > 10 Then bShuaiDuaiMei = False: Exit Function
         '�������,�Ҵ��Ӳ�Ϊ��,��˵���м�����,���˳�,������False
         If iQiJu(Di, Dj + K) <> Enum_QiZhi.NoZhi _
            And Abs(iQiJu(Di, Dj + K)) <> Enum_QZ.Shuai Then
              bShuaiDuaiMei = False: Exit Function
         End If
         If Abs(iQiJu(Di, Dj + K)) = Enum_QZ.Shuai Then
            '�ҵ���,��������ѭ��,������ɨ���ҽ�
             Exit For
         End If
     Next K
     For K = 1 To 9 '����ɨ���ҽ�
         '�����߽�,��˵�������ڴ�����,���˳�,������False
         If Dj - K < 1 Then bShuaiDuaiMei = False: Exit Function
         '�������,�Ҵ��Ӳ�Ϊ��,��˵���м�����,���˳�,������False
         If iQiJu(Di, Dj - K) <> Enum_QiZhi.NoZhi _
            And Abs(iQiJu(Di, Dj - K)) <> Enum_QZ.Shuai Then
            bShuaiDuaiMei = False: Exit Function
         End If
         If Abs(iQiJu(Di, Dj - K)) = Enum_QZ.Shuai Then
            '�ҵ���,�򽫶���
            bShuaiDuaiMei = True
            If Show Then MsgBox s˧������, vbCritical
            Exit Function
         End If
     Next K
End If
End Function

'����Ϊ���ӵ��߷������ӵ㣨DI��DJ�����㣨I��J���Ƿ�����
'�����ǵ�(I,J)�Ƿ��ǶԷ�����
'----------------------------------------------------------------------------------------

'----------------------------------------------------------------------------------------
'����ʱ�����Ƿ�����߷�
Public Function bBuJu_eWalk_fa(I As Integer, j As Integer, Source As Object) As Boolean
Dim X As Single, Y As Single, Di As Integer, Dj As Integer
Select Case Sgn(Source.Tag) * (Abs(Source.Tag) Mod 10)
       Case Enum_QiZhi.jBing
            If j < 4 Or ((j = 5 Or j = 4) And _
             (I Mod 2 = 0)) Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
             'δ����ʱ������������һ������������
            If j = 5 Or j = 4 Then 'δ����ʱ������������һ������������
               If Abs(Source.Tag) \ 10 Mod 10 = 0 Then '���������ƶ�ʱ
                  '���ƶ��Լ�ʱ
                  Form1.ZhouBiao_eTranslate Source.Left, Source.Top, Di, Dj
                  If Di = I Then
                     GoTo bBuJu_eWalk_Fa_Loop
                  End If
               End If
               '�ӱ�������ϻ������������
               If j = 5 Then
                  j = 4
               Else
                  j = 5
               End If
               Form1.ZhouBiao_eTranslate X, Y, I, j, ���������ת��Ϊ�����ϵ�����
               If Form1.QiJu_eArrary(X, Y) = Enum_QiZhi.jBing Then
                  bBuJu_eWalk_fa = False
                  MsgBox s�������������߷�, vbCritical
                  Exit Function
               End If
            End If
       Case Enum_QiZhi.yBing
            If j > 7 Or ((j = 6 Or j = 7) And _
             (I Mod 2 = 0)) Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
             'δ����ʱ������������һ������������
            If j = 6 Or j = 7 Then 'δ����ʱ������������һ������������
               If Abs(Source.Tag) \ 10 Mod 10 = 0 Then '���������ƶ�ʱ
                  '���ƶ��Լ�ʱ
                  Form1.ZhouBiao_eTranslate Source.Left, Source.Top, Di, Dj
                  If Di = I Then
                     GoTo bBuJu_eWalk_Fa_Loop
                  End If
               End If
               '�ӱ�������ϻ������������
               If j = 6 Then
                  j = 7
               Else
                  j = 6
               End If
               Form1.ZhouBiao_eTranslate X, Y, I, j, ���������ת��Ϊ�����ϵ�����
               If Form1.QiJu_eArrary(X, Y) = Enum_QiZhi.yBing Then
                  bBuJu_eWalk_fa = False
                  MsgBox s�������������߷�, vbCritical
                  Exit Function
               End If
            End If
       Case Enum_QiZhi.jXiang
            If Not ((j = 1 And (I = 3 Or I = 7)) Or _
                    (j = 3 And (I = 1 Or I = 5 Or I = 9)) Or _
                    (j = 5 And (I = 3 Or I = 7))) Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.yXiang
            If Not ((j = 10 And (I = 3 Or I = 7)) Or _
                    (j = 8 And (I = 1 Or I = 5 Or I = 9)) Or _
                    (j = 6 And (I = 3 Or I = 7))) Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.jShi
            If Not ((I = 4 And (j = 1 Or j = 3)) Or _
                   (I = 5 And j = 2) Or _
                   (I = 6 And (j = 1 Or j = 3))) Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.yShi
            If Not ((I = 4 And (j = 10 Or j = 8)) Or _
                   (I = 5 And j = 9) Or _
                   (I = 6 And (j = 10 Or j = 8))) Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.jShuai
            If I < 4 Or I > 6 Or j > 3 Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
       Case Enum_QiZhi.yShuai
            If I < 4 Or I > 6 Or j < 8 Then
               bBuJu_eWalk_fa = False
               MsgBox s�����������߷�, vbCritical
               Exit Function
            End If
End Select
bBuJu_eWalk_Fa_Loop:
bBuJu_eWalk_fa = True
End Function

'------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
'��ֱ���ͽ���
'������(I,J)������ϵ�λ��,QiZhi�ڱ���ʱ�����ӵĴ���,�ڽ���ʱ��Ҫ���н���Ĵ���
'����ֵ:���Ǳ���ʱ,�Ǳ�õĴ���
'       ���ǽ���ʱ,�����ӵĴ���
Public Function QiJuBianMa(I As Integer, j As Integer, Optional QiZhi As Integer = Enum_QiZhi.NoZhi, Optional Flag As Enum_QiJuBianMa_Flag = Enum_QiJuBianMa_Flag.���б���) As Integer
Select Case Flag
       Case ���б���
            If QiZhi = Enum_QiZhi.NoZhi Then
               QiJuBianMa = j + I * 100
            Else
               QiJuBianMa = Sgn(QiZhi) * (j + I * 100 + Abs(QiZhi * 1000))
            End If
       Case ���н���
            I = Abs(QiZhi) \ 100 Mod 10
            j = Abs(QiZhi) Mod 100
            QiJuBianMa = QiZhi \ 1000
End Select
End Function

'�����Ӵ��뷭�������
Public Function Read_QiZhi(QiZhi As Integer) As String
Select Case QiZhi
       Case Enum_QiZhi.NoZhi
            Read_QiZhi = "����"
       Case Enum_QiZhi.jChe
            Read_QiZhi = "�׳�"
       Case Enum_QiZhi.jBing
            Read_QiZhi = "�ױ�"
       Case Enum_QiZhi.jMa
            Read_QiZhi = "����"
       Case Enum_QiZhi.jPao
            Read_QiZhi = "����"
       Case Enum_QiZhi.jShi
            Read_QiZhi = "����"
       Case Enum_QiZhi.jShuai
            Read_QiZhi = "��˧"
       Case Enum_QiZhi.jXiang
            Read_QiZhi = "����"
       Case Enum_QiZhi.yBing
            Read_QiZhi = "����"
       Case Enum_QiZhi.yChe
            Read_QiZhi = "�ҳ�"
       Case Enum_QiZhi.yMa
            Read_QiZhi = "����"
       Case Enum_QiZhi.yPao
            Read_QiZhi = "����"
       Case Enum_QiZhi.yShi
            Read_QiZhi = "��ʿ"
       Case Enum_QiZhi.yShuai
            Read_QiZhi = "�ҽ�"
       Case Enum_QiZhi.yXiang
            Read_QiZhi = "����"
End Select
End Function

'----------------------------------------------------------------------------------------------------------------------------
'������ֵ���������
Public Function Read_Controled(XinShi As Integer) As String
Select Case XinShi
       Case 0
            Read_Controled = "��"
       Case Is > 0
            Read_Controled = "���׷�"
       Case Is < 0
            Read_Controled = "���ҷ�"
End Select
End Function

'���Ʒ���
Public Function XinShiFenXi(iQiJu() As Integer, XinShiBiao() As Type_XinShiFenXiBiao, jFQi() As Integer, yFQi() As Integer)
Dim I As Integer, j As Integer, K As Long, Di As Integer, Dj As Integer

'1.ɨ�������ϵ�����,����¼����
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
'2.ȷ��������֮��Ĺ�ϵ,����¼�����ӵı��ķ�����,
'�����������ֵ.
'��������Ӧ��Ȩֵ,������Ƿ��ܹ������򱣻�
For I = 1 To 9
    For j = 1 To 10
        With XinShiBiao(I, j)
                K = 1
                ReDim .jF_eControl(0)
                While (K <= UBound(jFQi)) 'ɨ�豻�׷��������
                      Call QiJuBianMa(Di, Dj, jFQi(K), ���н���)
                      If bQiZhi_eWalk(Di, Dj, I, j, iQiJu) Then
                         ReDim Preserve .jF_eControl _
                           (UBound(.jF_eControl) + 1)
                         .jF_eControl(UBound(.jF_eControl)) = jFQi(K)
                      End If
                      K = K + 1
                Wend
                K = 1
                ReDim .yF_eControl(0)
                While (K <= UBound(jFQi)) 'ɨ�豻�ҷ��������
                      Call QiJuBianMa(Di, Dj, yFQi(K), ���н���)
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
'3.ͳ�������ϸ�λ�õı��׷��ӻ��ҷ��ӿ���,�����������,��ȷ��
'���ķ�����

End Function
