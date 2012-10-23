# Python packages
import os
import logging
import sys

# ROOT packages
from ROOT import TFile
from ROOT import TTree
from ROOT import TString

class Data():

    def __init__(self):
        self.user = TString();
        
        

def Execute(filename):

    # save stdin 
    savecout = sys.stdout
    savecerr = sys.stderr

    # redirect stdin to log file
    fcout = open('cout.log', 'w')
    fcerr = open('cerr.log', 'w')
    sys.stdout = fcout
    sys.stderr = fcerr

    # Open the input file 
    input = TFile(filename,"OPEN")

    # redirect log file to stdin
    fcout.close()
    fcerr.close()
    sys.stdout = savecout
    sys.stderr = savecerr

    # Check if the file is opened ?
    if (not input.IsOpen()) or input.IsZombie():
        print "File called '" + sys.argv[1] + "' is not found"
        return

    # Get the tree
    tree = input.Get("MyModule/SampleInfo")
    if tree==None:
        print "TTree called 'MyModule/SampleInfo' is not found"       
        return

    # Printing the tree structure
    nentries = tree.GetEntries()
    print "Number of samples merged: " + str(nentries)

    #data = Data()
#    tree.SetMakeClass(1)
    #tree.SetBranchAddress("user",data.user)
    
    # Loop over samples
    for i in range(0,nentries):

        #tree.LoadTree(i)
        #tree.GetEntry(i)

        #print "---------------------------------------------"
        #print " user = " + str(data.user)
        #print "---------------------------------------------"
        tree.Show(i)

if len(sys.argv)<2:
    print "################################"
    print " sbgTrace "
    print " usage: sbgTrace.py <rootfilename>"
else:
    print "execute"
    Execute(sys.argv[1])
