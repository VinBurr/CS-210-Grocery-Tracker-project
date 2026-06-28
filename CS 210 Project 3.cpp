//Vincent D Esposito
//6/16/2026
//Southern New Hampshire University
//The purpose of this program is to function as an item-tracking program
//This program will analize text records generated throughout the day at a grocery store 

#include <iostream> // console input and output 
#include <fstream> // input/output files 
#include <map> // Ordered key value storage 
#include <string> // so I can use strings 
#include <limits> // for input validation 
#include <cctype> // Character functions 
#include <algorithm> // for algorithms 
#include <iomanip> // formatting output 
#include <conio.h> // needed for _getch() function to pause after each menu 
#include <cstdlib> // need for system() function to clear the screen after menu swap 
using namespace std;


// Class: GroceryTracker
// Manages item frequency tracking, file I/O, and user
// menu interactions for the Corner Grocer program.

class GroceryTracker {
private:
    // Map to store item names (key) and their purchase frequencies (value)
    // Using map ensures items are stored in alphabetical order automatically
    map<string, int> itemFrequencies;

    // File names - centralized for easy maintenance
    const string inputFileName = "CS210_Project_Three_Input_File.txt";
    const string backupFileName = "frequency.dat";

    // Converts a string to lowercase for case-insensitive comparisons
    string toLowerCase(const string& str) const {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

    // Trims leading and trailing whitespace from a string
    void trimString(string& str) const {
        // Remove leading whitespace
        str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !isspace(ch);
            }));
        // Remove trailing whitespace
        str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !isspace(ch);
            }).base(), str.end());
    }

    /**
    This method Clears the terminal screen
    Return - None
    */
    void clearScreen() const {
        system("cls");

    }

public:
    /**
    This constructor initializes the tracker by reading the input file,
    populating the frequency map, and creating the backup data file.
    It runs automatically when the object is created.
    Parameter - None
    Return - None
    */
    GroceryTracker() {
        cout << "Initializing Corner Grocer Item Tracker..." << endl;
        cout << "Reading purchase records from: " << inputFileName << endl;

        ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            cerr << "ERROR: Unable to open input file '" << inputFileName << "'." << endl;
            cerr << "Please ensure the file exists in the program directory." << endl;
            return; // Frequencies map remains empty
        }

        string line;
        int totalItems = 0;
        while (getline(inputFile, line)) {
            trimString(line); // Clean up any extra spaces
            if (!line.empty()) {
                // Store with original casing from file for display consistency
                itemFrequencies[line]++;
                totalItems++;
            }
        }
        inputFile.close();

        cout << "Successfully loaded " << totalItems << " purchase records." << endl;
        cout << "Unique items tracked: " << itemFrequencies.size() << endl;


        // Create backup frequency.dat file at program start (as required)
        createBackupFile();
    }

    /**
    This method creates or overwrites the frequency.dat backup file.
    Format: One item and its frequency per line.
    Parameter - None
    Return - void
    */
    void createBackupFile() const {
        ofstream backupFile(backupFileName);
        if (!backupFile.is_open()) {
            cerr << "WARNING: Could not create backup file '" << backupFileName << "'." << endl;
            return;
        }

        for (const auto& entry : itemFrequencies) {
            backupFile << entry.first << " " << entry.second << endl;
        }
        backupFile.close();

        cout << "Backup data file created successfully: " << backupFileName << endl;
        cout << "\nPress Enter to continue . . . " << endl;
    }

    /**
     This method contains the main program loop.
     It displays the menu and processes user selections
     Parameter - None
     Return - void
     */
    void run() {
        int choice = 0;
        bool running = true;

        while (running) {
            clearScreen(); //to clean up the screen for the display menu 
            displayMenu();

            // Read user choice with basic input validation (optional challenge)
            if (!(cin >> choice)) {
                // Input was not a valid integer
                cout << "\n[ERROR] Invalid input. Please enter a number between 1 and 4." << endl;
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
                cout << "\nPress any key to continue...";
                _getch();
                continue;
            }
            clearScreen();           // Clear the main menu as soon as a choice is made

            // Process the valid menu choice
            switch (choice) {
            case 1:
                // Menu Option 1: Search for specific item frequency
                searchForItem();
                break;

            case 2:
                // Menu Option 2: Display all frequencies as list
                displayAllFrequencies();
                break;

            case 3:
                // Menu Option 3: Display histogram
                displayHistogram();
                break;

            case 4:
                // Menu Option 4: Exit program
                cout << "\nThank you for using the Corner Grocer Item Tracker." << endl;
                cout << "Exiting program..." << endl;
                running = false;
                break;

            default:
                // Invalid menu option
                cout << "\n[ERROR] Invalid menu option. Please select 1, 2, 3, or 4." << endl;
                break;
            }

            // Pause after showing result (except when exiting)
            if (running && choice != 4) {
                cout << "\nPress any key to return to the main menu...";
                _getch();                    // Wait for key press
            }
        }
    }

