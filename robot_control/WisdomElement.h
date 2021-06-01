
#ifndef _WisdomElement_H_
#define _WisdomElement_H_
//versions


#include "BCSH_SI2C.h"
#include "BCSH_UART2.h"
#include "BCSH_UART1.h"

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






#define CHANNEL_SDA1		20
#define CHANNEL_SCL1		21
#define CHANNEL1_AD1		A15
//#define CHANNEL1_AD2		21


#define CHANNEL_SCL2		35
#define CHANNEL_SDA2		34
#define CHANNEL2_AD1		A14
//#define CHANNEL2_AD2		21

#define CHANNEL_SCL3		33
#define CHANNEL_SDA3		32
#define CHANNEL3_AD1		A13
//#define CHANNEL3_AD2		21

#define CHANNEL_SCL4		31
#define CHANNEL_SDA4		30
#define CHANNEL4_AD1		A12
//#define CHANNEL4_AD2		21


#define CHANNEL1_VALUE	1
#define CHANNEL2_VALUE	2
#define CHANNEL3_VALUE	3
#define CHANNEL4_VALUE	4



#define COLOR_DVICEADD			0x10		//颜色
#define US_DVICEADD				0x20		//超声
#define TEMP_DVICEADD			0x30		//温度
#define ANGLE_DVICEADD			0x40		//角度传感器


#define WisdomElementPack_MAXLENGTH	15
#define WisdomElementPack_HEAD1		0xF5
#define WisdomElementPack_HEAD2		0x5F

//定义设备类型
#define WisdomElementPACK_DEVICETYPE_VOICE			0x01
#define WisdomElementPACK_DEVICETYPE_SERVO			0x07
#define WisdomElementPACK_DEVICETYPE_CHASSIS			0x08
#define WisdomElementPACK_DEVICETYPE_ROBOT			0x09


#define WisdomElementPACK_RIBOTCMD_START				0x40
#define WisdomElementPACK_RIBOTCMD_STOP				0x41
#define WisdomElementPACK_RIBOTCMD_PAUSE				0x42


void UART2Packcallback(UART2_DATAPACKAGE *pack);


class WisdomElement
{
public:	
	UART1_DATAPACKAGE Qrcode_pack_now;	//当前识别的二维码包存储
	uint8 Qrcode_pack_now_ok;
	//初始化
	void Begin();
	void WaitBegin();
	void Stop();
	void ReStart();
public:
	//移动模式设置
	uint8 MoveModeSet(uint8 mode);
	//移动控制
	uint8 MoveControl(uint16 Angle,uint16 speed,int16 turn,uint16 time);
	//机器人模式设置
	uint8 RobotMode(uint8 mode);
	//动作控制
	uint8 MotionSet(uint8 value);
	uint8 MotionRun_name(uint8 *name);
	//
	uint8 VoicePlay(uint8 value);
	uint8 VoicePlay_User(uint8 *filename);
	//舵机位置设置
	uint8 ServoMotor_Set(uint8 id,uint16 sit,uint16 time);
	//霍尔伤害事件输出开关
	uint8 HarmEventOutSwitch(uint8 sw);
	//武器名称读
	uint8 WeaponNameRead();
	//
	uint8 RobotContestState_Updata(uint8 state);

	uint8 QRcode_compare(uint8 *str);
	void QRcode_cleare();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							传感器
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef WisdomElement_Sensor

union WisdomElement_FLOAT32bit
{
	float data;
	uint8 datas[4];
};

union WisdomElement_Union
{
	uint8 valueUint8;
	int8 valueInt8;
	uint16 valueUint16;
	int16 valueInt16;
	float data;
	uint8 values[4];
};

typedef enum
{
	US_MODE_CONTINU=1,
	US_MODE_LISTENER=2,	
	US_MODE_SINGLE=3
}WisdomElement_US_MODE;

class WisdomElement_Sensor
{
private:
	SI2C i2c;
	int AD1;
	int AD2;
	uint16 ReadUint16(uint8 Deviceadd,uint8 dataadd);
public:
	void Begin(uint8 channel);
	void SetChannel(uint8 channel);
private:
public:
	//颜色传感器
	uint8 COLOR_ColorRead();
	uint8 COLOR_LumRead();
	uint8 COLOR_ReflexRead();	
	uint8 COLOR_Read(uint8 type);
	uint8 Infrared_Exp_Bod(uint8 number);

private:
	WisdomElement_US_MODE US_Mode=US_MODE_SINGLE;
public:
	//超声传感器
	uint8 US_ContinuMode();
	uint8 US_ListenerMode();
	uint8 US_SingleMode();
	uint16 US_ContinuRead();
	uint8 US_ListenerRead();
	uint16 US_SingleRead();
	uint16 US_ReadValue();
	float US_Read_CM();

	//温度传感器
	uint8 TEMP_SetOffset(float offset);
	float TEMP_ReadValue();
	uint16 TEMP_ReadValueInt16();
	//角度传感器
	int16 ANGLE_AccelX();
	int16 ANGLE_AccelY();
	int16 ANGLE_AccelZ();
	int16 ANGLE_GyroX();
	int16 ANGLE_GyroY();
	int16 ANGLE_GyroZ();	
	int16 ANGLE_Yaw();
	int16 ANGLE_Pitch();
	int16 ANGLE_Roll();
	int16 ANGLE_MathHz();	
	int16 ANGLE_AngleT();
	int16 ANGLE_Angle();
	uint8 ANGLE_RTS();
	float AccelRead(uint8 xyz);
	//数码管
	void DisplayInt16(int16 value);
	void DisplayFloat(float value,uint8 point);
	//触碰
	uint8 Touch_ReadStatus();
	//声音
	uint16 Sound_ReadValue();
};
#endif



#endif



