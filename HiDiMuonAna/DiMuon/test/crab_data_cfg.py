[CRAB]
jobtype = cmssw
### Specify the scheduler to be used.
scheduler = glite
use_server = 1
[CMSSW]
### The data you want to access (to be found on DBS)
datasetpath=/Mu/Run2010A-PromptReco-v1/RECO
### The name of ParameterSet to be used
pset=MuSkim_cfg.py

lumi_mask = jsonfile
total_number_of_lumis=100
number_of_jobs = 50
#runselection= XXX000-XXX999

### The output files produced by your application (comma separated list)
output_file=MuSkim_JSON.root
[USER]
### OUTPUT file management ###
### To have back the job executable output into UI set return_data= 1
return_data = 0
### To copy the CMS executable output into a SE set copy_data = 1
copy_data = 1
### if copy_data = 1 ###
storage_element=srm-cms.cern.ch
storage_path=/srm/managerv2?SFN=/castor/cern.ch
user_remote_dir=/user/k/kumarv/Z0/data
### To publish produced output in a local instance of DBS set publish_data = 1
publish_data=0
### Specify the dataset name. The full path will be //USER
#publish_data_name = yourDataName
### Specify the URL of DBS istance where CRAB has to publish the output files
#dbs_url_for_publication = http://cmssrv17.fnal.gov:8989/DBS108LOC1/servlet/DBSServlet

### To switch from status print on screen to DB serialization to a file specify here the destination files.
### CRAB will create it on CRAB_Working_Dir/share
#xml_report=
[GRID]
### To change the CMS-broker RB/WMS to be used. The ones available for CMS
### are "CERN" and "CNAF": the configuration
### files needed to change the broker will be automatically downloaded from CRAB web page.
### If the files are already present on the working directory they will be used.
#rb = CNAF
### CMS myproxy server, to proxy delegation
proxy_server = myproxy.cern.ch

### To specify  VOMS role and/or group
#role = superman
#group = superheros

### To add other requirements to jdl file, as example the Operating System
#requirements = (other.GlueHostOperatingSystemName == "RedHat")

### To add other parameters to jdl file: semicolon separated list;
#additional_jdl_parameters = AllowZippedISB = false

### To use a specific WMS end point put here the right name:
#wms_service=


## fields written into jdl
virtual_organization = cms

## number or retry count
retry_count = 2


