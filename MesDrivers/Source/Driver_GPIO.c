#include "Driver_GPIO.h"
#include "stm32f10x.h"

void GPIO_Init_Input_ODR( MyGPIO_Struct_TypeDef * GPIOStructPtr) {
    // Pour différencier InPullDown et InPullUp 
    if ((int)GPIOStructPtr->GPIO_Conf == IN_PULLDOWN) {
        GPIOStructPtr->GPIO->ODR &= 0x0 << GPIOStructPtr->GPIO_Pin;
        GPIOStructPtr->GPIO_Conf = 0x8;
    }
    else if ((int)GPIOStructPtr->GPIO_Conf == IN_PULLUP) {
        GPIOStructPtr->GPIO->ODR &= 0x0 << GPIOStructPtr->GPIO_Pin;
        GPIOStructPtr->GPIO->ODR |= 0x1 << GPIOStructPtr->GPIO_Pin;
        GPIOStructPtr->GPIO_Conf = 0x8;
    }
} 

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr) {
    // Initialisation de l'horloge
    RCC->APB2ENR |= (0x01 << 2) | (0x01<< 3) | (0x01 << 4);
    // On fait la différence entre les high register et les low register
    if (GPIOStructPtr->GPIO_Pin < 8) {
        GPIO_Init_Input_ODR(GPIOStructPtr); 
				// Accéder au registre correspondant et l'allumer
        GPIOStructPtr->GPIO->CRL &= ~(0xF << 4 * GPIOStructPtr->GPIO_Pin); 
        GPIOStructPtr->GPIO->CRL |= GPIOStructPtr->GPIO_Conf << 4*GPIOStructPtr->GPIO_Pin; 
			// Modification de l'ODR
				GPIOStructPtr->GPIO->ODR |= (0x1 << GPIOStructPtr->GPIO_Pin);
    }
    else {
        GPIO_Init_Input_ODR(GPIOStructPtr); 
				// Accéder au registre correspondant et l'allumer
        GPIOStructPtr->GPIO->CRH &= ~(0xF << 4 * (GPIOStructPtr->GPIO_Pin-8)); 
        GPIOStructPtr->GPIO->CRH |= GPIOStructPtr->GPIO_Conf << 4*(GPIOStructPtr->GPIO_Pin-8);
				// Modification de l'ODR
				GPIOStructPtr->GPIO->ODR |= (0x1 << GPIOStructPtr->GPIO_Pin);
    }
}

int MyGPIO_Read( GPIO_TypeDef * GPIO , char GPIO_Pin ){
    // Renvoi le numéro de pin
    int res = 0; 
    res = GPIO -> IDR & 0x1<<GPIO_Pin;
    return res; 
}

void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
    // Set le pin à 1
    GPIO->ODR |= 0x1 << GPIO_Pin; 
}

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
    // Reset le pin à 0
    GPIO->ODR &= ~(0x1 << GPIO_Pin);
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
    // Inverse la valeur du pin 
    // Créer un masque avec juste le bit du pin à 1 pour pouvoir
    char idrPin = 0x1 << GPIO_Pin;
    // Si le bit du pin est à 1 alors on le met à 0 et inversement
    if (GPIO -> IDR & idrPin) {
        MyGPIO_Reset(GPIO, GPIO_Pin);
    }
    else {
        MyGPIO_Set(GPIO, GPIO_Pin); 
    }
}
