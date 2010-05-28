import FWCore.ParameterSet.Config as cms
process = cms.Process("ANASKIM")
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')
#process.GlobalTag.globaltag = 'GR09_R_34X_V5::All'
process.GlobalTag.globaltag = 'MC_3XY_V26::All'
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(


#'rfio:/castor/cern.ch/user/s/silvest/rootfiles/Hydjet_RECO/361/Hydjet_MinBias_2760_QW_pt6_EmbeddingZtoMuMu_RAW-L2-RECO/root/Embedding_Hydjet_MinBias_2760GeV_pt6_RAW_e10_9_9_job7585_RECO.root'
    ##pp Cath File
    'rfio:/castor/cern.ch/user/s/silvest/rootfiles/SignalOnly/Z0/root/RECO/Z0_SignalOnly_PPofflineReco_job1_RECO.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/Zmumu_HIReco_PtYGunFlat2000.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_pp_Reco_1_10.root',
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_pp_Reco_11_20.root'
   #'file:HiHLT_HiReco_15Events.root'
    ),

)


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# =============== Filter Path =====================
process.load("Z0Ana.ZToMuMu.ZMuMuFilters_cff")

#process.load("HeavyIonsAnalysis.Configuration.dimuons_cfi")
#process.load("HeavyIonsAnalysis.Configuration.analysisProducers_cff")
#process.load("HeavyIonsAnalysis.Configuration.patCandidatesForHISkim_cff")

#Uncomment for HI reconstruction
#process.patAODTrackCandsUnfiltered.src = cms.InputTag("hiSelectedTracks")
#process.patAODTrackIsoDepositCtfTk.ExtractorPSet.inputTrackCollection = cms.InputTag("hiSelectedTracks")


process.DiMuonsGen_Step=cms.Path(process.GenMuons*process.GenDimuons*process.GenDimuonsFilter)
process.DiMuonsGlobal_Step =cms.Path(process.goodMuonRecoForDimuon*process.Dimuons*process.dimuonsGlobal*process.dimuonsGlobalFilter)
process.DiMuonsGlobalSTA_Step=cms.Path(process.goodMuonRecoForDimuon*process.Dimuons*process.dimuonsGlobalSTA*process.dimuonsGlobalSTAFilter)
process.DiMuonsSTA_Step=cms.Path(process.goodMuonRecoForDimuon*process.Dimuons*process.dimuonsSTA*process.dimuonsSTAFilter)


#To exclude PAT
#process.DiMuonsGlobal_Step =cms.Path(process.Dimuons*process.dimuonsGlobal*process.dimuonsGlobalFilter)
#process.DiMuonsGlobalSTA_Step=cms.Path(process.Dimuons*process.dimuonsGlobalSTA*process.dimuonsGlobalSTAFilter)
#process.DiMuonsSTA_Step=cms.Path(process.Dimuons*process.dimuonsSTA*process.dimuonsSTAFilter)

# =============== Output ================================
process.load("Z0Ana.ZToMuMu.ZMuMuEventContent_cff")
process.output = cms.OutputModule("PoolOutputModule",
    #process.hiAnalysisSkimContent,
    process.ZMuMuContent,
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD'),
     filterName = cms.untracked.string('')),
    fileName = cms.untracked.string('file:CathppReco.root')
                                  )

process.outpath = cms.EndPath(process.output)

#process.schedule=cms.Schedule(process.GlobalDiMuons,process.STADiMuons,process.Tracks,process.GoodMuonRecoForDiMuon,process.outpath)
process.schedule=cms.Schedule(process.DiMuonsGen_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.outpath)
