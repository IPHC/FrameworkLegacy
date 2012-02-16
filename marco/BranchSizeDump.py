import os
import logging
from ROOT import TFile
from ROOT import TTree
import sys



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
    tree = input.Get("MyModule/Event")
    if tree==None:
        print "TTree called 'MyModule/Event' is not found"       
        return

    # Printing the tree structure
    tree.Print()
        
    
def Dump(tree):
    try:
        file = open ('log.txt','r')
    except:
        logging.error("File called tog.txt is not found")

    name=""
    compress=""
    filesize=""
    basketsize=""
    totalsize="" 
    entries=""
   
    for line in file:
        line=line.replace("="," = ")
        line=line.lstrip()
        line=line.replace("*","")
        line=line.replace(":","")
        line=line.split()
        #    print line
        for i in range(0,len(line)):
            if line[i]=='Tree':
                name=line[i+1]
            if line[i]=='Br':
                name=line[i+2]
            if line[i]=='Entries':
                entries=line[i+1]
            if line[i]=='=' and line[i-1]=='Size' and line[i-2]=='File':
                filesize=line[i+1]
            print name + ";" + entries + ";" + filesize
    file.close()



if len(sys.argv)<2:
    print "################################"
    print " BranchSizeDump "
    print " usage: ./BranchSizeDump <rootfilename>"
else:
    Execute(sys.argv[1])
