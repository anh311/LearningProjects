import math

# calculations/wavelength_calcs.py

def wavelength_calc_lamda(Er, f_GHz):
    """
    Berechnet die geführte Wellenlänge einer Mikrostreifenleitung.

    Parameter:
        Er     : float - effektive Dielektrizitätszahl des Substrats
        f_GHz  : float - Frequenz in GHz

    Rückgabe:
        lamda  : float - geführte Wellenlänge in Metern
    """

    # Lichtgeschwindigkeit im Vakuum (m/s)
    c = 299_792_458

    # Frequenz in Hz umrechnen
    f = f_GHz * 1e9

    # Geführte Wellenlänge berechnen: lambda = c / (f * sqrt(Er))
    lamda = c / (f * math.sqrt(Er))

    return lamda*100

def wavelength_calc_f(Er, lamda_cm):
    """
    Berechnet die Frequenz einer Mikrostreifenleitung aus der geführten Wellenlänge.

    Parameter:
        Er        : float - effektive Dielektrizitätszahl des Substrats
        lamda_cm  : float - geführte Wellenlänge in Zentimetern

    Rückgabe:
        f_GHz     : float - Frequenz in GHz
    """

    # Lichtgeschwindigkeit im Vakuum (m/s)
    c = 299_792_458

    # Wellenlänge in Meter umrechnen
    lamda_m = lamda_cm / 100.0

    # Frequenz berechnen: f = c / (lambda * sqrt(Er))
    f_Hz = c / (lamda_m * math.sqrt(Er))

    # In GHz umrechnen
    f_GHz = f_Hz / 1e9

    return f_GHz