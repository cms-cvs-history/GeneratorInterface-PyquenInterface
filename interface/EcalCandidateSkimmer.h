#ifndef _HI_EcalCandSkimmer_h__
#define _HI_EcalCandSkimmer_h__

#include "GeneratorInterface/PyquenInterface/interface/BaseHiGenSkimmer.h"

class EcalCandidateSkimmer : public BaseHiGenSkimmer {
 public:
   EcalCandidateSkimmer(const edm::ParameterSet& pset) : BaseHiGenSkimmer(pset){;}
   virtual ~EcalCandidateSkimmer(){;}

   bool filter(HepMC::GenEvent *);

};

#endif
