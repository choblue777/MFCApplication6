
// MFCApplication6View.h: CMFCApplication6View 클래스의 인터페이스
//

#pragma once
#include "CRectObject.h"

class CMFCApplication6View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication6View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication6View)

// 특성입니다.
public:
	CMFCApplication6Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApplication6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	//bool m_selected;
	CRectObject obj[10];
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int m_index;
	int num;
	CString str;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CImage back;
};

#ifndef _DEBUG  // MFCApplication6View.cpp의 디버그 버전
inline CMFCApplication6Doc* CMFCApplication6View::GetDocument() const
   { return reinterpret_cast<CMFCApplication6Doc*>(m_pDocument); }
#endif

