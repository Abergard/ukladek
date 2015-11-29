/*
 * Tomasz Kowalczyk
 * Lukasz Zawistowicz
 */

#pragma once

 //#define F_CPU 16000000UL
#include <avr/io.h> // zawiera on definicje, odpowiednie dla naszego mikrokontrolera.
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

//#define sbi(x,y) x |= _BV(y) //set bit - using bitwise OR operator
//#define cbi(x,y) x &= ~(_BV(y)) //clear bit - using bitwise AND operator
//#define tbi(x,y) x ^= _BV(y) //toggle bit - using bitwise XOR operator
//#define is_high(x,y) (x & _BV(y) == _BV(y)) //check if the y'th bit of register 'x' is high ... test if its AND with 1 is 1
//#define is_low(x,y) ((x & _BV(y)) == 0) //check if the input pin is low

void wait(uint32_t czas);

void setAll_PortA();
void setAll_PortB();
void setAll_PortC();
void setAll_PortD();

void unsetAll_PortA();
void unsetAll_PortB();
void unsetAll_PortC();
void unsetAll_PortD();

void setAt_PortA(uint8_t position);
void setAt_PortB(uint8_t position);
void setAt_PortC(uint8_t position);
void setAt_PortD(uint8_t position);

void unsetAt_PortA(uint8_t position);
void unsetAt_PortB(uint8_t position);
void unsetAt_PortC(uint8_t position);
void unsetAt_PortD(uint8_t position);

bool isSetAt_PortA(uint8_t position);
bool isSetAt_PortB(uint8_t position);
bool isSetAt_PortC(uint8_t position);
bool isSetAt_PortD(uint8_t position);

bool isSetAt_PinA(uint8_t position);
bool isSetAt_PinB(uint8_t position);
bool isSetAt_PinC(uint8_t position);
bool isSetAt_PinD(uint8_t position);

void setInputAll_PortA();
void setInputAll_PortB();
void setInputAll_PortC();
void setInputAll_PortD();

void setOutputAll_PortA();
void setOutputAll_PortB();
void setOutputAll_PortC();
void setOutputAll_PortD();

void setInputAt_PortA(uint8_t position);
void setInputAt_PortB(uint8_t position);
void setInputAt_PortC(uint8_t position);
void setInputAt_PortD(uint8_t position);

void setOutputAt_PortA(uint8_t position);
void setOutputAt_PortB(uint8_t position);
void setOutputAt_PortC(uint8_t position);
void setOutputAt_PortD(uint8_t position);
