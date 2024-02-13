
//
//          Author:  Daina Leyva
//         Created:  Aug. 2021
//         Reviwed:  Feb. 2024
//
//

// system include files
#include <iostream>
#include <fstream>
// 
// user include files
#include "Analysis/Trigger/interface/MuonTriggerAnalyser.h"
#include "Analysis/Tools/interface/Composite.h"


//
// class declaration
//

using namespace analysis;
using namespace analysis::tools;
using namespace analysis::muontrigger;

//
// constructors and destructor
//
MuonTriggerAnalyser::MuonTriggerAnalyser()
{
}

MuonTriggerAnalyser::MuonTriggerAnalyser(int argc, char ** argv) : BaseAnalyser(argc,argv), Analyser(argc,argv)
{

   this -> output() -> cd();
   
}

MuonTriggerAnalyser::~MuonTriggerAnalyser()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   
}


//
// member functions
//
// ------------ method called for each event  ------------
bool MuonTriggerAnalyser::event(const int & i)
{
   // parent function checks only json and run range validity
   if ( ! Analyser::event(i) ) return false;
   
// PILEUP RE-WEIGHT
   this->actionApplyPileupWeight(); 
   
   return true;
}



bool MuonTriggerAnalyser::muonsSelection()
{
    TLorentzVector m1,m2,m;
    double DiMuonMassObtained;
    double JPsiMass = 3.1;	 //GeV
    double MassWindow = 0.2;     //GeV
    int q1, q2;
    
    if ( ! this -> selectionMuonId()                             )   return false; // check if event has muons
    if ( ! this -> selectionMuons()                              )   return false; // selection of the 2 leading muons according to nminMuons, ptmax, ptmin and etamax from config file
    if (selectedMuons_[0] -> deltaR(*selectedMuons_[1]) < 0.1    )   return false; // check deltaR between 2 leading muons
    
    //Discriminate two muons with same charge and that their sum is outside J/Psi mass window
    for ( int i = 0; i < config_ -> nMuonsMin(); i++ )
    {
        for ( int j = i+1 ; j < config_->nMuonsMin(); j++ )
        {
            m1 = selectedMuons_[i] -> p4();
            m2 = selectedMuons_[j] -> p4();
            q1 = selectedMuons_[i] -> q();
            q2 = selectedMuons_[j] -> q();

	    if (q1 == q2)  // check if the muons have opposite charges
            return false;

            m = m1+m2;
            DiMuonMassObtained = m.M();
            
            if (fabs(DiMuonMassObtained-JPsiMass) > MassWindow) //see if sum inside J/Psi mass window
            return false;
        }
    }

    return true;
}

bool MuonTriggerAnalyser::muonTagsSelection()
{
    TLorentzVector m1_afterTagSelection, m2_afterTagSelection, m_afterTagSelection; //reconstructed mass after tag selection
    double MassObtained;

    //matching of tag muon to online object and kinematic selection
    if ( ! onlineL1MuonMatching(1) )        return false;          //check tags L1 online matching 
    if ( ! onlineL3MuonMatching(1) )        return false;          //check tags L3 online matching 
    if ( selectedMuons_[0] -> pt() < 10 )   return false;          //pt condition for tags

    for ( int i = 0; i < config_->nMuonsMin(); i++ ) //loop to fill histogram after tag selection
    {
        for ( int j = i+1 ; j < config_->nMuonsMin(); j++ )
        {
            m1_afterTagSelection = selectedMuons_[i] -> p4();
            m2_afterTagSelection = selectedMuons_[j] -> p4();
            m_afterTagSelection = m1_afterTagSelection + m2_afterTagSelection;
            MassObtained = m_afterTagSelection.M();

            DiMuonMass_afterTagSelection -> Fill (MassObtained); //filling histograms with counts of the Jpsi muons resulting after the tag selection
        }
    }

    TagsPt -> Fill (selectedMuons_[0]->pt()); //filling histogram of Tag's pt

    return true;
}

void MuonTriggerAnalyser::reconstructJPsi()
{
    TLorentzVector m1matched, m2matched, mmatched; //reconstructed mass after probes selection, from passing probes
    TLorentzVector m1failedmatched,m2failedmatched,mfailedmatched; //reconstructed mass after probes selection, from failing probes
    double matchedDiMuonMassObtained;
    double failedmatchedDiMuonMassObtained;


    if (onlineL1MuonMatching(2) && onlineL3MuonMatching(2))//Passing condition
    {
       for ( int i = 0; i < config_->nMuonsMin(); i++ ) //loop to fill histograms
       {
          for ( int j = i+1 ; j < config_->nMuonsMin(); j++ )
          {
             m1matched = selectedMuons_[i] -> p4();
             m2matched = selectedMuons_[j] -> p4();
             mmatched = m1matched+m2matched;
             matchedDiMuonMassObtained = mmatched.M();

             PassedDiMuonMass_vs_probespT -> Fill (matchedDiMuonMassObtained, selectedMuons_[j] -> pt());
          }
       }

       PassedProbesPt -> Fill (selectedMuons_[1]->pt()); //filling histogram of Passing Probe's pt
    }


    else //failing condition
    {
       for ( int i = 0; i < config_->nMuonsMin(); i++ ) //loop to fill histograms
       {
          for ( int j = i+1 ; j < config_->nMuonsMin(); j++ )
          {
             m1failedmatched = selectedMuons_[i] -> p4();
             m2failedmatched = selectedMuons_[j] -> p4();
             mfailedmatched = m1failedmatched+m2failedmatched;
             failedmatchedDiMuonMassObtained = mfailedmatched.M();

             FailedDiMuonMass_vs_probespT -> Fill (failedmatchedDiMuonMassObtained, selectedMuons_[j] -> pt());
          }
       }

             
       FailedProbesPt -> Fill (selectedMuons_[1]->pt()); //filling histogram of Failing Probe's pt
    }

}



