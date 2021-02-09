/**\class MssmHbb MssmHbbAnalyser.cc Analysis/Tools/src/MssmHbbAnalyser.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roberval Walsh
//         Created:  Mon, 20 Oct 2014 14:24:08 GMT
//
//

// system include files
#include <iostream>
// 
// user include files
#include "Analysis/MssmHbb/interface/JetTriggerAnalyser.h"
#include "Analysis/Tools/interface/Composite.h"


//
// class declaration
//

using namespace analysis;
using namespace analysis::tools;
using namespace analysis::JTA;

//
// constructors and destructor
//
JetTriggerAnalyser::JetTriggerAnalyser()
{
}

JetTriggerAnalyser::JetTriggerAnalyser(int argc, char ** argv) : BaseAnalyser(argc,argv), Analyser(argc,argv)
{

   this->output()->cd();
   /*this->output()->mkdir("histogramsJKTE");
   this->output()->cd("histogramsJKTE");

   h1_["NumeratorJKTE"] = std::make_shared<TH1F>("NumeratorJKTE","Probes with matching", 30,0,300);
   h1_["ProbesJKTE"] = std::make_shared<TH1F>("ProbesJKTE","Probes", 30,0,300);
   h1_["JKTE"] = std::make_shared<TH1F>("JKTE","Jet Kinematic Trigger Efficiency", 30,0,300);*/

   this->jetHistograms(config_->nJetsMin(),"Probes with matching 0<n<1");
   this->jetHistograms(config_->nJetsMin(),"Probes 0<n<1");
   this->jetHistograms(config_->nJetsMin(),"Probes with matching 1<n<1.4");
   this->jetHistograms(config_->nJetsMin(),"Probes 1<n<1.4");
   this->jetHistograms(config_->nJetsMin(),"Probes with matching 1.4<n<2.2");
   this->jetHistograms(config_->nJetsMin(),"Probes 1.4<n<2.2");

}

JetTriggerAnalyser::~JetTriggerAnalyser()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   
   //if ( do_tree_ ) mssmhbb_tree_ -> Write();
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
    if ( selectedJets_[0]->eta() > 2.3 ) return false;
    if ( selectedJets_[1]->eta() > 2.3 ) return false;
    if ( selectedJets_[2])
         if ( selectedJets_[2]->pt() > (0.3*(selectedJets_[0]->pt()+selectedJets_[1]->pt())*0.5) ) return false;


    return true;
}


void JetTriggerAnalyser::jetKTEtagandprobeSelection()
{
    // kinematics selection
    if ( ! this->selectionJet(1)          )   return;
    if ( ! this->onlineJetMatching(1)     )   return;
    
    //this->fillJetHistograms("Probes");
     
    if (selectedJets_[1]->eta()>0 && selectedJets_[1]->eta()<=1.)
    this->fillJetHistograms("Probes 0<n<1");
    if (selectedJets_[1]->eta()>1. && selectedJets_[1]->eta()<=1.4)
    this->fillJetHistograms("Probes 1<n<1.4");
    if (selectedJets_[1]->eta()>1.4 && selectedJets_[1]->eta()<=2.2)
    this->fillJetHistograms("Probes 1.4<n<2.2");
    
/*
    this->output()->cd();
    this->output()->cd("histogramsJKTE");     
    h1_["ProbesJKTE"] -> Fill(selectedJets_[1]->pt()); 
*/

    // kinematics selection for numerator
    if ( ! this->selectionJet(2)          )   return;
    if ( ! this->onlineJetMatching(2)     )   return;

    //now fill numerator histogram
    
    //this->fillJetHistograms("Probes with matching");

     
    if (selectedJets_[1]->eta()>0 && selectedJets_[1]->eta()<=1.)
    this->fillJetHistograms("Probes with matching 0<n<1");
    if (selectedJets_[1]->eta()>1. && selectedJets_[1]->eta()<=1.4)
    this->fillJetHistograms("Probes with matching 1<n<1.4");
    if (selectedJets_[1]->eta()>1.4 && selectedJets_[1]->eta()<=2.2)
    this->fillJetHistograms("Probes with matching 1.4<n<2.2");
    
/*
    this->output()->cd();
    this->output()->cd("histogramsJKTE");
    h1_["NumeratorJKTE"] -> Fill(selectedJets_[1]->pt());
*/

    return;
}


/*void JetTriggerAnalyser::jetKTE()
{
      // fill Jet Kinematic Trigger Efficiency Histograms
   // this->output()->cd();
   // this->output()->cd("histogramsJKTE");
    
    //h1_["JKTE"]->Divide(h1_["NumeratorJKTE"].get(),h1_["ProbesJKTE"].get(), 1,1,"B" );
    //TGraphAsymmErrors * g_eff = new TGraphAsymmErrors(h1_["NumeratorJKTE"].get(),h1_["ProbesJKTE"].get(),"cl=0.683 b(1,1) mode");
    //h1_["JKTE"]=g_eff.get();


    return;
}*/




