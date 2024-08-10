#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TMath.h>
#include <TROOT.h>
#include <cmath>

#include <iostream>

using namespace std;

#include "/eos/cms/store/group/phys_heavyions_ops/pchou/ElectroWeak-Jet-Track-Analyses/CorrelationTuple/EventMatcher.h"

int main(int argc, char *argv[]){

  //TFile::Open("/eos/cms/store/group/phys_heavyions/soohwan/Run3_2023/HLT/Merged/openHLT_MBppref_newCaloParam.root");
  //TTree* HltTree = (TTree*)gFile->Get("hltanalysis/HltTree");

  //string mbpath = "~/eos/HLT_DIGI_CMSSW1321/ppref_MC_MB_1320V32/Macro/CRAB_UserFiles/ppref_MC_MB_1320V32_Macro/230910_112746/0000/*.root";

  string mbpath = "/eos/cms//store/group/phys_heavyions_ops/pchou/HLT_DIGI_CMSSW1321/ppref_MC_MB_1320V32/Macro/CRAB_UserFiles/ppref_MC_MB_1320V32_tag132X2023_Macro/230911_140716/0000/*.root";
  TChain *HltTree = new TChain("hltanalysis/HltTree");
  HltTree   ->Add(mbpath.c_str());

  //TChain *HltTree = new TChain("HltTree");
  //HltTree->Add("~/hlt/HltTree_hydjet.root");

  Long64_t duplicateEntriesHlt = 0;
  Long64_t entriesAnalyzedHlt = 0;

  HltTree->SetBranchStatus("*",0);
  HltTree->SetBranchStatus("Event", 1);
  HltTree->SetBranchStatus("LumiBlock", 1);
  HltTree->SetBranchStatus("Run", 1);

  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton50_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton60_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton40_v", 1);

  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton50_EB_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton60_EB_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton40_EB_v", 1);

  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton10_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton20_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton30_v", 1);

  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton10_EB_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton20_EB_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton30_EB_v", 1);

  HltTree->SetBranchStatus("HLT_PPRefEle10Gsf_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefEle15Gsf_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefEle20Gsf_v", 1);

  HltTree->SetBranchStatus("HLT_PPRefEle30Gsf_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefEle40Gsf_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefEle50Gsf_v", 1);

  HltTree->SetBranchStatus("HLT_PPRefDoubleEle15Gsf_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefEle15Ele10Gsf_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefDoubleEle10Gsf_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefDoubleEle15GsfMass50_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefEle15Ele10GsfMass50_v", 1);
  HltTree->SetBranchStatus("HLT_PPRefDoubleEle10GsfMass50_v", 1);

  HltTree->SetBranchStatus("HLT_AK4PFJet100_v", 1);

  ULong64_t       hlt_event;
  Int_t           hlt_lumi, hlt_run;
  Bool_t HLT_HIGEDPhoton40_EB, HLT_HIGEDPhoton50_EB, HLT_HIGEDPhoton60_EB;
  Bool_t HLT_HIGEDPhoton40, HLT_HIGEDPhoton50, HLT_HIGEDPhoton60;

  Bool_t HLT_HIGEDPhoton10_EB, HLT_HIGEDPhoton20_EB, HLT_HIGEDPhoton30_EB;
  Bool_t HLT_HIGEDPhoton10, HLT_HIGEDPhoton20, HLT_HIGEDPhoton30;

  Bool_t HLT_HIEle10Gsf, HLT_HIEle15Gsf, HLT_HIEle20Gsf;
  Bool_t HLT_HIEle30Gsf, HLT_HIEle40Gsf, HLT_HIEle50Gsf;

  Bool_t HLT_HIDoubleEle15Gsf, HLT_HIEle15Ele10Gsf, HLT_HIDoubleEle10Gsf;
  Bool_t HLT_HIDoubleEle15GsfMass50, HLT_HIEle15Ele10GsfMass50, HLT_HIDoubleEle10GsfMass50;

  Bool_t HLT_AK4PFJet100;

  HltTree->SetBranchAddress("Event", &hlt_event);
  HltTree->SetBranchAddress("LumiBlock", &hlt_lumi);
  HltTree->SetBranchAddress("Run", &hlt_run);

  HltTree->SetBranchAddress("HLT_AK4PFJet100_v", &HLT_AK4PFJet100);

  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton50_v", &HLT_HIGEDPhoton50);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton60_v", &HLT_HIGEDPhoton60);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton40_v", &HLT_HIGEDPhoton40);

  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton10_v", &HLT_HIGEDPhoton10);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton20_v", &HLT_HIGEDPhoton20);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton30_v", &HLT_HIGEDPhoton30);

  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton50_EB_v", &HLT_HIGEDPhoton50_EB);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton60_EB_v", &HLT_HIGEDPhoton60_EB);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton40_EB_v", &HLT_HIGEDPhoton40_EB);

  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton10_EB_v", &HLT_HIGEDPhoton10_EB);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton20_EB_v", &HLT_HIGEDPhoton20_EB);
  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton30_EB_v", &HLT_HIGEDPhoton30_EB);

  HltTree->SetBranchAddress("HLT_PPRefEle10Gsf_v", &HLT_HIEle10Gsf);
  HltTree->SetBranchAddress("HLT_PPRefEle15Gsf_v", &HLT_HIEle15Gsf);
  HltTree->SetBranchAddress("HLT_PPRefEle20Gsf_v", &HLT_HIEle20Gsf);

  HltTree->SetBranchAddress("HLT_PPRefEle30Gsf_v", &HLT_HIEle30Gsf);
  HltTree->SetBranchAddress("HLT_PPRefEle40Gsf_v", &HLT_HIEle40Gsf);
  HltTree->SetBranchAddress("HLT_PPRefEle50Gsf_v", &HLT_HIEle50Gsf);

  HltTree->SetBranchAddress("HLT_PPRefDoubleEle15Gsf_v", &HLT_HIDoubleEle15Gsf);
  HltTree->SetBranchAddress("HLT_PPRefEle15Ele10Gsf_v", &HLT_HIEle15Ele10Gsf);
  HltTree->SetBranchAddress("HLT_PPRefDoubleEle10Gsf_v", &HLT_HIDoubleEle10Gsf);
  HltTree->SetBranchAddress("HLT_PPRefDoubleEle15GsfMass50_v", &HLT_HIDoubleEle15GsfMass50);
  HltTree->SetBranchAddress("HLT_PPRefEle15Ele10GsfMass50_v", &HLT_HIEle15Ele10GsfMass50);
  HltTree->SetBranchAddress("HLT_PPRefDoubleEle10GsfMass50_v", &HLT_HIDoubleEle10GsfMass50);

  EventMatcher* emTrig = 0;
  emTrig = new EventMatcher();


  Long64_t entriesHlt = HltTree->GetEntries();
  std::cout << "entries in HLT = " << entriesHlt << std::endl;

  std::cout << "Loop over the file with HLT emulation output..." << std::endl;

  Long64_t nak4=0;
  Long64_t n40=0, n50=0, n60=0;
  Long64_t n40_dup=0, n50_dup=0, n60_dup=0;

  Long64_t n10p=0, n20p=0, n30p=0;
  Long64_t n10p_dup=0, n20p_dup=0, n30p_dup=0;

  Long64_t n40eb=0, n50eb=0, n60eb=0;
  Long64_t n40eb_dup=0, n50eb_dup=0, n60eb_dup=0;

  Long64_t n10peb=0, n20peb=0, n30peb=0;
  Long64_t n10peb_dup=0, n20peb_dup=0, n30peb_dup=0;

  Long64_t n10=0, n15=0, n20=0;
  Long64_t n10_dup=0, n15_dup=0, n20_dup=0;

  Long64_t n40e=0, n50e=0, n30e=0;
  Long64_t n40e_dup=0, n50e_dup=0, n30e_dup=0;

  Long64_t n1515=0, n1510=0, n1010 = 0;
  Long64_t n1515_dup=0, n1510_dup=0, n1010_dup = 0;

  Long64_t n1515m=0, n1510m=0, n1010m = 0;
  Long64_t n1515m_dup=0, n1510m_dup=0, n1010m_dup = 0;

  for (Long64_t j_entry = 0; j_entry < entriesHlt; ++j_entry){
    if (j_entry % 10000 == 0)  {
        std::cout << "current entry = " <<j_entry<< " out of " <<entriesHlt<< " : " <<std::setprecision(2)<<(double)j_entry/entriesHlt*100<< " %" << std::endl;
    }
    HltTree->GetEntry(j_entry);



    if(HLT_HIGEDPhoton40>0)       n40_dup++;
    if(HLT_HIGEDPhoton50>0)       n50_dup++;
    if(HLT_HIGEDPhoton60>0)       n60_dup++;
      
    if(HLT_HIGEDPhoton10>0)      n10p_dup++;
    if(HLT_HIGEDPhoton20>0)      n20p_dup++;
    if(HLT_HIGEDPhoton30>0)      n30p_dup++;
  
    if(HLT_HIGEDPhoton40_EB>0)  n40eb_dup++;
    if(HLT_HIGEDPhoton50_EB>0)  n50eb_dup++;
    if(HLT_HIGEDPhoton60_EB>0)  n60eb_dup++;

    if(HLT_HIGEDPhoton10_EB>0) n10peb_dup++;
    if(HLT_HIGEDPhoton20_EB>0) n20peb_dup++;
    if(HLT_HIGEDPhoton30_EB>0) n30peb_dup++;

    if(HLT_HIEle10Gsf>0) n10_dup++;
    if(HLT_HIEle15Gsf>0) n15_dup++;
    if(HLT_HIEle20Gsf>0) n20_dup++;

    if(HLT_HIEle30Gsf>0) n30e_dup++;
    if(HLT_HIEle40Gsf>0) n40e_dup++;
    if(HLT_HIEle50Gsf>0) n50e_dup++;

    if(HLT_HIDoubleEle15Gsf>0) n1515_dup++;
    if(HLT_HIEle15Ele10Gsf>0) n1510_dup++;
    if(HLT_HIDoubleEle10Gsf>0) n1010_dup++;

    if(HLT_HIDoubleEle15GsfMass50>0) n1515m_dup++;
    if(HLT_HIEle15Ele10GsfMass50>0) n1510m_dup++;
    if(HLT_HIDoubleEle10GsfMass50>0) n1010m_dup++;


    bool eventAdded = emTrig->addEvent(hlt_run, hlt_lumi, hlt_event, j_entry);
    if(!eventAdded) // this event is duplicate, skip this one.
    {
        duplicateEntriesHlt++;
        continue;
    }
    entriesAnalyzedHlt++;

    if(HLT_AK4PFJet100>0)       nak4++;

    if(HLT_HIGEDPhoton40>0)       n40++;
    if(HLT_HIGEDPhoton50>0)       n50++;
    if(HLT_HIGEDPhoton60>0)       n60++;
      
    if(HLT_HIGEDPhoton10>0)      n10p++;
    if(HLT_HIGEDPhoton20>0)      n20p++;
    if(HLT_HIGEDPhoton30>0)      n30p++;
  
    if(HLT_HIGEDPhoton40_EB>0)  n40eb++;
    if(HLT_HIGEDPhoton50_EB>0)  n50eb++;
    if(HLT_HIGEDPhoton60_EB>0)  n60eb++;

    if(HLT_HIGEDPhoton10_EB>0) n10peb++;
    if(HLT_HIGEDPhoton20_EB>0) n20peb++;
    if(HLT_HIGEDPhoton30_EB>0) n30peb++;

    if(HLT_HIEle10Gsf>0) n10++;
    if(HLT_HIEle15Gsf>0) n15++;
    if(HLT_HIEle20Gsf>0) n20++;

    if(HLT_HIEle30Gsf>0) n30e++;
    if(HLT_HIEle40Gsf>0) n40e++;
    if(HLT_HIEle50Gsf>0) n50e++;

    if(HLT_HIDoubleEle15Gsf>0) n1515++;
    if(HLT_HIEle15Ele10Gsf>0) n1510++;
    if(HLT_HIDoubleEle10Gsf>0) n1010++;

    if(HLT_HIDoubleEle15GsfMass50>0) n1515m++;
    if(HLT_HIEle15Ele10GsfMass50>0) n1510m++;
    if(HLT_HIDoubleEle10GsfMass50>0) n1010m++;

  }

  std::cout << "###" << std::endl;
  std::cout << "Loop HLT ENDED" << std::endl;
  std::cout << "entries HLT          = " << entriesHlt << std::endl;
  std::cout << "duplicateEntries HLT = " << duplicateEntriesHlt << std::endl;
  std::cout << "entriesAnalyzed HLT  = " << entriesAnalyzedHlt << std::endl;
  //std::cout << "nFilesSkipped  = " << nFilesSkipped << std::endl;
  std::cout << "###" <<std::setprecision(5)<< std::endl;
  std::cout << "n40 = "<<n40<<", n50 = "<<n50<<", n60 = "<<n60<<std::endl;
  std::cout << "rate: 40 = "<<(double) 74243.988*n40/entriesAnalyzedHlt<<"kHz, 50 = "<<(double) 74243.988*n50/entriesAnalyzedHlt<<"kHz, 60 = "<<(double) 74243.988*n60/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  40 = "<<(double) 74243.988*sqrt((double) n40/entriesAnalyzedHlt*(1-n40/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 50 = "<<(double) 74243.988*sqrt((double) n50/entriesAnalyzedHlt*(1-n50/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 60 = "<<(double) 74243.988*sqrt((double) n60/entriesAnalyzedHlt*(1-n60/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl;
  //std::cout << "n40_dup = "<<n40_dup<<", n50_dup = "<<n50_dup<<", n60_dup = "<<n60_dup<<std::endl;
  //std::cout << "rate: 40_dup = "<<(double) 74243.988*n40_dup/entriesHlt<<"kHz, 50_dup = "<<(double) 74243.988*n50_dup/entriesHlt<<"kHz, 60_dup = "<<(double) 74243.988*n60_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;

  std::cout << "n10p = "<<n10p<<", n20p = "<<n20p<<", n30p = "<<n30p<<std::endl;
  std::cout << "rate: 10 = "<<(double) 74243.988*n10p/entriesAnalyzedHlt<<"kHz, 20 = "<<(double) 74243.988*n20p/entriesAnalyzedHlt<<"kHz, 30 = "<<(double) 74243.988*n30p/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  10 = "<<(double) 74243.988*sqrt((double) n10p/entriesAnalyzedHlt*(1-n10p/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 20 = "<<(double) 74243.988*sqrt((double) n20p/entriesAnalyzedHlt*(1-n20p/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 30 = "<<(double) 74243.988*sqrt((double) n30p/entriesAnalyzedHlt*(1-n30p/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl;
  //std::cout << "n10p_dup = "<<n10p_dup<<", n20p_dup = "<<n20p_dup<<", n30p_dup = "<<n30p_dup<<std::endl;
  //std::cout << "rate: 10_dup = "<<(double) 74243.988*n10p_dup/entriesHlt<<"kHz, 20_dup = "<<(double) 74243.988*n20p_dup/entriesHlt<<"kHz, 30_dup = "<<(double) 74243.988*n30p_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;

  std::cout << "n40eb = "<<n40eb<<", n50eb = "<<n50eb<<", n60eb = "<<n60eb<<std::endl;
  std::cout << "rate: 40 = "<<(double) 74243.988*n40eb/entriesAnalyzedHlt<<"kHz, 50 = "<<(double) 74243.988*n50eb/entriesAnalyzedHlt<<"kHz, 60 = "<<(double) 74243.988*n60eb/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  40 = "<<(double) 74243.988*sqrt((double) n40eb/entriesAnalyzedHlt*(1-n40eb/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 50 = "<<(double) 74243.988*sqrt((double) n50eb/entriesAnalyzedHlt*(1-n50eb/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 60 = "<<(double) 74243.988*sqrt((double) n60eb/entriesAnalyzedHlt*(1-n60eb/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl;
  //std::cout << "n40eb_dup = "<<n40eb_dup<<", n50eb_dup = "<<n50eb_dup<<", n60eb_dup = "<<n60eb_dup<<std::endl;
  //std::cout << "rate: 40_dup = "<<(double) 74243.988*n40eb_dup/entriesHlt<<"kHz, 50_dup = "<<(double) 74243.988*n50eb_dup/entriesHlt<<"kHz, 60_dup = "<<(double) 74243.988*n60eb_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;

  std::cout << "n10peb = "<<n10peb<<", n20peb = "<<n20peb<<", n30peb = "<<n30peb<<std::endl;
  std::cout << "rate: 10 = "<<(double) 74243.988*n10peb/entriesAnalyzedHlt<<"kHz, 20 = "<<(double) 74243.988*n20peb/entriesAnalyzedHlt<<"kHz, 30 = "<<(double) 74243.988*n30peb/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  10 = "<<(double) 74243.988*sqrt((double) n10peb/entriesAnalyzedHlt*(1-n10peb/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 20 = "<<(double) 74243.988*sqrt((double) n20peb/entriesAnalyzedHlt*(1-n20peb/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 30 = "<<(double) 74243.988*sqrt((double) n30peb/entriesAnalyzedHlt*(1-n30peb/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl;
  //std::cout << "n10peb_dup = "<<n10peb_dup<<", n20peb_dup = "<<n20peb_dup<<", n30peb_dup = "<<n30peb_dup<<std::endl;
  //std::cout << "rate: 10_dup = "<<(double) 74243.988*n10peb_dup/entriesHlt<<"kHz, 20_dup = "<<(double) 74243.988*n20peb_dup/entriesHlt<<"kHz, 30_dup = "<<(double) 74243.988*n30peb_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;
  std::cout << "###" << std::endl;

  std::cout << "n10 = "<<n10<<", n15 = "<<n15<<", n20 = "<<n20<<std::endl;
  std::cout << "rate: 10 = "<<(double) 74243.988*n10/entriesAnalyzedHlt<<"kHz, 15 = "<<(double) 74243.988*n15/entriesAnalyzedHlt<<"kHz, 20 = "<<(double) 74243.988*n20/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  10 = "<<(double) 74243.988*sqrt((double) n10/entriesAnalyzedHlt*(1-n10/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 15 = "<<(double) 74243.988*sqrt((double) n15/entriesAnalyzedHlt*(1-n15/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 20 = "<<(double) 74243.988*sqrt((double) n20/entriesAnalyzedHlt*(1-n20/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl;
  //std::cout << "n10_dup = "<<n10_dup<<", n15_dup = "<<n15_dup<<", n20_dup = "<<n20_dup<<std::endl;
  //std::cout << "rate: 10_dup = "<<(double) 74243.988*n10_dup/entriesHlt<<"kHz, 15_dup = "<<(double) 74243.988*n15_dup/entriesHlt<<"kHz, 20_dup = "<<(double) 74243.988*n20_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;
  std::cout << "###" << std::endl;

  std::cout << "n1515 = "<<n1515<<", n1510 = "<<n1510<<", n1010 = "<<n1010<<std::endl;
  std::cout << "rate: 1515 = "<<(double) 74243.988*n1515/entriesAnalyzedHlt<<"kHz, 1510 = "<<(double) 74243.988*n1510/entriesAnalyzedHlt<<"kHz, 1010 = "<<(double) 74243.988*n1010/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  1515 = "<<(double) 74243.988*sqrt((double) n1515/entriesAnalyzedHlt*(1-n1515/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 1510 = "<<(double) 74243.988*sqrt((double) n1510/entriesAnalyzedHlt*(1-n1510/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 1010 = "<<(double) 74243.988*sqrt((double) n1010/entriesAnalyzedHlt*(1-n1010/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl; 
  //std::cout << "n1515_dup = "<<n1515_dup<<", n1510_dup = "<<n1510_dup<<", n1010_dup = "<<n1010_dup<<std::endl;
  //std::cout << "rate: 1515_dup = "<<(double) 74243.988*n1515_dup/entriesHlt<<"kHz, 1510_dup = "<<(double) 74243.988*n1510_dup/entriesHlt<<"kHz, 1010_dup = "<<(double) 74243.988*n1010_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;

  std::cout << "n1515m = "<<n1515m<<", n1510m = "<<n1510m<<", n1010m = "<<n1010m<<std::endl;
  std::cout << "rate: 1515m = "<<(double) 74243.988*n1515m/entriesAnalyzedHlt<<"kHz, 1510m = "<<(double) 74243.988*n1510m/entriesAnalyzedHlt<<"kHz, 1010m = "<<(double) 74243.988*n1010m/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  1515m = "<<(double) 74243.988*sqrt((double) n1515m/entriesAnalyzedHlt*(1-n1515m/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 1510m = "<<(double) 74243.988*sqrt((double) n1510m/entriesAnalyzedHlt*(1-n1510m/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 1010m = "<<(double) 74243.988*sqrt((double) n1010m/entriesAnalyzedHlt*(1-n1010m/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl; 
  //std::cout << "n1515m_dup = "<<n1515m_dup<<", n1510m_dup = "<<n1510m_dup<<", n1010m_dup = "<<n1010m_dup<<std::endl;
  //std::cout << "rate: 1515m_dup = "<<(double) 74243.988*n1515m_dup/entriesHlt<<"kHz, 1510m_dup = "<<(double) 74243.988*n1510m_dup/entriesHlt<<"kHz, 1010m_dup = "<<(double) 74243.988*n1010m_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;

  std::cout << "n40e = "<<n40e<<", n50e = "<<n50e<<", n30e = "<<n30e<<std::endl;
  std::cout << "rate: 40e = "<<(double) 74243.988*n40e/entriesAnalyzedHlt<<"kHz, 50e = "<<(double) 74243.988*n50e/entriesAnalyzedHlt<<"kHz, 30e = "<<(double) 74243.988*n30e/entriesAnalyzedHlt<<"kHz"<<std::endl;
  std::cout << "err:  40e = "<<(double) 74243.988*sqrt((double) n40e/entriesAnalyzedHlt*(1-n40e/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 50e = "<<(double) 74243.988*sqrt((double) n50e/entriesAnalyzedHlt*(1-n50e/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz, 30e = "<<(double) 74243.988*sqrt((double) n30e/entriesAnalyzedHlt*(1-n30e/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl;
  //std::cout << "n40e_dup = "<<n40e_dup<<", n50e_dup = "<<n50e_dup<<", n30e_dup = "<<n30e_dup<<std::endl;
  //std::cout << "rate: 40e_dup = "<<(double) 74243.988*n40e_dup/entriesHlt<<"kHz, 50e_dup = "<<(double) 74243.988*n50e_dup/entriesHlt<<"kHz, 30e_dup = "<<(double) 74243.988*n30e_dup/entriesHlt<<"kHz"<<std::endl;
  std::cout << "###" << std::endl;

  std::cout << "nak4 = "<<nak4<<", rate ak4 = "<<(double) 74243.988*nak4/entriesAnalyzedHlt<<"kHz"<<", err ak4 = "<<(double) 74243.988*sqrt((double) nak4/entriesAnalyzedHlt*(1-nak4/entriesAnalyzedHlt)/entriesAnalyzedHlt)<<"kHz"<<std::endl;

}