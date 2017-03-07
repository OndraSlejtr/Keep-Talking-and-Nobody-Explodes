#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "CSerial.h"


/**
 * @brief CSerial class constructor
 *
 * @param Lets object know its position in the order of modules
 */

CSerial::CSerial (int posGiven){

  positionBomb = posGiven;
  solved = true;
  selectedSerial = random (0,6);
  
}

/**
 * @brief Function to check whether serial code contains vowel
 * 
 * Every odd combinations contains vowel.
 * 
 */

bool CSerial::hasVowel (void) {
    if (selectedSerial % 2)
      return false;
    else
      return true;
}

/**
 * @brief Function to check whether serial code's last number is odd
 *  
 */

bool CSerial::lastOdd  (void){
    if (selectedSerial == 0 || selectedSerial == 4 || selectedSerial == 5)
      return true;
    else
      return false;
}


/**
 * @brief Function that displays the entire module to user
 *
 */

void CSerial::showModule (void){

  EsploraTFT.stroke(255,255,255);
  EsploraTFT.setTextSize(2);
  EsploraTFT.text(serialNumberArray[selectedSerial], 25, 65);

}

bool CSerial::pushSymbol(){}



/**
 * @brief Functions for movement across displayed keypads
 * 
 *  No movement within this module
 */

void CSerial::moveLeft(void){}

void CSerial::moveRight(void){}

void CSerial::moveDown(void){}

void CSerial::moveUp(void){}

