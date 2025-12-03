
# SFML Pong Game

This project is a complete Pong game built using **C++** and **SFML**.  
It includes a main menu, AI mode, PvP mode, ball physics, paddle controls, collision handling, scoring, and high-score tracking.

---

## 📁 Project Structure

```
Pong_SFML-master/
│
├── src/
│   ├── Game.cpp
│   ├── Ball.cpp
│   ├── Paddle.cpp
│   ├── Menu.cpp
│   └── main.cpp
│
├── include/
│   ├── Game.h
│   ├── Ball.h
│   ├── Paddle.h
│   └── Menu.h
│
├── assets/
│   ├── font.ttf
│   └── (other assets)
│
└── CMakeLists.txt
```

---

## 🎮 Features

### **1. Menu System**

- Displays the game title and high score.
- Buttons:
  - **Play vs AI**
  - **Two Players (PvP)**
- Uses bounding-box collision detection for mouse clicks.

### **2. Game Modes**

- **AI Mode:** Right paddle is controlled by an automated opponent.
- **PvP Mode:** Two human players play against each other.

### **3. Ball Physics**

- Ball moves using velocity and **delta time (`dt`)**.
- Detects wall collisions (top/bottom).
- Paddle collision detection using `getGlobalBounds().intersects()`.
- Ball resets after each score.

### **4. Paddle Mechanics**

- Player controls paddles using keyboard inputs.
- AI paddle follows ball smoothly.
- Paddles are kept within screen boundaries via clamping.

### **5. Scoring & High Score**

- Score updates when a ball crosses a player's side.
- High score persists and is shown on the menu.

---

## 🧠 Important Concepts Used

### ✔ Delta Time (`dt`)

Ensures smooth, frame-rate–independent movement.

### ✔ Collision Detection

Uses **SFML bounding boxes**.

### ✔ Game States

Switches between:

- MENU
- AI_GAME
- PVP_GAME

### ✔ SFML Render Loop

Every frame:

1. Update positions
2. Clear window
3. Draw objects
4. Display updated frame

---

## 🛠 Requirements

- **C++17 or later**
- **SFML 2.5+**
- CMake or Visual Studio / Code::Blocks

---

## ▶ How to Build & Run (CMake)

```
mkdir build
cd build
cmake ..
make
./Pong
```

---

## 📌 Credits

Created by **Gungun Goyal and Kushagra Garg**.
