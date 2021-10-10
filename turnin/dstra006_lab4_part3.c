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
enum SM_States {SM_Start, SM_Begin, SM_Check, SM_Hold, SM_Inside, SM_Pound, SM_Pound_R, SM_Y_Pressed} SM_State;

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
      if (PINA == 0x04) {
        SM_State = SM_Pound;
      } else if (PINA == 0x80) {
        SM_State = SM_Inside;
      } else {
        SM_State = SM_Begin;
      }
      break;

    case (SM_Inside):
      SM_State = SM_Check;
      break;

    case (SM_Y_Pressed):
      SM_State = SM_Check;
      break;

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
        SM_State = SM_Y_Pressed;
      } else if (PINA == 0x80) {
        SM_State = SM_Inside;
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
    case (SM_Y_Pressed):
      PORTB = 0x01;
      break;

    case (SM_Inside):
      PORTB = 0x00; 
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
