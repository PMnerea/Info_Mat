#include "stm32f10x.h"
#include "Driver_GPIO.h"
#define DIODE 5
#define BUTTON 13
#define PCB_EXT 8
#define LED_EXT 10
//#define OUTPUT_PUSH_PULL 0x2
#define BIT_A_1 0x1
#define BIT_A_0 0x0

int main(void) 
{
	//RCC->APB2ENR |= (0x01 << 2) | (0x01<< 3) | (0x01 << 4); // Allumer la clock
	
	// Projet 1
	/*GPIOA->CRL &= ~(0xF << 4*DIODE); // masque : on veut remettre à 0 la 5eme broche qui correspond à la diode
	GPIOA->CRL |= (OUTPUT_PUSH_PULL << 4*DIODE); // masque : on veut que la diode soit en mode push_pull
	GPIOA->ODR |= (BIT_A_1 << DIODE); // masque : on veut le 5eme bit de ODR à 1 pour allumer la diode
	while(1) {
		if (GPIOC->IDR &= (BIT_A_1 << BUTTON)) {
			GPIOA->ODR &= ~(BIT_A_1 << DIODE); // éteindre la led
		} else {
			GPIOA->ODR |= (BIT_A_1 << DIODE); // allumer la led
		}
	}*/
	
	// Projet 2
	/*GPIOC->CRH &= ~(0xF << 4*(LED_EXT-8)); // masque : on veut remettre à 0 la 5eme broche qui correspond à la diode
	GPIOC->CRH |= (OUTPUT_PUSH_PULL << 4*(LED_EXT-8)); // masque : on veut que la diode soit en mode push_pull
	GPIOC->ODR |= (BIT_A_1 << LED_EXT); // masque : on veut le 5eme bit de ODR à 1 pour allumer la diode
	while(1) {
		if (GPIOC->IDR &= (BIT_A_1 << PCB_EXT)) {
			GPIOC->ODR &= ~(BIT_A_1 << LED_EXT); // éteindre la led
		} else {
			GPIOC->ODR |= (BIT_A_1 << LED_EXT); // allumer la led
		}
	}*/
	
	// Test librairie
	MyGPIO_Struct_TypeDef Led; 
	MyGPIO_Struct_TypeDef Bouton; 
	
	Led.GPIO = GPIOA; 
	Led.GPIO_Pin = 5; 
	Led.GPIO_Conf = OUT_PPULL;
	
	Bouton.GPIO = GPIOC;
	Bouton.GPIO_Pin = 13; 
	Bouton.GPIO_Conf = IN_FLOATING;
	
	MyGPIO_Init(&Led); 
	MyGPIO_Init(&Bouton); 
	
	while(1) {
		if (MyGPIO_Read(Bouton.GPIO, Bouton.GPIO_Pin)) {
			MyGPIO_Reset ( Led.GPIO , Led.GPIO_Pin ); // éteindre la led
		} else {
			MyGPIO_Set ( Led.GPIO , Led.GPIO_Pin ); // allumer la led
		}
	}
}
