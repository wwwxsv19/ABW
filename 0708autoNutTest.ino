/*
Auto-Nut : ABW Auto Break Water

무접점 수위 센서로 감지된 파도 수위에 따라 
자동으로 방파제 벽이 오르락내리락 ( 솔레노이드 액추에이터 ) 가능한 시스템 
*/

#include <LiquidCrystal_I2C.h>    
LiquidCrystal_I2C lcd(0x3F, 16, 2); 

#define wlsnsr 2 // 무접점 수위 센서

#define snide 3 // 솔레노이드 액추에이터

#define RedLED 4 // 빨강
#define GreenLED 5 // 초록

void setup() {
  pinMode(wlsnsr, INPUT);

  pinMode(snide, OUTPUT);

  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  digitalWrite(RedLED, LOW);
  digitalWrite(GreenLED, LOW);  

  lcd.init();
  setLcd(); 
  lcd.print("Hi Auto-Nut!");
  delay(3000);

  Serial.begin(9600);
}

void loop() {
  Serial.print("State : ");
  Serial.println(digitalRead(wlsnsr), HEX); // Serial 통신으로 현재 무접점 수위 센서의 상태 파악

  if(digitalRead(wlsnsr)) {

    digitalWrite(snide, HIGH);
    warn();
  
  }
  else {
  
    digitalWrite(snide, LOW);
    safe();
  
  }

  delay(500); // lcd 출력 용이 & 규칙적인 상태 검사를 위해 0.5초 딜레이
}

void setLcd() {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void safe() {
  setLcd();
  lcd.print("Safety!");

  digitalWrite(RedLED, LOW);
  digitalWrite(GreenLED, HIGH);
}

void warn() {
  setLcd();
  lcd.print("Warning!");

  digitalWrite(RedLED, HIGH);
  digitalWrite(GreenLED, LOW);
}
