  The so_long project is part of 42school curriculum, this project aims to introduce the student in concepts and techniques in game-design, the subject requires
the program to follow certain rules, such as:

  - Limitations in which library functions you can use (mandatory part), it means any function not allowed you have to code youself if you really needed, or pursue
    different approaches to resolve the problem.
  - The use of MiniLibX to render images and windows.
  - Be a 2D view game (top-down or profile).
  - And other shennennigans..

  The great and maybe more pendatic aspect of the game is that the program must be able to receive as argument the map in the format of a .ber file (map1.ber)
so any user can make your own map! since it follow certain rules of course, the main are:

  - The map must be composed of only 5 characters:
    0 for empty space;
    1 for a wall;
    C for a collectible;
    E for the map exit;
    P for the player's starting position.

    example:
    ## 
          11111111111
          1000100P001
          10C010EC001
          11111111111

  The map also must be surrounded by wall ('1'), must have a valid path, it means that the player must be able to reach the collectibles and exit, this is done use
a DFS (Depth-First Search algorithm) using a flood-fill implementation of it. More details google it. The program must have some other safety and map validation
checks that are not worth mention.

  Skipping to the bonus part, the project propose the student to add some sprite animations to the game, and enemy patrols GWAAAA, and a count of players movement
directly on the screen instead of shell.

To run the project you must first install the following packages
##
    apt install libx11-dev libxext-dev libbsd-dev install clang

  Get the minilibx sources at 42paris repository:
##
    git clone https://github.com/42Paris/minilibx-linux minilibx_linux

  Compile and install mlx.a in a minilibx_linux folder:
##
    cd minilibx_linux; make && sudo ./configure

  and ready to go. (add mac and windows steps later)

  Now that you have the minilibx ready you should clone this repository on the desired folder and run
##
    make
  
  To run the game:
##
    ./so_long <map.ber>

  The players moves with the keyboard arrows keys, and now your mission is to collect all the collectible without hit a enemy patrol!! NOTE: the use of enemies is
not mandatory, to add them you must include in the .ber file map grid the character 'F' for foe. And now you are in the same room with all the people who ghosted
you, good luck.
    
