#pragma once

// CInputNumber

class CInputNumber : public CEdit
{
	DECLARE_DYNAMIC(CInputNumber)
private:
	bool checkPoint;
	int max_number_len, old_max;
	int number_of_decimal_points;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	CInputNumber();
	virtual ~CInputNumber();
	void setCheckPoint(bool cp);
	void setData(int old_max, int number_of_decimal_points, int max_number_len);
	int getMaxLen() {
		return this->max_number_len;
	}

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnUpdate();
	void SetMaxLen(int max);
};
