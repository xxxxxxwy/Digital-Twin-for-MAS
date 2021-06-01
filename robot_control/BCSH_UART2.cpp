
#include "arduino.h"
#include "BCSH_UART2.h"

/**********************************************************
*
*					
*			
************************************************************/
//*
//BCSHUART2_x		
#define BCSHUART2_2								//

#define BCSHUART2_OS_CLK				16000000		//
//#define BCSHUART2_UBRR		9600					//
#define BCSHUART2_BAUD_X2								//

#ifdef BCSHUART2_BAUD_X2
#define BCSHUART2_BAUD_COF				8				//
#else
#define BCSHUART2_BAUD_COF				16				//
#endif

#if		(defined BCSHUART2_0)
//UCSRxA	->		x=0,1,2 ����
#define BCSHUART2_REGA		UCSR0A					//�Ĵ���A
#define BCSHUART2_REGB		UCSR0B					//�Ĵ���B
#define BCSHUART2_REGC		UCSR0C					//�Ĵ���C
#define BCSHUART2_UBRRL		UBRR0L					//�����ʼĴ�����λ
#define BCSHUART2_UBRRH		UBRR0H					//�����ʼĴ�����λ
#define BCSHUART2_UDR		UDR0					//˫�����ݻ���Ĵ���	
#define BCSHUART2_ISR		USART0_RX_vect			//�ж�����
#elif	(defined BCSHUART2_1)
//UCSRxA	->		x=0,1,2 ����
#define BCSHUART2_REGA		UCSR1A					//�Ĵ���A
#define BCSHUART2_REGB		UCSR1B					//�Ĵ���B
#define BCSHUART2_REGC		UCSR1C					//�Ĵ���C
#define BCSHUART2_UBRRL		UBRR1L					//�����ʼĴ�����λ
#define BCSHUART2_UBRRH		UBRR1H					//�����ʼĴ�����λ
#define BCSHUART2_UDR		UDR1					//˫�����ݻ���Ĵ���	
#define BCSHUART2_ISR		USART1_RX_vect			//�ж�����
#elif	(defined BCSHUART2_2)
//UCSRxA	->		x=0,1,2 ����
#define BCSHUART2_REGA		UCSR2A					//�Ĵ���A
#define BCSHUART2_REGB		UCSR2B					//�Ĵ���B
#define BCSHUART2_REGC		UCSR2C					//�Ĵ���C
#define BCSHUART2_UBRRL		UBRR2L					//�����ʼĴ�����λ
#define BCSHUART2_UBRRH		UBRR2H					//�����ʼĴ�����λ
#define BCSHUART2_UDR		UDR2					//˫�����ݻ���Ĵ���
#define BCSHUART2_ISR		USART2_RX_vect			//�ж�����
#elif	(defined BCSHUART2_3)
#define BCSHUART2_REGA		UCSR3A					//�Ĵ���A
#define BCSHUART2_REGB		UCSR3B					//�Ĵ���B
#define BCSHUART2_REGC		UCSR3C					//�Ĵ���C
#define BCSHUART2_UBRRL		UBRR3L					//�����ʼĴ�����λ
#define BCSHUART2_UBRRH		UBRR3H					//�����ʼĴ�����λ
#define BCSHUART2_UDR		UDR3					//˫�����ݻ���Ĵ���
#define BCSHUART2_ISR		USART3_RX_vect			//�ж�����
#else
#define BCSHUART2_REGA
#define BCSHUART2_REGB
#define BCSHUART2_REGC
#define BCSHUART2_UBRRL
#define BCSHUART2_UBRRH
#define BCSHUART2_UDR
#define BCSHUART2_ISR
#endif


//�Ĵ���A--------REGA
#define BCSHUART2_REGA_RXC			0x80					//
#define BCSHUART2_REGA_TXC			0x40
#define BCSHUART2_REGA_UDRE			0x20
#define BCSHUART2_REGA_FE			0x10
#define BCSHUART2_REGA_DOR			0x08
#define BCSHUART2_REGA_PE			0x04
#define BCSHUART2_REGA_U2X			0x02
#define BCSHUART2_REGA_MPCM			0x01
//bit
#define BCSHUART2_REGA_RXC_B		0x07
#define BCSHUART2_REGA_TXC_B		0x06
#define BCSHUART2_REGA_UDRE_B		0x05
#define BCSHUART2_REGA_FE_B			0x04
#define BCSHUART2_REGA_DOR_B		0x03
#define BCSHUART2_REGA_PE_B			0x02
#define BCSHUART2_REGA_U2X_B		0x01
#define BCSHUART2_REGA_MPCM_B		0x00

