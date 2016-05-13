#include "nrf24l01.h"
#include "spi.h"
#include "delay.h"
#include "oled.h"
#include "joystick.h"
#include "my_operator.h"

u8 const TX_ADDRESS[TX_ADR_WIDTH] = {0x12, 0x34, 0x56, 0x78, 0x9A};	//本地地址
u8 const RX_ADDRESS[RX_ADR_WIDTH] = {0x12, 0x34, 0x56, 0x78, 0x9A};	//接收地址
u8 tx_buf[TX_PLOAD_WIDTH] = {0x01, 0x03, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
u8 rx_buf[RX_PLOAD_WIDTH] = {0x00, 0x00, 0x00, 0x00, 0x00};

NrfOptStruct nrfOpts;
NrfOptStruct_P NRF24L01OptsPtr = &nrfOpts;

//从NRF读取一个字节数据
//reg 寄存器地址
u8 SPI_Read(u8 regAddr)
{
	u8 reg_val;
	
	NRF24L01_CSN = 0;                		//片选使能  
	
	SPI1_ReadWriteByte(regAddr);
	reg_val = SPI1_ReadWriteByte(0xff);    	// 读取数据到reg_val
	
	NRF24L01_CSN = 1;                		// 取消片选
	
	return(reg_val);        				// 返回读取的数据
}
   


//向NRF写入一个字节数据
//reg 寄存器地址  value 要写入的数据
u8 SPI_RW_Reg(u8 reg, u8 value)
{
	u8 status;
	
	NRF24L01_CSN = 0;                   	// CSN low, init SPI transaction
	status = SPI1_ReadWriteByte(reg);
    SPI1_ReadWriteByte(value);
	NRF24L01_CSN = 1;                   	// CSN high again
		
	return(status);            				// return nRF24L01 status uchar
}



//从NRF读取多个字节数据
//reg 寄存器地址  *pBuf 读取数据存储指针  uchars 读取的字节个数
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	NRF24L01_CSN = 0;                    		// Set CSN low, init SPI tranaction

	status = SPI1_ReadWriteByte(reg);
	for(uchar_ctr = 0; uchar_ctr < uchars; uchar_ctr++)		  	//循环 uchars次
	{
    	pBuf[uchar_ctr] = SPI1_ReadWriteByte(0xff); 			//分别将SPI_RW(0)读出的数据地址 放入数组中
	}
	
	NRF24L01_CSN = 1;                           
	
	return status;                    // return nRF24L01 status uchar
}


//向NRF写入多个字节数据
//reg 寄存器地址  *pBuf 要写入的数据  uchars 写入的字节个数
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	NRF24L01_CSN = 0;            // SPI使能       

	status = SPI1_ReadWriteByte(reg);
	
	for(uchar_ctr=0; uchar_ctr < uchars; uchar_ctr++) 		// 根据数据个数循环	
	{
		SPI1_ReadWriteByte(*pBuf++);						// 将数组的数据 依次写入
	}

	NRF24L01_CSN = 1;           //关闭SPI
	return(status);    // 
}


//检测24L01是否存在
//返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5] = {0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
	u8 i;
	
    //SPI1_SetSpeed(SPI_BaudRatePrescaler_8);       //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   	 
	SPI_Write_Buf(WRITE_REG_CMD + TX_ADDR, buf, 5);   //写入5个字节的地址.	
	SPI_Read_Buf(TX_ADDR, buf, 5); //读出写入的地址  
	
	for(i = 0;i < 5; i++)
	{
		if(buf[i] != 0xA5)
		{
			break;
		}
	}
	
	if(i != 5)
	{
		return 1;//检测24L01错误	
	}
	
	return 0;		 //检测到24L01
}


