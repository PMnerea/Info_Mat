#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"

// TIM1 Update interrupt postition 25
#define TIM1_UPDATE_INTERRUPT_POS 25;
// TIM2 interrupt general position 28
#define TIM2_GENERAL_INTERRUPT_POS 28;
// TIM3 interrupt general position 29
#define TIM3_GENERAL_INTERRUPT_POS 29;
// TIM4 interrupt general position 30
#define TIM4_GENERAL_INTERRUPT_POS 30;

// 4 pointeurs pour les 4 timers
static void (* pFuncTIM1) (void);
static void (* pFuncTIM2) (void);
static void (* pFuncTIM3) (void);
static void (* pFuncTIM4) (void);

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer){
	if (Timer->TIMER == TIM1) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		TIM1->ARR = Timer->ARR;
		TIM1->PSC = Timer->PSC;
		TIM1->CR1 |= 0x1;
	}
	else if (Timer->TIMER == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		TIM2->ARR = Timer->ARR;
		TIM2->PSC = Timer->PSC;
		TIM2->CR1 |= 0x1;
	}
	else if (Timer->TIMER == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		TIM3->ARR = Timer->ARR;
		TIM3->PSC = Timer->PSC;
		TIM3->CR1 |= 0x1;
	}
	else if (Timer->TIMER == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		TIM4->ARR = Timer->ARR;
		TIM4->PSC = Timer->PSC;
		TIM4->CR1 |= 0x1;
	}
}

  /*
  1. Analyser le périphérique et repérer l’événement à prendre en compte
	2. Trouver le numéro (et donc le vecteur associé) de l’interruption concernée
	3.Configurer les registres du périphérique pour valider en local l’envoi d’une demande d’interruption
	4. Fixer dans le NVIC la priorité de l’interruption
	5. Autoriser dans le NVIC la prise en compte de l’interruption
	6.Trouver le nom du Handler de l’interruption et écrire une routine avec le même prototype quine sera pas weak. Dans cette routineil est impératif d’effacer le bit du périphérique quiprovoque le déclenchement de l’interruptionfaute de quoi celle-ci sera derechef activée auretour (même si dans cer-tains rares cas cela est fait automatiquement...).

  void TIM4_IRQHandler(void){
    TIM4->DIER &= 0x0 <<8;
    if(pFuncTIM1 != 0){
      (*pFuncTIM4)();
    };
  };*/



