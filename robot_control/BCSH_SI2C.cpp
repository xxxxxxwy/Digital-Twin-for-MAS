/***************************************************
*
*	����:LH

*	2016-12-01
*	����I2CЭ���ͨ
				   
*	2016-12-26
*	����:
	uchar Write_Data(uchar deviceadd,uchar add,uchar data);
	uchar Write_Datas(uchar deviceadd,uchar add,uchar *data,uchar datelen);
*
*
*
*
*
****************************************************/

#include "arduino.h"
#include "BCSH_SI2C.h"

/***************************************************
*
*					ģ��I2C
*		 �ײ�˽�����Ա��������ֲʱ�޸�
****************************************************/
void SI2C::SDAINPUT()
{
	pinMode(SDA, INPUT);
}
void SI2C::SDAOUTPUT()
{
	pinMode(SDA, OUTPUT);
}
void SI2C::SCLINPUT()
{
	pinMode(SCL, INPUT);
}
void SI2C::SCLOUTPUT()
{
	pinMode(SCL, OUTPUT);
}


uchar SI2C::SdaIN()
{
	return digitalRead(SDA);
}
void SI2C::SdaOUT(uchar dat)
{
	if(dat==0)digitalWrite(SDA, LOW);
	else digitalWrite(SDA, HIGH);
}
void SI2C::SdaoutHIGH()
{
	digitalWrite(SDA, HIGH);
}
void SI2C::SdaoutLOW()
{
	digitalWrite(SDA, LOW);
}


uchar SI2C::SclIN()
{
	return digitalRead(SCL);
}
void SI2C::SclOUT(uchar dat)
{
	if(dat==0)digitalWrite(SCL, LOW);
	else digitalWrite(SCL, HIGH);
}
void SI2C::ScloutHIGH()
{
	digitalWrite(SCL, HIGH);
}
void SI2C::ScloutLOW()
{
	digitalWrite(SCL, LOW);
}


/***************************************************
*
*					ģ��I2C
*				�������Ա����
****************************************************/
void SI2C::Begin(uchar sda,uchar scl)
{
	SDA=sda;
	SCL=scl;
	acktimeout=100;
	delaytime=2;
	SCLOUTPUT();
	SDAOUTPUT();
}

void SI2C::AcktimeoutWrite(uint timeout)
{
	acktimeout=timeout;
}
uint SI2C::AcktimeoutRead()
{
	return acktimeout;
}
void SI2C::DelaytimeWrite(uchar time)
{
	delaytime=time;
}
uchar SI2C::DelaytimeRead()
{
	return delaytime;
}


void SI2C::Start()
{
	SCLOUTPUT();
	SDAOUTPUT();
	SdaoutHIGH();	delayMicroseconds(delaytime);
	ScloutHIGH();	delayMicroseconds(delaytime);
	SdaoutLOW();	delayMicroseconds(delaytime);
	ScloutLOW();	
}
void SI2C::Stop()
{
	SDAOUTPUT();
	SdaoutLOW();	delayMicroseconds(delaytime);
	ScloutHIGH();	delayMicroseconds(delaytime);
	SdaoutHIGH();	delayMicroseconds(delaytime);
	ScloutLOW();
}
uchar SI2C::WaitAck()
{
	uint timeout=0;
	SDAINPUT();
	SdaoutHIGH();	delayMicroseconds(delaytime);

	ScloutHIGH();	delayMicroseconds(delaytime);
	while(SdaIN()!=LOW)
	{
		delayMicroseconds(1);
		timeout++;
		if(timeout>=acktimeout)
		{
			return 0;
		}
	}
	ScloutLOW();	delayMicroseconds(delaytime);
	return 1;
}

void SI2C::SendAck()
{
	ScloutLOW();	delayMicroseconds(delaytime);
	SDAOUTPUT();
	SdaoutLOW();	delayMicroseconds(delaytime);
	ScloutHIGH();	delayMicroseconds(delaytime);
	ScloutLOW();
}

void SI2C::SendNAck()
{
	ScloutLOW();	delayMicroseconds(delaytime);
	SDAOUTPUT();
	SdaoutHIGH();	delayMicroseconds(delaytime);
	ScloutHIGH();	delayMicroseconds(delaytime);
	ScloutLOW();
}

void SI2C::WriteByte(uchar dat)
{
	int i=8;
	while(i--)
	{
		ScloutLOW();delayMicroseconds(delaytime);
		SDAOUTPUT();
		if(dat&0x80)
		{
			SdaoutHIGH();
		}
		else SdaoutLOW();
		delayMicroseconds(delaytime);
		dat<<=1;
		ScloutHIGH();delayMicroseconds(delaytime);
	}
	ScloutLOW();
}

uchar SI2C::ReadByte()
{
	uchar dat=0;
	uchar i=8;
	while(i--)
	{
		dat<<=1;
		ScloutLOW();delayMicroseconds(delaytime);
		SDAINPUT();
		ScloutHIGH();delayMicroseconds(delaytime);
		if(SdaIN())
		{
			dat+=1;
		}
	}
	ScloutLOW();
	return dat;
}


uchar SI2C::Write_Data(uchar deviceadd,uchar add,uchar data)
{
	Start();
	WriteByte(deviceadd&0xFE);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	WriteByte(add);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	WriteByte(data);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	Stop();
	return 1;
}

uchar SI2C::Write_Datas(uchar deviceadd,uchar add,uchar *data,uchar datelen)
{
	uchar i=0;
	Start();
	WriteByte(deviceadd&0xFE);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	WriteByte(add);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	for(i=0;i<datelen;i++)
	{
		WriteByte(*(data+i));
		if(WaitAck()==0)
		{
			Stop();
			return 0;
		}
	}
	Stop();
	return 1;
}

uchar SI2C::Read_Data(uchar deviceadd,uchar add,uchar *data)
{
	Start();
	WriteByte(deviceadd&0xFE);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	WriteByte(add);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	Start();
	//
	//*
	WriteByte(deviceadd|0x01);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	*data=ReadByte();
	SendNAck();
	Stop();//*/
	return 1;
}

uchar SI2C::Read_Datas(uchar deviceadd,uchar add,uchar *data,uint datalen)
{
	uint i=0;
	Start();
	WriteByte(deviceadd&0xFE);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	WriteByte(add);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	Start();
	//
	WriteByte(deviceadd|0x01);
	if(WaitAck()==0)
	{
		Stop();
		return 0;
	}
	while(i<datalen)
	{
		*(data+i)=ReadByte();
		i++;
		if(i<datalen)SendAck();
		else SendNAck();
	}
	Stop();
	return 1;
}


