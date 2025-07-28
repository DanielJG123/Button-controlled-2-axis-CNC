/*
 * CNC Lathe Controller
 * Arduino Mega-based system for converting manual lathe to CNC
 * 
 * Features:
 * - Dual-axis control (X and Z)
 * - Manual speed control via potentiometers
 * - Direction control via buttons
 * - Automated G-code execution from SD card
 * - LCD display for status information
 * - 4x4 keypad for menu navigation
 * 
 * Hardware:
 * - Arduino Mega 2560
 * - Sieg SC4 Mini Lathe (converted from manual to CNC)
 * - 2x NEMA 23 Stepper motors with drivers
 * - Specialized bench power packs for current/voltage regulation
 * - 2x Potentiometers for speed control
 * - 4x4 Matrix keypad
 * - 16x2 I2C LCD display
 * - SD card module
 * - 2x Limit switches for homing
 * 
 * Author: [Your Name]
 * Date: [Date]
 * License: MIT
 */

// Keypad configuration
#include <Keypad.h>
char keys[4][4]={
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}};
byte rowPin[4]={41,40,39,38};
byte colPin[4]={45,44,43,42};
Keypad kpd=Keypad(makeKeymap(keys),rowPin,colPin,4,4);

// LCD display configuration
#include "Wire.h" // Library for I2C communication
#include "LiquidCrystal_I2C.h" // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

// Pin definitions for stepper motors
const int MOTOR_X_STEP_PIN = 3;  // X-axis step signal
const int MOTOR_Y_STEP_PIN = 2;  // Y-axis step signal (used as Z-axis)
const int MOTOR_Z_STEP_PIN = 4;  // Z-axis step signal (unused in this setup)
const int MOTOR_X_DIR_PIN = 7;   // X-axis direction control
const int MOTOR_Y_DIR_PIN = 5;   // Y-axis direction control (used as Z-axis)
const int MOTOR_Z_DIR_PIN = 6;   // Z-axis direction control (unused)
const int STEPPERS_ENABLE_PIN = 8; // Enable pin for all stepper drivers
const int LIMIT_SWITCH_X_PIN = 9;  // X-axis limit switch
const int LIMIT_SWITCH_Y_PIN = 10; // Y-axis limit switch

// Stepper motor libraries
#include <AccelStepper.h>
#include <MultiStepper.h>
AccelStepper stepperX(AccelStepper::DRIVER, MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);

MultiStepper multiStepper;
#define home_switch_X  LIMIT_SWITCH_X_PIN// Pin 9 connected to Home Switch (MicroSwitch)
#define home_switch_Y  LIMIT_SWITCH_Y_PIN

#include <SPI.h>

// Position tracking variables
long Xpos,Ypos = 0;

/**
 * Home X-axis by moving until limit switch is triggered
 * Moves in negative direction until switch activates, then positive until deactivated
 */
void HomeX(){
  while (digitalRead(home_switch_X)) {  // Make the Stepper move CCW until the switch is activated   
    digitalWrite(MOTOR_X_DIR_PIN,0);
    digitalWrite(MOTOR_X_STEP_PIN,HIGH);
    delay(10);
    digitalWrite(MOTOR_X_STEP_PIN,LOW);
    delay(10);}
  while (!digitalRead(home_switch_X)) { // Make the Stepper move CW until the switch is deactivated
    digitalWrite(MOTOR_X_DIR_PIN,1);
    digitalWrite(MOTOR_X_STEP_PIN,HIGH);
    delay(10);
    digitalWrite(MOTOR_X_STEP_PIN,LOW);
    delay(10);}
  Xpos = 0;}

/**
 * Home Y-axis by moving until limit switch is triggered
 * Moves in negative direction until switch activates, then positive until deactivated
 */
