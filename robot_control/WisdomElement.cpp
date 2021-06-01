/** 
 * @file   WisdomElement.cpp
 * @brief  本库主要通过对串口的读写实现Arduino控制器同机器人主控器的通信功能
 * @author LH
 * @version v2.0(版本号)
 * @date   2017-12-14
 * @note   本库只通过Areuino IDE1.81调试验证
 * @license  GNU General Public License (GPL)
 */
/*
更新记录
20181112：
1.增加声音传感器

*/

#include "arduino.h"
#include "WisdomElement.h"


#define UARTx_NUMBER			BCSH_Uart2


void(* WisdomElementresetFunc) (void) = 0;
//startFlag=1 run
//startFlag=0 stop
volatile uint8 StartFlag=1;

void Reset()
{
	WisdomElementresetFunc();
}

void UART2Packcallback(UART2_DATAPACKAGE *pack)
{
	if(pack->devicetype==0x09)
	{
		switch(pack->devicecmd)
		{
			case 0x40:
				if(StartFlag==0)StartFlag=1;
			break;
			//
			case 0x41:
				Reset();
			break;
			//
			case 0x42:
				UARTx_NUMBER.PackSendD1(0x09,0x42,StartFlag);
			break;
			//
			case 0x43:
				if(StartFlag)
				{
					Reset();
				}
				else 
				{
					StartFlag=1;
				}
			break;
			//
			default:break;
		}
	} 
}


//============================================================
//				公有成员
//============================================================
void WisdomElement::Begin()
{
	BCSH_Uart1.Begin(115200);
	BCSH_Uart2.Begin(115200,UART2Packcallback);
	StartFlag=1;
	MoveModeSet(0);
}
void WisdomElement::WaitBegin()
{
	BCSH_Uart1.Begin(115200);
	BCSH_Uart2.Begin(115200,UART2Packcallback);
	MoveModeSet(0);
	StartFlag=0;
	while(StartFlag==0)
	{
	}
}
void WisdomElement::Stop()
{
	MoveModeSet(0);
	delay(5);
	Reset();
}
void WisdomElement::ReStart()
{
	MoveModeSet(0);
	delay(5);
	Reset();
}



//=================================================
//				上层设备控制命令
//=================================================

/**
 * @brief 设置底盘移动模式
 * 
 * @param mode 0：单闭环	2：双闭环
 * @return uint8 
 */
uint8 WisdomElement::MoveModeSet(uint8 mode)
{
	UARTx_NUMBER.PackSendD1(0x08,0x01,mode);
	return true;
}
//移动控制
uint8 WisdomElement::MoveControl(uint16 Angle,uint16 speed,int16 turn,uint16 time)
{
	WisdomElement_Union value;
	uint8 data[8];
	if(speed>100)speed=100;
	if(turn<-1000)turn=-1000;
	else if(turn>1000)turn=1000;
	//
	data[0]=Angle;
	data[1]=Angle>>8;
	//
	data[2]=speed;
	data[3]=speed>>8;
	//
	value.valueInt16=turn;
	data[4]=turn;
	data[5]=turn>>8;
	data[6]=time;
	data[7]=time>>8;	
	UARTx_NUMBER.PackSendDS(0x08,0x02,data,8);
}
//机器人模式设置
uint8 WisdomElement::RobotMode(uint8 mode)
{
	UARTx_NUMBER.PackSendD1(0x09,0x01,mode);
    return 1;
}
/**
 * @brief 控制机器人做出特定的动作
 * 
 * @param value 动作编号
 * @return uint8 成功返回true，失败返回false
 */
uint8 WisdomElement::MotionSet(uint8 value)
{
	UARTx_NUMBER.PackSendD1(0x07,0x55,value);
    return 1;
}
uint8 WisdomElement::MotionRun_name(uint8 *name)
{
	uint8 i=0;
	while(name[i]!=0)
	{
		i++;
	}
	if(i>63)
	{
		return 0;
	}
	UARTx_NUMBER.PackSendDS(0x07,0x54,name,i);
    return 1;
}



