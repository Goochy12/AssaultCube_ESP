// AssaultCube_ESP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AssaultCube_ESP.h"
using namespace std;

int main()
{
    cout << "Waiting to open Assult Cube...\n"; // Welcome message

    //get process window
    hwndAC_Client = NULL;

    // wait for the user to open the game
    while (hwndAC_Client == NULL) {
        //find game process
        hwndAC_Client = FindWindow(0, L"AssaultCube");
    }

    cout << "Assult Cube opened!" << endl;  // confirm the game is open

    //open game process


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
