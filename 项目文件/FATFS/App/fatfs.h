/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.h
  * @brief  Header for fatfs applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __fatfs_H
#define __fatfs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h" /* defines SD_Driver as external */

/* USER CODE BEGIN Includes */

#include "lcd.h"
#include "sram.h"
/* USER CODE END Includes */



extern uint8_t retSD; /* Return value for SD */
extern char SDPath[4]; /* SD logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern FIL SDFile; /* File object for SD */

void MX_FATFS_Init(void);

/* USER CODE BEGIN Prototypes */

typedef struct bmp_file_struct { 
uint16_t   None; 
uint16_t   Type;// �ļ������ͣ���ֵ������0x4D42��Ҳ�����ַ�'BM'��
uint32_t   Size; // λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
uint16_t   Reserved1; // ��������������Ϊ0
uint16_t   Reserved2; // ��������������Ϊ0
uint32_t   Offset; // λͼ���ݾ����ļ���ͷƫ���������ֽ�Ϊ��λ
} bmp_file;

typedef struct bmp_info_struct{ 
uint32_t     Size; // BITMAPINFOHEADER�ṹ����Ҫ������
uint32_t     Width; // ͼ���ȣ���λΪ����
uint32_t      Height; // ͼ��߶ȣ���λΪ���أ���������˵��ͼ���������
uint16_t      Planes; // ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1
uint16_t     Count; // һ������ռ�õ�bitλ��ֵλ1��4��8��16��24��32
uint32_t     Compression; // ѹ������
uint32_t     SizeImage; // λͼ���ݵĴ�С�����ֽ�Ϊ��λ
uint32_t     Xmeter; // ˮƽ�ֱ��ʣ���λ ����/��
uint32_t     Ymeter; // ��ֱ�ֱ��ʣ���λ ����/��
uint32_t     Cused; 
uint32_t     Cimportant; 
} bmp_info;

typedef struct bmp_head_file{ 
bmp_file file;
bmp_info info;
} bmp_head;

typedef struct chinese_char{
	uint16_t len;
	uint16_t size;
	uint8_t* data;
	struct chinese_char* next;
	
}chinese_char;






FRESULT scan_files(char *path);
void show_chinese_char(uint8_t* gbk,uint16_t size, uint16_t x,uint16_t y);
chinese_char* load_chinese_char(uint8_t* gbk,uint16_t size);
void show_chinese_from_struct(int x,int y,chinese_char*CHINESE_CH);
void show_chinese_str_from_struct(int x,int y,chinese_char*CHINESE_STR);
chinese_char* load_chinese_str(char *str,uint16_t size);

char Load_bmp(uint16_t x,uint16_t y,char* path) ;
char show_bmp_8bit(uint16_t x,uint16_t y,char* path);



/* USER CODE END Prototypes */
#ifdef __cplusplus
}
#endif
#endif /*__fatfs_H */
