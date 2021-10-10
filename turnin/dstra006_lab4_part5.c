/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #5
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
unsigned char enterCode[7] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01};
unsigned char currentPos = 0x00;
enum SM_States {SM_Start, SM_Begin, SM_Check, SM_Inside, SM_Code_Entered, SM_Increment, SM_Hold} SM_State;

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
      if (PINA == enterCode[currentPos]) {
        SM_State = SM_Increment;
      } else if (PINA == 0x80) {
        SM_State = SM_Inside;
      } else {
        SM_State = SM_Begin;
      }
      break;

    case (SM_Inside):
      SM_State = SM_Check;
      break;

    case (SM_Code_Entered):
      SM_State = SM_Check;
      break;

    case (SM_Increment):
      if (currentPos == 7) {
        SM_State = SM_Code_Entered;
      } else {
        SM_State = SM_Hold;
      }
      break;

    case (SM_Hold):
      if (PINA == currA) {
        SM_State = SM_Hold;
      } else {
        SM_State = SM_Check;
      }
      break;
      /*
    case (SM_Pound):
      if (PINA == 0x04) {
        SM_State = SM_Pound;
      } else if (PINA == 0x80) {
        SM_State = SM_Inside;
      } else if (PINA == 0x00) {
        SM_State = SM_Pound_R;
      } else {
        SM_State = SM_Check;
      }
      break;

    case (SM_Pound_R):
      if (PINA == 0x00) {
        SM_State = SM_Pound_R;
      } else if (PINA == 0x02) {
        SM_State = SM_Code_Entered;
      } else if (PINA == 0x80) {
        SM_State = SM_Inside;
      } else {
        SM_State = SM_Check;
      }
      break;
      */
    default:
      SM_State = SM_Begin;
      break;
  }

  switch (SM_State) {
    case SM_Begin:
      break;
    case (SM_Code_Entered):
      if (PORTB == 0x00) {
        PORTB = 0x01;
      } else {
        PORTB = 0x00;
      }
      break;

    case (SM_Inside):
      PORTB = 0x00;
      break;

    case (SM_Hold):
      currA = PINA;
      break;

    case (SM_Increment):
    currentPos = currentPos + 1;
      if (currentPos == 7) {
        currentPos = 0;
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
    PORTB = 0x00;
    while (1) {
      Tick();
    }
    return 1;
}
