#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
 
/* 
使用说明 	
TIM1的CH1和CH1N 产生带有死区的PWM波
TIM8的CH2和CH2N 产生带有死区的PWM波
同时 TIM1和TIM8波形有一定可控相位差
1.频率调节 TIM1_PWM_Init(1160,0);	TIM8_PWM_Init(1160,0);中的数
2.占空比调节 改变 TIM_SetCompare1(TIM1,580);	TIM_SetCompare2(TIM8,580); 580/1160 
3.移项角改变   改变TIM1_PWM_Init函数中的TIM1->CCR2值
4.改变死区时间 改变TIM1_PWM_Init函数和TIM8_PWM_Init函数中的TIM_BDTRInitStructure.TIM_DeadTime 
  死区时间计算参考： https://www.cnblogs.com/NickQ/p/8550901.html

*/	

// ADC1 Chanel0,1,2,3  -> PA0,1,2,3
	u16 adcx0,adcx1,adcx2,adcx3;
u8 a;
 int main(void)
 {		
 	u16 led0pwmval=0;
	u8 dir=1;	

	float temp;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
  TIM1_PWM_Init(1160,0);	 //不分频。PWM频率=72000000/1161=62Khz
	TIM8_PWM_Init(1160,0);	 //不分频。PWM频率=72000000/1161=62Khz
	Adc_Init();		  		//ADC初始化
	 a=0;
   	while(1)
	{								 
		a=1;
		TIM_SetCompare1(TIM1,580);		   // 设置TIM1通道1占空比 = 580/1160
		TIM_SetCompare2(TIM8,580);		   // 设置TIM8通道2占空比 = 580/1160
//	a=2;
//		delay_ms(500);
		adcx0=Get_Adc_Average(ADC_Channel_0,10);
		temp=(float)adcx0*(3.3/4096);
		a=3;
//		adcx0=10;
		adcx1=Get_Adc_Average(ADC_Channel_1,10);
		adcx2=Get_Adc_Average(ADC_Channel_2,10);
		adcx3=Get_Adc_Average(ADC_Channel_3,10);

		delay_ms(200);	
		
//		delay_ms(1000);	
	}	 
 }

