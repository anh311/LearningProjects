import os
import tkinter as tk

from ui.base_design import BaseDesign
from calculations.WilkinsonPowerDivider_calcs import (
    WilkinsonPowerDivider_calculate_lamda_4,
    WilkinsonPowerDivider_calculate_Z1
)
from ui_helpers import get_image_path
class WilkinsonDivider(BaseDesign):
    def __init__(self, parent):
        params = ["Er", "f (GHz)", "Z (Ohm)", "Z1 (Ohm)", "lamda/4 (cm)"]

        modes = [
            {
                "label": "Calculate Z1 and lamda/4",
                "key": "all",
                "inputs": ["Er", "f (GHz)", "Z (Ohm)"],
                "outputs": ["Z1 (Ohm)", "lamda/4 (cm)"]
            }
        ]

        # Berechnung als Dict für mehrere Outputs
        def calc_all(Er, f_GHz, Z_Ohm):
            return {
                "Z1 (Ohm)": WilkinsonPowerDivider_calculate_Z1(Er, Z_Ohm, f_GHz),
                "lamda/4 (cm)": WilkinsonPowerDivider_calculate_lamda_4(Er, Z_Ohm, f_GHz)
            }

        funcs = {"all": calc_all}

        param_map = {
            "Er": "Er",
            "f (GHz)": "f_GHz",
            "Z (Ohm)": "Z_Ohm",
            "Z1 (Ohm)": "Z1_Ohm",
            "lamda/4 (cm)": "lamda_4_cm"
        }

        super().__init__(
            parent,
            "Wilkinson Power Divider",
            params,
            modes,
            funcs,
            image_path=get_image_path("Wilkinson_Power_Divider.png"),
            image_size=(350,150),
            param_map=param_map
        )
