#include <LiquidCrystal.h>
#include <Servo.h>
int servo = 8;

Servo myservo;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//timer
int seconds = 0;
int minutes = 0;
int hours   = 0;

//button - LED
int LED = 7;
int BUTTON = 13;
int BUTTON2 =6;

//counter
int btnPreState = 0;
int btnCurState = 0;

void setup() {
  // put your setup code here, to run once:
  //button and LED setup
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(BUTTON2,INPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Timer: ");

  //servo
  myservo.attach(servo);
  myservo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON2) == HIGH) {
    digitalWrite(LED,HIGH); 
    delay(20);
  }
  else {
    digitalWrite(LED,LOW);
    delay(20);
  }

  if (digitalRead(BUTTON) == HIGH && btnPreState == 0) 
  {
    lcd.setCursor(0,0);
    lcd.print("Timer: ");
    seconds = seconds + 1;
    digitalWrite(LED,HIGH);
    if (seconds > 59) {
        minutes++;
        seconds = 0;
      }
    

    //printing
    lcd.setCursor(0,1);
    lcd.print(minutes);
    lcd.print(":");
    lcd.print(seconds);
    lcd.print(" ");

    
    //digitalWrite(LED,LOW);
    delay(100);
  }
  else 
  {
    digitalWrite(LED,LOW);
    btnPreState = 0;
    if (digitalRead(BUTTON2) == HIGH) 
    {
      if (seconds > 59) {
        minutes++;
        seconds = 0;
      }
    //timer 
      myservo.write(90);
      while (minutes >= 0) 
      {
        seconds--;
        
        if (seconds < 0) 
        {
          minutes--;
          seconds = 59;
        }
        if (seconds == 0 && minutes == 0) break;
        lcd.setCursor(0,1);
        lcd.print(minutes);
        lcd.print(":");
        //lcd.print(" ");
        lcd.print(seconds);
        lcd.print(" ");
        delay(1000);
      }
      while (digitalRead(BUTTON) == LOW) {
        myservo.write(0);
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Unlocked!");
        delay(20);
        lcd.clear();
      }
     }
     delay(50);
  }
  delay(20);

}