//NRF24L01初始化
//m 1 发送模式   0 接收模式
void TX_Mode(void)	        //接收 or 发射 模式 初始化
{
	u8 temp = 0;
	
 	NRF24L01_CE = 0;    // chip enable
 	
	SPI_Write_Buf(WRITE_REG_CMD + TX_ADDR, (u8*)TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG_CMD + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	
	SPI_RW_Reg(WRITE_REG_CMD + RF_SETUP, 0x0f);   		//设置发射速率为2MHZ，发射功率为最大值0dB
	SPI_RW_Reg(WRITE_REG_CMD + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG_CMD + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	
	#if 1

	SPI_RW_Reg(WRITE_REG_CMD + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	temp = SPI_Read(READ_REG_CMD + EN_AA);
	printf("TX_EN_AA = %x\r\n", temp);
	temp = 0xff;
	
	SPI_RW_Reg(WRITE_REG_CMD + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21  
	temp = SPI_Read(READ_REG_CMD + EN_RXADDR);
	printf("TX_EN_RXADDR = %x\r\n", temp);
	temp = 0xff;
	
	SPI_RW_Reg(WRITE_REG_CMD + SETUP_RETR, 0x1a);	// 自动重发10次, 间隔500us
	temp = SPI_Read(READ_REG_CMD + SETUP_RETR);
	printf("TX_SETUP_RETR = %x\r\n\r\n", temp);
	temp = 0xff;
	
	#else
	
	SPI_RW_Reg(WRITE_REG_CMD + EN_AA, 0x00);
	temp = SPI_Read(READ_REG_CMD + EN_AA);
	printf("TX_EN_AA = %x\r\n", temp);
	temp = 0xff;
	
	SPI_RW_Reg(WRITE_REG_CMD + EN_RXADDR, 0x00);
	temp = SPI_Read(READ_REG_CMD + EN_RXADDR);
	printf("TX_EN_RXADDR = %x\r\n", temp);
	temp = 0xff;
	
	SPI_RW_Reg(WRITE_REG_CMD + SETUP_RETR, 0x00);
	temp = SPI_Read(READ_REG_CMD + SETUP_RETR);
	printf("TX_SETUP_RETR = %x\r\n\r\n", temp);
	temp = 0xff;
	#endif
	
	SPI_RW_Reg(WRITE_REG_CMD + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送

	NRF24L01_CE = 1;
}

void Change_To_TX_Mode_Fast(void)
{
	NRF24L01_CE = 0;    // chip enable
 	
	SPI_RW_Reg(WRITE_REG_CMD + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送

	NRF24L01_CE = 1;
}

void RX_Mode(void)
{
	u8 temp = 0;
	
	NRF24L01_CE = 0;	// chip enable
	
	SPI_Write_Buf(WRITE_REG_CMD + TX_ADDR, (u8*)TX_ADDRESS, TX_ADR_WIDTH);	  // 写本地地址 
	SPI_Write_Buf(WRITE_REG_CMD + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG_CMD + EN_RXADDR, 0x01);			//	允许接收地址只有频道0，如果需要多频道可以参考Page21  
	SPI_RW_Reg(WRITE_REG_CMD + RF_SETUP, 0x0f); 			//设置发射速率为2MHZ，发射功率为最大值0dB
	SPI_RW_Reg(WRITE_REG_CMD + RF_CH, 0);		 			//   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG_CMD + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	
	#if 1

	
	SPI_RW_Reg(WRITE_REG_CMD + EN_AA, 0x01);				//	频道0自动	ACK应答允许 
	temp = SPI_Read(READ_REG_CMD + EN_AA);
	printf("RX_EN_AA = %x\r\n\r\n", temp);
	
	#else
	
	SPI_RW_Reg(WRITE_REG_CMD + EN_AA, 0x00);
	temp = SPI_Read(READ_REG_CMD + EN_AA);
	printf("RX_EN_AA = %x\r\n", temp);
	
	#endif
	
	SPI_RW_Reg(WRITE_REG_CMD + CONFIG, 0x0f);			// IRQ收发完成中断响应，16位CRC，主接收
	
	NRF24L01_CE = 1;
}

void Change_To_RX_Mode_Fast(void)
{
	NRF24L01_CE = 0;    // chip enable
 	//NRF24L01_CSN = 1;   // Spi disable 
 	
	SPI_RW_Reg(WRITE_REG_CMD + CONFIG, 0x0f);   		 // IRQ收发完成中断响应，16位CRC，主发送

	NRF24L01_CE = 1;
}

//NRF接收数据函数
//rx_buf  数据缓存区
//该函数检测NRF状态寄存器状态 当有中断立即接收数据到rx_buf缓存区
u8 nRF24L01_RxPacket(u8 *rx_buf)
{	 
    u8 sta;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz） 

	sta = SPI_Read(READ_REG_CMD + STATUS);	    				// 读取状态寄存器来判断数据接收状况
	SPI_RW_Reg(WRITE_REG_CMD + STATUS, sta);   //清中断 （接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志）
	if(sta & RX_OK)								// 判断是否接收到数据
	{

		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		SPI_RW_Reg(FLUSH_RX,0xff);

		return 0; 
	}
	
	return 1;
}


//将缓存区tx_buf中的数据发送出去
//tx_buf  要发送的数据缓存区
u8 nRF24L01_TxPacket(u8 *tx_buf)
{	 
    u8 st;
	
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz） 
	
	NRF24L01_CSN = 0;			//StandBy I模式	

	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // 装载数据	

	NRF24L01_CSN = 1;		 				//置高CE，激发数据发送
	
	while(NRF24L01_IRQ != 0);		   //等待发送完成
	
	st=	SPI_Read(STATUS);			  //读NRF寄存器状态
	SPI_RW_Reg(WRITE_REG_CMD + STATUS, st);  //清中断

	if(st & MAX_TX)//达到最大重发次数
	{
		SPI_RW_Reg(FLUSH_TX, 0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}

	if(st & TX_OK)				 //发送成功
	{
		return TX_OK;
	}

	return 0xff;
}

u8 NRF24L01_Get_Status_Reg(void)
{
	u8 temp;
	
	temp = SPI_Read(READ_REG_CMD + STATUS);

	return temp;
}

u8 NRF24L01_Clean_Status_Reg(u8 clean)
{
	u8 temp = 0xff;
	
	temp = SPI_RW_Reg(WRITE_REG_CMD + STATUS, clean);

	return temp;
}

u8 NRF24L01_Clean_All_Status_Reg(void)
{
	u8 temp = 0;

	temp = SPI_Read(READ_REG_CMD + STATUS);
	temp = SPI_RW_Reg(WRITE_REG_CMD + STATUS, temp);
	//printf("STATUS_A1 = %x\r\n", temp);
	temp = SPI_Read(READ_REG_CMD + STATUS);
	//printf("STATUS_A2 = %x\r\n", temp);
	
	return 0;
}



void NRF24L01_Read_Buf_Process(u8 *pBuf)
{
	
	My_Change_NRFandAGV_View(pBuf);
	
}


void NRF24L01_IT_Process(void)
{
	u8 status, i = 0;
	
	status = SPI_Read(READ_REG_CMD + STATUS);
	printf("status = %x\r\n", status);
	
	if(status & RX_DR)			// 收到数据
	{
		printf("RX_DR\r\n");
		//NRF24L01_Read_Data_2Buf();
		SPI_Read_Buf(RD_RX_PLOAD, rx_buf, RX_PLOAD_WIDTH);	//读取数据
		NRF24L01_Read_Buf_Process(rx_buf);
		
		for(i = 0; i < RX_PLOAD_WIDTH; i++)
		{
			printf("rx_buf[%d] = %d\r\n", i, rx_buf[i]);
		}
		
		//printf("rx_buf[3] = %d\r\n\r\n", rx_buf[3]);
		printf("\r\n");
		NRF24L01_Clean_Status_Reg(status);					// 清除RX_DR中断标志			
		SPI_RW_Reg(FLUSH_RX, NOP);    						// 清除RX FIFO寄存器 
		//rf_rec_flag = RX_DR; 
	}
	else if(status & TX_DS)		// 发送完成ACK中断
	{
		// 发送成功处理
		printf("TX_DS\r\n");
		Change_To_RX_Mode_Fast();
		NRF24L01_Clean_Status_Reg(status);					// 清除TX_DS或MAX_RT中断标志
		SPI_RW_Reg(FLUSH_TX, NOP);      					// 清除TX FIFO寄存器
		//rf_rec_flag = TX_DS;
	}
	else if(status & MAX_RT) 	//达到最大重发次数 
	{	
		// 最大重发次数处理
		printf("MAX_RT\r\n");
		NRF24L01_Clean_Status_Reg(status);					// 清除TX_DS或MAX_RT中断标志
		SPI_RW_Reg(FLUSH_TX, NOP);      					// 清除TX FIFO寄存器
		//rf_rec_flag = MAX_RT;
	}
	else 
	{
		//rf_rec_flag = 0;   // 没收到任何数据
	}

}


void NRF24L01_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;  // PC0 1 推挽 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3);			  //上拉 取消SPI总线片选

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	      //PC2 下拉输入  该IO判断 NRF是否有低电平信号
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void NRF24L01_SPI_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	
	SPI_Cmd(SPI1, DISABLE); // SPI外设不使能			  NRF的SPI要特殊配置一下

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//SPI主机
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//发送接收8位帧结构

	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;			//时钟悬空低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;		//数据捕获于第1个时钟沿

	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			//NSS信号由软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		//定义波特率预分频的值:波特率预分频值为16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;			//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  				//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); 								//使能SPI外设
}



void NRF24L01_TEST_Send(void)
{
	#if 1
	
	u8 temp = 0;
	
	printf("STATUS = %x\r\n", SPI_Read(READ_REG_CMD + STATUS));
	printf("FIFO_STATUS = %x\r\n", SPI_Read(READ_REG_CMD + FIFO_STATUS));
	
	//NRF24L01_TxPacket((u8 *)tx_buf);
	//SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, 1);
	delay_ms(100);

	temp = SPI_Read(READ_REG_CMD + STATUS);
	printf("STATUS3 = %x\r\n", temp);
	printf("FIFO_STATUS3 = %x\r\n", SPI_Read(READ_REG_CMD + FIFO_STATUS));
	SPI_RW_Reg(WRITE_REG_CMD + STATUS, temp);
	temp = SPI_Read(READ_REG_CMD + STATUS);
	printf("STATUS_A = %x\r\n\r\n", temp);
	
	#else
	Change_To_TX_Mode_Fast();
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
	
	#endif
	
}

void nrf_up(void)
{
	//NRF24L01_TEST_Send();
	Change_To_TX_Mode_Fast();
	tx_buf[3] = 0x01;
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
}

void nrf_down(void)
{
	Change_To_TX_Mode_Fast();
	tx_buf[3] = 0x02;
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
}

void nrf_left(void)
{
	Change_To_TX_Mode_Fast();
	tx_buf[3] = 0x03;
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
}

void nrf_right(void)
{
	Change_To_TX_Mode_Fast();
	tx_buf[3] = 0x04;
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
}

void nrf_stop(void)
{
	Change_To_TX_Mode_Fast();
	tx_buf[3] = 0x05;
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
}

void NRF24L01_TEST_Recv(void)
{
	int i = 0, status = 0;
	//printf("%d\r\n", SPI_Read(READ_REG_CMD + STATUS));
	if(0x40 == SPI_Read(READ_REG_CMD + STATUS))
	//if(1)
	{	
		printf("STATUS = %x\r\n", SPI_Read(READ_REG_CMD + STATUS));
		printf("FIFO_STATUS = %x\r\n", SPI_Read(READ_REG_CMD + FIFO_STATUS));
		
		status = SPI_Read_Buf(RD_RX_PLOAD, rx_buf, RX_PLOAD_WIDTH);
		printf("r_status = %x\r\n", status);
		//Delay_ms(100);

		status = 0;
		status = SPI_Read(READ_REG_CMD + STATUS);
		printf("STATUS4 = %x\r\n", status);
		printf("FIFO_STATUS4 = %x\r\n", SPI_Read(READ_REG_CMD + FIFO_STATUS));
		for(i = 0; i < RX_PLOAD_WIDTH; i++)
		{
			printf("rx_buf[%d] = %d\r\n", i, rx_buf[i]);
		}
		
		SPI_RW_Reg(WRITE_REG_CMD + STATUS, status);
		status = SPI_Read(READ_REG_CMD + STATUS);
		printf("STATUS4 = %x\r\n\r\n", status);
		
	}
}

void My_Change_AGV_Sta_View(u8 mode)
{
	switch(mode)
	{
		case stopStatus:
			OLED_ShowString(71, 0, "Stop");
			break;

		case goStraightStatus:
			OLED_ShowString(71, 0, "goFo");
			break;

		case backStatus:
			OLED_ShowString(71, 0, "Back");
			break;

		case cirLeft:
			OLED_ShowString(71, 0, "cirL");
			break;

		case cirRight:
			OLED_ShowString(71, 0, "cirR");
			break;

		default:
			break;
			
	}
	
}

void My_Change_AGV_LM_View(u8 lmSpeed, u8 en, u8 fr)
{
	OLED_ShowxNum(15, 16, lmSpeed, 3, 16, 0x01);
	OLED_ShowxNum(71, 16, en, 1, 16, 0x01);
	OLED_ShowxNum(111, 16, fr, 1, 16, 0x01);
}

void My_Change_AGV_RM_View(u8 rmSpeed, u8 en, u8 fr)
{
	OLED_ShowxNum(15, 32, rmSpeed, 3, 16, 0x01);
	OLED_ShowxNum(71, 32, en, 1, 16, 0x01);
	OLED_ShowxNum(111, 32, fr, 1, 16, 0x01);
}

void My_Change_NRF_Sta_View(u8 sta)
{
	switch(sta)
	{
		case 0:
			OLED_ShowString(39,48,"TX SUCC");
			break;

		case 1:
			OLED_ShowString(39,48,"TX FAIL");
			break;

		case 2:
			OLED_ShowString(39,48,"RX SUCC");
			break;

		case 3:
			OLED_ShowString(39,48,"RX FAIL");
			break;

		default:
			break;
	}
	
}

void My_Change_NRFandAGV_View(u8 *rx_buf)
{
	//tx_buf[3];		// AGV STATUS
	
	//tx_buf[4];		// LeftMotorSpeed
	//tx_buf[5];		// LeftMotorEN
	//tx_buf[6];		// LeftMotorFR
	
	//tx_buf[7];		// RightMotorSpeed
	//tx_buf[8];		// RightMotorEN
	//tx_buf[9];		// RightMotorFR
	
	My_Change_AGV_Sta_View(rx_buf[3]);
	My_Change_AGV_LM_View(rx_buf[4], rx_buf[5], rx_buf[6]);
	My_Change_AGV_RM_View(rx_buf[7], rx_buf[8], rx_buf[9]);
	//My_Change_NRF_Sta_View(1);
	OLED_Refresh_Gram();
}


void joystickScan_Send_NRF(void)
{
	uint8_t key;
	
	key = (JoyStick_Scan(0));
	
	if(key)
	{
		printf("key = %d\r\n", key);
		switch(key)
		{
			case KEY_CENTER:
				NRF24L01OptsPtr->nrf_send_stop();
				break;
				
			case KEY_UP:
				NRF24L01OptsPtr->nrf_send_up();
				break;
				
			case KEY_LEFT:
				NRF24L01OptsPtr->nrf_send_left();
				break;
				
			case KEY_DOWN:
				NRF24L01OptsPtr->nrf_send_down();
				break;
				
			case KEY_RIGHT:
				NRF24L01OptsPtr->nrf_send_right();
				break;
				
			case KEY_NONE:
				break;
				
			default:
				break;
		}
	}
}




void NFR24L01_Init(void)
{
	int i = 0;
	printf("in\r\n");
	NRF24L01_GPIO_Init();
	//NRF24L01_SPI_Init();
	if(0 != NRF24L01_Check())
	{
		OLED_ShowString(0,48,"NRF:ERROR!");
		//return;
	}
	else
	{
		OLED_ShowString(0,48,"NRF: SUCCESS!");
	}
	
	OLED_Refresh_Gram();
	delay_ms(250);
	
	TX_Mode();
	Change_To_RX_Mode_Fast();
	//RX_Mode();

	for(i = 0; i < TX_PLOAD_WIDTH; i++)
	{
		tx_buf[i] = 0;
	}

	tx_buf[0] = 0x01;
	tx_buf[1] = 0x01;
	tx_buf[2] = 0x02;
	
	NRF24L01OptsPtr->TEST_Send = NRF24L01_TEST_Send;
	NRF24L01OptsPtr->TEST_Recv = NRF24L01_TEST_Recv;
	NRF24L01OptsPtr->Read_Register = SPI_Read;
	NRF24L01OptsPtr->Write_Register = SPI_RW_Reg;
	NRF24L01OptsPtr->Read_Buf = SPI_Read_Buf;
	NRF24L01OptsPtr->Write_Buf = SPI_Write_Buf;
	NRF24L01OptsPtr->Check = NRF24L01_Check;
	NRF24L01OptsPtr->TxMode = TX_Mode;
	NRF24L01OptsPtr->RxMode = RX_Mode;
	NRF24L01OptsPtr->TxMode_Fast = Change_To_TX_Mode_Fast;
	NRF24L01OptsPtr->RxMode_Fast = Change_To_RX_Mode_Fast;
	NRF24L01OptsPtr->Get_Status_Reg = NRF24L01_Get_Status_Reg;
	NRF24L01OptsPtr->Clean_Status_Reg = NRF24L01_Clean_Status_Reg;
	NRF24L01OptsPtr->Clean_All_Status_Reg = NRF24L01_Clean_All_Status_Reg;
	NRF24L01OptsPtr->IT_Process = NRF24L01_IT_Process;
	NRF24L01OptsPtr->nrf_send_up = nrf_up;
	NRF24L01OptsPtr->nrf_send_down = nrf_down;
	NRF24L01OptsPtr->nrf_send_left = nrf_left;
	NRF24L01OptsPtr->nrf_send_right = nrf_right;
	NRF24L01OptsPtr->nrf_send_stop = nrf_stop;
	
}


