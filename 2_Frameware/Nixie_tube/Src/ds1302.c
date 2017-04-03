#include "ds1302.h"

GPIO_InitTypeDef GPIO_InitStruct;

static void DS1302_IN()
{
	GPIO_InitStruct.Pin=TIME_IO_Pin;
	GPIO_InitStruct.Pull=GPIO_MODE_INPUT;
	HAL_GPIO_Init(TIME_IO_GPIO_Port, &GPIO_InitStruct);
}

static void DS1302_OUT()
{
	GPIO_InitStruct.Pin=TIME_IO_Pin;
	GPIO_InitStruct.Pull=GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(TIME_IO_GPIO_Port, &GPIO_InitStruct);
}

void DS1302SendByte(uint8_t byte)
{
	uint8_t	i;

	for(i=0x01;i;i<<=1)
	{
		if(byte&i)	DS1302_OUT_H();
		else	DS1302_OUT_L();
		DS1302_CLK_H();
		bsp_DelayUS(50);		//加延时
		DS1302_CLK_L();
	}
}

uint8_t DS1302ReceiveByte(void)
{
	uint8_t	i,byte=0;

	for(i=0x01;i;i<<=1)
	{
		if(DS1302_IN_X)	byte |= i;
		DS1302_CLK_H();
		bsp_DelayUS(50);		//加延时
		DS1302_CLK_L();
	}
	return(byte);
}

void Write1302(uint8_t addr,uint8_t data)
{
    DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	bsp_DelayUS(100);
	DS1302SendByte(addr);
	DS1302SendByte(data);
	bsp_DelayUS(100);
	DS1302_RST_L();
}

uint8_t Read1302(uint8_t addr)
{
    uint8_t data=0;

    DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	bsp_DelayUS(100);
	DS1302SendByte(addr|0x01);
	DS1302_IN();
	data = DS1302ReceiveByte();
	bsp_DelayUS(100);
	DS1302_RST_L();
	return(data);
}

//读取时间函数
void DS1302_GetTime(uint8_t *time)
{
//	uint8_t tmp;
	time[0] = Read1302(DS1302_YEAR);
	time[1] = Read1302(DS1302_WEEK);
	time[2] = Read1302(DS1302_MONTH);
	time[3] = Read1302(DS1302_DAY);
	time[4] = Read1302(DS1302_HOUR);
	time[5] = Read1302(DS1302_MINUTE);
	time[6] = Read1302(DS1302_SECOND);	
}

/*
读取DS1302中的RAM
addr:地址,从0到30,共31个字节的空间
返回为所读取的数据
*/
uint8_t ReadDS1302Ram(uint8_t addr)
{
	uint8_t	tmp,res;

	tmp = (addr<<1)|0xc0;
	res = Read1302(tmp);
	return(res);
}

/*
写DS1302中的RAM
addr:地址,从0到30,共31个字节的空间
data:要写的数据
*/
void WriteDS1302Ram(uint8_t addr,uint8_t data)
{
	uint8_t	tmp;

	Write1302(DS1302_WRITE,0x00);		//关闭写保护
	tmp = (addr<<1)|0xc0;
	Write1302(tmp,data);
	Write1302(DS1302_WRITE,0x80);		//打开写保护
}

void ReadDSRam(uint8_t *p,uint8_t add,uint8_t cnt)
{
	uint8_t i;
	
	if(cnt>30) return;
	for(i=0;i<cnt;i++)
	{
		*p = ReadDS1302Ram(add+1+i);
		p++;
	}
}

void WriteDSRam(uint8_t *p,uint8_t add,uint8_t cnt)
{
	uint8_t i;
	
	if(cnt>30) return;
	for(i=0;i<cnt;i++)
	{
		WriteDS1302Ram(add+1+i,*p++);
	}
}
  
/*
读时间函数,顺序为:年周月日时分秒
*/
void ReadDS1302Clock(uint8_t *p)
{
	DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	bsp_DelayUS(100);
	DS1302SendByte(0xbf);			//突发模式
	DS1302_IN();
	p[5] = DS1302ReceiveByte();		//秒
	p[4] = DS1302ReceiveByte();		//分
	p[3] = DS1302ReceiveByte();		//时
	p[2] = DS1302ReceiveByte();		//日
	p[1] = DS1302ReceiveByte();		//月
	DS1302ReceiveByte();			//周
	p[0] = DS1302ReceiveByte();		//年
	DS1302ReceiveByte();			//保护标志字节
	bsp_DelayUS(100);
	DS1302_RST_L();
}

/*
写时间函数,顺序为:年周月日时分秒
*/
void WriteDS1302Clock(uint8_t *p)
{
	Write1302(DS1302_WRITE,0x00);		//关闭写保护
	DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	bsp_DelayUS(100);
	DS1302SendByte(0xbe);				//突发模式
	DS1302SendByte(p[5]);				//秒
	DS1302SendByte(p[4]);				//分
	DS1302SendByte(p[3]);				//时
	DS1302SendByte(p[2]);				//日
	DS1302SendByte(p[1]);				//月
	DS1302SendByte(0x01);				//周，设置成周一，没有使用
	DS1302SendByte(p[0]);				//年
	DS1302SendByte(0x80);				//保护标志字节
	bsp_DelayUS(100);
	DS1302_RST_L();
}
void bsp_1302_Init(void)
{
	uint8_t	tmp;
	tmp = ReadDS1302Ram(0);
	if(tmp^0xa5)
	{
		WriteDS1302Ram(0,0xa5);
		Write1302(DS1302_WRITE,0x00);		//关闭写保护
		Write1302(0x90,0x03);				//禁止涓流充电
		Write1302(DS1302_HOUR,0x00);		//设置成24小时制
		Write1302(DS1302_SECOND,0x00);		//使能时钟运行
		Write1302(DS1302_WRITE,0x80);		//打开写保护
	}
}
