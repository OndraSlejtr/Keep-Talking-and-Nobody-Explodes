#ifndef CONSTANTS_H
#define CONSTANTS_H

// *****************************************************************************************
//  List of constants initializing various key components of program 
// *****************************************************************************************

#define BOMB_START_TIMER_MIN  300
#define BOMB_START_TIMER_MAX  540
#define BOMB_START_MODULE_AMOUNT_MIN  3
#define BOMB_START_MODULE_AMOUNT_MAX  10 

#define MAXIMUM_STRIKES_ALLOWED 3    

#define KEYPADS_SHOWN_SYMBOLS_NMBR 4 
#define KEYPADS_LIST_SIZE 8

// Constants for display options within Keypads module
#define KEYPADS_LEFT_PADDING  37  
#define KEYPADS_TOP_PADDING   25  
#define KEYPADS_KEY_SIZE      40
#define KEYPADS_KEY_SPREAD    50

#define SIMON_SAYS_COMBINATIONS 3
#define SIMON_SAYS_PADS_SHOWN 4
#define SIMON_SAYS_BLINKS 5

// Keywords for possible color combinations
#define SIMON_BLUE      0
#define SIMON_RED       1
#define SIMON_YELLOW    2
#define SIMON_GREEN     3

// Constants for display options within SimonSays module
#define SIMON_KEY_SIZE      35
#define SIMON_TOP_PADDING   30
#define SIMON_LEFT_PADDING  40
#define SIMON_SPREAD        44  
#define SIMON_BORDER        2

// Constants for display options within Wires module
#define WIRES_MAX_AMOUNT  6
#define WIRES_MIN_AMOUNT  3
#define WIRES_COLOR_USED  4



/*static const char keypadsListArray0[] = {'A','B','C','D','E','F','G','H'};
static const char keypadsListArray1[] = {'I','J','K','L','M','N','O','P'};
static const char keypadsListArray2[] = {'Q','R','S','T','U','V','W','X'};*/

// Array of possible symbol combinations for Keypads module
static const char keypadsListArray0[] = {'!','"','#','<','|','m','*','P'};
static const char keypadsListArray1[] = {'/',':','h','$','>','=','?','d'};
static const char keypadsListArray2[] = {'X','&','+','^','_','%','Q','~'};

static const char keypadsListArray3[] = {'%','7','_','#','+',':','A','<'};  // : < A # h     m9sto X ~ Q ^ &
static const char keypadsListArray4[] = {'_','~','h','$','>','&','9','E'};  // ~ 9 & E _     misto = ? : d /
static const char keypadsListArray5[] = {'^','&','G','/','.','0','=','~'};  // . = G / 0     misto _ Q + X %

// Array with pointers to possible Keypads combinations
static const char * keypadsList[] = {&keypadsListArray0[0], &keypadsListArray1[0], &keypadsListArray2[0],
                                     &keypadsListArray3[0], &keypadsListArray4[0], &keypadsListArray5[0]};


// Arrays with combinations for Simon Says
struct TColor{
    short r;
    short g;
    short b;
};
                                        // blue     red         yellow      green
static const struct TColor simonSaysColors[] = {{0,0,255}, {255,0,0}, {255,255,0}, {0,255,0}};

// No vowels in serial number, based on amount of strikes
static const int simonSaysCombination0[] = {SIMON_RED,SIMON_BLUE,SIMON_GREEN,SIMON_YELLOW};
static const int simonSaysCombination1[] = {SIMON_GREEN,SIMON_YELLOW,SIMON_RED,SIMON_BLUE};
static const int simonSaysCombination2[] = {SIMON_RED,SIMON_GREEN,SIMON_BLUE,SIMON_YELLOW};

// Vowel in serial number, based on amount of strikes
static const int simonSaysCombination3[] = {SIMON_YELLOW,SIMON_BLUE,SIMON_RED,SIMON_GREEN};
static const int simonSaysCombination4[] = {SIMON_BLUE,SIMON_RED,SIMON_YELLOW,SIMON_GREEN};
static const int simonSaysCombination5[] = {SIMON_GREEN,SIMON_YELLOW,SIMON_RED,SIMON_BLUE};


static const int * simonSaysList[] = {&simonSaysCombination0[0], &simonSaysCombination1[0], &simonSaysCombination2[0], 
                                      &simonSaysCombination3[0], &simonSaysCombination4[0], &simonSaysCombination5[0]};


// Serial numbers
static const char serialNumberArray[][10] = {{"vZ2W3M1T"},{"ttugNhyd"},{"tVzCS48q"},{"0jiCsaST"},{"1gcpZ5ZX"},{"j3nASrmR"}};
#endif // CONSTANTS_H
