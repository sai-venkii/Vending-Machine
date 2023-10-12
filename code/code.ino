#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define sensorpin1 A0
#define sensorpin2 A1
#define sensorpin3 A2

void readPins(int *i);
void processing();
void printSelected(unsigned int ch);
void displayPrice();

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int button1Pin = 2;  
const int button2Pin = 3; 
const int button3Pin = 4;

const int motor1Pin = 5;
const int motor2Pin = 6;
const int motor3Pin = 7;

/*
int force1=analogRead(sensorpin1);
int force_per1= map(force1, 0, 205, 0, 100);
int force2=analogRead(sensorpin2);
int force_per2= map(force2, 0, 205, 0, 100);
int force3=analogRead(sensorpin3);
int force_per3= map(force3, 0, 205, 0, 100);
*/

int res_juice;
int res_size;
void setup()
{
	lcd.begin();
	lcd.backlight();
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(motor1Pin,OUTPUT);
  pinMode(motor2Pin,OUTPUT);
  pinMode(motor3Pin,OUTPUT);
}

const unsigned int price[3]={10,20,30};
int button1State=0,button2State=0,button3State=0;

void loop()
{   
    lcd.clear();
    lcd.print("Vending Machine");
    delay(3000);
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Choose your");
    lcd.setCursor(5, 1);
    lcd.print("Drink");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Options:");
    lcd.setCursor(0, 1);
    lcd.print("1       2      3");


    readPins(&res_juice);
    delay(2000);
    displayPrice();
    readPins(&res_size);
    delay(2000);


    processing();

}

void readPins(int *i)
{
  button1State=button2State=button3State=0;
  while(1){
    button1State = digitalRead(button1Pin);
    button2State = digitalRead(button2Pin);
    button3State = digitalRead(button3Pin);
  
    if(button1State == LOW)
    {
      *i=1;
      printSelected(1);
      break;
    }
    else if(button2State==LOW)
    {
      *i=2;
      printSelected(2);
      break;
    }
    else if(button3State==LOW)
    {
      *i=3;
      printSelected(3);
      break;
    }
  }
}

void processing()
{
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Processing...");
  delay(1000);
  //to check if the bottle is empty
 /* if (res_juice==1){
    if(force_per1<10){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unavailable!");
    }
    else{
      motor();
    }
  }
  else if (res_juice==2){
    if(force_per2<10){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unavailable!");
    }
    else{
      motor();
    }
  }
  if (res_juice==3){
    if(force_per3<10){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unavailable!");
    }
    else{
      motor();
    }
  }*/
  motor();
}

void printSelected(unsigned int ch)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(ch);
    lcd.print(" is selected");
}

void displayPrice()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Choose your");
  lcd.setCursor(6, 1);
  lcd.print("Size");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1-S   2-M   3-L");
  lcd.setCursor(0, 1);
  lcd.print("$10   $20   $30");
}


void timeSelect(int size_no)
{
  if(size_no==1)
  {
    delay(5000);
  }
  else if(size_no==2){
    delay(10000);
  }
  else if (size_no==3) {
    delay(15000);
  }
}

void motor()
{
  if(res_juice==1){
         digitalWrite(motor1Pin, HIGH);
          timeSelect(res_size);
          digitalWrite(motor1Pin, LOW);
    }
    else if(res_juice==2){
        digitalWrite(motor2Pin, HIGH);
          timeSelect(res_size);
          digitalWrite(motor2Pin, LOW);
    }
    else {
        digitalWrite(motor3Pin, HIGH);
          timeSelect(res_size);
          digitalWrite(motor3Pin, LOW);
    }
  
}

