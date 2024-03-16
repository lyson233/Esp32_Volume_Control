#include <stdint.h>
#include "OLED_091.h"

void setup() {
	Serial.begin(115200);

	OLED_Task_Init();
  RotaryEncoderInit();
}

void loop() {
  //Serial.printf("0x%02x\n", analogRead(POT_PIN));
}