void HomeY(){
  while (digitalRead(home_switch_Y)) {  // Make the Stepper move CCW until the switch is activated 
    Serial.println(digitalRead(home_switch_Y)) ; 
    digitalWrite(MOTOR_Y_DIR_PIN,0);
    digitalWrite(MOTOR_Y_STEP_PIN,HIGH);
    delay(10);
    digitalWrite(MOTOR_Y_STEP_PIN,LOW);
    delay(10);}
  while (!digitalRead(home_switch_Y)) { // Make the Stepper move CW until the switch is deactivated
    digitalWrite(MOTOR_Y_DIR_PIN,1);
    Serial.println(digitalRead(home_switch_Y)) ; 
    digitalWrite(MOTOR_Y_STEP_PIN,HIGH);
    delay(10);
    digitalWrite(MOTOR_Y_STEP_PIN,LOW);
    delay(10);}
  Ypos = 0;
}

// LCD display functions for showing current direction
void lcdRight(){
  lcd.setCursor(0,0);
  lcd.print("X dir - Right   ");}
void lcdLeft(){
  lcd.setCursor(0,0);
  lcd.print("X dir - Left    ");}
void lcdForward(){
  lcd.setCursor(0,1);
  lcd.print("Y dir - Forward ");}
void lcdBackward(){
  lcd.setCursor(0,1);
  lcd.print("Y dir - Backward");
}

/**
 * Setup function - initializes all components
 */
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);  // Start the Serial monitor with speed of 115200 Bauds
  
  // Note: Homing is commented out for safety - uncomment when ready
  // pinMode(home_switch_X, INPUT_PULLUP);
  // pinMode(home_switch_Y, INPUT_PULLUP);
  // delay(5);  // Wait for EasyDriver wake up 
  
  multiStepper.addStepper(stepperX);
  multiStepper.addStepper(stepperY);
  //.multiStepper.addStepper(stepperZ);
  
  // Start Homing procedure of Stepper Motor at startup (commented out for safety)
  // lcd.setCursor(0,0);
  // lcd.print("X-axis Homing...");
  // HomeX();
  // lcd.print("X-axis Homed   ");
  // lcd.setCursor(0,1);
  // lcd.print("Y-axis Homing...");
  // HomeY();
  // lcd.print("Y-axis Homed   ");
  // delay(3000);
  // lcd.clear();
  
  // Initialize display and motor directions
  lcdLeft();
  lcdForward();
  digitalWrite(MOTOR_Y_DIR_PIN, HIGH);
  digitalWrite(MOTOR_X_DIR_PIN, HIGH);
  stepperX.setMaxSpeed(1500);
  stepperY.setMaxSpeed(1500);
}

// Speed control potentiometers
int speedpotX = A15;  // X-axis speed control
int speedpotY = A0;   // Y-axis speed control (used as Z-axis)
long pdx, pdy= 1500;  // Speed values for X and Y axes
long mx0,mx1,my1,t = 0;  // Timing variables

// State machine for bishop carving sequence
byte bishopState = 0;  // 0=IDLE, 1=MOVING_TO_START, 2=READY_TO_CUT, 3=CUTTING, 4=COMPLETED

/**
 * Main loop - handles all real-time operations
 */
void loop() {
  t = micros();
  if((uint32_t)(t-mx0) > 100000){  // Update every 100ms
    
    // Read potentiometers and calculate speed
    // Non-linear mapping: potentiometer value (0-1023) -> speed (1-64) -> squared -> multiplied by 10
    pdx = pow(map(analogRead(speedpotX),0,1023,64,1), 2)*10;
    pdy = pow(map(analogRead(speedpotY),0,1023,64,1), 2)*10;
    
    // Check for keypad input
    char key = kpd.getKey();

    if (key) {
        switch (key) {
            case 'A':
                // Reserved for future use
                break;
            case 'D':
                toggleDirection(MOTOR_Y_DIR_PIN, "Y");  // Toggle Y-axis direction
                break;
            case 'C':
                toggleDirection(MOTOR_X_DIR_PIN, "X");  // Toggle X-axis direction
                break;
            case '7':
                executeGCodeFromSD("Knight.txt");  // Execute knight piece carving
                break;
            case '6':
                // Cycle through bishop carving states
                if (bishopState < 4) {
                  bishopState += 1;}
                else {bishopState = 0;}
                break;
        }
    }
    
    // Handle bishop carving state machine
    run_bishop();
    mx0 = t;}

  // X-axis stepper control
  if(pdx<36000){  // Speed limit check
    if ((uint32_t)(t-mx1) >= pdx){  // Timing control for step frequency
      digitalWrite(MOTOR_X_STEP_PIN,HIGH);
      delayMicroseconds(20);    
      digitalWrite(MOTOR_X_STEP_PIN,LOW);
      mx1=t;}
  }

  // Y-axis stepper control
  if(pdy<36000){  // Speed limit check
    if ((uint32_t)(t-my1) >= pdy){  // Timing control for step frequency
      digitalWrite(MOTOR_Y_STEP_PIN,HIGH);
      delayMicroseconds(20);
      digitalWrite(MOTOR_Y_STEP_PIN,LOW);
      my1=t;}
  }
}

