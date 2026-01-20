# Microstrip Lines and λ Transformer Simulation

This simulation replicates the **Microstrip Line Experiment**: [Microstrip Lines and λ Transformer](../../HF-Projects/MicrostripLineAndLambdaTransformer)


## Goal
- Simulate λ/4 and λ/2 transformers on a microstrip line
- Verify their effects on signal transmission
- Compare simulated results with experimental measurements

## Setup
- **openEMS**: See Microstrip_Lines_and_λ_Transformer.m for the full setup (traded some accuracy for shorter simulation time)
- FR4 board with single-sided copper (1.5 mm thick)
- 50 Ω main microstrip line (3 mm wide)
- λ/4 and λ/2 transformers / resonators (3 mm wide) hooked up to the main line
- Shorted and open-ended terminations
- simulate S21 over frequency

## Theory
- λ/4 line transforms Open ↔ Short at its resonant frequency
- λ/2 line keeps the load impedance the same
- Resonance effects appear as peaks or dips in transmission (S21)

## Simulation Observations

1. **Measurement**
    - **Setup:**
        50 Ω microstrip
    
        <img src="img/Microstrip_Line_geo.png" alt="transmission line" width="500"/>
    
    - **Action:**
        Simulate S21,S11
      
        <img src="img/Microstrip_Line.png" alt="transmission line" width="500"/>
    - **Observation / Note:**
    
        transmission line is matched to 50 Ω

2. **Measurement**
   - **Setup:**
     
       λ/4 transformer (4cm @1GHz) with shorted end
   
       <img src="img/Microstrip_lambda4_short_geo.png" alt="transmission line" width="500"/>
     
   - **Action:**
     
       Measure S21, S11
     
       <img src="img/Microstrip_lambda4_short.png" alt="transmission line" width="500"/>
       
   - **Observation / Note:**
     - At ~1 GHz: the λ/4 line transforms the short into an open → S21 ≈ -2 dB (acts like a **band-pass**)
     - At ~2 GHz: the λ/2 line transforms the short into a short → S21 ≈ -40 dB (acts like a **band-stop / notch filter**)
     - Matches what theory says

3. **Measurement**
   - **Setup:**
     
       λ/4 transformer (4cm @1GHz) with open end
   
       <img src="img/Microstrip_lambda4_open_geo.png" alt="transmission line" width="500"/>
     
   - **Action:**
     
       Measure S21, S11
     
       <img src="img/Microstrip_lambda4_open.png" alt="transmission line" width="500"/>
       
   - **Observation / Note:**
     - At 1 GHz: the λ/4 line transforms open into an short → S21 ≈ -2 dB (acts like a **band-stop / notch filter**)
     - At 2 GHz: the λ/2 line transforms the open into a open → S21 ≈ -43 dB (acts like a **band-pass**)
     - Matches what theory says
       
4. **Measurement**
   - **Setup:**

      2x λ/4 transformers (4 cm @ 1 GHz) with shorted ends, 1 mm gap in between
     
      <img src="img/Microstrip_lambda4_2xshort_geo.png" alt="transmission line" width="500"/>
   - **Action:**
     
       Measure S21,S11
     
       <img src="img/Microstrip_lambda4_2xshort.png" alt="transmission line" width="500"/>
       
   - **Observation / Note:** Combined effects on transmission
       - **Simulation**: 2 λ/4 shorts → **two resonance dips** + S21 outside resonance drops (~-7 dB).  
       - **Real experiment**: same layout → **single dip** + S21 outside resonance almost 0 dB.
       - Why? Perfect geometry in sim → coupled resonators → standing waves. Reality = imperfections + losses → smoother, nicer-looking results??
       - Two λ/4 shorts act like **perfectly coupled resonators**.
       - Simulation shows **resonance splitting** → two dips + strong S21 drop outside resonance.


## End Note

Almost everything behaves as expected, but there are some quirks between simulation and real measurements:

- **Single λ/4 line**  
  - Transforms Open ↔ Short exactly as theory predicts.  

- **Single λ/2 line**  
  - Transforms Open → Open and Short → Short, just like expected.  

- **λ/4 line behavior**:  
  - **Short-ended:** acts like a parallel resonant circuit → you get dips (band-stop).  
  - **Open-ended:** acts like a series resonant circuit → you get peaks (band-pass).  

### Differences compared to real experiments

 **Ports matter**  
   Even with 50 Ω lumped ports, placement & size are super important:  
   - Signal needs to be **exactly on the microstrip**  
   - Ground has to be **directly below on the GND plane**  
   - Too close to the shorts → reflections → S21 drops outside resonance  

**Losses & material effects**  
   - FR4 and copper losses in real life **flatten the resonances**, smoothing peaks and troughs.  
   - Simulations assume **perfect metal & lossless dielectric**, which makes dips sharper and S21 more sensitive.  

**Grid / Mesh & FDTD settings**  
   - **Mesh fineness** is crucial: too coarse → transmission looks lower, fields not resolved properly.  
   - Smooth and refined mesh around **ports, line, and shorts** gives more realistic S21.  
   - **FDTD settings** like excitation type, central frequency, bandwidth, and `EndCriteria` affect results:  
     - Too strict → longer sim, very sharp resonances  
     - Too loose → inaccurate S-parameters, S21 may be artificially low outside resonance  
   - Basically: the better your mesh & simulation setup, the closer it looks to reality.  

---

**TL;DR:**  
- Simulations are idealized → can exaggerate dips and standing waves.  
- Real circuits have tolerances, parasitics, and losses → smoother response, often “better-looking” S21.  
- Pay attention to **ports, mesh, and FDTD settings** to make sim more realistic.  

