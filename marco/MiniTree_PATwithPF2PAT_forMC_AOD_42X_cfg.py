# import skeleton process
#from PhysicsTools.PatAlgos.patTemplate_cfg import *


import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")


## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")




## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

from Configuration.PyReleaseValidation.autoCond import autoCond

# modifdg
#startup == START311_V2::All for CMSSW_4_1_4 (seems obsolete, to be confirmed!)
#process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
#process.GlobalTag.globaltag = cms.string('START41_V0::All')
process.GlobalTag.globaltag = cms.string('START42_V13::All')

process.GlobalTag.toGet = cms.VPSet(
  cms.PSet(record = cms.string("BTagTrackProbability2DRcd"),
#        tag = cms.string("TrackProbabilityCalibration_2D_2010Data_v1_offline"),
#        tag = cms.string("TrackProbabilityCalibration_2D_2011Data_v1_offline"),
       tag = cms.string("TrackProbabilityCalibration_2D_2011_v1_mc"),
       connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_BTAU")),
  cms.PSet(record = cms.string("BTagTrackProbability3DRcd"),
#        tag = cms.string("TrackProbabilityCalibration_3D_2010Data_v1_offline"),
#        tag = cms.string("TrackProbabilityCalibration_3D_2011Data_v1_offline"),
       tag = cms.string("TrackProbabilityCalibration_3D_2011_v1_mc"),
       connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_BTAU"))
)



process.load("Configuration.StandardSequences.MagneticField_cff")

## Standard PAT Configuration File
#process.load("PhysicsTools.PatAlgos.patSequences_cff")


## Output Module Configuration (expects a path 'p')
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('drop *', *patEventContent )
                               )

process.outpath = cms.EndPath(process.out)







# PAT Layer 0+1
process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")

#trigger matching & dynamic prescales stuff
from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger( process )

process.jetMatchHLTJets = cms.EDProducer(
  # matching in DeltaR, sorting by best DeltaR
  "PATTriggerMatcherDRLessByR"
  # matcher input collections
, src     = cms.InputTag( 'selectedPatJetsPF2PAT' )
, matched = cms.InputTag( 'patTrigger' )
  # selections of trigger objects
#, matchedCuts = cms.string( 'type( "TriggerTau" ) && path( "HLT_QuadJet40_IsoPFTau40_v*" )' )
, matchedCuts = cms.string( 'type( "TriggerJet" ) && path( "HLT_QuadJet40_IsoPFTau40_v*", 0, 0) && filter( "hltQuadJet40IsoPFTau40" )') 
  # selection of matches
, maxDPtRel   = cms.double( 0.5 ) # no effect here
, maxDeltaR   = cms.double( 0.5 )
, maxDeltaEta = cms.double( 0.2 ) # no effect here
  # definition of matcher output
, resolveAmbiguities    = cms.bool( True )
, resolveByMatchQuality = cms.bool( True )
)
switchOnTriggerMatching( process, triggerMatchers = [ 'jetMatchHLTJets' ] )

#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTrigger( process )

from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector

process.goodOfflinePrimaryVertices = cms.EDFilter(
    "PrimaryVertexObjectFilter",
    filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
    src=cms.InputTag('offlinePrimaryVertices')
    )
    
    
process.noscraping = cms.EDFilter("FilterOutScraping",
                                  applyfilter = cms.untracked.bool(True),
                                  debugOn = cms.untracked.bool(True),
                                  numtrack = cms.untracked.uint32(10),
                                  thresh = cms.untracked.double(0.20)
)    

#Noise filter
process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')










# the source is already defined in patTemplate_cfg.
# overriding source and various other things
#process.load("CommonTools.ParticleFlow.Sources.source_ZtoEles_DBS_312_cfi")
#process.source = cms.Source("PoolSource", 
#     fileNames = cms.untracked.vstring('file:myAOD.root')
#)


# process.load("CommonTools.ParticleFlow.Sources.source_ZtoMus_DBS_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False))

# process.load("CommonTools.ParticleFlow.Sources.source_ZtoMus_DBS_cfi")
runOnMC = True

## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.out.fileName = cms.untracked.string('patTuple.root')

# load the PAT config
process.load("PhysicsTools.PatAlgos.patSequences_cff")


# Configure PAT to use PF2PAT instead of AOD sources
# this function will modify the PAT sequences. It is currently 
# not possible to run PF2PAT+PAT and standart PAT at the same time
from PhysicsTools.PatAlgos.tools.pfTools import *

#from PhysicsTools.PFCandProducer.Isolation.isoValMuonWithCharged_cfi import isoValMuonWithCharged
#process.load('PhysicsTools.PFCandProducer.Isolation.isoValMuonWithCharged_cfi')
#process.isoValMuonWithCharged.deltaR = 0.3
#from PhysicsTools.PFCandProducer.Isolation.isoValMuonWithCharged_cfi import isoValMuonWithCharged
#process.isoValMuonWithCharged.deltaR = cms.double(0.3)
 
 
# An empty postfix means that only PF2PAT is run,
# otherwise both standard PAT and PF2PAT are run. In the latter case PF2PAT
# collections have standard names + postfix (e.g. patElectronPFlow)  


postfix = "PF2PAT"  # to have only PF2PAT
jetAlgo="AK5"

usePFnoPU = True # before any top projection


# levels to be accessible from the jets
# jets are corrected to L3Absolute (MC), L2L3Residual (data) automatically, if enabled here
# and remain uncorrected, if none of these levels is enabled here
useL1FastJet    = True  # needs useL1Offset being off, error otherwise
useL1Offset     = False # needs useL1FastJet being off, error otherwise
useL2Relative   = True
useL3Absolute   = True
# useL2L3Residual = True  # takes effect only on data; currently disabled for CMSSW_4_2_X GlobalTags!
useL5Flavor     = False
useL7Parton     = False

# JEC set
jecSetBase = jetAlgo
jecSetPF = jecSetBase + 'PF'
if usePFnoPU:
  jecSetPF += 'chs'

# JEC levels
if useL1FastJet and useL1Offset:
  sys.exit( 'ERROR: switch off either "L1FastJet" or "L1Offset"' )
jecLevels = []
if useL1FastJet:
  jecLevels.append( 'L1FastJet' )
if useL1Offset:
  jecLevels.append( 'L1Offset' )
if useL2Relative:
  jecLevels.append( 'L2Relative' )
if useL3Absolute:
  jecLevels.append( 'L3Absolute' )
# if useL2L3Residual and not runOnMC:
#   jecLevelsPF.append( 'L2L3Residual' )
if useL5Flavor:
  jecLevels.append( 'L5Flavor' )
if useL7Parton:
  jecLevels.append( 'L7Parton' )




#usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, jetCorrections = ( jecSetPF , jecLevels) ) 
#adaptPFTaus( process, tauType='hpsPFTau', postfix=postfix )

usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix) 
#adaptPFTaus( process, tauType='hpsPFTau', postfix=postfix )

