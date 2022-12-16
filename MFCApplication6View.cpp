
// MFCApplication6View.cpp: CMFCApplication6View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication6.h"
#include <afxwin.h>
#include "resource.h"
#endif

#include "MFCApplication6Doc.h"
#include "MFCApplication6View.h"

#pragma comment(lib, "winmm")  
#include <mmsystem.h>  

CString bgSoundPath = (L"./bgm.wav"); 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication6View

IMPLEMENT_DYNCREATE(CMFCApplication6View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication6View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMFCApplication6View 생성/소멸

CMFCApplication6View::CMFCApplication6View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다..
	
	CString pt[13] = { L"./res/pet.png", L"./res/hanger.png", L"./res/gas.png", L"./res/glass.png", L"./res/banana.png", L"./res/wm.png",
		L"./res/cabo.png", L"./res/shaver.png", L"./res/hammer.png", L"./res/um.png", L"./res/mouse.png", L"./res/phone.png", L"./res/sten.png" };   // 이미지 경로 배열

	CString na[13] = { L"페트병", L"철사 옷걸이", L"가스통", L"유리병", L"바나나 껍질", L"수박 껍질", L"골판지", L"면도기", L"망치", L"우산대", L"마우스", L"전화기", L"스텐 그릇" };  //이름 배열

	for (size_t i = 0; i <13; i++) { 
		obj[i] = CRectObject(CPoint(750, 500), 100, 100, pt[i], na[i]);
	}
	m_stack = 0;
	m_index = -1;
	num = 0;
	order = 0;

	hint = CRectObject(CPoint(50, 450), 200, 200, L"./res/hint.png", NULL);
	
	MessageBox(_T("안녕하세요, 환경에 일조하조입니다."));

	if (AfxMessageBox(_T("분리수거 게임을 시작하시겠습니까?",), MB_YESNO | MB_ICONQUESTION) == IDNO)
		exit(0);
		
	str.Format(L"현재 점수: %d", num);
	
	PlaySound(L"./bgm.wav", AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_NOSTOP);
	
	TrashCan[0].Load(L"./res/E-WASTE-removebg-preview.png");
	TrashCan[1].Load(L"./res/GLASS-removebg-preview.png");
	TrashCan[2].Load(L"./res/METAL-removebg-preview.png");
	TrashCan[3].Load(L"./res/ORGANIC-removebg-preview.png");
	TrashCan[4].Load(L"./res/PAPER-removebg-preview.png");
	TrashCan[5].Load(L"./res/PLASTIC-removebg-preview.png");

	for (int i = 0; i < 6; i++)
	{
		rcTrashCan[i].right = rcTrashCan[i].left + TrashCan[i].GetWidth();
		rcTrashCan[i].bottom = rcTrashCan[i].top + TrashCan[i].GetHeight();
	}
}

CMFCApplication6View::~CMFCApplication6View()
{
}

BOOL CMFCApplication6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication6View 그리기

void CMFCApplication6View::OnDraw(CDC* pDC)
{
	CMFCApplication6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	CImage wall;
	wall.Load(L"./res/wall.png");
	wall.Draw(pDC->m_hDC, 0, 0);

	for (int i = 0; i < 6; i++)
	{
		CPoint& xy = rcTrashCan[i].TopLeft();
		TrashCan[i].Draw(pDC->m_hDC, xy.x, xy.y);

		pDC->SelectStockObject(NULL_BRUSH);
		pDC->Rectangle(rcTrashCan[i]);
	}

	obj[order].Draw(pDC);
	hint.Draw(pDC);
	pDC->TextOut(1000, 0, str);
}


// CMFCApplication6View 인쇄

BOOL CMFCApplication6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication6View 진단

#ifdef _DEBUG
void CMFCApplication6View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication6Doc* CMFCApplication6View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication6Doc)));
	return (CMFCApplication6Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication6View 메시지 처리기

void CMFCApplication6View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	for (size_t i = 0; i < 13; i++) { //최대 9개까지 클릭했다는거 인지
		if (obj[i].CheckSelected(point) == true) {
			m_index = i;
			break;
		}
	}
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
	
}


void CMFCApplication6View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_index != -1) { 
		obj[m_index].m_pos.x = point.x - 50;
		obj[m_index].m_pos.y = point.y - 50;
		Invalidate(false);
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCApplication6View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (obj[0].IsCollide(rcTrashCan[5]) || obj[1].IsCollide(rcTrashCan[2]) || obj[2].IsCollide(rcTrashCan[2]) ||
		obj[3].IsCollide(rcTrashCan[1]) || obj[4].IsCollide(rcTrashCan[3]) || obj[5].IsCollide(rcTrashCan[3]) || 
		obj[6].IsCollide(rcTrashCan[4]) || obj[7].IsCollide(rcTrashCan[0]) || obj[8].IsCollide(rcTrashCan[2]) ||
		obj[9].IsCollide(rcTrashCan[2]) || obj[10].IsCollide(rcTrashCan[0]) || obj[11].IsCollide(rcTrashCan[0]) || obj[12].IsCollide(rcTrashCan[2]))
	{
		if (order >= 12) {
			MessageBox(_T("수고하셨습니다."));
			PlaySound(NULL, AfxGetInstanceHandle(), NULL);
			exit(0);
		}

		obj[order].m_pos.x = 0;
		obj[order].m_pos.y = 750;
		num= num + 1; // 점수 증가
		order++;
		str.Format(L"현재 점수: %d", num);
		Invalidate();
	}
	else if (hint.CheckSelected(point) == true) {
		switch (order)
		{
		case 0:
			MessageBox(_T("힌트: 병의 소재는 플리에틸렌입니다."));
			break;
		case 1:
			MessageBox(_T("힌트: 철사가 뭘로 만들어졌을까?"));
			break;
		case 2:
			MessageBox(_T("힌트: 가스를 빼면 캔류로 분리 가능합니다."));
			break;
		case 3:
			MessageBox(_T("힌트: 유리는 영어로?"));
			break;
		case 4:
			MessageBox(_T("힌트: 먹고 남은 '음식'"));
			break;
		case 5:
			MessageBox(_T("힌트: 먹고 남은 '음식'"));
			break;
		case 6:
			MessageBox(_T("힌트: 골판지의 '지'는?"));
			break;
		case 7:
			MessageBox(_T("힌트: 일반 면도기와 가장 큰 차이는?"));
			break;
		case 8:
			MessageBox(_T("힌트: 손잡이때문에 헷갈리지만 머리 부분을 봐야한다."));
			break;
		case 9:
			MessageBox(_T("힌트: 가림막은 일반, 플라스틱으로 분류 가능하지만 대는 다르다."));
			break;
		case 10:
			MessageBox(_T("힌트: 겉보기와 달리 수많은 부품이 들어간다."));
			break;
		case 11:
			MessageBox(_T("힌트: 전화를 할 수 있는 '기계'"));
			break;
		case 12:
			MessageBox(_T("힌트: 스텐은 스테인리스강의 줄임말이다."));
			break;
		}
		
	}
	else {
		obj[order].m_pos.x = 750;
		obj[order].m_pos.y = 500;
		AfxMessageBox(_T("다시 시도해주세요."));
		Invalidate();
	}

	m_index = -1;

	if (num >= 13)
		if (AfxMessageBox(_T("성공했습니다 게임을 나가시겠습니까?", ), MB_YESNO | MB_ICONQUESTION) == IDYES)
			exit(0);
	CView::OnLButtonUp(nFlags, point);
}
