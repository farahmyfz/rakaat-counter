#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Initialization (address I2C: 0x27, size 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;

int sujud;
int rakaat;
bool sujudState = false;

void setup() {
    // LCD Initialization
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Inisialisasi...");
    delay(2000);

    // Pin Configuration
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Variable Settings
    sujud = -1;
    rakaat = 0;
    sujudState = false;

    // Clean the LCD after initialization
    lcd.clear();
}

void loop() {
    // Calculating distance using sensors
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    // Logic to detect position and count rakaat/prostration
    if (distance < 10 && !sujudState) {
        sujud++;
        sujudState = true;
        if (sujud == 2) {
            rakaat++;
            sujud = 0;
        }
    } else if (distance >= 10) {
        sujudState = false;
    }

    // Displays the number of rakaat on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fokus Sholat!");
    lcd.setCursor(0, 1);
    lcd.print("Rakaat ke: ");
    lcd.print(rakaat);

    delay(500); // Add a pause for stability
}
 

