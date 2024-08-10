#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TMath.h>
#include <TROOT.h>
#include <cmath>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TSystem.h>
#include <TLatex.h>
#include <TLine.h>
#include <TH1F.h>
#include <TGraphAsymmErrors.h>
#include <TFrame.h>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

#include "include/EventMatcher.h"
#include "include/ggHiNtuplizerTree.h"
#include "include/hltObjectTree.h"
#include "include/tdrstyle.C"
#include "include/CMS_lumi.C"
#include "include/CommandLine.h"

void DrawTurnOn(bool isEB, bool is456, CommandLine CL);

int main(int argc, char *argv[]){

  CommandLine CL(argc, argv);

  DrawTurnOn(true, true, CL);
  DrawTurnOn(true, false, CL);
  DrawTurnOn(false, true, CL);
  DrawTurnOn(false, false, CL);
}

void DrawTurnOn(bool isEB, bool is456, CommandLine CL){

  std::cout<<"isEB = "<<isEB<<", is456 = "<<is456<<std::endl;

  string typeofdata  = CL.Get("typeofdata", "QCDPhoton_ppref");
  string folder      = CL.Get("folder"    , "/eos/user/p/pchou/figs/hlt/");
  string frtfile     = CL.Get("forestfile", "Forest/");
  string hltfile     = CL.Get("hltfile"   , "HLT/*.root");
  string uptext      = CL.Get("uptext"    , "pp ref, #sqrt{s_{NN}} = 5.36 TeV, 2024 Simulation");

  int pt_min         = CL.GetInt("pt_min", 10);
  int pt_max         = CL.GetInt("pt_max", 90);
  int pt_bin         = CL.GetInt("pt_bin", 28);
  int ax_min         = CL.GetInt("ax_min", 10);
  int ax_max         = CL.GetInt("ax_max", 105);

  double dRmax       = CL.GetDouble("dRmax", 0.5);
  double GendRmax    = CL.GetDouble("GendRmax", 0.1);

  bool isVerbose     =  CL.GetBool("isVerbose", false);

  if(!is456)
    typeofdata += "_123"; 

  string EBtxt = "";

  if(isEB){
    EBtxt = "_EB";
    folder += "/EB/";
  }

  string null_trigger = "HLT_PPRefGEDPhoton10" + EBtxt + "_v";

  vector<string> triggers, trigger_names;

  if(is456){
    triggers = vector<string>{"HLT_PPRefGEDPhoton40" + EBtxt + "_v","HLT_PPRefGEDPhoton50" + EBtxt + "_v","HLT_PPRefGEDPhoton60" + EBtxt + "_v"};
    trigger_names = vector<string>{"HI GED Photon" + EBtxt + " 40","HI GED Photon" + EBtxt + " 50","HI GED Photon" + EBtxt + " 60"}; 
  }else{
    triggers = vector<string>{"HLT_PPRefGEDPhoton10" + EBtxt + "_v","HLT_PPRefGEDPhoton20" + EBtxt + "_v","HLT_PPRefGEDPhoton30" + EBtxt + "_v"};
    trigger_names = vector<string>{"HI GED Photon" + EBtxt + " 10","HI GED Photon" + EBtxt + " 20","HI GED Photon" + EBtxt + " 30"}; 

  }

  setTDRStyle();
  gStyle->SetLegendBorderSize(0);

  writeExtraText = true;       // if extra text
  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  int iPos=11;
  lumi_sqrtS = uptext;

  std::cout << "Reading files..." << std::endl;

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

  Bool_t HLT_HIGEDPhoton40, HLT_HIGEDPhoton50, HLT_HIGEDPhoton60, HLT_HIGEDPhoton10;

  HiTree->SetBranchAddress("hiBin", &hiBin);
  HiTree->SetBranchAddress("hiHF", &hiHF);
  HiTree->SetBranchAddress("weight", &pthat_weight);

  HltTree->SetBranchAddress("Event", &hlt_event);
  HltTree->SetBranchAddress("LumiBlock", &hlt_lumi);
  HltTree->SetBranchAddress("Run", &hlt_run);

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

    emTrig->removeEvent(ggHi.run, ggHi.lumis, ggHi.event);
    entriesAnalyzed++;

    //cout<<"entryTrig = "<<entryTrig<<endl;
    HltTree->GetEntry(entryTrig);
    Tree10->GetEntry(entryTrig);
    Tree40->GetEntry(entryTrig);
    Tree50->GetEntry(entryTrig);
    Tree60->GetEntry(entryTrig);
    
    float sumIso, maxPt=0;
    int maxPt_i = -1;

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

    if(sel_cut==kTRUE){
        
      hdenom->Fill((*ggHi.phoEt)[maxPt_i],pthat_weight);count0++;

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

  hratio[1]->SetMarkerStyle(kFullTriangleUp);
  hratio[1]->SetMarkerColor(kBlue);
  hratio[1]->SetMarkerSize(2);
  hratio[1]->SetLineColor(kBlue);

  hratio[2]->SetMarkerStyle(kFullSquare);
  hratio[2]->SetMarkerColor(kRed);
  hratio[2]->SetMarkerSize(2);
  hratio[2]->SetLineColor(kRed);

  hratio[0]->SetMinimum(0);
  hratio[0]->SetMaximum(1.2);

  hratio[0]->GetXaxis()->SetLimits(ax_min,ax_max);

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

  CMS_lumi( canvas1, iPeriod, iPos );
  gSystem->Exec(("mkdir -p " + folder ).c_str());
  canvas1->SaveAs((folder + "/HLTEff_" + typeofdata + EBtxt + ".png").c_str()); //_cent10 _EB _onlyL1

  delete hdenom;
  delete hnum40;
  delete hnum50;
  delete hnum60;
  delete hratio[0];
  delete hratio[1];
  delete hratio[2];
  delete canvas1;
}