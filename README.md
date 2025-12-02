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
