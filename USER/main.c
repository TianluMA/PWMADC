#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "median_filter.h"
#include "nokia_5110.h" 
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
int a;
u16 I1=0;
int b[30]={0};
int c[31];
u8 time=0;

 int main(void)
 {		
	float temp=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
  TIM1_PWM_Init(1160,0);	 //����Ƶ��PWMƵ��=72000000/1161=62Khz
	TIM8_PWM_Init(1160,0);	 //����Ƶ��PWMƵ��=72000000/1161=62Khz
	Adc_Init();		  		//ADC��ʼ��
	LCD_init(); //?????    
	LCD_clear(); 
   	while(1)
	{								 

		TIM_SetCompare1(TIM1,580);		   // ����TIM1ͨ��1ռ�ձ� = 580/1160
		TIM_SetCompare2(TIM8,580);		   // ����TIM8ͨ��2ռ�ձ� = 580/1160
//	a=2;
		delay_ms(50);
		Get_Adc_Window(ADC_Channel_0);
		a= GetMedianNum(b, 31);
//		printf("%d\r\n",a);
		adcx0=Get_Adc_Average(ADC_Channel_0,10);
		temp=(float)adcx0*(3.3/4096);
//		a=3;

		adcx1=Get_Adc_Average(ADC_Channel_1,10);
		adcx2=Get_Adc_Average(ADC_Channel_2,10);
		adcx3=Get_Adc_Average(ADC_Channel_3,10);

//		delay_ms(200);	
		LCD_write_english_string(0,0,"frequence:");
//		delay_ms(1000);	
	}	 
 }

