#include "Analysis/Trigger/interface/JetTriggerAnalyser.h"

using namespace analysis;
using namespace analysis::tools;
using namespace analysis::JTA;

int main(int argc, char ** argv)
{
    TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms

    JetTriggerAnalyser JTA(argc,argv);

    for ( int i = 0 ; i < JTA.nEvents() ; ++i )
    {
        if ( ! JTA.event(i)                       )  continue;    // read event, run selection/json
        if ( ! JTA.triggerSelection()             )  continue;    // trigger
        if ( ! JTA.preselection()                 )  continue;    // preselection
        if ( ! JTA.jetCorrections()               )  continue;    // jet corrections
        if ( ! JTA.jetKTEfirstSelection()         )  continue;    // jet corrections
        JTA.jetKTEtagandprobeSelection();
    }
} // end main
     



