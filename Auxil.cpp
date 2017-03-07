#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "Auxil.h"

/**
 * @brief Function to display menu to start a new game
 *
 *  
 *
 */

void showMenu (void) {

  eraseDisplay();
  Esplora.writeRGB(0,0,0);

  int timer = (map(Esplora.readSlider(), 0, 1023, BOMB_START_TIMER_MIN, BOMB_START_TIMER_MAX) / 10) * 10;
  int newTimer = timer;
  int moduleAmount = BOMB_START_MODULE_AMOUNT_MIN;
  int newModuleAmount = moduleAmount;


  // Print basic menu template
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.setTextSize(2);
  EsploraTFT.text("Create game", 10, 10);
  EsploraTFT.setTextSize(1);
  EsploraTFT.text("Module amount: ", 20, 35);
  EsploraTFT.text("Timer: <> use slider", 20, 65);
  EsploraTFT.text("Press UP to confirm.", 20, 110);

  // Transform int values from selected time limit and module amount into displayable char array
  char timeStr [5];
  sprintf (timeStr, "%d:%02d", newTimer / 60, newTimer % 60);
  EsploraTFT.text(timeStr, 80, 80);

  char moduleStr [5];
  sprintf (moduleStr, "%d", moduleAmount);
  EsploraTFT.text(moduleStr, 80, 50);

  
  // Start loop to read user's input until he decides to create a new game with picked settings
  while (true){

      // Check whether user moved slider enough to update displayed value - moving by tens of seconds
      newTimer = (map(Esplora.readSlider(), 0, 1023, BOMB_START_TIMER_MIN, BOMB_START_TIMER_MAX) / 10) * 10;
      if (newTimer >= timer+10 || newTimer <= timer-10){
        EsploraTFT.noStroke();
        EsploraTFT.fill(0,0,0);
        EsploraTFT.rect(80, 80, 40, 10);
        sprintf (timeStr, "%d:%02d", newTimer / 60, newTimer % 60);
        EsploraTFT.stroke(255,255,255);
        EsploraTFT.text(timeStr, 80, 80);
        timer = newTimer;
      }

      // Check whether user changed amount of required modules
      if (newModuleAmount != moduleAmount){
        EsploraTFT.noStroke();
        EsploraTFT.fill(0,0,0);
        EsploraTFT.rect(80, 50, 40, 10);
        sprintf (moduleStr, "%d", newModuleAmount);
        EsploraTFT.stroke(255,255,255);
        EsploraTFT.text(moduleStr, 80, 50);
        moduleAmount = newModuleAmount;
      }


      // Read user input to change amount of modules for newly created game
      if (Esplora.readJoystickY() > 250 && !joystickPressed ) {
        if (newModuleAmount - 1 >= BOMB_START_MODULE_AMOUNT_MIN)
          newModuleAmount--;
        joystickPressed = true;
      }
      if (Esplora.readJoystickY() < -250 && !joystickPressed ) {
        if (newModuleAmount + 1 <= BOMB_START_MODULE_AMOUNT_MAX)
          newModuleAmount++;
        joystickPressed = true;
      }
      if (Esplora.readJoystickX() < 250 && Esplora.readJoystickX() > -250 && Esplora.readJoystickY() < 250 && Esplora.readJoystickY() > -250){
         joystickPressed = false;
      }


      // Create new bomb if button UP is pressed
      if (buttonEvent(UP)) {  
        delete theBomb;   

          // Initialize random seed if this is first created bomb
          if (needToInit){   
              randomSeed(millis());
              needToInit = false;
          }
        createNewBomb (moduleAmount, timer);
        break;
      }
  }
}

/**
 * @brief Function to create a new bomb with given paramters
 *
 * @param Amount of modules for bomb to be created with
 * @param Time limit for the bomb
 */

void createNewBomb (int moduleAmount, int timer) {
  theBomb = new CBomb(moduleAmount, timer);
  timeLeft = theBomb->timeExplosion - (millis() / 1000);
  eraseDisplay();
  theBomb->showBomb();
}

/**
 * @brief Function to display remaining time before bomb explodes
 *
 *  
 *
 */

