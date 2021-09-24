#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"

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

void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio){
	// enable IT Timer overflow
    Timer->DIER |= 0x1;
		// les codes IRQ negatifs sont pour le systeme interne du processeur
    // les codes IRQ positifs sont pour ce qui est externe
    // NVIC_EnableIRQ(...) function in startup
    // NVIC_SetPriority(...) function in startup
	
		if(Timer == TIM1){
  		NVIC_EnableIRQ(TIM1_UP_IRQn);
      //NVIC_SetPriority(TIM1_UP_IRQn,Prio);
  	}else if (Timer == TIM2){
  		NVIC_EnableIRQ(TIM2_IRQn);
      //NVIC_SetPriority(TIM2_IRQn,Prio);
    }else if (Timer == TIM3) {
  		NVIC_EnableIRQ(TIM3_IRQn);
      //NVIC_SetPriority(TIM3_IRQn,Prio);
  	}else if (Timer == TIM4){
  		NVIC_EnableIRQ(TIM4_IRQn);
      //NVIC_SetPriority(TIM4_IRQn,Prio);
  	};
}

  /*
  1. Analyser le périphérique et repérer l’événement à prendre en compte
	2. Trouver le numéro (et donc le vecteur associé) de l’interruption concernée
	3. Configurer les registres du périphérique pour valider en local l’envoi d’une demande d’interruption
	4. Fixer dans le NVIC la priorité de l’interruption
	5. Autoriser dans le NVIC la prise en compte de l’interruption
	6. Trouver le nom du Handler de l’interruption et écrire une routine avec le même prototype quine sera pas weak. Dans cette routineil est impératif d’effacer le bit du périphérique quiprovoque le déclenchement de l’interruptionfaute de quoi celle-ci sera derechef activée auretour (même si dans cer-tains rares cas cela est fait automatiquement...).
	*/

  void TIM4_IRQHandler(void){
		TIM4->SR &= ~TIM_SR_UIF;
		
		
  };



