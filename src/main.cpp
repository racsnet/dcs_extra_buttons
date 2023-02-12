#include <Arduino.h>
#include <buttonbox.h>
#include "DigiJoystick.h"

void load_pio() {
  digitalWrite(PIN_77HC165_SH_LD, LOW);
  delayMicroseconds(DELAY_77HC165);
  digitalWrite(PIN_77HC165_SH_LD, HIGH);
  delayMicroseconds(DELAY_77HC165);
}

void setup() {
  pinMode(PIN_77HC165_SH_LD, OUTPUT);
  pinMode(PIN_77HC165_CLK, OUTPUT);
  pinMode(PIN_77HC165_QH, INPUT);
}

void loop() {
  int btn_state = 0;
  load_pio();
  btn_state = shiftIn(PIN_77HC165_QH, PIN_77HC165_CLK, LSBFIRST) << 8;
  btn_state += shiftIn(PIN_77HC165_QH, PIN_77HC165_CLK, LSBFIRST);
  if ( !(bitRead(btn_state, 4)) && !(bitRead(btn_state, 5))) {
    bitSet(btn_state, 7);
  }
  DigiJoystick.setButtons((char)lowByte(btn_state), (char)highByte(btn_state));
  DigiJoystick.delay(50);
}