import math
# calculations/WilkinsonPowerDivider_calcs.py

def WilkinsonPowerDivider_calculate_lamda_4(Er, Z_Ohm, f_GHz):
    """
    Calculates the guided wavelength of a microstrip line for a Wilkinson Power Divider.

    Parameters:
        Er     : float - effective dielectric constant of the substrate
        Z_Ohm  : float - characteristic impedance in ohms (not used in wavelength calculation)
        f_GHz  : float - frequency in GHz

    Returns:
        lamda  : float - guided wavelength in centimeters
    """

    # Speed of light in vacuum (m/s)
    c = 299_792_458

    # Convert frequency from GHz to Hz
    f = f_GHz * 1e9

    # Calculate guided wavelength: lambda/4 = c / (f * sqrt(Er)*4)
    lamda_4 = c / (f * math.sqrt(Er)*4)

    
    return lamda_4 * 100  # now in cm


def WilkinsonPowerDivider_calculate_Z1(Er, Z_Ohm, f_GHz):
    """
    Calculates the characteristic impedance Z1 for a Wilkinson Power Divider.

    Parameters:
        Er     : float - effective dielectric constant of the substrate (not used in calculation)
        Z_Ohm  : float - reference impedance in ohms
        f_GHz  : float - frequency in GHz (not used in calculation)

    Returns:
        Z1     : float - calculated impedance in ohms
    """

    # Standard Wilkinson Power Divider formula: Z1 = Z0 * sqrt(2)
    Z1 = Z_Ohm * math.sqrt(2)
    return Z1