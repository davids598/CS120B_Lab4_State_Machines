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
//variables for SM
unsigned char currA = 0x00;
enum SM_States {SM_Start, SM_Begin, SM_Check, SM_Hold} SM_State;

void Tick() {
  switch (SM_State) {
    case SM_Start:
      SM_State = SM_Begin;
      break;

    case (SM_Begin):
      if (PINA == 0x00) {
        SM_State = SM_Begin;
      } else {
        SM_State = SM_Check;
      }
      break;

    case (SM_Check):
      SM_State = SM_Hold;
      break;

    case (SM_Hold):
      if (PINA == currA) {
        SM_State = SM_Hold;
      } else {
        SM_State = SM_Check;
      }
      break;

    default:
      SM_State = SM_Begin;
      break;
  }

  switch (SM_State) {
    case SM_Begin:
      break;
    case (SM_Check):
      currA = PINA;
      if (PINA == 0x01 && PORTC <= 8) {
        PORTC = PORTC + 1;
      }
      else if (PINA == 0x02 && PORTC >= 1){
        PORTC = PORTC - 1;
      }
      else if (PINA == 0x03) {
        PORTC = 0x00;
      }
      break;

    case SM_Hold:
      break;

    default:
    break;
  }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
    /* Insert your solution below */
    SM_State = SM_Start;
    PORTC = 0x07;
    while (1) {
      Tick();
    }
    return 1;
}
