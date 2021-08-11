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
   analyser.l1tjetHistograms(2,"initial");
   analyser.l1tjetHistograms(2,"final");
   

   auto vfloat = analyser.config()->vectorFloat();
   auto vint = analyser.config()->vectorInt();
         
   // selection
   auto jet_ptX  = vfloat[0];
   auto jet_etaX = vfloat[1];
   auto jet_ptY  = vfloat[2];
   auto jet_etaY = vfloat[3];
   auto jet_deta = vfloat[4];
   auto jet_nmin = vint[0];
   
   for ( int i = 0 ; i < analyser.nEvents() ; ++i )
   {
      if ( ! analyser.event(i) ) continue;
      
      // min number of jets (must be 2)
      if ( ! analyser.selectionNL1TJets(2) ) continue;
      
      // histograms
      analyser.fillL1TJetHistograms("initial");
      // kinematics
      if ( ! analyser.selectionL1TDijet(jet_ptX, jet_etaX, jet_ptY, jet_etaY) ) continue;
      // delta_eta
      if ( ! analyser.selectionL1TDijetDeta(jet_deta) ) continue;
      
      // histograms
      analyser.fillL1TJetHistograms("final");
   }
   
   return 0;
}
