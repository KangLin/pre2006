#pragma once

// CCoordinate ����Ŀ��

class CCoordinate : public CObject
{
public:
	CCoordinate();
	virtual ~CCoordinate();

private:
	double m_X;
	double m_Y;
	double m_Scale;

};


