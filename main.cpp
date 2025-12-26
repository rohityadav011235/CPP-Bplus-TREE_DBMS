// =============================================================
// FILE: main.cpp
// PURPOSE: Handles User Input, Menus, and File Reading/Writing
// =============================================================

#include <iostream>
#include <fstream> // Required for file handling (saving/loading data)
#include <string>
#include <limits>     // Required for the numeric_limits fix
#include "bptree.hpp" // Links to your B+ Tree header file

using namespace std;

// =============================================================
// FUNCTION: saveStudentToFile
// PURPOSE: Writes student details to a text file.
// EXPLANATION: We use the ID as the filename (e.g., "101.txt") to
// quickly find the file later without searching through a big list.
// =============================================================
void saveStudentToFile(int id, string name, int age, string course)
{
    string filename = to_string(id) + ".txt";
    ofstream outFile(filename); // Open file in "write" mode

    if (outFile.is_open())
    {
        outFile << name << endl;   // Line 1: Name
        outFile << age << endl;    // Line 2: Age
        outFile << course << endl; // Line 3: Course

        outFile.close(); // Always close files to prevent data loss!
        cout << "[Success] Student data saved to " << filename << endl;
    }
    else
    {
        cout << "[Error] Could not create file! Check permissions." << endl;
    }
}

// =============================================================
// FUNCTION: readStudentFromFile
// PURPOSE: Opens a specific student's file and prints the details.
// =============================================================
void readStudentFromFile(int id)
{
    string filename = to_string(id) + ".txt";
    ifstream inFile(filename); // Open file in "read" mode

    if (inFile.is_open())
    {
        string name, ageStr, course;

        // We must read in the EXACT same order we wrote (Name -> Age -> Course)
        getline(inFile, name);
        getline(inFile, ageStr);
        getline(inFile, course);

        // Print a professional looking ID card
        cout << "\n================================" << endl;
        cout << "       STUDENT RECORD FOUND      " << endl;
        cout << "================================" << endl;
        cout << " ID     : " << id << endl;
        cout << " Name   : " << name << endl;
        cout << " Age    : " << ageStr << endl;
        cout << " Course : " << course << endl;
        cout << "================================\n"
             << endl;

        inFile.close();
    }
    else
    {
        // This handles the edge case where the ID is in the Tree index,
        // but the actual text file was deleted.
        cout << "[Error] Index found, but data file is missing!" << endl;
    }
}

// =============================================================
// MAIN FUNCTION
// =============================================================
int main()
{
    BTree t(3); // Create B+ Tree with minimum degree 3
    int choice;

    cout << "Welcome to the University Database System" << endl;

    while (true)
    {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Show Tree Structure" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        // --- BUG FIX: INFINITE LOOP PREVENTION ---
        // If user types '!' or 'abc' instead of a number, cin fails.
        if (cin.fail())
        {
            cin.clear(); // 1. Reset the error flag on cin
            // 2. Ignore the rest of the bad line (up to new line)
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number (1-4)." << endl;
            continue; // Restart the loop immediately
        }
        // -----------------------------------------

        if (choice == 1)
        {
            // --- ADD STUDENT ---
            int id, age;
            string name, course;

            cout << "\nEnter ID (e.g., 101): ";
            cin >> id;

            // Same bug fix for ID input
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID! Must be a number." << endl;
                continue;
            }

            // Duplicate Check
            if (t.search(id))
            {
                cout << "[Warning] Student ID " << id << " already exists!" << endl;
                continue;
            }

            // CRITICAL: Clear the "newline" left in the buffer by 'cin'
            // before using 'getline', otherwise getline reads an empty line.
            cin.ignore();

            cout << "Enter Name (e.g., Rahul Sharma): ";
            getline(cin, name);

            cout << "Enter Age: ";
            cin >> age;

            // Bug fix for Age input
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Age! Student not added." << endl;
                continue;
            }
            cin.ignore(); // Clear buffer again

            cout << "Enter Course (e.g., B.Tech CS): ";
            getline(cin, course);

            // 1. Update Index (Tree)
            t.insert(id);
            // 2. Update Storage (File)
            saveStudentToFile(id, name, age, course);
        }
        else if (choice == 2)
        {
            // --- SEARCH STUDENT ---
            int searchId;
            cout << "Enter ID to Search: ";
            cin >> searchId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!" << endl;
                continue;
            }

            // Check the B+ Tree Index first for speed
            bool found = t.search(searchId);

            if (found)
            {
                // If found in index, go fetch the details from disk
                readStudentFromFile(searchId);
            }
            else
            {
                cout << "[Result] Student ID " << searchId << " not found." << endl;
            }
        }
        else if (choice == 3)
        {
            // --- SHOW STRUCTURE ---
            cout << "\n--- Current B+ Tree Index Structure ---" << endl;
            t.display();
            cout << "---------------------------------------" << endl;
        }
        else if (choice == 4)
        {
            cout << "Exiting system..." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice, please try again." << endl;
        }
    }
    return 0;

}
