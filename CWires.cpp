#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "CWires.h"


/**
 * @brief CWires class constructor
 *
 * @param Lets object know its position in the order of modules
 */

CWires::CWires (int posGiven, bool odd){

  wiresAmount = random (WIRES_MIN_AMOUNT, WIRES_MAX_AMOUNT+1);
  positionBomb = posGiven;
  selectedWire = 0;
  solved = false;
  oddSerial = odd;

  for (int i=0; i < 10; i++)                   
    shownWires[i] = 0;

  for (int i=0; i < wiresAmount; i++)                   
    shownWires[i] = random (0, WIRES_COLOR_USED);
}


/**
 * @brief Functions to select correct drawing color
 *
 * @param Code of color ot be drawn
 */

void CWires::drawWireColor (int color){
    switch (color){
    case 0 :    // red
      EsploraTFT.fill(255,0,0);
      break;
    case 1 :    // green
      EsploraTFT.fill(0,255,0);
      break;
    case 2 :    // yellow
      EsploraTFT.fill(255,255,0);
      break;
    case 3 :    // blue
      EsploraTFT.fill(0,0,255);
      break;
   }
}



/**
 * @brief Function that displays the entire module to user
 *
 */

void CWires::showModule (void){
/*
    for (int i=0; i < wiresAmount; i++ ){        
      char tmp[5];
      sprintf (tmp, "%d", shownWires[i]);
      EsploraTFT.text(tmp, 1, 40 + 14*i);
    }
*/
    char tmp[5];
      sprintf (tmp, "%d", oddSerial);
      EsploraTFT.text(tmp, 1, 40);
    
    for (int i=0; i < wiresAmount; i++ ){
      if (selectedWire == i)
        EsploraTFT.stroke(255,255,255);
      else
        EsploraTFT.noStroke();
        
      drawWireColor (shownWires[i]);
      EsploraTFT.rect(25, 30 + 14*i, 110, 5);
    }
}


/**
 * @brief Functions that's called whenever user confirms its input
 *
 */

bool CWires::pushSymbol(){
  if ( checkCorrectSymbol (selectedWire) ){
    solved = true;
    EsploraTFT.fill(0,0,0);
    EsploraTFT.noStroke();
    EsploraTFT.rect (50, 5, 70, 10);
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

bool CWires::checkCorrectSymbol(int pos){
  switch (wiresAmount){
    case 3 :
      return checkWires3 (pos);
    case 4 :
      return checkWires4 (pos);
    case 5 :
      return checkWires5 (pos);
    case 6 :
      return checkWires6 (pos);
  }
}


/**
 * @brief Function called by checkCorrectSymbol to find out whether selected wire is correct choice for total of 3 wires shown.
 * 
 * @param Position of cut wire.
 */

bool CWires::checkWires3 (int pos) const{

  bool flag = true;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == 0)
      flag = false;

  int blueCount = 0;
  int lastBlue = -1;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == 3){
      blueCount++;
      lastBlue = i;
    }
      
  // If there are no red wires, cut the second wire.

  if (flag){
    if (pos == 1)
      return true;
    else 
      return false;
  }

  // Otherwise, if the last wire is green, cut the last wire.
  else if (shownWires [wiresAmount-1] == 1){
    if ( pos == wiresAmount-1 )
      return true;
    else
      return false;
  }
  
  // Otherwise, if there is more than one blue wire, cut the last blue wire.


  else if (blueCount > 1){
    if (pos == lastBlue)
      return true;
    else
      return false;
  }

  // Otherwise, cut the last wire.
  else if (pos == wiresAmount-1)
    return true;
  else
    return false;

}


/**
 * @brief Function called by checkCorrectSymbol to find out whether selected wire is correct choice for total of 4 wires shown.
 * 
 * @param Position of cut wire.
 */