applyPostfix(process,"patJetCorrFactors",postfix).levels     = cms.vstring('L1FastJet','L2Relative','L3Absolute')
applyPostfix(process,"patJetCorrFactors",postfix).rho        = cms.InputTag("kt6PFJets","rho")
applyPostfix(process,"patJetCorrFactors",postfix).payload    = cms.string('AK5PFchs')
applyPostfix(process,"pfPileUp",postfix).checkClosestZVertex = cms.bool(False) 


# to use tau-cleaned jet collection uncomment the following:
#getattr(process,"pfNoTau"+postfix).enable = True

#changes for iso and deltaR
#muons
applyPostfix(process,"isoValMuonWithNeutral",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"isoValMuonWithCharged",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"isoValMuonWithPhotons",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"pfIsolatedMuons",postfix).combinedIsolationCut = cms.double(9999.)
#electrons
applyPostfix(process,"isoValElectronWithNeutral",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"isoValElectronWithCharged",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"isoValElectronWithPhotons",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"pfIsolatedElectrons",postfix).combinedIsolationCut = cms.double(9999.)
# jec should be ok
# by default: 'L1Offset','L2Relative','L3Absolute'
#  and primaryVertices = cms.InputTag("offlinePrimaryVertices")

#addJetCollection(process,cms.InputTag('JetPlusTrackZSPCorJetAntiKt5'),
#                 'AK5', 'JPT',
#                 doJTA        = True,
#                 doBTagging   = True,
#modifdg (L1Offset to substract PU effect)       
#                 jetCorrLabel = ('AK5JPT', cms.vstring([ 'L2Relative', 'L3Absolute'])),
#                 jetCorrLabel = ('AK5JPT', cms.vstring(['L1Offset', 'L2Relative', 'L3Absolute'])),
#                 doType1MET   = False,
#                 doL1Cleaning = False,
#                 doL1Counters = True,                 
#                 genJetCollection = cms.InputTag("ak5GenJets"),
#                 doJetID      = True
#                 )
     
