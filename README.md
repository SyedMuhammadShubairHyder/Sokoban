Sokoban Console Game
Overview
This project is an object-oriented implementation of the classic Sokoban game using C++. Sokoban is a puzzle game in which the player pushes boxes around in a warehouse, trying to get them to designated storage locations. The player can only push the boxes and cannot pull them, making the game both challenging and engaging.

Features
Classic Sokoban Gameplay: Move the player character to push boxes to their target locations.
Console-Based Interface: Play the game directly in your terminal or console window.
Object-Oriented Design: Leverages OOP principles for clean and maintainable code.
15 Hardcoded Levels: Includes a variety of levels to challenge your puzzle-solving skills.
Restart Feature: Allows you to restart the game.


Controls
"w  a  s  d ": Move the player character up, down, left, or right.

How to Play
The objective is to push all the boxes onto the storage locations.
Use the control keys to move the player character. The player can push a box by moving towards it.
Plan your moves carefully, as you cannot pull boxes, only push them.
Although this implementation includes 15 hardcoded levels 
@ : Player starting position
# : Wall
O : Box
+ : Storage location
X : Box on storage location
(space) : Empty space
Example of a level layout:
<img width="661" alt="Game" src="https://github.com/shubairHyder/Sokoban/assets/167424904/3f296289-f15d-4cb4-aa9a-c4ee19116ef6">

Object-Oriented Design
The game is designed using OOP principles to ensure clean, modular, and maintainable code. Key classes include:

Game: Manages the overall game state and game loop.
Level: Represents individual levels, including layout and level-specific logic.
Player: Manages player state and movement.
Box: Represents the boxes that need to be pushed to storage locations.
Tile: Represents each tile in the level grid (e.g., floor, wall, storage).
Contributing
Contributions are welcome! Here are some ways you can contribute:

Report bugs and issues.
Suggest new features.
Create new levels.
Improve documentation.
To contribute:

Fork the repository.
Create a new branch for your feature or bugfix.
Commit your changes and push to your branch.
Create a pull request explaining your changes.
License
This project is licensed under the MIT License. See the LICENSE file for more details.

Acknowledgements
Sokoban game concept and original design.
C++ community for making programming fun and accessible.
Contact
If you have any questions or feedback, feel free to reach out at your.email@example.com.

Enjoy the game and happy puzzling!
