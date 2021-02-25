/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Debounce.h"
/*
 =================================================================================================
              	  	  	  	 	##### Initialization functions #####
 =================================================================================================
 */
/*
 * Funci�n: Debounce_Init
 * --------------------------
 *
 * PtrDataStruct: Especifica datos del retardo, antirebote y estado del bot�n
 * 
 * DebounceTick: Especifica el tiempo del retardo para el antirebote  de acuerdo al tiempo de ejecuci�n de Debounce_Update()
 *		Ej:
 *			 Si Debounce_Update(); se ejecuta cada 1ms, DebounceTick =40 ;   **40ms**
 * 			 Si Debounce_Update(); se ejecuta cada 10ms, DebounceTick =4 ;   **40ms**
 *
 * PULL_x = PULLUP,   Si pulsador fisico tiene pullUp.
 * PULL_x = PULLDOWN, Si pulsador fisico tiene pullDown.
 *
 *
 * Ej:  Debounce_Init(&DebounceData,40, PULLUP);
 *
 */
void Debounce_Init(DebounceData_t *PtrDataStruct,uint32_t DebounceTick, DebounceState_t PULL_x){
    PtrDataStruct->Delay=DebounceTick; /*DELAY_DEBOUNCE;*/
    PtrDataStruct->PreviousState_ = (PULL_x == PULL_UP) ? HIGH_:LOW_;
    PtrDataStruct->PreviousState_ = (PULL_x == PULL_DOWN) ? LOW_:HIGH_;
    PtrDataStruct->FlagFalling = 0;
    PtrDataStruct->FlagRising = 0;
}


/*
 =================================================================================================
              	  	  	  	  	  ##### Debounce  functions #####
 =================================================================================================
 */
/**
 * Funci�n: Debounce_Update
 * ----------------------------
 *
 * PtrDataStruct: Especifica datos del retardo, antirebote, estado del boton, la funci�n modifica por referencia FlagFalling o FlagRising
 *
 * PinState: 	Especifica el estado actual del pin de entrada (pulsador).
 *
 * Return:  OFF		=	0  Pulsador OFF
 * 			ON		=   1  Pulsador ON
 * 			RISING  =	2  Flanco subida
 * 			FALLING =	3  Flanco Bajada
 *			FLAG_UNKNOWN = 4
 * Nota: Colocar Debounce_Update() en una tarea que se ejecute cada 1ms, DebounceTick=40; **40ms**
 * 		 La variable a donde retorna el rebote , debe ser volatile.
 *
 * Ej: 	Debounce_Update(&DebounceData, HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13));
 *
 */

void Debounce_Update(DebounceData_t *PtrDataStruct,uint8_t PinState){
    if((PtrDataStruct->PreviousState_ && !PinState ) || (!PtrDataStruct->PreviousState_ && PinState) ){ /*FALLING*/
        if(PtrDataStruct->TimeCounter++ >= PtrDataStruct->Delay){  /* 40 ms*/
			if(PtrDataStruct->PreviousState_ && !PinState) {PtrDataStruct->Status = FALLING; PtrDataStruct->FlagFalling = 1;}
        	if(!PtrDataStruct->PreviousState_ && PinState) {PtrDataStruct->Status = RISING; PtrDataStruct->FlagRising = 1; }
        	PtrDataStruct->PreviousState_ = PinState;
         	PtrDataStruct->TimeCounter=0;
		}else PtrDataStruct->Status =FLAG_UNKNOWN;

    }else   PtrDataStruct->Status = PinState;
}
