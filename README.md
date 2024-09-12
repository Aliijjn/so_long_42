# so_long_42

### Skills learned from project:
- How to use external libraries
- How to make a basic game loop
- Proper structuring of data for error handling
- Handeling of real-time user input
- How backtrack algorithms work

### Images
![image](https://github.com/user-attachments/assets/e5cfbdb7-3e6d-420e-a4f2-6a6627bbfdef)
![image](https://github.com/user-attachments/assets/d0de1eff-ee48-43aa-b975-08ec64fe0359)

### Project goals
so_long is a project in the 42 curriculum, where the goal is to make a 2d game. For this project had to use MLX42, an external graphics library, which is needed to render sprites and to get user input. To run the executable, you need the path to a .ber file as the second argument. A .ber file should consist of these characters:
`1` Wall
`0` Open space
`P` Player spawn
`E` Exit
`C` Collectable

There are also a couple of rules a map has to follow to be considered valid:
- The map should only contain these aformentioned characters
- The map should be rectangular and surrounded by walls
- There should be only one player spawn and exit
- There should be at least one collectable
- The player should be able to reach all collectables and the exit

The last requirement was quite tricky to verify, as I needed to check if the player is able to reach every coin and the exit. I used a backtracking algorithm for this, which will check all possible moves the player can make.  

### An example of an valid map file:
![image](https://github.com/user-attachments/assets/86aa6756-3f72-4a76-aa76-9be70ac9cd19)
### Which will display this level:
![image](https://github.com/user-attachments/assets/811fde54-f718-4c42-80f0-89536ab1b5b5)

Made by Alijn Kuijer, 2024
