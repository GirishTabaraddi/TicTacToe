# TicTacToe

**Learning focus:**

Class Design, Class Diagrams, Activity Diagrams, Code Reuse, Static and Dynamic Polymorphism.

The task is to develop an object oriented version of the game TicTacToe.

## 1 Class Relations

### 1.1 Requirements

The task is to develop a console based version of the board game TicTacToe

- The game consists of a 3x3/4x4/5x5 board.
- On every position, the players place a “x” (player 1) or a “o” (Player 2) stone.
- The first player, who has 3 stones in a row (horizontally, vertically or diagonally) wins the game.

Technical requirements

- Player 1 and 2 can either be human or computer, i.e.

    1. Human against Computer
    2. Human against human
    3. Computer against human
    4. Computer against computer are possible combinations.
    
- The computer may never loose.
- The board will be displayed as a console application.
- Displaying the screen later on in a graphical format shall be easily supported.
- Provide DoxyGen Style comments for all entities and create a website for your project.

### 1.2 OO Analysis

From the requirements, identify the mentioned objects and describe them using the concept of OOA (object oriented analysis)

| Object    | Properties | Capabilities |
|:---------:|:----------:|:------------:|
| CGame     | has one board (Composition), has two players (Composition), knows CDisplay (Association) | It controls the game, runs the loop for the game. Gets coordinates from CPlayer -> validate pos -> update board -> if error, inform CDisplay |
| CBoard    | creates 3x3 board | checks the coordinates, checks for winner |
| CDisplay  | needs reference of the board | prints the board, prints ErrorCode |
| CPlayer   | uses CBoard | selectCoordinate |
| CHuman    | inherits CPlayer | getInput(), placesStone |
| CComputer | inherits CPlayer | calcValidPos(), placesStone |
| CErrorStatus | helper class  | Enum with error codes required |

### 1.3 OO Design

Create a first rough class design based on the results of the object oriented analysis. Methods and attributes can be ommitted.

![UML Diagram](TicTacToe/UML/UML.jpg)

### 1.4 Reuse

Check the implementation of the Reversi Boardgrame and describe which classes can be reused. Provide a class diagram for every class you reuse and describe if changes are required.

![Reversi UML Diagram](TicTacToe/UML/reversi_uml.jpg)

| Class    | Required Modifications |
|:---------:|:----------:|
| ReversiBoard    | QueryFieldState() can be reused |  
| ReversiConsoleView    | printBoard() can be reused |


### 1.5 Static Polymorphism

Draw a class diagram for a possible implementation of the TicTacToe boardgame using static polymorphism for the Screen and Player partition.

<to be drawn later>

### 1.6 Dynamic Polymorphism

The disadvantage of the static design is the missing flexibility of choosing computer / human players. Use dynamic polymorphism for both the screen and the players to support a code structure like the one below. Note, that inside the loop, we do not care if the player is a human or a computer, nor, what type of screen we have connected.

```
void CTicTacToe::play()
{
    selectPlayer(0);
    selectPlayer(1);
    for (unsigned short i = 0; i < 9; i++)
    {
        cout << "Placing a stone in round " << i+1 << endl;
        bool finished = m_player[i%2]->placeStone();
        m_screen->print();
        if (finished)
        {
            cout << "We have a winner!!!" << endl;
            return; //hacky break
        }
    }
    cout << "Draw...." << endl;
}
```

Draw the corresponding class diagram.

<to be drawn later>


## 2 Algorithms and Design Decisions

### 2.1 Activity Diagram

Draw an activity diagram describing the top level placeStone-Strategy for the computer player.

![UML Diagram](TicTacToe/UML/ActivityDiagram_ComputerAlgorithm.png)

### 2.2 Spooky Hierarchy

After spending a frustratingly large number of hours for creating the first design, you decide to hack the notebook from Nelly, the Nerd to check for his solution. You find the following design snippet:

![UML Diagram](TicTacToe/UML/nellynerd_UML.png)


#### Friend Class

A **Friend Class** is a class that is granted special access to the **private** and **protected** members of another class. Under normal object-oriented rules, private data is hidden from outside classes. However, if Class A declares Class B as a `friend`, Class B can access Class A's private variables and functions.

**Key Characteristics:**
* **Not Symmetric:** If A is a friend of B, B is not automatically a friend of A.
* **Not Transitive:** If A is a friend of B, and B is a friend of C, A is *not* automatically a friend of C.
* **Not Inherited:** Friendships are not passed down to derived classes.

**Syntax:**

```
class CStorage {
private:
    int m_secretData = 42;

    // CStorage gives permission to CDisplay
    friend class CDisplay; 
};

class CDisplay {
public:
    void printSecret(const CStorage& storage) {
        // This works only because CDisplay is a friend!
        std::cout << storage.m_secretData << std::endl; 
    }
};
```

