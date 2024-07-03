#include "/eos/cms/store/group/phys_heavyions_ops/pchou/ElectroWeak-Jet-Track-Analyses/CorrelationTuple/EventMatcher.h"
#include "/eos/cms/store/group/phys_heavyions_ops/pchou/ElectroWeak-Jet-Track-Analyses/TreeHeaders/ggHiNtuplizerTree.h"
#include "/eos/cms/store/group/phys_heavyions_ops/pchou/ElectroWeak-Jet-Track-Analyses/TreeHeaders/hltObjectTree.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"
void style(){

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLabelFont(43,"xyz");
  gStyle->SetTitleFont(43);
  gStyle->SetTitleFont(43,"xyz");
  gStyle->SetStatFont(43);

  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetOptStat(0); /*don't show statistics box*/
  gStyle->SetOptTitle(0); /*don't show histogram titles*/
  gStyle->SetTitleSize(48, "xyz");
  gStyle->SetTitleOffset(1, "xyz");
  gStyle->SetLabelSize(36, "xyz");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);

  gStyle->SetLineScalePS(1.5);

  gROOT->ForceStyle();
}
/*
float findNcoll(int hiBin) {
   const int nbins = 200;
   const float Ncoll[nbins] = {1976.95, 1944.02, 1927.29, 1891.9, 1845.3, 1807.2, 1760.45, 1729.18, 1674.8, 1630.3, 1590.52, 1561.72, 1516.1, 1486.5, 1444.68, 1410.88, 1376.4, 1347.32, 1309.71, 1279.98, 1255.31, 1219.89, 1195.13, 1165.96, 1138.92, 1113.37, 1082.26, 1062.42, 1030.6, 1009.96, 980.229, 955.443, 936.501, 915.97, 892.063, 871.289, 847.364, 825.127, 806.584, 789.163, 765.42, 751.187, 733.001, 708.31, 690.972, 677.711, 660.682, 640.431, 623.839, 607.456, 593.307, 576.364, 560.967, 548.909, 530.475, 519.575, 505.105, 490.027, 478.133, 462.372, 451.115, 442.642, 425.76, 416.364, 405.154, 392.688, 380.565, 371.167, 360.28, 348.239, 340.587, 328.746, 320.268, 311.752, 300.742, 292.172, 281.361, 274.249, 267.025, 258.625, 249.931, 240.497, 235.423, 228.63, 219.854, 214.004, 205.425, 199.114, 193.618, 185.644, 180.923, 174.289, 169.641, 161.016, 157.398, 152.151, 147.425, 140.933, 135.924, 132.365, 127.017, 122.127, 117.817, 113.076, 109.055, 105.16, 101.323, 98.098, 95.0548, 90.729, 87.6495, 84.0899, 80.2237, 77.2201, 74.8848, 71.3554, 68.7745, 65.9911, 63.4136, 61.3859, 58.1903, 56.4155, 53.8486, 52.0196, 49.2921, 47.0735, 45.4345, 43.8434, 41.7181, 39.8988, 38.2262, 36.4435, 34.8984, 33.4664, 31.8056, 30.351, 29.2074, 27.6924, 26.7754, 25.4965, 24.2802, 22.9651, 22.0059, 21.0915, 19.9129, 19.1041, 18.1487, 17.3218, 16.5957, 15.5323, 14.8035, 14.2514, 13.3782, 12.8667, 12.2891, 11.61, 11.0026, 10.3747, 9.90294, 9.42648, 8.85324, 8.50121, 7.89834, 7.65197, 7.22768, 6.7755, 6.34855, 5.98336, 5.76555, 5.38056, 5.11024, 4.7748, 4.59117, 4.23247, 4.00814, 3.79607, 3.68702, 3.3767, 3.16309, 2.98282, 2.8095, 2.65875, 2.50561, 2.32516, 2.16357, 2.03235, 1.84061, 1.72628, 1.62305, 1.48916, 1.38784, 1.28366, 1.24693, 1.18552, 1.16085, 1.12596, 1.09298, 1.07402, 1.06105, 1.02954};
   return Ncoll[hiBin];
}
*/
void HLTperformance_QCDPhoton_ppref(){

  bool isEB = true;
  bool isVerbose = false;
  //string typeofdata = "QCDPhoton_ppref_1400v60v2_EG10_dr05_123";
  string typeofdata = "QCDPhoton_ppref_1400v60v2_EG10_dr05";

  string folder = "20240601";

  int pt_min = 10, pt_max=90, pt_bin=28;
  int ax_min = 10, ax_max=105;

  //float dRmax = 0.5;
  //float GendRmax = 0.1;
  float dRmax = 0.5;
  float GendRmax = 0.1;

  string EBtxt = "";

  if(isEB)
    EBtxt = "_EB";

  string null_trigger = "HLT_PPRefGEDPhoton10" + EBtxt + "_v";

  vector<string> triggers = vector<string>{"HLT_PPRefGEDPhoton40" + EBtxt + "_v","HLT_PPRefGEDPhoton50" + EBtxt + "_v","HLT_PPRefGEDPhoton60" + EBtxt + "_v"};
  vector<string> trigger_names = vector<string>{"HI GED Photon" + EBtxt + " 40","HI GED Photon" + EBtxt + " 50","HI GED Photon" + EBtxt + " 60"}; 
//
  //vector<string> triggers = vector<string>{"HLT_PPRefGEDPhoton10" + EBtxt + "_v","HLT_PPRefGEDPhoton20" + EBtxt + "_v","HLT_PPRefGEDPhoton30" + EBtxt + "_v"};
  //vector<string> trigger_names = vector<string>{"HI GED Photon" + EBtxt + " 10","HI GED Photon" + EBtxt + " 20","HI GED Photon" + EBtxt + " 30"}; 

  //string filebase = "/data/submit/pinchun/HLT2024/";
  string filebase = "/eos/cms/store/group/phys_heavyions_ops/pchou/";

  //string hltfilebase = "";
  string hltfilebase = "HLT2024_1/CMSSW_14_0_0/src/HLTrigger/Configuration/test/workstation/";

  string frtfile = filebase + "Forest/Pythia8_ppRef_QCDPhoton30_TuneCP5/QCDPhoton_20230524_miniAOD/240417_212103/";
  //string hltfile = filebase + hltfilebase + "openHLT_ppref_MC_QCDPhoton_1400v60v2_20240531.root";
  string hltfile = filebase + hltfilebase + "openHLT_ppref_MC_QCDPhoton_1400v60v2_EG10_20240531l.root";


  //style();
  setTDRStyle();
  gStyle->SetLegendBorderSize(0);

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

  int iPos=11;

  std::cout << "Reading files..." << std::endl;
  //TFile file_hlt("/data/submit/pinchun/ppref_QCDphoton_geom.root","READ");
  //TFile file_for("/data/submit/pinchun/ppref_forest_QCDPhoton.root","READ");

  //TFile::Open("/data/submit/pinchun/QCDPhoton_geom.root");
  //TTree* HltTree = (TTree*) file_hlt.Get("hltanalysis/HltTree");
  //TTree* EventTree = (TTree*) file_for.Get("ggHiNtuplizer/EventTree");
  //TTree* HiTree = (TTree*) file_for.Get("hiEvtAnalyzer/HiTree");

  
  TChain *HltTree = new TChain("hltanalysis/HltTree");
  HltTree->Add(hltfile.c_str());

  TChain *EventTree = new TChain("ggHiNtuplizer/EventTree");
  TChain *HiTree = new TChain("hiEvtAnalyzer/HiTree");

  string frttmp;
  for(int i=0;i<10;i++){
    frttmp = frtfile + "/000" + std::to_string(i) + "/*.root";
    EventTree->Add(frttmp.c_str());
    HiTree   ->Add(frttmp.c_str());
    //cout<<"Add: "<<frttmp<<endl;
  }

  
  TChain *Tree10 = new TChain(("hltobject/" + null_trigger).c_str());
  TChain *Tree40 = new TChain(("hltobject/" + triggers[0] ).c_str());
  TChain *Tree50 = new TChain(("hltobject/" + triggers[1] ).c_str());
  TChain *Tree60 = new TChain(("hltobject/" + triggers[2] ).c_str());
/*
  TChain *Tree10 = new TChain("hltobject/HLT_PPRefGEDPhoton10_EB_v");
  TChain *Tree40 = new TChain("hltobject/HLT_PPRefGEDPhoton40_EB_v");
  TChain *Tree50 = new TChain("hltobject/HLT_PPRefGEDPhoton50_EB_v");
  TChain *Tree60 = new TChain("hltobject/HLT_PPRefGEDPhoton60_EB_v");
*/
  Tree10->Add(hltfile.c_str());
  Tree40->Add(hltfile.c_str());
  Tree50->Add(hltfile.c_str());
  Tree60->Add(hltfile.c_str());


  
  TH1F* hdenom   = new TH1F("hdenom","",pt_bin,pt_min,pt_max);
  TH1F* hnum40   = new TH1F("hnum40","",pt_bin,pt_min,pt_max);
  TH1F* hnum50   = new TH1F("hnum50","",pt_bin,pt_min,pt_max);
  TH1F* hnum60   = new TH1F("hnum60","",pt_bin,pt_min,pt_max);

  EventMatcher* emTrig = 0;
  emTrig = new EventMatcher();

  EventMatcher* em = new EventMatcher();

  Long64_t duplicateEntriesHlt = 0;
  Long64_t entriesAnalyzedHlt = 0;
  //Long64_t nFilesSkipped=0;


  Tree10->SetBranchStatus("*",0);
  Tree40->SetBranchStatus("*",0);
  Tree50->SetBranchStatus("*",0);
  Tree60->SetBranchStatus("*",0);

  Tree10->SetBranchStatus("eta", 1);
  Tree40->SetBranchStatus("eta", 1);
  Tree50->SetBranchStatus("eta", 1);
  Tree60->SetBranchStatus("eta", 1);

  Tree10->SetBranchStatus("phi", 1);
  Tree40->SetBranchStatus("phi", 1);
  Tree50->SetBranchStatus("phi", 1);
  Tree60->SetBranchStatus("phi", 1);

  Tree10->SetBranchStatus("pt", 1);
  Tree40->SetBranchStatus("pt", 1);
  Tree50->SetBranchStatus("pt", 1);
  Tree60->SetBranchStatus("pt", 1);




  HltTree->SetBranchStatus("*",0);
  HltTree->SetBranchStatus("Event", 1);
  HltTree->SetBranchStatus("LumiBlock", 1);
  HltTree->SetBranchStatus("Run", 1);

  //HltTree->SetBranchStatus("HLT_PPRefGEDPhoton50_EB_v", 1);
  //HltTree->SetBranchStatus("HLT_PPRefGEDPhoton60_EB_v", 1);
  //HltTree->SetBranchStatus("HLT_PPRefGEDPhoton40_EB_v", 1);

  HltTree->SetBranchStatus(triggers[0].c_str(), 1);
  HltTree->SetBranchStatus(triggers[1].c_str(), 1);
  HltTree->SetBranchStatus(triggers[2].c_str(), 1);
  HltTree->SetBranchStatus(null_trigger.c_str(), 1);

  HiTree->SetBranchStatus("*",0);
  HiTree->SetBranchStatus("hiBin",1);
  HiTree->SetBranchStatus("hiHF",1);
  HiTree->SetBranchStatus("weight",1);


  ULong64_t       hlt_event;
  Int_t           hlt_lumi, hlt_run, hiBin;
  Float_t         hiHF, pthat_weight;

  //Bool_t HLT_HIGEDPhoton10_EB_v, HLT_HIGEDPhoton20_EB_v, HLT_HIGEDPhoton30_EB_v;
  //Bool_t HLT_HIGEDPhoton40_EB_v, HLT_HIGEDPhoton50_EB_v, HLT_HIGEDPhoton60_EB_v;
  Bool_t HLT_HIGEDPhoton40, HLT_HIGEDPhoton50, HLT_HIGEDPhoton60, HLT_HIGEDPhoton10;

  HiTree->SetBranchAddress("hiBin", &hiBin);
  HiTree->SetBranchAddress("hiHF", &hiHF);
  HiTree->SetBranchAddress("weight", &pthat_weight);

  HltTree->SetBranchAddress("Event", &hlt_event);
  HltTree->SetBranchAddress("LumiBlock", &hlt_lumi);
  HltTree->SetBranchAddress("Run", &hlt_run);
/*
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton50_EB_v", &HLT_HIGEDPhoton50);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton60_EB_v", &HLT_HIGEDPhoton60);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton40_EB_v", &HLT_HIGEDPhoton40);
*/
  HltTree->SetBranchAddress(triggers[0].c_str(), &HLT_HIGEDPhoton40);
  HltTree->SetBranchAddress(triggers[1].c_str(), &HLT_HIGEDPhoton50);
  HltTree->SetBranchAddress(triggers[2].c_str(), &HLT_HIGEDPhoton60);

  if( null_trigger.compare(triggers[0]) != 0 )
    HltTree->SetBranchAddress(null_trigger.c_str(), &HLT_HIGEDPhoton10);

  EventTree->SetBranchStatus("*",0);
  EventTree->SetBranchStatus("run",1);
  EventTree->SetBranchStatus("event",1);
  EventTree->SetBranchStatus("lumis",1);

  EventTree->SetBranchStatus("nPho",1);
  //EventTree->SetBranchStatus("nEle",1);
  EventTree->SetBranchStatus("mcPID",1);

  EventTree->SetBranchStatus("pho_genMatchedIndex",1);
  EventTree->SetBranchStatus("mcIndex",1);

  EventTree->SetBranchStatus("phoEt",1);
  EventTree->SetBranchStatus("phoEta",1);
  EventTree->SetBranchStatus("phoHoverE",1);
  EventTree->SetBranchStatus("phoPhi",1);

  EventTree->SetBranchStatus("phoSigmaIEtaIEta_2012",1);

  EventTree->SetBranchStatus("mcCalIsoDR04",1);
  EventTree->SetBranchStatus("pfpIso3subUE",1);
  EventTree->SetBranchStatus("pfcIso3subUE",1);
  EventTree->SetBranchStatus("pfnIso3subUE",1);

  /*
  EventTree->SetBranchStatus("pho_swissCrx",1);
  EventTree->SetBranchStatus("pho_seedTime",1);

 
  EventTree->SetBranchStatus("pho_ecalClusterIsoR3",1);
  EventTree->SetBranchStatus("pho_hcalRechitIsoR3",1);
  EventTree->SetBranchStatus("pho_trackIsoR3PtCut20",1);
   */

  EventTree->SetBranchStatus("mcEta",1);
  EventTree->SetBranchStatus("mcPhi",1);

  //EventTree->SetBranchStatus("phoSCEta",1);
  //EventTree->SetBranchStatus("phoSCPhi",1);

/*
  ULong64_t       forest_event;
  UInt_t          forest_lumi, forest_run;
  vector<float>   phoEt, phoEta, phoHoverE;
  int nPho, nEle;

  EventTree->SetBranchAddress("event", &forest_event);
  EventTree->SetBranchAddress("lumis", &forest_lumi);
  EventTree->SetBranchAddress("run", &forest_run);

  EventTree->SetBranchAddress("nPho", &nPho);
  EventTree->SetBranchAddress("nEle", &nEle);

  EventTree->SetBranchAddress("phoEt", &phoEt);
  EventTree->SetBranchAddress("phoEta", &phoEta);
  EventTree->SetBranchAddress("phoHoverE", &phoHoverE);
*/

  Long64_t entriesHlt = HltTree->GetEntries();
  std::cout << "entries in HLT = " << entriesHlt << std::endl;

  std::cout << "Loop over the file with HLT emulation output..." << std::endl;

  for (Long64_t j_entry = 0; j_entry < entriesHlt; ++j_entry){
    if (j_entry % 10000 == 0)  {
        std::cout << "current entry = " <<j_entry<< " out of " <<entriesHlt<< " : " <<std::setprecision(2)<<(double)j_entry/entriesHlt*100<< " %" << std::endl;
    }
    HltTree->GetEntry(j_entry);

    if( null_trigger.compare(triggers[0]) == 0 )
      HLT_HIGEDPhoton10 = HLT_HIGEDPhoton40;

    bool eventAdded = emTrig->addEvent(hlt_run, hlt_lumi, hlt_event, j_entry);
    if(!eventAdded) // this event is duplicate, skip this one.
    {
        duplicateEntriesHlt++;
        continue;
    }
    entriesAnalyzedHlt++;

  }

  std::cout << "###" << std::endl;
  std::cout << "Loop HLT ENDED" << std::endl;
  std::cout << "entries HLT          = " << entriesHlt << std::endl;
  std::cout << "duplicateEntries HLT = " << duplicateEntriesHlt << std::endl;
  std::cout << "entriesAnalyzed HLT  = " << entriesAnalyzedHlt << std::endl;
  //std::cout << "nFilesSkipped  = " << nFilesSkipped << std::endl;
  std::cout << "###" << std::endl;

  std::cout << "Loop over the file with offline reco output..." << std::endl;


  //treeggHiNtuplizer = (TTree*)fileTmp->Get(treePath.c_str());

  ggHiNtuplizer ggHi;
  ggHi.setupTreeForReading(EventTree);



  hltObject ho40;
  ho40.setupTreeForReading(Tree40);

  hltObject ho50;
  ho50.setupTreeForReading(Tree50);

  hltObject ho60;
  ho60.setupTreeForReading(Tree60);

  hltObject ho10;
  if( null_trigger.compare(triggers[0]) == 0 )
    ho10 = ho40;
  else
    ho10.setupTreeForReading(Tree10);



  Long64_t entriesTmp = EventTree->GetEntries();
  std::cout << "entries in File = " << entriesTmp << std::endl;

  Long64_t entryTrig = 0;
  Int_t entriesNotFoundinTrigger=0;
  Int_t duplicateEntries=0, entriesAnalyzed=0;

  Int_t count0=0, count40=0, count50=0, count60=0;

  if(isVerbose)
    cout<<"Photons with pT>70 but HLT_PPRefGEDPhoton40 not triggered:"<<endl;

  for (Long64_t j_entry = 0; j_entry < entriesTmp; ++j_entry){
    if (j_entry % 10000 == 0)  {
        std::cout << "current entry = " <<j_entry<< " out of " <<entriesTmp<< " : " <<std::setprecision(2)<<(double)j_entry/entriesTmp*100<< " %" << std::endl;
    }

    EventTree->GetEntry(j_entry);
    HiTree->GetEntry(j_entry);

    entryTrig = emTrig->getEntry(ggHi.run, ggHi.lumis, ggHi.event);
    //entryTrig = emTrig->getEntry(forest_run, forest_lumi, forest_event);

    //bool eventAdded = em->addEvent(forest_run, forest_lumi, forest_event, j_entry);
    bool eventAdded = em->addEvent(ggHi.run, ggHi.lumis, ggHi.event, j_entry);
    if(!eventAdded) // this event is duplicate, skip this one.
    {
        duplicateEntries++;
        continue;
    }

    if (entryTrig < 0) {
      entriesNotFoundinTrigger++;
      continue;
    }

    //emTrig->removeEvent(forest_run, forest_lumi, forest_event);
    emTrig->removeEvent(ggHi.run, ggHi.lumis, ggHi.event);

    entriesAnalyzed++;

    //cout<<"entryTrig = "<<entryTrig<<endl;
    HltTree->GetEntry(entryTrig);

    
    Tree10->GetEntry(entryTrig);
    Tree40->GetEntry(entryTrig);
    Tree50->GetEntry(entryTrig);
    Tree60->GetEntry(entryTrig);
    

    //cout<<"HLT_HIGEDPhoton40_EB_v = "<<HLT_HIGEDPhoton40_EB_v<<", HLT_HIGEDPhoton50_EB_v = "<<HLT_HIGEDPhoton50_EB_v<<", HLT_HIGEDPhoton60_EB_v = "<<HLT_HIGEDPhoton60_EB_v<<endl;

    //int hlt40 = HLT_HIGEDPhoton40_EB_v, hlt50 = HLT_HIGEDPhoton50_EB_v, hlt60 = HLT_HIGEDPhoton60_EB_v;

    //if(ggHi.nPho>0) cout<<"nPho = "<<ggHi.nPho<<endl;
    //if(nEle>0) cout<<"nEle = "<<nEle<<endl;

    float sumIso, maxPt=0;
    int maxPt_i = -1;

    //vector<float> eta40, eta50, eta60, phi40, phi50, phi60;

    //cout<<"Loop into the photons in the event."<<endl;
    //pho_genMatchedIndex mcIndex

    float dr00;
    for(int i=0; i < ggHi.nPho; ++i) {
      int64_t genID = (*ggHi.pho_genMatchedIndex)[i];
      if (genID == -1) { continue; }
      auto pid = (*ggHi.mcPID)[genID];
      auto mpid = (*ggHi.mcMomPID)[genID];
      if (pid != 22 || (std::abs(mpid) > 22 && mpid != -999)) continue;
      //if(((*ggHi.mcPID)[i]!=22) || ((*ggHi.pho_genMatchedIndex)[i]!=(*ggHi.mcIndex)[i])) continue;
      dr00 = sqrt(((*ggHi.mcEta)[genID]-(*ggHi.phoEta)[i])*((*ggHi.mcEta)[genID]-(*ggHi.phoEta)[i])+((*ggHi.mcPhi)[genID]-(*ggHi.phoPhi)[i])*((*ggHi.mcPhi)[genID]-(*ggHi.phoPhi)[i]));
      if(dr00 > GendRmax) continue;
      if((*ggHi.phoEt)[i]>maxPt){
        maxPt = (*ggHi.phoEt)[i]; 
        maxPt_i = i;
      }
    }


    if(maxPt_i==-1) continue;
    //cout<<"maxPt_i = "<<maxPt_i<<endl;
    //cout<<"phoEt[maxPt_i] = "<<(*ggHi.phoEt)[maxPt_i]<<endl;

    //sumIso = (*ggHi.pho_ecalClusterIsoR3)[maxPt_i]+(*ggHi.pho_hcalRechitIsoR3)[maxPt_i]+(*ggHi.pho_trackIsoR3PtCut20)[maxPt_i];

    sumIso =  (*ggHi.pfpIso3subUE)[maxPt_i]+(*ggHi.pfcIso3subUE)[maxPt_i]+(*ggHi.pfnIso3subUE)[maxPt_i];

    //cout<<"Photon Selection"<<endl;

    float dr10, dr40, dr50, dr60;

    bool sel_cut = kFALSE;
    if(abs((*ggHi.phoSCEta)[maxPt_i]) < 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.072266 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.010806 && sumIso < 0.416894) sel_cut=kTRUE;
    else if(!isEB && abs((*ggHi.phoSCEta)[maxPt_i]) > 1.57 && abs((*ggHi.phoSCEta)[maxPt_i]) < 2.1 && (*ggHi.phoHoverE)[maxPt_i] < 0.032548 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.027323 && sumIso < 0.970591) sel_cut=kTRUE;
    else sel_cut = kFALSE;

    //VETO
    //bool sel_cut = kFALSE;
    //if(abs((*ggHi.phoEta)[maxPt_i]) < 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.069 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] > 0.002 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.0106 && sumIso < 20.164) sel_cut=kTRUE;
    //else if(abs((*ggHi.phoEta)[maxPt_i]) > 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.0544 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] > 0.002 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.0267 && sumIso < 46.273 ) sel_cut=kTRUE;
    //else sel_cut = kFALSE;

    //TIGHT
    //bool sel_cut = kFALSE;
    //if(abs((*ggHi.phoEta)[maxPt_i]) < 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.022 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] > 0.002 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.0102 && sumIso < 0.267) sel_cut=kTRUE;
    //else if(abs((*ggHi.phoEta)[maxPt_i]) > 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.0351 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] > 0.002 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.0262 && sumIso < 22.656 ) sel_cut=kTRUE;
    //else sel_cut = kFALSE;

    //if(/*hiHF > 3039.47 &&  */abs((*ggHi.phoEta)[maxPt_i]) < 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.069 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] > 0.002 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.0106 /*&& (*ggHi.pho_swissCrx)[maxPt_i] < 0.9 && abs((*ggHi.pho_seedTime)[maxPt_i]) < 3  && sumIso < 5&& (*ggHi.mcCalIsoDR04)[maxPt_i]<5*/){
    //if(/*hiHF > 3039.47 &&  */abs((*ggHi.phoEta)[maxPt_i]) < 1.44){
    //if(/*hiHF > 3039.47 &&  */abs((*ggHi.phoEta)[maxPt_i]) < 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.2 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] > 0.002 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.01 /*&& (*ggHi.pho_swissCrx)[maxPt_i] < 0.9 && abs((*ggHi.pho_seedTime)[maxPt_i]) < 3 && sumIso < 5*/){
    //if(abs((*ggHi.phoEta)[maxPt_i]) > 1.44 && (*ggHi.phoHoverE)[maxPt_i] < 0.3 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] > 0.002 && (*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i] < 0.034 && (*ggHi.pho_swissCrx)[maxPt_i] < 0.9 && abs((*ggHi.pho_seedTime)[maxPt_i]) < 3 && sumIso < 5){
    if(sel_cut==kTRUE){
        //cout<<"phoEt[maxPt_i] = "<<(*ggHi.phoEt)[maxPt_i]<<endl;

        //cout<<"hiHF = "<<hiHF<<endl;
        //dr00 = sqrt(((*ggHi.mcEta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])*((*ggHi.mcEta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])+((*ggHi.mcPhi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i])*((*ggHi.mcPhi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i]));
        //cout<<"dr00 = "<<dr00<<endl;
        //if(dr00 > dRmax) continue;

        //if(HLT_HIGEDPhoton40>0) dr40 = sqrt(((*ho40.eta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])*((*ho40.eta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])+((*ho40.phi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i])*((*ho40.phi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i]));
        //if(HLT_HIGEDPhoton50>0) dr50 = sqrt(((*ho50.eta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])*((*ho50.eta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])+((*ho50.phi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i])*((*ho50.phi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i]));
        //if(HLT_HIGEDPhoton60>0) dr60 = sqrt(((*ho60.eta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])*((*ho60.eta)[maxPt_i]-(*ggHi.phoEta)[maxPt_i])+((*ho60.phi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i])*((*ho60.phi)[maxPt_i]-(*ggHi.phoPhi)[maxPt_i]));
        //
        //if(HLT_HIGEDPhoton10>0) dr10 = sqrt(((*ho10.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])*((*ho10.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])+((*ho10.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i])*((*ho10.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i]));
        //if(HLT_HIGEDPhoton40>0) dr40 = sqrt(((*ho40.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])*((*ho40.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])+((*ho40.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i])*((*ho40.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i]));
        //if(HLT_HIGEDPhoton50>0) dr50 = sqrt(((*ho50.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])*((*ho50.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])+((*ho50.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i])*((*ho50.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i]));
        //if(HLT_HIGEDPhoton60>0) dr60 = sqrt(((*ho60.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])*((*ho60.eta)[maxPt_i]-(*ggHi.mcEta)[maxPt_i])+((*ho60.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i])*((*ho60.phi)[maxPt_i]-(*ggHi.mcPhi)[maxPt_i]));
  

        //if(dr10>0.4||dr40>0.4||dr50>0.4||dr60>0.4) continue;


        hdenom->Fill((*ggHi.phoEt)[maxPt_i],pthat_weight);count0++;
/*
        cout<<"hdenom fill done"<<endl;
        if(HLT_HIGEDPhoton40_EB_v>0) {
          cout<<"(*ho40.eta)[maxPt_i] = "<<(*ho40.eta)[maxPt_i]<<", (*ggHi.phoEta)[maxPt_i] = "<<(*ggHi.phoEta)[maxPt_i]<<endl;
          cout<<"(*ho40.phi)[maxPt_i] = "<<(*ho40.phi)[maxPt_i]<<", (*ggHi.phoPhi)[maxPt_i] = "<<(*ggHi.phoPhi)[maxPt_i]<<endl;
        }

*/      
        float n_pho_ho = 0;

        float dr40temp, dr50temp, dr60temp;

        float dr10temp;


        dr40 = 10000, dr50 = 10000, dr60 = 10000;
        dr10 = 10000;

        if(HLT_HIGEDPhoton40==0&&HLT_HIGEDPhoton10>0){

          n_pho_ho = size(*ho10.eta);
          //cout<<"n_pho_ho 10 ="<<n_pho_ho<<endl;
          for(int i=0;i<n_pho_ho;i++){
            dr10temp = sqrt(((*ho10.eta)[i]-(*ggHi.phoEta)[maxPt_i])*((*ho10.eta)[i]-(*ggHi.phoEta)[maxPt_i])+((*ho10.phi)[i]-(*ggHi.phoPhi)[maxPt_i])*((*ho10.phi)[i]-(*ggHi.phoPhi)[maxPt_i]));
            //if((*ggHi.phoEt)[maxPt_i] > 70 && dr10 < dRmax) 
            if (dr10temp < dr10) dr10=dr10temp;
          }

          if(isVerbose && (*ggHi.phoEt)[maxPt_i] > 70 && dr10 < dRmax) {

            cout<<"Run:"<<hlt_run<<", LumiBlock: "<<hlt_lumi<<", Event: "<<hlt_event<<endl;
            cout<<"HLT_PPRefGEDPhoton10 = "<<HLT_HIGEDPhoton10<<", HLT_PPRefGEDPhoton40 = "<<HLT_HIGEDPhoton40<<", HLT_PPRefGEDPhoton50 = "<<HLT_HIGEDPhoton40<<", HLT_PPRefGEDPhoton60 = "<<HLT_HIGEDPhoton40<<std::endl;
            std::cout<<"phoEt = "<<(*ggHi.phoEt)[maxPt_i]<<", phoEta = "<<(*ggHi.phoEta)[maxPt_i]<<", phoPhi = "<<(*ggHi.phoPhi)[maxPt_i]<<", dr = "<<dr10<<std::endl;
            cout<<"phoHoverE = "<<(*ggHi.phoHoverE)[maxPt_i]<<", phoSigmaIEtaIEta_2012 = "<<(*ggHi.phoSigmaIEtaIEta_2012)[maxPt_i]<<endl;
            for(int i=0;i<n_pho_ho;i++) cout<<"(*ho10.eta)["<<i<<"] = "<<(*ho10.eta)[i]<<", (*ho10.phi)["<<i<<"] = "<<(*ho10.phi)[i]<<", dr = "<<sqrt(((*ho10.eta)[i]-(*ggHi.phoEta)[maxPt_i])*((*ho10.eta)[i]-(*ggHi.phoEta)[maxPt_i])+((*ho10.phi)[i]-(*ggHi.phoPhi)[maxPt_i])*((*ho10.phi)[i]-(*ggHi.phoPhi)[maxPt_i]))<<", (*ho10.pt)["<<i<<"] = "<<(*ho10.pt)[i]<<endl;
            cout<<"------------"<<endl;
          }
        }
        


        if(HLT_HIGEDPhoton40>0){
         n_pho_ho = size(*ho40.eta);
         //cout<<"n_pho_ho 40 ="<<n_pho_ho<<endl;
         for(int i=0;i<n_pho_ho;i++){
          dr40temp = sqrt(((*ho40.eta)[i]-(*ggHi.phoEta)[maxPt_i])*((*ho40.eta)[i]-(*ggHi.phoEta)[maxPt_i])+((*ho40.phi)[i]-(*ggHi.phoPhi)[maxPt_i])*((*ho40.phi)[i]-(*ggHi.phoPhi)[maxPt_i]));
          if (dr40temp < dr40) dr40=dr40temp;
         }
        }
        if(HLT_HIGEDPhoton50>0){
          n_pho_ho = size(*ho50.eta);
          //cout<<"n_pho_ho 50 ="<<n_pho_ho<<endl;
          for(int i=0;i<n_pho_ho;i++){
          dr50temp = sqrt(((*ho50.eta)[i]-(*ggHi.phoEta)[maxPt_i])*((*ho50.eta)[i]-(*ggHi.phoEta)[maxPt_i])+((*ho50.phi)[i]-(*ggHi.phoPhi)[maxPt_i])*((*ho50.phi)[i]-(*ggHi.phoPhi)[maxPt_i]));
          if (dr50temp < dr50) dr50=dr50temp;
         }
        }
        if(HLT_HIGEDPhoton60>0){
          n_pho_ho = size(*ho60.eta);
          //cout<<"n_pho_ho 60 ="<<n_pho_ho<<endl;
          for(int i=0;i<n_pho_ho;i++){
          dr60temp = sqrt(((*ho60.eta)[i]-(*ggHi.phoEta)[maxPt_i])*((*ho60.eta)[i]-(*ggHi.phoEta)[maxPt_i])+((*ho60.phi)[i]-(*ggHi.phoPhi)[maxPt_i])*((*ho60.phi)[i]-(*ggHi.phoPhi)[maxPt_i]));
          if (dr60temp < dr60) dr60=dr60temp;
         }
        }
        
        
        //cout<<"dr40 = "<<dr40<<", dr50 = "<<dr50<<", dr60 = "<<dr60<<endl;
        //dr40 = dr00, dr50 = dr00, dr60 = dr00;
        //cout<<"*(*ho40.eta)[maxPt_i] = "<<(*ho40.eta)[maxPt_i]<<", *(*ho50.eta)[maxPt_i] = "<<(*ho50.eta)[maxPt_i]<<", *(*ho60.eta)[maxPt_i] = "<<(*ho60.eta)[maxPt_i]<<endl;
        
        //cout<<"dr40 = "<<dr40<<", dr50 = "<<dr50<<", dr60 = "<<dr60<<endl;
        //cout<<"HLT_HIGEDPhoton40 = "<<HLT_HIGEDPhoton40<<", HLT_HIGEDPhoton50 = "<<HLT_HIGEDPhoton50<<", HLT_HIGEDPhoton60 = "<<HLT_HIGEDPhoton60<<endl;

        if(HLT_HIGEDPhoton40>0 && dr40 < dRmax){hnum40->Fill((*ggHi.phoEt)[maxPt_i],pthat_weight); count40++;}
        if(HLT_HIGEDPhoton50>0 && dr50 < dRmax){hnum50->Fill((*ggHi.phoEt)[maxPt_i],pthat_weight); count50++;}
        if(HLT_HIGEDPhoton60>0 && dr60 < dRmax){hnum60->Fill((*ggHi.phoEt)[maxPt_i],pthat_weight); count60++;}
      }


/*
    for(int i=0; i < ggHi.nPho; ++i) {

      if((*ggHi.mcPID)[i]!=22) continue;

      sumIso = (*ggHi.pho_ecalClusterIsoR3)[i]+(*ggHi.pho_hcalRechitIsoR3)[i]+(*ggHi.pho_trackIsoR3PtCut20)[i];

      //cout<<"phoEta[i] = "<<(*ggHi.phoEta)[i]<<", phoHoverE[i] = "<<(*ggHi.phoHoverE)[i]<<endl;

      //if ((*ggHi.phoSCEta)[i]<-1.39&&(*ggHi.phoSCPhi)[i]<-0.9&&(*ggHi.phoSCPhi)[i]>-1.6) continue;

      if(abs((*ggHi.phoEta)[i]) < 1.44 && (*ggHi.phoHoverE)[i] < 0.1 && (*ggHi.phoSigmaIEtaIEta_2012)[i] > 0.002 && (*ggHi.pho_swissCrx)[i] < 0.9 && abs((*ggHi.pho_seedTime)[i]) < 3 && sumIso < 5){
        //cout<<"phoEt[i] = "<<(*ggHi.phoEt)[i]<<endl;

        hdenom->Fill((*ggHi.phoEt)[i]);count0++;

        float dr40 = sqrt((*eta40[i]-(*ggHi.phoEta)[i])*(*eta40[i]-(*ggHi.phoEta)[i])+(*phi40[i]-(*ggHi.phoPhi)[i])*(*phi40[i]-(*ggHi.phoPhi)[i]));
        float dr50 = sqrt((*eta50[i]-(*ggHi.phoEta)[i])*(*eta50[i]-(*ggHi.phoEta)[i])+(*phi50[i]-(*ggHi.phoPhi)[i])*(*phi50[i]-(*ggHi.phoPhi)[i]));
        float dr60 = sqrt((*eta60[i]-(*ggHi.phoEta)[i])*(*eta60[i]-(*ggHi.phoEta)[i])+(*phi60[i]-(*ggHi.phoPhi)[i])*(*phi60[i]-(*ggHi.phoPhi)[i]));
        
        cout<<"dr40 = "<<dr40<<", dr50 = "<<dr50<<", dr60 = "<<dr60<<endl;
        if(HLT_HIGEDPhoton40_EB_v>0 && dr40 < 0.4){hnum40->Fill((*ggHi.phoEt)[i]); count40++;}
        if(HLT_HIGEDPhoton50_EB_v>0 && dr50 < 0.4){hnum50->Fill((*ggHi.phoEt)[i]); count50++;}
        if(HLT_HIGEDPhoton60_EB_v>0 && dr60 < 0.4){hnum60->Fill((*ggHi.phoEt)[i]); count60++;}
      }

    }
    */

  }

  std::cout << "count0 = "<<count0<<", count40 = "<<count40<<", count50 = "<<count50<<", count60 = "<<count60 << std::endl;

  std::cout << "###" << std::endl;
  std::cout << "Loop Forest ENDED"  << std::endl;
  std::cout << "entries Forest          = " << entriesTmp << std::endl;
  std::cout << "duplicateEntries Forest = " << duplicateEntries << std::endl;
  std::cout << "entriesAnalyzed Forest  = " << entriesAnalyzed << std::endl;
  std::cout << "entriesNotFoundinTrigger  = " << entriesNotFoundinTrigger << std::endl;
  std::cout << "###" << std::endl;

  TCanvas *canvas1 = new TCanvas("canvas1","Comparison of two histograms",1000,800);
  canvas1->SetMargin(0.15, 0.05, 0.15, 0.08);
  canvas1->GetFrame()->SetBorderSize(12);

  TGraphAsymmErrors* hratio[3];

  hratio[0] = new TGraphAsymmErrors();
  hratio[1] = new TGraphAsymmErrors();
  hratio[2] = new TGraphAsymmErrors();

  hratio[0] ->SetName("hratio40");
  hratio[1] ->SetName("hratio50");
  hratio[2] ->SetName("hratio60");

  hratio[0]->BayesDivide(hnum40, hdenom);
  hratio[1]->BayesDivide(hnum50, hdenom);
  hratio[2]->BayesDivide(hnum60, hdenom);


  hratio[0]->GetXaxis()->SetTitle("p^{#gamma}_{T} [GeV/c]");
  hratio[0]->GetYaxis()->SetTitle("HLT Efficiency");
  hratio[0]->SetMarkerStyle(kFullCircle);
  hratio[0]->SetMarkerColor(kBlack);
  hratio[0]->SetMarkerSize(2);
  hratio[0]->SetLineColor(kBlack);
  //hratio40->Draw("p e");
  //hratio40->Draw("AP");


  //hratio50 = (TH1D*)hnum50->Clone("hratio50");
  //hratio50->Divide(hdenom);

  hratio[1]->SetMarkerStyle(kFullTriangleUp);
  hratio[1]->SetMarkerColor(kBlue);
  hratio[1]->SetMarkerSize(2);
  hratio[1]->SetLineColor(kBlue);
  //hratio50->Draw("same p e");
  //hratio50->Draw("same AP");

  //hratio60 = (TH1D*)hnum60->Clone("hratio60");
  //hratio60->Divide(hdenom);

  hratio[2]->SetMarkerStyle(kFullSquare);
  hratio[2]->SetMarkerColor(kRed);
  hratio[2]->SetMarkerSize(2);
  hratio[2]->SetLineColor(kRed);
  //hratio60->Draw("same p e");
  //hratio60->Draw("same AP");

  hratio[0]->SetMinimum(0);
  hratio[0]->SetMaximum(1.2);
  //hratio[1]->SetMinimum(20);
  //hratio[2]->SetMinimum(20);

  hratio[0]->GetXaxis()->SetLimits(ax_min,ax_max);
  //hratio[0]->GetYaxis()->SetLimits(0,1.2);

  hratio[0]->Draw("AP");
  hratio[1]->Draw("P");
  hratio[2]->Draw("P");

  //float endcap_legendpp = 0.3;
  float endcap_legendpp = 0;

  TLegend leg(0.58,0.18+endcap_legendpp,0.98,0.4+endcap_legendpp);

  leg.AddEntry(hratio[0] ,trigger_names[0].c_str(),"ep");
  leg.AddEntry(hratio[1] ,trigger_names[1].c_str(),"ep");
  leg.AddEntry(hratio[2] ,trigger_names[2].c_str(),"ep");
  
  leg.SetFillColorAlpha(kWhite,0);
  leg.Draw();

  TLine *l1 = new TLine(ax_min,1,ax_max,1);
  l1->SetLineWidth(2);
  l1->SetLineStyle(2);
  l1->Draw();

  TLatex *pt = new TLatex(0.78,0.42+endcap_legendpp,"|#eta^{#gamma}| < 1.44");
  pt->SetTextFont(42);
  pt->SetNDC(kTRUE);

  if(isEB)
    pt->Draw();

/*
  TLatex *pt1 = new TLatex(0.4,0.95,"pp ref, #sqrt{s_{NN}} = 5.02 TeV, Run 3 Simulation");
  pt1->SetTextFont(42);
  pt1->SetNDC(kTRUE);
  pt1->Draw();
*/

  lumi_sqrtS = "pp ref, #sqrt{s_{NN}} = 5.36 TeV, 2024 Simulation";

  CMS_lumi( canvas1, iPeriod, iPos );

  gSystem->Exec(("mkdir -p figs/" + folder ).c_str());

  //canvas1->SaveAs("figs/20240530/HLTEff_QCDPhoton_ppref_1320V32_tag132X2023.pdf"); //_cent10 _EB _onlyL1
  canvas1->SaveAs(("figs/" + folder + "/HLTEff_" + typeofdata + EBtxt + ".png").c_str()); //_cent10 _EB _onlyL1


}