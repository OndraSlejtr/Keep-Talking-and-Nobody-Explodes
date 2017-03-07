#ifndef CONTROLS_H
#define CONTROLS_H
#include "CBomb.h"

#define DOWN  SWITCH_DOWN
#define UP    SWITCH_UP
#define LEFT  SWITCH_LEFT
#define RIGHT SWITCH_RIGHT

void loadingScreen (void);
void eraseDisplay  (void);

bool buttonEvent (int button);

#endif // CONTROLS_H
