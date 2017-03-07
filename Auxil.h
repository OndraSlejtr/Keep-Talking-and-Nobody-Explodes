// *****************************************************************************************
//  Auxiliary functions connected to functioning of Bomb
// *****************************************************************************************

#ifndef AUXIL_H
#define AUXIL_H
#include "CBomb.h"
#include "Controls.h"

static CBomb * theBomb;                           // Currently used bomb

static int timeLeft;                              // Time remaining until bomb explodes
static bool displayChange = false;                // Flag to check for movement across screens
static bool joystickPressed = false;              
static bool joystickButtonPressed = false;        // Flags to check for input element release
static bool tickTock = false;                     // Flag for bomb ticking simulation
static bool needToInit = true;                    // Flag for first bomb initialization

void showMenu (void);
void createNewBomb (int moduleAmount, int timer);

void displayTime (void);
void readInput (void);
void checkTime (void);
void checkSolved (void);

#endif // AUXIL_H
