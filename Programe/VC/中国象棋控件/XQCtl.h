#if !defined(AFX_XQCTL_H__8A497636_8516_444B_868E_0E753A2D3BA9__INCLUDED_)
#define AFX_XQCTL_H__8A497636_8516_444B_868E_0E753A2D3BA9__INCLUDED_

#include <afxtempl.h>
#include <vector>
#include <mmsystem.h>
#include "GoRule.h"
#include "EnumAndStructAndConst.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma comment(lib, "winmm")
#pragma comment(lib, "Msimg32")

/*******************************************************************************************************
����
*******************************************************************************************************/

//������λ
enum ENUM_XINWEI{XinWei, Left_XinWei, Right_XinWei};
//����ת��
enum ENUM_ConvertCoordinate{XYToIJ, IJToXY};
//���̲���
enum ENUM_QiPang{  NoQi = 0, OnlyTopRed = 1, OnlyBottomBlack = 2, SwapRedBetweenBlack = 4, 
                   OnlyTopBlack = OnlyTopRed | SwapRedBetweenBlack, 
				   OnlyBottomRed = OnlyBottomBlack | SwapRedBetweenBlack,
				   TopRedAndBottomBlack = OnlyTopRed | OnlyBottomBlack,
				   TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed | SwapRedBetweenBlack};
//����״̬
enum ENUM_WalkState{RedReadly, RedWalked, BlackReadly, BlackWalked};

/*******************************************************************************************************
�ṹ
*******************************************************************************************************/

//��ʾ���λ��
struct struct_TiShiBoxPostion{          
		CPoint p1;
		CPoint p2;
};

//�ļ�ͷ
struct struct_File{
	TCHAR szAppName[MAX_STRING_BUFFER];    //������,��Restart������
	TCHAR szAuthor[MAX_STRING_BUFFER];     //�������ߣ�����,��Restart������
	DWORD dwVersion;                       //�汾,��Restart������
	time_t timeStart;                      //��ʼ�����ʱ��,��Restart������
	time_t timeEnd;                        //���������ʱ��,��Restart������
	TCHAR szRedName[MAX_STRING_BUFFER];    //�췽�û���
    TCHAR szBlackName[MAX_STRING_BUFFER];  //�ڷ��û���
	int iStartSide;                        //���汾���ķ�������,��Restart��SetStartSide�ж�������
	int iBuShu;                            //��������SaveChess������
	DWORD dwReserve;                       //����
};

#define AUTHOR _T("���ߣ����֡���Ȩ���С�")

/*******************************************************************************************************
����
*******************************************************************************************************/

//��͸��ͼƬ
void TransparentBlt2(HDC hdcDest,         // Ŀ��DC
                     int nXOriginDest,    // Ŀ��Xƫ��
                     int nYOriginDest,    // Ŀ��Yƫ��
                     int nWidthDest,      // Ŀ����
                     int nHeightDest,     // Ŀ��߶�
                     HDC hdcSrc,          // ԴDC
                     int nXOriginSrc,     // ԴX���
                     int nYOriginSrc,     // ԴY���
                     int nWidthSrc,       // Դ���
                     int nHeightSrc,      // Դ�߶�
                     UINT crTransparent   // ͸��ɫ,COLORREF����
					 );
/////////////////////////////////////////////////////////////////////////////
// CXQCtrl : See XQCtl.cpp for implementation.

class CXQCtrl : public COleControl
{
	DECLARE_DYNCREATE(CXQCtrl)

// Constructor
public:
	CXQCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXQCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CXQCtrl();

