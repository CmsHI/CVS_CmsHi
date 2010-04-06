#ifndef HiTrivialTune_h
#define HiTrivialTune_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

class HiTrivialTune
{

public:

    HiTrivialTune(edm::ParameterSet const &) {}

    bool select(HepMC::GenParticle const &) const
    {
        return true;
    }
};

#endif
