# Microstrip Line Experiment

## Goal
- Understand the behavior of λ/4 and λ/2 transformers
- Verify their basic properties
- Observe their effect on signal transmission

## Setup
- 50 Ω main microstrip line
- λ/4 and λ/2 transformer / resonator connected directly to the main line
- Measurement of S21 using a LiteVNA

## Theory
- λ/4 transformers are used for impedance matching
- A λ/4 line transforms an open circuit into a short circuit and vice versa
- λ/2 lines repeat the impedance of the load
- Resonance effects occur at specific frequencies

## Measurements

1. **Measurement 1**
   - **Setup:** Only the main 50 Ω microstrip line
   <img src="50Ohm_Transmissionline.png" alt="transmission line" width="500"/>
   - **Action:** Measure S21
   - **Observation / Note:** baseline transmission line is well-matched to 50 Ω

2. **Measurement 2**
   - **Setup:** Main line + λ/4 transformer short
   - **Action:** Measure S21
   - **Observation / Note:** Look for impedance transformation effects

3. **Measurement 3**
   - **Setup:** Main line + λ/2 transformer connected
   - **Action:** Measure S21
   - **Observation / Note:** Impedance repeats at load; resonance behavior

4. **Measurement 4**
   - **Setup:** Main line + λ/4 and λ/2 transformers together
   - **Action:** Measure S21
   - **Observation / Note:** Combined effects on transmission
