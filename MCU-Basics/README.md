# MCU Basics

All projects in this folder are developed and tested using **VS Code with PlatformIO**.

## Structure

  Each subfolder represents a small project e.g., GPIO, PWM, sensors, communication protocols, or integrated projects.  

## Concepts

**Board selection**:  
  When creating a new project, the chosen board defines the **hardware mapping**:
   
  - Board definition / board setup = purely hardware mapping
  - Which pins exist on the board → GPIO, ADC, PWM
  - Which timers exist → Timer1–Timer4, base addresses for each timer
  - Register addresses → which register controls GPIO, PWM, ADC
  - Upload and flashing settings → which serial port and memory addresses to use for this MCU
  - CPU, memory, flash size, and bootloader ... – fundamental hardware features


**Framework**:  
  The framework (e.g., Arduino) provides a **software layer** that allows you to use high-level functions like `digitalWrite`, `analogRead`, `Serial.print`, without manually configuring hardware registers.  
  It abstracts low-level hardware details and provides libraries for sensors, displays, communication, and more.

**Folder Structure**
- **.pio/**: PlatformIO internal build folder (compiled binaries, temporary files) 
- **.vscode/**: VS Code project settings and debug configurations  
- **include/**: 
    - Header files (`.h`) with declarations
    - Implementation (`.cpp`) in `src/`
    - scope → Only for this project
    - Usage → `#include "Mensch.h"`
    - Reusability → To use in another project, you must manually copy the files 

- **lib/**:
    - Folder for self-contained, reusable libraries
    - Each library in its own subfolder, e.g.:  
        ```
        lib/Mensch/
            Mensch.h
            Mensch.cpp
        ```
    - scope → Project-local, automatically recognized by PlatformIO
    - Usage → `#include <Mensch.h>`
    - Reusability → Copy the library folder into another project, or use a global PlatformIO library path
- **src/**: main project code, including `main.cpp`  
- **test/**: 
    - `.cpp` files here can be used to test individual functions, classes, or modules  
    - Allows you to check functionality independently from the main project code
- **.gitignore** → files/folders ignored by Git (e.g., `.pio/`, `.vscode/`)
- **platformio.ini** → project configuration: board, framework, build options, upload settings 



