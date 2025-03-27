# 🎮 Tetris Game (C++)

Welcome to **Tetris in C++**! Experience the nostalgic fun of arranging Tetromino blocks, clearing lines, and chasing the highest score. This console-based Tetris game is lightweight, engaging, and easy to play!

## ✨ Features

- 🧱 Classic Tetris gameplay
- 🎲 Random Tetromino generation
- 🏆 Score tracking
- ⚡ Adjustable game speed
- 💥 Collision detection
- 🚀 Smooth controls

## 🖥️ Requirements

- C++ Compiler (e.g., **GCC** or **MSVC**)
- Windows Operating System (for `conio.h` and `windows.h` support)

## 🚀 How to Compile and Run

1. Ensure a C++ compiler is installed (e.g., **GCC** or **MSVC**).

2. Download or copy `tetris.cpp` to your system.

3. Open your terminal or command prompt and navigate to the directory.

4. Compile the code:

   **For GCC:**

   ```bash
   g++ tetris.cpp -o tetris
   ```

   **For MSVC:**

   ```bash
   cl tetris.cpp
   ```

5. Run the executable:

   **For GCC:**

   ```bash
   ./tetris
   ```

   **For MSVC:**

   ```bash
   tetris.exe
   ```

6. Start the game and have fun!

## 🎮 Gameplay Instructions

- **Controls:**

  - 🔄 **W** - Rotate Tetromino
  - ⬅ **A** - Move Left
  - ➡ **D** - Move Right
  - ⬇ **S** - Drop Faster
  - ❌ **Q** - Quit the Game

- **Game Objective:**

  - Arrange falling blocks to create complete horizontal lines.
  - Each cleared line scores points.
  - The game ends when the blocks stack to the top.

## ⚙️ Customization

- **Speed Adjustment:**
  Customize the game speed by modifying the `Sleep()` function value in the `gameLoop()`.

  ```cpp
  Sleep(200); // Lower value = faster game
  ```

- **Board Size:**
  You can tweak the board dimensions using `BOARD_WIDTH` and `BOARD_HEIGHT`.

  ```cpp
  const int BOARD_WIDTH = 10;
  const int BOARD_HEIGHT = 20; // Customize as desired
  ```

## 👋 Greetings

When you start the game, a friendly welcome message will appear, followed by your current score. Compete with yourself to achieve the highest score and enjoy the thrill of classic Tetris!

## 🧑‍💻 Author

**TECH TITANS**



