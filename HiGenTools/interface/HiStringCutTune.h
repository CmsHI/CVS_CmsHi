#ifndef HiStringCutTune_h
#define HiStringCutTune_h

#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

class HiStringCutTune
{

public:

    HiStringCutTune(edm::ParameterSet const & config) :
            evaluate_( config.getParameter<std::string>("cut") ) {}

    bool select(HepMC::GenParticle const & particle) const
    {
        return evaluate_(particle);
    }

private:

    StringCutObjectSelector<HepMC::GenParticle> evaluate_;
};

#endif
