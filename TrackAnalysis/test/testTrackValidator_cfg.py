import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions#22X_Releases_starting_from_CMSSW
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'IDEAL_V12::All' 

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")          
			   
#process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
#                                        ignoreTotal=cms.untracked.int32(0),
#                                        oncePerEventMode = cms.untracked.bool(False)
#                                        )

#process.Timing = cms.Service("Timing")

##################################################################################
# Input Source
process.source = cms.Source('PoolSource',
	skipEvents = cms.untracked.uint32(0),
	fileNames = cms.untracked.vstring(
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV01.root',
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV02.root',	
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV03.root',	
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV04.root',
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV05.root',	
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV06.root',	
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV07.root',	
		'dcache:///pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig100/QuenchedEcalTrig4TeV08.root'		
	) 
)
							
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

##################################################################################
# Centrality Filter from UserCode/CmsHi/Utilities
process.centFilter4050 = cms.EDFilter("CentFilter",
							  bmin = cms.untracked.double(10.105),
							  bmax = cms.untracked.double(11.294)
                              )

##################################################################################
#Reconstruction			
process.load("RecoHI.Configuration.Reconstruction_HI_cff") # full heavy ion reconstruction

# reco track quality cuts
process.selectRecoTracks = cms.EDFilter("TrackSelector",                
									src = cms.InputTag("globalPrimTracks"),
									cut = cms.string('pt > 2.0 && d0/d0Error<3. && recHitsSize>12. && chi2prob(chi2,ndof)>0.01')
									)


# sim track quality cuts: pt>2, nhit>8, # of hit pixel layers >=3, etc.
process.load("CmsHi.TrackAnalysis.findableSimTracks_cfi") 
																	

##############################################################################
# MultiTrackValidator

# track associator settings
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")	 # sim to reco associator
process.TrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')  # matching fraction: shared/nrechit! default='sim', shared/nsimhit
process.TrackAssociatorByHits.UseGrouped = cms.bool(False)               # grouping hits on overlap layers? default=True

process.load("Validation.RecoTrack.MultiTrackValidator_cff")
process.multiTrackValidator.associators = cms.vstring('TrackAssociatorByHits')
process.multiTrackValidator.UseAssociators = True
process.multiTrackValidator.label = ['selectRecoTracks'] # selection on globalPrimTracks
process.multiTrackValidator.label_tp_effic = cms.InputTag("findableSimTracks") # selection on mergedtruth
process.multiTrackValidator.label_tp_fake  = cms.InputTag("findableSimTracks")
process.multiTrackValidator.outputFile = 'test_track_validation_HI_outfile.root'


##################################################################################
# Output EDM File
process.output = cms.OutputModule("PoolOutputModule",
                                  outputCommands = cms.untracked.vstring('keep *'),
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string('outputTest_RECO.root')
                                  )
# Paths
process.trkReco = cms.Sequence(process.offlineBeamSpot*process.trackerlocalreco*process.heavyIonTracking)
process.p = cms.Path(process.centFilter4050
					* process.trkReco 
					* process.selectRecoTracks 
					* process.findableSimTracks
					* process.multiTrackValidator
					)
#process.save = cms.EndPath(process.output)

