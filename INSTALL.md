# Installation Guide

This guide will help you set up the CNC Lathe Controller system on your Arduino Mega.

## Prerequisites

### Software Requirements
- Arduino IDE (version 1.8.x or later)
- USB cable for Arduino Mega
- SD card (8GB or larger, formatted as FAT32)

### Hardware Requirements
- Arduino Mega 2560
- Sieg SC4 Mini Lathe (or similar)
- NEMA 23 stepper motors
- Specialized bench power packs
- All components listed in the [Bill of Materials](hardware/bom.md)

## Step 1: Install Arduino IDE

1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the IDE following the instructions for your operating system
3. Launch Arduino IDE

## Step 2: Install Required Libraries

Open Arduino IDE and install the following libraries via Library Manager:

1. **AccelStepper**
   - Go to `Tools` → `Manage Libraries...`
   - Search for "AccelStepper"
   - Install the library by Mike McCauley

2. **Keypad**
   - Search for "Keypad"
   - Install the library by Mark Stanley and Alexander Brevig

3. **LiquidCrystal I2C**
   - Search for "LiquidCrystal I2C"
   - Install the library by Frank de Brabander

## Step 3: Prepare SD Card

1. Format the SD card as FAT32
2. Copy the G-code files from the `examples/` folder to the SD card root:
   - `Knight.txt`
   - `Bishop.txt`
   - `Bishop_finishing.txt`
   - `Test_Square.txt` (for testing)

## Step 4: Upload Code

1. Connect Arduino Mega to your computer via USB
2. Open `CNC_accelstep.ino` in Arduino IDE
3. Select the correct board:
   - Go to `Tools` → `Board` → `Arduino AVR Boards` → `Arduino Mega or Mega 2560`
4. Select the correct port:
   - Go to `Tools` → `Port` → Select the port with Arduino Mega
5. Click the upload button (→) or press `Ctrl+U` (Windows/Linux) or `Cmd+U` (Mac)

## Step 5: Hardware Assembly

Follow the [wiring guide](docs/wiring.md) to connect all components:

1. **Stepper Motors**
   - Connect X-axis stepper to pins 3 (step) and 7 (direction)
   - Connect Y-axis stepper to pins 2 (step) and 5 (direction)
   - Connect enable pin to pin 8

2. **Input Devices**
   - Connect X-axis potentiometer to A15
   - Connect Y-axis potentiometer to A0
   - Connect keypad to pins 41, 40, 39, 38 (rows) and 45, 44, 43, 42 (columns)

3. **Display and Storage**
   - Connect LCD to I2C pins (SDA: 20, SCL: 21)
   - Connect SD card module to SPI pins (CS: 53, MOSI: 51, MISO: 50, SCK: 52)

4. **Limit Switches**
   - Connect X-axis limit switch to pin 9
   - Connect Y-axis limit switch to pin 10

## Step 6: Power Supply

1. **Logic Power**: Arduino can be powered via USB or external 5V supply
2. **Motor Power**: Connect specialized bench power pack to stepper drivers
3. **Bench Power Pack Setup**: Configure current and voltage regulation for NEMA 23 motors
4. **Safety**: Ensure proper grounding and use appropriate fuses

## Step 7: Initial Testing

### Basic Functionality Test
1. Power on the system
2. LCD should display initial direction status
3. Turn potentiometers to test speed control
4. Press keypad buttons to test direction changes

### Motor Test
1. **Manual Control**: Use potentiometers to control motor speed
2. **Direction Test**: Press 'C' and 'D' to change directions
3. **Display Test**: Verify LCD shows correct direction information

### G-Code Test
1. Insert SD card with test files
2. Press '7' to execute Knight.txt
3. Press '6' to cycle through bishop states
4. Monitor LCD for status updates

## Step 8: Calibration

Follow the [calibration guide](docs/calibration.md) to:

1. **Calculate steps per millimeter** for your specific setup
2. **Test limit switches** and homing functionality
3. **Adjust speed mapping** if needed
4. **Verify G-code execution** with test files

## Step 9: Safety Setup

1. **Emergency Stop**: Install and test emergency stop button
2. **Limit Switches**: Verify proper installation and operation
3. **Tool Clearance**: Ensure adequate clearance before operation
4. **Workpiece Clamping**: Secure workpiece properly

## Troubleshooting

### Common Issues

1. **Arduino not recognized**
   - Check USB cable and drivers
   - Try different USB port
   - Install Arduino drivers if needed

2. **Motors not moving**
   - Check power supply connections
   - Verify enable pin (pin 8)
   - Check stepper driver connections

3. **LCD not displaying**
   - Check I2C address (default: 0x27)
   - Verify wiring connections
   - Use I2C scanner to find correct address

4. **SD card not reading**
   - Check card format (must be FAT32)
   - Verify SPI connections
   - Test with different SD card

5. **G-code execution errors**
   - Check file format and syntax
   - Verify file names match code
   - Check SD card file structure

### Debug Information

- **Serial Monitor**: Open at 115200 baud for debug output
- **LCD Messages**: Status information during operation
- **LED Indicators**: Check for error indicators on components

## Next Steps

1. **Customize G-code files** for your specific projects
2. **Add safety features** like emergency stop
3. **Implement additional features** like tool change
4. **Optimize performance** based on your lathe specifications

## Support

- Check the [troubleshooting section](docs/calibration.md#troubleshooting-calibration)
- Review [wiring documentation](docs/wiring.md)
- Consult Arduino forums for general Arduino issues
- Create an issue on GitHub for project-specific problems

## Safety Reminder

⚠️ **IMPORTANT**: This system controls mechanical equipment that can be dangerous. Always:
- Follow proper safety procedures
- Keep emergency stop accessible
- Verify all connections before operation
- Test with low speeds first
- Never leave the system unattended during operation 