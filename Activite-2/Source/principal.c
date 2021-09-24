#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#define DIODE 5
#define PCB_EXT 8
#define LED_EXT 10
#define BUTTON 13


int main(void){
	//RCC->APB2ENR |= (0x01 << 2) | (0x01<< 3) | (0x01 << 4); // Allumer la clock
	// Test allumage du timer 2 manuelement
	/*RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->ARR = 5999;
	TIM2->PSC = 5999;
	TIM2->CR1 |= 0x1;*/
	
	// Test allumage d'un timer entre 1 et 4 en passant par la librairie
	MyTimer_Struct_TypeDef TIM;
	TIM.TIMER = TIM4;
	TIM.ARR = 5999;
	TIM.PSC = 5999;
	MyTimer_Base_Init(&TIM);
	MyTimer_ActiveIT(TIM.TIMER, 4);
	
	while(1);
}
