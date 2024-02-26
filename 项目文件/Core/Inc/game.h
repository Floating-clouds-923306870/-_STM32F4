#ifndef __GAME_H
#define __GAME_H

#include "sram.h"
#include "usart.h"
#include "main.h"
#include "lcd.h"
#include "delay.h"
#include "touch.h"
#include "rng.h"
#include <stdlib.h>

#define LCDWIDTH 480

#define CHANNEL_1 (LCDWIDTH/6)
#define CHANNEL_2 (LCDWIDTH/2)
#define CHANNEL_3 (LCDWIDTH*5/6)

#define HONGBAO 0 //item_name
#define LUOBO 1


typedef struct xinnai_item 
{
	sram_bmp_file* bmp_file;
	int pos_y;
	int last_pos_x;
	int cur_pos_x;
	
}xinnai_item;

typedef struct drop_node 
{
	sram_bmp_file* bmp_file;
	int pos_channel;//choose from CHANNEL_1 CHANNEL_2 CHANNEL_3
	int pos_x;
	int last_pos_y;
	int cur_pos_y;
	int NAME;//choose from HONGBAO LUOBO
	struct drop_node* next;
	
}drop_node;

extern int DROP_SPEED;
extern int point;
extern int count_down;
extern int health_point;
	
extern drop_node* HEAD;
extern sram_bmp_file* xinnai;
extern sram_bmp_file* xinnai_sad;
extern sram_bmp_file* xinnai_happy;
extern sram_bmp_file* back;
extern sram_bmp_file* hongbao;
extern sram_bmp_file* luobo;

extern sram_bmp_file* DROP_BMP_FILE[2];

extern xinnai_item *XINNAI_ITEM;

extern int XINNAI_W;
extern int x_XINNAI;


int rand_int();//���������

void game_init();   //��ʼ����Ϸ
void game_reinit();//���³�ʼ����Ϸ

drop_node* create_drop_item(int item_name,int channel);  //����һ�������������
drop_node* place_drop_item();//����һ�������������
void add_new_drop_item(void);//���������������ӵ�����������
int check_overlap_with_xinnai(drop_node* drop_item);//���������������Ƿ�����νӴ�
int check_drop_item(drop_node* drop_item);//���������������Ƿ������������
void destroy_drop_item(void);//��������Ӧ�ñ����ٵ������������

void move_drop_item(drop_node* drop_item);//�����ƶ������������
void move_all_drop_item(void);//�����ƶ������������е������������
void move_xinnai(void);//�����ƶ�����

void show_move_drop(drop_node* drop_item,sram_bmp_file* background);//����ˢ����Ļ ��ʾһ�������������
void show_all_move_drop(void);//����ˢ����Ļ ��ʾ���������������
void show_move_xinnai(void);//����ˢ����Ļ ��ʾ����

int update_xinnai_pos(void);//�Ӵ���ģ���ȡ��������λ��

int check_click(int x,int w,int y,int h);//������Ƿ���������

void game(void);//��Ϸ����

#endif