from PhysicsTools.PatAlgos.tools.metTools import *

addTcMET(process, 'TC')
process.patMETsTC.addGenMET = False

process.pfPileUpPF2PAT.Enable = True
#process.pfPileUpPF2PAT.checkClosestZVertex = cms.bool(False)
process.pfPileUpPF2PAT.Vertices = cms.InputTag('goodOfflinePrimaryVertices')
process.pfJetsPF2PAT.doAreaFastjet = True
process.pfJetsPF2PAT.doRhoFastjet = False

removeMCMatching(process, ['All'])
removeIfInSequence(process, 'patJetGenJetMatchAK5JPT', "patDefaultSequence")
removeIfInSequence(process, 'patJetPartonMatchAK5JPT', "patDefaultSequence")
removeIfInSequence(process, 'patJetPartons',           "patDefaultSequence")
removeIfInSequence(process, 'patJetPartonAssociation', "patDefaultSequence")
removeIfInSequence(process, 'patJetPartonAssociationAK5JPT',  "patDefaultSequence")
removeIfInSequence(process, 'patJetFlavourAssociation',       "patDefaultSequence")
removeIfInSequence(process, 'patJetFlavourAssociationAK5JPT', "patDefaultSequence")

process.load('RecoJets.Configuration.RecoJets_cff')
from RecoJets.JetProducers.kt4PFJets_cfi import kt4PFJets

process.kt6PFJets               = kt4PFJets.clone()
process.kt6PFJets.rParam        = 0.6     
process.kt6PFJets.src           = cms.InputTag('pfNoElectron'+postfix)
process.kt6PFJets.Rho_EtaMax    = cms.double( 4.4)
process.kt6PFJets.doRhoFastjet  = True
process.kt6PFJets.doAreaFastjet = True
#process.kt6PFJets.voronoiRfact  = 0.9

#process.patJetCorrFactorsPFlow.rho = cms.InputTag("kt6PFJets", "rho")
getattr(process,"patJetCorrFactors"+postfix).rho = cms.InputTag("kt6PFJets", "rho")

process.load("MiniTree.MiniTreeProducer.neutralpfcandidates_cfi")

process.kt6NeutralPFJets = kt4PFJets.clone()
process.kt6NeutralPFJets.rParam        = 0.6     
process.kt6NeutralPFJets.Rho_EtaMax    = cms.double( 4.4)
process.kt6NeutralPFJets.doRhoFastjet  = True
process.kt6NeutralPFJets.doAreaFastjet = True
process.kt6NeutralPFJets.src           = "neutralPFCandidatesProducer"
#process.kt6PFJets.voronoiRfact  = 0.9


