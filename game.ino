#include <Adafruit_NeoPixel.h>
#include <OneButton.h>


//int lightCount[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int button[]={22, 23, 24, 25, 26, 27, 28, 29};
int dataPin[]={46, 47, 48, 49, 50, 51, 52, 53};
int used[8]={0}; 
int count =1;
bool repeated = false;

Adafruit_NeoPixel strip1(1, 46, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(1, 47, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(1, 48, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(1, 49, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5(1, 50, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6(1, 51, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7(1, 52, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8(1, 53, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel LEDStripes[8]= {strip1,strip2,strip3,strip4,strip5,strip6,
                   strip7,strip8};


OneButton btn1 = OneButton(22,true,true);
OneButton btn2 = OneButton(23,true,true);
OneButton btn3 = OneButton(24,true,true);
OneButton btn4 = OneButton(25,true,true);
OneButton btn5 = OneButton(26,true,true);
OneButton btn6 = OneButton(27,true,true);
OneButton btn7 = OneButton(28,true,true);
OneButton btn8 = OneButton(29,true,true);

OneButton btns[8] = {btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8};

int randomValue;
int stat=1;

void setup() {
  // put your setup code here, to run once:
   for(int i=0;i<=8;i++)
  {
      pinMode(button[i],INPUT_PULLUP);
//    pinMode(lightCount[i], OUTPUT);
      pinMode(dataPin[i],OUTPUT);
      btns[i].attachLongPressStart(longPressStart);
      btns[i].attachLongPressStop(longPressStop);
      LEDStripes[i].begin();
      LEDStripes[i].show();
  }
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<=8; i++){
    btns[i].tick();
  }

 int m;
  randomValue = random(0,8);
  Serial.println(randomValue);
  check();
  if(!repeated){
     if(count%2 !=0){
   LEDStripes[randomValue].setPixelColor(1, LEDStripes[randomValue].Color(255, 0, 0));
   digitalWrite(dataPin[randomValue], HIGH);
    Serial.println("Red");
    LEDStripes[randomValue].show();
   }else if(count%2 ==0){
    LEDStripes[randomValue].setPixelColor(1, LEDStripes[randomValue].Color(255, 0, 255));
    digitalWrite(dataPin[randomValue], HIGH);
    Serial.println("Blue");
    LEDStripes[randomValue].show();
   }
  m= ledBlink(randomValue);
    count++;
 
  }
  repeated = false;
}

int ledBlink(int num){
   
   stat = digitalRead(button[num]);

   
   while(stat ==1){
       for(int i=0; i<=8; i++){
    btns[i].tick();
  }
        stat = digitalRead(button[num]);
        
     Serial.println("count: ");
     Serial.println(count);
     Serial.println("num");
     Serial.println(num);
//   LEDStripes[count].show();
     used[count] = num;
     Serial.println("looping");

   }
   Serial.println(count);
   return count;
   delay(1000);
}

void check(){
  for(int i=0; i<=sizeof(used)/sizeof(used[0]);i++){
    if(used[i+1]==randomValue){
      repeated = true;
    }
  }
}

void longPressStart() {
  Serial.println("Button long-press started");
}

void longPressStop() {
  Serial.println("Button long-press stopped");
  stopPlay();
}

void stopPlay(){
  while(true){
   Serial.println("GAMEOVER");
  }
}
