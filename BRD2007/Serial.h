#pragma once

class CSerial
{
	HANDLE f;
public:
	CSerial(void);
	~CSerial(void);

	void Open(char *comPort, DWORD baud_rate = CBR_9600, BYTE parity = NOPARITY, BYTE stop_bits = ONESTOPBIT, BYTE byte_size = 8);
	void Close();
	BOOL SetComTimeout(unsigned int read = 5000, unsigned int write = 100);
	int Send(unsigned char *data, DWORD len);
	int Receive(unsigned char *data, unsigned long len, unsigned int timeout = 5000);
};