process.load('PhysicsTools.SelectorUtils.pfJetIDSelector_cfi')
process.load('PhysicsTools.SelectorUtils.jetIDSelector_cfi')
process.jetIDSelector.version = cms.string('PURE09')



process.load("MiniTree.MiniTreeProducer.simpleEleIdSequence_cff")
#process.load("RecoEgamma.ElectronIdentification.electronIdLikelihoodExt_cfi")
#process.load("RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_DataTuning_cfi")
#process.load("RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi")

process.patElectronIDs = cms.Sequence(process.simpleEleIdSequence)

process.patElectrons.addElectronID = cms.bool(True)
process.patElectrons.electronIDSources = cms.PSet(
    eidLoose= cms.InputTag("eidLoose"),
    eidTight= cms.InputTag("eidTight"),
    eidRobustTight= cms.InputTag("eidRobustTight"),
    eidRobustLoose= cms.InputTag("eidRobustLoose"),
    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
    simpleEleId90cIso= cms.InputTag("simpleEleId90cIso"),
    cicVeryLoose     =  cms.InputTag("cicVeryLoose"),
    cicLoose         =  cms.InputTag("cicLoose"),
    cicMedium        =  cms.InputTag("cicMedium"),
    cicTight         =  cms.InputTag("cicTight"),
    cicSuperTight    =  cms.InputTag("cicSuperTight"),
    cicHyperTight1    =  cms.InputTag("cicHyperTight1"),
    cicHyperTight2    =  cms.InputTag("cicHyperTight2"),
    cicHyperTight3    =  cms.InputTag("cicHyperTight3"),
    cicVeryLooseMC     =  cms.InputTag("cicVeryLooseMC"),
    cicLooseMC         =  cms.InputTag("cicLooseMC"),
    cicMediumMC        =  cms.InputTag("cicMediumMC"),
    cicTightMC         =  cms.InputTag("cicTightMC"),
    cicSuperTightMC    =  cms.InputTag("cicSuperTightMC"),
    cicHyperTight1MC    =  cms.InputTag("cicHyperTight1MC"),
    cicHyperTight2MC    =  cms.InputTag("cicHyperTight2MC"),
    cicHyperTight3MC    =  cms.InputTag("cicHyperTight3MC") 
)

process.patElectronIDsPF2PAT = cms.Sequence(process.simpleEleIdSequence)

process.patElectronsPF2PAT.addElectronID = cms.bool(True)
process.patElectronsPF2PAT.electronIDSources = cms.PSet(
    eidLoose= cms.InputTag("eidLoose"),
    eidTight= cms.InputTag("eidTight"),
    eidRobustTight= cms.InputTag("eidRobustTight"),
    eidRobustLoose= cms.InputTag("eidRobustLoose"),
    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
    simpleEleId90cIso= cms.InputTag("simpleEleId90cIso"),
    cicVeryLoose     =  cms.InputTag("cicVeryLoose"),
    cicLoose         =  cms.InputTag("cicLoose"),
    cicMedium        =  cms.InputTag("cicMedium"),
    cicTight         =  cms.InputTag("cicTight"),
    cicSuperTight    =  cms.InputTag("cicSuperTight"),
    cicHyperTight1    =  cms.InputTag("cicHyperTight1"),
    cicHyperTight2    =  cms.InputTag("cicHyperTight2"),
    cicHyperTight3    =  cms.InputTag("cicHyperTight3"),
    cicVeryLooseMC     =  cms.InputTag("cicVeryLooseMC"),
    cicLooseMC         =  cms.InputTag("cicLooseMC"),
    cicMediumMC        =  cms.InputTag("cicMediumMC"),
    cicTightMC         =  cms.InputTag("cicTightMC"),
    cicSuperTightMC    =  cms.InputTag("cicSuperTightMC"),
    cicHyperTight1MC    =  cms.InputTag("cicHyperTight1MC"),
    cicHyperTight2MC    =  cms.InputTag("cicHyperTight2MC"),
    cicHyperTight3MC    =  cms.InputTag("cicHyperTight3MC") 
)





