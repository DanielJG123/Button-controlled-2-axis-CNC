# CNC Lathe Controller

A microcontroller-based system that converts a manual lathe into a computer numerical control (CNC) lathe using an Arduino Mega. This project provides manual control via potentiometers and buttons, plus automated cutting sequences using pre-loaded G-code files from an SD card.

## Features

- **Dual-Axis Control**: X and Z axis control for lathe operations
- **Manual Control**: 
  - Potentiometer-based speed control for each axis
  - Forward/backward direction buttons for each axis
  - Real-time LCD display showing current axis directions
- **Automated Sequences**: Pre-loaded G-code files for chess piece carving
- **Safety Features**: Limit switches for homing operations
- **User Interface**: 4x4 keypad for menu navigation and preset selection

## Hardware Requirements

### Microcontroller
- Arduino Mega 2560

### Lathe Platform
- Sieg SC4 Mini Lathe (converted from manual to CNC)

### Motors & Drivers
- 2x NEMA 23 Stepper motors (X and Z axes)
- Specialized bench power packs for current and voltage regulation
- Stepper motor drivers (compatible with AccelStepper library)

### Input Devices
- 2x Potentiometers (10kΩ) for speed control
- 4x4 Matrix Keypad
- 2x Direction control buttons
- 2x Limit switches for homing

### Display
- 16x2 I2C LCD Display

### Storage
- SD Card module for G-code files

### Power
- Specialized bench power packs for NEMA 23 stepper motors
- Current and voltage regulation for optimal motor performance
- 5V power for Arduino and components

## Pin Configuration

| Component | Pin | Description |
|-----------|-----|-------------|
| X-Axis Step | 3 | NEMA 23 stepper motor step signal |
| X-Axis Direction | 7 | NEMA 23 stepper motor direction |
| Y-Axis Step | 2 | NEMA 23 stepper motor step signal (Z-axis) |
| Y-Axis Direction | 5 | NEMA 23 stepper motor direction (Z-axis) |
| Z-Axis Step | 4 | Stepper motor step signal (unused) |
| Z-Axis Direction | 6 | Stepper motor direction (unused) |
| Stepper Enable | 8 | Enable all stepper drivers |
| X Limit Switch | 9 | X-axis homing switch |
| Y Limit Switch | 10 | Y-axis homing switch |
| X Speed Pot | A15 | X-axis speed control |
| Y Speed Pot | A0 | Y-axis speed control |
| SD Card CS | 53 | SD card chip select |
| LCD I2C | SDA/SCL | I2C communication |

### Keypad Pins
- Row Pins: 41, 40, 39, 38
- Column Pins: 45, 44, 43, 42

## Software Dependencies

### Required Libraries
- `AccelStepper` - Stepper motor control
- `MultiStepper` - Coordinated multi-axis movement
- `Keypad` - Matrix keypad interface
- `LiquidCrystal_I2C` - LCD display control
- `SD` - SD card file operations
- `Wire` - I2C communication
- `SPI` - SD card communication

### Installation
1. Install Arduino IDE
2. Install required libraries via Library Manager:
   - AccelStepper
   - Keypad
   - LiquidCrystal I2C

## Usage

### Manual Control
1. **Speed Control**: Use potentiometers to adjust X and Z axis speeds
2. **Direction Control**: Use buttons to change direction for each axis
3. **LCD Display**: Shows current direction status for both axes

### Automated Sequences
1. **Knight Piece**: Press '7' to execute Knight.txt G-code sequence
2. **Bishop Piece**: Press '6' to cycle through bishop carving states:
   - State 1: Move to starting position
   - State 2: Execute main cutting sequence
   - State 3: Finishing operations
   - State 4: Final finishing pass

### Keypad Functions
- `A`: Reserved for future use
- `C`: Toggle X-axis direction
- `D`: Toggle Y-axis direction
- `6`: Cycle through bishop carving states
- `7`: Execute knight piece carving

## G-Code File Format

The system reads simplified G-code files from the SD card. Each line should contain:
- X coordinate (optional, uses previous if omitted)
- Z coordinate (optional, uses previous if omitted)
- F feedrate (optional, uses previous if omitted)

Example:
```
X0.0 Z0.0 F200
X10.0 Z5.0
X20.0 Z10.0 F150
```

## Safety Considerations

- Always ensure proper workpiece clamping
- Verify tool clearance before starting automated sequences
- Keep emergency stop accessible
- Check limit switch functionality before operation
- Ensure proper grounding of all components
- **Sieg SC4 Specific**: Follow mechanical conversion guidelines in [Sieg SC4 Conversion Guide](docs/sieg-sc4-conversion.md)
- **NEMA 23 Motors**: Ensure proper current and voltage regulation via bench power packs

## Calibration

### Steps per Millimeter
- X-axis: 100 steps/mm
- Z-axis: 200 steps/mm

### Speed Mapping
- Potentiometer range: 0-1023
- Mapped to: 1-64 (inverted)
- Final speed: `pow(mapped_value, 2) * 10`

## Troubleshooting

### Common Issues
1. **Motors not moving**: Check enable pin and power supply
2. **LCD not displaying**: Verify I2C address (default: 0x27)
3. **SD card not reading**: Check wiring and file format
4. **Inaccurate movements**: Recalibrate steps per millimeter

### Debug Information
- Serial monitor output at 115200 baud
- LCD status messages during operations
- Step count and coordinate feedback

## Project Structure

```
CNC-Lathe-Controller/
├── CNC_accelstep.ino    # Main Arduino sketch
├── README.md            # This file
├── LICENSE              # Project license
├── docs/                # Documentation
│   ├── wiring.md        # Detailed wiring diagram
│   ├── calibration.md   # Calibration procedures
│   └── sieg-sc4-conversion.md # Sieg SC4 specific conversion guide
├── examples/            # Example G-code files
│   ├── Knight.txt       # Knight piece carving sequence
│   ├── Bishop.txt       # Bishop main cutting sequence
│   ├── Bishop_finishing.txt # Bishop finishing sequence
│   └── Test_Square.txt  # Simple test pattern
└── hardware/            # Hardware documentation
    ├── bom.md           # Bill of materials
    └── schematics/      # Circuit diagrams
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- AccelStepper library by Mike McCauley
- Keypad library by Mark Stanley and Alexander Brevig
- LiquidCrystal I2C library by Frank de Brabander

## Disclaimer

This project involves mechanical systems that can be dangerous if not properly implemented. Always follow proper safety procedures and ensure all components are correctly installed and tested before operation. The authors are not responsible for any injury or damage resulting from the use of this project. 