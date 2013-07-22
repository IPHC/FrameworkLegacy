#! /usr/bin/env python
import sys
import os
import commands

class DateType:

    months = {"Jan" : 1, "Feb" : 2, "Mar" : 3, "Apr" : 4, \
              "May" : 5, "Jun" : 6, "Jul" : 7, "Aug" : 8, \
              "Sep" : 9, "Oct" : 10, "Nov" : 11, "Dec" : 12 }

    def __init__(self):
        self.month = 0
        self.day = 0
        self.hour = 0
        self.min = 0
        
    def value(self):
        return self.month*1000000 + self.day*10000 + self.hour*100 + self.min*1

    @staticmethod
    def string2int(word):
        if word in DateType.months:
            return DateType.months[word]
        return 0
    

def Help():
    print "The correct syntax is :"
    print "./harvest.py <minitree/ntuple> <folder on dpm/castor containing the samples> <output file>" 


def Execute(pattern,folder,output):
    print "====================================================================="
    print " Looking for NTuples in the folder : " + folder
    print "====================================================================="

    # Dump content of the folder in log file
    os.system("rfdir "+folder+" >& harvest.tmp~")

    # Open the log file 
    try:
        input = open("harvest.tmp~")
    except :
        print "ERROR : file called 'harvest.tmp~' is not found"
        return

    # Loop over the log file
    files = []
    nums = []
    sizes = []
    dates = []

    for lines in input:

        # Error : folder not found ?
        if "No such file or directory" in lines:
            print "ERROR : folder called '" + folder + "' is not found"
            return

        # Treat lines
        lines = lines.lstrip()
        lines = lines.split()

        # Reject
        if len(lines)<9:
            continue

        # Get MiniTree/Ntuple
        if lines[8].startswith(pattern):
            files.append(lines[8])

            name = lines[8].replace("_"," ")
            name = name.split()
            try:
                num = int(name[1])
            except:
                print "ERROR : cannot extract job number from " + lines[8]
                return
            nums.append(num)
            sizes.append(int(lines[4]))
            date = DateType()
            date.month = DateType.string2int(lines[5])
            date.day = int(lines[6])
            time = lines[7].split(':')
            date.hour = int(time[0])
            date.min = int(time[1])
            dates.append(date)
            
    # Print number of files
    print " Nb files = " + str(len(files))
    if len(files)==0:
        print " Nothing to do !"
        return

    # Get the first and last job number
    numfirst=nums[0]
    numlast=nums[0]
    for i in range(0,len(files)):
        if nums[i]<numfirst:
            numfirst=nums[i]
        if nums[i]>numlast:
            numlast=nums[i]
    print " First job number = " + str(numfirst) + " ; " +\
          "Last job number = "+ str(numlast)
    
    # Print size
    average=0
    minsize=sizes[0]
    maxsize=sizes[0]
    for i in range(0,len(files)):
        average += sizes[i]
        if sizes[i]<minsize:
            minsize=sizes[i]
        if sizes[i]>maxsize:
            maxsize=sizes[i]
    average /= len(files)
    print " File Size (Mo) : average = " + str(average/1e6) + " ; min = " \
          + str(minsize/1e6)  + " ; max = " + str(maxsize/1e6)


    # Check job num
    missing=[]
    nduplicates=0
    for i in range(numfirst,numlast+1):
        entry=[]
        for j in range(0,len(nums)):
            if i==nums[j]:
                entry.append(j)
        if len(entry)==0:
            missing.append(i)
        elif len(entry)>1:
	    nduplicates+=1
            print "ERROR : several files have the same numbers : "
            for item in entry:
                print " - '" + files[item] + "'"
	    print " Should first file be removed ? (Y/N)"
	    allowed_answers=['n','no','y','yes']
            answer=""
            while answer not in allowed_answers:
	        answer=raw_input(" Answer : ")
	        answer=answer.lower()
                if answer=="yes" or answer=="y":
		    nduplicates-=1;
	            os.system("rfrm " + folder + "/" + files[ entry[0] ] )
		    print " file '" +  files[ entry[0] ]  +"' removed"
    if(nduplicates>0):
        print " Still duplicates. (" + str(nduplicates) + ")"
        return
    else:    
        print " No Duplicates found !"
    if len(missing)==0:
        print " All jobs are found !"
    else:
        print "WARNING : jobs number '" + ",".join(map(str,missing)) + "' are missed"   

    # Confirmation
    print "====================================================================="
    print " Are you sure to copy all files in '" + output + "_tmp_harvest' folder and to merge files into '" + output + ".root' ? (Y/N)"
    allowed_answers=['n','no','y','yes']
    answer=""
    while answer not in allowed_answers:
        answer=raw_input(" Answer : ")
        answer=answer.lower()
        if answer=="no" or answer=="n":
            return

    # Check output file exist
    if os.path.isfile(output+".root"):
        print " A file called '" + output + ".root' is found. Would you like to remove it ? (Y/N)"
        answer=""
        while answer not in allowed_answers:
            answer=raw_input(" Answer : ")
            answer=answer.lower()
            if answer=="no" or answer=="n":
                return
        os.system("rm -f " + output + ".root")    

    # Check temporary dir exist
    if os.path.isdir(output+"_tmp_harvest"):
        print " A dir called '" + output + "_tmp_harvest' is found. Would you like to remove it ? (Y/N)"
        answer=""
        while answer not in allowed_answers:
            answer=raw_input(" Answer : ")
            answer=answer.lower()
            if answer=="no" or answer=="n":
                return
        os.system("rm -rf " + output + "_tmp_harvest")    
    
    # Merging
    print " Copying to the local disk ..."
    os.system("mkdir "+output+"_tmp_harvest")
    for i in range(0,len(files)):
        print "====================================================================="
        print " " + str(i+1) + "/" + str(len(files)) + " : copying file '" + files[i] + "' ..."
        print ""
        os.system("lcg-cp -v srm://sbgse1.in2p3.fr/" + folder + "/" + files[i] + " " + output + "_tmp_harvest/" + files[i])
    print " Merging ..."    
    os.system("hadd " + output + ".root " + output + "_tmp_harvest/*")
    print " Done."
    print " Please, do not forget to remove the temporary folder '" + output + "_tmp_harvest'"
        


# Check number of arguments
if len(sys.argv)<4:
    print "Error : wrong number of arguments"
    Help()
else:
    folder = sys.argv[2]
    output = sys.argv[3]

    #check output name
    if not output.endswith(".root"):
        print "Error: output file name must end by '.root'"
        Help()
    else:
        output = output[:-5]
        if sys.argv[1]=="ntuple":
            Execute("NTuple",folder,output)
        elif sys.argv[1]=="minitree":
            Execute("patTuple",folder,output)
        else:
            print "Error : the only format is 'ntuple' or 'minitree'"
        
    
        