# to run second PF2PAT+PAT with differnt postfix uncomment the following lines
# and add it to path
#postfix2 = "PFlow2"
#jetAlgo2="AK7"
#usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo2, runOnMC=True, postfix=postfix2)

# to use tau-cleaned jet collection uncomment the following:
#getattr(process,"pfNoTau"+postfix).enable = True 

# to switch default tau to HPS tau uncomment the following:
#adaptPFTaus(process,"hpsPFTau",postfix=postfix)





process.MiniTreeProduction = cms.EDProducer('MiniTreeProducer',
# ---------------------- General info -------------------------------
        verbose             = cms.uint32(2),   #0: nothing - >1 gradually more information
        isAOD               = cms.bool(True),  # true if processing AOD data
        isData              = cms.bool(False), # true if processing AOD data
# ----------------------   Trigger    -------------------------------
        doTrigger           = cms.bool(True),
        saveAllTriggers     = cms.bool(True), #should be True by default !!
        triggerList         = cms.vstring("HLT_Mu15_L1Mu7","HLT_DoubleMu3","HLT_IsoEle10_Mu10_L1R","HLT_IsoEle18_L1R","HLT_DoubleIsoEle12_L1R","HLT_Mu5","HLT_Mu9","HLT_Mu11","HLT_Mu15","HLT_IsoMu9","HLT_Ele10_SW_L1R","HLT_Ele15_SW_L1R","HLT_Ele15_LW_L1R","HLT_Ele10_LW_L1R","HLT_DoubleEle5_SW_L1R","HLT_LooseIsoEle15_LW_L1R","HLT_L2Mu3","HLT_L2Mu5","HLT_L2Mu9","HLT_Jet15U","HLT_Photon10_L1R","HLT_Photon15_L1R","HLT_Photon10_Cleaned_L1R","HLT_Photon15_Cleaned_L1R","HLT_Ele15_SW_CaloEleId_L1R","HLT_Ele20_SW_L1R","HLT_DoubleEle10_SW_L1R"),
# ----------------------  Electrons   -------------------------------
        doElectrons         = cms.bool(True),
        electron_cut_pt     = cms.double(10),
        electron_cut_eta    = cms.double(2.5),
        electron_saveAllID  = cms.bool(False),
        electron_IDlist     = cms.vstring("eidLoose","eidTight","eidRobustLoose","eidRobustTight","simpleEleId90relIso","simpleEleId90cIso","cicVeryLoose","cicLoose","cicMedium","cicTight","cicSuperTight","cicHyperTight1","cicHyperTight2","cicHyperTight3","cicVeryLooseMC","cicLooseMC","cicMediumMC","cicTightMC","cicHyperTight1MC","cicHyperTight2MC","cicHyperTight3MC"),
        electronHLTmatching = cms.vstring(""),
        electronProducer    = cms.VInputTag(cms.InputTag("selectedPatElectronsPF2PAT")),
# ----------------------   Photons    -------------------------------
        doPhotons           = cms.bool(False),
        photon_cut_pt       = cms.double(10),
        photon_cut_eta      = cms.double(2.5), 
        photonHLTmatching      = cms.vstring(""),
        photonProducer      = cms.VInputTag(cms.InputTag("selectedPatPhotonsPF2PAT")),
# -----------------------   Muons     -------------------------------
        doMuons             = cms.bool(True),
        muon_cut_pt         = cms.double(10),
        muon_cut_eta        = cms.double(2.5), 
        muon_cut_keepStandaloneMu  = cms.bool(False),
        muon_cut_keepTrackerMu     = cms.bool(True),
        muon_cut_keepCaloMu        = cms.bool(False),
        muon_cut_keepGlobalMu      = cms.bool(True),
        muon_IDlist                = cms.vstring("GlobalMuonPromptTight"),
        muonHLTmatching      = cms.vstring(""),
        muonProducer        = cms.VInputTag(cms.InputTag("selectedPatMuonsPF2PAT")),
# -----------------------   Taus   ---------------------------------- 
        doTaus              = cms.bool(False),
        tau_cut_pt          = cms.double(10),
        tau_cut_eta         = cms.double(2.4),
        tau_saveAllID       = cms.bool(True),
        tau_IDlist          = cms.vstring(""),
        tauHLTmatching      = cms.vstring(""),
        tauProducer         = cms.VInputTag(cms.InputTag("selectedPatTausPF2PAT")),
# -----------------------   Tracks  --------------------------------- 
        doTracks            = cms.bool(False),
        track_cut_pt        = cms.double(0.5),
        track_cut_eta       = cms.double(2.4),
        trackProducer       = cms.VInputTag(cms.InputTag("generalTracks")),
# -----------------------  Vertices --------------------------------- 
        doVertices          = cms.bool(True), 
        saveAllVertex       = cms.bool(True),
        vertexProducer      = cms.VInputTag(cms.InputTag("offlinePrimaryVertices")),
# -----------------------  BeamSpot --------------------------------- 
        doBeamSpot          = cms.bool(True),
        beamSpotProducer    = cms.InputTag("offlineBeamSpot"),
# -----------------------   JetMet ---------------------------------- 
        doJetMet            = cms.bool(True),
        doMuonCorrection    = cms.bool(True),
        jet_cut_pt          = cms.double(10),
        jet_cut_eta         = cms.double(2.5), 
        jetIDList           = cms.vstring("LOOSE","TIGHT"),
        jetBTagList         = cms.vstring("trackCountingHighEffBJetTags","trackCountingHighPurBJetTags","simpleSecondaryVertexBJetTags","simpleSecondaryVertexHighEffBJetTags","simpleSecondaryVertexHighPurBJetTags","softMuonBJetTags","jetProbabilityBJetTags","jetBProbabilityBJetTags","combinedSecondaryVertexBJetTags"),
	jetHLTmatching      = cms.vstring("jetMatchHLTJets"),
        jetmetProducer      = cms.VPSet(
                    cms.PSet(jet = cms.untracked.string("selectedPatJetsPF2PAT"),
                             met = cms.untracked.string("patMETsPF2PAT"),
                             algo =cms.untracked.string("pf")),
                    cms.PSet(jet = cms.untracked.string("selectedPatJets"),
                             met = cms.untracked.string("patMETs"),
                             algo =cms.untracked.string("ak5"))
                    ),
# -----------------------  Pile-Up ----------------------------------
        doPileUp            = cms.bool(True),  
        rho_PUUE_dens       = cms.InputTag("kt6PFJets", "rho"),
        neutralRho_PUUE_dens= cms.InputTag("kt6NeutralPFJets", "rho"),
# -----------------------  MonteCarlo ------------------------------- 
        doGenParticleCollection = cms.bool(True),
        mcDescentMax = cms.uint32(4),
        mcNGenPartMax = cms.uint32(100)

                                            )

