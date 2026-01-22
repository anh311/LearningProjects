# Wilkinson Power Divider with Microstrip (FAILED – my structure was bad and SMD resistor needed)

## Goal
- Try simulate a Wilkinson Power Divider at 1 GHz
- Check how it splits power and matches the ports


## Setup
- FR4 board with single-sided copper (1.5 mm thick)
- 50 Ω main microstrip line (3 mm wide)
- λ/4 microstrip section: 3.7 mm long, 1.5 mm wide (~70 Ω)
- 100 Ω resistor

## Theory
- A Wilkinson Power Divider splits input power evenly between two outputs (~-3 dB each)
- All ports are ideally matched, and the divider is theoretically lossless
- Isolation resistor ensures that the outputs don’t interfere with each other
- The λ/4 lines transform impedances to make everything match nicely

    <img src="img/Wilkinson_Power_Divider.png" alt=" Wilkinson Power Divider" width="500"/>

## Simulations

- **Setup:**
  
    <img src="img/Wilkinson.png" alt=" Wilkinson Power Divider" width="500"/>
   
- **Action:**
  
    - simulate S21,S31,S11
  
        Port 2
      
        <img src="img/S21_S11.png" alt=" Wilkinson Power Divider" width="500"/>
        
        Port 3
      
        <img src="img/S31_S11.png" alt=" Wilkinson Power Divider" width="500"/>

    - simulate S12,S32,S22
  
        Port 1
      
        <img src="img/S12_S22.png" alt=" Wilkinson Power Divider" width="500"/>
        
        Port 3
      
        <img src="img/S32_S22.png" alt=" Wilkinson Power Divider" width="500"/>

    - simulate S13,S23,S33
  
        Port 1
      
        <img src="img/S13_S33.png" alt=" Wilkinson Power Divider" width="500"/>
        
        Port 3
      
        <img src="img/S23_S33.png" alt=" Wilkinson Power Divider" width="500"/>
     
    
- **Observation / Note:** 
    
