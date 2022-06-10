#include <TFT_eSPI.h>
#include <stdio.h>

// HC-SR04
#define ECHO_PIN 12
#define TRIG_PIN 13

// Board
#define TFT_BL 4
#define PWR_ON 22
#define RedLED 25

TFT_eSPI tft = TFT_eSPI();

long duration; // duration of sound wave travel
int distance1; // initial distance measurement
int distance2; // final distance measurement
double speed; // movement speed

void setup() {
    Serial.begin(115200);

    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);

    pinMode(PWR_ON, OUTPUT);
    pinMode(RedLED, OUTPUT);
    pinMode(TFT_BL, OUTPUT);
    
    digitalWrite(PWR_ON, 1);

    tft.init();
    tft.setRotation(3);
    tft.setTextSize(2);
    tft.setSwapBytes(true);

    analogWrite(TFT_BL, 0xFF);

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);

    Serial.println("HC-SR04 ready!");
}

void loop() {
    distance1 = ultrasonicRead();
    delay(250);
    distance2 = ultrasonicRead();

    speed = distance2 - distance1;
    // Avoid negative speed
    if (speed < 0) {
        speed *= -1;
    }

    Serial.println("Distance1: " + String(distance1));
    Serial.println("Distance2: " + String(distance2));
    Serial.println("Speed: " + String(speed));

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0,0);

    tft.setTextSize(3);
    tft.println("DISTANCE");
    tft.setTextSize(4);
    tft.printf("%d cm\n", distance2);
    
    tft.setTextSize(3);
    tft.println("SPEED");
    tft.setTextSize(4);
    tft.printf("%d cm/s", int(speed));
}

float ultrasonicRead() {
    // Clears the trigPin condition
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN, HIGH);
    // Calculating the distance
    return duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}