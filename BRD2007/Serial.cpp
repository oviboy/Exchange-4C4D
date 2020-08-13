#include "StdAfx.h"
#include ".\serial.h"

CSerial::CSerial(void)
{
	f = NULL;
}

CSerial::~CSerial(void)
{
	f = NULL;
}
void CSerial::Open(char *comPort, DWORD baud_rate, BYTE parity, BYTE stop_bits, BYTE byte_size)
{
	char com[255];
	sprintf_s(com, sizeof(com), "\\\\.\\%s", comPort);
	f = CreateFile((LPCSTR)com, GENERIC_WRITE|GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(f != INVALID_HANDLE_VALUE) {
		//setez parametrii de comunicare 1200,8N1
		DCB dcb;
		GetCommState(f, &dcb);		//get default values
		dcb.DCBlength = sizeof(DCB);
		
		dcb.BaudRate = baud_rate; 
		dcb.fBinary = TRUE;
		dcb.ByteSize = byte_size;
		dcb.Parity = parity; 
		dcb.StopBits = stop_bits;
		SetCommState(f, &dcb);

		//setez parametrii de timeout (las implicit 5000 si 100)
		SetComTimeout();
	}
	else {
		AfxMessageBox(_T("Nu pot deschide portul serial !"));
		SendMessage(NULL, WM_CLOSE, NULL, NULL);
	}
}

BOOL CSerial::SetComTimeout(unsigned int read, unsigned int write)
{
	COMMTIMEOUTS CommTimeouts;
	GetCommTimeouts(f, &CommTimeouts);
	CommTimeouts.ReadIntervalTimeout = 100;  
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
	CommTimeouts.ReadTotalTimeoutConstant = read;  

	CommTimeouts.WriteTotalTimeoutMultiplier = 100;  
	CommTimeouts.WriteTotalTimeoutConstant = write;
	return SetCommTimeouts(f, &CommTimeouts);
}

void CSerial::Close()
{
	if(f != NULL)
		CloseHandle(f);
}

int CSerial::Send(unsigned char *data, DWORD len)
{
	DWORD bytes_written = 0L;
	int result = 0;
	BOOL rez = FALSE;

	if(f != NULL) {
		rez = WriteFile(f, data, len, &bytes_written, NULL);
		if(!rez)
			result = -1;
		FlushFileBuffers(f);
	}
	
	if(result != 0)	{
		char a[10];
		memset(a, 0x00, 10);
		sprintf_s(a, sizeof(a), "%d", result);
		//itoa(result, a, 10);
		AfxMessageBox(_T("Eroare de transmisie: ") + CString(a));
	}

	return result;
}

int CSerial::Receive(unsigned char *data, unsigned long len, unsigned int timeout)
{
	int result = 0;						//SUCCESS
	unsigned long bytes_read = 0;
	BOOL rez = FALSE;
	unsigned long index = 0;
	unsigned char *rx;
	unsigned char ch;

	if(f != NULL) {
		if(SetComTimeout(timeout, 100) != 0)	
			return -1;						//eroare la setarea timeout-ului

		rx = (unsigned char*)malloc(len + 1);

		while(index < len) {
			//citesc octet cu octet daca len > 1
			rez = ReadFile(f, &ch, 1, &bytes_read, NULL);
			if(rez) {
				if(bytes_read == 1) {			//SUCCESS
					rx[index] = ch;
					rx[index + 1] = 0x0;
					result = 0;
				}
				else if(bytes_read != len) {	//timeout la citire
					result = -2;		
					break;
				}
				else if(bytes_read == 0)
					result = -3;			//eroare de transmisie
			}
			else {
				result = -99;				//eroare necunoscuta
			}
			index++;
		}
	}
	else
		result = -5;						//portul serial nu a fost deschis

	if(index == len) {
		memcpy((unsigned char*)data, (unsigned char*)rx, len);
		free(rx);
	}

	return result;
}
