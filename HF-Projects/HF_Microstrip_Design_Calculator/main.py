import tkinter as tk
from tkinter import ttk
from designs.transmission_line import TransmissionLine
from ui_helpers import BG_COLOR, FG_COLOR, create_label, create_button, create_entry, BUTTON_BG, BUTTON_FG, BUTTON_ACTIVE_BG, BUTTON_ACTIVE_FG, ENTRY_BG, ENTRY_FG
# -----------------------------
# Liste aller Designs
# -----------------------------
DESIGNS = [
    ("Transmission Line", TransmissionLine),
    ("Transmission Line", TransmissionLine),
    ("Transmission Line", TransmissionLine),
    ("Transmission Line", TransmissionLine),
    ("Transmission Line", TransmissionLine),
    ("Transmission Line", TransmissionLine),
]

# -----------------------------
# Funktion um Design anzuzeigen
# -----------------------------
def show_design(design_class):
    for widget in window.winfo_children():
        widget.destroy()
    
    # Design initialisieren
    design_class(window)
    
    # Back-Button unten
    back_button = tk.Button(window, text="Back", command=start_screen,bg=BG_COLOR, fg=FG_COLOR)
    back_button.pack(side="bottom", padx=10, pady=10)

# -----------------------------
# Startscreen
# -----------------------------
def start_screen():
    for widget in window.winfo_children():
        widget.destroy()

    window.configure(bg=BG_COLOR)

    # Titel
    label = tk.Label(window, text="HF Microstrip Design Calculator", font=("Arial", 16),bg=BG_COLOR, fg=FG_COLOR)
    label.pack(pady=20)

    # Buttons Frame
    button_frame = tk.Frame(window, bg=BG_COLOR)
    button_frame.pack(pady=20)

    cols = 3  # max Buttons pro Reihe
    for i, (name, cls) in enumerate(DESIGNS):
        row = i // cols
        col = i % cols
        btn = tk.Button(button_frame, text=name, width=20, bg=BUTTON_BG, fg=BUTTON_FG,
                        activebackground=BUTTON_ACTIVE_BG, activeforeground=BUTTON_ACTIVE_FG,
                        command=lambda c=cls: show_design(c))
        btn.grid(row=row, column=col, padx=10, pady=10)

# -----------------------------
# Hauptfenster
# -----------------------------
window = tk.Tk()
window.title("HF Microstrip Design Calculator")
window.geometry("800x400")
window.resizable(False, False)
window.configure(bg=BG_COLOR)

start_screen()
window.mainloop()



