/*********************************************************************

*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int a_slajder_y_pos ;
int slajder_a = A0;

int b_slajder_y_pos ;
int slajder_b = A1;

int vx = -2;
int vy = -2;

int boll_x_pos = 64;
int boll_y_pos = 32;
int half_brick_len = 6;

int score_a = 0;
int score_b = 0;

void setup()   {                
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
}


void loop() {

    a_slajder_y_pos  = analogRead(slajder_a)/5 - 100;
    b_slajder_y_pos  = analogRead(slajder_b)/5 - 100;

    if ( a_slajder_y_pos  < half_brick_len ) {
      a_slajder_y_pos  = half_brick_len;
    }
    if ( a_slajder_y_pos  > (64 - half_brick_len) ) {
      a_slajder_y_pos  = 64 - half_brick_len;
    }

    if ( b_slajder_y_pos  < half_brick_len ) {
      b_slajder_y_pos  = half_brick_len;
    }
    if ( b_slajder_y_pos  > (64 - half_brick_len) ) {
      b_slajder_y_pos  = 64 - half_brick_len;
    }
    
    boll_x_pos += vx;
    boll_y_pos += vy;

    if (boll_x_pos < 0) {
      vx = -vx;
      boll_x_pos = 0;
      if ( (boll_y_pos < (a_slajder_y_pos  - half_brick_len)) || 
           (boll_y_pos > (a_slajder_y_pos  + half_brick_len))    ) {
        score_b++;
      } else {
        //vy = (boll_y_pos - a_slajder_y_pos )/2;
      }
    }
     
    if (boll_x_pos > 127) {
      vx = -vx;
      boll_x_pos = 127;
      if ( (boll_y_pos < (b_slajder_y_pos  - half_brick_len)) || 
           (boll_y_pos > (b_slajder_y_pos  + half_brick_len))    ) {
        score_a++;
      } else {
        //vy = (boll_y_pos - b_slajder_y_pos )/2;
      }
    }
    
    if (boll_y_pos < 0) {
      vy = -vy;
      boll_y_pos = 0;
    }
    
    if (boll_y_pos > 64) {
      vy = -vy;
      boll_y_pos = 64;
    }

    display.clearDisplay();
    display.drawLine(0, (byte)(a_slajder_y_pos  - half_brick_len), 0, (byte)(a_slajder_y_pos  + half_brick_len), WHITE);
    display.drawLine(127, (byte)(b_slajder_y_pos  - half_brick_len), 127, (byte)(b_slajder_y_pos  + half_brick_len), WHITE);
  
    display.drawPixel((byte)(boll_x_pos), (byte)(boll_y_pos), WHITE);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(54,0);
    display.print(score_a);
    display.print('-');
    display.print(score_b);
    display.display();
}

