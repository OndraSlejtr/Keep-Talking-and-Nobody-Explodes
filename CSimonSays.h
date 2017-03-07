#ifndef CSIMONSAYS_H
#define CSIMONSAYS_H

//#include "Auxil.h"
#include "CModule.h"
#include "Controls.h"
#include "Constants.h"

// *****************************************************************************************
//  Extended CSimonSays class, which inherits its basic components from CModule parent
// *****************************************************************************************

class CSimonSays: public CModule {

  public:
    CSimonSays (int posGiven, bool vowel);
    
    void moveLeft   (void);
    void moveRight  (void);
    void moveUp     (void);
    void moveDown   (void);
    
    bool pushSymbol (void);
    void showModule (void);
    void blinkKeys  (void);

  private:
    void drawColor (int color) const;
    
    int  selectedKey;
    int  blinkOrder[SIMON_SAYS_BLINKS]; // Saved sequence of blinks
    int  combinationUsed;               // Number of used color coding combination
    int  progress;                      // How many keys have I managed to press in correct order thus far
    int  currentOrderKey;               // Which key in shown combination am I currently supposed to be pressing
    bool needToShow;                    // Do we need to show visual clue to user


};

#endif // CSIMONSAYS_H
