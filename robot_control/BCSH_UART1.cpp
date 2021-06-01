
#include "arduino.h"
#include "BCSH_UART1.h"

/**********************************************************
*
*					
*			
************************************************************/
//*
//BCSHUART1_x		
#define BCSHUART1_1								//

#define BCSHUART1_OS_CLK				16000000		//
//#define BCSHUART1_UBRR		9600					//
#define BCSHUART1_BAUD_X2								//

#ifdef BCSHUART1_BAUD_X2
#define BCSHUART1_BAUD_COF				8				//
#else
#define BCSHUART1_BAUD_COF				16				//
#endif

#if		(defined BCSHUART1_0)
//UCSRxA	->		x=0,1,2 ����
#define BCSHUART1_REGA		UCSR0A					//�Ĵ���A
#define BCSHUART1_REGB		UCSR0B					//�Ĵ���B
#define BCSHUART1_REGC		UCSR0C					//�Ĵ���C
#define BCSHUART1_UBRRL		UBRR0L					//�����ʼĴ�����λ
#define BCSHUART1_UBRRH		UBRR0H					//�����ʼĴ�����λ
#define BCSHUART1_UDR		UDR0					//˫�����ݻ���Ĵ���	
#define BCSHUART1_ISR		USART0_RX_vect			//�ж�����
#elif	(defined BCSHUART1_1)
//UCSRxA	->		x=0,1,2 ����
#define BCSHUART1_REGA		UCSR1A					//�Ĵ���A
#define BCSHUART1_REGB		UCSR1B					//�Ĵ���B
#define BCSHUART1_REGC		UCSR1C					//�Ĵ���C
#define BCSHUART1_UBRRL		UBRR1L					//�����ʼĴ�����λ
#define BCSHUART1_UBRRH		UBRR1H					//�����ʼĴ�����λ
#define BCSHUART1_UDR		UDR1					//˫�����ݻ���Ĵ���	
#define BCSHUART1_ISR		USART1_RX_vect			//�ж�����
#elif	(defined BCSHUART1_2)
//UCSRxA	->		x=0,1,2 ����
#define BCSHUART1_REGA		UCSR2A					//�Ĵ���A
#define BCSHUART1_REGB		UCSR2B					//�Ĵ���B
#define BCSHUART1_REGC		UCSR2C					//�Ĵ���C
#define BCSHUART1_UBRRL		UBRR2L					//�����ʼĴ�����λ
#define BCSHUART1_UBRRH		UBRR2H					//�����ʼĴ�����λ
#define BCSHUART1_UDR		UDR2					//˫�����ݻ���Ĵ���
#define BCSHUART1_ISR		USART2_RX_vect			//�ж�����
#elif	(defined BCSHUART1_3)
#define BCSHUART1_REGA		UCSR3A					//�Ĵ���A
#define BCSHUART1_REGB		UCSR3B					//�Ĵ���B
#define BCSHUART1_REGC		UCSR3C					//�Ĵ���C
#define BCSHUART1_UBRRL		UBRR3L					//�����ʼĴ�����λ
#define BCSHUART1_UBRRH		UBRR3H					//�����ʼĴ�����λ
#define BCSHUART1_UDR		UDR3					//˫�����ݻ���Ĵ���
#define BCSHUART1_ISR		USART3_RX_vect			//�ж�����
#else
#define BCSHUART1_REGA
#define BCSHUART1_REGB
#define BCSHUART1_REGC
#define BCSHUART1_UBRRL
#define BCSHUART1_UBRRH
#define BCSHUART1_UDR
#define BCSHUART1_ISR
#endif


//�Ĵ���A--------REGA
#define BCSHUART1_REGA_RXC			0x80					//
#define BCSHUART1_REGA_TXC			0x40
#define BCSHUART1_REGA_UDRE			0x20
#define BCSHUART1_REGA_FE			0x10
#define BCSHUART1_REGA_DOR			0x08
#define BCSHUART1_REGA_PE			0x04
#define BCSHUART1_REGA_U2X			0x02
#define BCSHUART1_REGA_MPCM			0x01
//bit
#define BCSHUART1_REGA_RXC_B		0x07
#define BCSHUART1_REGA_TXC_B		0x06
#define BCSHUART1_REGA_UDRE_B		0x05
#define BCSHUART1_REGA_FE_B			0x04
#define BCSHUART1_REGA_DOR_B		0x03
#define BCSHUART1_REGA_PE_B			0x02
#define BCSHUART1_REGA_U2X_B		0x01
#define BCSHUART1_REGA_MPCM_B		0x00

