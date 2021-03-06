## import skeleton process
#from PhysicsTools.PatAlgos.patTemplate_cfg import *

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

import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")


## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")




## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

from Configuration.PyReleaseValidation.autoCond import autoCond

# modifdg
#process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
process.GlobalTag.globaltag = cms.string('START42_V17::All')



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



################################################################################################################################################



####################################
#  PV vertex selector
####################################
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
################################################################################################################################################

####################################
#  HBHE noise filter
####################################
#Noise filter
process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')


####################################
#  For Summer11 MC, MG, Powheg
#  Gen filter for pythia bug
####################################

process.load('GeneratorInterface/GenFilters/TotalKinematicsFilter_cfi')




process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False))


####################################
#  True to run on MC
####################################

runOnMC = True

####################################
#  Number of events read
####################################
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
####################################
#  Output Filename (PAT)
####################################
process.out.fileName = cms.untracked.string('patTuple.root')




####################################
#  Load the PAT config
####################################
process.load("PhysicsTools.PatAlgos.patSequences_cff")


####################################
#  Load the PAT config
####################################
# Configure PAT to use PF2PAT instead of AOD sources
# this function will modify the PAT sequences. It is currently 
# not possible to run PF2PAT+PAT and standart PAT at the same time
from PhysicsTools.PatAlgos.tools.pfTools import *


####################################
# An empty postfix means that only PF2PAT is run,
# otherwise both standard PAT and PF2PAT are run. In the latter case PF2PAT
# collections have standard names + postfix (e.g. patElectronPFlow)  
####################################


postfix = "PF2PAT"  # to have only PF2PAT
jetAlgo="AK5"

usePFnoPU = True # before any top projection


####################################
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
####################################
################################################################################################################################################

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

################################################################################################################################################



####################################
#  Enable PF2PAT
####################################
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, jetCorrections = ( jecSetPF , jecLevels) ) 
####################################

####################################
#  Setup JEC (useless ? already done by usePF2PAT ?
####################################

applyPostfix(process,"patJetCorrFactors",postfix).levels     = jecLevels
applyPostfix(process,"patJetCorrFactors",postfix).rho        = cms.InputTag("kt6PFJets","rho")
applyPostfix(process,"patJetCorrFactors",postfix).payload    = jecSetPF
applyPostfix(process,"pfJets",postfix).doAreaFastjet    = True
applyPostfix(process,"pfJets",postfix).doRhoFastjet     = False
applyPostfix(process,"pfPileUp",postfix).checkClosestZVertex = cms.bool(False) 
applyPostfix(process,"pfPileUp",postfix).Vertices = 'goodOfflinePrimaryVertices'



####################################
# to use tau-cleaned jet collection uncomment the following:
#  Desable for now
####################################
#getattr(process,"pfNoTau"+postfix).enable = True
####################################





################################################################################################################################################
####################################
#  changes for iso and deltaR
####################################
#muons # spectial recipe for 428_p7
applyPostfix(process,"pfIsolatedMuons",postfix).isolationValueMapsCharged = cms.VInputTag( cms.InputTag( 'muPFIsoValueCharged03PF2PAT' ) )
applyPostfix(process,"pfIsolatedMuons",postfix).isolationValueMapsNeutral = cms.VInputTag( cms.InputTag( 'muPFIsoValueNeutral03PF2PAT' ), cms.InputTag( 'muPFIsoValueGamma03PF2PAT' ) )
applyPostfix(process,"pfIsolatedMuons",postfix).deltaBetaIsolationValueMap = cms.InputTag( 'muPFIsoValuePU03PF2PAT' )
applyPostfix(process,"patMuons",postfix).isolationValues.pfNeutralHadrons = cms.InputTag( 'muPFIsoValueNeutral03PF2PAT' )
applyPostfix(process,"patMuons",postfix).isolationValues.pfPhotons = cms.InputTag( 'muPFIsoValueGamma03PF2PAT' )
applyPostfix(process,"patMuons",postfix).isolationValues.pfChargedHadrons = cms.InputTag( 'muPFIsoValueCharged03PF2PAT' )
applyPostfix(process,"patMuons",postfix).isolationValues.pfPUChargedHadrons = cms.InputTag( 'muPFIsoValuePU03PF2PAT' ) 
applyPostfix(process,"pfIsolatedMuons",postfix).combinedIsolationCut = cms.double(9999.)
#electrons
applyPostfix(process,"isoValElectronWithNeutral",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"isoValElectronWithCharged",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"isoValElectronWithPhotons",postfix).deposits[0].deltaR = cms.double(0.3)
applyPostfix(process,"pfIsolatedElectrons",postfix).combinedIsolationCut = cms.double(9999.)

applyPostfix(process,"pfIsolatedMuons",postfix).isolationCut = cms.double(9999.)
applyPostfix(process,"pfIsolatedElectrons",postfix).isolationCut = cms.double(9999.)

################################################################################################################################################