uint8 WisdomElement::VoicePlay(uint8 value)
{
	UARTx_NUMBER.PackSendD2(0x01,0x42,255,value);
    return 1;
}
//用户播放指定名称的用户自定义语音
uint8 WisdomElement::VoicePlay_User(uint8 *filename)
{
	uint8 file[16];
	uint8 i=0;
	file[0]='0';
	file[1]='2';
	file[2]='5';
	file[3]='5';
	file[4]='\\';
	i=0;
	while(i<11&&filename[i]!=0)
	{
		file[i+5]=filename[i];
		i++;
	}
	UARTx_NUMBER.PackSendDS(0x01,0x70,file,i+5);
    return 1;
}




//舵机位置设置
uint8 WisdomElement::ServoMotor_Set(uint8 id,uint16 sit,uint16 time)
{
    return 0;
}
//霍尔伤害事件输出开关
uint8 WisdomElement::HarmEventOutSwitch(uint8 sw)
{
    return 0;
}
//武器名称读
uint8 WisdomElement::WeaponNameRead()
{
    return 0;
}

//比赛状态位置记录更新
uint8 WisdomElement::RobotContestState_Updata(uint8 state)
{
	UARTx_NUMBER.PackSendD1(0x09,0xB1,state);
    return 0;
}



//*
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						机器人串口1通信相关
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//比较当前数据包中的二维码是否是想要的值
//匹配成功返回1
//否则返回0
uint8 WisdomElement::QRcode_compare(uint8 *str)
{
	uint8 i;
	if(BCSH_Uart1.Qrcode_pack_readok==0&&Qrcode_pack_now_ok==0)			//如果中断接收和二维码处理缓冲区都没有二维码数据，则返回
	{
		return 0;
	}
	if(BCSH_Uart1.Qrcode_pack_readok==1)
	{
		Qrcode_pack_now=BCSH_Uart1.Qrcode_pack;		//如果二维码处理缓冲区没有二维码数据则记录该数据
		Qrcode_pack_now_ok=1;						//当前处理的二维码包标记为可用
	}
	BCSH_Uart1.Qrcode_pack_readok=0;				//
	BCSH_Uart1.Qrcode_pack_read=1;					//中断可以再次接收二维码包
	//
	if(Qrcode_pack_now.datalength<=12||str==0||str[0]==0)
	{
		Qrcode_pack_now_ok=0;						//当前处理的二维码包标记为不可用
		return 0;
	}
	//
	for(i=12;i<Qrcode_pack_now.datalength;i++)
	{
		if(str[i-12]==0||str[i-12]!=Qrcode_pack_now.data[i])
		{
			return 0;
		}
	}
	if(i!=Qrcode_pack_now.datalength||str[i-12]!=0)
	{
		return 0;
	}
	return 1;
}
void WisdomElement::QRcode_cleare()
{
	BCSH_Uart1.Qrcode_pack_readok=0;	//清除中断接收缓冲区的二维码可用标记
	Qrcode_pack_now_ok=0;				//当前处理的二维码包标记为不可用
}
//*/






//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								传感器
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef WisdomElement_Sensor
uint16 WisdomElement_Sensor::ReadUint16(uint8 Deviceadd,uint8 dataadd)
{
	uint8 values[2];
	uint16 value;
	i2c.Read_Datas(Deviceadd,dataadd,values,2);
	value=(values[0]<<8)|values[1];
	return value;
}

void WisdomElement_Sensor::Begin(uint8 channel)
{
	SetChannel(channel);
	US_Mode=US_MODE_CONTINU;
	switch(channel)
	{
		case CHANNEL1_VALUE:
			AD1=CHANNEL1_AD1;
			#ifdef	CHANNEL1_AD2
				AD2=CHANNEL1_AD2;
			#endif
		break;
		case CHANNEL2_VALUE:
			AD1=CHANNEL2_AD1;
			#ifdef	CHANNEL2_AD2
				AD2=CHANNEL2_AD2;
			#endif
		break;
		case CHANNEL3_VALUE:
			AD1=CHANNEL3_AD1;
			#ifdef	CHANNEL3_AD2
				AD2=CHANNEL3_AD2;
			#endif
		break;
		case CHANNEL4_VALUE:
			AD1=CHANNEL4_AD1;
			#ifdef	CHANNEL4_AD2
				AD2=CHANNEL4_AD2;
			#endif
		break;
		default:
			AD1=CHANNEL1_AD1;
			#ifdef	CHANNEL1_AD2
				AD2=CHANNEL1_AD2;
			#endif
		break;
	}
}

