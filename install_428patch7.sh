#!/bin/bash
echo "Installing IPHC framework from CVS repository"
echo "----------------------------------------------"

cd $CMSSW_BASE/src
mkdir IPHCDataFormat
mkdir MiniTree
mkdir NTuple
mkdir marco
cvs co -d IPHCDataFormat UserCode/SusyIPHC/IPHCDataFormat
cvs co -d MiniTree UserCode/SusyIPHC/MiniTree
cvs co -d NTuple UserCode/SusyIPHC/NTuple
cvs co -d marco UserCode/SusyIPHC/marco


#Put the recipe here !!!
echo "Get PAT recipies"



#
echo "PAT RECIPE For 428_patch7!"
#
addpkg DataFormats/PatCandidates V06-04-19-02
addpkg PhysicsTools/PatAlgos V08-06-50
addpkg PhysicsTools/PatUtils V03-09-18
addpkg PhysicsTools/PatExamples V00-05-24
addpkg CommonTools/ParticleFlow B4_2_X_V00-03-00
addpkg PhysicsTools/SelectorUtils V00-03-24
addpkg PhysicsTools/UtilAlgos V08-02-14

echo "NEW RECIPE Type1/1p2 MET correction"
cvs co -r V04-05-07 JetMETCorrections/Type1MET
cvs co -r V03-03-07 DataFormats/METReco

cvs co -r V02-03-00 JetMETCorrections/Algorithms
rm -f JetMETCorrections/Algorithms/interface/L1JPTOffsetCorrector.h
rm -f JetMETCorrections/Algorithms/src/L1JPTOffsetCorrector.cc
cvs co -r V03-01-00 JetMETCorrections/Objects
addpkg JetMETCorrections/Modules
cvs up -r 1.4 JetMETCorrections/Modules/plugins/JetCorrectorOnTheFly.cc
cvs up -r 1.6 JetMETCorrections/Modules/interface/JetCorrectionProducer.h



#for eID with likelihood
cvs co -r V00-03-31 RecoEgamma/ElectronIdentification
 
echo "Now compile using scramv1 b -j 5"
scramv1 b -j 5
echo "Compilation finished"

cd IPHCDataFormat/NTFormat/src
make 
cd ../../..

# for systematics on jet energy
cp /afs/cern.ch/user/s/speer/public/JR_Standalone.tgz .
tar -xzvf JR_Standalone.tgz
rm -rf JR_Standalone.tgz
cd JR_Standalone/JetMETObjects/
make
cd ..
mv lib/libJetMETObjects.so ../NTuple/NTupleAnalysis/.
cd ..


cd NTuple/NTupleAnalysis/
mkdir .lib
make all
cd ../../.


echo "----------------------------------------------"
echo "Installation finished"
echo ""

