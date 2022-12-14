// CRectObject.h
#pragma once
class CRectObject
{
public:
	CPoint m_pos; //사각형의 위치. 좌측 상단 꼭지점의 좌표
	int m_width; // 사각형의 가로 길이
	int m_height; // 사각형의 세로 높이
	bool m_selected; //사각형이 선택 되었는지 여부를 나타내는 플래그

public:
	CRectObject();
	CRectObject(CPoint pt, int w, int h, CString pa, CString na); // 
	bool CheckSelected(CPoint pt); // pt 좌표가 사각형 내부인지 체크.
	void Draw(CDC* pDC); //pDC에 사각형 그리기
	CString m_path;  // 이미지 경로
	CString m_name;  // 이름
	bool IsCollide(CRect& other); // 11
};