	DECLARE_OLECREATE_EX(CXQCtrl) // Class factory and guid
	DECLARE_OLETYPELIB(CXQCtrl)   // GetTypeInfo
	DECLARE_PROPPAGEIDS(CXQCtrl)  // Property page IDs
	DECLARE_OLECTLTYPE(CXQCtrl)   // Type name and misc status

// Message maps
	//{{AFX_MSG(CXQCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CXQCtrl)
	OLE_COLOR m_QiPangColor;
	afx_msg void OnQiPangColorChanged();
	OLE_COLOR m_TiShiBoxColor;
	afx_msg void OnTiShiBoxColorChanged();
	long m_QiPang;
	afx_msg void OnQiPangLayoutChanged();
	afx_msg LPPICTUREDISP GetQiPangPicture();
	afx_msg void SetQiPangPicture(LPPICTUREDISP newValue);
	afx_msg long GetStartSide();
	afx_msg void SetStartSide(long nNewValue);
	afx_msg short GetCurrentSide();
	afx_msg void SetCurrentSide(short nNewValue);
    afx_msg long NextStep();                              //��һ��
    afx_msg long PreviouStep();                           //��һ��
    afx_msg void ReStart();                               //���¿�ʼ
    afx_msg BOOL SaveChess(LPCTSTR lpcszFileName);        //�������
    afx_msg BOOL LoadChess(LPCTSTR lpcszFileName);        //װ����֣�������Ϊ����״̬
    afx_msg BOOL LoadChessStart(LPCTSTR lpcszFileName);   //װ����֣�������Ϊ��ʼ״̬
    afx_msg void QiPangInterconvert();                    //���ӻ���
	afx_msg BOOL Walk(short i, short j);
	afx_msg void InterConvertCoordinate(short x, short y, short FAR* pi, short FAR* pj);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CXQCtrl)
	void FireMoveChess(short x, short y, long chess)
		{FireEvent(eventidMoveChess,EVENT_PARAM(VTS_I2  VTS_I2  VTS_I4), x, y, chess);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
    //{{AFX_DISP_ID(CXQCtrl)
	dispidQiPangColor = 1L,
	dispidTiShiBoxColor = 2L,
	dispidQiPangPicture = 4L,
	dispidQiPangLayout = 3L,
	dispidStartSide = 5L,
	dispidCurrentSide = 6L,
	dispidNextStep = 7L,
	dispidPreviouStep = 8L,
	dispidReStart = 9L,
	dispidSaveChess = 10L,
	dispidLoadChess = 11L,
	dispidLoadChessStart = 12L,
	dispidQiPangInterconvert = 13L,
	dispidWalk = 14L,
	dispidInterConvertCoordinate = 15L,
	eventidMoveChess = 1L,
	//}}AFX_DISP_ID
	};

private:	
    BOOL WalkChess(int i, int j, BOOL bEvent = TRUE);
	BOOL bWalkChess(int i, int j);

	int QiZiBianMa(int *i, int *j, ENUM_QiZi *QZ, int *Code,  ENUM_BianMa bianma= BianMa);
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC= XYToIJ);

	BOOL PromptSound(LPCTSTR ID = NULL);
	
	BOOL GetCBitmapFromCPictureHolder(CPictureHolder *ph, CBitmap *pb);
	
	void InvalidateRectage(CPoint p);
	void InvalidateRectage(int i, int j);
	
	BOOL DrawTiShiBox(CDC *pdc, CPoint p);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);
	BOOL DrawQiZi(CDC *pdc, int i, int j, ENUM_QiZi eQiZi);
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	void DrawQiPang(CDC *pdc, CRect rcBounds);

	BOOL Inital();

	LONG m_QiPangStartX;    //���̵Ŀ�ʼ������
	LONG m_QiPangStartY;    //���̵Ŀ�ʼ������
	LONG m_QiPangDistance;  //���̸�ľ���

	ENUM_WalkState m_WalkState;    //����״̬���췽ѡ�壬�췽���壬�ڷ����壬�ڷ����壩
	ENUM_QiZi m_ChessBoard[9][10]; //���� m_ChessBoard[i][j]
    CArray<int, int> m_QiJu;       //���
	INT m_iBuShu;                  //���岽��
	BOOL m_bFuPang;                //���̱�־
	struct struct_TiShiBoxPostion m_TiShiBoxPostion;

	CBitmap m_QiPangPicture;              //���̱���ͼƬ
	CPictureHolder m_QiPangPictureHolder; //���̱���ͼƬ��CPictureHolder����
	
	//����ͼƬ
    CBitmap m_RedShuai;     //��˧
    CBitmap m_RedShi;       //����
    CBitmap m_RedXiang;     //����
    CBitmap m_RedMa;        //����
    CBitmap m_RedChe;       //�쳵
    CBitmap m_RedBing;      //���
    CBitmap m_RedPao;       //����
	
    CBitmap m_BlackShuai;   //��˧
    CBitmap m_BlackShi;     //����
    CBitmap m_BlackXiang;   //����
    CBitmap m_BlackMa;      //����
    CBitmap m_BlackChe;     //�ڳ�
    CBitmap m_BlackBing;    //�ڱ�
    CBitmap m_BlackPao;     //����

	/*ENUM_QiPang m_QiPang; /*��ʼ�����̣����壬ֻ���Ϸ����壬ֻ���·����壬
						                ֻ���Ϸ����壬ֻ���·����塢
										�Ϻ��º��嶼�ڣ��Ϻ��º춼�ڣ�
										*/
	CGoRule *m_pGoRule;       //�������ָ��
	struct_File m_FileHead;   //����ļ�ͷ
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_XQCTL_H__8A497636_8516_444B_868E_0E753A2D3BA9__INCLUDED)
