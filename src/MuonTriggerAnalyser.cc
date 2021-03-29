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
    double JPsiMass = 3.096;	 //GeV
    double MassWindow = 0.15;    //GeV
    int q1, q2;
    
    if ( ! this -> selectionMuonId()                 )   return false; // check if event has muons
    if ( ! this -> selectionMuons()                  )   return false; // selection of the two leading muons according to nminMuons, ptmax, ptmin and etamax from config file
    if ( ! selectedMuons_[0] -> isTightMuon()        )   return false; // check tight ID condition of the two leading muons 
    if ( ! selectedMuons_[1] -> isTightMuon()        )   return false; // check tight ID condition of the two leading muons 
    
    //Discriminate two muons with same charge and that they sum is outside J/Psi mass window
    for ( int i = 0; i < config_ -> nMuonsMin(); i++ )
    {
        for ( int j = i+1 ; j < config_->nMuonsMin(); j++ )
        {
            m1 = selectedMuons_[i] -> p4();
            m2 = selectedMuons_[j] -> p4();
            q1 = selectedMuons_[i] -> q();
            q2 = selectedMuons_[j] -> q();

	    if (q1 == q2)  // check if the muons have opposite charges
            {
	        //std::cout <<"EVENT NOT VALID q1 = q2"<<std::endl;
                return false;
            }

            m = m1+m2;
            DiMuonMassObtained = m.M();

            
            if (fabs(DiMuonMassObtained-JPsiMass) > MassWindow) //see if sum inside J/Psi mass window
            {
	        //std::cout <<"EVENT NOT VALID : |DiMuonMass - JPsiMass| > MassWindow"<<std::endl;
                return false;
            }

            //DiMuonMass -> Fill (DiMuonMassObtained); //filling histograms with counts of Jpsi muons
        }
    }

    return true;
}

bool MuonTriggerAnalyser::muonTagsSelection()
{
  //  if ( ! analysis_ -> match <Muon,TriggerObject> (selectedMuons_[1],config_ -> triggerObjectsL1Muons(),0.3) ) return;    //check tags L1 online matching 
  //  if ( ! analysis_ -> match <Muon,TriggerObject> (selectedMuons_[1],config_ -> triggerObjectsL3Muons(),0.3) ) return;    //check tags L3 online matching 

    TLorentzVector m1_afterTagSelection, m2_afterTagSelection, m_afterTagSelection;
    double MassObtained;

    if ( ! onlineL1MuonMatching(1) )        return false;          //check tags L1 online matching 
    if ( ! onlineL3MuonMatching(1) )        return false;          //check tags L3 online matching 
    if ( selectedMuons_[0] -> pt() < 10 )   return false;          //pt condition for tags

    for ( int i = 0; i < config_->nMuonsMin(); i++ ) //loop to fill histogram after tag selection
    {
        for ( int j = i+1 ; j < config_->nMuonsMin(); j++ )
        {
            m1_afterTagSelection = selectedMuons_[i] -> p4();
            m2_afterTagSelection = selectedMuons_[j] -> p4();
            m_afterTagSelection = m1_afterTagSelection+m2_afterTagSelection;
            MassObtained = m_afterTagSelection.M();

            DiMuonMass_afterTagSelection -> Fill (MassObtained); //filling histograms with counts of the Jpsi muons resulting after the tag selection
        }
    }

    TagsPt -> Fill (selectedMuons_[0]->pt()); //filling histogram of Tag's pt

    return true;
}

void MuonTriggerAnalyser::muonPassandFail_MatchingProbesSelection()
{
    TLorentzVector m1matched, m2matched, mmatched;
    TLorentzVector m1failedmatched,m2failedmatched,mfailedmatched;
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

             MatchedDiMuonMass -> Fill (matchedDiMuonMassObtained); //filling histograms with counts of the matched Jpsi muons 
                  
             if (selectedMuons_[1] -> pt() > 11.5 && selectedMuons_[1] -> pt() < 12.5)
             MatchedDiMuonMass_pTBin1 -> Fill (matchedDiMuonMassObtained);

             if (selectedMuons_[1] -> pt() > 12.5 && selectedMuons_[1] -> pt() < 13.5)
             MatchedDiMuonMass_pTBin2 -> Fill (matchedDiMuonMassObtained);

             if (selectedMuons_[1] -> pt() > 13.5 && selectedMuons_[1] -> pt() < 18.5)
             MatchedDiMuonMass_pTBin3 -> Fill (matchedDiMuonMassObtained);

             if (selectedMuons_[1] -> pt() > 18.5 && selectedMuons_[1] -> pt() < 30.)
             MatchedDiMuonMass_pTBin4 -> Fill (matchedDiMuonMassObtained);

          }
       }
       MatchedProbesPt -> Fill (selectedMuons_[1]->pt()); //filling histogram of Passing Probe's pt
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
  
             FailedMatchingDiMuonMass -> Fill (failedmatchedDiMuonMassObtained); //filling histograms with counts of the failed Jpsi muons 
 
             if (selectedMuons_[1] -> pt() > 11.5 && selectedMuons_[1] -> pt() < 12.5)
             FailedMatchingDiMuonMass_pTBin1 -> Fill (failedmatchedDiMuonMassObtained);

             if (selectedMuons_[1] -> pt() > 12.5 && selectedMuons_[1] -> pt() < 13.5)
             FailedMatchingDiMuonMass_pTBin2 -> Fill (failedmatchedDiMuonMassObtained);

             if (selectedMuons_[1] -> pt() > 13.5 && selectedMuons_[1] -> pt() < 18.5)
             FailedMatchingDiMuonMass_pTBin3 -> Fill (failedmatchedDiMuonMassObtained);

             if (selectedMuons_[1] -> pt() > 18.5 && selectedMuons_[1] -> pt() < 30.)
             FailedMatchingDiMuonMass_pTBin4 -> Fill (failedmatchedDiMuonMassObtained);
          }
       }
       FailedProbesPt -> Fill (selectedMuons_[1]->pt()); //filling histogram of Failing Probe's pt
    }

   return;
}



