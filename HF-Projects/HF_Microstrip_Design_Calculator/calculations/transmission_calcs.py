import math
from scipy.optimize import fsolve
import numpy as np
# calculations/transmission_calcs.py

def transmission_line_calculate_Z(Er, h_mm, w_mm):
    """
    Berechnet die charakteristische Impedanz einer Mikrostreifenleitung nach Hammerstad.
    
    Parameter:
        Er   : float - relative Permittivität des Substrats
        h_mm : float - Substrathöhe in mm
        w_mm : float - Leiterbreite in mm
        t : float - Leiterplattendicke in mm (Standard 0.035 mm)
    
    Rückgabe:
        Z       : float - charakteristische Impedanz in Ohm
        Eeff     : float - effektive Dielektrizitätszahl
    """

    h = h_mm
    W = w_mm
    t = 0.035 

    # Effektive Breite W_eff (Korrektur für Leiterplattendicke t)
    if t > 0:
        W_eff = W + t / math.pi * (1 + math.log(4 * math.e / (t/h * (1/math.tanh(math.sqrt(6.517 * W/h))))))
    else:
        W_eff = W

    # Verhältnis W/h
    wh_ratio = W_eff / h

    # Effektive Dielektrizitätszahl
    Eeff = (Er + 1)/2 + (Er - 1)/2 * (1 + 12/wh_ratio)**-0.5

    # Charakteristische Impedanz
    if wh_ratio <= 1:
        Z = (60 / math.sqrt(Eeff)) * math.log(8/wh_ratio + 0.25*wh_ratio)
    else:
        Z = (120 * math.pi) / (math.sqrt(Eeff) * (wh_ratio + 1.393 + 0.667*math.log(wh_ratio + 1.444)))

    return Z

def transmission_line_calculate_w(Er, h_mm, Z_Ohm):
    """
    Berechnet die Mikrostreifenbreite W für eine gewünschte Impedanz Z0 (schmale Leiter W<h)
    
    Parameter:
        Z_target : float - gewünschte charakteristische Impedanz Ohm
        Er        : float - relative Permittivität
        h_mm      : float - Substrathöhe mm
        t_mm      : float - Leiterdicke mm (Standard 0.035 mm)
    
    Rückgabe:
        W_mm      : float - benötigte Leiterbreite mm
    """
    
    h = h_mm
    t = 0.035

    # Funktion zur Berechnung von Z0 für gegebenes W
    def Z0_equation(W):
        W = W[0]  # fsolve übergibt ein Array, wir brauchen die erste Komponente
        W_eff = W + t / np.pi * (1 + np.log(4 * np.e / (t/h * (1/np.tanh(np.sqrt(6.517 * W/h))))))
        wh_ratio = W_eff / h
        Eeff = (Er + 1)/2 + (Er - 1)/2 * (1 + 12/wh_ratio)**-0.5
        Z0 = (60 / np.sqrt(Eeff)) * np.log(8/wh_ratio + 0.25*wh_ratio)
        return Z0 - Z_Ohm

    W_initial = [0.5 * h]  # Startwert als Array
    W_solution = fsolve(Z0_equation, W_initial)
    return W_solution[0]
