#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "CSimonSays.h"


/**
 * @brief Functions for movement across displayed keypads
 * 
 * @param Lets object know its position in the order of modules
 * @param Gives information about vowel inclusion with bombs's serial number in order to pick correct color combination
 */

CSimonSays::CSimonSays(int posGiven, bool vowel){
  selectedKey = 0;
  currentOrderKey = 0;
  lastSelectedKey = -1;                     // Flag variable that calls to draw all Keys at the beginning
  progress = 0;
  positionBomb = posGiven;
  needToShow = true;
  combinationUsed = /*strikes +*/ 3*(vowel);    // Use combinations 1-3 if there is no vowel within bomb serial code, 4-6 in case there are. One of these 3 is picked based on amount of collected strikes.

  for (int i=0; i < SIMON_SAYS_BLINKS; i++)
      blinkOrder[i] = random(0,4);
}

/**
 * @brief Functions to pick correct color for drawing
 * 
 * @param Takes ID of colow to be drawn.
 */

void CSimonSays::drawColor (int color) const{
  switch (color){
    case 0 :
      EsploraTFT.fill(0,0,255);
      break;
    case 1 :
      EsploraTFT.fill(255,0,0);
      break;
    case 2 :
      EsploraTFT.fill(255,255,0);
      break;
    case 3 :
      EsploraTFT.fill(0,255,0);
      break;
   }
}

/**
 * @brief Function that's called whenever user needs to be given clue as to how progress further within sequence
 * 
 */

void CSimonSays::blinkKeys(void){
  
  int drawTime = millis ();
  int nextDrawTime = drawTime;


  Serial.println(strikes+combinationUsed);

  // Keep drawing colored squares based on order specified within blinkOrder
  for (int i = 0; i <= progress; i++){
    switch (simonSaysList[strikes+combinationUsed][blinkOrder[i]]){
    case 0 :
      EsploraTFT.fill(0,191,255);
      break;
    case 1 :
      EsploraTFT.fill(255,153,153);
      break;
    case 2 :
      EsploraTFT.fill(255,255,153);
      break;
    case 3 :
      EsploraTFT.fill(153,255,153);
      break;
    }

    // Draw "blinking" button for a short period
    EsploraTFT.rect(SIMON_LEFT_PADDING+(simonSaysList[strikes+combinationUsed][blinkOrder[i]] % 2 == 1 ? 1 : 0) * SIMON_SPREAD, SIMON_TOP_PADDING + (simonSaysList[strikes+combinationUsed][blinkOrder[i]] > 1 ? 1 : 0) * SIMON_SPREAD, SIMON_KEY_SIZE, SIMON_KEY_SIZE);

    drawTime = millis ();
    nextDrawTime = drawTime + 600;  

    while (drawTime < nextDrawTime){
      if (buttonEvent(LEFT) || buttonEvent(RIGHT)) 
        goto exit;
      drawTime = millis ();
    }

    // Redraw button with original color to simulate blinking
    drawColor (simonSaysList[strikes+combinationUsed][blinkOrder[i]]);      
    EsploraTFT.rect(SIMON_LEFT_PADDING+(simonSaysList[strikes+combinationUsed][blinkOrder[i]] % 2 == 1 ? 1 : 0) * SIMON_SPREAD, SIMON_TOP_PADDING + (simonSaysList[strikes+combinationUsed][blinkOrder[i]] > 1 ? 1 : 0) * SIMON_SPREAD, SIMON_KEY_SIZE, SIMON_KEY_SIZE);

    drawTime = millis ();
    nextDrawTime = drawTime + 600;  

    while (drawTime < nextDrawTime){
      if (buttonEvent(LEFT) || buttonEvent(RIGHT)) 
        goto exit;
      drawTime = millis ();
    }
  
    
  }
  needToShow = false;  
  exit: 
    return;    
}

/**
 * @brief Functions for movement across displayed keypads
 * 
 */

void CSimonSays::moveLeft(void){
  lastSelectedKey = selectedKey;
  if (selectedKey == 0 || selectedKey == 1)
    selectedKey = 0;
  else if (selectedKey == 2 || selectedKey == 3)
    selectedKey = 2;
}

void CSimonSays::moveRight(void){
  lastSelectedKey = selectedKey;
  if (selectedKey == 0 || selectedKey == 1)
    selectedKey = 1;
  else if (selectedKey == 2 || selectedKey == 3)
    selectedKey = 3;
}

