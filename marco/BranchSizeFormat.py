import os
import logging
from ROOT import TFile
from ROOT import TTree
import sys


class item:

    def __init__(self,s=None):
        self.reset()
        if s!=None:
            self.name=s.name
            self.compress=s.compress
            self.filesize=s.filesize
            self.basketsize=s.basketsize
            self.totalsize=s.totalsize
            self.entries=s.entries

    def reset(self):    
        self.name=""
        self.compress=""
        self.filesize=""
        self.basketsize=""
        self.totalsize=""
        self.entries=""
       

def Execute(filename):

    # Opening the input file
    try:
        file = open (filename,'r')
    except:
        print "Error : file called '"+filename+"' is not found"
        return

    # Creating one container for each branch info
    listOfBranches = []
    currentBranch = item()

    # Loop over lines
    for line in file:

        # Treat lines before split
        line=line.replace("="," = ")
        line=line.lstrip()
        line=line.replace("*","")
        line=line.replace(":","")

        # Split lines in words
        line=line.split()
        
        # Fill the branch info
        for i in range(0,len(line)):
            if line[i]=='Tree':
                currentBranch.name=line[i+1]
            if line[i]=='Br':
                currentBranch.name=line[i+2]
            if line[i]=='Entries':
                currentBranch.entries=line[i+1]
            if line[i]=='=' and line[i-1]=='Size' and line[i-2]=='File':
                currentBranch.filesize=line[i+1]
                listOfBranches.append(item(currentBranch))
                currentBranch.reset()


    # Close the file
    file.close()

    # Calculate the length of the longest words
    len_name = 4
    len_entries = 7
    len_filesize = 8
    for branch in listOfBranches:
        if len(branch.name)>len_name:
            len_name=len(branch.name)
        if len(branch.entries)>len_entries:
            len_entries=len(branch.entries)
        if len(branch.filesize)>len_filesize:
            len_name=len(branch.filesize)

    # Display with a good format
    tag1 = '%-' + str(len_name+2) + 's'
    tag2 = '%-' + str(len_entries+2) + 's'
    tag3 = '%-' + str(len_filesize+2) + 's'
    print tag1 % "Name" + tag2 % "Entries" + tag3 % "FileSize" 
    for branch in listOfBranches:
        print tag1 % branch.name + tag2 % branch.entries + tag3 % branch.filesize

    # Final Check
    totalSize = 0
    for branch in listOfBranches[1:]:
        totalSize+=int(branch.filesize)
    print
    print "Check : Tree Size = " + listOfBranches[0].filesize + " ; Total variable Size = " + str(totalSize)
    print "------> difference = " + str(int(listOfBranches[0].filesize) - totalSize) + " bytes"
    

if len(sys.argv)<2:
    print "################################"
    print " BranchSizeFormat "
    print " usage: ./BranchSizeFormat <textfile>"
else:
    Execute(sys.argv[1])
