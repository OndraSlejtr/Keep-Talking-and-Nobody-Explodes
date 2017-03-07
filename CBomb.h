#ifndef CBOMB_H
#define CBOMB_H

#include "CModule.h"
#include "CKeypads.h"
#include "CSerial.h"
#include "CWires.h"
#include "CSimonSays.h"
#include "Controls.h"

// *****************************************************************************************
//  Class that initializes the bomb itself and contains all required modules
// *****************************************************************************************

class CBomb {
    public:
        CBomb (int moduleAmount, int timeLeft);
        ~CBomb (void);

        void listLeft       (void);
        void listRight      (void);
        void showBomb       (void);
        bool isSolved       (void) const;
        void detonateBomb   (void);
        void showSolvedBomb (void);

        CModule ** moduleList;          // Pointer to array of modules dynamically included in the bomb
        CModule * currentModule;        // Pointer to currently selected module within moduleList array

        int currentlyShown;             // ID of currently shown bomb
        int timeExplosion;

    private:
        int moduleAmount;
        bool vowelSerial;
};

#endif // CBOMB_H
