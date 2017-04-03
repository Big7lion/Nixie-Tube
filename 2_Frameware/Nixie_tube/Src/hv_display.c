#include "hv_display.h"

/*芯片初始控制结构体*/
typedef struct{
	uint8_t LE_flag;
	uint8_t BL_flag;
	uint8_t POL_flag;
	uint8_t DIR;
}HV_Init_data;

/*显示数组*/
uint32_t	DIS_Data[10]={DISPLAY_0,DISPLAY_1,DISPLAY_2,DISPLAY_3,DISPLAY_4,
												DISPLAY_5,DISPLAY_6,DISPLAY_7,DISPLAY_8,DISPLAY_9};

/*写芯片初始设置*/
void HV_Setting_Write(HV_Init_data *HV_Init2data)
{
	LE_Enable(HV_Init2data->LE_flag);
	HVPOL_Enable(HV_Init2data->POL_flag);
}

/*芯片初始化*/
void HV_Display_Init_write(void)
{
	HV_Init_data HV_Init2data;
	TXB0108_Enable(1);
	HV_Init2data.BL_flag = BL_RESET;
	HV_Init2data.LE_flag = LE_RESET;
	HV_Init2data.POL_flag = POL_RESET;
	HV_Init2data.DIR = DIR_A2B;
	HV_Setting_Write(&HV_Init2data);
}

/*写数据并输出*/
void HV_Data_Write(uint32_t *Data)
{
	uint32_t Temp=Data[0];
	LE_Enable(LE_RESET);
	
	HVCLK_Write(HVCLK_Down);
	bsp_DelayUS(1);
	for(uint8_t i=8;i--;)
	{
		HVCLK_Write(HVCLK_Down);
		bsp_DelayUS(1);
		HVDIN1_Write(Temp&1);
		Temp>>=1;
		HVDIN2_Write(Temp&1);
		Temp>>=1;
		HVDIN3_Write(Temp&1);
		Temp>>=1;
		HVDIN4_Write(Temp&1);
		Temp>>=1;
		bsp_DelayUS(1);
		HVCLK_Write(HVCLK_Up);
		bsp_DelayUS(1);
		HVCLK_Write(HVCLK_Down);
	}
	
	Temp=Data[1];
	bsp_DelayUS(1);
	for(uint8_t i=8;i--;)
	{
		HVCLK_Write(HVCLK_Down);
		bsp_DelayUS(1);
		HVDIN1_Write(Temp&1);
		Temp>>=1;
		HVDIN2_Write(Temp&1);
		Temp>>=1;
		HVDIN3_Write(Temp&1);
		Temp>>=1;
		HVDIN4_Write(Temp&1);
		Temp>>=1;
		bsp_DelayUS(1);
		HVCLK_Write(HVCLK_Up);
		bsp_DelayUS(1);
		HVCLK_Write(HVCLK_Down);
	}
	
	bsp_DelayUS(1);
	LE_Enable(LE_SET);
	return;
}

uint8_t Data2Signal(uint8_t *Point2Data)
{
	uint32_t Data2Write[2]={0x00000000,0x00000000};
	
	for(unsigned int i=5;i--;)
	{
		if(Point2Data[i]<10)
			continue;
		else
			return Dataerror;
	}
	
	Data2Write[0]|=DIS_Data[Point2Data[0]]<<4;
	Data2Write[0]|=DIS_Data[Point2Data[1]]<<14;
	Data2Write[0]|=DIS_Data[Point2Data[2]]<<24;
	
	Data2Write[1]|=DIS_Data[Point2Data[2]]>>8;
	Data2Write[1]|=DIS_Data[Point2Data[3]]<<2;
	Data2Write[1]|=DIS_Data[Point2Data[4]]<<12;
	Data2Write[1]|=DIS_Data[Point2Data[5]]<<22;
	
	HV_Data_Write(Data2Write);
	return 0;
}

