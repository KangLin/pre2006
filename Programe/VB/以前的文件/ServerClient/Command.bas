Attribute VB_Name = "Command"
'*****************************************************************************
'       ��           ��          ��          ��       ��          ��
'                                �� ��:  �� ��
'*****************************************************************************
Option Explicit

'====================================================================================
'                  ��                          ��
'====================================================================================
'����ṹ
'������ת��Ϊ�ַ���Str (lngcommand)
'   ���磺Str(lngCommand) & <NULL> &  sPara1 & <NULL>
'         & sPara2 & <NULL> & ����& <NULL><NULL>
'�������,��������һ��<NULL>�ֿ�,������<NULL>����

'���ܣ�������
Public Const cCmdNull As Long = 0

'���ܣ�ȡ�����ڽ��е�����.
Public Const cCmdCancel As Long = cCmdNull

'����:���ݴ��ͽ���
Public Const cCmdDataSendEnd As Long = 1

'------------------------------------------------------------------------
'                   ��        ��        ��         ��
'------------------------------------------------------------------------
'���ܣ�ȡ�ñ��ص�������������
'����: �޲�����
'���أ����ص������������������ԣ����ͣ���ȡ���������ͳ���һ����
'���͸�ʽ��<C:><NULL><D:><NULL><NULL>
'        �̷���һ��<NULL>���֣�������<NULL>������
'        ����sckCmdServer���͡�
'����û���߼���������cNoLogicalDrives=10000����
Public Const cCmdGetLogicalDrives As Long = 100
'û���߼�������
Public Const cCmdErrorNoLogicalDrives As Long = 10000

'���ܣ���ָ����Ŀ¼��������������Ŀ¼��
'����: Ŀ¼����
'      �ͻ��˵�IP��ַ
'      �ͻ��˵Ķ˿�
'������ʽ��<Ŀ¼><NULL><�ͻ������ݽ���WinSock��IP��ַ><NULL> _
           <�ͻ����ݽ���WinSock�Ķ˿�><NULL><NULL>
'����ֵ: ����Ŀ¼���ļ���ϳɵ��ַ�������ʽΪ:
'        <Ŀ¼1><NULL><�ļ�2><NULL>����<NULL><NULL>��
'        ��һ��vbNullChar�ָ�Ŀ¼���ļ���������vbNullChar����������
'����1��Ŀ¼��������(cCmdErrorNoDirectory)��
'2 ���޷���ֵ��
'����:��sckDataServer���͡�
Public Const cCmdOpenDirectory As Long = 101

'���ܣ�����ָ����Ŀ¼��
'����: Ŀ¼����
'      �ͻ��˵�IP��ַ
'      �ͻ��˵Ķ˿�
'������ʽ��<Ŀ¼><NULL><�ͻ������ݽ���WinSock��IP��ַ><NULL> _
           <�ͻ����ݽ���WinSock�Ķ˿�><NULL><NULL>
'����ֵ: ����Ŀ¼���ļ���ϳɵ��ַ�������ʽΪ:
'        <Ŀ¼1><NULL><�ļ�2><NULL>����<NULL><NULL>��
'        ��һ��vbNullChar�ָ�Ŀ¼���ļ���������vbNullChar����������
'����1��Ŀ¼��������(cCmdErrorNoDirectory)��
'2 ���޷���ֵ��
'����:��sckDataServer���͡�
Public Const cCmdTraverseDirectory As Long = 102

'���ܣ���ָ���ķ�Χ�ڲ���ָ�����ļ���
'������1��Ҫ���ҵ��ļ�������ͨ�����*��������
'      2 ��ָ�����ҵķ�Χ��
'          A�� ָ����Ŀ¼��
'          B�� ָ������������
'          C�� ����������
'      3���ͻ��˵�IP��ַ
'      4 �� �ͻ��˵Ķ˿�
'������ʽ:<Ҫ���ҵ��ļ���><NULL><ָ�����ҵķ�Χ><NULL> _
          <�ͻ������ݽ���WinSock��IP��ַ><NULL> _
          <�ͻ������ݽ���WinSock�Ķ˿�><NULL><NULL>
'����ֵ:�ҵ�������·������ϡ���ʽΪ:
'       <Ŀ¼1><NULL><Ŀ¼2><NULL>����<NULL><NULL>��
'       ��һ��vbNullChar�ָ�Ŀ¼��������vbNullChar����������
'����1��Ŀ¼�������ڡ�(cCmdErrorNoDirectory)
'      2 ���޷���ֵ��
'���ͣ�1����sckDataServer���͡�
'      2����sckCmdServer�����ļ����ҽ���(cCmdFindFileEnd)���ҵ��ĸ���
Public Const cCmdFindFile As Long = 103
'�ļ����ҽ���
Public Const cCmdFindFileEnd As Long = 104

'���ܣ�����Ŀ¼����
'���ͽ���
Public Const cCmdDirectoryEnd As Long = 105
'Ŀ¼������
Public Const cCmdErrorNoDirectory As Long = 10001

