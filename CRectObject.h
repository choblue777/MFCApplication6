// CRectObject.h
#pragma once
class CRectObject
{
public:
	CPoint m_pos; 
	int m_width; 
	int m_height; 
	bool m_selected; 
public:
	CRectObject();
	CRectObject(CPoint pt, int w, int h, CString pa, CString na); // 
	bool CheckSelected(CPoint pt); 
	void Draw(CDC* pDC); 
	CString m_path;  
	CString m_name;  
	bool IsCollide(CRect& other); 
};

