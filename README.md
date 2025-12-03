# **Pong SFML – Modern C++ Arcade Remaster**

A clean, modern re-implementation of the classic Pong game built using **C++** and **SFML**, featuring:

* Player vs AI mode with **lives + high-score saving**
* Player vs Player mode (two-player keyboard control)
* Fully modular OOP architecture
* Clean UI with a dedicated menu system
* Fully documented academic + industrial style source code

---

## 🎮 **Game Modes**

### **1. Player vs AI**

* You start with **3 lives**
* Your score increases the longer you survive
* High score is saved to `highscore.txt`
* The AI tracks the ball with a mild delay for fair gameplay

### **2. Player vs Player**

* Local multiplayer
* Left paddle: `W` and `S`
* Right paddle: `Up` and `Down`
* First player to reach the winning score takes the round

---

## 🧩 **Project Structure**

```
Pong_SFML-master/
│
├── include/
│   ├── Ball.h        — Ball physics + collision
│   ├── Paddle.h      — Paddle movement + boundaries
│   ├── Game.h        — Core game loop + states
│   ├── Menu.h        — Main menu UI + interactions
│
├── src/
│   ├── Ball.cpp
│   ├── Paddle.cpp
│   ├── Game.cpp
│   ├── Menu.cpp
│   ├── main.cpp
│
├── assets/
│   └── font.ttf
│
├── highscore.txt
├── Makefile
└── README.md
```

The code follows a clear **entity-based architecture**, with every class responsible for one task (Single Responsibility Principle).

---

## ⚙️ **How to Build**

### **Linux / WSL / MacOS / MinGW**

Install SFML:

```
sudo apt install libsfml-dev
```

Build and run:

```
make
./pong
```

### **Windows (MSYS2 or MinGW)**

Install SFML from the official binaries, configure include/lib paths, then:

```
make
```

---

## 🕹️ **Controls**

### Player vs AI

* Move Left Paddle: **W / S**
* Right paddle is AI-controlled
* Press **Enter** on Game Over screen to return to menu

### Player vs Player

* Left Paddle: **W / S**
* Right Paddle: **Up / Down**
* Press **Enter** after a match ends

### Global

* **Escape** → Quit game

---

## 🎮 Features

### **1. Menu System**

* Displays the game title and high score.
* Buttons:
  * **Play vs AI**
  * **Two Players (PvP)**
* Uses bounding-box collision detection for mouse clicks.

### **2. Game Modes**

* **AI Mode:** Right paddle is controlled by an automated opponent.
* **PvP Mode:** Two human players play against each other.

### **3. Ball Physics**

* Ball moves using velocity and **delta time (`dt`)**.
* Detects wall collisions (top/bottom).
* Paddle collision detection using `getGlobalBounds().intersects()`.
* Ball resets after each score.

### **4. Paddle Mechanics**

* Player controls paddles using keyboard inputs.
* AI paddle follows ball smoothly.
* Paddles are kept within screen boundaries via clamping.

### **5. Scoring & High Score**

* Score updates when a ball crosses a player's side.
* High score persists and is shown on the menu.

---

## 🧠 Important Concepts Used

### ✔ Delta Time (`dt`)

Ensures smooth, frame-rate–independent movement.

### ✔ Collision Detection

Uses **SFML bounding boxes**.

### ✔ Game States

Switches between:

* MENU
* AI_GAME
* PVP_GAME

### ✔ SFML Render Loop

Every frame:

1. Update positions
2. Clear window
3. Draw objects
4. Display updated frame

---

---

## 📚 **High Score System**

In AI mode your highest score is saved in:

```
highscore.txt
```

It persists even after closing the game.

---

## 🧠 **Technical Features**

* Smooth physics using delta time
* State-driven system (Menu → Game → Game Over → Menu)
* Simple but effective AI tracking algorithm
* Collision detection using bounding boxes
* SFML text + shapes for UI
* Fully documented source code for learning and upskilling

---

## 🛠️ **Dependencies**

* **C++17**
* **SFML 2.5+**

---

## 🙌 **Contributing**

Contributions improving gameplay, UI, AI, readability, or documentation are welcome.
This project is excellent for learning:

* Game loops
* SFML rendering
* Physics + collision logic
* AI steering
* Modular C++ game architecture

---

## 📄 **License**

MIT License — free to use, modify, and distribute.

---
