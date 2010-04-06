#include "CmsHi/HiGenTools/interface/HiEventTuner.h"

#include "CmsHi/HiGenTools/interface/HiTrivialTune.h"
typedef HiEventTuner<HiTrivialTune> HiTrivialTuner; 
DEFINE_FWK_MODULE(HiTrivialTuner);

#include "CmsHi/HiGenTools/interface/HiStringCutTune.h"
typedef HiEventTuner<HiStringCutTune> HiStringCutTuner; 
DEFINE_FWK_MODULE(HiStringCutTuner);
