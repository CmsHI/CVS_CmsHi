{

   gSystem->Load( "libFWCoreFWLite" );
   gSystem->Load("libDataFormatsFWLite");
   gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
   gSystem->AddIncludePath("-I$CMSSW_RELEASE_BASE/src/");
   AutoLibraryLoader::enable();



}

