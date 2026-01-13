import tkinter as tk
from ui_helpers import (
    BG_COLOR, FG_COLOR,
    ENTRY_BG, ENTRY_FG,
    create_label, create_entry, create_button,
    show_error, load_design_image
)

class BaseDesign:
    def __init__(self, parent, title, params, modes, calculate_funcs,
                 image_path=None, image_size=(350,150), param_map=None):
        self.parent = parent
        self.params = params
        self.param_map = param_map
        self.modes = modes
        self.calculate_funcs = calculate_funcs
        self.entries = {}
        self.mode = tk.StringVar(value=modes[0]["key"])
        self.image = None
        self.image_size = image_size
        self._build_ui(title, image_path)

    # -----------------------------
    # UI Aufbau
    # -----------------------------
    def _build_ui(self, title, image_path):
        main = tk.Frame(self.parent, bg=BG_COLOR)
        main.pack(padx=20, pady=20, fill="both", expand=True)

        left = tk.Frame(main, bg=BG_COLOR)
        left.grid(row=0, column=0, sticky="nw")

        tk.Label(left, text=title, font=("Arial", 18, "bold"),
                 bg=BG_COLOR, fg=FG_COLOR).grid(row=0, column=0, columnspan=2, sticky="w", pady=(0,10))

        self._create_mode_buttons(left)
        self._create_entries(left)

        create_button(left, "Calculate", self.calculate)\
            .grid(row=len(self.params)+3, column=0, columnspan=2, pady=10)

        if image_path:
            right = tk.Frame(main, bg=BG_COLOR)
            right.grid(row=0, column=1, sticky="ne", padx=20)
            img = load_design_image(image_path, self.image_size)
            tk.Label(right, image=img, bg=BG_COLOR).pack()
            self.image = img

        self.update_mode()

    # -----------------------------
    # Modus Radiobuttons
    # -----------------------------
    def _create_mode_buttons(self, parent):
        frame = tk.Frame(parent, bg=BG_COLOR)
        frame.grid(row=1, column=0, columnspan=2, sticky="w", pady=10)

        for m in self.modes:
            tk.Radiobutton(
                frame, text=m["label"],
                variable=self.mode, value=m["key"],
                command=self.update_mode,
                bg=BG_COLOR, fg=FG_COLOR,
                selectcolor=BG_COLOR,
                activebackground=BG_COLOR,
                activeforeground=FG_COLOR
            ).pack(anchor="w")

    # -----------------------------
    # Parameter Eingabefelder
    # -----------------------------
    def _create_entries(self, parent):
        for i, p in enumerate(self.params):
            create_label(parent, p).grid(row=i+2, column=0, sticky="w", pady=5)
            e = create_entry(parent)
            e.grid(row=i+2, column=1, pady=5)
            self.entries[p] = e

    # -----------------------------
    # Modus Umschalten
    # -----------------------------
    def update_mode(self):
        calc_field = self.mode.get()
        for name, entry in self.entries.items():
            entry.config(state="normal", bg=ENTRY_BG, fg=ENTRY_FG)
            # Falls outputs definiert sind, diese Felder readonly setzen
            mode = next(m for m in self.modes if m["key"] == calc_field)
            readonly_fields = mode.get("outputs", [calc_field])
            if name in readonly_fields:
                entry.delete(0, tk.END)
                entry.config(state="readonly", bg=ENTRY_BG, fg=ENTRY_FG)

    # -----------------------------
    # Berechnung
    # -----------------------------
    def calculate(self):
        try:
            calc_field = self.mode.get()
            mode = next(m for m in self.modes if m["key"] == calc_field)

            # Eingaben einlesen
            values = {k: float(self.entries[k].get()) for k in mode["inputs"]}
            if hasattr(self, "param_map"):
                values = {self.param_map[k]: v for k, v in values.items()}

            # Berechnung durchführen
            result = self.calculate_funcs[calc_field](**values)

            # Ergebnisse eintragen (ein Wert oder Dict)
            if isinstance(result, dict):
                for key, val in result.items():
                    if key in self.entries:
                        e = self.entries[key]
                        e.config(state="normal")
                        e.delete(0, tk.END)
                        e.insert(0, f"{val:.6f}")
                        e.config(state="readonly", bg=ENTRY_FG, fg=ENTRY_BG)
            else:
                e = self.entries[calc_field]
                e.config(state="normal")
                e.delete(0, tk.END)
                e.insert(0, f"{result:.6f}")
                e.config(state="readonly", bg=ENTRY_FG, fg=ENTRY_BG)

        except ValueError:
            from ui_helpers import show_error
            show_error(self.parent, "Please enter valid numbers!")