#### Static Attribute (Static Data Member)

A **Static Attribute** is a variable that belongs to the **class itself**, rather than to any specific object (instance) of that class. No matter how many objects of the class you create, there is only **one copy** of the static variable in memory. All objects share this single variable.

**Key Rules:**
  * **Shared Memory:** Changing the value in one object changes it for all objects.
  * **Initialization:** Static members must be defined and initialized **outside** the class definition (usually in the `.cpp` file) to allocate memory.
  * **Lifetime:** It exists for the entire duration of the program, initialized before `main()` runs.

**Syntax:**

```
#include <iostream>

class Counter {
public:
    // Declaration inside the class
    static int objectCount; 

    Counter() {
        objectCount++; // Increment shared counter every time an object is born
    }
};

// Definition and Initialization OUTSIDE the class (Critical Step)
int Counter::objectCount = 0;

int main() {
    Counter c1;
    Counter c2;
    Counter c3;

    // Accessed via Class Name (preferred) or Object
    std::cout << "Total objects created: " << Counter::objectCount << std::endl; 
    // Output: Total objects created: 3
    return 0;
}
```

#### Static Method

A **Static Method** is a function that belongs to the class rather than an instance. It can be called without creating an object of the class.

**Key Rules:**
  * **No `this` Pointer:** Since it is not attached to an object, it does not have a `this` pointer.
  * **Limited Access:** A static method can **only** access **Static Attributes** or call other **Static Methods**. It cannot access non-static (regular) member variables because it doesn't know which object's data to look at.
  * **Invocation:** Called using the scope resolution operator `ClassName::MethodName()`.

**Syntax:**

```
#include <iostream>

class MathUtils {
public:
    static int add(int a, int b) {
        return a + b;
    }

    // This method cannot access non-static variables!
};

int main() {
    // No need to create 'MathUtils m;' 
    // We call the function directly on the class.
    int result = MathUtils::add(10, 5);
    
    std::cout << "Result: " << result << std::endl; // Output: Result: 15
    return 0;
}
```
#### Throwing and Catching Exceptions

Exception handling provides a way to transfer control from one part of a program to another when an error or "exceptional" situation occurs. It separates error-handling code from normal program logic.

**Keywords:**
  * **`try`**: A block of code where exceptions might occur.
  * **`throw`**: Used to signal that an error has occurred. You can throw integers, strings, or objects (like `std::exception`).
  * **`catch`**: A block of code that handles the specific exception thrown.

**Key Rules:**
  * **Stack Unwinding:** When an exception is thrown, the program leaves the current scope immediately. Local objects are destroyed (destructors are called) as the program looks for a `catch` block.
  * **Handlers:** You can have multiple `catch` blocks for different types of errors. `catch(...)` catches anything.

**Syntax:**

```
#include <iostream>
#include <stdexcept> // Standard exceptions

double divide(double numerator, double denominator) {
    if (denominator == 0) {
        // Signal an error
        throw std::invalid_argument("Error: Division by zero is not allowed.");
    }
    return numerator / denominator;
}

int main() {
    try {
        // Attempt risky code
        double result = divide(10.0, 0.0);
        std::cout << "Result: " << result << std::endl;
    } 
    catch (const std::invalid_argument& e) {
        // Handle the specific error caught
        std::cerr << "Caught Exception: " << e.what() << std::endl;
    }
    catch (...) {
        // Handle any other unknown error
        std::cerr << "Caught unknown error." << std::endl;
    }

    std::cout << "Program continues..." << std::endl;
    return 0;
}
```

Using these concepts, describe how you can implement the following feature:

    - A CPosition object describes a specific position on the boardgame.
    - The CPosition Object knows the size of the board (number of rows and columns).
    - The size attribute may only be set by the CBoard class, while the board is being constructed.
    - If a CPosition object is constructed, whose value is out of the range of the board, the user will be informed so that he can initiate a proper error handling.

## 3 Implementation and Test

### 3.1 Final UML Design of the Game

![UML Diagram](TicTacToe/UML/Final_UML.jpg)

### 3.2 Output of the game

```
TicTacToe started.

Choose the Game Type from below options: 
1. Human vs Human
2. Human vs Computer
3. Computer vs Computer
3
Enter TicTacToe Board Size (3, 4, or 5): 3

----------- Game Configuration -----------

Type: Computer vs Computer

Grid: 3x3

Player-0: Computer (o)

Player-1: Computer (x)
---------------------------------------

. . . 
. . . 
. . . 

Player-1 x (Computer) turn:

x . . 
. . . 
. . . 

Player-0 o (Computer) turn:

x . . 
. o . 
. . . 

Player-1 x (Computer) turn:

x x . 
. o . 
. . . 

Player-0 o (Computer) turn:

x x o 
. o . 
. . . 

Player-1 x (Computer) turn:

x x o 
. o . 
x . . 

Player-0 o (Computer) turn:

x x o 
o o . 
x . . 

Player-1 x (Computer) turn:

x x o 
o o x 
x . . 

Player-0 o (Computer) turn:

x x o 
o o x 
x o . 

Player-1 x (Computer) turn:

x x o 
o o x 
x o x 

Unfortunately it is a draw!!!

Game Ended!!!
```

