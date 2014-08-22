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

###Console functions in the framework

##### void initConsole(COORD consoleSize, LPCSTR lpConsoleTitle=0);
Inits the console size, and give it a title, pass in a C-Style string

##### void shutDownConsole();
Call this before you quit the game. Returns the console to show output from the STDOUT stream  



##### void clearBuffer(WORD attribute = 0x0F);
Clears the data buffer, hence "clearing the screen", preparing for new data.

##### void writeToBuffer(COORD c, LPCSTR str, WORD attribute = 0x0F);
##### void writeToBuffer(COORD c, std::string s, WORD attribute = 0x0F);
##### void writeToBuffer(COORD c, char ch, WORD attribute = 0x0F);
These 3 functions writes to the buffer at that coordinate, you can use C-Style strings, C++ string class or a char. The attribute is a optional parameter.

##### void flushBufferToConsole();
Call this at the end of the render() function so that the contents of the buffer will be displayed onto the screen.

### Advanced users only

##### CHAR_INFO* getScreenDataBuffer();
Gets the screen data buffer, the buffer used in displaying the output. Do not use this unless you know what you are doing.  
##### void writeToConsole(const CHAR_INFO* lpBuffer);
With the screen data buffer, flush the output to the console.

FAQ
---

None yet
