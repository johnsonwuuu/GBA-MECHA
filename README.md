# GBA MECHA Game

A Game Boy Advance game recreation of https://mechazilla.io/
Your mission: Land the rocket perfectly upright without any residual angular velocity or translational momentum.

## Technical Details

This game is built using:
- C++ programming language
- DevkitARM GBA toolchain
- Mode 3 bitmap graphics (3 Levels)
- DMA for efficient memory transfers
- Hardware sprites for character animations
- Numerical state vector updates

## Prerequisites

To build and run this game, you need:
- DevkitPro with DevkitARM installed
- A GBA emulator (like mGBA, VBA-M, or NO$GBA)
- Make utility

## Building the Game

1. Open your terminal/command prompt
2. Navigate to the project directory
3. Run the make command:
This will compile the source code and create a .gba file.

## Running the Game

You can run the generated .gba file using any GBA emulator:
- mGBA: Open mGBA and load the .gba file
- VBA-M: Open VBA-M and load the .gba file
- Hardware: Load the .gba file onto a flash cart

## Controls
- Left/Right Keys: Override control systems to adjust thrust vector
- The goal is to land perfectly upright
- Avoid any angular velocity or unnecessary momentum
- Monitor the fixed thrust curve for guidance