void WisdomElement_Sensor::SetChannel(uint8 channel)
{
	if(channel==CHANNEL1_VALUE)
	{
		i2c.Begin(CHANNEL_SDA1,CHANNEL_SCL1);
	}
	else if(channel==CHANNEL2_VALUE)
	{
		i2c.Begin(CHANNEL_SDA2,CHANNEL_SCL2);
	}
	else if(channel==CHANNEL3_VALUE)
	{
		i2c.Begin(CHANNEL_SDA3,CHANNEL_SCL3);
	}
	else if(channel==CHANNEL4_VALUE)
	{
		i2c.Begin(CHANNEL_SDA4,CHANNEL_SCL4);
	}
	#ifdef CHANNEL5_VALUE
	else if(channel==CHANNEL5_VALUE)
	{
		i2c.Begin(CHANNEL_SDA5,CHANNEL_SCL5);
	}	
	#endif
}



uint8 WisdomElement_Sensor::COLOR_ColorRead()
{
	uint8 value;
  	i2c.Read_Data(COLOR_DVICEADD,0x01,&value);
  	return value;
}
uint8 WisdomElement_Sensor::COLOR_LumRead()
{
	uint8 value;
  	i2c.Read_Data(COLOR_DVICEADD,0x03,&value);
  	return value;
}
uint8 WisdomElement_Sensor::COLOR_ReflexRead()
{
	uint8 value;
  	i2c.Read_Data(COLOR_DVICEADD,0x05,&value);
  	return value;
}


uint8 WisdomElement_Sensor::COLOR_Read(uint8 type)
{
	if(type==0)
	{
		return COLOR_ColorRead();
	}
	else if(type==1)
	{
		return COLOR_LumRead();
	}
	else if(type==2)
	{
		return COLOR_ReflexRead();
	}
	return 0;
}

uint8 WisdomElement_Sensor::Infrared_Exp_Bod(uint8 number)
{
	uint8 value;
	value=COLOR_ColorRead();
	if(number==1)
	{
		if(value&0x01)return 1;
		else return 0;
	}
	else if(number==2)
	{
		if(value&0x02)return 1;
		else return 0;
	}
	else if(number==3)
	{
		if(value&0x04)return 1;
		else return 0;
	}
	return value;
}

uint8 WisdomElement_Sensor::US_ContinuMode()
{
	uint8 value;
  	if(i2c.Read_Data(US_DVICEADD,0x00,&value))
  	{
  		US_Mode=US_MODE_CONTINU;
      	return 1;
  	}
  	return 0;
}
uint8 WisdomElement_Sensor::US_ListenerMode()
{
	uint8 value;
  	if(i2c.Read_Data(US_DVICEADD,0x04,&value))
  	{
  		US_Mode=US_MODE_LISTENER;
      	return 1;
  	}
  	return 0;
}
uint8 WisdomElement_Sensor::US_SingleMode()
{
  	if(i2c.Write_Data(US_DVICEADD,0x05,0x01))
  	{
  		US_Mode=US_MODE_SINGLE;
      	return 1;
  	}
  	return 0;
}

uint16 WisdomElement_Sensor::US_ContinuRead()
{
	uint16 value=0;
	US_Mode=US_MODE_CONTINU;
	value=ReadUint16(US_DVICEADD,0x00);
	return value;
}
uint8 WisdomElement_Sensor::US_ListenerRead()
{
	uint8 value=0;
	US_Mode=US_MODE_LISTENER;
	i2c.Read_Data(US_DVICEADD,0x04,&value);
	return value;
}
uint16 WisdomElement_Sensor::US_SingleRead()
{
	uint16 value=0;
	US_Mode=US_MODE_SINGLE;
	value=ReadUint16(US_DVICEADD,0x02);
	return value;
}
uint16 WisdomElement_Sensor::US_ReadValue()
{
	uint8 valuel=0;
	uint16 value=0;
	if(US_Mode==US_MODE_CONTINU)
	{
		value=ReadUint16(US_DVICEADD,0x00);
	}
	else if(US_Mode==US_MODE_LISTENER)
	{
		i2c.Read_Data(US_DVICEADD,0x04,&valuel);
		value=valuel;
	}
	else if(US_Mode==US_MODE_SINGLE)
	{
		value=ReadUint16(US_DVICEADD,0x02);
	}
	return value;
}