/**
 * Bishop carving state machine
 * Controls the multi-step process for carving a bishop chess piece
 */
void run_bishop() {
    switch (bishopState) {
        case 0: // IDLE
            // Do nothing
            break;

        case 1: // MOVING_TO_START
            displayStartMessageBishop();
            break;

        case 2: // READY_TO_CUT
            executeGCodeFromSD("Bishop.txt");  // Execute main cutting sequence
            bishopState += 1;
            break;

        case 3: // CUTTING
            displayFinishingMessageBishop();  // Blocking call
            break;

        case 4: // COMPLETED
            executeGCodeFromSD("Bishop_finishing.txt");  // Execute finishing sequence
            bishopState +=1;
            Serial.println("Bishop sequence complete.");
            break;
    }
}

/**
 * Coordinated movement of X and Y axes
 * @param stepsX Number of steps for X-axis
 * @param stepsY Number of steps for Y-axis
 * @param speedFactor Speed multiplier (0.0 to 1.0)
 */
void moveXYWithCoordination(long stepsX, long stepsY, float speedFactor) {
    
    if (stepsX == 0 && stepsY == 0) {
        Serial.println("No movement required");
        return;
    }
    const float MAX_SPEED = 2200;
    const float ACCELERATION = 800;
    
    // Calculate the absolute values for ratio calculation
    unsigned long absX = abs(stepsX);
    unsigned long absY = abs(stepsY);
    
    // Find the longer distance to determine the primary axis
    unsigned long maxSteps = max(absX, absY);
    
    // Calculate speed ratios (fixed point arithmetic with 1000 as base)
    long speedRatioX = (absX * 1000) / maxSteps;
    long speedRatioY = (absY * 1000) / maxSteps;
    
    speedFactor = 1;

    // Handle single-axis movements differently
    float finalSpeedX, finalSpeedY;
    if (stepsX == 0) {
        finalSpeedX = 0;
        finalSpeedY = MAX_SPEED * speedFactor;  // Full speed for Y
    } else if (stepsY == 0) {
        finalSpeedX = MAX_SPEED * speedFactor;  // Full speed for X
        finalSpeedY = 0;
    } else {
        // Both axes moving - apply coordination
        finalSpeedX = MAX_SPEED * speedRatioX * speedFactor / 1000.0;
        finalSpeedY = MAX_SPEED * speedRatioY * speedFactor / 1000.0;
    }
    Serial.println(finalSpeedX);
    Serial.println(finalSpeedY);
    delay(100);
    stepperX.setMaxSpeed(finalSpeedX);
    stepperY.setMaxSpeed(finalSpeedY);
    
    // Set accelerations proportionally
    float finalAccelX = stepsX != 0 ? ACCELERATION : 0;
    float finalAccelY = stepsY != 0 ? ACCELERATION : 0;
    
    stepperX.setAcceleration(finalAccelX);
    stepperY.setAcceleration(finalAccelY);

    // Calculate target positions
    long targetPosX = stepperX.currentPosition() + stepsX;
    long targetPosY = stepperY.currentPosition() + stepsY;
    
    // Set target positions in MultiStepper
    long targetPositions[2] = {targetPosX, targetPosY};
    multiStepper.moveTo(targetPositions);
    
    // Run until both motors reach their targets
    while(multiStepper.run()) {
        // Keep stepping
    }
}

// SD card and G-code processing
#include <SD.h>
#include <math.h>
const int chipSelect = 53;  // SD card chip select pin

