//
//          Author:  Daina Leyva
//         Created:  Aug. 2021
//         Reviwed:  Feb. 2024
//
//


// system include files
#include <iostream>
// 
// user include files
#include "Analysis/Trigger/interface/JetTriggerAnalyser.h"
#include "Analysis/Tools/interface/Composite.h"


//
// class declaration
//

using namespace analysis;
using namespace analysis::tools;
using namespace analysis::trigger;

//
// constructors and destructor
//
JetTriggerAnalyser::JetTriggerAnalyser()
{
}

JetTriggerAnalyser::JetTriggerAnalyser(int argc, char ** argv) : BaseAnalyser(argc,argv), Analyser(argc,argv)
{

   this->output()->cd();
}

JetTriggerAnalyser::~JetTriggerAnalyser()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   
}


//
// member functions
//
// ------------ method called for each event  ------------
bool JetTriggerAnalyser::event(const int & i)
{
   // parent function checks only json and run range validity
   if ( ! Analyser::event(i) ) return false;
   
// PILEUP RE-WEIGHT
   this->actionApplyPileupWeight(); 
   
   return true;
}


bool JetTriggerAnalyser::jetKTEfirstSelection()
{
    if ( ! this->selectionNJets()         )   return false;
    for ( int i = 1; i <= config_->nJetsMin(); ++i )
    {
        // delta R selection
        for ( int j = i+1; j <= config_->nJetsMin(); ++j )
            if ( ! this->selectionJetDr(i,j)      )   return false;
    }

    if ( selectedJets_[0]->deltaPhi(*selectedJets_[1]) < 2.4 ) return false;
    if ( fabs(selectedJets_[0]->eta()) > 2.3 ) return false;
    if ( fabs(selectedJets_[1]->eta()) > 2.3 ) return false;
    if ( selectedJets_[2])
         if ( selectedJets_[2]->pt() > (0.3*(selectedJets_[0]->pt()+selectedJets_[1]->pt())*0.5) ) return false;


    return true;
}


void JetTriggerAnalyser::jetKTEtagandprobeSelection()
{
    // kinematics selection for denominator
    if ( ! this->selectionJet(1)          )   return;
    if ( ! this->onlineJetMatching(1)     )   return;
    if ( ! this->selectionJet(2)          )   return;
    
    this->fillJetHistograms("Probes");

    // kinematics selection for numerator
    if ( ! this->onlineJetMatching(2)     )   return;

    //now fill numerator histogram
    
    this->fillJetHistograms("Probes with matching");


    return;
}





