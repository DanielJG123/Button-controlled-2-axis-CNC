# Wiring Diagram and Connections

This document provides detailed wiring information for the CNC Lathe Controller project.

## Arduino Mega Pin Connections

### Stepper Motor Connections

#### X-Axis (Cross Slide)
- **Step Pin**: Digital Pin 3
- **Direction Pin**: Digital Pin 7
- **Enable**: Digital Pin 8 (shared with Y-axis)

#### Y-Axis (Carriage)
- **Step Pin**: Digital Pin 2
- **Direction Pin**: Digital Pin 5
- **Enable**: Digital Pin 8 (shared with X-axis)

#### Z-Axis (Spindle - if used)
- **Step Pin**: Digital Pin 4
- **Direction Pin**: Digital Pin 6
- **Enable**: Digital Pin 8 (shared)

### Input Devices

#### Speed Control Potentiometers
- **X-Axis Speed**: Analog Pin A15
- **Y-Axis Speed**: Analog Pin A0
- **Wiring**: 
  - Pin 1: 5V
  - Pin 2: Analog input
  - Pin 3: GND

#### Limit Switches
- **X-Axis Limit**: Digital Pin 9
- **Y-Axis Limit**: Digital Pin 10
- **Wiring**:
  - One terminal: Digital pin
  - Other terminal: GND
  - Internal pull-up resistors enabled

### User Interface

#### 4x4 Matrix Keypad
- **Row Pins**: 41, 40, 39, 38
- **Column Pins**: 45, 44, 43, 42
- **Key Layout**:
  ```
  1 2 3 A
  4 5 6 B
  7 8 9 C
  * 0 # D
  ```

#### I2C LCD Display (16x2)
- **SDA**: Arduino Mega SDA pin (Pin 20)
- **SCL**: Arduino Mega SCL pin (Pin 21)
- **VCC**: 5V
- **GND**: GND
- **I2C Address**: 0x27 (default)

### Storage

#### SD Card Module
- **CS**: Digital Pin 53
- **MOSI**: Digital Pin 51
- **MISO**: Digital Pin 50
- **SCK**: Digital Pin 52
- **VCC**: 5V
- **GND**: GND

## Power Supply Connections

### Stepper Motor Power
- **Voltage**: Regulated by specialized bench power pack
- **Current**: Regulated by specialized bench power pack for NEMA 23 motors
- **Connection**: To stepper driver power inputs via bench power pack

### Arduino Power
- **Voltage**: 5V DC (from USB or external supply)
- **Current**: ~500mA typical

## Stepper Driver Connections

### Typical A4988 or DRV8825 Setup
- **VMOT**: Bench power pack output
- **GND**: Common ground
- **VDD**: 5V logic power
- **STEP**: Arduino step pin
- **DIR**: Arduino direction pin
- **ENABLE**: Arduino enable pin
- **RESET**: Connect to SLEEP pin
- **SLEEP**: Connect to RESET pin

### Bench Power Pack Setup
- **Input**: AC mains power
- **Output**: Regulated DC for NEMA 23 stepper motors
- **Current Regulation**: Adjustable for optimal motor performance
- **Voltage Regulation**: Stable output for consistent operation

### Motor Connections
- **A+**: Motor coil A positive
- **A-**: Motor coil A negative
- **B+**: Motor coil B positive
- **B-**: Motor coil B negative

## Safety Considerations

### Emergency Stop
- Install emergency stop button in series with stepper enable
- Connect to enable pin through normally closed contact

### Limit Switch Installation
- Mount limit switches at safe travel limits
- Ensure proper actuation before mechanical stops
- Use normally open switches with pull-up resistors

### Grounding
- Connect all grounds together
- Ensure proper grounding of power supplies
- Use shielded cables for long runs

## Cable Management

### Recommended Cable Types
- **Signal wires**: 22-24 AWG stranded
- **Power wires**: 18-20 AWG stranded
- **Motor wires**: 18-20 AWG stranded

### Cable Routing
- Separate signal and power cables
- Use cable ties and routing clips
- Leave slack for movement
- Protect cables from sharp edges

## Testing Connections

### Continuity Test
1. Check all connections with multimeter
2. Verify no shorts between adjacent pins
3. Test limit switch operation
4. Verify potentiometer range

### Power-Up Sequence
1. Connect Arduino first
2. Power up logic circuits
3. Power up stepper drivers
4. Test motor movement
5. Verify all inputs and outputs

## Troubleshooting

### Common Wiring Issues
- **Reversed motor direction**: Swap A+ and A- or B+ and B-
- **No motor movement**: Check enable pin and power supply
- **Erratic behavior**: Check for loose connections
- **LCD not working**: Verify I2C address and connections
- **SD card issues**: Check SPI connections and card format

### Testing Procedures
1. Use Arduino serial monitor for debugging
2. Test each component individually
3. Verify voltage levels at each connection
4. Check for proper signal timing 