import tkinter as tk
import os
from calculations.transmission_calcs import transmission_line_calculate, transmission_line_calculate_inverse
from ui_helpers import load_design_image, show_error, BG_COLOR, FG_COLOR, create_label, create_button, create_entry, BUTTON_BG, BUTTON_FG, BUTTON_ACTIVE_BG, BUTTON_ACTIVE_FG, ENTRY_BG, ENTRY_FG

class TransmissionLine:
    def __init__(self, parent):
        self.parent = parent
        self.entries = {}
        self.z_entry = None
        self.geometry_image = None
        self.mode = tk.StringVar(value="calc_z")  # Default: Z berechnen
        self.create_ui()

    def create_ui(self):
        # Hauptframe für Links/ Rechts
        main_frame = tk.Frame(self.parent, bg=BG_COLOR)
        main_frame.pack(padx=20, pady=20, fill="both", expand=True)

        # Links: Eingabe-Frame
        input_frame = tk.Frame(main_frame, bg=BG_COLOR)
        input_frame.grid(row=0, column=0, sticky="nw")

        # Überschrift oben links
        title_label = tk.Label(
            input_frame,
            text="Transmission Line by Hammerstad",
            font=("Arial", 18, "bold"),
            bg=BG_COLOR,
            fg=FG_COLOR
        )
        title_label.grid(row=0, column=0, columnspan=2, sticky="nw", pady=(0,10))

        # Modus-Radiobuttons
        mode_frame = tk.Frame(input_frame, bg=BG_COLOR)
        mode_frame.grid(row=1, column=0, columnspan=2, sticky="w", pady=(0,15))

        rb_z = tk.Radiobutton(
            mode_frame,
            text="Calculate Z",
            variable=self.mode,
            value="calc_z",
            command=self.update_mode,
            bg=BG_COLOR,
            fg=FG_COLOR,
            selectcolor=BG_COLOR,
            activebackground=BG_COLOR,
            activeforeground=FG_COLOR
        )
        rb_z.pack(anchor="w")

        rb_w = tk.Radiobutton(
            mode_frame,
            text="Calculate width w",
            variable=self.mode,
            value="calc_w",
            command=self.update_mode,
            bg=BG_COLOR,
            fg=FG_COLOR,
            selectcolor=BG_COLOR,
            activebackground=BG_COLOR,
            activeforeground=FG_COLOR
        )
        rb_w.pack(anchor="w")

        # Rechts: Image-Frame
        image_frame = tk.Frame(main_frame, bg=BG_COLOR)
        image_frame.grid(row=0, column=1, sticky="ne", padx=20)

        # -----------------------------
        # Eingabefelder
        # -----------------------------
        params = ["Er", "h (mm)", "w (mm)", "Z (Ohm)"]  # Z am Ende
        for i, param in enumerate(params):
            label = create_label(input_frame, param)
            label.grid(row=i+2, column=0, sticky="w", pady=5)  # +2 wegen Überschrift + Modus

            entry = create_entry(input_frame)
            entry.grid(row=i+2, column=1, pady=5)

            if param == "Z (Ohm)":
                entry.config(state="readonly")
                self.z_entry = entry
            else:
                self.entries[param] = entry

        # Calculate Button
        calc_button = create_button(input_frame, "Calculate", self.calculate)
        calc_button.grid(row=len(params)+2, column=0, columnspan=2, pady=10)

        # -----------------------------
        # Bild rechts laden
        # -----------------------------
        project_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        image_path = os.path.join(project_dir, "images", "Microstrip.png")
        self.geometry_image = load_design_image(image_path, (350,150))
        image_label = tk.Label(image_frame, image=self.geometry_image, bg=BG_COLOR)
        image_label.pack()

        # Initiale Aktivierung der Felder nach Default-Modus
        self.update_mode()

    # -----------------------------
    # Modus umschalten
    # -----------------------------
    def update_mode(self):
        if self.mode.get() == "calc_z":
            # Z berechnen → w eingeben
            self.entries["w (mm)"].config(state="normal")
            self.entries["w (mm)"].delete(0, tk.END)  # w-Feld löschen
            self.z_entry.config(state="readonly")
            self.z_entry.delete(0, tk.END)          # Z-Feld löschen
        else:
            # w berechnen → Z eingeben
            self.entries["w (mm)"].config(state="readonly")
            self.entries["w (mm)"].delete(0, tk.END)  # w-Feld löschen
            self.z_entry.config(state="normal")
            self.z_entry.delete(0, tk.END)           # Z-Feld löschen

    # -----------------------------
    # Berechnung
    # -----------------------------
    def calculate(self):
        try:
            if self.mode.get() == "calc_z":
                # Werte außer Z einlesen
                values = {
                    "Er": float(self.entries["Er"].get()),
                    "h": float(self.entries["h (mm)"].get()),
                    "w": float(self.entries["w (mm)"].get())
                }
                result = transmission_line_calculate(**values)

                # Ergebnis in Z schreiben
                self.z_entry.config(state="normal")
                self.z_entry.delete(0, tk.END)
                self.z_entry.insert(0, f"{result:.3f}")  # Optional 3 Nachkommastellen
                self.z_entry.config(state="readonly", readonlybackground=ENTRY_FG, fg=ENTRY_BG)

            else:  # calc_w
                # Werte außer w einlesen
                values = {
                    "Er": float(self.entries["Er"].get()),
                    "h": float(self.entries["h (mm)"].get()),
                    "Z": float(self.z_entry.get())
                }
                result = transmission_line_calculate_inverse(**values)

                # Ergebnis in w schreiben
                self.entries["w (mm)"].config(state="normal")
                self.entries["w (mm)"].delete(0, tk.END)
                self.entries["w (mm)"].insert(0, f"{result:.3f}")
                self.entries["w (mm)"].config(state="readonly", readonlybackground=ENTRY_FG, fg=ENTRY_BG)

        except ValueError:
            show_error(self.parent, "Please enter valid numbers!")
