#ifndef CKEYPADS_H
#define CKEYPADS_H

#include "CModule.h"
#include "Constants.h"


// *****************************************************************************************
//  Extended CKeypads class, which inherits its basic components from CModule parent
// *****************************************************************************************

class CKeypads : public CModule {
  private:
    bool checkCorrectSymbol (int positionBomb);

    int  combinationUsed;
    int  leftToSolve;
    int  selectedKey;
    
    int  shownSymbols  [KEYPADS_SHOWN_SYMBOLS_NMBR];
    bool solvedSymbols [KEYPADS_SHOWN_SYMBOLS_NMBR];

  public:  
    CKeypads (int posGiven);
    
    bool pushSymbol         (void);
    void showModule         (void);
    void moveLeft           (void);
    void moveRight          (void);
    void moveUp             (void);
    void moveDown           (void);


};

#endif // CKEYPADS_H
