# Wilkinson Power Divider with Microstrip (FAILED – needs a slightly different structure and SMD resistor)

## Goal
- Try building a Wilkinson Power Divider at 1 GHz
- Check how it splits power and matches the ports
- Learn from the design and see what works and what doesn’t

## Setup
- FR4 board with single-sided copper (~1.5 mm thick)
- 50 Ω main microstrip line (~3 mm wide)
- λ/4 microstrip section: ~3.7 mm long, 1.5 mm wide (~70 Ω)
- 100 Ω wire resistor

## Theory
- A Wilkinson Power Divider splits input power evenly between two outputs (~-3 dB each)
- All ports are ideally matched, and the divider is theoretically lossless
- Isolation resistor ensures that the outputs don’t interfere with each other
- The λ/4 lines transform impedances to make everything match nicely

<img src="image/Wilkinson_Power_Divider.png" alt=" Wilkinson Power Divider" width="500"/>

## Measurements

- **Setup:**

   
- **Action:**
    - Measure S21,S31,S11
- **Observation / Note:**
      