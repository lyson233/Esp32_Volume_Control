#include <ESP32Encoder.h>
#include "Rotary_Encoder.h"

int32_t volatile Encoder_Count = 0;

ESP32Encoder encoder;

// 旋转编码器任务
void RotaryEncoderTask(void *pv)
{
	int previousValue = 0;
	unsigned char key_flag = HIGH;
	// Enable the weak pull up resistors
  	ESP32Encoder::useInternalWeakPullResistors = UP;
	// use pin 34 and 35 for the first encoder
  	encoder.attachHalfQuad(ENCODER_CLK, ENCODER_DT);
	// set starting count value after attaching
	encoder.setCount(0);
	encoder.setFilter(1023);

	// 开启按键中断
	pinMode(ENCODER_SW, INPUT_PULLUP);
	
	while(1)
	{
		if (previousValue != encoder.getCount())
		{ 	
			//Serial.print("Encoder value = ");
			//Serial.println(encoder.getCount());
			Encoder_Count = encoder.getCount();
			vTaskDelay(pdMS_TO_TICKS(100));
			//Check if the encoder has change
			previousValue = encoder.getCount();
		}

		if(key_flag == LOW)
		{
			vTaskDelay(pdMS_TO_TICKS(200));
			if(key_flag == LOW)
			{
				Serial.print("Button has been pressed\n");
				key_flag = HIGH;
			}
		}
		key_flag = digitalRead(ENCODER_SW);
		vTaskDelay(10);
	}
}

void RotaryEncoderInit(void)
{
	if(xTaskCreate(RotaryEncoderTask, "Rotary Encoder Task", 1024, NULL, 1, NULL) == pdPASS)
		Serial.println("Rotary Encoder Task Create");
}


