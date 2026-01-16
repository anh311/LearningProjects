# Microstrip Lines and λ Transformer Simulation

This simulation replicates the **Microstrip Line Experiment**: [Microstrip Lines and λ Transformer](HF-Projects/Microstrip Lines and λ Transformer)

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


## Conclusion

