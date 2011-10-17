
#
# \version $Id: MultiPhotonAnalyzer_cfi.py,v 1.1 2010/09/30 12:57:35 yjlee Exp $
#

import FWCore.ParameterSet.Config as cms

from CmsHi.PhotonAnalysis.SinglePhotonAnalyzer_cfi import *

multiPhotonAnalyzer = singlePhotonAnalyzer.clone()
multiPhotonAnalyzer._TypedParameterizable__type="MultiPhotonAnalyzerTree"



