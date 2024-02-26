#include "sram.h"
#include "usart.h"


SRAM_HandleTypeDef g_sram_handler; /* SRAM��� */

/**
 * @brief       ��ʼ�� �ⲿSRAM
 * @param       ��
 * @retval      ��
 */
void sram_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    FSMC_NORSRAM_TimingTypeDef fsmc_readwritetim;

    SRAM_CS_GPIO_CLK_ENABLE();    /* SRAM_CS��ʱ��ʹ�� */
    SRAM_WR_GPIO_CLK_ENABLE();    /* SRAM_WR��ʱ��ʹ�� */
    SRAM_RD_GPIO_CLK_ENABLE();    /* SRAM_RD��ʱ��ʹ�� */
    __HAL_RCC_FSMC_CLK_ENABLE();  /* ʹ��FSMCʱ�� */
    __HAL_RCC_GPIOD_CLK_ENABLE(); /* ʹ��GPIODʱ�� */
    __HAL_RCC_GPIOE_CLK_ENABLE(); /* ʹ��GPIOEʱ�� */
    __HAL_RCC_GPIOF_CLK_ENABLE(); /* ʹ��GPIOFʱ�� */
    __HAL_RCC_GPIOG_CLK_ENABLE(); /* ʹ��GPIOGʱ�� */

    gpio_init_struct.Pin = SRAM_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(SRAM_CS_GPIO_PORT, &gpio_init_struct); /* SRAM_CS����ģʽ���� */

    gpio_init_struct.Pin = SRAM_WR_GPIO_PIN;
    HAL_GPIO_Init(SRAM_WR_GPIO_PORT, &gpio_init_struct); /* SRAM_WR����ģʽ���� */

    gpio_init_struct.Pin = SRAM_RD_GPIO_PIN;
    HAL_GPIO_Init(SRAM_RD_GPIO_PORT, &gpio_init_struct); /* SRAM_CS����ģʽ���� */

    /* PD0,1,4,5,8~15 */
    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | 
                       GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
                       GPIO_PIN_14 | GPIO_PIN_15;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;       /* ���츴�� */
    gpio_init_struct.Pull = GPIO_PULLUP;           /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* ���� */
    HAL_GPIO_Init(GPIOD, &gpio_init_struct);

    /* PE0,1,7~15 */
    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
                       GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                       GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);

    /* PF0~5,12~15 */
    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
                       GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);

    /* PG0~5,10 */
    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    HAL_GPIO_Init(GPIOG, &gpio_init_struct);

    g_sram_handler.Instance = FSMC_NORSRAM_DEVICE;
    g_sram_handler.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

    g_sram_handler.Init.NSBank = (SRAM_FSMC_NEX == 1) ? FSMC_NORSRAM_BANK1 : \
                                 (SRAM_FSMC_NEX == 2) ? FSMC_NORSRAM_BANK2 : \
                                 (SRAM_FSMC_NEX == 3) ? FSMC_NORSRAM_BANK3 : 
                                                        FSMC_NORSRAM_BANK4; /* ��������ѡ��FSMC_NE1~4 */
    g_sram_handler.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;     /* ��ַ/�����߲����� */
    g_sram_handler.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;                 /* SRAM */
    g_sram_handler.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    /* 16λ���ݿ�� */
    g_sram_handler.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;   /* �Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ� */
    g_sram_handler.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW; /* �ȴ��źŵļ���,����ͻ��ģʽ���������� */
    g_sram_handler.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;      /* �洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT */
    g_sram_handler.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;       /* �洢��дʹ�� */
    g_sram_handler.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;              /* �ȴ�ʹ��λ,�˴�δ�õ� */
    g_sram_handler.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;          /* ��дʹ����ͬ��ʱ�� */
    g_sram_handler.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;  /* �Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ� */
    g_sram_handler.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;              /* ��ֹͻ��д */
    /* FSMC��ʱ����ƼĴ��� */
    fsmc_readwritetim.AddressSetupTime = 0x02;                              /* ��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/168M=6ns*2=12ns */
    fsmc_readwritetim.AddressHoldTime = 0x00;                               /* ��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ� */
    fsmc_readwritetim.DataSetupTime = 0x08;                                 /* ���ݱ���ʱ��Ϊ8��HCLK =6*8= 48ns */
    fsmc_readwritetim.BusTurnAroundDuration = 0x00;
    fsmc_readwritetim.AccessMode = FSMC_ACCESS_MODE_A;                      /* ģʽA */
    HAL_SRAM_Init(&g_sram_handler, &fsmc_readwritetim, &fsmc_readwritetim);
}






