
# ---------------------------------------------------------------------------
# BEGIN    TRACEABILITY - TRACEABILITY - TRACEABILITY - TRACEABILITY 
# ---------------------------------------------------------------------------
def GetTraceability():
    import inspect, os, socket, time
    Traceability=[]
    Traceability.append( "SkyFall" ) #VERSION NAME
    logScript = inspect.getfile(inspect.currentframe())
    Traceability.append( logScript )
    logDir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
    Traceability.append( logDir )
    Traceability.append( os.getlogin() )
    Traceability.append( socket.gethostname() )
    Traceability.append( time.strftime('%d/%m/%y %H:%M',time.localtime()) )
    try:
        logInput = open(logDir+'/'+logScript)
        for line in logInput:
          Traceability.append(line)
        logInput.close()
    except:
        print "TraceabilityError : impossible to get configuration"
    return Traceability
Traceability = GetTraceability()
# ---------------------------------------------------------------------------
# END    TRACEABILITY - TRACEABILITY - TRACEABILITY - TRACEABILITY 
# ---------------------------------------------------------------------------


# =========================================
#		  General config
# =========================================




import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.coreTools import *

# load the PAT config
#process.load("PhysicsTools.PatAlgos.patSequences_cff")

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")



# PAT Layer 0+1
process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")

#trigger matching & dynamic prescales stuff
from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger( process )

# =========================================
#				PF2PAT
# =========================================


# Configure PAT to use PF2PAT instead of AOD sources
# this function will modify the PAT sequences.
from PhysicsTools.PatAlgos.tools.pfTools import *

postfix = "PF2PAT"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=True, postfix=postfix)
# Add PF2PAT output to the created file
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning

# top projections in PF2PAT:
getattr(process,"pfNoPileUp"+postfix).enable = True
getattr(process,"pfNoMuon"+postfix).enable = True
getattr(process,"pfNoElectron"+postfix).enable = True
getattr(process,"pfNoTau"+postfix).enable = True
getattr(process,"pfNoJet"+postfix).enable = True

# verbose flags for the PF2PAT modules
getattr(process,"pfNoMuon"+postfix).verbose = False

# enable delta beta correction for muon selection in PF2PAT?
getattr(process,"pfIsolatedMuons"+postfix).doDeltaBetaCorrection = True



# =========================================
#				kt6PFJets
# =========================================

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


# =========================================
#				Test area ...
# =========================================


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


import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt
process.JetHLTFilter = hlt.triggerResultsFilter.clone(
     triggerConditions = cms.vstring(
        "HLT_PFJet80_v6"
     ),
     hltResults = cms.InputTag("TriggerResults","","HLT"),
     l1tResults = cms.InputTag( "" ),
     throw = cms.bool( False) #set to false to deal with missing triggers while running over different trigger menus
     )


#from PhysicsTools.PatAlgos.tools.coreTools import removeCleaning
#removeCleaning(process)

# ========================================= #
#				MiniTree					#
# ========================================= #