// Steps per millimeter calibration
const float stepsPerMM_X = 100.0;  // X-axis steps per millimeter
const float stepsPerMM_Z = 200.0;  // Z-axis steps per millimeter

const int NUM_FILES = 3;  // Number of predefined G-code files

/**
 * Structure to store file information and initial coordinates
 */
struct FileData {
    String filename;
    float prevX;
    float prevZ;
};

/**
 * File dictionary with predefined coordinates for each G-code file
 */
FileData fileDictionary[NUM_FILES] = {
    {"Knight.txt", 19.1, 87.956},
    {"Bishop.txt", -20, 118.526},
    {"Bishop_finishing.txt", -14.566, 98.23}
};

/**
 * Calculate speed factor based on current radius
 * Adjusts cutting speed to maintain consistent surface finish
 * @param currentRadius Current workpiece radius in mm
 * @return Speed factor (0.4 to 1.0)
 */
float calculateSpeedFactor(float currentRadius) {
    // Linear scaling based on radius
    float speedFactor = currentRadius / 19.0;
    
    // Don't let speed drop below 40% of max even at smallest radius
    // to maintain chip formation
    return max(speedFactor, 0.4);
}

/**
 * Execute G-code file from SD card
 * @param filename Name of the G-code file to execute
 */
void executeGCodeFromSD(const char* filename) {
    
  lcd.clear();
  Serial.println("executing G code file");
  if (!SD.begin(chipSelect)) {
    lcd.setCursor(0, 0);
    lcd.println("SD card failed!");
    return;}

  // Open the G-code file from the SD card
  File gcodeFile = SD.open(filename);
  if (!gcodeFile) {
    lcd.setCursor(0, 0);
    lcd.println("File failed!");
    return;
  }
  
  // Initialize variables for previous and current coordinates
  float prevX = 0.0; // Initialize with a default value or use a global if necessary
  float prevZ = 0.0; // Initialize with a default value or use a global if necessary

  // Search for the file in the dictionary to set initial values
  for (int i = 0; i < NUM_FILES; i++) {
      if (fileDictionary[i].filename == filename) {
          prevX = fileDictionary[i].prevX; // Assign directly to the function scope variable
          prevZ = fileDictionary[i].prevZ; // Assign directly to the function scope variable
          break; // Exit the loop once found
      }
  }

  float fractionalX, fractionalZ = 0.0;  // Fractional step accumulation
  float currentX, currentZ, feedrate, speed_calc, tool_changeX, tool_changeZ;
  int moveNumber = 0;
  int previousFeedrate = 200; // Initial feedrate
  int totalMoves = countLinesInFile(filename);

  displayStatusInitial(totalMoves); 
  displayStatus(moveNumber); 
  
  // Read each line from the file
  while (gcodeFile.available()) {
    String line = gcodeFile.readStringUntil('\n');
    line.trim(); // Remove whitespace

    if (line.length() == 0) {
      continue; // Skip empty lines
    }
    moveNumber++;
    displayStatus(moveNumber); 
    
    // Parse the current line
    if (parseGCodeLine(line, currentX, currentZ, feedrate)) {
        if (feedrate == -1) {
          feedrate = previousFeedrate;
        }
        if (currentX == -1) {
          currentX = prevX;
        }
        if (currentZ == -1) {
          currentZ = prevZ;
        }      // ... (conversion to steps)

      // Map feedrate to speed (adjust the range as needed)
      int speed = map(feedrate, 0, 2016, 100, 2500);
      previousFeedrate = feedrate;
      
      // Calculate relative coordinates if valid values exist
      float deltaX_mm = currentX - prevX;
      float deltaZ_mm = currentZ - prevZ;

      // Convert mm to steps with fractional step accumulation
      int deltaX_steps = deltaX_mm * stepsPerMM_X;
      fractionalX += deltaX_mm * stepsPerMM_X - deltaX_steps;
      if (fractionalX >= 1.0) {
        deltaX_steps++;
        fractionalX -= 1.0;
      }

      int deltaZ_steps = deltaZ_mm * stepsPerMM_Z;
      fractionalZ += deltaZ_mm * stepsPerMM_Z - deltaZ_steps;
      if (fractionalZ >= 1.0) {
        deltaZ_steps++;
        fractionalZ -= 1.0;
      }

      Serial.print("Moving to X:");
      Serial.print(deltaX_steps);
      Serial.print(", Z:");
      Serial.println(deltaZ_steps);
      
      // Update previous coordinates for next iteration
      prevX = currentX;
      prevZ = currentZ;
      
      // Use your library function to move motors with relative coordinates and speed
      //moveXYWithCoordination(deltaX_steps, deltaZ_steps, speed, 500);
      if (deltaZ_steps < 0){speed = 1500;}
      else {speed = 20000/prevX;}
      moveXYWithCoordination(deltaZ_steps, deltaX_steps, calculateSpeedFactor(currentX)); 
    ;} else {
      // Handle invalid lines (optional: log errors or skip)
      Serial.println("Error parsing G-code line!");
    }
  }

  // Close the file after reading all lines
  gcodeFile.close();
}

