#include <Arduino.h>
#include <PZEM004T.h>
#if defined(ESP32)
  #include <WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

// Provide the token generation process info
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions
#include "addons/RTDBHelper.h"

// WiFi credentials
#define WIFI_SSID "DSU" 
#define WIFI_PASSWORD "Learnforlife@99"

// Firebase project API Key and URL
#define API_KEY "AIzaSyBCeg8TP8-V3stw3aKVG_LyINaM-fOarnk"
#define DATABASE_URL "https://spring-bonfire-316807-default-rtdb.firebaseio.com/"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;
unsigned long sendDataPrevMillis = 0;

// PZEM configuration
PZEM004T pzem(16, 17); // Connect to RX (16) and TX (17)
IPAddress ip(192, 168, 1, 1);

// Function prototypes
void getPZEMDataAndSendToFirebase();

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nConnected with IP: " + WiFi.localIP().toString());

  // Configure Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // Monitor token generation

  // Firebase sign-up
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Sign-Up Success");
    signupOK = true;
  } else {
    Serial.printf("Sign-Up Error: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Set PZEM address
  pzem.setAddress(ip);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    getPZEMDataAndSendToFirebase();
  }
}

void getPZEMDataAndSendToFirebase() {
  // Read PZEM data
  float voltage = pzem.voltage(ip);
  float current = pzem.current(ip);
  float power = pzem.power(ip);
  float energy = pzem.energy(ip);
  float frequency = pzem.frequency(ip);

  // Handle invalid readings
  voltage = voltage < 0.0 ? 0.0 : voltage;
  current = current < 0.0 ? 0.0 : current;
  power = power < 0.0 ? 0.0 : power;
  energy = energy < 0.0 ? 0.0 : energy;
  frequency = frequency < 0.0 ? 0.0 : frequency;

  // Log data to Serial Monitor
  Serial.printf("Voltage: %.2f V\n", voltage);
  Serial.printf("Current: %.2f A\n", current);
  Serial.printf("Power: %.2f W\n", power);
  Serial.printf("Energy: %.2f Wh\n", energy);
  Serial.printf("Frequency: %.2f Hz\n", frequency);

  // Upload data to Firebase
  if (Firebase.RTDB.setFloat(&fbdo, "/PZEM/Voltage", voltage)) {
    Serial.println("Voltage uploaded successfully");
  } else {
    Serial.println("Failed to upload Voltage: " + fbdo.errorReason());
  }

  if (Firebase.RTDB.setFloat(&fbdo, "/PZEM/Current", current)) {
    Serial.println("Current uploaded successfully");
  } else {
    Serial.println("Failed to upload Current: " + fbdo.errorReason());
  }

  if (Firebase.RTDB.setFloat(&fbdo, "/PZEM/Power", power)) {
    Serial.println("Power uploaded successfully");
  } else {
    Serial.println("Failed to upload Power: " + fbdo.errorReason());
  }

  if (Firebase.RTDB.setFloat(&fbdo, "/PZEM/Energy", energy)) {
    Serial.println("Energy uploaded successfully");
  } else {
    Serial.println("Failed to upload Energy: " + fbdo.errorReason());
  }

  if (Firebase.RTDB.setFloat(&fbdo, "/PZEM/Frequency", frequency)) {
    Serial.println("Frequency uploaded successfully");
  } else {
    Serial.println("Failed to upload Frequency: " + fbdo.errorReason());
  }
}
