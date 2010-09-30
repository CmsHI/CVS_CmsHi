
#
# \version $Id: MultiPhotonAnalyzer_cfi.py,v 1.5 2010/03/17 10:51:26 adebened Exp $
#

import FWCore.ParameterSet.Config as cms

from CmsHi.PhotonAnalysis.SinglePhotonAnalyzer_cfi import *

multiPhotonAnalyzer = singlePhotonAnalyzer.clone()
multiPhotonAnalyzer._TypedParameterizable__type="MultiPhotonAnalyzer"