/**
 * Count the number of lines in a file
 * @param filename Name of the file to count
 * @return Number of lines in the file
 */
int countLinesInFile(const char* filename) {
  File file = SD.open(filename);
  if (!file) {
    Serial.println("Failed to open file for line counting.");
    return 0;
  }

  int lineCount = 0;
  while (file.available()) {
    if (file.read() == '\n') {
      lineCount++;
    }
  }

  file.close();
  return lineCount;
}

/**
 * Parse a G-code line and extract X, Z, and F values
 * @param line The G-code line to parse
 * @param x Reference to store X coordinate
 * @param z Reference to store Z coordinate
 * @param f Reference to store feedrate
 * @return true if parsing was successful
 */
bool parseGCodeLine(const String& line, float& x, float& z, float&f) {

  // Extract X and Z coordinates
  int xIndex = line.indexOf('X');
  int zIndex = line.indexOf('Z');
  int fIndex = line.indexOf('F');

  if (xIndex != -1) {
    x = line.substring(xIndex + 1).toFloat();
  } else {x=-1;
    // Handle missing X coordinate (optional: use previous value or error)
  }

  if (zIndex != -1) {
    z = line.substring(zIndex + 1).toFloat();
  } else {z=-1;
    // Handle missing Z coordinate (optional: use previous value or error)
  }

  // Extract feedrate
  if (fIndex != -1) {
    f = line.substring(fIndex + 1).toInt();
  } else {
    f = -1; // Or set a default feedrate
  }

  return true;
}

/**
 * Toggle direction for a specified axis
 * @param pin The direction pin to toggle
 * @param axis The axis name for display purposes
 */
void toggleDirection(int pin, const char* axis) {
    if (digitalRead(pin) == LOW) {
        digitalWrite(pin, HIGH);
        if (strcmp(axis, "Y") == 0) lcdForward();
        else lcdRight();
    } else {
        digitalWrite(pin, LOW);
        if (strcmp(axis, "Y") == 0) lcdBackward();
        else lcdLeft();
    }
}

/**
 * Display initial status message for G-code execution
 * @param totalMoves Total number of moves in the file
 */
void displayStatusInitial(int totalMoves) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Carving piece");
  lcd.setCursor(0, 1);
  lcd.print("Move ");
  lcd.setCursor(10, 1);
  lcd.print("0/");
  lcd.print(totalMoves);
}

/**
 * Update status display with current move number
 * @param moveNumber Current move number
 */
void displayStatus(int moveNumber) {
  lcd.setCursor(10-int(log10(moveNumber)), 1);
  lcd.print(moveNumber);
}

/**
 * Display start message for bishop carving sequence
 */
void displayStartMessageBishop() {
  lcd.clear();
  lcd.print("From base left");
  lcd.setCursor(0, 1);
  lcd.print("20mm radius *");
  
  // Blocking wait for any keypress
  lcd.setCursor(0, 1);
  lcd.print("20mm radius     *");}

/**
 * Display finishing message for bishop carving sequence
 */
void displayFinishingMessageBishop() {
  lcd.clear();
  lcd.print("New Tool touch");
  lcd.setCursor(0, 1);
  lcd.print("widest point  *");
}