/**
 * @brief       ��SRAMָ����ַд��ָ���������� ������ ������ʵ��ʹ��
 * @param       pbuf    : ���ݴ洢��
 * @param       addr    : ��ʼд��ĵ�ַ(���32bit)
 * @param       datalen : Ҫд����ֽ���(���32bit)
 * @retval      ��
 */
void sram_write(uint8_t *pbuf, uint32_t addr, uint32_t datalen)
{
    for (; datalen != 0; datalen--)
    {
        *(volatile uint8_t *)(SRAM_BASE_ADDR + addr) = *pbuf;
        addr++;
        pbuf++;
    }
}


void sram_write_(uint8_t *pbuf, uint32_t addr, uint32_t datalen)
{
    for (; datalen != 0; datalen--)
    {
        *(volatile uint8_t *)(SRAM_BASE_ADDR + addr) = 0xff;
        addr++;
        pbuf++;
    }
}


/**
 * @brief       ��SRAMָ����ַ��ȡָ���������� ������ ������ʵ��ʹ�� 
 * @param       pbuf    : ���ݴ洢��
 * @param       addr    : ��ʼ��ȡ�ĵ�ַ(���32bit)
 * @param       datalen : Ҫ��ȡ���ֽ���(���32bit)
 * @retval      ��
 */
void sram_read(uint8_t *pbuf, uint32_t addr, uint32_t datalen)
{
    for (; datalen != 0; datalen--)
    {
        *pbuf++ = *(volatile uint8_t *)(SRAM_BASE_ADDR + addr);
        addr++;
    }
}

uint32_t sram_current_add =0;


sram_bmp_file* sram_load_bmp_from_sd_withbuf(char* path)
{		
	FRESULT res;
	bmp_head bmp;
	uint32_t br;
	static sram_bmp_file sram_bmp;
	sram_bmp.addr=sram_current_add;
	static uint8_t buf[960];
	static uint8_t buf2[960];
	res=f_open(&SDFile,path,FA_READ);
	if(res==FR_OK)
	{
		if(f_read(&SDFile,(char*)&bmp+2,sizeof(bmp_head)-2,&br)==FR_OK)
		{
			int Height=bmp.info.Height;
			sram_bmp.h=Height;
			int Width=bmp.info.Width;
			sram_bmp.w=Width;
			sram_bmp.len=Width*2*Height;
			f_lseek(&SDFile,bmp.file.Offset);
			printf("sram_current_add%d\n\r",sram_current_add);
			while(1)
			{
			if(f_read(&SDFile,buf,960,&br)==FR_OK)
			{
				printf("br%d\n\r",br);
				sram_write_(buf,sram_current_add,br);
				sram_current_add+=br;
				printf("write success sram_current_add=%d\n\r",sram_current_add);
			
			}
			else
			{
					break;
			}
			if(br==0)
			{
				break;
			}
		}
		}
		return &sram_bmp;
	}
	else{
		printf("opened fail %x",res);
		return NULL;
	}
}







/**
 * @brief       ��ȡSD��16bitɫ���bmpͼ���ļ����ⲿSRAM
 * @param       path         SD��bmpͼ���ļ��洢·��
 * @retval      �������ݴ洢�׵�ַ�����ݳ��ȵ���Ϣ�Ľṹ��sram_bmp_file
 */
sram_bmp_file* sram_load_bmp_from_sd(char* path)
{		
	FRESULT res;
	bmp_head bmp;
	uint32_t br;
	sram_bmp_file* sram_bmp=(sram_bmp_file*)malloc(sizeof(sram_bmp_file));
	sram_bmp->addr=sram_current_add;
	res=f_open(&SDFile,path,FA_READ);
	if(res==FR_OK)
	{
		if(f_read(&SDFile,(char*)&bmp+2,sizeof(bmp_head)-2,&br)==FR_OK)
		{
			int Height=bmp.info.Height;
			sram_bmp->h=Height;
			int Width=bmp.info.Width;
			sram_bmp->w=Width;
			sram_bmp->len=Width*2*Height;
			f_lseek(&SDFile,bmp.file.Offset);
			if(f_read(&SDFile,(uint8_t *)(SRAM_BASE_ADDR + sram_current_add),sram_bmp->len,&br)==FR_OK)//��ȡSD�����ݵ��ⲿSRAM
			{
				printf("br%d\n\r",br);
				sram_current_add+=br;
			}
			else
			{
				printf("read fail \r\n");
				return NULL;
			}
		}
		f_close(&SDFile);
		printf("%s load success \r\n", path);
		return sram_bmp;
	}
	else{
		printf("opened fail %x\r\n",res);
		return NULL;
	}
}















