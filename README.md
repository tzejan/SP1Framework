SP1 Framework
============

This framework is to help students on the SP1 module to get started quickly on their projects. This framework only works on the Windows environment as it uses Windows API in some of its features. 

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

### Console functions in the framework

There are 2 types of console functions, one that uses that std::cout, and one that uses the Console object.  
For beginners, the functions that work with std::cout is more suitable as they are more familiar.
If you experience flickering of the screen, that is because the output is flushed to the std output every time it is written. Hence, a faster way is to write the output to a buffer, and flushed at the end of the render() loop.

#### Console functions to use with std::cout
The following functions might need a console object to be instantiated and then you can call these functions. Needless to say, these functions are going to be deprecated and you should not be using them.

##### void gotoXY(int x,int y);
##### void gotoXY(COORD c);
Go to a specific location on the screen and writes to the std output from there. Origin is top left.

##### void colour(WORD attrib);
Sets a specific colour to be used in the next call to std::cout.

##### void cls( HANDLE hConsole = 0);
Clears the screen with the last colour attribute set.

#### Console object
You will only need to create one console object, and use this one true object in your code for all the console output. 

##### Console(COORD consoleSize, LPCSTR lpConsoleTitle = 0);
##### Console(unsigned short consoleWidth, unsigned short consoleHeight, LPCSTR lpConsoleTitle = 0);
Inits the console size, and give it a title, pass in a C-Style string

##### COORD getConsoleSize();  
Gets the console size, in a COORD struct.

##### void setConsoleTitle(LPCSTR lpConsoleTitle);
Sets the console title

##### void setConsoleFont(SHORT width, SHORT height, LPCWSTR lpcwFontName); 
Sets the console font. You can set the width and height of the raster fonts. If you are using a TrueType font, you can use the height as the font size. 

##### void clearBuffer(WORD attribute = 0x0F);
Clears the data buffer, hence "clearing the screen", preparing for new data.

##### void writeToBuffer(COORD c, LPCSTR str, WORD attribute = 0x0F);
##### void writeToBuffer(COORD c, std::string& s, WORD attribute = 0x0F);
##### void writeToBuffer(COORD c, char ch, WORD attribute = 0x0F);
##### void writeToBuffer(SHORT x, SHORT y, LPCSTR str, WORD attribute = 0x0F);
##### void writeToBuffer(SHORT x, SHORT y, std::string& s, WORD attribute = 0x0F);
##### void writeToBuffer(SHORT x, SHORT y, char ch, WORD attribute = 0x0F);  
The origin of the screen is on the top left.
These 6 functions writes to the buffer at that coordinate, you can use C-Style strings, C++ string class or a char. The attribute is a optional parameter. The last 3 functions are overloaded versions of the first 3 functions.


##### void flushBufferToConsole();
Call this at the end of the render() function so that the contents of the buffer will be displayed onto the screen.


FAQ
---

**How do I set the size of the console?**  
The console size is set in the constructor of the console object. See the sample code to see how this is done. Note that if you tried to set an invalid size, the size of the console will be set to a default size, and you will get an error message.

**The screen flickers!**  
It could be due to too much flushing of the buffer to the screen. Make sure that there is no std::cout functions called in your code. You should be clearing the buffer only once. You should be flushing the buffer to the console only once. 

**Unicode**  
Right now, there is no support for unicode, but talk to me if you really need unicode, and we see if we can try out some stuff.

Tips
----
- Do not write all your code in just the files provided. Create your files, write your code in your own files and call your functions.    
- Each functionality should be in its own file, this will make it easier for you to merge changes later.  
- Pass in the data you need into your function, do not use global variables unnecessarily.  
- Talk to your teammates, keep them updated, and informed, especially if you have difficulties.  
- Try not to have more than 1 person working on the same file, or even worse, same function.  
- One commit for one functionality  
- Mega commits are frowned upon. It might kill your project.  - 
- Commit often, commit early  


