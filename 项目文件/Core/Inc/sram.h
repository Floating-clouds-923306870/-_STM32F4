#ifndef __SRAM_H
#define __SRAM_H

#include "main.h"
#include "fatfs.h"

/******************************************************************************************/
/* SRAM WR/RD/CS ���� ���� 
 * SRAM_D0~D15 �� ��ַ��,��������̫��,�Ͳ������ﶨ����,ֱ����SRAM_init�����޸�.��������ֲ��ʱ��,
 * ���˸���3��IO��, ���ø�SRAM_init����� ������ �� ��ַ�� ���ڵ�IO��.
 */

#define SRAM_WR_GPIO_PORT               GPIOD
#define SRAM_WR_GPIO_PIN                GPIO_PIN_5
#define SRAM_WR_GPIO_CLK_ENABLE()       do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)     /* ����IO��ʱ��ʹ�� */

#define SRAM_RD_GPIO_PORT               GPIOD
#define SRAM_RD_GPIO_PIN                GPIO_PIN_4
#define SRAM_RD_GPIO_CLK_ENABLE()       do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)     /* ����IO��ʱ��ʹ�� */

/* SRAM_CS(��Ҫ����SRAM_FSMC_NEX������ȷ��IO��) ���� ���� */
#define SRAM_CS_GPIO_PORT                GPIOG
#define SRAM_CS_GPIO_PIN                 GPIO_PIN_10
#define SRAM_CS_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* ����IO��ʱ��ʹ�� */

/* FSMC��ز��� ���� 
 * ע��: ����Ĭ����ͨ��FSMC��3������SRAM, ��1��4��Ƭѡ: FSMC_NE1~4
 *
 * �޸�SRAM_FSMC_NEX, ��Ӧ��SRAM_CS_GPIO�������Ҳ�ø�
 */
#define SRAM_FSMC_NEX           3         /* ʹ��FSMC_NE3��SRAM_CS,ȡֵ��Χֻ����: 1~4 */

#define SRAM_FSMC_BCRX          FSMC_Bank1->BTCR[(SRAM_FSMC_NEX - 1) * 2]       /* BCR�Ĵ���,����SRAM_FSMC_NEX�Զ����� */
#define SRAM_FSMC_BTRX          FSMC_Bank1->BTCR[(SRAM_FSMC_NEX - 1) * 2 + 1]   /* BTR�Ĵ���,����SRAM_FSMC_NEX�Զ����� */
#define SRAM_FSMC_BWTRX         FSMC_Bank1E->BWTR[(SRAM_FSMC_NEX - 1) * 2]      /* BWTR�Ĵ���,����SRAM_FSMC_NEX�Զ����� */

/******************************************************************************************/

/* SRAM����ַ, ���� SRAM_FSMC_NEX ��������������ַ��ַ
 * ����һ��ʹ��FSMC�Ŀ�1(BANK1)������SRAM, ��1��ַ��Χ�ܴ�СΪ256MB,���ֳ�4��:
 * �洢��1(FSMC_NE1)��ַ��Χ: 0X6000 0000 ~ 0X63FF FFFF
 * �洢��2(FSMC_NE2)��ַ��Χ: 0X6400 0000 ~ 0X67FF FFFF
 * �洢��3(FSMC_NE3)��ַ��Χ: 0X6800 0000 ~ 0X6BFF FFFF
 * �洢��4(FSMC_NE4)��ַ��Χ: 0X6C00 0000 ~ 0X6FFF FFFF
 */
#define SRAM_BASE_ADDR         (0X60000000 + (0X4000000 * (SRAM_FSMC_NEX - 1)))

typedef struct sram_bmp_file{
	uint32_t addr;
	uint32_t len;
	uint32_t h;
	uint32_t w;
} sram_bmp_file;









extern SRAM_HandleTypeDef g_sram_handler;    /* SRAM��� */

extern uint32_t sram_current_add;
	
void sram_init(void);
void sram_write(uint8_t *pbuf, uint32_t addr, uint32_t datalen);
void sram_read(uint8_t *pbuf, uint32_t addr, uint32_t datalen);

uint8_t sram_test_read(uint32_t addr);
void sram_test_write(uint32_t addr, uint8_t data);
void fsmc_sram_test(void);
sram_bmp_file* sram_load_bmp_from_sd(char* path);//��sd������ͼƬ��sram
void show_bmp_from_sram(int  x,int y,sram_bmp_file* bmp_file);//��sram��ʾͼƬ
void show_bmp_from_sram_with_background(int  x,int y,sram_bmp_file* bmp_file,sram_bmp_file* background_bmp);//��sram��ʾ���б�����ͼƬ��ͼƬ��ɫ������ʾΪ��Ӧλ�õı�����
void range_show_bmp_from_sram(int  x,int y,int width,int height,sram_bmp_file* background_bmp);//��sram��ʾ����ͼƬ��һ������
char Load_bmp_with_backgroung_from_sram(uint16_t x,uint16_t y,char* path,sram_bmp_file* background_bmp) ;//��sd����ʾ���б�����ͼƬ��ͼƬ��ɫ������ʾΪ��Ӧλ�õı�����
#endif