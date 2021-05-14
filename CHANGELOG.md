## Changelog 
All notable changes to this project will be documented in this file. 

### Unreleased
#### Added
- `README.md` explanation to setup game
- `CHANGELOG.md`

### [Version 2.0](https://github.com/ceh-2000/game-design-team-4/releases/tag/v2.0)
#### Added
- Main menu
    - Settings tab where users can type in their name to be used in the game and choose who the final chef in our game will be.  
    - Resources page which displays all of the art and music that we used in our game.
- Minigame switching/rounds
    - Added automatic minigame switching after a game ends. When 30 seconds has elapsed for games 1, 3 and 4, the `currentGame` variable is incremented and the next game starts. When the player hits the space bar at the end of minigame 2, game switching happens.
    - After the user presses the spacebar at the end of each round, all game parameters are reset including score and elapsed time and the round number is incremented to begin the next round.
- Rhythm Charter
    - Created play and stop button art.
- Cutscene Class
    - Implemented separate class that draws dialogue box along with scrolling text.
    - Created individual sprites of the main character, an opposing male chef, a background, and the dialogueBox.
    - Scrolling text utilizes the game loop to add characters to the text on screen until it has reached its end.
- Minigame 1
    - Bowl art.
    - Added a scoring system to quantify good and bad hits.
    - Added original ingredient textures.
    - Added game instructions.
    - Animation for AI Satsana to provide hit feedback.
    - Music added.
- Minigame 2
    - Added original knife sprite.
    - Graphics and score.
- Minigame 3
    - Added original knife sprite.
    - Implemented Animation object to animate a conveyor belt that carries the food across the screen.  
    - Added in logic code and corresponding view code to cut the sushi in half when there is a good hit.
    - Added game instructions.
    - Animation for AI Satsana to provide hit feedback.
    - Music.
- Minigame 4
    - In addition to position and scaling sprites, added a board and arrows with endpoints that acted as DDR.
    - The minigame logic pushes Beat Box objects to a vector that the view sees and checks for the x-value to determine which arrow corresponds.
    - Added colored arrows sprites and player sprites.
    - Created player sprite concept art.
    - Animation for AI Satsana to provide hit feedback.
    - Music added.

#### Fixed
- Animation class
    - Fully implemented the Animation class.  Has the ability to display sprites, either looping forever or not.  In addition, there is now an option to display text with the animation.
- BeatBox Logic
    - Rearranged conditional logic so that Beat Boxes no longer shake when they get to their final destination.
- Minigame 1
    - Fixed bowl movement so that bowl does not go off the screen if the player spams the arrow keys.
    - Fixed logic to determine if the user should tap left or right by correcting the check to see if the food fell on the left or right side of the screen.
- Minigame switching/rounds
    - Corrected logic that skipped minigame 3 because `currentGame` was iterated by 2 after minigame 2 instead of 1.
    - Fixed a bug that started the game over instead of returning to the Main Menu by changing the keyboard input in the Main Menu to enter instead of spacebar.

#### Removed
- Option to switch between games by pressing 1, 2, 3, or 4

### [Version 1.2](https://github.com/ceh-2000/game-design-team-4/releases/tag/1.2)
#### Added
- The basic logic for all four minigames:
    - Game 1: Bowl moves back and forth according to arrow key inputs and ingredient boxes drop in accordance with the beats.
    - Game 2: The view includes a rotating circle representing the pizza and a series of rotating cut slices representing the player cuts on the pizza. There is also a knife cutting animation done after the user presses the spacebar.
    - Game 3: Pressing the spacebar on the beat cuts the food.
    - Game 4: Input visual cues fly from the bottom to the top of the screen and the player must tap on the beat.
- We created more cutscene art and gifs that will go in as animations into the minigames. Most of the art has been created for Game 1.

#### Changed
- The view and logic classes are better defined. Instead of inheriting from the super view and super logic classes, these general classes are called first to detect and respond to beat hits and then the individual game’s logic is called.

#### Fixed
- BeatBox class now allows Beat Boxes to move even after the beat hit. This will allow for post-hit animations in games 1, and 3, 4.

#### Removed
- We removed the Animation class for now to limit complexity. We needed to refactor the game into logic and view, but for next time we plan to add it back in. The programmer should be able to specify a row of the sprite sheet and whether or not to loop the animation and then it will play.

### [Version 1.1](https://github.com/ceh-2000/game-design-team-4/releases/tag/v1.1)
#### Added
- Created basic minigame. The player attempts to tap on the beat and gets feedback on how good the tap was with a red, green, or yellow screen. Blue is neutral. Implemented tap check logic to produce this feedback.
- Implemented the ability in the Song class to read in timing arrays from the JSON file created by the charting tool.
- Illustrated cutscene concept and created tutorial character AI Satsana along with an animation
- Added and animated the character AI Satsana to the screen.  Gives feedback on how accurate the user’s input was with animation when she is talking.
- Implemented media player capabilities in the charting tool (play, pause, stop) and can chart based on position in song.
    - Horizontal scrollbar auto-scrolls in time to the song’s current playing position.
    - Can also select, delete, and click and drag beats and map to correct timings in seconds through use of rectangle-point collision.  
- Added export functionality with JSON files and arrays of timings which can be imported by the game for use in other minigames.

#### Fixed
- Made code more readable and made view and logic more understandable
- Fixed missed hits so that if the player never hits on the beat a miss hit is recorded.
- Reworked the player hit method to better distinguish between adjacent minigame timing actions by adding neutral areas between actions.


### [Version 1.0](https://github.com/ceh-2000/game-design-team-4/releases/tag/v1.0)
#### Added
- Created a new Song class and Game class. Song class holds SFML Music object to play, stop, pause, and get elapsed song time. 
- Created a very basic game loop. If the user presses the spacebar after 4 seconds of music playing, the screen flashes green, otherwise red. When the spacebar is released, the screen reverts to its original blue color. 
- Basic charting tool (separate from game for now) determines the major rhythm and beats of a given song.
