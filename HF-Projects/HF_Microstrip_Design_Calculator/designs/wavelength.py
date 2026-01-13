import os
import tkinter as tk

from ui.base_design import BaseDesign
from calculations.wavelength_calc import (
    wavelength_calc_lamda,
    wavelength_calc_f
)
from ui_helpers import get_image_path

class WaveLength(BaseDesign):
    def __init__(self, parent):
        params = ["Er", "f (GHz)", "lamda (cm)"]

        modes = [
            {
                "label": "Calculate lamda",
                "key": "lamda (cm)",
                "inputs": ["Er","f (GHz)"]
            },
            {
                "label": "Calculate f",
                "key": "f (GHz)",
                "inputs": ["Er","lamda (cm)"]
            }
        ]

        funcs = {
            "f (GHz)": wavelength_calc_f,
            "lamda (cm)": wavelength_calc_lamda
        }

        param_map = {
            "Er": "Er",
            "lamda (cm)": "lamda_cm",
            "f (GHz)": "f_GHz"
        }

        # Optional: Bild rechts
        image_path = get_image_path("wavelength.png")  
        image_size = (350, 150)                        

        super().__init__(
            parent,
            "Wavelength in a Transmission Line",
            params,
            modes,
            funcs,
            image_path=image_path,
            image_size=image_size,
            param_map=param_map 
        )
