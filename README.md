# 🎮 Mini Games Console

A comprehensive C++ console-based gaming application featuring three classic games with a unified score management system. This project demonstrates Object-Oriented Programming (OOP) principles and implements the **Minimax Algorithm** for AI-powered gameplay.

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Games Included](#-games-included)
- [How to Run](#-how-to-run)
- [Game Instructions](#-game-instructions)
- [Technical Implementation](#-technical-implementation)
  - [Object-Oriented Programming (OOP)](#object-oriented-programming-oop)
  - [Minimax Algorithm](#minimax-algorithm)
- [Code Structure](#-code-structure)
- [Screenshots](#-screenshots)
- [Future Improvements](#-future-improvements)

---

## 🎯 Overview

This project is a **Mini Games Console** application built entirely in C++. It provides an interactive menu-driven interface where users can play three different games, track their high scores, and compete against either another player or an AI opponent.

The application showcases:
- Clean Object-Oriented Design
- AI implementation using the Minimax Algorithm
- Persistent score tracking across game sessions
- Multiple difficulty levels with score multipliers

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🎲 **Multiple Games** | Three classic games in one application |
| 🤖 **AI Opponent** | Play against computer with varying difficulty |
| 📊 **Score System** | Track wins, games played, and cumulative scores |
| 🏆 **Leaderboard** | View high scores for each game |
| ⚙️ **Difficulty Levels** | Multiple difficulty settings with score multipliers |
| 🎨 **Clean UI** | Well-formatted console interface |

---

## 🎮 Games Included

### 1. 🪨📄✂️ Rock Paper Scissors
Classic hand game against the computer with customizable win targets.

- **Win Targets**: First to 3, 5, or 10 wins
- **Scoring**: 20 points per round won

### 2. ⭕❌ Tic-Tac-Toe
The timeless 3x3 grid game with both PvP and PvE modes.

- **Modes**: Player vs Player, Player vs Computer
- **AI Difficulty**: Easy (Random) or Hard (Minimax AI)
- **Scoring**: 100 base points × difficulty multiplier

### 3. 🔢 Number Guessing Game
Guess the secret number within limited attempts.

- **Difficulty Levels**:
  | Level | Range | Attempts | Multiplier |
  |-------|-------|----------|------------|
  | Easy | 1-50 | 10 | 1x |
  | Medium | 1-100 | 10 | 2x |
  | Hard | 1-200 | 5 | 3x |
  | Expert | 1-500 | 10 | 5x |

---

## 🚀 How to Run

### Prerequisites
- Windows Operating System
- C++ Compiler (g++, MSVC, or similar)
- C++11 or higher

### Compilation

Using **g++**:
```bash
g++ -o MiniGames main.cpp -std=c++11
```

Using **MSVC** (Visual Studio Developer Command Prompt):
```bash
cl /EHsc main.cpp /Fe:MiniGames.exe
```

### Execution
```bash
./MiniGames.exe
```

---

## 📖 Game Instructions

### Main Menu Navigation
```
  +----------------------------------+
  |     SELECT A GAME TO PLAY        |
  +----------------------------------+
  | 1. Rock-Paper-Scissors           |
  | 2. Tic-Tac-Toe                   |
  | 3. Number Guessing               |
  +----------------------------------+
  |     OTHER OPTIONS                |
  +----------------------------------+
  | 4. View High Scores              |
  | 5. Reset High Scores             |
  | 6. Exit                          |
  +----------------------------------+
```

### Tic-Tac-Toe Board Layout
```
  1  |  2  |  3
-----|-----|-----
  4  |  5  |  6
-----|-----|-----
  7  |  8  |  9
```
Enter a number (1-9) to place your mark on the corresponding cell.

---

## 🔧 Technical Implementation

### Object-Oriented Programming (OOP)

This project demonstrates several key OOP concepts:

#### 1. **Encapsulation**
Each class encapsulates its data and provides controlled access through public methods.

```cpp
class TicTacToe {
private:
    char board[9];           // Hidden internal state
    string player1Name;
    bool vsComputer;
    int difficulty;
    
    void initialBoard();     // Private helper methods
    bool checkWin(char mark) const;
    
public:
    void play(ScoreManager &scoreManager);  // Public interface
};
```

**Benefits:**
- Internal implementation details are hidden
- Data integrity is maintained
- Changes to internal structure don't affect external code

#### 2. **Abstraction**
Complex operations are abstracted into simple method calls.

```cpp
// Complex AI logic is abstracted behind a simple interface
int getComputerMove();  // Returns the best move - complexity hidden

// Score management abstracted
scoreManager.saveScore("TicTacToe", playerName, score, wins);
```

#### 3. **Classes and Objects**

| Class | Responsibility |
|-------|----------------|
| `ScoreManager` | Manages all game scores, rankings, and persistence |
| `TicTacToe` | Handles Tic-Tac-Toe game logic and AI |
| `NumberGuessing` | Manages number guessing game mechanics |
| `RockPaperScissors` | Controls RPS game flow and scoring |
| `PlayerScore` (struct) | Data structure for player statistics |

#### 4. **Composition**
The main program composes game objects and a score manager:

```cpp
int main() {
    ScoreManager scoreManager;      // Score management component
    RockPaperScissors rpsGame;      // Game components
    TicTacToe tttGame;
    NumberGuessing ngGame;
    
    // Games use scoreManager through composition
    tttGame.play(scoreManager);
}
```

#### 5. **Const Correctness**
Methods that don't modify state are marked `const`:

```cpp
void displayBoard() const;
bool checkWin(char mark) const;
bool isBoardFull() const;
void displayScores(const string &title, const vector<PlayerScore> &scores) const;
```

---

### Minimax Algorithm

The **Minimax Algorithm** is a decision-making algorithm used in game theory for two-player zero-sum games. In this project, it powers the "Hard" difficulty AI in Tic-Tac-Toe.

#### How Minimax Works

```
                    Current Board State
                           |
            +--------------+--------------+
            |              |              |
         Move A         Move B         Move C
            |              |              |
         Player          Player        Player
        Responds        Responds      Responds
            |              |              |
           ...            ...            ...
            |              |              |
      Final Score    Final Score   Final Score
```

#### Algorithm Explanation

1. **Recursive Tree Search**: The algorithm explores all possible future game states
2. **Maximizing Player (AI/O)**: Tries to maximize the score
3. **Minimizing Player (Human/X)**: Tries to minimize the score
4. **Base Cases**: Win, Loss, or Draw

#### Code Implementation

```cpp
int minimax(bool isMaximizing, int depth) {
    // BASE CASES - Terminal states
    if (checkWin('O')) return 10 - depth;   // AI wins (prefer faster wins)
    if (checkWin('X')) return depth - 10;   // Human wins (prefer slower losses)
    if (isBoardFull()) return 0;            // Draw
    
    if (isMaximizing) {
        // AI's turn - maximize score
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';                          // Try move
                int score = minimax(false, depth + 1);   // Recurse
                board[i] = ' ';                          // Undo move
                bestScore = max(bestScore, score);       // Keep best
            }
        }
        return bestScore;
    } else {
        // Human's turn - minimize score
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';                          // Try move
                int score = minimax(true, depth + 1);    // Recurse
                board[i] = ' ';                          // Undo move
                bestScore = min(bestScore, score);       // Keep worst for AI
            }
        }
        return bestScore;
    }
}
```

#### Depth Consideration

The `depth` parameter serves two purposes:
1. **Prefer Faster Wins**: `10 - depth` means winning sooner gives higher score
2. **Delay Losses**: `depth - 10` means losing later is better than losing sooner

#### Visual Example

```
Initial State:          After Minimax Analysis:
                        
  X | O | X             AI evaluates all possibilities
----|---|----           and determines the optimal move
  O |   |               that guarantees a win or draw
----|---|----           
    |   |               Best Move: Position 5 (center-right)
```

#### Time Complexity
- **Worst Case**: O(b^d) where b = branching factor, d = depth
- **For Tic-Tac-Toe**: Maximum ~9! = 362,880 states (but pruning reduces this significantly)

---

## 📁 Code Structure

```
mini-games-console/
│
├── main.cpp                 # Complete source code
│
├── Components:
│   ├── PlayerScore (struct) # Player data structure
│   ├── ScoreManager (class) # Score tracking & display
│   ├── TicTacToe (class)    # TTT game with Minimax AI
│   ├── NumberGuessing (class)# Number guessing game
│   └── RockPaperScissors (class) # RPS game
│
└── README.md                # This file
```

### Class Diagram

```
┌──────────────────────┐
│    ScoreManager      │
├──────────────────────┤
│ - tttScores          │
│ - ngScores           │
│ - rpsScores          │
├──────────────────────┤
│ + saveScore()        │
│ + displayScores()    │
│ + showAllHighScores()│
│ + resetAllScores()   │
└──────────────────────┘
         ▲
         │ uses
         │
┌────────┴────────────────────────────┐
│                                      │
▼                ▼                     ▼
┌──────────────┐ ┌──────────────┐ ┌──────────────┐
│  TicTacToe   │ │NumberGuessing│ │    RPS       │
├──────────────┤ ├──────────────┤ ├──────────────┤
│ - board[9]   │ │-secretNumber │ │-playerScore  │
│ - players    │ │-maxAttempts  │ │-computerScore│
│ - difficulty │ │-difficulty   │ │              │
├──────────────┤ ├──────────────┤ ├──────────────┤
│ + play()     │ │ + play()     │ │ + play()     │
│ - minimax()  │ │-generateNum()│ │-determineWin│
│ - checkWin() │ │              │ │              │
└──────────────┘ └──────────────┘ └──────────────┘
```

---

## 📸 Screenshots

### Main Menu
```
  +----------------------------------+
  |     SELECT A GAME TO PLAY        |
  +----------------------------------+
  | 1. Rock-Paper-Scissors           |
  | 2. Tic-Tac-Toe                   |
  | 3. Number Guessing               |
  +----------------------------------+
```

### Tic-Tac-Toe Gameplay
```
==================================================
              TIC TAC TOE
==================================================

Player1 (X)  vs  Computer (O)

  X  |  O  |  3
-----|-----|-----
  4  |  X  |  6
-----|-----|-----
  7  |  8  |  O

Player1's turn. Enter your move (1-9): 
```

### High Scores
```
============================================================
                    HIGH SCORES
============================================================

--- TIC-TAC-TOE GAME ---
Rank  Player              Score     Games     Wins
--------------------------------------------------------
1     Alice               300       3         3
2     Bob                 150       2         1
```

---

## 🔮 Future Improvements

- [ ] Add file persistence for scores (save/load from disk)
- [ ] Implement Alpha-Beta pruning for faster Minimax
- [ ] Add more games (Hangman, Connect Four, etc.)
- [ ] Cross-platform support (Linux/macOS)
- [ ] Implement undo/redo functionality
- [ ] Add game statistics and analytics
- [ ] Network multiplayer support