void CSimonSays::moveDown(void){
  lastSelectedKey = selectedKey;
  if (selectedKey == 0 || selectedKey == 2)
    selectedKey = 2;
  else if (selectedKey == 1 || selectedKey == 3)
    selectedKey = 3;
}

void CSimonSays::moveUp(void){
  lastSelectedKey = selectedKey;
  if (selectedKey == 0 || selectedKey == 2)
    selectedKey = 0;
  else if (selectedKey == 1 || selectedKey == 3)
    selectedKey = 1;
}



void CSimonSays::showModule (void){
     
  if (lastSelectedKey == -1)  // If we switch screens, make sure to show user proper blink order clue again
    needToShow = true;

  // Placeholder: display solution
  EsploraTFT.setTextSize(1);
  for (int i=0; i < SIMON_SAYS_BLINKS; i++){
    char tmp [2];
    tmp [0] = blinkOrder[i] + '0';
    tmp [1] = '\0';
    EsploraTFT.text( tmp , 5 + 10*i, 120 );
  }
  EsploraTFT.setTextSize(2);
  // END Placeholder
  
  EsploraTFT.noStroke();

  // Draw 4 background squares, with their color depending on whether they are behind currently selected square to simulate thicker border
  for (int i=0; i < SIMON_SAYS_PADS_SHOWN; i++){
    if (i == selectedKey && i != lastSelectedKey){
      EsploraTFT.fill(255,255,255);
      EsploraTFT.rect(SIMON_LEFT_PADDING - SIMON_BORDER + (i % 2 == 1 ? 1 : 0) * SIMON_SPREAD, SIMON_TOP_PADDING - SIMON_BORDER + (i > 1 ? 1 : 0) * SIMON_SPREAD, SIMON_KEY_SIZE + SIMON_BORDER * 2, SIMON_KEY_SIZE + SIMON_BORDER * 2);
    }
    else if (i == lastSelectedKey && i != selectedKey) {
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(SIMON_LEFT_PADDING - SIMON_BORDER + (i % 2 == 1 ? 1 : 0) * SIMON_SPREAD, SIMON_TOP_PADDING - SIMON_BORDER + (i > 1 ? 1 : 0) * SIMON_SPREAD, SIMON_KEY_SIZE + SIMON_BORDER * 2, SIMON_KEY_SIZE + SIMON_BORDER * 2);
    }

    // Finally draw the square itself on top of "border"
    drawColor (i);
    if ( (i == selectedKey && i != lastSelectedKey) || (i == lastSelectedKey && i != selectedKey) || lastSelectedKey == -1)
      EsploraTFT.rect(SIMON_LEFT_PADDING + (i % 2 == 1 ? 1 : 0) * SIMON_SPREAD, SIMON_TOP_PADDING + (i > 1 ? 1 : 0) * SIMON_SPREAD, SIMON_KEY_SIZE, SIMON_KEY_SIZE);
   
  }

  if (needToShow && !solved)
      blinkKeys ();

}

/**
 * @brief Functions that's called whenever user confirms its input
 *
 */

bool CSimonSays::pushSymbol (void){

  // Don't accept anymore incput if module is already solved
  if (solved)
    return true;

  // Check whether user inputed correct symbol in sequence
  if (selectedKey == blinkOrder[currentOrderKey]){
    currentOrderKey++;

    // If I've reached end of sequence shown thus far, push me further in progress and make module give visual clue again
    if ( progress == currentOrderKey - 1 ){
      needToShow = true;
      progress++;
      currentOrderKey = 0;
    }

    // If we've reached end of sequence, mark module as solved
    if (progress == SIMON_SAYS_BLINKS){
      solved = true;
      needToShow = false;
      EsploraTFT.fill(0,0,0);
      EsploraTFT.noStroke();
      EsploraTFT.rect (50, 5, 70, 10);
    }
    return true;
  }
  else{
      addError();
      currentOrderKey = 0;
      progress = 0;
      needToShow = true;

      EsploraTFT.fill(0,0,0);
      EsploraTFT.noStroke();
      EsploraTFT.rect (5, 120, 60, 10);
      for (int i=0; i < SIMON_SAYS_BLINKS; i++)
        blinkOrder[i] = random(0,4);
        
      return false;
  }
}
