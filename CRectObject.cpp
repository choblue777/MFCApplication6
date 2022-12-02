#include "pch.h"
#include "CRectObject.h"
CRectObject::CRectObject() {

}
CRectObject::CRectObject(CPoint pt, int w, int h) {
	m_pos = pt;
	m_width = w;
	m_height = h;
	m_selected = false;
}

bool CRectObject::CheckSelected(CPoint pt)
{
	// TODO: 여기에 구현 코드 추가.
	if (m_pos.x <= pt.x && pt.x <= m_pos.x+m_width
		&& m_pos.y <= pt.y && pt.y <= m_pos.y+m_height) {
		m_selected = true;
	}
	else {
		m_selected = false;
	}
	return(m_selected);
}


void CRectObject::Draw(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	/*
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	if (m_selected) {
		pDC->SelectObject(&pen);
	}
	else {
		pDC->SelectObject(GetStockObject(BLACK_PEN));
	}
	*/
	pDC->Rectangle(m_pos.x, m_pos.y, m_pos.x+m_width, m_pos.y+m_height);
}
