# Angle Determination Module Part 
This submodule consumes data pair in the format of  X1,Y1,Z1,E1 and X2,Y2,Z2,E2 and calculates Cosine theta and Phi.
---

### 📦 Requirements
### 🧰 Compiler
- **C++17 or newer**
  - Required features: `<string_view>`, structured bindings, etc.
  - Tested with:
    - Microsoft Visual Studio **2022 (MSVC v19.44+)**
    - GCC **9.0+**
    - Clang **10.0+**

### ⚛️ ROOT Framework
- **ROOT ≥ 6.26**
  - Tested with **ROOT 6.30/06** (64-bit build for Windows)
  - Must include the following libraries:
    ```
    Core.lib Hist.lib Graf.lib Gpad.lib Graf3d.lib RIO.lib Matrix.lib Imt.lib
    ```

---

## ⚙️ File Structure
AngleCalc.h:  Header File for calculating the angles  
main.cpp:  Main file of the project  
randomEventGenerator.cpp:  Random Data Generator  
anglePlotter.cpp:  Angle plotter before and after  

---

## ▶️ Instructions to Run 
Compile the project and run main.cpp
---
## 📊 Outputs
This project automatically generates the following files:
- events.csv  
- phi1_list.csv  
- phi2_list.csv  
- updated_phi_list.csv  
- updated_theta_list.csv  
- cosTheta_comparison_hist.png  
- phi_comparison_hist.png
