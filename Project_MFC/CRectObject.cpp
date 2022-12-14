#include "pch.h"
#include "CRectObject.h"
CRectObject::CRectObject() {

}
CRectObject::CRectObject(CPoint pt, int w, int h, CString pa, CString na) {
	m_pos = pt;
	m_width = w;
	m_height = h;
	m_selected = false;
	m_path = pa;
	m_name = na;
}


bool CRectObject::CheckSelected(CPoint pt)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
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
	// TODO: ���⿡ ���� �ڵ� �߰�.
	/*
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	if (m_selected) {
		pDC->SelectObject(&pen);
	}
	else {
		pDC->SelectObject(GetStockObject(BLACK_PEN));
	}
	*/
	CImage img;
	img.Load(m_path);  // ��� ���� ����
	img.Draw(*pDC, m_pos.x, m_pos.y);

	pDC->DrawText(m_name, CRect(m_pos.x, m_pos.y+100, m_pos.x+100, m_pos.y+150), DT_CENTER);  //�ؽ�Ʈ ���� ����

	//pDC->Rectangle(m_pos.x, m_pos.y, m_pos.x+m_width, m_pos.y+m_height);
}

bool CRectObject::IsCollide(CRect& other)
{
	CRect rcResult;
	CRect rcMy(m_pos, CPoint(m_pos.x + m_width, m_pos.y + m_height));

	return rcResult.IntersectRect(&rcMy, &other);
}