process.TFileService = cms.Service("TFileService", fileName = cms.string("NTuple.root") )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

# loads your analyzer
process.MyModule = cms.EDAnalyzer('NTupleProducer',
        verbose             = cms.uint32(2),   #0: nothing - >1 gradually more information
# -------------------------------------------------------------------
#                         GENERAL SKIM 
# -------------------------------------------------------------------
   general_skim = cms.PSet(
# ---------------------- Monte Carlo  -------------------------------
        skimGenParticles = cms.bool(True),
        skimGenTaus      = cms.bool(True),
# ----------------------   Trigger    -------------------------------
        skimTrigger = cms.bool(False),
        triggerList = cms.vstring(""),
# ----------------------  Electrons   -------------------------------
        skimElectrons = cms.bool(False),
        electron_keepAllCollections = cms.bool(True),
        electron_collectionList     = cms.vstring(""),
        electron_pt                 = cms.double(7),
        electron_eta                = cms.double(2.5),
# ----------------------  Muons   -------------------------------
        skimMuons = cms.bool(False),
        muon_keepAllCollections = cms.bool(True),
        muon_collectionList     = cms.vstring(""),
        muon_pt                 = cms.double(7),
        muon_eta                = cms.double(2.5),
# ----------------------  Photons   -------------------------------
        skimPhotons = cms.bool(False),
        photon_keepAllCollections = cms.bool(True),
        photon_collectionList     = cms.vstring(""),
        photon_pt                 = cms.double(7),
        photon_eta                = cms.double(2.5),
# ----------------------  Taus   -------------------------------
        skimTaus = cms.bool(False),
        tau_keepAllCollections = cms.bool(True),
        tau_collectionList     = cms.vstring(""),
        tau_pt                 = cms.double(7),
        tau_eta                = cms.double(2.5),
# ----------------------  Jets   -------------------------------
        skimJets = cms.bool(False),
        jet_keepAllCollections = cms.bool(False),
        jet_collectionList     = cms.vstring("pf"),
        jet_pt                 = cms.double(10),
        jet_eta                = cms.double(2.5),
# ----------------------  Tracks   -------------------------------
        skimTracks = cms.bool(False),
        track_keepAllCollections = cms.bool(True),
        track_collectionList     = cms.vstring(""),
        track_pt                 = cms.double(7),
        track_eta                = cms.double(2.5),
# ----------------------  Vertices   -------------------------------
        skimVertices = cms.bool(False),
        vertex_keepAllCollections = cms.bool(True),
        vertex_collectionList     = cms.vstring("")
	),
# -------------------------------------------------------------------
#                         TOPDILEPTON SKIM
# -------------------------------------------------------------------
   topdilepton_skim = cms.PSet(
# ----------------------   Trigger    -------------------------------
	doTriggerSkimming     = cms.bool(False), # skim on trigger decisions
	triggerSkimList       = cms.vstring("HLT_QuadJet15U"),
# ----------------------  Muons   -------------------------------
        numberOfLept   = cms.int32(2),# for skims ! Total number of sel lepton,  -1 for no skiming
        numberOfMuon   = cms.int32(0),# number of sel muon
        muon_cut_pt      = cms.double(10),
   	muon_cut_iso     = cms.double(-1),  # PLEASE NO ISO FOR SKIMMING!!!
  	useMuonIdSkim	      = cms.bool(False),
# ----------------------  Electrons   -------------------------------
        numberOfElec   = cms.int32(0),# number of sel electron
  	useElectronIdSkim     = cms.bool(False),
  	electron_cut_pt  = cms.double(7),
  	electron_cut_iso = cms.double(-1), # PLEASE NO ISO FOR SKIMMING!!!
# ----------------------  MonteCarlo   -------------------------------
	doTMEMESkimming       = cms.bool(False), # skim on the TMEME
  	TMEMESkimList         = cms.vint32(),
  	doMCDiLepSkimming     = cms.bool(False),
  	MCDiLepList           = cms.vstring(""),
# ----------------------  Taus   -------------------------------
	doTauSkimming    = cms.bool(False), # skim on the number of reco taus (no id so far)
        numberOfTau      = cms.int32(1),
	tau_cut_pt       = cms.double(5),
	tau_algo         = cms.string("selectedPatTaus"),
# ----------------------  Jets   -------------------------------
	doJetSkimming         = cms.bool(False), # skim on the number of jets
	numberOfJet      = cms.int32(3),
	jet_cut_pt       = cms.double(20),	
	jet_cut_eta      = cms.double(2.5),
	jet_algo         = cms.string("pf"))
)

