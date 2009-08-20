#include <iostream>
#include "GeneratorInterface/PyquenInterface/interface/EcalCandidateSkimmer.h"

bool EcalCandidateSkimmer::filter(HepMC::GenEvent *){
   std::cout<<"Ecal Fired"<<std::endl;
   return false;
}
