[CMSSW]
scheduler    = caf
[CAF]
queue = cmscaf1nd
total_number_of_events=498079
pset=ExSt_MuSkim_cfg.py
#dbs_url = http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet
#dbs_url = http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet
dbs_url = http://cmsdbsprod.cern.ch/cms_dbs_caf_analysis_01/servlet/DBSServlet
##HI Data
#datasetpath=/HICorePhysics/HIRun2010-PromptReco-v1/RECO
#datasetpath=/HIAllPhysics/HIRun2010-PromptReco-v1/RECO
datasetpath=/HIExpressPhysics/HIRun2010-Express-v2/FEVT
total_number_of_lumis = -1
lumis_per_job = 100
#get_edm_output = 1
#lumi_mask = jsonfile
#total_number_of_lumis=100
#number_of_jobs = 10

##Z0 Mu Mu
#datasetpath=/Hydjet_Quenched_MinBias_2760GeV_START39V0_GEN_SIM_RAW_390pre5/davidlw-SingleZmumu_FlatPt0to20_START39V1_GEN_SIM_RECO_390pre5-6dc75065b07f0b7687f52fc678e8a8c4/USER
##JPsi Mu Mu
#datasetpath=/Hydjet_Quenched_MinBias_2760GeV_START39V0_GEN_SIM_RAW_390pre5/davidlw-SingleJPsimumu_FlatPt0to20_START39V1_GEN_SIM_RECO_390pre5-6dc75065b07f0b7687f52fc678e8a8c4/USER
##Upsilon Mu Mu
#datasetpath=/Hydjet_Quenched_MinBias_2760GeV_START39V0_GEN_SIM_RAW_390pre5/davidlw-SingleUpsilonmumu_FlatPt0to20_START39V1_GEN_SIM_RECO_390pre5-6dc75065b07f0b7687f52fc678e8a8c4/USER

#datasetpath=none
output_file=HI_ExSt_MuSkim_V2.root
[USER]
return_data=0
email=Vineet.Kumar@cern.ch
copy_data=1
storage_element=srm-cms.cern.ch
storage_path=/srm/managerv2?SFN=/castor/cern.ch
user_remote_dir=/user/k/kumarv/cms391/HiData/ExSt  
#additional_input_files=/afs/cern.ch/user/k/kumarv/scratch0/CMSSW_3_3_1/src1/GridUPC/starlight.up1s.ee.hepmc-00.dat
#additional_input_files=none
publish_data = 0
publish_data_name = YourName_Data
dbs_url_for_publication = https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_01_writer/servlet/DBSServlet
[CRAB]
scheduler=glite
jobtype=cmssw
#server_name=bari
[GRID]
lcg_version=2
rb=CERN
proxy_server=myproxy.cern.ch
virtual_organization=cms
retry_count=2
## LFC catalog parameters
lcg_catalog_type = lfc
lfc_host = lfc-cms-test.cern.ch
lfc_home = /grid/cms
