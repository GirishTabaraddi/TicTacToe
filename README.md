# 🎮 C++ Tic-Tac-Toe Engine (Console & WebAssembly)

![Language](https://img.shields.io/badge/language-C++17-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20|%20WebAssembly-lightgrey.svg)
![Build](https://img.shields.io/badge/build-CMake%20|%20Emscripten-green.svg)

A robust, object-oriented implementation of the classic Tic-Tac-Toe game. This project demonstrates advanced C++ concepts (Polymorphism, MVC pattern) and features a fully functional port to WebAssembly, allowing the C++ engine to run directly in the browser.

---

## ✨ Features

* **Dynamic Boards:** Support for 3x3, 4x4, and 5x5 grids.
* **Game Modes:**
    * 👤 vs 👤 (Human vs Human)
    * 👤 vs 🤖 (Human vs Computer)
    * 🤖 vs 🤖 (Computer vs Computer simulation)
* **Smart Computer:** Minimax algorithm for 3x3 (unbeatable) and srand(time) for larger grids.
* **Cross-Platform:** Runs as a native Console App or a Web App.

---

## 🚀 Quick Start: Web Version (Recommended)

You can run the game in your browser without installing a C++ compiler.

**Prerequisites:** [Python 3.x](https://www.python.org/) (for the local server).

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/yourusername/TicTacToe.git](https://github.com/yourusername/TicTacToe.git)
    cd TicTacToe
    ```
2.  **Run the Launcher:**
    Double-click **`run_web_app.bat`** in the root folder.

**What happens?**
1.  The script activates the embedded Emscripten SDK (`emsdk`).
2.  It compiles the C++ code to WebAssembly (`game.wasm`).
3.  It starts a local Python server.
4.  It opens your default browser to the game interface.

---

## 💻 Quick Start: Console Version

To build the standard command-line version:

**Prerequisites:** Eclipse IDE

1.  Open Eclipse and choose File -> Import
2.  General -> Existing Projects into Workspace.
3.  Browse the file
4.  Click Finish

---

## 📂 Repository Structure

```text
Root/
├── emsdk/                  # Emscripten Toolchain (Web Compiler)
├── run_web_app.bat         # One-click script to build & run Web version
├── README.md               # This file
└── TicTacToe/              # Main Project Folder
    ├── DESIGN.md           # 📘 UML Diagrams, OOA/OOD, and Answers
    ├── UML/                # Diagram images
    └── myCode/             # C++ Source Code & HTML Frontend
        ├── CGame.cpp       # Game Controller
        ├── CBoard.cpp      # Model
        ├── CDisplay.cpp    # Display
        ├── WasmEntry.cpp   # WebAssembly Adapter
        └── index.html      # Web GUI
````

-----

## 📘 Design & Architecture

This project was built with a strong focus on Object-Oriented Analysis and Design (OOAD).
For detailed documentation regarding:

  * UML Class Diagrams
  * Static vs Dynamic Polymorphism
  * Algorithms (Minimax/Activity Diagrams)
  * Assignment Questions (Class Relations, Reuse)

👉 **[Click here to read the detailed DESIGN.md](https://www.google.com/search?q=TicTacToe/DESIGN.md)**

-----

## 🛠️ Technical Architecture (Web Port)

The web build uses a specific bridge to connect C++ to JavaScript:

  * **`WasmEntry.cpp`**: Contains the `WasmGameAdapter` class. It bridges the event-driven browser model (clicks) to the stateful C++ engine.
  * **Emscripten Bindings**: Exposes C++ methods (`clickCell`, `getBoardState`) directly to the JS Runtime.

### Manual Web Build Command

If you prefer not to use the batch file:

```bash
cd TicTacToe/myCode
emcc -O3 --bind -o game.js WasmEntry.cpp CGame.cpp CBoard.cpp CPlayer.cpp CHuman.cpp CComputer.cpp CDisplay.cpp -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1
python -m http.server 8000
```