# top projections in PF2PAT:
getattr(process,"pfNoPileUp"  +postfix).enable = True
getattr(process,"pfNoMuon"    +postfix).enable = False 
getattr(process,"pfNoElectron"+postfix).enable = False
getattr(process,"pfNoTau"     +postfix).enable = False
getattr(process,"pfNoJet"     +postfix).enable = False

# verbose flags for the PF2PAT modules
getattr(process,"pfNoMuon"+postfix).verbose = False




if runOnMC == False:
    removeMCMatchingPF2PAT( process, '')    


#process.load('PhysicsTools.PFCandProducer.Isolation.isoValMuonWithCharged_cfi')
#process.isoValMuonWithCharged.deltaR = cms.double(0.3)

getattr(process,"patPF2PATSequence"+postfix).replace(
    getattr(process,"pfNoElectron"+postfix),
    getattr(process,"pfNoElectron"+postfix)*process.kt6PFJets )

# Let it run
process.p = cms.Path( process.goodOfflinePrimaryVertices*
                      process.HBHENoiseFilter*
                      process.noscraping + 
                      process.patElectronIDs *
                      getattr(process,"patPF2PATSequence"+postfix)*
		      #process.kt6PFJets*
#                      process.kt6PFJets*
#                      getattr(process,"patPF2PATSequence"+postfix)*
                      process.neutralPFCandidatesProducer*
                      process.kt6NeutralPFJets
              
#    second PF2PAT
#    + getattr(process,"patPF2PATSequence"+postfix2)
)
if not postfix=="":
    process.p += process.patDefaultSequence
    
    
