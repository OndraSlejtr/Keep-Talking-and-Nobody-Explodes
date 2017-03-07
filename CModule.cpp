#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include "CModule.h"


// Static class variables that collect information about their common atributes
int CModule::amountOfModules = 0;
int CModule::strikes = 0;


/**
 * @brief Parent class constructor for each module
 * 
 */

CModule::CModule (){
    strikes = 0;
    amountOfModules++;
    solved = false;
}


/**
 * @brief Function to add error for all current modules 
 * 
 */
 
void CModule::addError (void){
    strikes++;
}

