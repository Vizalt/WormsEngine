# Game of Worms
## Context
Game of Worms is a space-based worm game in which two cannons are separated on two different planets. After a nuclear war between the two nations, the two planets were immersed in an ice age. Although the low temperatures were thought to have wiped out all life on both planets, two small rusty cannons survived.  As a duel in a western movie, the survivors are facing each other in the last final fight of their lives. Each of them aims to destroy the other by firing cannonballs through the obstacles in their way, such as asteroids, the gravity of each planet or the frozen sea itself through which each cannon moves. 

### Controlers
- A and D - Movement
- Space - Shoot
- Left and Right - Cannon tilt
- Up and Down - Increase or decrease ball speed
- 1 - Enable/Disable Verlet
- 2 - Enable/Disable Backward Euler
- 3 - Enable/Disable Forward Euler
- F - Enable/Disable Drag
- G - Enable/Disable Lift
- H - Enable/Disable Newton Law
- F2 - Change dt 60 to 30

### Instructions
In each round players can only shoot once. Each player uses the same controls, which are exchanged each time one of them shoots. It is allowed to shoot with the player's own chosen speed and inclination, as well as choosing which forces are enabled or disabled and using the integrator of his choice. The first one to shoot against his opponent is the winner.