//�Ĵ���B--------REGB
#define BCSHUART2_REGB_RXCIE		0x80
#define BCSHUART2_REGB_TXCIE		0x40
#define BCSHUART2_REGB_UDRIE		0x20
#define BCSHUART2_REGB_RXEN			0x10
#define BCSHUART2_REGB_TXEN			0x08
#define BCSHUART2_REGB_UCSZ2		0x04
#define BCSHUART2_REGB_RXB8			0x02
#define BCSHUART2_REGB_TXB8			0x01
//bit
#define BCSHUART2_REGB_RXCIE_B		0x07
#define BCSHUART2_REGB_TXCIE_B		0x06
#define BCSHUART2_REGB_UDRIE_B		0x05
#define BCSHUART2_REGB_RXEN_B		0x04
#define BCSHUART2_REGB_TXEN_B		0x03
#define BCSHUART2_REGB_UCSZ2_B		0x02
#define BCSHUART2_REGB_RXB8_B		0x01
#define BCSHUART2_REGB_TXB8_B		0x00

//�Ĵ���C--------REGC
#define BCSHUART2_REGC_URSEL		0x80
#define BCSHUART2_REGC_UMSEL		0x40
#define BCSHUART2_REGC_UUPM1		0x20
#define BCSHUART2_REGC_UPM0			0x10
#define BCSHUART2_REGC_USBS			0x08
#define BCSHUART2_REGC_UCSZ1		0x04
#define BCSHUART2_REGC_UCSZ0		0x02
#define BCSHUART2_REGC_UCPOL		0x01
//bit
#define BCSHUART2_REGC_URSEL_B		0x07
#define BCSHUART2_REGC_UMSEL_B		0x06
#define BCSHUART2_REGC_UUPM1_B		0x05
#define BCSHUART2_REGC_UPM0_B		0x04
#define BCSHUART2_REGC_USBS_B		0x03
#define BCSHUART2_REGC_UCSZ1_B		0x02
#define BCSHUART2_REGC_UCSZ0_B		0x01
#define BCSHUART2_REGC_UCPOL_B		0x00
//*/

BCSH_UART2CLASS BCSH_Uart2;


union FloatToArray
{
	float value_float;
	uchar value_array[4];
};



void BCSH_UART2CLASS::ArduinoSetBaud(ulong baud)
{
	#ifdef BCSHUART2_BAUD_X2
	bitSet(BCSHUART2_REGA,BCSHUART2_REGA_U2X_B	);						//�����ʼӱ�
	#else
	bitClear(BCSHUART2_REGA,BCSHUART2_REGA_U2X_B);						//�����ʲ��ӱ�
	#endif
	bitSet(BCSHUART2_REGB,BCSHUART2_REGB_RXCIE_B);                     	//�����������ж�
  	bitSet(BCSHUART2_REGB,BCSHUART2_REGB_RXEN_B);                      	//������չ���
  	bitSet(BCSHUART2_REGB,BCSHUART2_REGB_TXEN_B);                      	//�����͹���
  	bitClear(BCSHUART2_REGB,BCSHUART2_REGB_UCSZ2_B);               		//λ2,1,0����ͨ������λ��Ϊ8λ
  	bitSet(BCSHUART2_REGC,BCSHUART2_REGC_UCSZ1_B);                   	//λ2,1,0����ͨ������λ��Ϊ8λ
  	bitSet(BCSHUART2_REGC,BCSHUART2_REGC_UCSZ0_B);            			//λ2,1,0����ͨ������λ��Ϊ8λ
  	bitClear(BCSHUART2_REGC,BCSHUART2_REGC_UMSEL_B);                   	//�첽ģʽ
  	
  	#ifdef BCSHUART2_UBRR
	Arduinobaud=BCSHUART2_UBRR;
  	BCSHUART2_UBRRL=  (BCSHUART2_OS_CLK/BCSHUART2_BAUD_COF/BCSHUART2_UBRR-1)%0x100;     		//�����ʵ�λ
  	BCSHUART2_UBRRH=(((BCSHUART2_OS_CLK/BCSHUART2_BAUD_COF/BCSHUART2_UBRR-1)>>8)&0x0F); 		//�����ʸ�λ
  	#else
	Arduinobaud=baud;
  	BCSHUART2_UBRRL=  (BCSHUART2_OS_CLK/BCSHUART2_BAUD_COF/baud-1)%0x100;     					//�����ʵ�λ
  	BCSHUART2_UBRRH=(((BCSHUART2_OS_CLK/BCSHUART2_BAUD_COF/baud-1)>>8)&0x0F); 					//�����ʸ�λ
  	#endif
}

ulong BCSH_UART2CLASS::ArduinoGetBaud()
{
	return Arduinobaud;
}

