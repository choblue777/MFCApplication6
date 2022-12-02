
// MFCApplication6View.cpp: CMFCApplication6View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication6.h"
#endif

#include "MFCApplication6Doc.h"
#include "MFCApplication6View.h"

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
	// TODO: 여기에 생성 코드를 추가합니다.

	for (size_t i = 0; i <= 9; i++) {
		obj[i] = CRectObject(CPoint(100 * (i +1), 600), 50, 50);
	}

	m_index = -1;
	num = 1;
	str.Format(L"현재 점수: %d", num);
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
	CImage e_w;
	e_w.Load(L"./res/E-WASTE1-removebg.png");
	e_w.Draw(pDC->m_hDC, 50, 50);

	CImage gl;
	gl.Load(L"./res/GLASS-removebg.png");
	gl.Draw(pDC->m_hDC, 350, 50);
	
	CImage mt;
	mt.Load(L"./res/METAL-removebg.png");
	mt.Draw(pDC->m_hDC, 650, 50);

	CImage og;
	og.Load(L"./res/ORGANIC-removebg.png");
	og.Draw(pDC->m_hDC, 950, 50);

	CImage pp;
	pp.Load(L"./res/PAPER-removebg.png");
	pp.Draw(pDC->m_hDC, 1250, 50);

	CImage ps;
	ps.Load(L"./res/PLASTIC-removebg.png");
	ps.Draw(pDC->m_hDC, 1550, 50);

	for (size_t i = 0; i <= 9; i++) {
		obj[i].Draw(pDC);
	}
	pDC->TextOut(1000, 0, str);
	/* 1점씩 추가되는 코드
	 	num = num + 1;
	str.Format(L"현재 점수: %d", num);
	*/

	CBrush brush1(RGB(255, 0, 0)); //쓰레기통 좌표 알기 위한 사각형
	CBrush* c_brush;
	c_brush = pDC->SelectObject(&brush1);
	pDC->Rectangle(50, 50, 300, 450);

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
	//(100,200,300,300), (pint.x, point.y)
	/*
	if (100 <= point.x && point.x <= 300 && 200 <= point.y && point.y <= 300) {
		m_selected = true;
		Invalidate();
	}
	*/
	for (size_t i = 0; i <= 9; i++) { //최대 9개까지 클릭했다는거 인지
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
	if (m_index != -1) { //클릭한 도형을 현재 마우스 좌표로 이동
		obj[m_index].m_pos = point;
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCApplication6View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (obj[1].m_pos.x <= 350 && obj[1].m_pos.x >= 50 &&
		obj[1].m_pos.y <= 450 && obj[1].m_pos.y >= 50) {
		num = num + 1;
		str.Format(L"현재 점수: %d", num);
		obj[1] = CRectObject(CPoint(0, 0), 0, 0);
		Invalidate();
	}
	if (m_index == 0 || m_index == 2 || m_index == 3 || m_index == 4
		|| m_index == 5 || m_index == 6 || m_index == 7 || m_index == 8 || m_index == 9)
	{
		obj[m_index] = CRectObject(CPoint(100 * (m_index + 1), 600), 50, 50); ;
		Invalidate();
	}
	m_index = -1;
	CView::OnLButtonUp(nFlags, point);
}
