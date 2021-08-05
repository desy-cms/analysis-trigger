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
   analyser.l1tjetHistograms(2,"intermediate");
   analyser.l1tjetHistograms(2,"final");
   

   auto vfloat = analyser.config()->vectorFloat();
   auto vint = analyser.config()->vectorInt();
         
   // selection
   auto jet_ptX  = vfloat[0];
   auto jet_etaX = vfloat[1];
   auto jet_ptY  = vfloat[2];
   auto jet_etaY = vfloat[3];
   
   for ( int i = 0 ; i < analyser.nEvents() ; ++i )
   {
      if ( ! analyser.event(i) ) continue;

      auto l1t_jets  = analyser.l1tJets();
      
      if ( l1t_jets.size() < 2 ) continue;
      
      analyser.fillL1TJetHistograms("initial");
      
      std::vector<std::shared_ptr<L1TJet> > double_jet;
      
      
      for ( size_t j = 0 ; j < l1t_jets.size() ; ++j )
      {
         auto l1j = l1t_jets.at(j);
         if ( l1j->pt() >= jet_ptY && fabs(l1j->eta()) <= jet_etaY )
         {
            double_jet.push_back(l1j);
         }
      }
      if ( double_jet.size() < 2 ) continue;
      analyser.fillL1TJetHistograms("intermediate",double_jet);
      
      auto l1j1 = l1t_jets.at(0);
      if ( !( l1j1->pt() >= jet_ptX && fabs(l1j1->eta()) <= jet_etaX ) ) continue;
      analyser.fillL1TJetHistograms("final",double_jet);
   }
   
   return 0;
}
