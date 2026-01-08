#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LED_LAMP 13
#define TOUCH_BUTTON 2
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define OLED_RESET 4
#define MAX_DATA 15

unsigned long curr_time; 
unsigned long scores[MAX_DATA]; 
unsigned long total_data = 0; 
unsigned long waiting_time; 
unsigned long state_time; 
unsigned long led_time; 
unsigned long touch_button_time; 
unsigned long result; 
unsigned long mean; 
int index = 0;
int state = 0;  
int count_data = 1; 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(){
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 ALLOCATION FAILED"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,1);
  display.display();

  pinMode(LED_LAMP, OUTPUT);
  pinMode(TOUCH_BUTTON, INPUT_PULLUP);
  digitalWrite(LED_LAMP, LOW);
  randomSeed(analogRead(0));
}

void loop(){
  curr_time = millis();
  if(state == 0){
    display.clearDisplay();
    waiting_time = random(2000, 5000);
    state_time = millis();
    state++;
  }else if(curr_time - state_time >= waiting_time && state == 1){
    digitalWrite(LED_LAMP, HIGH);
    led_time = millis();
    state++;
  } else if(state == 2){
    if(digitalRead(TOUCH_BUTTON) == LOW){
      touch_button_time = millis();
      result = touch_button_time - led_time;
      digitalWrite(LED_LAMP, LOW);
      state++;
    }
  } else if(state == 3){
    scores[index] = result;
    index++;
    total_data = 0;
    for(int i = 0; i < MAX_DATA; i++){
      total_data += scores[i];
    }
    mean = total_data / count_data;
    count_data++;
    display.setCursor(0,1);
    Serial.print(index);
    Serial.print(",");
    Serial.print(result);
    Serial.print(",");
    Serial.println(mean);
    display.print("Reflects: ");
    display.print(result);
    display.print("\n");
    display.print("Result : ");
    display.print(mean);
    display.display();
    delay(3000);
    state = 0;
    if(index == 15 && count_data > 15){
      state = 4;
      index = 0;
    }
  } else if(state == 4){
    display.clearDisplay();
    display.setCursor(0,5);
    display.println("GAME OVER !");
    display.println("Press reset button");
    display.println("to play again...");
    display.display();
  }
}