## 4 Tic-Tac-Toe WebAssembly (Wasm) Port

This project module allows the C++ Tic-Tac-Toe engine to run directly in a web browser using WebAssembly. It utilizes **Emscripten** to compile the C++ logic into a `.wasm` binary that interacts with JavaScript via a frontend HTML interface.

### 4.1 Repository Structure

The web build relies on specific file locations. Based on this repository setup:

* **`TicTacToe/myCode/`**: Contains the C++ source code, the HTML frontend, and the build script.
    * `WasmEntry.cpp`: The bridge between C++ and JavaScript.
    * `index.html`: The graphical user interface.
    * `run_web.bat`: Automation script to build and serve the app.
* **`emsdk/`**: The Emscripten SDK toolchain (located parallel to the `TicTacToe` folder).

### 4.2 Prerequisites

Before running the web version, ensure you have:

1.  **Python 3.x**: Required to run the local web server.
    * Verify by running: `python --version`
2.  **Web Browser**: Chrome, Edge, Firefox, or Safari (Wasm is supported in all modern browsers).
3.  **Windows OS**: The provided automation script (`run_web.bat`) is written for Windows.

---

### 4.3 How to Run (Quick Start)

There is a "One-Click" batch script that handles environment activation, compilation, and server hosting.

1.  Run the web launcher script:
    ```cmd
    run_web.bat
    ```

### 4.4 What the script does:
1.  **Activates EMSDK**: It looks for the `emsdk` folder in the repo root and activates the compiler environment variables for the current session.
2.  **Compiles**: It runs the `emcc` compiler to generate `game.js` and `game.wasm`.
3.  **Launches Browser**: It opens `http://localhost:8000/index.html`.
4.  **Starts Server**: It spins up a Python HTTP server to host the files.

> **Note:** Do not close the terminal window while playing. Closing it will stop the local web server.

---

### 4.5 Manual Build Instructions

If you prefer to compile manually or are debugging the build process, follow these steps:

#### 1. Activate Emscripten
From the repo root, run the environment script:
```cmd
..\emsdk\emsdk_env.bat
````

#### 2. Compile Command

Run this command from inside the `TicTacToe\myCode` folder:

```bash
emcc -O3 --bind -o game.js ^
    WasmEntry.cpp CGame.cpp CBoard.cpp CPlayer.cpp CHuman.cpp CComputer.cpp CDisplay.cpp ^
    -s ALLOW_MEMORY_GROWTH=1 ^
    -s NO_EXIT_RUNTIME=1
```

  * `-O3`: Maximizes optimization for speed.
  * `--bind`: Enables **Embind**, allowing C++ classes (`WasmGameAdapter`) to be called from JavaScript.
  * `-s NO_EXIT_RUNTIME=1`: Ensures the C++ memory stays alive after initialization so the buttons continue to work.

#### 3. Serve

Start a local server in the directory:

```bash
python -m http.server 8000
```

-----

### 4.6 How to Use the Web App

1.  **Configuration**:
      * Select **Grid Size** (3x3, 4x4, or 5x5).
      * Select **Game Mode** (Human vs Human, Human vs Computer, or Computer vs Computer).
2.  **Start**: Click the **"Start New Game"** button.
3.  **Gameplay**:
      * **HvC**: Click a cell to make your move. The AI will respond instantly (Minimax for 3x3, Random for larger grids).
      * **CvC**: The game will enter an automatic loop where the AI plays against itself every second.
4.  **Reset**: Click **"Clear Game"** to stop the current match and change settings.

-----

### 4.7 Technical Architecture

#### WasmEntry.cpp

Since the browser is event-driven (waiting for user clicks), we cannot use the standard `cin`/`while` loop found in `main.cpp`.

The created wrapper class **`WasmGameAdapter`** bridges the gap:

  * **Persistence**: It holds a pointer to `CGame` on the heap, keeping the game state alive between browser clicks.
  * **Methods**:
      * `clickCell(row, col)`: Handles input, updates the board, checks for wins, and triggers the AI turn.
      * `computerStep()`: Exposed specifically for the CvC loop logic.
      * `getBoardState()`: Returns a string representation of the grid (e.g., `"x..o.x..."`) for efficient UI rendering.

<!-- end list -->

```
