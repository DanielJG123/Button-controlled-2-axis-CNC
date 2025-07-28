# Sieg SC4 Lathe Conversion Guide

This document provides specific information for converting a Sieg SC4 Mini Lathe to CNC control.

## Sieg SC4 Lathe Specifications

### Original Lathe Features
- **Swing over bed**: 7" (178mm)
- **Distance between centers**: 12" (305mm)
- **Spindle bore**: 0.787" (20mm)
- **Spindle speeds**: 100-2000 RPM
- **Cross slide travel**: 3.5" (89mm)
- **Compound slide travel**: 2.5" (63.5mm)
- **Tailstock travel**: 2.5" (63.5mm)

### Mechanical Conversion Requirements

#### X-Axis (Cross Slide)
- **Leadscrew**: Replace manual leadscrew with ball screw or keep original
- **Motor mounting**: Custom bracket required for NEMA 23 stepper
- **Coupling**: Flexible coupling between motor and leadscrew
- **Bearing support**: Additional bearing support may be required

#### Z-Axis (Carriage)
- **Leadscrew**: Replace manual leadscrew with ball screw or keep original
- **Motor mounting**: Custom bracket required for NEMA 23 stepper
- **Coupling**: Flexible coupling between motor and leadscrew
- **Bearing support**: Additional bearing support may be required

## NEMA 23 Stepper Motor Specifications

### Recommended Motors
- **Size**: NEMA 23 (57mm x 57mm faceplate)
- **Step angle**: 1.8° (200 steps per revolution)
- **Holding torque**: 1.8-2.8 Nm (180-280 oz-in)
- **Current rating**: 2-3A per phase
- **Voltage**: 12-48V DC

### Motor Selection Considerations
- **Torque requirements**: NEMA 23 provides adequate torque for SC4
- **Size constraints**: Must fit within lathe dimensions
- **Heat generation**: Consider cooling for continuous operation
- **Noise levels**: NEMA 23 motors can be noisy at high speeds

## Specialized Bench Power Packs

### Power Requirements
- **Voltage**: 12-48V DC (adjustable)
- **Current**: 2-3A per motor (4-6A total)
- **Regulation**: Both voltage and current regulation required
- **Protection**: Overcurrent and overvoltage protection

### Recommended Power Pack Features
- **Adjustable voltage output**: 0-50V DC
- **Adjustable current limit**: 0-10A
- **Digital display**: Voltage and current monitoring
- **Protection circuits**: Overcurrent, overvoltage, short circuit
- **Cooling fan**: For continuous operation
- **Multiple outputs**: For powering multiple motors

### Power Pack Setup
1. **Initial setup**:
   - Set voltage to 24V DC (typical for NEMA 23)
   - Set current limit to 2.5A per motor
   - Connect to stepper drivers

2. **Fine tuning**:
   - Monitor motor temperature during operation
   - Adjust current limit if motors run too hot
   - Adjust voltage for optimal performance

## Mechanical Modifications

### X-Axis Conversion
1. **Remove manual handwheel** and associated components
2. **Fabricate motor mount** for NEMA 23 stepper
3. **Install flexible coupling** between motor and leadscrew
4. **Add bearing support** if required
5. **Install limit switch** for homing

### Z-Axis Conversion
1. **Remove manual handwheel** and associated components
2. **Fabricate motor mount** for NEMA 23 stepper
3. **Install flexible coupling** between motor and leadscrew
4. **Add bearing support** if required
5. **Install limit switch** for homing

### Mounting Considerations
- **Alignment**: Ensure motor and leadscrew are properly aligned
- **Backlash**: Minimize backlash in the system
- **Rigidity**: Ensure mounting is rigid enough for precision work
- **Accessibility**: Maintain access for maintenance

## Electrical Considerations

### Wiring Requirements
- **Motor wires**: Use appropriate gauge for current requirements
- **Shielding**: Shield motor wires to reduce electrical noise
- **Grounding**: Proper grounding for all components
- **Cable management**: Route wires to avoid interference

### Safety Features
- **Emergency stop**: Install emergency stop button
- **Limit switches**: Install limit switches for safety
- **Fuses**: Use appropriate fuses for protection
- **Enclosure**: Protect electronics from chips and coolant

## Calibration for SC4

### Steps per Millimeter
Typical values for Sieg SC4:
- **X-axis**: 100-200 steps/mm (depending on leadscrew)
- **Z-axis**: 200-400 steps/mm (depending on leadscrew)

### Speed Settings
- **Maximum speed**: 1500-2000 steps/second
- **Acceleration**: 800-1000 steps/second²
- **Jog speed**: 500-1000 steps/second

### Testing and Verification
1. **Manual movement test**: Verify motors move in correct directions
2. **Accuracy test**: Measure actual vs. commanded movements
3. **Speed test**: Verify speed control works properly
4. **Homing test**: Test limit switch functionality

## Maintenance Considerations

### Regular Maintenance
- **Lubrication**: Regular lubrication of leadscrews and bearings
- **Cleaning**: Remove chips and debris from moving parts
- **Inspection**: Regular inspection of couplings and mounts
- **Calibration**: Periodic recalibration of steps per millimeter

### Troubleshooting
- **Motor overheating**: Check current settings and cooling
- **Inaccurate movements**: Check for backlash and recalibrate
- **Noise issues**: Check alignment and lubrication
- **Electrical problems**: Check wiring and connections

## Cost Considerations

### Major Components
- **NEMA 23 motors**: $50-80 each
- **Bench power pack**: $100-200
- **Stepper drivers**: $20-40 each
- **Mechanical parts**: $100-200
- **Electronics**: $50-100

### Total Conversion Cost
- **Basic conversion**: $400-600
- **Professional conversion**: $600-1000
- **Complete system**: $800-1200

## Safety Warnings

⚠️ **IMPORTANT SAFETY CONSIDERATIONS**:

1. **Mechanical Safety**:
   - Ensure all mechanical modifications are properly secured
   - Test all movements at low speeds first
   - Keep hands clear of moving parts during operation

2. **Electrical Safety**:
   - Use appropriate fuses and circuit breakers
   - Ensure proper grounding
   - Protect electronics from chips and coolant

3. **Operation Safety**:
   - Never leave the lathe unattended during operation
   - Keep emergency stop accessible
   - Wear appropriate safety equipment

4. **Maintenance Safety**:
   - Disconnect power before maintenance
   - Use appropriate tools and procedures
   - Follow manufacturer guidelines

## Resources

### Documentation
- Sieg SC4 manual (if available)
- Stepper motor datasheets
- Power pack user manual

### Community Resources
- Online forums for lathe conversions
- YouTube tutorials for similar conversions
- Local maker spaces for advice

### Professional Help
- Machine shops for custom parts
- Electronics technicians for wiring
- CNC specialists for advanced features 