#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#define DIODE 5
#define PCB_EXT 8
#define LED_EXT 10
#define BUTTON 13


void callback(MyGPIO_Struct_TypeDef Led) {
	MyGPIO_Toggle(Led.GPIO, Led.GPIO_Pin);
}

int main(void){
	//RCC->APB2ENR |= (0x01 << 2) | (0x01<< 3) | (0x01 << 4); // Allumer la clock
	// Test allumage du timer 2 manuelement
	/*RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->ARR = 5999;
	TIM2->PSC = 5999;
	TIM2->CR1 |= 0x1;*/
	
	MyGPIO_Struct_TypeDef Led; 
	MyTimer_Struct_TypeDef TIM;
	
	Led.GPIO = GPIOB; 
	Led.GPIO_Pin = 6; 
	Led.GPIO_Conf = ALTOUT_PPULL;
	
	MyGPIO_Init(&Led); 
	
	// Test allumage d'un timer entre 1 et 4 en passant par la librairie
	TIM.TIMER = TIM4;
	TIM.ARR = 719;
	TIM.PSC = 0;
	MyTimer_Base_Init(&TIM);
	//MyTimer_ActiveIT(TIM.TIMER, 4, callback);
	
	MyTimer_PWM(TIM.TIMER ,1, 10);
	while(1);
}
