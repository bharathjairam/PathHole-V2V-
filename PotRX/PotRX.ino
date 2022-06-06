// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte degree_symbol[8] =
{
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
// Define output strings

String str_dist;
String str_speed;
String str_out;

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

//distance measurement

#define trigpin 4 // digital pin 4 
#define echopin 3 // digital pin 3

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);

  lcd.init();   // initializing the LCD
  lcd.clear();
  lcd.backlight(); // Enable or Turn On the backlight

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  
}

void loop()
{

  int D = Usensor();
 Serial.println(D);


  // Set buffer to size of expected message
  byte distance = 0;
  byte Speed = 0;
  uint8_t buf[27];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen))
  {

    // Message received with valid checksum
    // Get values from string

    // Convert received data into string
    str_out = String((char*)buf);
    Serial.println("#BEGIN#");
    Serial.println(str_out);
    Serial.println("#END#");
    // Split string into two values
    for (int i = 0; i < str_out.length(); i++)
    {
      if (str_out.substring(i, i + 1) == ",")
      {
        str_dist = str_out.substring(0, i);
        str_speed = str_out.substring(i + 1);
        break;
      }

    }
    Serial.println("BEGIN");
    str_dist.trim();
    Serial.println(str_dist);
    //Serial.println(str_speed);
    Serial.println("END");
    // Print values to Serial Monitor
    //Serial.print("Distance: ");
    //Serial.print(distance);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.setCursor(9, 0);
    lcd.print(D);
    lcd.setCursor(12, 0);
    lcd.print("Cm");

    lcd.setCursor(0, 1);
    lcd.print("12.97, 77.59");
    delay(2000);
    lcd.clear();
    str_dist.trim();
    if(str_dist=="1"){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PATHOLE DETECTED");
      delay(2000);
    }
  }
}

int Usensor() {
  int duration, Distance;
  digitalWrite(trigpin, HIGH);

  delayMicroseconds(1000);
  digitalWrite(trigpin, LOW);


  duration = pulseIn(echopin, HIGH);

  Distance = ( duration / 2) / 29.1;
  //Serial.println("inches:");
  //Serial.println(Distance);

  Distance = map(Distance, 0 , 197, 0 , 255 );
  return Distance;

}
