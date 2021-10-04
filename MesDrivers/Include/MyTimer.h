#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct
{
	TIM_TypeDef * TIMER; // TIM1 � TIM4
	unsigned short ARR;
	unsigned short PSC;
} MyTimer_Struct_TypeDef;


/*
*****************************************************************************************
* @brief
* @param -> Param�tre sous forme d�une structure (son adresse) contenant les informations de base
* @Note -> Fonction � lancer syst�matiquement avant d�aller plus en d�tail dans les conf plus fines (PWM, codeurinc...)
*****************************************************************************************
*/

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer);
void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_function)(void));
// RC correspond au Rapport Cyclique de la PWM, c'est un pourcentage
void MyTimer_PWM(TIM_TypeDef*Timer ,char Channel, int RC);

#define MyTimer_Base_Start(Timer)(Timer->TimId->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer)(Timer->TimId->CR1 |= 0x0)

#endif