//�Ĵ���B--------REGB
#define BCSHUART1_REGB_RXCIE		0x80
#define BCSHUART1_REGB_TXCIE		0x40
#define BCSHUART1_REGB_UDRIE		0x20
#define BCSHUART1_REGB_RXEN			0x10
#define BCSHUART1_REGB_TXEN			0x08
#define BCSHUART1_REGB_UCSZ2		0x04
#define BCSHUART1_REGB_RXB8			0x02
#define BCSHUART1_REGB_TXB8			0x01
//bit
#define BCSHUART1_REGB_RXCIE_B		0x07
#define BCSHUART1_REGB_TXCIE_B		0x06
#define BCSHUART1_REGB_UDRIE_B		0x05
#define BCSHUART1_REGB_RXEN_B		0x04
#define BCSHUART1_REGB_TXEN_B		0x03
#define BCSHUART1_REGB_UCSZ2_B		0x02
#define BCSHUART1_REGB_RXB8_B		0x01
#define BCSHUART1_REGB_TXB8_B		0x00

//�Ĵ���C--------REGC
#define BCSHUART1_REGC_URSEL		0x80
#define BCSHUART1_REGC_UMSEL		0x40
#define BCSHUART1_REGC_UUPM1		0x20
#define BCSHUART1_REGC_UPM0			0x10
#define BCSHUART1_REGC_USBS			0x08
#define BCSHUART1_REGC_UCSZ1		0x04
#define BCSHUART1_REGC_UCSZ0		0x02
#define BCSHUART1_REGC_UCPOL		0x01
//bit
#define BCSHUART1_REGC_URSEL_B		0x07
#define BCSHUART1_REGC_UMSEL_B		0x06
#define BCSHUART1_REGC_UUPM1_B		0x05
#define BCSHUART1_REGC_UPM0_B		0x04
#define BCSHUART1_REGC_USBS_B		0x03
#define BCSHUART1_REGC_UCSZ1_B		0x02
#define BCSHUART1_REGC_UCSZ0_B		0x01
#define BCSHUART1_REGC_UCPOL_B		0x00
//*/
//*
BCSH_UART1CLASS BCSH_Uart1;


void BCSH_UART1CLASS::ArduinoSetBaud(ulong baud)
{
	#ifdef BCSHUART1_BAUD_X2
	bitSet(BCSHUART1_REGA,BCSHUART1_REGA_U2X_B	);						//�����ʼӱ�
	#else
	bitClear(BCSHUART1_REGA,BCSHUART1_REGA_U2X_B);						//�����ʲ��ӱ�
	#endif
	bitSet(BCSHUART1_REGB,BCSHUART1_REGB_RXCIE_B);                     	//�����������ж�
  	bitSet(BCSHUART1_REGB,BCSHUART1_REGB_RXEN_B);                      	//������չ���
  	bitSet(BCSHUART1_REGB,BCSHUART1_REGB_TXEN_B);                      	//�����͹���
  	bitClear(BCSHUART1_REGB,BCSHUART1_REGB_UCSZ2_B);               		//λ2,1,0����ͨ������λ��Ϊ8λ
  	bitSet(BCSHUART1_REGC,BCSHUART1_REGC_UCSZ1_B);                   	//λ2,1,0����ͨ������λ��Ϊ8λ
  	bitSet(BCSHUART1_REGC,BCSHUART1_REGC_UCSZ0_B);            			//λ2,1,0����ͨ������λ��Ϊ8λ
  	bitClear(BCSHUART1_REGC,BCSHUART1_REGC_UMSEL_B);                   	//�첽ģʽ
  	
  	#ifdef BCSHUART1_UBRR
	Arduinobaud=BCSHUART1_UBRR;
  	BCSHUART1_UBRRL=  (BCSHUART1_OS_CLK/BCSHUART1_BAUD_COF/BCSHUART1_UBRR-1)%0x100;     		//�����ʵ�λ
  	BCSHUART1_UBRRH=(((BCSHUART1_OS_CLK/BCSHUART1_BAUD_COF/BCSHUART1_UBRR-1)>>8)&0x0F); 		//�����ʸ�λ
  	#else
	Arduinobaud=baud;
  	BCSHUART1_UBRRL=  (BCSHUART1_OS_CLK/BCSHUART1_BAUD_COF/baud-1)%0x100;     					//�����ʵ�λ
  	BCSHUART1_UBRRH=(((BCSHUART1_OS_CLK/BCSHUART1_BAUD_COF/baud-1)>>8)&0x0F); 					//�����ʸ�λ
  	#endif
}

ulong BCSH_UART1CLASS::ArduinoGetBaud()
{
	return Arduinobaud;
}

//
void BCSH_UART1CLASS::Write(uchar byte)
{
  while(!(BCSHUART1_REGA&BCSHUART1_REGA_UDRE));
  BCSHUART1_UDR=byte;
  while(!(BCSHUART1_REGA&BCSHUART1_REGA_TXC));
  bitSet(BCSHUART1_REGA,BCSHUART1_REGA_TXC_B);
}
void BCSH_UART1CLASS::Write(uchar *str)
{
	uint len = 0;
	for (len=0;*(str+len)!=0;len++)
	{
		Write(*(str+len));
	}
}
void BCSH_UART1CLASS::Write(uchar *value,uchar len)
{
	uint i = 0;
	for (i=0;i<len;i++)
	{
		Write(*(value+i));
	}
}

