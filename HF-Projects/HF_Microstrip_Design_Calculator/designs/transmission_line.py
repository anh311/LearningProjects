import os
import tkinter as tk

from ui.base_design import BaseDesign
from calculations.transmission_calcs import (
    transmission_line_calculate_Z,
    transmission_line_calculate_w
)
from ui_helpers import get_image_path

class TransmissionLine(BaseDesign):
    def __init__(self, parent):
        params = ["Er", "h (mm)", "w (mm)", "Z (Ohm)"]

        modes = [
            {
                "label": "Calculate Z",
                "key": "Z (Ohm)",
                "inputs": ["Er", "h (mm)", "w (mm)"]
            },
            {
                "label": "Calculate width w",
                "key": "w (mm)",
                "inputs": ["Er", "h (mm)", "Z (Ohm)"]
            }
        ]

        funcs = {
            "Z (Ohm)": transmission_line_calculate_Z,
            "w (mm)": transmission_line_calculate_w
        }

        param_map = {
            "Er": "Er",
            "h (mm)": "h_mm",
            "w (mm)": "w_mm",
            "Z (Ohm)": "Z_Ohm"
        }

        # Optional: Bild rechts
        image_path = get_image_path("Microstrip.png")
        image_size = (350, 150)

        super().__init__(
            parent,
            "Transmission Line by Hammerstad",
            params,
            modes,
            funcs,
            image_path=image_path,
            image_size=image_size,
            param_map=param_map 
        )
