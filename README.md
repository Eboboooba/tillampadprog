Här är ett exempel på en **README.md**-fil för att beskriva koden och dess funktionalitet:

---

# Temperaturstyrd Servo och LED Projekt

Det här projektet använder en temperaturmätare för att kontrollera en servo och tända en LED-lampa baserat på den uppmätta temperaturen. Programmet läser av temperaturvärdet, styr en servo till en position baserat på temperaturintervallet, och kontrollerar en LED som en indikator.

## Funktionalitet

### 1. **Display Text (u8g.drawStr)**
Programmet använder ett grafiskt displaybibliotek (`u8g`) för att visa text på en skärm. Texten kan vara temperaturvärden eller annan information, och den ritas ut på en skärm i ett specificerat koordinatsystem. Displayen används för att visa aktuell status för systemet.

```cpp
u8g.drawStr(x2, y2, text2.c_str());
```

### 2. **Servo Control**
Temperaturen används för att styra en servo. Funktionen `servoWrite` tar ett temperaturvärde som inparameter och mappar det till en servo-position (0–179 grader) beroende på värdet. Om temperaturen är lägre än 15°C kommer servon att vara nära 0 grader, medan den är vid 179 grader vid 30°C.

```cpp
void servoWrite(float Temp) {
  myServo.write(map(Temp, 15, 30, 0, 179));
}
```

### 3. **LED Lampa**
Om temperaturen överstiger 24°C, tänds en LED-lampa (ansluten till pin 13 på Arduino). Om temperaturen är under 24°C släcks lampan. Detta gör att lampan fungerar som en indikator för när temperaturen är hög eller låg.

```cpp
void LedLampa() {
  if (getTemp() > 24) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
```

## Installation

1. Klona eller ladda ner repositoryt.
2. Anslut en temperaturgivare (t.ex. DHT11 eller DS18B20) till din Arduino.
3. Koppla en servo till en PWM-utgång och en LED till pin 13.
4. Ladda upp koden till din Arduino via Arduino IDE.
5. Se temperaturen visas på displayen, servon justeras baserat på temperaturen och LED-lampan tänds eller släcks.

## Funktioner och Förbättringar

- **Temperaturstyrning**: Systemet justerar servons position baserat på temperaturen.
- **LED-indikator**: Lampan ger visuell feedback baserat på temperaturstatus.
- **Display för feedback**: Textinformation om aktuell status visas på skärmen.

### Förbättringar:

- Möjlighet att justera temperaturgränser för LED-indikatorn.
- Lägg till fler sensorer för att mäta andra parametrar.
- Skala upp systemet för att hantera fler servon eller en större display.

## Användning

Detta projekt är användbart för att lära sig grundläggande mikrocontroller-programmering, sensorintegration och hur man styr externa enheter som servon och LED-lampor baserat på sensorvärden.

---

Denna README-fil ger en kortfattad beskrivning av projektet, dess funktioner och hur användaren kan komma igång med det. Om du har några specifika detaljer att lägga till, kan du alltid anpassa den ytterligare.
