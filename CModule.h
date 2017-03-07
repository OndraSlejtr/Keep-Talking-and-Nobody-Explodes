#ifndef CMODULE_H
#define CMODULE_H

// *****************************************************************************************
// Basic CModule class, parent for all modules
// *****************************************************************************************

class CModule {
  protected:
    static int amountOfModules;
    
  public:
    CModule (void);
    
    virtual void moveLeft   (void) = 0;
    virtual void moveRight  (void) = 0;
    virtual void moveUp     (void) = 0;
    virtual void moveDown   (void) = 0;
    virtual void showModule (void) = 0;
    virtual bool pushSymbol (void) = 0;

    virtual bool hasVowel   (void) { return false; }
    virtual bool lastOdd    (void) { return false; }

    void       addError (void);  

    int positionBomb;           // Position in current set of modules
    static int strikes;         // Amount of collected strikes
    bool       solved;          
    int        lastSelectedKey; // Variable that lets modules remember last selected position when moving across screens. 
                                // Value -1 marks special need for modules that react to change of scene (new blinking for SimonSays)
};

#endif // CMODULE_H
