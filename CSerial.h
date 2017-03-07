#ifndef CSERIAL_H
#define CSERIAL_H

#include "CModule.h"
#include "Constants.h"

// *****************************************************************************************
//  Extended CSerial class, which inherits its basic components from CModule parent
// *****************************************************************************************

class CSerial : public CModule {

  public:
    CSerial (int posGiven);
    
    bool pushSymbol         (void);
    void showModule         (void);
    
    void moveLeft  (void);
    void moveRight (void);
    void moveUp    (void);
    void moveDown  (void);

    virtual bool hasVowel (void);
    virtual bool lastOdd  (void);

    
  private:
    int selectedSerial;
    


};

#endif // CSERIAL_H
