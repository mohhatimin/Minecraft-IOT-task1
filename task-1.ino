/*
 * Project Title: Smart Temperature Monitoring & Alert System
 * Target Hardware: Arduino UNO
 * Sensor: TMP36 Analog Temperature Sensor
 * Output Indicators: Red LED (Alert), Green LED (Normal/Safe)
 */

// Pin Definitions
const int tempPin = A1;       // Analog input pin for TMP36 sensor
const int redLed = 10;        // Digital output pin for High Temperature Alert LED
const int greenLed = 8;       // Digital output pin for Safe Temperature LED

// System Threshold Setting
const float tempThreshold = 30.0; // Temperature threshold in degrees Celsius

void setup() {
  // Configure LED pins as digital outputs
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Initialize Serial Communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // 1. Read raw 10-bit analog value from ADC (0 to 1023)
  int sensorVal = analogRead(tempPin);

  // 2. Convert raw ADC value to voltage (0.0V to 5.0V)
  float voltage = (sensorVal * 5.0) / 1024.0;

  // 3. Convert voltage to temperature in Celsius (°C)
  // TMP36 scale factor: 10 mV/°C with a 500 mV (0.5V) offset
  float temperatureC = (voltage - 0.5) * 100.0;

  // 4. Output temperature reading to the Serial Monitor
  Serial.print("Current Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // 5. Decision Logic for Visual Alerts
  if (temperatureC >= tempThreshold) {
    digitalWrite(redLed, HIGH);   // Turn ON Red Alert LED
    digitalWrite(greenLed, LOW);  // Turn OFF Green Safe LED
  } else {
    digitalWrite(redLed, LOW);    // Turn OFF Red Alert LED
    digitalWrite(greenLed, HIGH); // Turn ON Green Safe LED
  }

  // 6. Execution delay between readings
  delay(1000); // 1-second sampling interval
}