# CS-210-Grocery-Tracker-project
This project required building a menu-driven C++ program that analyzes daily purchase records from a text file () for the Corner Grocer. The main goal was to help the store understand how often items are purchased so they can make better decisions about rearranging their produce section.
The program reads the input file, counts the frequency of each item using a map, creates a backup file (), and provides an interactive menu with four options: search for a specific item’s frequency, display all frequencies in a list, display a histogram, and exit the program.

I believe I did well with overall program structure and organization. I created a single GroceryTracker class that properly encapsulated the data and functionality. Using a std::map was an effective choice because it automatically kept items sorted alphabetically and provided efficient lookup for the search feature.
I also paid close attention to user experience by adding screen clearing between menus, input validation for the menu choice, and a clean “Press any key to continue” flow. The improved histogram with scaled bars and solid block characters made the output much more readable than a basic asterisk version. Additionally, I followed good documentation practices by writing clear function comments.

There are a few areas where I feel the code could be improved:

Error handling: Currently, if the input file is missing, the program continues with an empty map. Adding more robust error handling (such as preventing the menu from running if no data was loaded) would make the program more reliable.
Code duplication: The screen clearing and pause logic is repeated in a few places. Creating more helper functions or a dedicated MenuManager class could reduce repetition.
Histogram scaling: While the current scaling works, it could be made more dynamic or allow the user to choose different visualization styles.
Testing: Adding more automated testing (especially for file reading and frequency counting) would increase confidence in the program’s correctness.

These improvements would make the code more robust, easier to maintain, and more professional.

The most challenging parts were:

Managing the input buffer correctly when mixing cin >> with cin.get() / _getch() for pauses. This caused several “double Enter” issues.
Properly structuring the menu loop so the screen cleared at the right times without breaking the flow.
Getting the histogram to look clean while also adding scaling logic.

I overcame these challenges by testing small pieces of code incrementally and using the debugger in Visual Studio. I also referenced zyBooks sections on file I/O, classes, and the STL map container. Moving forward, I’m adding incremental testing and rubber duck debugging (explaining the code out loud) to my support network, along with continuing to use Visual Studio’s debugging tools effectively.

Several skills from this project are highly transferable:

Object-Oriented Programming — Designing classes with proper public and private sections (encapsulation).
STL usage — Comfort using std::map, std::string, and algorithms from <algorithm>.
File I/O — Reading from and writing to text files, which will be useful in future database or data processing projects.
Menu-driven program design — Creating clean user interfaces in console applications.
Input validation and error handling — Skills that apply to almost any interactive program.
Code documentation — Writing clear comments and following consistent formatting standards.

These skills will directly help in future courses involving data structures, software engineering, and application development.

I focused on several practices to improve maintainability and readability:

Used meaningful variable and function names (e.g., searchForItem(), itemFrequencies, displayHistogram()).
Organized the code into a single, well-structured class with clear separation between public interface and private implementation.
Added in-line comments and followed the required function comment format.
Used const where appropriate to prevent accidental modification of data.
Made the file names (inputFileName and backupFileName) easy to change if needed in the future.
Kept the run() method as the central control point, making the overall program flow easy to follow.

These choices make the code easier for someone else (or future me) to read, understand, and modify.
