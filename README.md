# RPG Console: The Savior of Princess

> A text-based RPG adventure built in C++ with turn-based combat, puzzle rooms, a simple shop system, inventory management, and a level progression flow.

---

## ✨ Overview

**RPG Console** is a console-based role-playing game where you play as a brave adventurer sent to rescue Princess Elara from the dark sorcerer Malvador. The game blends:

- **Combat rooms** with turn-based enemy battles
- **Puzzle rooms** with riddle-based wisdom challenges
- **A shop system** for buying useful items
- **Inventory tracking** to manage collected items
- **Lives, health, coins, and wisdom** as core player stats

The game is designed as a single-player journey through 10 levels, alternating between combat and puzzle challenges, ending in a final boss room.

---

## 🎮 Game Features

| Feature | Description |
|---|---|
| **Level progression** | 10 structured levels linked in sequence using a doubly linked list |
| **Combat system** | Fight enemies with attack/defend choices |
| **Puzzle system** | Answer riddles correctly to increase wisdom |
| **Shop** | Buy a **First Aid Kit** or **Sword** using coins |
| **Inventory** | Store purchased items in a 10-slot inventory |
| **Player stats** | Health, wisdom, coins, lives, and attack power |
| **Replay option** | Restart the adventure after finishing or losing |

---

## 🕹️ Gameplay Loop

1. Enter your character name.
2. Progress through a story-driven sequence of levels.
3. Complete each level by either:
   - defeating an enemy in combat, or
   - answering a puzzle question correctly.
4. Use the shop when available to restore health or increase attack power.
5. Reach the final level, defeat the final enemy, and rescue the princess.

---

## ⚔️ Controls

| Action | Input |
|---|---|
| Attack | `A` |
| Defend | `D` |
| Move to next level | `M` |
| Move to previous level | `B` |
| Open shop | `S` |
| View inventory | `I` |
| Yes / No prompts | `Y` / `N` |

---

## 📦 Player Stats

The game tracks the following attributes:

- **Health** — decreases in combat or after wrong answers
- **Wisdom** — increases after correct puzzle answers
- **Coins** — earned from victory and spent in the shop
- **Lives** — limited retries before game over
- **Attack Power** — boosted by buying the sword

---

## 🧩 Level Design

The adventure contains **10 levels**:

- **9 regular stages** alternating between combat and puzzle rooms
- **1 final boss room** at the end

This creates a simple but satisfying rhythm of:

**fight → think → upgrade → advance**

---

## 🛒 Shop Items

| Item | Cost | Effect |
|---|---:|---|
| **FIRST AID KIT** | 10 coins | Restores health to full |
| **SWORD** | 20 coins | Increases attack power |

Purchased items are also added to the player inventory.

---

## 🧠 Puzzle System

The puzzle rooms use a pool of riddles such as:

- “What has keys but can’t open locks?”
- “What is always in front of you but can’t be seen?”
- “What belongs to you but other people use more than you do?”

Correct answers increase wisdom. Wrong answers reduce health and wisdom.

---

## 🧰 Tech Stack

- **Language:** C++
- **Standard Library:** `<iostream>`, `<string>`, `<vector>`, `<set>`, `<algorithm>`, `<cstdlib>`, `<ctime>`
- **Game Structure:** console I/O, linked-list level progression, random question selection

---

## 🚀 How to Run

### Option 1: Using g++

```bash
g++ rpg_console.cpp -o rpg_console
./rpg_console
```

### Option 2: Using a C++ IDE

1. Open `rpg_console.cpp`
2. Build the project
3. Run the generated executable

> If you are on Windows, the executable may be `rpg_console.exe`.

---

## 📁 Project Files

| File | Purpose |
|---|---|
| `rpg_console.cpp` | Main game source code |
| `rpg_console.exe` | Compiled Windows executable |
| `question answer.txt` | Riddle/answer reference list |
| `class diagram.drawio.png` | Class diagram reference |
| `activity diagram.drawio (1).png` | Activity flow reference |

---

## 🧱 How It Works

The game is organized around a `LevelProgression` class that manages:

- player state
- levels
- combat
- puzzle logic
- shop purchases
- inventory

Each level is represented as a node in a doubly linked list, which allows forward and backward movement through the adventure.

---

## 🎯 Goal

Defeat the final enemy, clear all levels, and rescue Princess Elara.

---

## 🔮 Possible Improvements

- Add more enemy types and boss phases
- Expand the inventory and item effects
- Add save/load support
- Improve combat balance
- Introduce multiple endings
- Add colorized console output for a more immersive experience

---

## 👤 Author

Created as a console-based RPG project focused on simple data structures and gameplay logic.

