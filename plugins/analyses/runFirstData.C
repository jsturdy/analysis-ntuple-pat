{
  const double NUMSAMPS = 2;

  gROOT->ProcessLine(".L firstData.C++");

  string infilenames[NUMSAMPS]  = {"/tmp/sturdy/7TeV_Collisions_PATtified.root",
				   "/tmp/sturdy/MinBiasSpring10_7TeV_PATtified.root"};

  string outfilenames[NUMSAMPS] = {"7TeVCollisionData_out.root",
				   "7TeVMinBiasMC_out.root"};

  bool doGen[2] = {false, true};

  for (int z = 0; z < NUMSAMPS; z++) {
    TChain *chainA = new TChain("diJetAnalyzer/AllData");
    chainA->Add(infilenames[z].c_str());
    TTree *treeA = chainA;
    
    firstData treeData(treeA, outfilenames[z], doGen[z]);
    treeData.Loop();
  }
}

