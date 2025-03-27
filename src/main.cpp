#include <Arduino.h>
#include "core/FlightController.h"

FlightController flightController;
String inputString = "";
bool stringComplete = false;

void processCommand() {
    // Remove whitespace
    inputString.trim();
    
    // Parse command
    if (inputString.startsWith("set")) {
        // Format: "set roll pitch yaw"
        // Example: "set 0.5 -0.3 0.0"
        
        // Skip "set" and get the rest of the string
        String values = inputString.substring(4);
        
        // Parse three float values
        float roll = values.substring(0, values.indexOf(' ')).toFloat();
        values = values.substring(values.indexOf(' ') + 1);
        float pitch = values.substring(0, values.indexOf(' ')).toFloat();
        values = values.substring(values.indexOf(' ') + 1);
        float yaw = values.toFloat();
        
        // Constrain values between -1 and 1
        roll = constrain(roll, -1.0, 1.0);
        pitch = constrain(pitch, -1.0, 1.0);
        yaw = constrain(yaw, -1.0, 1.0);
        
        // Set the orientation
        flightController.setTargetOrientation(roll, pitch, yaw);
        
        // Print confirmation
        Serial.print(F("Setting orientation - Roll: "));
        Serial.print(roll);
        Serial.print(F(" Pitch: "));
        Serial.print(pitch);
        Serial.print(F(" Yaw: "));
        Serial.println(yaw);
    }
    else if (inputString == "help") {
        Serial.println(F("Available commands:"));
        Serial.println(F("set roll pitch yaw - Set servo positions (values between -1 and 1)"));
        Serial.println(F("Example: 'set 0.5 -0.3 0.0'"));
        Serial.println(F("help - Show this message"));
    }
    
    // Clear the string for next command
    inputString = "";
    stringComplete = false;
}

void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    while (!Serial) delay(10);  // Wait for Serial on Teensy
    
    Serial.println(F("Initializing Flight Controller..."));
    
    // Initialize the flight controller
    if (!flightController.begin()) {
        Serial.println(F("Failed to initialize flight controller!"));
        while (1) delay(10);  // Halt if initialization fails
    }
    
    // Enable debug printing for sensor calibration
    flightController.enableDebugPrinting(true);
    
    Serial.println(F("Flight Controller initialized successfully!"));
    Serial.println(F("Type 'help' for available commands"));
    
    // Reserve bytes for the input string
    inputString.reserve(200);
}

void loop() {
    // Check for Serial commands
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        if (inChar == '\n') {
            stringComplete = true;
        } else {
            inputString += inChar;
        }
    }
    
    // Process command if complete
    if (stringComplete) {
        processCommand();
    }
    
    // Update flight controller (reads sensors, applies filters, updates servos)
    flightController.update();
    
    // Add a small delay to prevent overwhelming the serial output
    delay(100);  // 50Hz update rate
} 