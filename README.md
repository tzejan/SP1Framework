SP1 Framework
============


This framework is for helping students on the SP1 module to get started quickly on their projects. This framework only works on the Windows environment as it uses Windows API in some of its features. 

Main Features
-------------

- Game loop  
- Key press detection  
- Go to a certain console coordinate  
- Colours in console  
- Frame rate limiter  

What to do
----------

1. Team leader should fork this project into their own repository
2. Add your team mates as collaborators
3. Read and understand the code
4. Team leader should add this repository as a upstream remote repository if you want to get the latest bug fix or improvements. [Configuring a remote for a fork](https://help.github.com/articles/configuring-a-remote-for-a-fork)
5. Periodically sync changes to this repository to get latest awesome code. [Syncing a fork](https://help.github.com/articles/syncing-a-fork)
6. Start working on your project! Remember to commit often!

Framework usage
---------------

The framework is a basic bare bones implementation of a game loop. You should not mess around with the main files unless you know what you are doing.  
There are certain functions that you should be implementing.
##### init()
Initializes the game variables, load data, allocate memory, etc. Code that should run before the game starts should be here.

##### getInput()
Detects input from input sources, e.g. keyboard. This is where you detect if the user has given any input to the game, and set your flags accordingly.

##### update(double dt)
This is the meat of your code, the game logic should be done here. i.e. reaction to input, enemy movement, enemy spawning, win game condition, lose game condition, state of game, etc.
Sounds can be played here.

##### render()
Renders the current state of game onto screen. Go to a specific coordinate on the screen, set colours, write output, etc.

##### shutdown()
Code for cleaning up of game, writing of files, close files, free up memory, etc.

###Other functions in the framework

#### setConsoleSize()
Sets the size of the console. The largest size depends on your screen  

#### SetConsoleTitle()
Sets the title of the console. 



FAQ
---

**How do I set the size of the console?**  
There is a function setConsoleSize() that does this. See above

**The screen flickers!**  
Everyone else is facing the same problem, don't worry too much about it. I'm working on a solution.


