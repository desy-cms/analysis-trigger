#include "Analysis/Tools/interface/Analyser.h"

using namespace std;
using namespace analysis;
using namespace analysis::tools;

int main(int argc, char ** argv)
{
   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
   Analyser analyser(argc,argv);
   auto config = analyser.config();
   auto analysis = analyser.analysis(); // that's the usual Analysis class
   
   // histograms
   analyser.l1tjetHistograms("initial");
   analyser.l1tjetHistograms("muon_jet");
   analyser.l1tjetHistograms("dijet");
   analyser.l1tjetHistograms("final");
   

   auto vfloat = analyser.config()->vectorFloat();
   auto vint = analyser.config()->vectorInt();
         
   // selection
   auto jet_ptX  = vfloat[0];
   auto jet_etaX = vfloat[1];
   auto jet_ptY  = vfloat[2];
   auto jet_etaY = vfloat[3];
   auto jet_deta = vfloat[4];
   auto mu_pt    = vfloat[5];
   auto mu_eta   = vfloat[6];
   auto mu_jet_dr = vfloat[7];
   
   auto jet_nmin = vint[0];
   auto mu_nmin = vint[1];
   auto mu_qual = vint[2];
   
   for ( int i = 0 ; i < analyser.nEvents() ; ++i )
   {
      if ( ! analyser.event(i) ) continue;
      
      // histograms
      analyser.fillL1TJetHistograms("initial");

// muon in jet
      if ( ! analyser.selectionL1TJet(jet_ptY, jet_etaY) ) continue;
      // muon
      if ( ! analyser.selectionNL1TMuons(1) ) continue;      
      if ( ! analyser.selectionL1TMuon(mu_pt, mu_eta) ) continue;
      if ( ! analyser.selectionL1TMuonQuality(mu_qual) ) continue;
      // muon in jet
      if ( ! analyser.selectionL1TMuonJet(mu_jet_dr) ) continue;
      // histograms
      analyser.fillL1TJetHistograms("muon_jet");

// dijet      
      // kinematics
      if ( ! analyser.selectionL1TDijet(jet_ptY, jet_etaY) ) continue;
      // delta_eta
      if ( ! analyser.selectionL1TDijetDeta(jet_deta) ) continue;
      // histograms
      analyser.fillL1TJetHistograms("dijet");
      // dijet asymmetric
      if ( ! analyser.selectionL1TDijet(jet_ptX, jet_etaX, jet_ptY, jet_etaY) ) continue;
      
      // histograms
      analyser.fillL1TJetHistograms("final");
   }
   
   return 0;
}
