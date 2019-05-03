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
int a1,a2,a3,a0;
u16 I1=0;
int b0[30]={0};int b1[30]={0};int b2[30]={0};int b3[30]={0};
int c0[31],c1[31],c2[31],c3[31];
u8 time0=0;u8 time1=0;u8 time2=0;u8 time3=0;
    char str0[3]="0";
		char str1[3]="0";
		char str2[3]="0";
		char str3[3]="0";
 int main(void)
 {		
	float temp0,temp1,temp2,temp3;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
  TIM1_PWM_Init(1160,0);	 //不分频。PWM频率=72000000/1161=62Khz
	TIM8_PWM_Init(1160,0);	 //不分频。PWM频率=72000000/1161=62Khz
	Adc_Init();		  		//ADC初始化
	LCD_init(); //?????    
	LCD_clear(); 
   	while(1)
	{								 

		TIM_SetCompare1(TIM1,580);		   // 设置TIM1通道1占空比 = 580/1160
		TIM_SetCompare2(TIM8,580);		   // 设置TIM8通道2占空比 = 580/1160

		delay_ms(50);
		Get_Adc_Window0(ADC_Channel_0);
		Get_Adc_Window1(ADC_Channel_1);
		Get_Adc_Window2(ADC_Channel_2);
		Get_Adc_Window3(ADC_Channel_3);
		a0= GetMedianNum(b0, 31);
		a1= GetMedianNum(b1, 31);
		a2= GetMedianNum(b2, 31);
		a3= GetMedianNum(b3, 31);

//		adcx0=Get_Adc_Average(ADC_Channel_0,10);
//		temp=(float)adcx0*(3.3/4096);
    temp0=(float)a0*(3.3/4096);
		temp1=(float)a1*(3.3/4096);
//		temp2=(float)a2*(3.3/4096);
//		temp3=(float)a3*(3.3/4096);
    sprintf(str0,"%.3f",temp0);
		sprintf(str1,"%.3f",temp1);
//		sprintf(str2,"%.3f",temp2);
//		sprintf(str3,"%.3f",temp3);


		
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