bool CWires::checkWires4 (int pos) const{

  int yellowCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == 0)
      yellowCount++;

  int redCount = 0;
  int lastRed = -1;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == 0){
      redCount++;
      lastRed = i;
    }

  bool flag = true;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == 0)
      flag = false;

  int blueCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == 3)
      blueCount++;
    

  // If there is more than one red wire and the last digit of the serial number is odd, cut the last red wire.


  if (redCount > 1 && oddSerial ){
    if (pos == lastRed)
      return true;
    else
      return false;
  }
  
  // Otherwise, if the last wire is yellow and there are no red wires, cut the first wire.

      
  else if (flag && shownWires[wiresAmount-1] == 2){
    if (pos == 0)
      return true;
    else
      return false;
  }
  
  // Otherwise, if there is exactly one blue wire, cut the first wire.

  else if (blueCount == 1){
    if (pos == 0)
      return true;  
    else
      return false; 
  }
  
  // Otherwise, if there is more than one yellow wire, cut the last wire.

  else if (yellowCount > 1){
    if (pos == wiresAmount - 1)
      return true;
    else
      return false;
  }
  
  // Otherwise, cut the second wire.
  else if (pos == 1)
    return true;
  else
    return false;
  
}


/**
 * @brief Function called by checkCorrectSymbol to find out whether selected wire is correct choice for total of 5 wires shown.
 * 
 * @param Position of cut wire.
 */

bool CWires::checkWires5 (int pos) const{

  int redCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == SIMON_RED)
      redCount++;

  int yellowCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == SIMON_YELLOW)
      yellowCount++;

  int greenCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == SIMON_GREEN)
      greenCount++;
  
// If the last wire is green and the last digit of the serial number is odd, cut the fourth wire.
  if ( shownWires[wiresAmount-1] == SIMON_GREEN && oddSerial ){
    if (pos == 3)
      return true;
    else
      return false;
  }


// Otherwise, if there is exactly one red wire and there is more than one yellow wire, cut the first wire.


  else if ( redCount == 1 && yellowCount > 1 ){
    if (pos == 0)
      return true;
    else
      return false;
  }


// Otherwise, if there are no green wires, cut the second wire.

  else if ( greenCount == 0 ){
    if (pos == 1)
      return true;
    else
      return false;
  }

// Otherwise, cut the first wire.

  else if (pos == 0)
    return true;
  else
    return false;


}


/**
 * @brief Function called by checkCorrectSymbol to find out whether selected wire is correct choice for total of 6 wires shown.
 * 
 * @param Position of cut wire.
 */

bool CWires::checkWires6 (int pos) const{
  

  int yellowCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == SIMON_YELLOW)
      yellowCount++;

  int blueCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == SIMON_BLUE)
      blueCount++;

  int redCount = 0;
  for (int i = 0; i < wiresAmount; i++)
    if (shownWires [i] == SIMON_RED)
      redCount++;

// If there are no yellow wires and the last digit of the serial number is odd, cut the third wire.
      
  if ( yellowCount == 0 && oddSerial ){
    if (pos == 2)
      return true;
    else
      return false;
  }


// Otherwise, if there is exactly one yellow wire and there is more than one blue wire, cut the fourth wire.

  else if ( yellowCount == 1 && blueCount > 1 ){
    if (pos == 3)
      return true;
    else
      return false;
  }

// Otherwise, if there are no red wires, cut the last wire.

  else if ( redCount == 0 ){
    if (pos == 5)
      return true;
    else
      return false;
  }

// Otherwise, cut the fourth wire.

  else if (pos == 3)
    return true;
  else
    return false;
  
}


/**
 * @brief Functions for movement across displayed keypads
 * 
 */

 // No movement left within this module
void CWires::moveLeft(void){}

 // No movement right within this module
void CWires::moveRight(void){}

void CWires::moveDown(void){
  selectedWire++;
  if (selectedWire > wiresAmount-1)
    selectedWire--;
}

void CWires::moveUp(void){
  selectedWire--;
  if (selectedWire < 0)
    selectedWire++;
}

