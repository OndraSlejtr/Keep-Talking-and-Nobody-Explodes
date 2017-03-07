#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "CBomb.h"

/**
 * @brief Function to create a new bomb with given paramters
 *
 * @param Amount of modules for bomb to be created with
 * @param Time limit for the bomb
 */

CBomb::CBomb (int moduleAmount, int timeLeft)  : moduleAmount(moduleAmount+1), currentlyShown(0),
              timeExplosion ((millis() / 1000) + timeLeft) {
                
  moduleList = new CModule* [this->moduleAmount];

  

  // First three modules are always given so each type is represented at least once. Plus Serial number display.
  moduleList[0] = new CSerial(0);
    bool vowelSerial = moduleList[0]->hasVowel();
    bool oddSerial = moduleList[0]->lastOdd();
  
  moduleList[1] = new CKeypads(1);
  moduleList[2] = new CSimonSays(2, vowelSerial);
  moduleList[3] = new CWires(3, oddSerial);

  // If there are more than 3 modules to be created, start picking random modules to implement
  for (int i=4; i < moduleAmount+1; ++i){

    int rndChoice = random(1,4);
    switch (rndChoice){
      case 1 :
        moduleList[i] = new CKeypads(i);
        break;
      case 2 :
        moduleList[i] = new CSimonSays(i, vowelSerial);
        break;
      case 3 :
        moduleList[i] = new CWires(i, oddSerial);
        break;
   
    }
  }
  currentModule = moduleList[0];  
}


CBomb::~CBomb (void){
  for (int i=0; i < moduleAmount; ++i){
    delete moduleList[i];    
  }
  delete [] moduleList;  
}

/**
 * @brief Function to detonate bomb - show information to user.
 *
 */

void CBomb::detonateBomb(void) {
    eraseDisplay();    
    Esplora.writeRed(255);
    EsploraTFT.stroke(255,255,255);
    EsploraTFT.setTextSize(5);
    EsploraTFT.text("BOOM", 22, 30);
    EsploraTFT.setTextSize(2);
    EsploraTFT.text("You are dead :(", 10, 80);
    EsploraTFT.setTextSize(1);
    EsploraTFT.text("Press UP to start again.", 10, 110);
}


/**
 * @brief Function to inform user that he has successfully defused bomb.
 *
 */

void CBomb::showSolvedBomb(void) {
    eraseDisplay();    
    Esplora.writeGreen(255);
    EsploraTFT.stroke(255,255,255);
    EsploraTFT.setTextSize(5);
    EsploraTFT.text("WOW", 40, 15);
    EsploraTFT.setTextSize(2);
    EsploraTFT.text("You survived", 10, 65);
    EsploraTFT.setTextSize(1);
    EsploraTFT.stroke(100,100,100);
    EsploraTFT.text("Unexpected.", 50, 90);
    EsploraTFT.stroke(255,255,255);
    EsploraTFT.text("Press UP to start again.", 10, 110);
}


/**
 * @brief Function checking all modules for whether the entire bomb has been solved.
 *
 */

bool CBomb::isSolved(void) const{

  for (int i=0; i < moduleAmount; ++i){
    if (! moduleList[i]->solved)
      return false; 
  }

  return true;

}

/**
 * @brief Function for displaying bomb template.
 *
 */

void CBomb::showBomb (void){

    EsploraTFT.setTextSize(1);
    if (currentModule->solved){
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text( "SOLVED", 60, 5 );
    }
    else{
      EsploraTFT.stroke(120,120,120);
      EsploraTFT.text( "Not solved", 50, 5 );
    }
    
    EsploraTFT.setTextSize(1);
    for (int i = 0; i < MAXIMUM_STRIKES_ALLOWED; i++){

      // Check whether strike is already used up or not
      if (i < currentModule->strikes){
        EsploraTFT.stroke(255,0,0);
        EsploraTFT.text("X", 130+7*i, 5);
        EsploraTFT.stroke(255,255,255);
      }
      else{
        EsploraTFT.stroke(0,255,0);
        EsploraTFT.text("X", 130+7*i, 5);
        EsploraTFT.stroke(255,255,255);
      }
    }


   // Display current position within model list
    char tmp[10];
    sprintf (tmp, "%d/%d", currentModule->positionBomb+1, moduleAmount);
    EsploraTFT.text(tmp, 130, 120);
    
    
    EsploraTFT.setTextSize(2);
    
    currentModule->showModule();
}

/**
 * @brief Functions to move between modules of the bomb
 *
 */

void CBomb::listLeft (void){

    currentModule->lastSelectedKey = -1;
    currentlyShown = (currentlyShown - 1 + moduleAmount) % moduleAmount;

    if (currentModule == moduleList[0])
      currentModule = moduleList[moduleAmount-1];
    else
      currentModule = moduleList[currentlyShown];
    
}

void CBomb::listRight (void){

    currentModule->lastSelectedKey = -1;
    currentlyShown = (currentlyShown + 1) % moduleAmount;

    if (currentModule == moduleList[moduleAmount-1])
      currentModule = moduleList[0];
    else
      currentModule = moduleList[currentlyShown];
  
}
