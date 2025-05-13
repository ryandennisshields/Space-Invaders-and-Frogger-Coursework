#include "Menu.h"

extern int menuChoice = 0;

void Menu::run() 
{
    bool valid = false;
    int choice;
    do { 
        system("cls");
        cout << "Start Screen:" << endl;
        cout << "1. Space Invaders" << endl;
        cout << "2. Frogger" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            menuChoice = 1;
            valid = true;
            system("cls");
            break;
        case 2:
            menuChoice = 2;
            valid = true;
            system("cls");
            break;
        case 3:
            menuChoice = 3;
            valid = true;
            system("cls");
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        if (!valid) {
            cout << "Press any key to continue..." << endl;
            _getch();
        }
    } while (!valid);

}