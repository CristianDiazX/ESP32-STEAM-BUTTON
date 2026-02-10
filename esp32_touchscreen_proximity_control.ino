#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ===== PIN DEFINITIONS =====
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8
#define TOUCH_CS   4
#define MOSI       11
#define MISO       12
#define SCK        13

#define PROXIMITY_SENSOR_PIN  A0  // Analog pin for proximity sensor
#define LIGHT_PWM_PIN         5   // PWM pin for LED brightness control

// ===== DISPLAY & TOUCH SETUP =====
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// ===== VARIABLES =====
int lightBrightness = 0;
bool imageDisplayed = false;
const int PROXIMITY_THRESHOLD = 100;  // Adjust based on your sensor

// ===== TOUCH CALIBRATION POINTS =====
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  
  // Initialize light control pin
  pinMode(LIGHT_PWM_PIN, OUTPUT);
  analogWrite(LIGHT_PWM_PIN, 0);
  
  // Initialize proximity sensor
  pinMode(PROXIMITY_SENSOR_PIN, INPUT);
  
  // Draw initial UI
  drawInitialUI();
  
  Serial.println("ESP32 Touchscreen & Proximity Control Ready!");
}

void loop() {
  // Handle proximity sensor and brightness
  updateProximitySensor();
  
  // Handle touchscreen input
  checkTouchInput();
  
  delay(100);
}

// ===== PROXIMITY SENSOR CONTROL =====
void updateProximitySensor() {
  int sensorValue = analogRead(PROXIMITY_SENSOR_PIN);
  
  // Map proximity value to brightness (0-255)
  // Closer object = higher brightness
  // Adjust the mapping based on your sensor characteristics
  lightBrightness = map(sensorValue, 0, 1023, 0, 255);
  
  // Apply brightness if sensor detects something
  if (sensorValue > PROXIMITY_THRESHOLD) {
    analogWrite(LIGHT_PWM_PIN, lightBrightness);
    Serial.print("Proximity: ");
    Serial.print(sensorValue);
    Serial.print(" | Brightness: ");
    Serial.println(lightBrightness);
  } else {
    analogWrite(LIGHT_PWM_PIN, 0);  // Turn off light if nothing nearby
  }
}

// ===== TOUCHSCREEN INPUT =====
void checkTouchInput() {
  // Read touch coordinates
  TSPoint p = readTouch();
  
  // Check if valid touch detected
  if (p.z > 0 && p.z < 1000) {
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print(", Y = ");
    Serial.print(p.y);
    Serial.print(", Pressure = ");
    Serial.println(p.z);
    
    // Toggle image display on touch
    if (!imageDisplayed) {
      displayImage();
      imageDisplayed = true;
    } else {
      clearImage();
      imageDisplayed = false;
    }
    
    delay(500);  // Debounce delay
  }
}

TSPoint readTouch() {
  // Simple touch detection (adjust for your specific touchscreen)
  // This is a placeholder - adjust based on your touchscreen library
  TSPoint p = {0, 0, 0};
  
  // For ILI9341 with resistive touch, you'd typically use:
  // Read from analog pins connected to touch panel
  // This depends on your specific touchscreen module
  
  return p;
}

// ===== DISPLAY FUNCTIONS =====
void drawInitialUI() {
  tft.fillScreen(ILI9341_BLACK);
  
  // Draw title
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("ESP32 Control");
  
  // Draw instructions
  tft.setCursor(10, 50);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_CYAN);
  tft.println("Touch screen to display image");
  
  // Draw status box
  tft.drawRect(10, 100, 300, 100, ILI9341_GREEN);
  tft.setCursor(20, 110);
  tft.setTextColor(ILI9341_GREEN);
  tft.println("Status: Ready");
  
  tft.setCursor(20, 130);
  tft.println("Light: OFF");
  
  tft.setCursor(20, 150);
  tft.println("Proximity: Monitoring");
  
  tft.setCursor(20, 170);
  tft.println("Brightness: 0%");
}

void displayImage() {
  tft.fillScreen(ILI9341_BLACK);
  
  // Draw a simple image (circle with patterns)
  tft.fillCircle(160, 120, 50, ILI9341_BLUE);
  tft.drawCircle(160, 120, 55, ILI9341_YELLOW);
  
  // Draw decorative elements
  tft.fillRect(100, 200, 120, 40, ILI9341_GREEN);
  tft.setCursor(110, 210);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("Image Active!");
  
  // Display brightness info
  tft.setCursor(50, 270);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print("Current Brightness: ");
  tft.print(lightBrightness);
  tft.println("%");
  
  Serial.println("Image displayed on screen");
}

void clearImage() {
  tft.fillScreen(ILI9341_BLACK);
  drawInitialUI();
  Serial.println("Image cleared");
}

// ===== ADVANCED: Custom Touch Reading (if needed) =====
// Uncomment and modify if using a specific touchscreen library
/*
#include <XPT2046_Touchscreen.h>

XPT2046_Touchscreen ts(TOUCH_CS);

TS_Point getRawTouchPoint() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    // Map raw coordinates to display coordinates
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    return p;
  }
  return TS_Point(0, 0, 0);
}
*/