void BCSH_UART1CLASS::bytesCopy(uint8 *obj,uint8 *src,uint16 length)
{
	uint16 i;
	for(i=0;i<length;i++)
	{
		obj[i]=src[i];
	}
}

void BCSH_UART1CLASS::packsend_bytes(uint8 devicetype,uint8 devicecmd,uint8 *data,uint16 length)
{
	uint8 sum_not=0;
	uint8 i=0;
	Write(UART1_DATAPACKAGE_HEAD1);
	Write(UART1_DATAPACKAGE_HEAD2);
	Write(devicetype);	sum_not=devicetype;
	Write(devicecmd);	sum_not+=devicecmd;
	Write(length);	sum_not+=length;
	for(i=0;i<length;i++)
	{
		Write(data[i]);
		sum_not+=data[i];
	}
	sum_not=~sum_not;
	Write(sum_not);
}

void BCSH_UART1CLASS::packsend_d0(uint8 devicetype,uint8 devicecmd)
{
	packsend_bytes(devicetype,devicecmd,0,0);
}

void BCSH_UART1CLASS::packsend_d1(uint8 devicetype,uint8 devicecmd,uint8 data)
{
	packsend_bytes(devicetype,devicecmd,&data,1);
}
void BCSH_UART1CLASS::packsend_d2(uint8 devicetype,uint8 devicecmd,uint8 data1,uint8 data2)
{
	uint8 value[2];
	value[0]=data1;
	value[1]=data2;	
	packsend_bytes(devicetype,devicecmd,value,2);
}

//========================================================

void BCSH_UART1CLASS::Begin(ulong baud)
{
	ArduinoSetBaud(baud);
	Qrcode_pack_read=1;	
	Qrcode_pack_readok=0;
}

//
uchar BCSH_UART1IRQstep=0;					
uchar BCSH_UART1IRQdata=0;
uchar BCSH_UART1DataSit=0;
UART1_DATAPACKAGE uart1_datapackage;//临时包存储

//*/
//*
#if (defined BCSHUART1_0) || (defined BCSHUART1_1) || (defined BCSHUART1_2) || (defined BCSHUART1_3)

ISR(BCSHUART1_ISR)                     
{
	BCSH_UART1IRQdata=BCSHUART1_UDR;
	switch(BCSH_UART1IRQstep)
	{
		case 0:
		if(BCSH_UART1IRQdata==UART1_DATAPACKAGE_HEAD1)BCSH_UART1IRQstep=10;
		break;
		//
		case 10:
		if(BCSH_UART1IRQdata==UART1_DATAPACKAGE_HEAD2)BCSH_UART1IRQstep=20;
		else if(BCSH_UART1IRQdata!=UART1_DATAPACKAGE_HEAD1)BCSH_UART1IRQstep=0;
		break;
		//
		case 20:
		uart1_datapackage.checksumnot=BCSH_UART1IRQdata;
		uart1_datapackage.devicetype=BCSH_UART1IRQdata;
		BCSH_UART1IRQstep=30;
		break;
		//
		case 30:
		uart1_datapackage.checksumnot+=BCSH_UART1IRQdata;
		uart1_datapackage.devicecmd=BCSH_UART1IRQdata;
		BCSH_UART1IRQstep=40;
		break;
		//
		case 40:
		uart1_datapackage.checksumnot+=BCSH_UART1IRQdata;
		uart1_datapackage.datalength=BCSH_UART1IRQdata;
		if(BCSH_UART1IRQdata>UART1_DATAPACKAGE_MAXLENGTH)BCSH_UART1IRQstep=0;
		else if(BCSH_UART1IRQdata==0)BCSH_UART1IRQstep=60;
		else BCSH_UART1IRQstep=50;
		BCSH_UART1DataSit=0;
		break;
		//
		case 50:
		uart1_datapackage.checksumnot+=BCSH_UART1IRQdata;
		uart1_datapackage.data[BCSH_UART1DataSit]=BCSH_UART1IRQdata;
		BCSH_UART1DataSit++;
		if(BCSH_UART1DataSit>=uart1_datapackage.datalength)
		{
			BCSH_UART1IRQstep=60;
		}
		break;
		//
		case 60:
		uart1_datapackage.checksumnot=~uart1_datapackage.checksumnot;
		if(uart1_datapackage.checksumnot==BCSH_UART1IRQdata)
		{
			//判断当前数据包是否是二维码命令
			if(BCSH_Uart1.Qrcode_pack_read==1&&uart1_datapackage.devicetype==0x09&&uart1_datapackage.devicecmd==0x50)
			{
				BCSH_Uart1.Qrcode_pack=uart1_datapackage;
				BCSH_Uart1.Qrcode_pack_read=0;
				BCSH_Uart1.Qrcode_pack_readok=1;
			}
		}
		BCSH_UART1IRQstep=0;
		break;
		//
		default:BCSH_UART1IRQstep=0;break;	
	}
}
#endif
//*/

