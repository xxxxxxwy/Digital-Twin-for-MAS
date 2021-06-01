#ifndef _BCSH_SI2C_H_
#define _BCSH_SI2C_H_

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif


class SI2C
{
//private:
	public:
	uchar SDA;
	uchar SCL;
	uint acktimeout;
	uchar delaytime;
	//
	void SDAINPUT();
	void SDAOUTPUT();
	void SCLINPUT();
	void SCLOUTPUT();
	uchar SdaIN();
	void SdaOUT(uchar dat);
	void SdaoutHIGH();
	void SdaoutLOW();
	uchar SclIN();
	void SclOUT(uchar dat);
	void ScloutHIGH();
	void ScloutLOW();

		
public:
	void Begin(uchar sda,uchar scl);
	void AcktimeoutWrite(uint timeout);
	uint AcktimeoutRead();
	void DelaytimeWrite(uchar time);
	uchar DelaytimeRead();
	//
	void Start();
	void Stop();
	uchar WaitAck();
	void SendAck();
	void SendNAck();
	void WriteByte(uchar dat);
	uchar ReadByte();
	
	//FUNCTION
	uchar Write_Data(uchar deviceadd,uchar add,uchar data);
	uchar Write_Datas(uchar deviceadd,uchar add,uchar *data,uchar datelen);
	uchar Read_Data(uchar deviceadd,uchar add,uchar *data);
	uchar Read_Datas(uchar deviceadd,uchar add,uchar *data,uint datalen);
};










#endif