void show_bmp_from_sram(int  x,int y,sram_bmp_file* bmp_file)
{
			lcd_show_inverted_pic(x,  y, x+bmp_file->w-1,y+bmp_file->h-1,( uint8_t *)(SRAM_BASE_ADDR + bmp_file->addr));
}
void show_bmp_from_sram_cut(int  x,int y,sram_bmp_file* bmp_file)
{
			lcd_show_inverted_pic_cut(x,  y, x+bmp_file->w-1,y+bmp_file->h-1,( uint8_t *)(SRAM_BASE_ADDR + bmp_file->addr));
}

void show_bmp_from_sram_full(sram_bmp_file* bmp_file)
{
 lcd_show_inverted_pic_full( bmp_file->h, bmp_file->w, ( uint8_t *)(SRAM_BASE_ADDR + bmp_file->addr));	
}











/**
 * @brief       ��ʾbmpͼƬ�е���״���������� ���ڵ�������ʾ 
 * @param       x��y           ��ʾ��ʼλ��
 * @param       bmp_file       Ҫ��ʾ��ͼƬ���� 
 * @param       background_bmp Ҫ��ʾ�ı���ͼ����
 * @retval      ��
 */
void show_bmp_from_sram_with_background(int  x,int y,sram_bmp_file* bmp_file,sram_bmp_file* background_bmp)
{
	   uint16_t height, width;
	int cursorx,cursory;
		uint8_t* color=( uint8_t *)(SRAM_BASE_ADDR + bmp_file->addr);
		uint8_t* back_color=( uint8_t *)(SRAM_BASE_ADDR + background_bmp->addr);
    width = bmp_file->w;          /* �õ����Ŀ�� */
    height = bmp_file->h;           /* �߶� */
	cursorx=x;
	cursory=y+height-1;
	uint16_t tempcolor;
					
		for(int i=0;i<height*width*2;i+=2)
				
		{
					if(cursorx==x+width)
					{
						cursorx=x;
						cursory--;
						lcd_set_cursor(cursorx, cursory); /* ���ù��λ�� */
						lcd_write_ram_prepare();  
					}

					if(cursory<24||cursory>lcddev.height-1)/* ������ʾ��Χ */
					{
						cursorx++;
						continue;
					}
					tempcolor=((((uint16_t)color[i+1])<<8)|((uint16_t)color[i]));
					if(tempcolor!=0xffff)
					{					
						LCD->LCD_RAM =tempcolor;
					}
					else
					{
						int num=lcddev.width*(lcddev.height-1-cursory)+cursorx;
						LCD->LCD_RAM =(((uint16_t)back_color[num*2+1])<<8)|((uint16_t)back_color[num*2]);
					}
					cursorx++;
		}
		lcd_set_cursor(480-1, 800-1);//���ù�굽��Ļ��ĩ ��ֹ��ԭ��������ȡ������Ϊ��ʾ����
}







/**
 * @brief       �ֲ�ˢ�±���ͼ  ����ͼ��Ҫ��LCD��Ļ��Сһ��
 * @param       x��y           ��ʾ��ʼλ��
 * @param       width��height  ��ʾ���ݵĿ���
 * @param       background_bmp Ҫ��ʾ�ı���ͼ����
 * @retval      ��
 */
void range_show_bmp_from_sram(int  x,int y,int width,int height,sram_bmp_file* background_bmp)
{
		int cursorx,cursory;
		uint8_t* back_color=( uint8_t *)(SRAM_BASE_ADDR + background_bmp->addr);
		cursorx=x;
		cursory=y+height-1;
				for(int i=0;i<height*width*2;i+=2)
		{
					if(cursorx==x+width)
					{
						cursorx=x;
						cursory--;
						lcd_set_cursor(cursorx, cursory); /* ���ù��λ�� */
						lcd_write_ram_prepare();  
					}			
					if(cursory<24||cursory>lcddev.height-1)/* ������ʾ��Χ */
					{
						cursorx++;
						continue;
					}
					int num=lcddev.width*(lcddev.height-1-cursory)+cursorx;/* ���㵱ǰ�����Ӧ�����ݵ�ַ */
					LCD->LCD_RAM =(((uint16_t)back_color[num*2+1])<<8)|((uint16_t)back_color[num*2]);
					cursorx++;
		}
		lcd_set_cursor(lcddev.width-1, lcddev.height-1);//���ù�굽��Ļ��ĩ ��ֹ��ԭ��������ȡ������Ϊ��ʾ����
}























