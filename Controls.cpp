#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "Controls.h"


/**
 * @brief Commonly used function to destroy all currently shown objects
 * 
 */
 
void eraseDisplay (void){
  EsploraTFT.noStroke();
  EsploraTFT.fill (0,0,0);
  EsploraTFT.rect (0,0,160,140);
}

/**
 * @brief Function to draw loading screen on bomb setup
 * 
 */

void loadingScreen (void){

  EsploraTFT.stroke(255,255,255);
  EsploraTFT.setTextSize(2);
  EsploraTFT.text("Keep talking", 10, 30);
  EsploraTFT.setTextSize(1);
  EsploraTFT.text("and nobody explodes", 20, 54);
  EsploraTFT.setTextSize(1);
  EsploraTFT.stroke(100,100,100);
  EsploraTFT.text("(hopefully)", 80, 110);
  delay (5000);
}


/**
 * @brief Function controlling button presses
 * 
 */

byte buttonFlag = 0;
bool buttonEvent(int button)
{
  switch(button)
  {
    case UP:
     if (Esplora.readButton(UP) == LOW)
     {
       buttonFlag |= 1;
     }
     else if (buttonFlag & 1)
     {
       buttonFlag ^= 1;
       return true;
     }
     break;
 
    case DOWN:
     if (Esplora.readButton(DOWN) == LOW)
     {
       buttonFlag |= 2;
     }
     else if (buttonFlag & 2)
     {
       buttonFlag ^= 2;
       return true;
     }
     break;
 
    case RIGHT:
     if (Esplora.readButton(RIGHT) == LOW)
     {
       buttonFlag |= 4;
     }
     else if (buttonFlag & 4)
     {
       buttonFlag ^= 4;
       return true;
     }
     break;
 
    case LEFT:
     if (Esplora.readButton(LEFT) == LOW)
     {
       buttonFlag |= 8;
     }
     else if (buttonFlag & 8)
     {
       buttonFlag ^= 8;
       return true;
     }
  }
   return false;
}

