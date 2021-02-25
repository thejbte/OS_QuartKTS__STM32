/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Debounce.h
 * Author: Julian Bustamante
 *
 * Created on 1 de marzo de 2019, 12:23 AM
 */

#ifndef FSM_H
#define FSM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>    
 
#define DELAY_DEBOUNCE  40  /*40 mS*/

    
typedef enum {
	LOW_=0,
	HIGH_
}GPIO_PINState;


/*Pin entrada , boton*/
//typedef uint8_t (*PtrGpioMap_t)(void);

typedef enum{
    OFF=0,
    ON,    
    RISING,
    FALLING ,
    FLAG_UNKNOWN,
	PULL_UP,
	PULL_DOWN
}DebounceState_t;

typedef struct{
   volatile uint8_t         PinState,PreviousState_,FlagFalling,FlagRising;
   volatile uint8_t         Delay; /*mS*/
   volatile uint8_t         TimeCounter;
   volatile uint8_t         Status;
 }DebounceData_t;

 
void Debounce_Init(DebounceData_t *PtrDataStruct,uint32_t DebounceTick, DebounceState_t PULL_x);
void Debounce_Update(DebounceData_t *PtrDataStruct,uint8_t PinState);


#ifdef __cplusplus
}
#endif

#endif /* FSM_H */