//
void BCSH_UART2CLASS::Write(uchar byte)
{
  while(!(BCSHUART2_REGA&BCSHUART2_REGA_UDRE));
  BCSHUART2_UDR=byte;
  while(!(BCSHUART2_REGA&BCSHUART2_REGA_TXC));
  bitSet(BCSHUART2_REGA,BCSHUART2_REGA_TXC_B);
}
void BCSH_UART2CLASS::Write(uchar *str)
{
	uint len = 0;
	for (len=0;*(str+len)!=0;len++)
	{
		Write(*(str+len));
	}
}
void BCSH_UART2CLASS::Write(uchar *value,uchar len)
{
	uint i = 0;
	for (i=0;i<len;i++)
	{
		Write(*(value+i));
	}
}

void BCSH_UART2CLASS::bytesCopy(uint8 *obj,uint8 *src,uint16 length)
{
	uint16 i;
	for(i=0;i<length;i++)
	{
		obj[i]=src[i];
	}
}


void BCSH_UART2CLASS::PackSend(uint8 devicetype,uint8 devicecmd,uint8 *data,uint16 length)
{
	uint8 sum_not=0;
	uint8 i=0;
	Write(UART2_DATAPACKAGE_HEAD1);
	Write(UART2_DATAPACKAGE_HEAD2);
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


void BCSH_UART2CLASS::PackSendD0(uint8 devicetype,uint8 devicecmd)
{
	PackSend(devicetype,devicecmd,0,0);
}

void BCSH_UART2CLASS::PackSendD1(uint8 devicetype,uint8 devicecmd,uint8 data)
{
	PackSend(devicetype,devicecmd,&data,1);
}
void BCSH_UART2CLASS::PackSendD2(uint8 devicetype,uint8 devicecmd,uint8 data1,uint8 data2)
{
	uint8 value[2];
	value[0]=data1;
	value[1]=data2;	
	PackSend(devicetype,devicecmd,value,2);
}
void BCSH_UART2CLASS::PackSendDS(uint8 devicetype,uint8 devicecmd,uint8 *data,uint16 length)
{
	PackSend(devicetype,devicecmd,data,length);
}

//========================================================

void BCSH_UART2CLASS::Begin(ulong baud,UART2_PACK_CallBack callback)
{
	ArduinoSetBaud(baud);
	Uart2PackCallback=callback;
}

//
uchar BCSH_UART2IRQstep=0;					
uchar BCSH_UART2IRQdata=0;
uchar BCSH_UART2DataSit=0;
UART2_DATAPACKAGE uart2_datapackage;
//*
#if (defined BCSHUART2_0) || (defined BCSHUART2_1) || (defined BCSHUART2_2) || (defined BCSHUART2_3)

ISR(BCSHUART2_ISR)                     
{

	BCSH_UART2IRQdata=BCSHUART2_UDR;
	switch(BCSH_UART2IRQstep)
	{
		case 0:
		if(BCSH_UART2IRQdata==UART2_DATAPACKAGE_HEAD1)BCSH_UART2IRQstep=10;
		break;
		//
		case 10:
		if(BCSH_UART2IRQdata==UART2_DATAPACKAGE_HEAD2)BCSH_UART2IRQstep=20;
		else if(BCSH_UART2IRQdata!=UART2_DATAPACKAGE_HEAD1)BCSH_UART2IRQstep=0;
		break;
		//
		case 20:
		uart2_datapackage.checksumnot=BCSH_UART2IRQdata;
		uart2_datapackage.devicetype=BCSH_UART2IRQdata;
		BCSH_UART2IRQstep=30;
		break;
		//
		case 30:
		uart2_datapackage.checksumnot+=BCSH_UART2IRQdata;
		uart2_datapackage.devicecmd=BCSH_UART2IRQdata;
		BCSH_UART2IRQstep=40;
		break;
		//
		case 40:
		uart2_datapackage.checksumnot+=BCSH_UART2IRQdata;
		uart2_datapackage.datalength=BCSH_UART2IRQdata;
		if(BCSH_UART2IRQdata>UART2_DATAPACKAGE_MAXLENGTH)BCSH_UART2IRQstep=0;
		else if(BCSH_UART2IRQdata==0)BCSH_UART2IRQstep=60;
		else BCSH_UART2IRQstep=50;
		BCSH_UART2DataSit=0;
		break;
		//
		case 50:
		uart2_datapackage.checksumnot+=BCSH_UART2IRQdata;
		uart2_datapackage.data[BCSH_UART2DataSit]=BCSH_UART2IRQdata;
		BCSH_UART2DataSit++;
		if(BCSH_UART2DataSit>=uart2_datapackage.datalength)
		{
			BCSH_UART2IRQstep=60;
		}
		break;
		//
		case 60:
		uart2_datapackage.checksumnot=~uart2_datapackage.checksumnot;
		if(uart2_datapackage.checksumnot==BCSH_UART2IRQdata)
		{
			if(BCSH_Uart2.Uart2PackCallback)
			{
				BCSH_Uart2.Uart2PackCallback(&uart2_datapackage);
			}
		}
		BCSH_UART2IRQstep=0;
		break;
		//
		default:BCSH_UART2IRQstep=0;break;	
	}
}
#endif
//*/