private:

    /**
    UI menu. We use void becauce this function isn't returning a value
    This function exsists to display our UI menu
    Parameter - none
    Return - there is none. It just prints to the user
    */
    void displayMenu() const {
        cout << "\n========================================" << endl;
        cout << "      CORNER GROCER - ITEM TRACKER      " << endl;
        cout << "========================================" << endl;
        cout << "  1. Search for an item's purchase frequency" << endl;
        cout << "  2. Display all item frequencies" << endl;
        cout << "  3. Display item frequency histogram" << endl;
        cout << "  4. Exit the program" << endl;
        cout << "========================================" << endl;
        cout << "Enter your selection (1-4): ";
    }

    // Menu Option 1:
    /**
    This method prompts the user for an item name and displays its frequency count.
    Parameter - None
    Return - None
    */
    void searchForItem() {
        cout << "\n--- Item Frequency Search ---" << endl;
        cout << "Enter the item name to look up: ";

        // Use getline to allow for item names that might contain spaces (future-proof)
        // First, consume any leftover newline from previous cin >>
        string itemName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, itemName);
        trimString(itemName);

        if (itemName.empty()) {
            cout << "[ERROR] No item name entered." << endl;
            return;
        }

        // Case-insensitive search using toLowerCase helper
        string searchKey = toLowerCase(itemName);
        bool found = false;
        int frequency = 0;
        string actualItemName; // To show original casing from file

        for (const auto& entry : itemFrequencies) {
            if (toLowerCase(entry.first) == searchKey) {
                found = true;
                frequency = entry.second;
                actualItemName = entry.first;
                break;
            }
        }

        if (found) {
            cout << "\n'" << actualItemName << "' appears " << frequency << " time(s) in the purchase records." << endl;
        }
        else {
            cout << "\n'" << itemName << "' was not found in the purchase records." << endl;
            cout << "It may not have been purchased today, or check spelling." << endl;
        }
    }

    // Menu Option 2:
    /**
    This method prints every item paired with its frequency count to the screen.
    It matches the required format and the content of frequency.dat.
    Parameter - None
    Return - None
    */
    void displayAllFrequencies() const {
        cout << "\n--- All Item Frequencies ---" << endl;
        cout << "Item Name          Frequency" << endl;
        cout << "-----------------------------" << endl;

        if (itemFrequencies.empty()) {
            cout << "No data available." << endl;
            return;
        }

        // Iterate through map (already sorted alphabetically)
        for (const auto& entry : itemFrequencies) {
            // Use left alignment and setw for neat columns
            cout << left << setw(20) << entry.first << entry.second << endl;
        }

        cout << "-----------------------------" << endl;
        cout << "Total unique items: " << itemFrequencies.size() << endl;
    }

    // Menu Option 3:
    /**
    This method prints a text-based histogram showing the purchase frequency of each item.
    It uses solid block characters and automatically scales the bars if any frequency is very high.
    Parameter - None
    Return - None
    */
    void displayHistogram() const {
        cout << "\n========================================" << endl;
        cout << "     PURCHASE FREQUENCY HISTOGRAM       " << endl;
        cout << "========================================" << endl;

        if (itemFrequencies.empty()) {
            cout << "No data available to display." << endl;
            return;
        }

        // Find the highest frequency for scaling (optional but nice)
        int maxFreq = 0;
        for (const auto& entry : itemFrequencies) {
            if (entry.second > maxFreq) maxFreq = entry.second;
        }

        for (const auto& entry : itemFrequencies) {
            cout << left << setw(18) << entry.first << " | ";

            // Scale bars if frequency is very high (max bar width = 50)
            int barLength = (maxFreq > 50) ? (entry.second * 50 / maxFreq) : entry.second;
            cout << string(barLength, char(219)) << "  " << entry.second << endl;
        }

        cout << "========================================" << endl;
        if (maxFreq > 50) {
            cout << "(Bars scaled to max width of 50)" << endl;
        }
    }
};

    /**
    This is the main entry point for the Corner Grocer Item Tracking program.
    It creates the GroceryTracker object and starts the interactive menu system.
    Parameter - None
    Return - int (program exit status)
    */
    int main()
    {
        cout << "Welcome to the Corner Grocer Item Tracking System" << endl;
        cout << "Developed for Chada Tech - Junior Developer Vinny Esposito" << endl;
        cout << "\nPress Enter to continue . . . " << endl;   // Wait for user to press enter key before showing the menu
        _getch(); // pause menu 
        system("cls"); // thank god for this function. makes menus poof be gone 
   
        GroceryTracker tracker;
        _getch(); // pause menu 
        system("cls"); // Clear everything again 

        tracker.run();

        cout << "\nProgram terminated successfully." << endl;
        return 0;
    }
