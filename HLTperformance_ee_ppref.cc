#include "/eos/cms/store/group/phys_heavyions_ops/pchou/ElectroWeak-Jet-Track-Analyses/CorrelationTuple/EventMatcher.h"
#include "/eos/cms/store/group/phys_heavyions_ops/pchou/ElectroWeak-Jet-Track-Analyses/TreeHeaders/ggHiNtuplizerTree.h"
#include "/eos/cms/store/group/phys_heavyions_ops/pchou/ElectroWeak-Jet-Track-Analyses/TreeHeaders/hltObjectTree.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"

void HLTperformance_ee_ppref(){

  bool isVerbose = false;

  string typeofdata = "Zee_ppref_1400v60v2_EG10_dr05";
  //string typeofdata = "Zee_ppref_1400v60v2_dr05_345";

  string folder = "20240601";

  int pt_min = 5, pt_max=80, pt_bin=40;
  int ax_min = 5, ax_max=85;

  float dRmax = 0.5;
  float GendRmax = 0.1;

  vector<string> triggers = vector<string>{"HLT_PPRefEle10Gsf_v","HLT_PPRefEle15Gsf_v","HLT_PPRefEle20Gsf_v"};
  vector<string> trigger_names = vector<string>{"HLT PPRef Ele 10 Gsf","HLT PPRef Ele 15 Gsf","HLT PPRef Ele 20 Gsf"}; 
  
  //vector<string> triggers = vector<string>{"HLT_PPRefEle30Gsf_v","HLT_PPRefEle40Gsf_v","HLT_PPRefEle50Gsf_v"};
  //vector<string> trigger_names = vector<string>{"HLT PPRef Ele 30 Gsf","HLT PPRef Ele 40 Gsf","HLT PPRef Ele 50 Gsf"}; 

  //string filebase = "/data/submit/pinchun/HLT2024/";
  string filebase = "/eos/cms/store/group/phys_heavyions_ops/pchou/";

  //string hltfilebase = "";
  string hltfilebase = "HLT2024_1/CMSSW_14_0_0/src/HLTrigger/Configuration/test/workstation/";

  string frtfile = filebase + "Forest/Zee_20240417_miniAOD/240418_050541/";
  //string hltfile = filebase + hltfilebase + "openHLT_ppref_MC_Zee_1400v60v2_20240531.root";
  string hltfile = filebase + hltfilebase + "openHLT_ppref_MC_Zee_1400v60v2_EG10_20240531.root";

  setTDRStyle();
  gStyle->SetLegendBorderSize(0);

  writeExtraText = true;       // if extra text
  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  int iPos=11;
  lumi_sqrtS = "pp ref, #sqrt{s_{NN}} = 5.36 TeV, 2024 Simulation";

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
  
  TChain *Tree10 = new TChain(("hltobject/" + triggers[0] ).c_str());
  TChain *Tree15 = new TChain(("hltobject/" + triggers[1] ).c_str());
  TChain *Tree20 = new TChain(("hltobject/" + triggers[2] ).c_str());

  Tree10->Add(hltfile.c_str());
  Tree15->Add(hltfile.c_str());
  Tree20->Add(hltfile.c_str());
  
  TH1F* hdenom   = new TH1F("hdenom","",pt_bin,pt_min,pt_max);
  TH1F* hnum10   = new TH1F("hnum10","",pt_bin,pt_min,pt_max);
  TH1F* hnum15   = new TH1F("hnum15","",pt_bin,pt_min,pt_max);
  TH1F* hnum20   = new TH1F("hnum20","",pt_bin,pt_min,pt_max);

  EventMatcher* emTrig = 0;
  emTrig = new EventMatcher();

  EventMatcher* em = new EventMatcher();

  Long64_t duplicateEntriesHlt = 0;
  Long64_t entriesAnalyzedHlt = 0;
  //Long64_t nFilesSkipped=0;

  Tree10->SetBranchStatus("*",0);
  Tree15->SetBranchStatus("*",0);
  Tree20->SetBranchStatus("*",0);

  Tree10->SetBranchStatus("eta", 1);
  Tree15->SetBranchStatus("eta", 1);
  Tree20->SetBranchStatus("eta", 1);

  Tree10->SetBranchStatus("phi", 1);
  Tree15->SetBranchStatus("phi", 1);
  Tree20->SetBranchStatus("phi", 1);

  HltTree->SetBranchStatus("*",0);
  HltTree->SetBranchStatus("Event", 1);
  HltTree->SetBranchStatus("LumiBlock", 1);
  HltTree->SetBranchStatus("Run", 1);

  HltTree->SetBranchStatus(triggers[0].c_str(), 1);
  HltTree->SetBranchStatus(triggers[1].c_str(), 1);
  HltTree->SetBranchStatus(triggers[2].c_str(), 1);

  HltTree->SetBranchStatus("HLT_PPRefGEDPhoton30_v", 1);

  HiTree->SetBranchStatus("*",0);
  HiTree->SetBranchStatus("hiBin",1);
  HiTree->SetBranchStatus("hiHF",1);
  HiTree->SetBranchStatus("weight",1);

  ULong64_t       hlt_event;
  Int_t           hlt_lumi, hlt_run, hiBin;
  Float_t         hiHF, pthat_weight;

  Bool_t HLT_HIEle10Gsf, HLT_HIEle15Gsf, HLT_HIEle20Gsf, HLT_HIGEDPhoton30;

  HiTree->SetBranchAddress("hiBin", &hiBin);
  HiTree->SetBranchAddress("hiHF", &hiHF);
  HiTree->SetBranchAddress("weight", &pthat_weight);

  HltTree->SetBranchAddress("Event", &hlt_event);
  HltTree->SetBranchAddress("LumiBlock", &hlt_lumi);
  HltTree->SetBranchAddress("Run", &hlt_run);

  HltTree->SetBranchAddress(triggers[0].c_str(), &HLT_HIEle10Gsf);
  HltTree->SetBranchAddress(triggers[1].c_str(), &HLT_HIEle15Gsf);
  HltTree->SetBranchAddress(triggers[2].c_str(), &HLT_HIEle20Gsf);


  HltTree->SetBranchAddress("HLT_PPRefGEDPhoton30_v", &HLT_HIGEDPhoton30);

  EventTree->SetBranchStatus("*",0);
  EventTree->SetBranchStatus("run",1);
  EventTree->SetBranchStatus("event",1);
  EventTree->SetBranchStatus("lumis",1);

  EventTree->SetBranchStatus("nEle",1);
  EventTree->SetBranchStatus("mcPID",1);

  EventTree->SetBranchStatus("pho_genMatchedIndex",1);//?
  EventTree->SetBranchStatus("mcIndex",1);

  EventTree->SetBranchStatus("elePt",1);
  EventTree->SetBranchStatus("eleEta",1);
  EventTree->SetBranchStatus("eleHoverE",1);
  EventTree->SetBranchStatus("elePhi",1);

  EventTree->SetBranchStatus("eleSigmaIEtaIEta_2012",1);
  EventTree->SetBranchStatus("eledEtaSeedAtVtx",1);
  EventTree->SetBranchStatus("eledPhiAtVtx",1);
  EventTree->SetBranchStatus("eleHoverEBc",1);
  EventTree->SetBranchStatus("eleEoverPInv",1);
  EventTree->SetBranchStatus("eleMissHits",1);
  EventTree->SetBranchStatus("eleIP3D",1);

  EventTree->SetBranchStatus("eleSCEta",1);

  EventTree->SetBranchStatus("mcEta",1);
  EventTree->SetBranchStatus("mcPhi",1);

  EventTree->SetBranchStatus("eleSCRawEn",1);


  Long64_t entriesHlt = HltTree->GetEntries();
  std::cout << "entries in HLT = " << entriesHlt << std::endl;

  std::cout << "Loop over the file with HLT emulation output..." << std::endl;

  for (Long64_t j_entry = 0; j_entry < entriesHlt; ++j_entry){
    if (j_entry % 10000 == 0)  {
        std::cout << "current entry = " <<j_entry<< " out of " <<entriesHlt<< " : " <<std::setprecision(2)<<(double)j_entry/entriesHlt*100<< " %" << std::endl;
    }
    HltTree->GetEntry(j_entry);

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

  hltObject ho10;
  ho10.setupTreeForReading(Tree10);

  hltObject ho15;
  ho15.setupTreeForReading(Tree15);

  hltObject ho20;
  ho20.setupTreeForReading(Tree20);


  Long64_t entriesTmp = EventTree->GetEntries();
  std::cout << "entries in File = " << entriesTmp << std::endl;

  Long64_t entryTrig = 0;
  Int_t entriesNotFoundinTrigger=0;
  Int_t duplicateEntries=0, entriesAnalyzed=0;

  Int_t count0=0, count10=0, count15=0, count20=0, countp30=0;

  cout<<"Electrons with pT>60 but HLT_PPRefEle10Gsf_v not triggered:"<<endl;

  //for (Long64_t j_entry = 80000; j_entry < 90000; ++j_entry){
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
    Tree15->GetEntry(entryTrig);
    Tree20->GetEntry(entryTrig);

    float sumIso, maxPt=0;
    int maxPt_i = -1;

    std::vector<int> ele_genMatchedIndex;
    for(int iele=0;iele<size(*ggHi.elePt);iele++){
      int matchedIndex = -1;
      float minDR = GendRmax;
      for (unsigned igen = 0; igen < size(*ggHi.mcEt); ++igen) {
        if ( abs((*ggHi.mcPID)[igen]) != 11)
          continue;
        float deta = TMath::Abs((*ggHi.eleEta)[iele] - (*ggHi.mcEta)[igen]);
        float dphi = TMath::Abs((*ggHi.elePhi)[iele] - (*ggHi.mcPhi)[igen]);
        if (dphi > TMath::Pi()) 
          dphi = TMath::Abs(dphi - 2*TMath::Pi());
        if (TMath::Sqrt(dphi*dphi + deta*deta) < minDR){ 
          minDR = TMath::Sqrt(dphi*dphi + deta*deta);
          matchedIndex = igen;
        }
      }
      ele_genMatchedIndex.push_back(matchedIndex);
    }

    float dr00;
    for(int i=0; i < ggHi.nEle; ++i) {
      int64_t genID = ele_genMatchedIndex[i];
      if (genID == -1)  continue; 
      auto pid = (*ggHi.mcPID)[genID];
      auto mpid = (*ggHi.mcMomPID)[genID];
      if (std::abs(pid) != 11 || std::abs(mpid) != 23) continue;
      //dr00 = sqrt(((*ggHi.mcEta)[genID]-(*ggHi.eleEta)[i])*((*ggHi.mcEta)[genID]-(*ggHi.eleEta)[i])+((*ggHi.mcPhi)[genID]-(*ggHi.elePhi)[i])*((*ggHi.mcPhi)[genID]-(*ggHi.elePhi)[i]));
      //if(dr00 > dRmax) continue;
      
      if((*ggHi.elePt)[i]>maxPt){
        maxPt = (*ggHi.elePt)[i]; 
        maxPt_i = i;
      }/*
      if((*ggHi.eleSCRawEn)[i]/cosh((*ggHi.eleSCEta)[i])>maxPt){
        maxPt = (*ggHi.eleSCRawEn)[i]/cosh((*ggHi.eleSCEta)[i]); 
        maxPt_i = i;
      }*/ //eleSCRawEn / cosh(eleSCEta)
    }

    if(maxPt_i==-1) continue;
    //cout<<"maxPt_i = "<<maxPt_i<<endl;
    //cout<<"phoEt[maxPt_i] = "<<(*ggHi.phoEt)[maxPt_i]<<endl;

    //cout<<"Electron Selection"<<endl;

    float dr10, dr15, dr20;

    bool sel_cut = kFALSE;

    //VETO
    if(abs((*ggHi.eleEta)[maxPt_i]) < 1.442 && (*ggHi.eleSigmaIEtaIEta_2012)[maxPt_i] < 0.01020 && abs((*ggHi.eledEtaSeedAtVtx)[maxPt_i]) < 0.00327 && abs((*ggHi.eledPhiAtVtx)[maxPt_i]) < 0.06055 && abs((*ggHi.eleEoverPInv)[maxPt_i]) < 0.52688 ) sel_cut = kTRUE;
    else if(abs((*ggHi.eleEta)[maxPt_i]) > 1.57 && abs((*ggHi.eleEta)[maxPt_i]) < 2.1 && (*ggHi.eleSigmaIEtaIEta_2012)[maxPt_i] < 0.02957 && abs((*ggHi.eledEtaSeedAtVtx)[maxPt_i]) < 0.00490 && abs((*ggHi.eledPhiAtVtx)[maxPt_i]) < 0.09622 && abs((*ggHi.eleEoverPInv)[maxPt_i]) < 0.14600 ) sel_cut = kTRUE;
    else sel_cut = kFALSE;
    
    if(sel_cut==kTRUE){

      hdenom->Fill((*ggHi.elePt)[maxPt_i],pthat_weight);count0++;
      //hdenom->Fill((*ggHi.eleSCRawEn)[maxPt_i]/cosh((*ggHi.eleSCEta)[maxPt_i]));count0++;

      float n_ele_ho = 0;
      float dr10temp, dr15temp, dr20temp;

      dr10 = 10000, dr15 = 10000, dr20 = 10000;

      if(HLT_HIEle10Gsf>0){
       n_ele_ho = size(*ho10.eta);
       //cout<<"n_ele_ho 10 ="<<n_ele_ho<<endl;
       for(int i=0;i<n_ele_ho;i++){
        dr10temp = sqrt(((*ho10.eta)[i]-(*ggHi.eleEta)[maxPt_i])*((*ho10.eta)[i]-(*ggHi.eleEta)[maxPt_i])+((*ho10.phi)[i]-(*ggHi.elePhi)[maxPt_i])*((*ho10.phi)[i]-(*ggHi.elePhi)[maxPt_i]));
        if (dr10temp < dr10) dr10=dr10temp;
       }
      }
      if(HLT_HIEle15Gsf>0){
        n_ele_ho = size(*ho15.eta);
        //cout<<"n_ele_ho 15 ="<<n_ele_ho<<endl;
        for(int i=0;i<n_ele_ho;i++){
        dr15temp = sqrt(((*ho15.eta)[i]-(*ggHi.eleEta)[maxPt_i])*((*ho15.eta)[i]-(*ggHi.eleEta)[maxPt_i])+((*ho15.phi)[i]-(*ggHi.elePhi)[maxPt_i])*((*ho15.phi)[i]-(*ggHi.elePhi)[maxPt_i]));
        if (dr15temp < dr15) dr15=dr15temp;
       }
      }
      if(HLT_HIEle20Gsf>0){
        n_ele_ho = size(*ho20.eta);
        //cout<<"n_ele_ho 20 ="<<n_ele_ho<<endl;
        for(int i=0;i<n_ele_ho;i++){
        dr20temp = sqrt(((*ho20.eta)[i]-(*ggHi.eleEta)[maxPt_i])*((*ho20.eta)[i]-(*ggHi.eleEta)[maxPt_i])+((*ho20.phi)[i]-(*ggHi.elePhi)[maxPt_i])*((*ho20.phi)[i]-(*ggHi.elePhi)[maxPt_i]));
        //cout<<"dr20temp ="<<dr20temp<<endl;
        if (dr20temp < dr20) dr20=dr20temp;
        //cout<<"dr20 ="<<dr20<<endl;
       }
      }
      
      if(HLT_HIGEDPhoton30>0) countp30++;
      if(HLT_HIEle10Gsf>0 && dr10 < dRmax){hnum10->Fill((*ggHi.elePt)[maxPt_i],pthat_weight); count10++;}
      if(HLT_HIEle15Gsf>0 && dr15 < dRmax){hnum15->Fill((*ggHi.elePt)[maxPt_i],pthat_weight); count15++;}
      if(HLT_HIEle20Gsf>0 && dr20 < dRmax){hnum20->Fill((*ggHi.elePt)[maxPt_i],pthat_weight); count20++;}

      //if(HLT_HIEle10Gsf>0 && dr10 < dRmax){hnum10->Fill((*ggHi.eleSCRawEn)[maxPt_i]/cosh((*ggHi.eleSCEta)[maxPt_i])); count10++;}
      //if(HLT_HIEle15Gsf>0 && dr15 < dRmax){hnum15->Fill((*ggHi.eleSCRawEn)[maxPt_i]/cosh((*ggHi.eleSCEta)[maxPt_i])); count15++;}
      //if(HLT_HIEle20Gsf>0 && dr20 < dRmax){hnum20->Fill((*ggHi.eleSCRawEn)[maxPt_i]/cosh((*ggHi.eleSCEta)[maxPt_i])); count20++;}
    }
  }

  std::cout << "count0 = "<<count0<<", count10 = "<<count10<<", count15 = "<<count15<<", count20 = "<<count20 << std::endl;
  std::cout << "count photon 30 = "<<countp30<<std::endl;

  std::cout << "###" << std::endl;
  std::cout << "Loop Forest ENDED"  << std::endl;
  std::cout << "entries Forest          = " << entriesTmp << std::endl;
  std::cout << "duplicateEntries Forest = " << duplicateEntries << std::endl;
  std::cout << "entriesAnalyzed Forest  = " << entriesAnalyzed << std::endl;
  std::cout << "entriesNotFoundinTrigger  = " << entriesNotFoundinTrigger << std::endl;
  std::cout << "###" << std::endl;

  TCanvas *canvas1 = new TCanvas("canvas1","Comparison of two histograms",1200,800);
  canvas1->SetMargin(0.15, 0.05, 0.15, 0.08);
  canvas1->GetFrame()->SetBorderSize(12);

  TGraphAsymmErrors* hratio[3];

  hratio[0] = new TGraphAsymmErrors();
  hratio[1] = new TGraphAsymmErrors();
  hratio[2] = new TGraphAsymmErrors();

  hratio[0] ->SetName("hratio10");
  hratio[1] ->SetName("hratio15");
  hratio[2] ->SetName("hratio20");

  hratio[0]->BayesDivide(hnum10, hdenom);
  hratio[1]->BayesDivide(hnum15, hdenom);
  hratio[2]->BayesDivide(hnum20, hdenom);

  hratio[0]->GetXaxis()->SetTitle("p^{e}_{T} [GeV/c]");
  //hratio[0]->GetXaxis()->SetTitle("p^{e}_{SC} (Raw) [GeV/c]");
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

  float endcap_legendpp = 0;//0.3

  //HLT_PPRefEle10Gsf_v

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

  CMS_lumi( canvas1, iPeriod, iPos );
  gSystem->Exec(("mkdir -p figs/" + folder ).c_str());
  canvas1->SaveAs(("figs/" + folder + "/HLTEff_" + typeofdata + ".png").c_str()); //_cent10 _EB _onlyL1
}