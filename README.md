# This repository implements the use of Quantum Tomography to particle collider data 
Code based on the work enttiled "Quantum tomography for collider physics: Illustrations with lepton pair production"
By J. C. Martens, J.P. Ralston and J.D. Tapia Takaki
Published by Eur.Phys.J.C 78 (2018) 1, 5 
https://doi.org/10.1140/epjc/s10052-017-5455-8


## Angle Determination Module Part 
This submodule take data for two particles in the format of X1,Y1,Z1,E1 and X2,Y2,Z2,E2 and calculates Cosine theta and Phi.
---

### 📦 Requirements
#### 🧰 Compiler
- **C++17 or newer**
  - Required features: `<string_view>`, structured bindings, etc.
  - Tested with:
    - Microsoft Visual Studio **2022 (MSVC v19.44+)**
    - GCC **9.0+**
    - Clang **10.0+**

#### ⚛️ ROOT Framework
- **ROOT ≥ 6.26**
  - Tested with **ROOT 6.30/06** (64-bit build for Windows)
  - Must include the following libraries:
    ```
    Core.lib Hist.lib Graf.lib Gpad.lib Graf3d.lib RIO.lib Matrix.lib Imt.lib
    ```

---

#### ⚙️ File Structure
AngleCalc.h:  Header File for calculating the angles  
main.cpp:  Main file of the project  
randomEventGenerator.cpp:  Random Data Generator  
anglePlotter.cpp:  Angle plotter before and after  

---

#### ▶️ Instructions to Run 
Based on the main configuration, it produces different outputs,
- Angles Theta and Phi
- Graph of the distribution of the angles if data is provided in the CSV format
