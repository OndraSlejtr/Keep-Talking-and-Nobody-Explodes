#ifndef CWIRES_H
#define CWIRES_H

#include "CModule.h"
#include "Constants.h"

// *****************************************************************************************
//  Extended CWires class, which inherits its basic components from CModule parent
// *****************************************************************************************

class CWires : public CModule {

  public:
    CWires (int posGiven, bool oddSerial);
    
    void drawWireColor (int color);
    bool pushSymbol         (void);
    void showModule         (void);
    
    void moveLeft  (void);
    void moveRight (void);
    void moveUp    (void);
    void moveDown  (void);

    
  private:
    bool checkWires3 (int pos) const;
    bool checkWires4 (int pos) const;
    bool checkWires5 (int pos) const;
    bool checkWires6 (int pos) const;
  
    bool checkCorrectSymbol (int positionBomb);
    int  wiresAmount;
    int  shownWires  [10];
    int  selectedWire;
    bool oddSerial;
    


};

#endif // CWIRES_H
