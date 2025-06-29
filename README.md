# Chess Game - Qt/C++ Edition

<a href="https://www.linkedin.com/in/jose-luis-cardenas-54366983"><img src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white" /></a> <a href="https://leetcode.com/user6694X/"><img src="https://img.shields.io/badge/-LeetCode-FFA116?style=for-the-badge&logo=LeetCode&logoColor=black" /></a> <a href="mailto:jluispcardenas@gmail.com"><img src="https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white"></a>

![Qt](https://img.shields.io/badge/Qt-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

A comprehensive chess game implementation built with Qt/C++, featuring multiple game modes including local play, AI opponent, and online multiplayer capabilities.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Game Modes](#game-modes)
- [Technical Architecture](#technical-architecture)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [AI Implementation](#ai-implementation)
- [Network Protocol](#network-protocol)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## 🎯 Overview

This project is a Qt/C++ migration and enhancement of the original [C# Chess Game](https://github.com/jluispcardenas/ChessTest). It maintains all the core functionality while leveraging Qt's cross-platform capabilities and modern C++ features.

The game implements a complete chess engine with move validation, game state management, and an intelligent AI opponent using advanced algorithms.

## ✨ Features

- **Complete Chess Implementation**: Full rule compliance including special moves (castling, en passant, promotion)
- **Intuitive GUI**: Drag-and-drop interface with visual board representation
- **Multiple Game Modes**: Local, AI, and online multiplayer support
- **Advanced AI Engine**: Alpha-beta pruning with position evaluation
- **Network Play**: TCP-based online multiplayer functionality
- **Game State Management**: Save/load capabilities and move history
- **Cross-Platform**: Runs on Windows, macOS, and Linux

## 🎮 Game Modes

### Human vs Human
- Local multiplayer on the same device
- Turn-based gameplay with visual turn indicators
- Complete move validation and game state tracking

### Human vs Computer
- Single-player mode against AI opponent
- Adjustable difficulty through AI depth configuration
- Real-time move calculation in separate thread

### Online Multiplayer
- Network-based multiplayer over TCP/IP
- Server/client architecture
- Real-time move synchronization
- Connection status monitoring

## 🏗️ Technical Architecture

### Core Components

- **MainBoard**: Primary application window and UI controller
- **Board**: Game board widget handling rendering and user interaction
- **Piece**: Individual chess piece representation with move logic
- **Computer**: AI opponent implementation using QThread
- **IA (AI Engine)**: Alpha-beta pruning algorithm with position evaluation
- **BoardEvaluator**: Chess position scoring and analysis
- **Communication**: Network layer for online play
- **Move System**: Move representation and validation

### Design Patterns

- **Model-View-Controller**: Separation of game logic, UI, and control flow
- **Observer Pattern**: Qt signals/slots for event handling
- **Strategy Pattern**: Different AI evaluation strategies
- **Thread Safety**: Concurrent AI computation without UI blocking

## 📋 Prerequisites

- **Qt Framework**: Version 5.x or 6.x
- **C++ Compiler**: GCC, Clang, or MSVC with C++11 support
- **qmake**: Qt's build system (included with Qt installation)

### Required Qt Modules
- Qt Core
- Qt GUI  
- Qt Network (for online functionality)

## 🚀 Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/jluispcardenas/Chess.git
   cd Chess
   ```

2. **Ensure Qt is installed and properly configured**:
   ```bash
   qmake --version  # Verify Qt installation
   ```

## 🔨 Building the Project

1. **Generate Makefile**:
   ```bash
   qmake Chess.pro
   ```

2. **Compile the project**:
   ```bash
   make
   ```
   
   On Windows with Visual Studio:
   ```bash
   nmake
   ```

3. **Run the executable**:
   ```bash
   ./Chess        # Linux/macOS
   Chess.exe      # Windows
   ```

## 🎯 Usage

### Starting a Game

1. Launch the application
2. Select your preferred game mode from the main menu
3. For online play, choose to host a server or connect to an existing game
4. Begin playing by clicking and dragging pieces

### Game Controls

- **Move Pieces**: Click and drag pieces to valid positions
- **Game Menu**: Access new game, settings, and connection options
- **Status Display**: View current player turn and game state

### Online Play Setup

**Host a Game**:
1. Select "Host Game" from the menu
2. The application will start listening for connections
3. Share your IP address with the opponent

**Join a Game**:
1. Select "Join Game"
2. Enter the host's IP address
3. Click connect to join the game

## 🤖 AI Implementation

The AI engine uses sophisticated algorithms for intelligent gameplay:

### Alpha-Beta Pruning
- **Algorithm**: Minimax with alpha-beta optimization
- **Search Depth**: Configurable (default: 3 levels)
- **Evaluation**: Position-based scoring system
- **Performance**: Principal Variation Search (PVS) enhancement

### Position Evaluation Factors
- Material value (piece worth)
- Positional advantages
- King safety
- Pawn structure
- Piece mobility and control

### Performance Features
- **Threaded Computation**: Non-blocking AI calculation
- **Move Ordering**: Optimized search tree traversal
- **Transposition Tables**: Move caching for efficiency

## 🌐 Network Protocol

The online multiplayer uses a custom TCP-based protocol:

### Message Format
- Move commands with position encoding
- Game state synchronization
- Connection heartbeat and error handling

### Security Considerations
- Input validation for network messages
- Connection timeout handling
- Graceful disconnection management

## 📁 Project Structure

```
Chess/
├── Chess.pro              # Qt project file
├── main.cpp              # Application entry point
├── mainboard.{h,cpp}     # Main window implementation
├── board.{h,cpp}         # Game board and logic
├── piece.{h,cpp}         # Chess piece representation
├── computer.{h,cpp}      # AI opponent thread
├── ia.{h,cpp}            # AI algorithm implementation
├── boardevaluator.{h,cpp} # Position evaluation
├── move.{h,cpp}          # Move system
├── enums.{h,cpp}         # Game enumerations
├── comunication.{h,cpp}  # Network communication
├── online.{h,cpp}        # Online game management
├── *.ui                  # Qt Designer UI files
├── images/               # Game assets
│   ├── blackpieces.png
│   ├── whitepieces.png
│   ├── darkTile.png
│   └── lightTile.png
└── README.md
```

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.

### Development Guidelines
- Follow Qt coding conventions
- Maintain cross-platform compatibility
- Include unit tests for new features
- Document public APIs

### Areas for Enhancement
- Advanced AI algorithms (neural networks)
- Enhanced UI/UX design
- Tournament mode implementation
- Game analysis and notation support
- Database integration for game storage

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Author**: José Luis Cárdenas  
**Original C# Version**: [ChessTest Repository](https://github.com/jluispcardenas/ChessTest)  