####################################
#  Add tcMET. Not used anymore...
from PhysicsTools.PatAlgos.tools.metTools import *

addTcMET(process, 'TC')
process.patMETsTC.addGenMET = False
####################################


####################################
#  Remove some MC dependencies
####################################
removeMCMatching(process, ['All'])
removeIfInSequence(process, 'patJetGenJetMatchAK5JPT', "patDefaultSequence")
removeIfInSequence(process, 'patJetPartonMatchAK5JPT', "patDefaultSequence")
removeIfInSequence(process, 'patJetPartons',           "patDefaultSequence")
removeIfInSequence(process, 'patJetPartonAssociation', "patDefaultSequence")
removeIfInSequence(process, 'patJetPartonAssociationAK5JPT',  "patDefaultSequence")
removeIfInSequence(process, 'patJetFlavourAssociation',       "patDefaultSequence")
removeIfInSequence(process, 'patJetFlavourAssociationAK5JPT', "patDefaultSequence")
################################################################################################################################################



####################################
#  Produce kt6PFJets
#  For jet area and Rho subtraction
####################################
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
################################################################################################################################################


####################################
#  Selecion jet according to 
#  The sandard jetID PURE09
####################################
process.load('PhysicsTools.SelectorUtils.pfJetIDSelector_cfi')
process.load('PhysicsTools.SelectorUtils.jetIDSelector_cfi')
process.jetIDSelector.version = cms.string('PURE09')



####################################
#  Produce various eID
####################################
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

################################################################################################################################################



####################################
#  Produce PDF weights
#  To speed up the processing
#  Interactivaly, before staring CMSSW
#  do "scramv1 setup lhapdffull; scramv1 b;"
#  with crab, ass these two lines after 
#  eval `scramv1 runtime -sh in crab_.../job/CMSSW.sh
####################################
process.pdfWeights = cms.EDProducer("PdfWeightProducer",
	    # Fix POWHEG if buggy (this PDF set will also appear on output,
	    # so only two more PDF sets can be added in PdfSetNames if not "")
	    #FixPOWHEG = cms.untracked.string("cteq66.LHgrid"),
	    #GenTag = cms.untracked.InputTag("genParticles"),
	    PdfInfoTag = cms.untracked.InputTag("generator"),
	    PdfSetNames = cms.untracked.vstring(
		    "cteq66.LHgrid"
	    )
)
 

################################################################################################################################################


####################################
#  Extra MET collections
####################################
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
process.load("JetMETCorrections.Type1MET.pfMETCorrections_cff")


#process.ak5PFL1Fastjet.algorithm  =  cms.string('AK5PFchs')
#process.ak5PFL1FastL2L3.algorithm =  cms.string('AK5PFchs')

process.ak5PFL1FastjetPFNoPU = ak5PFL1Fastjet.clone()
process.ak5PFL1FastjetPFNoPU.algorithm  =  cms.string('AK5PFchs')

process.ak5PFL1FastL2L3PFNoPU = ak5PFL1FastL2L3.clone()
process.ak5PFL1FastL2L3PFNoPU.algorithm  =  cms.string('AK5PFchs')

process.pfCandsNotInJet.topCollection              = cms.InputTag('pfJetsPF2PAT')
process.pfCandsNotInJet.bottomCollection           = cms.InputTag('pfNoElectronPF2PAT')


process.pfJetMETcorr.src            = cms.InputTag('pfJetsPF2PAT')
process.pfJetMETcorr.offsetCorrLabel = cms.string("ak5PFL1FastjetPFNoPU")
process.pfJetMETcorr.jetCorrLabel    = cms.string("ak5PFL1FastL2L3PFNoPU")
#process.pfCandMETcorr.src = cms.InputTag('pfCandsNotInJetPF2PAT') 

process.pfType1CorrectedMet.src   = cms.InputTag('pfMETPF2PAT')
process.pfType1p2CorrectedMet.src = cms.InputTag('pfMETPF2PAT')

process.patMETsTypeIPF = process.patMETsPF2PAT.clone(
	metSource = cms.InputTag("pfType1CorrectedMet"),
	addMuonCorrections = cms.bool(False)
    )


process.patMETsTypeIIPF = process.patMETsPF2PAT.clone(
	metSource = cms.InputTag("pfType1p2CorrectedMet"),
	addMuonCorrections = cms.bool(False)
    )



################################################################################################################################################
#pfMET TypeI


####################################
#  Our Tree Producers
####################################




