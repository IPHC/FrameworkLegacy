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
echo "----------------------------------------------"
echo "Installation finished"
echo ""


