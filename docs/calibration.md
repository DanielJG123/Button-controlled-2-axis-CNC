# Calibration Guide

This document provides step-by-step instructions for calibrating the CNC Lathe Controller system.

## Initial Setup

### Prerequisites
- All hardware properly installed and wired
- Arduino IDE installed with required libraries
- Serial monitor access
- Measuring tools (calipers, ruler)

### Safety Check
- Ensure lathe is properly secured
- Verify emergency stop functionality
- Check all limit switches are operational
- Confirm proper workpiece clamping

## Mechanical Calibration

### Steps per Millimeter Calculation

The system uses the following default values:
- **X-axis**: 100 steps/mm
- **Z-axis**: 200 steps/mm

*Note: These values are specific to the Sieg SC4 lathe with NEMA 23 stepper motors. Different lathes may require different calibration values.*

To calculate your specific values:

1. **Measure your leadscrew pitch** (distance per revolution)
2. **Count stepper motor steps per revolution** (typically 200 for 1.8° motors)
3. **Account for microstepping** (if using 1/16 microstepping, multiply by 16)
4. **Calculate**: `steps_per_mm = (steps_per_rev * microstepping) / leadscrew_pitch`

Example for Sieg SC4:
- 1.8° NEMA 23 stepper (200 steps/rev)
- 1/16 microstepping
- Sieg SC4 leadscrew pitch (typically 1.5mm or 2mm)
- Result: `(200 * 16) / 1.5 = 2133 steps/mm` or `(200 * 16) / 2 = 1600 steps/mm`

### Updating Steps per Millimeter

Edit these lines in `CNC_accelstep.ino`:

```cpp
const float stepsPerMM_X = 100.0;  // Update for your X-axis
const float stepsPerMM_Z = 200.0;  // Update for your Z-axis
```

## Speed Calibration

### Potentiometer Mapping

The current mapping function:
```cpp
pdx = pow(map(analogRead(speedpotX),0,1023,64,1), 2)*10;
```

This creates a non-linear response where:
- Minimum speed: ~10 steps/second
- Maximum speed: ~40,960 steps/second

### Adjusting Speed Range

To modify the speed range, adjust the mapping parameters:

```cpp
// For linear mapping (0-1023 to 100-2000)
pdx = map(analogRead(speedpotX), 0, 1023, 100, 2000);

// For different non-linear curve
pdx = pow(map(analogRead(speedpotX), 0, 1023, 32, 1), 1.5) * 20;
```

## Limit Switch Calibration

### Homing Procedure

The system includes automatic homing functions:

```cpp
void HomeX() {
  // Move until switch is activated
  while (digitalRead(home_switch_X)) {
    // Move in negative direction
  }
  // Move until switch is deactivated
  while (!digitalRead(home_switch_X)) {
    // Move in positive direction
  }
  Xpos = 0;  // Set current position to zero
}
```

### Testing Homing

1. **Manual Test**: Trigger limit switches manually
2. **Movement Test**: Run homing sequence
3. **Position Verification**: Check if position resets to zero
4. **Repeatability Test**: Run homing multiple times

### Adjusting Homing Behavior

To modify homing speed or direction:

```cpp
// Change homing speed (delay between steps)
delay(5);  // Faster
delay(20); // Slower

// Change homing direction
digitalWrite(MOTOR_X_DIR_PIN, 0);  // Negative direction
digitalWrite(MOTOR_X_DIR_PIN, 1);  // Positive direction
```

## LCD Display Calibration

### I2C Address Detection

If LCD doesn't display, find the correct I2C address:

```cpp
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
    }
  }
}
```

### Updating LCD Address

Change the address in the main code:

```cpp
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);  // Update address
```

## G-Code File Calibration

### Coordinate System

The system uses a simplified G-code format:
- **X**: Cross slide position (mm)
- **Z**: Carriage position (mm)
- **F**: Feed rate (mm/min)

### File Format Example

```
X0.0 Z0.0 F200
X10.0 Z5.0
X20.0 Z10.0 F150
```

### Creating Test Files

1. **Simple Square**:
```
X0.0 Z0.0 F200
X10.0 Z0.0
X10.0 Z10.0
X0.0 Z10.0
X0.0 Z0.0
```

2. **Circle Approximation**:
```
X0.0 Z0.0 F200
X5.0 Z0.0
X10.0 Z5.0
X5.0 Z10.0
X0.0 Z5.0
X0.0 Z0.0
```

## Speed Factor Calibration

### Radius-Based Speed Adjustment

The system adjusts speed based on workpiece radius:

```cpp
float calculateSpeedFactor(float currentRadius) {
    float speedFactor = currentRadius / 19.0;
    return max(speedFactor, 0.4);
}
```

### Adjusting Speed Factors

- **Base radius**: Change `19.0` to your typical workpiece radius
- **Minimum speed**: Change `0.4` to desired minimum speed factor
- **Scaling**: Modify the division factor for different speed curves

## Testing and Verification

### Movement Accuracy Test

1. **Command a known distance** (e.g., 10mm)
2. **Measure actual movement** with calipers
3. **Calculate error**: `error = (actual - commanded) / commanded`
4. **Adjust steps per mm**: `new_steps = old_steps * (1 + error)`

### Speed Accuracy Test

1. **Set potentiometer to known position**
2. **Measure time for 100 steps**
3. **Calculate actual speed**: `speed = 100 / time`
4. **Compare to expected speed**
5. **Adjust mapping if necessary**

### Repeatability Test

1. **Move to position A**
2. **Move to position B**
3. **Return to position A**
4. **Measure final position**
5. **Repeat multiple times**
6. **Calculate standard deviation**

## Troubleshooting Calibration

### Common Issues

1. **Inconsistent movements**:
   - Check for mechanical backlash
   - Verify stepper driver settings
   - Check for loose connections

2. **Wrong direction**:
   - Swap motor wires
   - Invert direction pin logic
   - Check stepper driver wiring

3. **Speed too fast/slow**:
   - Adjust potentiometer mapping
   - Check stepper driver current settings
   - Verify power supply voltage

4. **Position drift**:
   - Check for missed steps
   - Verify stepper driver microstepping
   - Check for mechanical binding

### Calibration Checklist

- [ ] Steps per millimeter calculated and set
- [ ] Limit switches tested and working
- [ ] LCD display showing correct information
- [ ] Potentiometer range verified
- [ ] G-code files tested with simple shapes
- [ ] Speed factors adjusted for workpiece size
- [ ] Emergency stop tested
- [ ] All safety features verified 