import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.TFileService = cms.Service("TFileService",
		fileName = cms.string("dump_prims.root") 
		)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/net/hisrv0001/home/dav2105/hdir/raw/181985/00026B4D-DD11-E111-B567-00237DDC5CB0.root'
    )
)

process.ecalDigis = cms.EDProducer("EcalRawToDigi",
    tccUnpacking = cms.bool(True),
    FedLabel = cms.InputTag("listfeds"),
    srpUnpacking = cms.bool(True),
    syncCheck = cms.bool(True),
    feIdCheck = cms.bool(True),
    silentMode = cms.untracked.bool(True),
    InputLabel = cms.InputTag("rawDataRepacker"),
    orderedFedList = cms.vint32(601, 602, 603, 604, 605, 
        606, 607, 608, 609, 610, 
        611, 612, 613, 614, 615, 
        616, 617, 618, 619, 620, 
        621, 622, 623, 624, 625, 
        626, 627, 628, 629, 630, 
        631, 632, 633, 634, 635, 
        636, 637, 638, 639, 640, 
        641, 642, 643, 644, 645, 
        646, 647, 648, 649, 650, 
        651, 652, 653, 654),
    eventPut = cms.bool(True),
    numbTriggerTSamples = cms.int32(1),
    numbXtalTSamples = cms.int32(10),
    orderedDCCIdList = cms.vint32(1, 2, 3, 4, 5, 
        6, 7, 8, 9, 10, 
        11, 12, 13, 14, 15, 
        16, 17, 18, 19, 20, 
        21, 22, 23, 24, 25, 
        26, 27, 28, 29, 30, 
        31, 32, 33, 34, 35, 
        36, 37, 38, 39, 40, 
        41, 42, 43, 44, 45, 
        46, 47, 48, 49, 50, 
        51, 52, 53, 54),
    FEDs = cms.vint32(601, 602, 603, 604, 605, 
        606, 607, 608, 609, 610, 
        611, 612, 613, 614, 615, 
        616, 617, 618, 619, 620, 
        621, 622, 623, 624, 625, 
        626, 627, 628, 629, 630, 
        631, 632, 633, 634, 635, 
        636, 637, 638, 639, 640, 
        641, 642, 643, 644, 645, 
        646, 647, 648, 649, 650, 
        651, 652, 653, 654),
    DoRegional = cms.bool(False),
    feUnpacking = cms.bool(True),
    forceToKeepFRData = cms.bool(False),
    headerUnpacking = cms.bool(True),
    memUnpacking = cms.bool(True)
)

process.gctDigis = cms.EDProducer("GctRawToDigi",
    unpackSharedRegions = cms.bool(False),
    numberOfGctSamplesToUnpack = cms.uint32(1),
    verbose = cms.untracked.bool(False),
    numberOfRctSamplesToUnpack = cms.uint32(1),
    inputLabel = cms.InputTag("rawDataRepacker"),
    unpackerVersion = cms.uint32(0),
    gctFedId = cms.untracked.int32(745),
    hltMode = cms.bool(False)
)

process.hcalDigis = cms.EDProducer("HcalRawToDigi",
    UnpackZDC = cms.untracked.bool(True),
    FilterDataQuality = cms.bool(True),
    InputLabel = cms.InputTag("rawDataRepacker"),
    ComplainEmptyData = cms.untracked.bool(False),
    UnpackCalib = cms.untracked.bool(True),
    UnpackTTP = cms.untracked.bool(True),
    lastSample = cms.int32(9),
    firstSample = cms.int32(0)
)

process.RawToDigi = cms.Sequence(process.ecalDigis+process.gctDigis+process.hcalDigis)


process.demo = cms.EDAnalyzer('TriggerPrimitives',
                              ECALDigis = cms.InputTag("ecalDigis:EcalTriggerPrimitives"),
                              HCALDigis = cms.InputTag("hcalDigis")
)

#process.p = cms.Path(process.demo)
process.p1 = cms.Sequence(process.RawToDigi+process.demo)

process.p = cms.Path(process.p1)
