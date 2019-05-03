#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
void Get_Adc_Window0(u8 ch);
void Get_Adc_Window1(u8 ch);
void Get_Adc_Window2(u8 ch);
void Get_Adc_Window3(u8 ch);
 
 
extern int b0[30];
extern int b1[30];
extern int b2[30];
extern int b3[30];
extern int c0[31];
extern int c1[31];
extern int c2[31];
extern int c3[31];
extern u8 time0;
extern u8 time1;
extern u8 time2;
extern u8 time3;
#endif 
