# ui_helpers.py
import tkinter as tk
from PIL import Image, ImageTk
import os

# -----------------------------
# Dark Mode Farben
# -----------------------------
BG_COLOR = "#0B1F3B"        # Dunkelblauer Hintergrund
FG_COLOR = "#E0F7FF"        # Heller Text
BUTTON_BG = "#1A2E4D"       # Button Hintergrund
BUTTON_FG = "#E0F7FF"       # Button Text
BUTTON_ACTIVE_BG = "#274880" # Button Hover
BUTTON_ACTIVE_FG = "#FFFFFF"
ENTRY_BG = "#1A2E4D"        # Entry Hintergrund
ENTRY_FG = "#E0F7FF"        # Entry Textfarbe

# -----------------------------
# Widget-Hilfsfunktionen
# -----------------------------
def create_label(parent, text, font=("Arial", 14)):
    return tk.Label(parent, text=text, font=font, bg=BG_COLOR, fg=FG_COLOR)

def create_button(parent, text, command, width=20):
    return tk.Button(
        parent, text=text, width=width, bg=BUTTON_BG, fg=BUTTON_FG,
        activebackground=BUTTON_ACTIVE_BG, activeforeground=BUTTON_ACTIVE_FG,
        command=command
    )

def create_entry(parent):
    entry = tk.Entry(parent, bg=ENTRY_BG, fg=ENTRY_FG, insertbackground=ENTRY_FG)
    return entry

def show_error(parent, message):
    """Zeigt ein modales Fehlermeldungsfenster an."""
    error_window = tk.Toplevel(parent)
    error_window.title("Fehler")
    error_window.configure(bg=BG_COLOR)
    error_window.geometry("300x100")
    error_window.resizable(False, False)

    # Modal: man kann nur das Pop-up bedienen
    error_window.grab_set()

    # Nachricht
    msg = tk.Label(error_window, text=message, bg=BG_COLOR, fg=FG_COLOR, font=("Arial", 12))
    msg.pack(pady=20)

    # OK-Button
    btn = tk.Button(
        error_window, text="OK", width=10,
        bg=BUTTON_BG, fg=BUTTON_FG,
        activebackground=BUTTON_ACTIVE_BG,
        activeforeground=BUTTON_ACTIVE_FG,
        command=error_window.destroy
    )
    btn.pack(pady=5)

# -----------------------------
# Bilder laden
# -----------------------------
def load_design_image(path, size):
    """Lädt ein Bild und skaliert es."""
    img = Image.open(path)
    img = img.resize(size, Image.Resampling.LANCZOS)
    return ImageTk.PhotoImage(img)

# -----------------------------
# Projektstruktur / Image-Pfad
# -----------------------------
PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))  # ui_helpers.py liegt im Projektroot
# keine extra dirname() mehr, sonst sucht er zu weit oben

def get_image_path(filename):
    """Gibt den kompletten Pfad für ein Bild im images-Ordner zurück."""
    return os.path.join(PROJECT_ROOT, "images", filename)
