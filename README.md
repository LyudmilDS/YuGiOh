# Yu-Gi-Oh Game Recreation

## Overview
A command-line recreation of the popular card game Yu-Gi-Oh built in C++. This project demonstrates object-oriented design, advanced C++ features (move semantics, input validation), and proper game flow management.

## Project Structure

### Classes
- **Card**: Represents a single card with attributes
- **Player**: Manages player state
- **Game**: Orchestrates game flow and battle mechanics

## Gameplay

### Card System
Cards are loaded from `saved_cards.txt` and randomly assigned to each player's deck. Each card has:
- Name
- Attack Power
- Defence Power
- Position (attack/defence)

### Game Flow
A turn consists of four phases:

1. **Draw Phase**: Player draws one card from their deck to their hand
2. **Standby Phase**: Player can summon cards from hand to the field in attack or defence position, or change card positions
3. **Battle Phase**: Player selects an attacking card from their field and a defending card from opponent's field. Damage is calculated based on the card powers and positions
4. **End Phase**: Turn ends and passes to the opponent

## Key Features
- Robust input validation with error recovery
- Move semantics for efficient card transfers
- Modular function design with separation of concerns
- Proper resource management and memory efficiency