float WisdomElement_Sensor::US_Read_CM()
{
	uint8 value8=0;
	uint16 value16;
	float valuef=0;
	if(US_Mode==US_MODE_CONTINU)
	{
		value16=ReadUint16(US_DVICEADD,0x00);
		valuef=value16*0.1;
	}
	else if(US_Mode==US_MODE_LISTENER)
	{
		i2c.Read_Data(US_DVICEADD,0x04,&value8);
		valuef=value8;
	}
	else if(US_Mode==US_MODE_SINGLE)
	{
		value16=ReadUint16(US_DVICEADD,0x02);
		valuef=value16*0.1;
	}
	return valuef;
}

uint8 WisdomElement_Sensor::TEMP_SetOffset(float offset)
{
	WisdomElement_FLOAT32bit datax;
	datax.data=offset;
	if(i2c.Write_Datas(TEMP_DVICEADD,0x04,datax.datas,4))return 1;
	return 0;
}


float WisdomElement_Sensor::TEMP_ReadValue()
{
	float valuef;
	uint16 value=0;
	value=ReadUint16(TEMP_DVICEADD,0x02);
	valuef=value/10.0;
	return valuef;
}

uint16 WisdomElement_Sensor::TEMP_ReadValueInt16()
{
	uint16 value=0;
	value=ReadUint16(TEMP_DVICEADD,0x02);
	return value;
}


int16 WisdomElement_Sensor::ANGLE_AccelX()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x00);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_AccelY()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x02);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_AccelZ()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x04);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_GyroX()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x06);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_GyroY()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x08);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_GyroZ()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x0a);
	return value;
}

int16 WisdomElement_Sensor::ANGLE_Yaw()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x0c);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_Pitch()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x0E);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_Roll()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x10);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_MathHz()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x12);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_AngleT()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x14);
	return value;
}
int16 WisdomElement_Sensor::ANGLE_Angle()
{
	int16 value=0;
	value=(int16)ReadUint16(ANGLE_DVICEADD,0x16);
	return value;
}
uint8 WisdomElement_Sensor::ANGLE_RTS()
{
  	if(i2c.Write_Data(ANGLE_DVICEADD,0x18,0x01))
  	{
      	return 1;
  	}
  	return 0;
}
float WisdomElement_Sensor::AccelRead(uint8 xyz)
{
	float revalue;
	int16 value;
	//
	if(xyz>3)xyz=3;
	//
	if(xyz==1)//ƫ��
	{
		value=ANGLE_Yaw();
	}
	else if(xyz==2)//����
	{
		value=ANGLE_Pitch();
	}
	else if(xyz==3)//���
	{
		value=ANGLE_Roll();
	}	
	revalue=value/10;
	return revalue;
}






void WisdomElement_Sensor::DisplayInt16(int16 value)
{
	uint8 ds[3];
	ds[0]=0xB2;
	ds[1]=value>>8;
	ds[2]=value;
	i2c.Write_Datas(0x00,0x00,ds,3);
}
void WisdomElement_Sensor::DisplayFloat(float value,uint8 point)
{
	uint8 ds[6];
	WisdomElement_FLOAT32bit ff;
	ff.data=value;
	ds[0]=0xAF;
	ds[1]=point;
	ds[2]=ff.datas[3];
	ds[3]=ff.datas[2];
	ds[4]=ff.datas[1];
	ds[5]=ff.datas[0];
	i2c.Write_Datas(0x00,0x00,ds,6);
}


uint8 WisdomElement_Sensor::Touch_ReadStatus()
{
	uint16 value;
	value=analogRead(AD1);
	if(value>250)return 0;
	return 1;
}

/**
 * @brief 读取声音传感器采样值
 * 
 * @param mode 0-DB模式，1-DBA模式
 * @return uint16 
 */
uint16 WisdomElement_Sensor::Sound_ReadValue()
{
	uint16 value;
	/*if(mode==0)//DB
	{
		pinMode(i2c.SDA, OUTPUT);
		pinMode(i2c.SCL, OUTPUT);
		digitalWrite(i2c.SDA, LOW);
		digitalWrite(i2c.SCL, LOW);
	}
	else//DBA*/
	{
		pinMode(i2c.SDA, OUTPUT);
		pinMode(i2c.SCL, OUTPUT);
		digitalWrite(i2c.SDA, HIGH);
		digitalWrite(i2c.SCL, LOW);
	}
	value=analogRead(AD1);
    if(value>1000)value=1000;
	value=(1000-value)/10;
	return value;
}


#endif