process.p += process.MiniTreeProduction
   
process.p += process.MyModule   
   
# Add PF2PAT output to the created file
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.out.outputCommands = cms.untracked.vstring('drop *',
                               #'keep *_*_*_PAT',
                           'keep edmTriggerResults_*_*_*',
                           #'keep double_kt6PFJets_rho_*',
                           #'keep *_hltTriggerSummaryAOD_*_*',
                           #'keep *_offlineBeamSpot_*_*',
                           #'keep *_offlinePrimaryVertices_*_PAT',
                           #'keep *_muons_*_*',
                           #'keep *_muonTCMETValueMapProducer_*_*',
                           #'keep recoTracks_*_*_*',
                           #'keep GenEventInfoProduct_*_*_*',
                           #'keep recoGenParticles_*_*_*',
                                                   #*patEventContentNoCleaning 
                           'keep IPHCTreeMTEvent_*_*_*'
                           ) 


## ------------------------------------------------------
#  In addition you usually want to change the following
#  parameters:
## ------------------------------------------------------
#
#   process.GlobalTag.globaltag =  ...    ##  (according to https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions)
#                                         ##
#   process.source.fileNames = [          ##
#    '/store/relval/CMSSW_3_5_0_pre1/RelValTTbar/GEN-SIM-RECO/STARTUP3X_V14-v1/0006/14920B0A-0DE8-DE11-B138-002618943926.root'
#   ]                                     ##  (e.g. 'file:AOD.root')
#                                         ##



process.maxEvents.input = 100            ##  (e.g. -1 to run on all events)



#                                         ##
#   process.out.outputCommands = [ ... ]  ##  (e.g. taken from PhysicsTools/PatAlgos/python/patEventContent_cff.py)
#                                         ##
#   process.out.fileName = ...            ##  (e.g. 'myTuple.root')
#                                         ##
#   process.options.wantSummary = True    ##  (to suppress the long output at the end of the job)    

process.MessageLogger.cerr.FwkReport.reportEvery = 10

# to relax the muon isolation, uncomment the following:
#process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(99999.)
#process.PF2PAT.pfMuonSequence.pfIsolatedMuons.combinedIsolationCut = cms.double(99999.)


process.source = cms.Source(
    "PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
      'file:ttbar.root'
    )
)
