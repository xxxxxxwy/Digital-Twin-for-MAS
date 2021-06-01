#ifndef _BCSH_UART1_H_
#define _BCSH_UART1_H_


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


#define UART1_DATAPACKAGE_HEAD1				0xF5
#define UART1_DATAPACKAGE_HEAD2				0x5F

#define UART1_DATAPACKAGE_MAXLENGTH	150
typedef struct 
{
	uchar devicetype;
	uchar devicecmd;
	uchar datalength;
	uchar data[UART1_DATAPACKAGE_MAXLENGTH];
	uchar checksumnot;
}UART1_DATAPACKAGE;

typedef void (*UART1_PACK_CallBack)(UART1_DATAPACKAGE *);

class BCSH_UART1CLASS
{
public:
//private:
	UART1_DATAPACKAGE Qrcode_pack;	//有效包存储
	uchar Qrcode_pack_read=0;	
	uchar Qrcode_pack_readok=0;

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
	void packsend_bytes(uint8 devicetype,uint8 devicecmd,uint8 *data,uint16 length );
	void packsend_d0(uint8 devicetype,uint8 devicecmd);
	void packsend_d1(uint8 devicetype,uint8 devicecmd,uint8 data);	
	void packsend_d2(uint8 devicetype,uint8 devicecmd,uint8 data1,uint8 data2);
	void Begin(ulong baud);
};

extern BCSH_UART1CLASS BCSH_Uart1;

#endif

