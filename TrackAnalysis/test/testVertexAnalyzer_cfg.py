import FWCore.ParameterSet.Config as cms
import os 

process = cms.Process("TEST")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions#22X_Releases_starting_from_CMSSW
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'IDEAL_31X::All' 

##################################################################################

indir="/pnfs/cmsaf.mit.edu/hibat/cms/users/edwenger/vtx/mb" #dcache
firstfile=1
nfiles=1
maxevents=-1

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = ['hiProtoTracks','pixel3Vertices']  
process.MessageLogger.categories = ['MinBiasTracking','heavyIonHLTVertexing']
process.MessageLogger.cerr.threshold = "DEBUG" 

			   
#process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
#                                        ignoreTotal=cms.untracked.int32(0),
#                                        oncePerEventMode = cms.untracked.bool(False)
#                                        )

#process.Timing = cms.Service("Timing")

##################################################################################
# Input Source
process.source = cms.Source('PoolSource',
	fileNames = cms.untracked.vstring() 
)
							
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(maxevents)
)

# add specified files to fileNames
for i in range(firstfile,firstfile+nfiles):
	process.source.fileNames.append('dcache:%s/out%d_numEvent1.root' % (indir, i)) #dcache

##################################################################################
#Reconstruction			
process.load("RecoHI.Configuration.Reconstruction_HI_cff")              # full heavy ion reconstruction

#HI HLT implementation of proto-tracks
process.load("RecoHI.HiTracking.PixelProtoTracks_cfi") #hiProtoTracks
process.pixel3Vertices.TrackCollection = 'hiProtoTracks'

#Primary Vertex Producer modified for heavy ions
process.load("RecoHI.HiTracking.HeavyIonPrimaryVertices_cfi")

##############################################################################
# Vtx Analyzer
process.vtxAnalyzer = cms.EDAnalyzer("VtxAnalyzer")
# output file service
process.TFileService = cms.Service("TFileService", fileName = cms.string('output_VtxAnalyzer_%d.root' % (firstfile)) 
)


##############################################################################
# Output EDM File
process.load("CmsHi.Utilities.HiAnalysisEventContent_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.HIRecoObjects,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string('edmFile_testVertex.root')
                                  )

##################################################################################
# Paths
#process.pxlreco = cms.Path(process.offlineBeamSpot*process.trackerlocalreco*process.hiProtoTracks)
process.vtxreco = cms.Path(process.pixel3Vertices + process.heavyIonPrimaryVertices)
process.ana = cms.Path(process.vtxAnalyzer)
#process.save = cms.EndPath(process.output)
