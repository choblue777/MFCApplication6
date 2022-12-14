﻿
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

	CString pt[13] = { L"./res/pet.png", L"./res/alumin.png", L"./res/gas.png", L"./res/glass.png", L"./res/banana.png", L"./res/wm.png",
		L"./res/cabo.png", L"./res/shaver.png", L"./res/hammer.png", L"./res/um.png", L"./res/mouse.png", L"./res/phone.png", L"./res/sten.png" };   // 이미지 경로 배열

	CString na[13] = { L"페트병", L"알루미늄", L"가스", L"유리", L"바나나", L"수박", L"골판지", L"면도기", L"망치", L"우산", L"마우스", L"전화기", L"스텐" };  //이름 배열

	for (size_t i = 0; i <13; i++) { 
		obj[i] = CRectObject(CPoint(900, 600), 100, 100, pt[i], na[i]);
	}
	m_stack = 0;
	m_index = -1;
	num = 0;
	order = 0;

	MessageBox(_T("안녕하세요, 환경에 일조하조입니다."));

	if (AfxMessageBox(_T("분리수거 게임을 시작하시겠습니까?", ), MB_YESNO | MB_ICONQUESTION) == IDNO)
		exit(0);

	str.Format(L"현재 점수: %d", num);
	// 11
	TrashCan[0].Load(L"./res/E-WASTE1-removebg.png");
	TrashCan[1].Load(L"./res/GLASS-removebg.png");
	TrashCan[2].Load(L"./res/METAL-removebg.png");
	TrashCan[3].Load(L"./res/ORGANIC-removebg.png");
	TrashCan[4].Load(L"./res/PAPER-removebg.png");
	TrashCan[5].Load(L"./res/PLASTIC-removebg.png");

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
	/*
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
	*/
	//11
	for (int i = 0; i < 6; i++)
	{
		// 쓰레기통 그리기
		CPoint& xy = rcTrashCan[i].TopLeft();
		TrashCan[i].Draw(pDC->m_hDC, xy.x, xy.y);

		// 테두리 그리기
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->Rectangle(rcTrashCan[i]);
	}
	//
	/*
	for (size_t i = 0; i <13; i++) {
		obj[i].Draw(pDC);
	}
	*/
	obj[order].Draw(pDC);
	pDC->TextOut(1000, 0, str);
	/* 1점씩 추가되는 코드
	 	num = num + 1;
	str.Format(L"현재 점수: %d", num);
	*/



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
	if (m_index != -1) { //클릭한 도형을 현재 마우스 좌표로 이동
		obj[m_index].m_pos = point;
		Invalidate(false);
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCApplication6View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*
		if (obj[1].m_pos.x <= 350 && obj[1].m_pos.x >= 50 &&
			obj[1].m_pos.y <= 450 && obj[1].m_pos.y >= 50 ||
			obj[2].m_pos.x <= 350 && obj[2].m_pos.x >= 50 &&
			obj[2].m_pos.y <= 450 && obj[2].m_pos.y >= 50
			) {
			num ++;
			str.Format(L"현재 점수: %d", num);
			obj[m_index] = CRectObject(CPoint(0, 0), 0, 0, L"./res/um.png", L"");

			//obj[1] = CRectObject(CPoint(0, 0), 0, 0);
			Invalidate();
		}
		*/

	if (obj[0].IsCollide(rcTrashCan[5]) || obj[1].IsCollide(rcTrashCan[3]))
	{
		obj[order].m_pos.x = 0;
		obj[order].m_pos.y = 0;
		num= num + 1; // 점수 증가
		order++;	
		str.Format(L"현재 점수: %d", num);
		Invalidate();
		}
	
		/*
	if (!obj[0].IsCollide(rcTrashCan[5]) || !obj[1].IsCollide(rcTrashCan[5]) || obj[2].IsCollide(rcTrashCan[5]) ||
		obj[3].IsCollide(rcTrashCan[5]) || obj[4].IsCollide(rcTrashCan[5]) || obj[5].IsCollide(rcTrashCan[5]) ||
		obj[6].IsCollide(rcTrashCan[5]) || obj[7].IsCollide(rcTrashCan[5]) || obj[8].IsCollide(rcTrashCan[5]) ||
		obj[9].IsCollide(rcTrashCan[5]) || obj[10].IsCollide(rcTrashCan[5]) || obj[11].IsCollide(rcTrashCan[5]) ||
		obj[12].IsCollide(rcTrashCan[5]))
	{
		obj[order].m_pos.x = 900;
		obj[order].m_pos.y = 600;
		AfxMessageBox(_T("틀렸습니다."));
		Invalidate();
	}
	*/
		/*
		if (m_index == 0 || m_index == 2 || m_index == 3 || m_index == 4
			|| m_index == 5 || m_index == 6 || m_index == 7 || m_index == 8 || m_index == 9)
		{
			obj[m_index] = CRectObject(CPoint(100 * (m_index + 1), 600), 50, 50); ;
			Invalidate();
		}
		*/
	else {
		obj[order].m_pos.x = 900;
		obj[order].m_pos.y = 600;
		AfxMessageBox(_T("다시"));
		Invalidate();
	}
		
		m_index = -1;
	if (num >= 6)
		if (AfxMessageBox(_T("성공했습니다 게임을 나가시겠습니까?", ), MB_YESNO | MB_ICONQUESTION) == IDYES)
			exit(0);
	CView::OnLButtonUp(nFlags, point);
}