char Load_bmp_with_backgroung_from_sram(uint16_t x,uint16_t y,char* path,sram_bmp_file* background_bmp) 
{
	FRESULT res;
	bmp_head bmp;
	uint32_t br;
	uint32_t cursorx=x,cursory=y;
	static uint8_t buf[2400];
	res=f_open(&SDFile,path,FA_READ);
	if(res==FR_OK)
	{
		if(f_read(&SDFile,(char*)&bmp+2,sizeof(bmp_head)-2,&br)==FR_OK)
		{			
			int Height=bmp.info.Height;
			int Width=bmp.info.Width;
			f_lseek(&SDFile,bmp.file.Offset);
				uint8_t* back_color=( uint8_t *)(SRAM_BASE_ADDR + background_bmp->addr);
				cursorx=x;
				cursory=y+Height-1;
			while(1)
			{
			if(f_read(&SDFile,buf,2400,&br)==FR_OK)
			{
				for(int i=0;i<br;i+=2)
				{
					if(cursorx==x+Width)
					{
						cursorx=x;
						cursory--;
						lcd_set_cursor(cursorx, cursory); /* ���ù��λ�� */
						lcd_write_ram_prepare();  
					}
					uint16_t tempcolor=(((uint16_t)buf[i+1])<<8)|((uint16_t)buf[i]);
					if(tempcolor!=0xffff)
					{					
						LCD->LCD_RAM =tempcolor;
					}
					else
					{
						int num=lcddev.width*(lcddev.height-1-cursory)+cursorx;
						LCD->LCD_RAM =(((uint16_t)back_color[num*2+1])<<8)|((uint16_t)back_color[num*2]);
					}
					cursorx++;
				}
			}
			else
			{
				break;
			}
			if(br==0)
			{
				break;
			}
		}
}
		f_close(&SDFile);
	lcd_set_cursor(480-1, 800-1);
		return 0;
	}
	else
		
	{
		printf("opened fail %x",res);
		return -1;
	}
	
}










//void show_bmp_from_sram(int  x,int y,sram_bmp_file* bmp_file)
//{
//uint16_t height, width;
//	int cursorx,cursory;

//		uint8_t picH,picL;
//    width = bmp_file->w;            /* �õ����Ŀ�� */
//    height = bmp_file->h;           /* �߶� */
//	cursorx=x;
//	cursory=y+height-1;
//	volatile uint8_t* color =(volatile uint8_t *)(SRAM_BASE_ADDR + bmp_file->addr);
//					
//		for(int i=0;i<height*width*2;i+=2)
//				
//		{
//					if(cursorx==x+width)
//					{
//						cursorx=x;
//						cursory--;
//						lcd_set_cursor(cursorx, cursory); /* ���ù��λ�� */
//						lcd_write_ram_prepare();  
//					}
//					
//		LCD->LCD_RAM =(((uint16_t)color)<<8)|((uint16_t)color[i]);
//					cursorx++;
//		}
//		lcd_set_cursor(480-1, 800-1);
//}

































/*******************���Ժ���**********************************/

/**
 * @brief       ���Ժ��� ��SRAMָ����ַд��1���ֽ�
 * @param       addr    : ��ʼд��ĵ�ַ(���32bit)
 * @param       data    : Ҫд����ֽ�
 * @retval      ��
 */
void sram_test_write(uint32_t addr, uint8_t data)
{
    sram_write(&data, addr, 1); /* д��1���ֽ� */
}

/**
 * @brief       ���Ժ��� ��SRAMָ����ַ��ȡ1���ֽ�
 * @param       addr    : ��ʼ��ȡ�ĵ�ַ(���32bit)
 * @retval      ��ȡ��������(1���ֽ�)
 */
uint8_t sram_test_read(uint32_t addr)
{
    uint8_t data;
    sram_read(&data, addr, 1); /* ��ȡ1���ֽ� */
    return data;
}
 


void fsmc_sram_test(void)
{
	  uint32_t i = 0;
    uint8_t temp = 0;
    uint8_t sval = 0; /* �ڵ�ַ0���������� */

    /* ÿ��4K�ֽ�,д��һ������,�ܹ�д��256������,�պ���1M�ֽ� */
    for (i = 0; i < 1024 * 1024; i += 4096)
    {
        sram_write(&temp, i, 1);
        temp++;
    }

    /* ���ζ���֮ǰд�������,����У�� */
    for (i = 0; i < 1024 * 1024; i += 4096)
    {
        sram_read(&temp, i, 1);

        if (i == 0)
        {
            sval = temp;
        }
        else if (temp <= sval)
        {
            break; /* �������������һ��Ҫ�ȵ�һ�ζ��������ݴ� */
        }
				printf("%d\n\r" ,(uint16_t)(temp - sval + 1) * 4);

    }
	
}