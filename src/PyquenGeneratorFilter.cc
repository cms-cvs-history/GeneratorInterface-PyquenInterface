#include "GeneratorInterface/PyquenInterface/interface/PyquenGeneratorFilter.h"

template <>
bool gen::PyquenGeneratorFilter::filter(Event& ev, EventSetup const& /* es */){

if ( !hadronizer_.getHeavyIonParameters(ev) ) return false;
   
if ( !hadronizer_.generatePartonsAndHadronize() ) return false;

//  this is "fake" stuff
// in principle, decays are done as part of full event generation,
// except for particles that are marked as to be kept stable
// but we currently keep in it the design, because we might want
// to use such feature for other applications
//
if ( !hadronizer_.decay() ) return false;
    
HepMC::GenEvent* event = hadronizer_.getGenEvent();
if( !event ) return false; 

// The external decay driver is being added to the system,
// it should be called here
//
if ( decayer_ ) 
{
   event = decayer_->decay( event );
}
if ( !event ) return false;

// check and perform if there're any unstable particles after 
// running external decay packages
//
// fisrt of all, put back modified event tree (after external decay)
//
hadronizer_.resetEvent( event );
//
// now run residual decays
//
if ( !hadronizer_.residualDecay() ) return false;

hadronizer_.finalizeEvent();

event = hadronizer_.getGenEvent() ;
if ( !event ) return false;

event->set_event_number( ev.id().event() );

//
// tutto bene - finally, form up EDM products !
//
std::auto_ptr<HepMCProduct> bare_product(new HepMCProduct());
bare_product->addHepMCData( event );
ev.put(bare_product);

std::auto_ptr<GenEventInfoProduct> genEventInfo(hadronizer_.getGenEventInfo());
if (!genEventInfo.get())
{ 
   // create GenEventInfoProduct from HepMC event in case hadronizer didn't provide one
   genEventInfo.reset(new GenEventInfoProduct(event));
}
ev.put(genEventInfo);

return true;
}