process.MiniTreeProduction = cms.EDProducer('MiniTreeProducer',
# ---------------------- General info -------------------------------
        verbose             = cms.uint32(0),   #0: nothing - >1 gradually more information
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
        jetBTagList         = cms.vstring("trackCountingHighEffBJetTags","jetProbabilityBJetTags","jetBProbabilityBJetTags","combinedSecondaryVertexBJetTags"),
	jetHLTmatching      = cms.vstring("jetMatchHLTJets"),
        jetmetProducer      = cms.VPSet(
	 	    	  cms.PSet(
			    jet = cms.untracked.string("selectedPatJetsPF2PAT"), 
			    met = cms.untracked.string("patMETsPF2PAT"),   
			    algo =cms.untracked.string("pf")
			  ),
 	    		  cms.PSet(
			    jet = cms.untracked.string("selectedPatJetsPF2PAT"), 
			    met = cms.untracked.string("patMETsTypeIPF"),  
			    algo =cms.untracked.string("pfType1")
			  ),
 	    		  cms.PSet(
			    jet = cms.untracked.string("selectedPatJetsPF2PAT"), 
			    met = cms.untracked.string("patMETsTypeIIPF"), 
			    algo =cms.untracked.string("pfType12")
			  )
	
	
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


# loads your analyzer
process.MyModule = cms.EDAnalyzer('NTupleProducer',
        verbose             = cms.uint32(0),   #0: nothing - >1 gradually more information
        traceability        = cms.vstring(Traceability),
                                  
# -------------------------------------------------------------------
#                         GENERAL SKIM 
# -------------------------------------------------------------------
   general_skim = cms.PSet(
        verbose             = cms.uint32(0),   #0: nothing - >1 gradually more information
# ----------------------   Trigger    -------------------------------
        skimTrigger      = cms.bool(False),
        skimGenParticles = cms.bool(True),
        skimGenTaus      = cms.bool(True),
        triggerList      = cms.vstring(""),
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
        jet_keepAllCollections = cms.bool(True),
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
        numberOfLept     = cms.int32(-1),# for skims ! Total number of sel lepton,  -1 for no skiming
        numberOfMuon     = cms.int32(0),# number of sel muon
        muon_cut_pt      = cms.double(10),
   	muon_cut_iso     = cms.double(-1),  # PLEASE NO ISO FOR SKIMMING!!!
  	useMuonIdSkim	 = cms.bool(False),
# ----------------------  Electrons   -------------------------------
        numberOfElec       = cms.int32(0),# number of sel electron
  	useElectronIdSkim  = cms.bool(False),
  	electron_cut_pt    = cms.double(7),
  	electron_cut_iso   = cms.double(-1), # PLEASE NO ISO FOR SKIMMING!!!
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






################################################################################################################################################

####################################
#  top projections in PF2PAT:
####################################
getattr(process,"pfNoPileUp"  +postfix).enable = True
getattr(process,"pfNoMuon"    +postfix).enable = False 
getattr(process,"pfNoElectron"+postfix).enable = False
getattr(process,"pfNoTau"     +postfix).enable = False
getattr(process,"pfNoJet"     +postfix).enable = False

####################################
#  verbose flags for the PF2PAT modules
getattr(process,"pfNoMuon"+postfix).verbose = False
#  top projections in PF2PAT:
####################################



if runOnMC == False:
    removeMCMatchingPF2PAT( process, '')    


#process.load('PhysicsTools.PFCandProducer.Isolation.isoValMuonWithCharged_cfi')
#process.isoValMuonWithCharged.deltaR = cms.double(0.3)

####################################
#  Configure PF2PAT
####################################
getattr(process,"patPF2PATSequence"+postfix).replace(
    getattr(process,"pfNoElectron"+postfix),
    getattr(process,"pfNoElectron"+postfix)*process.kt6PFJets )

####################################
#  Define the Path
####################################
process.p = cms.Path( process.totalKinematicsFilter*
 		      #process.pdfWeights*  ## to be uncomment for ttbar
		      process.goodOfflinePrimaryVertices*
                      process.HBHENoiseFilter*
                      process.noscraping + 
                      process.patElectronIDs *                      
		      getattr(process,"patPF2PATSequence"+postfix)*
		      process.producePFMETCorrections*
 		      process.patMETsTypeIPF*
 		      process.patMETsTypeIIPF*
                      process.neutralPFCandidatesProducer*
                      process.kt6NeutralPFJets
              
#    second PF2PAT
#    + getattr(process,"patPF2PATSequence"+postfix2)
)
if not postfix=="":
    process.p += process.patDefaultSequence
    
  
#################################### 
# Add NTuple producers to the sequence 
####################################
process.p += process.MiniTreeProduction
   
process.p += process.MyModule   
 
####################################   
#  Output content
#################################### 
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.out.outputCommands = cms.untracked.vstring('drop *',
                              # 'keep *_*_*_PAT',
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







process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.source = cms.Source(
    "PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
      '/store/mc/Summer11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEFC7AEB-DBD5-E011-9CE1-002590200B7C.root'
      #  '/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCFD87D7-9E98-E011-BDA2-0018F3D09642.root',
      #  '/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCFB9DE1-8598-E011-BE64-003048679076.root',
      #  '/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FAD1CEE7-7A98-E011-89A0-001A92971B7E.root',
      #  '/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FAA9FD72-E497-E011-A542-001A92971BC8.root',
       
    )
)
