#include <Adafruit_SSD1306.h>
#include "Wire.h"
#include "OLED_091.h"

extern volatile int32_t Encoder_Count;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS);

void OLEDShow(void *pv)
{
	int32_t pre_count = 0;
	uint32_t display_count = 99;
	display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
	display.clearDisplay();
	while(1)
	{
		if(Encoder_Count > pre_count)
		{
			display_count++;
			if(display_count > 100)
				display_count = 100;
			pre_count = Encoder_Count;
		}
		else if(Encoder_Count < pre_count)
		{
			display_count--;
			if(display_count <= 0)
				display_count = 0;
			pre_count = Encoder_Count;
		}
		
		// 显示数字
		display.setCursor(SCREEN_WIDTH/2, SCREEN_HEIGHT - 10);
		display.setTextSize(1);             		
  		display.setTextColor(SSD1306_WHITE);
		display.print(display_count); // 7*7 像素字

		// 显示进度条
		display.fillRect(0, 5, (int16_t)((float)(display_count)/100*SCREEN_WIDTH), 10, SSD1306_WHITE);

		// 刷新显示
		display.display();
		display.clearDisplay();
		vTaskDelay(10);
	}
}

void OLED_Task_Init(void)
{
	if(xTaskCreate(OLEDShow, "OLED Task", 1024, NULL, 1, NULL) == pdPASS)
		Serial.println("OLED Task Create");
}

