#! /usr/bin/env python
import sys
import os

def Execute():
    print "===================================================================="
    print " Submit crab job for event type = " + sys.argv[1]
    print " and dataset = " + sys.argv[2]
    print "===================================================================="

    print " Writing 'crab_"+sys.argv[1]+".cfg' file ..."

    output = file('crab_'+sys.argv[1]+'.cfg','w')
    output.write('[CRAB]\n')
    output.write('jobtype    = cmssw\n')
    output.write('use_server = 0\n')
    output.write('scheduler  = glite\n')
    output.write('\n')

    output.write('[CMSSW]\n')
    output.write('datasetpath = '+sys.argv[2]+'\n')
    output.write('pset = MiniTree_PATwithPF2PAT_forMC_AOD_42X_cfg.py\n')
    output.write('total_number_of_events = -1\n')
    output.write('events_per_job         = 50000\n')
    output.write('output_file            = patTuple.root\n')
    output.write('\n')

    output.write('[USER]\n')
    output.write('publish_data_name = '+sys.argv[1]+'\n')
    output.write('user_remote_dir   = '+sys.argv[1]+'\n')
    output.write('ui_working_dir    = '+sys.argv[1]+'\n')
#output.write('eMail = eric.conte@cern.ch\n')
    output.write('eMail = jean-laurent.agram@cern.ch\n')
    output.write('check_user_remote_dir =0\n')
    output.write('thresholdLevel = 90\n')
    output.write('copy_data = 1\n')
    output.write('publish_data = 1\n')
    output.write('dbs_url_for_publication = https://cmsdbsprod.cern.ch:'
                 + '8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet\n')
    output.write('srm_version = srmv2\n')
    output.write('storage_element = T2_FR_IPHC\n')
    output.write('use_central_bossDB = 0\n')
    output.write('use_boss_rt = 1\n')
    output.write('\n')

    output.write('[GRID]\n')
    output.write('lcg_version = 2\n')
    output.write('rb  = CERN\n')
    output.write('proxy_server = myproxy.cern.ch \n')
    output.write('virtual_organization = cms\n')
    output.write('retry_count = 2\n')
    output.write('lcg_catalog_type = lfc\n')
    output.write('lfc_host = lfc-cms-test.cern.ch\n')
    output.write('lfc_home = /grid/cms\n')
    output.write('ce_white_list = sbgce1.in2p3.fr, '
                 + 'sbgce2.in2p3.fr, sbgce3.in2p3.fr, desy.de\n')
    output.write('\n')
    output.close()

    print "Executing crab ..."
    os.system('crab -create -submit -cfg crab_'+sys.argv[1]+'.cfg')



# Check number of arguments
if len(sys.argv)<2:
    print "Error : wrong number of arguments"
else:
    Execute()



