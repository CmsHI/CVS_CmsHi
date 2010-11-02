[CMSSW]
total_number_of_events=5000
number_of_jobs=250
pset=RV_MuSkim_cfg.py
dbs_url = http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet

##Z0 Mu Mu
#datasetpath=/Hydjet_Quenched_MinBias_2760GeV_START39V0_GEN_SIM_RAW_390pre5/davidlw-SingleZmumu_FlatPt0to20_START39V1_GEN_SIM_RECO_390pre5-6dc75065b07f0b7687f52fc678e8a8c4/USER

##JPsi Mu Mu
#datasetpath=/Hydjet_Quenched_MinBias_2760GeV_START39V0_GEN_SIM_RAW_390pre5/davidlw-SingleJPsimumu_FlatPt0to20_START39V1_GEN_SIM_RECO_390pre5-6dc75065b07f0b7687f52fc678e8a8c4/USER

##Upsilon Mu Mu
datasetpath=/Hydjet_Quenched_MinBias_2760GeV_START39V0_GEN_SIM_RAW_390pre5/davidlw-SingleUpsilonmumu_FlatPt0to20_START39V1_GEN_SIM_RECO_390pre5-6dc75065b07f0b7687f52fc678e8a8c4/USER



#datasetpath=none
output_file=RV_Upsilon_MuSkim.root
[USER]
return_data=0
email=Vineet.Kumar@cern.ch
copy_data=1
storage_element=srm-cms.cern.ch
storage_path=/srm/managerv2?SFN=/castor/cern.ch
user_remote_dir=/user/k/kumarv/cmssw390/Z0/UpsilonMuSkim  
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
