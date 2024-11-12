/* Description: This project uses a ds3231 to measure time and temputure and displays the time and temp to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include <U8glib.h>
#include <Servo.h>
// Init constants

const int tempPin = A0;
int current = 0;  //Current är servons position

// Init global variables

// construct objects
Servo myServo;
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);


void setup() {
  // init communication
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  // Init Hardware
  myServo.attach(9);
  pinMode(13, OUTPUT);

  // Settings
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  u8g.setFont(u8g_font_unifont);
}

void loop() {

  oledWrite(30, 20, getTime(), 30, 50, String(getTemp()));
  Serial.println(getTemp());
  servoWrite(getTemp());
  LedLampa();
  delay(200);
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();

  String newTime = String(now.hour());
  if (now.minute() < 10) {
    newTime = newTime + ":" + "0" + String(now.minute());
  } else {
    newTime = newTime + ":" + String(now.minute());
  }

  if (now.second() < 10) {
    newTime = newTime + ":" + "0" + String(now.second());
  } else {
    newTime = newTime + ":" + String(now.second());
  }

  return newTime;
}
/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float */
float getTemp() {

  int Vo;
  float R1 = 10000;  // value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;


  Vo = analogRead(tempPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);  //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));  // temperature in Kelvin
  T = T - 273.15;                                              //convert Kelvin to Celcius

  return T;
}
/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/

void oledWrite(int x, int y, String text, int x2, int y2, String text2) {
  u8g.firstPage();
  do {
    u8g.drawStr(x, y, text.c_str());
    u8g.drawStr(x2, y2, text2.c_str());
  } while (u8g.nextPage());
}


/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/

void servoWrite(float Temp) {

  myServo.write(map(Temp, 15, 30, 0, 179));
}

void LedLampa() {

  if (getTemp() > 24) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
