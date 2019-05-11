#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "median_filter.h"
#include "nokia_5110.h" 
#include "timer3.h"
/* 
ʹ��˵�� 	
TIM1��CH1��CH1N ��������������PWM��
TIM8��CH2��CH2N ��������������PWM��
ͬʱ TIM1��TIM8������һ���ɿ���λ��
1.Ƶ�ʵ��� TIM1_PWM_Init(1160,0);	TIM8_PWM_Init(1160,0);�е���
2.ռ�ձȵ��� �ı� TIM_SetCompare1(TIM1,580);	TIM_SetCompare2(TIM8,580); 580/1160 
3.����Ǹı�   �ı�TIM1_PWM_Init�����е�TIM1->CCR2ֵ
4.�ı�����ʱ�� �ı�TIM1_PWM_Init������TIM8_PWM_Init�����е�TIM_BDTRInitStructure.TIM_DeadTime 
  ����ʱ�����ο��� https://www.cnblogs.com/NickQ/p/8550901.html

*/	

// ADC1 Chanel0,1,2,3  -> PA0,1,2,3
	u16 adcx0,adcx1,adcx2,adcx3;
	float temp0,temp1,temp2,temp3,temp;
int a1,a2,a3,a0,a;
u16 I1=0;
int b0[200]={0};int b1[200]={0};int b2[200]={0};int b3[200]={0};
int c0[201],c1[201],c2[201],c3[201];
u8 time0=0;u8 time1=0;u8 time2=0;u8 time3=0;
    char str0[10]="0";   // ���鳤�Ȳ���ȡ̫С������ʾ��������
		char str1[10]="0";
		char str2[10]="0";
		char str3[10]="0";
 int main(void)
 {		
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
	TIM3_Int_Init(199,7199);//10Khz�ļ���Ƶ�ʣ�������200Ϊ20ms  
  TIM1_PWM_Init(1160,0);	 //����Ƶ��PWMƵ��=72000000/1161=62Khz
	TIM8_PWM_Init(1160,0);	 //����Ƶ��PWMƵ��=72000000/1161=62Khz
	Adc_Init();		  		//ADC��ʼ��
	LCD_init(); //?????    
	LCD_clear(); 
   	while(1)
	{								 

		TIM_SetCompare1(TIM1,580);		   // ����TIM1ͨ��1ռ�ձ� = 580/1160
		TIM_SetCompare2(TIM8,580);		   // ����TIM8ͨ��2ռ�ձ� = 580/1160

//		delay_ms(50);
//		Get_Adc_Window0(ADC_Channel_0);
//		Get_Adc_Window1(ADC_Channel_1);
//		Get_Adc_Window2(ADC_Channel_2);
//		Get_Adc_Window3(ADC_Channel_3);
//		a0= GetMedianNum(b0, 31);
//		a1= GetMedianNum(b1, 31);
//		a2= GetMedianNum(b2, 31);
//		a3= GetMedianNum(b3, 31);
//		temp0=temp0+1;
//		a=Get_Adc_Average(ADC_Channel_0,30);

//		temp=(float)(a*0.0033-4.85);
//    temp0=(float)(a0*0.0033-4.85);
//		temp1=(float)a1*(3.3/4096);
//		temp2=(float)a2*(3.3/4096);
//		temp3=(float)a3*(3.3/4096);
		Get_Adc_Window0(ADC_InjectedChannel_1);
		Get_Adc_Window1(ADC_InjectedChannel_2);
		Get_Adc_Window2(ADC_InjectedChannel_3);
		Get_Adc_Window3(ADC_InjectedChannel_4);
		a0= GetMedianNum(b0, 201);
		a1= GetMedianNum(b1, 201);
		a2= GetMedianNum(b2, 201);
		a3= GetMedianNum(b3, 201);
		
    sprintf(str0,"%.2f",temp0);
		sprintf(str1,"%.2f",temp1);
		sprintf(str2,"%.2f",temp2);
		sprintf(str3,"%.2f",temp3);


		
		LCD_write_english_string(0,0,"Iin:");
		LCD_write_english_string(30,0,str0);
		LCD_write_english_string(75,0,"A");
		
		LCD_write_english_string(0,9,"Vin:");
		LCD_write_english_string(30,9,str1);
		LCD_write_english_string(75,9,"V");
		
		LCD_write_english_string(0,18,"Iout:");
		LCD_write_english_string(30,18,str2);
		LCD_write_english_string(75,18,"A");
		
		LCD_write_english_string(0,27,"Vout:");
		LCD_write_english_string(30,27,str3);
		LCD_write_english_string(75,27,"V");
		
		LCD_write_english_string(0,37,"e:");
    LCD_write_english_string(30,37,"0.85");
		LCD_write_english_string(75,37,"%");

	}	 
 }