process.MiniTreeProduction = cms.EDProducer('MiniTreeProducer',
# ---------------------- General info -------------------------------
        verbose             = cms.uint32(0),   #0: nothing - >1 gradually more information
        isAOD               = cms.bool(True),  # true if processing AOD data
        isData              = cms.bool(False), # true if processing AOD data
# ----------------------   Trigger    -------------------------------
		doTrigger           = cms.bool(False),
        saveAllTriggers     = cms.bool(True), #should be True by default !!
        triggerList         = cms.vstring("HLT_Mu15_L1Mu7","HLT_DoubleMu3","HLT_IsoEle10_Mu10_L1R","HLT_IsoEle18_L1R","HLT_DoubleIsoEle12_L1R","HLT_Mu5","HLT_Mu9","HLT_Mu11","HLT_Mu15","HLT_IsoMu9","HLT_Ele10_SW_L1R","HLT_Ele15_SW_L1R","HLT_Ele15_LW_L1R","HLT_Ele10_LW_L1R","HLT_DoubleEle5_SW_L1R","HLT_LooseIsoEle15_LW_L1R","HLT_L2Mu3","HLT_L2Mu5","HLT_L2Mu9","HLT_Jet15U","HLT_Photon10_L1R","HLT_Photon15_L1R","HLT_Photon10_Cleaned_L1R","HLT_Photon15_Cleaned_L1R","HLT_Ele15_SW_CaloEleId_L1R","HLT_Ele20_SW_L1R","HLT_DoubleEle10_SW_L1R"),
# ----------------------  Electrons   -------------------------------
        doElectrons         = cms.bool(True),
        electron_cut_pt     = cms.double(10),
        electron_cut_eta    = cms.double(2.5),
        electron_saveAllID  = cms.bool(True),
        electron_IDlist     = cms.vstring("eidLoose","eidTight","eidRobustLoose","eidRobustTight","simpleEleId90relIso","simpleEleId90cIso","cicVeryLoose","cicLoose","cicMedium","cicTight","cicSuperTight","cicHyperTight1","cicHyperTight2","cicHyperTight3","cicVeryLooseMC","cicLooseMC","cicMediumMC","cicTightMC","cicHyperTight1MC","cicHyperTight2MC","cicHyperTight3MC"),
        electronHLTmatching = cms.vstring(""),
        electronProducer    = cms.VInputTag(cms.InputTag("selectedPatElectronsPF2PAT")),
        doElectronRhoCorrIso= cms.bool(False),
        doElectronRecoMatch = cms.bool(False),
        electronRecoProducer= cms.VInputTag(cms.InputTag("selectedPatElectrons")),
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
        muon_cut_keepStandaloneMu  = cms.bool(True),
        muon_cut_keepTrackerMu     = cms.bool(True),
        muon_cut_keepCaloMu        = cms.bool(True),
        muon_cut_keepGlobalMu      = cms.bool(True),
        muon_IDlist                = cms.vstring("GlobalMuonPromptTight"),
        muonHLTmatching     = cms.vstring(""),
        muonProducer        = cms.VInputTag(cms.InputTag("selectedPatMuonsPF2PAT")),
        doMuonRecoMatch     = cms.bool(False),
        muonRecoProducer    = cms.VInputTag(cms.InputTag("selectedPatMuonsBl")),
# -----------------------   Taus   ---------------------------------- 
        doTaus              = cms.bool(False),
        tau_cut_pt          = cms.double(10),
        tau_cut_eta         = cms.double(2.4),
        tau_saveAllID       = cms.bool(True),#
        tau_IDlist          = cms.vstring(""),
        tauHLTmatching      = cms.vstring(""),
        tauProducer         = cms.VInputTag(cms.InputTag("selectedPatTausPF2PAT")),
# -----------------------   Tracks  --------------------------------- 
        doTracks            = cms.bool(False),
        track_cut_pt        = cms.double(-0.1),
        track_cut_eta       = cms.double(2.6),
        trackProducer       = cms.VInputTag(cms.InputTag("generalTracks")),
# -----------------------   PFCandidates  --------------------------------- 
        doPFCandidates      = cms.bool(False),
        pfcandidate_cut_dR  = cms.double(0.3),
        pfcandidate_cut_dz  = cms.double(0.05),
        pfcandidate_cut_minPt	= cms.double(5.0),
        pfcandidate_VertexTag 	= cms.VInputTag(cms.InputTag("offlinePrimaryVertices")),
        pfcandidate_InputTag  	= cms.VInputTag(cms.InputTag("particleFlow")),
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
		#jetHLTmatching      = cms.vstring("jetMatchHLTJets"),
		jetHLTmatching      = cms.vstring(""),
		jetmetProducer      = cms.VPSet(
                    cms.PSet(jet = cms.untracked.string("selectedPatJetsPF"),
                             met = cms.untracked.string("patMETPF2PAT"),
                             algo =cms.untracked.string("pf")),
                    #cms.PSet(jet = cms.untracked.string("selectedPatJets"),
                    #         #met = cms.untracked.string("patMETs"),
                    #         met = cms.untracked.string("patMETsAK5Calo"),
                    #         algo =cms.untracked.string("ak5"))
                    ),
# -----------------------  Pile-Up ----------------------------------
        doPileUp            = cms.bool(True),  
        rho_PUUE_dens       = cms.InputTag("kt6PFJets", "rho"),
        #neutralRho_PUUE_dens= cms.InputTag("kt6NeutralPFJets", "rho"),
        neutralRho_PUUE_dens= cms.InputTag("kt6PFJetsCentralNeutral", "rho"),
# -----------------------  MonteCarlo ------------------------------- 
		doGenParticleCollection = cms.bool(True),
        mcDescentMax = cms.uint32(10),
        mcNGenPartMax = cms.uint32(10000)
    )

# ========================================= #
#				  NTuple              		#
# ========================================= #

process.TFileService = cms.Service("TFileService", fileName = cms.string("NTuple.root") )

# loads your analyzer
process.MyModule = cms.EDAnalyzer('NTupleProducer',
        verbose             = cms.uint32(0),   #0: nothing - >1 gradually more information
        traceability        = cms.vstring(Traceability),
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
# ----------------------- PFCandidates  --------------------------
        skimPFCandidates 			  	= cms.bool(False),
        pfcandidate_keepAllCollections 	= cms.bool(True),
        pfcandidate_collectionList     	= cms.vstring(""),
		pfcandidate_pt					= cms.double(5.0),
		pfcandidate_eta					= cms.double(2.5),
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
    #numberOfLept   = cms.int32(2),# for skims ! Total number of sel lepton,  -1 for no skiming
    numberOfLept   = cms.int32(-1),# for skims ! Total number of sel lepton,  -1 for no skiming
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


# =========================================
#				Path
# =========================================

# Let it run
'''
process.p = cms.Path(
    getattr(process,"patPF2PATSequence"+postfix)
)
'''

process.p = cms.Path(
	#process.patDefaultSequence*
	getattr(process,"patPF2PATSequence"+postfix)*
    process.neutralPFCandidatesProducer*
    process.kt6NeutralPFJets*
	process.MiniTreeProduction*
	process.MyModule
    )


# =========================================
#				Input
# =========================================

# Global tag
process.GlobalTag.globaltag = 'START53_V7E::All'

# Configuring source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/relval/CMSSW_5_3_2_patch1-START53_V7A/RelValTTbar/GEN-SIM-RECO/v1/0000/64542608-69C7-E111-AFC8-002618943953.root',
'/store/relval/CMSSW_5_3_2_patch1-START53_V7A/RelValTTbar/GEN-SIM-RECO/v1/0000/8C41444F-62C7-E111-9FE7-002618943833.root',
'/store/relval/CMSSW_5_3_2_patch1-START53_V7A/RelValTTbar/GEN-SIM-RECO/v1/0000/D80E86FF-7EC7-E111-BB09-003048678DD6.root'
                                    )
                                )

# Max events to run on
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )


# =========================================
#				Output
# =========================================

## Output Module Configuration (expects a path 'p')
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('myPatTuple.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('drop *', 
                           											  #'keep *_selected*_*_*',
                          											  'keep IPHCTreeMTEvent_*_*_*',
								   									  #*patEventContent
																	  )
                               )

process.outpath = cms.EndPath(process.out)

process.options.wantSummary = False   ##  (to suppress the long output at the end of the job)
