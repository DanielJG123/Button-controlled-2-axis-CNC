# Bill of Materials (BOM)

This document lists all components required to build the CNC Lathe Controller system.

## Microcontroller

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Arduino Mega 2560 | Main microcontroller board | 1 | $15-25 |

## Motors and Drivers

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Stepper Motor (X-axis) | NEMA 23, 1.8° step angle | 1 | $25-40 |
| Stepper Motor (Z-axis) | NEMA 23, 1.8° step angle | 1 | $25-40 |
| Stepper Driver | A4988 or DRV8825 | 2 | $5-15 each |
| Specialized Bench Power Pack | Current and voltage regulation for NEMA 23 | 1 | $50-100 |
| Motor Mounting Brackets | For Sieg SC4 lathe | 2 | $15-25 |

## Input Devices

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Potentiometer (10kΩ) | X-axis speed control | 1 | $1-3 |
| Potentiometer (10kΩ) | Z-axis speed control | 1 | $1-3 |
| 4x4 Matrix Keypad | Membrane or mechanical | 1 | $3-8 |
| Limit Switch | Micro switch, normally open | 2 | $2-5 each |
| Push Button | Direction control | 2 | $1-3 each |

## Display

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| LCD Display | 16x2 I2C LCD | 1 | $5-10 |
| I2C Adapter | If not included with LCD | 1 | $2-5 |

## Storage

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| SD Card Module | SPI interface | 1 | $2-5 |
| SD Card | 8GB or larger, Class 10 | 1 | $5-10 |

## Power Supply

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Specialized Bench Power Pack | For NEMA 23 stepper motors | 1 | $50-100 |
| Power Supply | 5V DC, 1A (for Arduino) | 1 | $10-20 |
| Power Distribution Board | Optional | 1 | $5-15 |

## Mechanical Components

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Leadscrew | For X-axis (if not using existing) | 1 | $20-50 |
| Leadscrew | For Z-axis (if not using existing) | 1 | $20-50 |
| Couplings | Motor to leadscrew | 2 | $5-15 each |
| Bearings | For leadscrew support | 4-6 | $3-8 each |
| Mounting Hardware | Screws, nuts, washers | Various | $10-20 |

## Electronics

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Breadboard | For prototyping | 1 | $5-10 |
| Jumper Wires | Male-to-male, male-to-female | 50+ | $5-10 |
| Wire | 22-24 AWG stranded | 50ft | $10-20 |
| Wire | 18-20 AWG for power | 20ft | $10-15 |
| Terminal Blocks | For power distribution | 4-6 | $2-5 each |
| Fuse Holder | 5A fuse | 1 | $2-5 |
| Fuse | 5A, 250V | 1 | $1-2 |

## Enclosure and Mounting

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Enclosure | Project box | 1 | $15-30 |
| Panel Mount Components | For enclosure | Various | $10-20 |
| Cable Glands | For wire entry | 4-6 | $2-5 each |
| Heat Shrink Tubing | Various sizes | 1 pack | $5-10 |

## Tools Required

| Item | Description | Estimated Cost |
|------|-------------|----------------|
| Soldering Iron | 40W or higher | $20-50 |
| Solder | Lead-free, 0.6mm | $5-10 |
| Wire Strippers | | $10-20 |
| Crimping Tool | For terminals | $15-30 |
| Multimeter | Digital | $20-50 |
| Drill and Bits | For mounting | $30-100 |
| Screwdrivers | Various sizes | $10-20 |

## Optional Components

| Item | Description | Quantity | Estimated Cost |
|------|-------------|----------|----------------|
| Emergency Stop Button | Normally closed | 1 | $10-20 |
| Status LEDs | For visual feedback | 4-6 | $2-5 |
| Cooling Fan | For stepper drivers | 1 | $5-10 |
| Heat Sinks | For stepper drivers | 2 | $3-8 each |
| Cable Management | Cable ties, clips | Various | $5-10 |

## Total Estimated Cost

**Basic System**: $200-400
**Complete System with Enclosure**: $250-500
**Professional Setup**: $400-700

*Note: Higher cost due to specialized NEMA 23 motors and bench power packs required for Sieg SC4 lathe.*

*Note: Costs are approximate and may vary based on location, quality, and availability.*

## Sourcing Recommendations

### Online Retailers
- **Arduino**: Official Arduino store or authorized resellers
- **Electronics**: Digi-Key, Mouser, SparkFun, Adafruit
- **Motors**: Automation Direct, StepperOnline, Pololu
- **Mechanical**: McMaster-Carr, Misumi, local hardware stores

### Local Sources
- Electronics stores
- Hardware stores
- Machine shops
- Scrap yards (for mechanical parts)

## Quality Considerations

### Critical Components
- **Stepper Motors**: Choose quality motors with proper torque rating
- **Stepper Drivers**: A4988 for basic use, DRV8825 for higher performance
- **Power Supply**: Ensure adequate current rating and stable voltage
- **Wiring**: Use appropriate gauge for current requirements

### Cost vs. Quality
- **Budget Option**: Use basic components, may require more maintenance
- **Mid-Range**: Good balance of cost and reliability
- **Professional**: Industrial-grade components, maximum reliability

## Alternative Components

### Stepper Motors
- **NEMA 17**: Smaller, lighter, good for small lathes (not recommended for SC4)
- **NEMA 23**: Recommended for Sieg SC4 lathe, good torque and reliability
- **NEMA 34**: Industrial grade, maximum torque (overkill for SC4)

### Stepper Drivers
- **A4988**: Basic, inexpensive, good for learning
- **DRV8825**: Higher current, better performance
- **TMC2208**: Silent operation, advanced features
- **TMC2130**: SPI control, advanced features

### Display Options
- **16x2 LCD**: Basic, inexpensive
- **20x4 LCD**: More information display
- **OLED Display**: Modern, better visibility
- **Touch Screen**: Advanced user interface 