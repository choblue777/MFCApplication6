// CRectObject.h
#pragma once
class CRectObject
{
public:
	CPoint m_pos; //�簢���� ��ġ. ���� ��� �������� ��ǥ
	int m_width; // �簢���� ���� ����
	int m_height; // �簢���� ���� ����
	bool m_selected; //�簢���� ���� �Ǿ����� ���θ� ��Ÿ���� �÷���

public:
	CRectObject();
	CRectObject(CPoint pt, int w, int h, CString pa, CString na); // 
	bool CheckSelected(CPoint pt); // pt ��ǥ�� �簢�� �������� üũ.
	void Draw(CDC* pDC); //pDC�� �簢�� �׸���
	CString m_path;  // �̹��� ���
	CString m_name;  // �̸�
	bool IsCollide(CRect& other); // 11
};

