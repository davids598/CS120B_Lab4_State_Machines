/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_States {SM_Start, SM_Begin, SM_Swap, SM_Hold} SM_State;

void Tick() {
  switch (SM_State) {
    case SM_Start:
      SM_State = SM_Begin;
      break;

    case (SM_Begin):
      if (PINA == 0x00) {
        SM_State = SM_Begin;
      } else if (PINA == 0x01){
        SM_State = SM_Swap;
      }
      break;
    case (SM_Swap):
      SM_State = SM_Hold;
      break;
    case (SM_Hold):
      if (PINA == 0x01) {
        SM_State = SM_Hold;
      }
      else if (PINA == 0x00) {
        SM_State = SM_Begin;
      }
      break;

    default:
      SM_State = SM_Begin;
      break;
  }

  switch (SM_State) {
    case SM_Begin:
      break;
    case (SM_Swap):
      if (PORTB == 0x01) {
        PORTB = 0x02;
      } else {
        PORTB = 0x01;
      }
      break;
    default:
    break;
  }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
    /* Insert your solution below */
    SM_State = SM_Start;
    PORTB = 0x01;
    while (1) {
      Tick();
    }
    return 1;
}