void displayTime (void) {

  // Check whether we need to redraw remaining time - we moved between screens or we still have time left and last show info is outdated
  if ( displayChange || timeLeft > 0 && timeLeft != theBomb->timeExplosion - (millis() / 1000)){
    EsploraTFT.noStroke();
    EsploraTFT.fill(0,0,0);
    EsploraTFT.rect(5, 5, 40, 10);
    EsploraTFT.setTextSize (1);
    timeLeft = ( theBomb->timeExplosion - (millis() / 1000) );
    char timeStr [10];
    sprintf (timeStr, "%d:%02d", timeLeft / 60, timeLeft % 60);

    // Draw remaining time in red if user is reaching the limit
    if (timeLeft < 30)
      EsploraTFT.stroke(255,0,0);
    else
      EsploraTFT.stroke(255,255,255);
    EsploraTFT.text(timeStr, 5, 5);
    displayChange = false;

    // Simulated timer ticking
    if (tickTock){
      Esplora.writeRed(5);
      tickTock = false;
    }
    else {
      Esplora.writeRed(0);
      tickTock = true;
    }
  }
}


/**
 * @brief Function to read user input during bomb defusal
 *
 *  Reads joystick movement and button presses.
 *  Joystick controls movement on the screen and potential confirmation of input.
 *  Buttons control displayed screen and allows user to end the game and call menu function to start a new game.
 *  
 */

void readInput (void) {


  // Joystick controls
  if (Esplora.readJoystickY() > 250 && !joystickPressed ) {
    joystickPressed = true;
    theBomb->currentModule->moveDown();
    theBomb->showBomb();
  }
  if (Esplora.readJoystickY() < -250 && !joystickPressed ) {
    joystickPressed = true;
    theBomb->currentModule->moveUp();
    theBomb->showBomb();
  }
  if (Esplora.readJoystickX() > 250 && !joystickPressed ) {
    joystickPressed = true;
    theBomb->currentModule->moveLeft();
    theBomb->showBomb();
  }
  if (Esplora.readJoystickX() < -250 && !joystickPressed) {
    joystickPressed = true;
    theBomb->currentModule->moveRight();
    theBomb->showBomb();
  }

  // Check whether Joystick has been released yet so user can continue moving on the screen
  if (Esplora.readJoystickX() < 250 && Esplora.readJoystickX() > -250 && Esplora.readJoystickY() < 250 && Esplora.readJoystickY() > -250){
     joystickPressed = false;
  }

  // If button is pressed, send confirmation to module
  if (Esplora.readJoystickButton() == LOW && !joystickButtonPressed) {
    joystickButtonPressed = true;
    theBomb->currentModule->pushSymbol();
    theBomb->showBomb();
  } 
  else if (Esplora.readJoystickButton() == HIGH){
    joystickButtonPressed = false;
  }

  // Button control: left lists to another module on the left
  if (buttonEvent(LEFT)) {
    eraseDisplay();
    theBomb->listLeft();
    theBomb->showBomb();
    displayChange = true;
  }
  
  // Button control: right lists to another module on the right
  if (buttonEvent(RIGHT)) {
    eraseDisplay();
    theBomb->listRight();
    theBomb->showBomb();
    displayChange = true;
  }

  // Button control: up ends current game and shows menu
  if (buttonEvent(UP)) {  
    showMenu();
  }

}


/**
 * @brief Function to check whether the bomb still has time left before explosion
 *
 *  If it has, it calls detonateBomb function and waits for user to start a new game.
 *
 */
 
void checkTime (void){
      
  if (timeLeft < 1 || theBomb->currentModule->strikes == MAXIMUM_STRIKES_ALLOWED){
    theBomb->detonateBomb();
    while (true){
      if (buttonEvent(UP)) {
        showMenu();      
        break;
      }      
    }
  }
}

/**
 * @brief Function to check whether the bomb hasn't been solved yet.
 *
 *  If it has, it calls showSolvedBomb function and waits for user to start a new game.
 *
 */

void checkSolved (void){

  if (theBomb->isSolved()){
    theBomb->showSolvedBomb();
    while (true){
      if (buttonEvent(UP)) {
        showMenu();        
        break;
      }      
    }
  }
}

