#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include <Arduino.h>
#include "CKeypads.h"


/**
 * @brief Constructor for CKeypads object
 *
 * @param Lets object know its position in the order of modules
 */

CKeypads::CKeypads (int posGiven){

  for (int i=0; i < KEYPADS_SHOWN_SYMBOLS_NMBR; i++){
    shownSymbols[i]=-1;
    solvedSymbols[i]=false;
  }
    
  combinationUsed = random (0, ( sizeof(keypadsList) / sizeof (keypadsList[0]) ) );       // Pick which set of symbols to generate module from
  leftToSolve = KEYPADS_SHOWN_SYMBOLS_NMBR;
  positionBomb = posGiven;
  selectedKey = 0;
  solved = false;

  for (int i=0; i < KEYPADS_SHOWN_SYMBOLS_NMBR; i++){                               // Fill array of shown symbols with predefined contents (see Constants.h)
    bool alreadyUsedFlag = false;                                                   
    int randTmp = random (0, KEYPADS_LIST_SIZE) ;

    for (int j=0; j < i && j < KEYPADS_SHOWN_SYMBOLS_NMBR; j++){                    // Procedure to check whether this symbol has already been used
        if (shownSymbols[j] == randTmp)
            alreadyUsedFlag = true;
    }

    if (!alreadyUsedFlag)
        shownSymbols[i] = randTmp;
    

    else
        i--;
  }
}


/**
 * @brief Function that displays the entire module to user
 *
 */

void CKeypads::showModule (void){

  EsploraTFT.setTextSize(4);
  EsploraTFT.stroke(0,0,0);
  for (int i=0; i < KEYPADS_SHOWN_SYMBOLS_NMBR; i++){
     EsploraTFT.rect(KEYPADS_LEFT_PADDING + (i % 2 == 1 ? 1 : 0) * KEYPADS_KEY_SPREAD, KEYPADS_TOP_PADDING + (i > 1 ? 1 : 0) * KEYPADS_KEY_SPREAD, KEYPADS_KEY_SIZE, KEYPADS_KEY_SIZE);
  }
  EsploraTFT.stroke(255,255,255);

  for (int i=0; i < KEYPADS_SHOWN_SYMBOLS_NMBR; i++){
    if (i == selectedKey){
      EsploraTFT.rect(KEYPADS_LEFT_PADDING + (i % 2 == 1 ? 1 : 0) * KEYPADS_KEY_SPREAD, KEYPADS_TOP_PADDING + (i > 1 ? 1 : 0) * KEYPADS_KEY_SPREAD, KEYPADS_KEY_SIZE, KEYPADS_KEY_SIZE);
    }
        
    char tmp[2];
    tmp[0] =  (keypadsList[combinationUsed][shownSymbols[i]]);
    tmp[1] = '\0';

    EsploraTFT.text( tmp , KEYPADS_LEFT_PADDING + 7 +(i % 2 == 1 ? 1 : 0) * KEYPADS_KEY_SPREAD, KEYPADS_TOP_PADDING + 7 + (i > 1 ? 1 : 0) * KEYPADS_KEY_SPREAD );
  }
}

/**
 * @brief Functions that's called whenever user confirms its input
 *
 */

bool CKeypads::pushSymbol(){

  // Don't accept anymore incput if module is already solved
  if (solved)
      return true;

  if (checkCorrectSymbol(selectedKey)){
      solvedSymbols[selectedKey] = true;
      leftToSolve--;

      if (!leftToSolve){
          solved = true;
          EsploraTFT.fill(0,0,0);
          EsploraTFT.noStroke();
          EsploraTFT.rect (50, 5, 70, 10);
      }
      
      return true;
  }

  else{
      addError();
      return false;
  }
}

/**
 * @brief Function called by pushSymbols to check whether user selected correct symbol
 * 
 */

bool CKeypads::checkCorrectSymbol(int pos){

    bool returnFlag = true;

    if (solvedSymbols[pos] == true)
      return false;
    
    for (int i=0; i < KEYPADS_SHOWN_SYMBOLS_NMBR; i++){
        
        if (shownSymbols[pos] > shownSymbols[i] && solvedSymbols[i] == false){
            returnFlag = false;
        }
            
    }
    return returnFlag;
}

/**
 * @brief Functions for movement across displayed keypads
 * 
 */

void CKeypads::moveLeft(void){
    if (selectedKey == 0 || selectedKey == 1)
        selectedKey = 0;
    else if (selectedKey == 2 || selectedKey == 3)
        selectedKey = 2;
}

void CKeypads::moveRight(void){
    if (selectedKey == 0 || selectedKey == 1)
        selectedKey = 1;
    else if (selectedKey == 2 || selectedKey == 3)
        selectedKey = 3;
}

void CKeypads::moveDown(void){
    if (selectedKey == 0 || selectedKey == 2)
        selectedKey = 2;
    else if (selectedKey == 1 || selectedKey == 3)
        selectedKey = 3;
}

void CKeypads::moveUp(void){
    if (selectedKey == 0 || selectedKey == 2)
        selectedKey = 0;
    else if (selectedKey == 1 || selectedKey == 3)
        selectedKey = 1;
}
