#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "Constants.h"

#include "CBomb.h"
#include "CModule.h"
#include "CKeypads.h"
#include "CSimonSays.h"
#include "CWires.h"

#include "Controls.h"
#include "Auxil.h"

void setup() {
  
  delay (1000);

  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.setTextSize(2);

  Serial.begin(9600);

  //loadingScreen();
  showMenu();

}

void loop() {

    checkTime();
    checkSolved();
    displayTime();
    readInput();

}
