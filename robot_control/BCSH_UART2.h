#ifndef _BCSH_UART2_H_
#define _BCSH_UART2_H_


#ifndef uchar
#define uchar unsigned char
#endif

#ifndef int8
#define int8 signed char
#endif
#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef int16
#define int16 signed int
#endif
#ifndef uint16
#define uint16 unsigned int
#endif


#ifndef uint
#define uint unsigned int
#endif

#ifndef ulong
#define ulong	unsigned long
#endif 


#ifndef true
#define true 	1
#endif

#ifndef false
#define false 	0
#endif


#define UART2_DATAPACKAGE_HEAD1				0xF5
#define UART2_DATAPACKAGE_HEAD2				0x5F

#define UART2_DATAPACKAGE_MAXLENGTH	15
typedef struct 
{
	uchar devicetype;
	uchar devicecmd;
	uchar datalength;
	uchar data[UART2_DATAPACKAGE_MAXLENGTH];
	uchar checksumnot;
}UART2_DATAPACKAGE;

typedef void (*UART2_PACK_CallBack)(UART2_DATAPACKAGE *);


#define UART2_DATAPACKAGE_BUFF_MAXLENGTH	10
class BCSH_UART2CLASS
{
public:
//private:
	ulong Arduinobaud;
	void ArduinoSetBaud(ulong baud);
	ulong ArduinoGetBaud();
	void Write(uchar byte);
	void Write(uchar *str);
	void Write(uchar *value,uchar len);
	//
	void bytesCopy(uint8 *obj,uint8 *src,uint16 length);
	//
public:
	void PackSend(uint8 devicetype,uint8 devicecmd,uint8 *data,uint16 length);
	void PackSendD0(uint8 devicetype,uint8 devicecmd);
	void PackSendD1(uint8 devicetype,uint8 devicecmd,uint8 data);
	void PackSendD2(uint8 devicetype,uint8 devicecmd,uint8 data1,uint8 data2);
	void PackSendDS(uint8 devicetype,uint8 devicecmd,uint8 *data,uint16 length);
	UART2_PACK_CallBack Uart2PackCallback;
	void Begin(ulong baud,UART2_PACK_CallBack callback);
};

extern BCSH_UART2CLASS BCSH_Uart2;

#endif

