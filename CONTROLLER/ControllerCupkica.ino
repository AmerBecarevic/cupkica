// Motors
#include <dummy.h>

#define PWMA 19
#define AIN1 32
#define AIN2 23

#define PWMB 26
#define BI1 33
#define BI2 25

int brzina = 180; // Speed setting
int delayTime = 50;

const int kanal1 = 0;
const int kanal2 = 1;

// LM393 sensor pins
#define SENSOR_LEFT_PIN 34
#define SENSOR_RIGHT_PIN 35

bool a1 = false, a2 = false, b1 = false, b2 = false, mode = true;


// this header is needed for Bluetooth Serial -> works ONLY on ESP32
#include "BluetoothSerial.h" 

// init Class:
BluetoothSerial ESP_BT; 

// Parameters for Bluetooth interface
int incoming;

void setup() {
  Serial.begin(115200);
  ESP_BT.begin("ESP32_Control"); //Name of your Bluetooth interface -> will show up on your phone

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);

  // LM393 sensor pins setup
  pinMode(SENSOR_LEFT_PIN, INPUT);
  pinMode(SENSOR_RIGHT_PIN, INPUT);

  ledcSetup(kanal1, 1000, 8);
  ledcSetup(kanal2, 1000, 8);

  ledcAttachPin(PWMA, kanal1);
  ledcAttachPin(PWMB, kanal2);
}

void RC(char button)
{
  
  switch (button) {
    case 'F':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_1, value);
      //Serial.println("btn 1");
      a1 = true;
      a2 = false;
      b1 = true;
      b2 = false;

      ledcWrite(kanal1, brzina);
      ledcWrite(kanal2, brzina);
      Serial.print("A1: "); Serial.println(a1);
      Serial.print("A2: "); Serial.println(a2);
      Serial.print("B1: "); Serial.println(b1);
      Serial.print("B2: "); Serial.println(b2);
      break;
    case 'R':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_2, value);
      //Serial.println("btn 2");
      
      a1 = false;
      a2 = true;
      b1 = true;
      b2 = false;

      ledcWrite(kanal1, brzina);
      ledcWrite(kanal2, brzina);
      break;
    case 'L':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_3, value);
      //Serial.println("btn 3");
      
      a1 = true;
      a2 = false;
      b1 = false;
      b2 = true;

      ledcWrite(kanal1, brzina);
      ledcWrite(kanal2, brzina);
      break;
    case 'B':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_3, value);
      //Serial.println("btn 3");
      
      a1 = false;
      a2 = true;
      b1 = false;
      b2 = true;

      ledcWrite(kanal1, brzina);
      ledcWrite(kanal2, brzina);
      break;
    case 'S':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_3, value);
      //Serial.println("btn 3");
      
      a1 = false;
      a2 = false;
      b1 = false;
      b2 = false;

      ledcWrite(kanal1, brzina);
      ledcWrite(kanal2, brzina);
      break;
    case 'G':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_3, value);
      //Serial.println("btn 3");

      a1 = true;
      a2 = false;
      b1 = true;
      b2 = false;

      ledcWrite(kanal1, brzina + brzina / 3);
      ledcWrite(kanal2, brzina);
      break;
    case 'I':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_3, value);
      //Serial.println("btn 3");
      
      a1 = true;
      a2 = false;
      b1 = true;
      b2 = false;

      ledcWrite(kanal1, brzina);
      ledcWrite(kanal2, brzina + brzina / 3);
      break;
    case 'H':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_3, value);
      //Serial.println("btn 3");

      a1 = false;
      a2 = true;
      b1 = false;
      b2 = true;

      ledcWrite(kanal1, brzina + brzina / 3);
      ledcWrite(kanal2, brzina);
      break;
    case 'J':  
      Serial.print("Button: "); Serial.println(button);
      //digitalWrite(led_pin_3, value);
      //Serial.println("btn 3");

      a1 = false;
      a2 = true;
      b1 = false;
      b2 = true;

      ledcWrite(kanal1, brzina);
      ledcWrite(kanal2, brzina + brzina / 3);
      break;
  }
}

void Lajna()
{
  
  int sensorLeftValue = digitalRead(SENSOR_LEFT_PIN);
  int sensorRightValue = digitalRead(SENSOR_RIGHT_PIN);
  Serial.print("Button: "); Serial.println(sensorLeftValue);
  Serial.print("Button: "); Serial.println(sensorRightValue);


  if (sensorLeftValue == LOW && sensorRightValue == LOW) {
    // Both sensors on black line, move forward
    a1 = true;
    a2 = false;
    b1 = true;
    b2 = false;
    //ledcWrite(kanal1, brzina);
    //ledcWrite(kanal2, brzina);
  } else if (sensorLeftValue == HIGH && sensorRightValue == LOW) {
    // Left sensor off line, turn slightly right
    a1 = false;
    a2 = true;
    b1 = true;
    b2 = false;
    //ledcWrite(kanal1, brzina + 10);
    //ledcWrite(kanal2, brzina);
  } else if (sensorLeftValue == LOW && sensorRightValue == HIGH) {
    // Right sensor off line, turn slightly left
    a1 = true;
    a2 = false;
    b1 = false;
    b2 = true;
    //ledcWrite(kanal1, brzina);
    //ledcWrite(kanal2, brzina  + 10);
  } else {
    // Both sensors off line, stop or take corrective action
    // For simplicity, let's stop the motors
    a1 = false;
    a2 = false;
    b1 = false;
    b2 = false;
    //ledcWrite(kanal1, brzina);
    //ledcWrite(kanal2, brzina);
  }

  // Set motor speed
  ledcWrite(kanal1, brzina);
  ledcWrite(kanal2, brzina);
}

void loop() {
  /*
  Serial.print("A1:                   "); Serial.println(a1);
  Serial.print("A2:                      "); Serial.println(a2);
  Serial.print("B1:                         "); Serial.println(b1);
  Serial.print("B2:                           "); Serial.println(b2);
  */

  //Serial.print("Button: "); Serial.println(ESP_BT.read());
  
  
  if(a1)
    digitalWrite(AIN1, HIGH);
  if(!a1)
    digitalWrite(AIN1, LOW);
  if(a2)
    digitalWrite(AIN2, HIGH);
  if(!a2)
    digitalWrite(AIN2, LOW);
  if(b1)
    digitalWrite(BI1, HIGH);
  if(!b1)
    digitalWrite(BI1, LOW);
  if(b2)
    digitalWrite(BI2, HIGH);
  if(!b2)
    digitalWrite(BI2, LOW);

  incoming = ESP_BT.read(); //Read what we receive 
  char button = incoming;

  if(mode)
    {
      delayTime = 50;
      brzina = 180;
      RC(button);
    }
    else
    {
      delayTime = 100;
      brzina = 140;
      Lajna();
    }
  
  
  // -------------------- Receive Bluetooth signal ----------------------
  if (ESP_BT.available()) 
  {
    incoming = ESP_BT.read(); //Read what we receive 

    // separate button ID from button value -> button ID is 10, 20, 30, etc, value is 1 or 0
    button = incoming;
    
    if(button == 'M')
    {
      mode = !mode;
      a1 = false;
      a2 = false;
      b1 = false;
      b2 = false;
    }

    
  }

  delay(delayTime);

}

