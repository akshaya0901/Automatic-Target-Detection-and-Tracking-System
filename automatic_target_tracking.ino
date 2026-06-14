#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myServo;

// Change to 0x3F if 0x27 doesn't work
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define trigPin 9
#define echoPin 10
#define buzzer 7

long duration;
int distance;

int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
    return 400;

  return duration * 0.034 / 2;
}

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  myServo.attach(6);
  myServo.write(90);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("RADAR SYSTEM");

  lcd.setCursor(0,1);
  lcd.print("Starting...");
  delay(2000);

  lcd.clear();
}

void loop() {

  // Scan Left to Right
  for (int angle = 0; angle <= 180; angle += 3) {

    myServo.write(angle);
    delay(8);

    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
    //Serial.println(distance);

    if (distance > 5 && distance <= 20) {

      digitalWrite(buzzer, HIGH);

      lcd.setCursor(0,0);
      lcd.print("TARGET FOUND  ");

      lcd.setCursor(0,1);
      lcd.print("D:");
      lcd.print(distance);
      lcd.print("cm A:");
      lcd.print(angle);
      lcd.print("   ");

      // Hold position while target exists
      while (distance > 5 && distance <= 20) {

        distance = getDistance();

        lcd.setCursor(0,1);
        lcd.print("D:");
        lcd.print(distance);
        lcd.print("cm A:");
        lcd.print(angle);
        lcd.print("   ");

        delay(100);
      }

      digitalWrite(buzzer, LOW);
    }

    lcd.setCursor(0,0);
    lcd.print("SCANNING...   ");

    lcd.setCursor(0,1);
    lcd.print("D:");
    lcd.print(distance);
    lcd.print("cm A:");
    lcd.print(angle);
    lcd.print("   ");
  }

  // Scan Right to Left
  for (int angle = 180; angle >= 0; angle -= 3) {

    myServo.write(angle);
    delay(8);

    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
    //Serial.println(distance);

    if (distance > 5 && distance <= 20) {

      digitalWrite(buzzer, HIGH);

      lcd.setCursor(0,0);
      lcd.print("TARGET FOUND  ");

      lcd.setCursor(0,1);
      lcd.print("D:");
      lcd.print(distance);
      lcd.print("cm A:");
      lcd.print(angle);
      lcd.print("   ");

      while (distance > 5 && distance <= 20) {

        distance = getDistance();

        lcd.setCursor(0,1);
        lcd.print("D:");
        lcd.print(distance);
        lcd.print("cm A:");
        lcd.print(angle);
        lcd.print("   ");

        delay(100);
      }

      digitalWrite(buzzer, LOW);
    }

    lcd.setCursor(0,0);
    lcd.print("SCANNING...   ");

    lcd.setCursor(0,1);
    lcd.print("D:");
    lcd.print(distance);
    lcd.print("cm A:");
    lcd.print(angle);
    lcd.print("   ");
  }
}
