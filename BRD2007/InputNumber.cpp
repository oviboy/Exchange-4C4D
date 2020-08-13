// InputNumber.cpp : implementation file
//

#include "stdafx.h"
#include "brd2007.h"
#include "InputNumber.h"

// CInputNumber

IMPLEMENT_DYNAMIC(CInputNumber, CEdit)

CInputNumber::CInputNumber()
{
	number_of_decimal_points = 0;
	checkPoint=false;
}

CInputNumber::~CInputNumber()
{
}

BEGIN_MESSAGE_MAP(CInputNumber, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_CONTROL_REFLECT(EN_UPDATE, OnEnUpdate)
	ON_WM_SIZE()
	//WM_PASTE()
END_MESSAGE_MAP()

// CInputNumber message handlers

void CInputNumber::setData(int old_max, int number_of_decimal_points, int max_number_len) {
	this->old_max = old_max;
	this->number_of_decimal_points = number_of_decimal_points;
	this->max_number_len = max_number_len;
}

void CInputNumber::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  CString temp;

  this->GetWindowTextA(temp);
  if(temp.Find('.') == -1) {
    checkPoint = false; //There is no point
	this->max_number_len = old_max;
	//max_number_len-=1;
  }
  else {
    checkPoint = true; //There is a point
	this->max_number_len = old_max+1;
	//max_number_len+=1;
  }

  CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CInputNumber::setCheckPoint(bool cp)
{
	this->checkPoint = cp;
}

void CInputNumber::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == 0x08) {
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}
	if(nChar == '.' && checkPoint == true) //Is a point and there is already a point
  {
     return;
  }
  else if(nChar == '.' && checkPoint == false) //Is a point but there is no point
  {
    CEdit::OnChar(nChar, nRepCnt, nFlags);
  }
	int len = LineLength();
  if(len >= max_number_len)
	  return;

  if((nChar < '0' || nChar > '9') && nChar != 8) //Is not a number or backspace
  {
     return;
  }
  else //Valid
  {
     CEdit::OnChar(nChar, nRepCnt, nFlags);
  } 
	/*if(nChar == 0x08) {
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}
	int len = LineLength();
	CString str;
	this->GetWindowTextA(str);
	CString text;
	GetWindowText(text);

	//inlocuire selectie(daca exista) cu caracterul apasat
	int st = 0, en = 0;
	GetSel(st, en);
	if(en-st != 0)
		len -= (en-st);

	int line_index = GetSel();
	if(nChar == '.' &&  line_index == 0)
			return;
	if(nChar == '.' && number_of_decimal_points == 0) {
		max_number_len = old_max + 1;
	}

	if(len < max_number_len) {
		if((nChar < 0x30 || nChar > 0x39) && (nChar != '.')) {
			Beep(750, 200);
			return;
		}
		else if(nChar == '.') {
			number_of_decimal_points++;
			if(number_of_decimal_points != 1)
				return;
		}
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}*/
}

void CInputNumber::SetMaxLen(int max)
{
	max_number_len = max;
	old_max = max;
}

void CInputNumber::OnEnUpdate()
{
	CString text;
	GetWindowText(text);
	if(text.Find('.') == -1) {
		if(number_of_decimal_points > 0) {
			max_number_len -= 1;
		}
		number_of_decimal_points = 0;
		//max_number_len = old_max;
	}
	else {
		number_of_decimal_points++;
	}
}

void CInputNumber::OnSize(UINT nType, int cx, int cy)
{	
	CWnd::OnSize(nType, cx, cy);
	ModifyStyle(ES_LEFT, ES_RIGHT);
	Invalidate();
}
