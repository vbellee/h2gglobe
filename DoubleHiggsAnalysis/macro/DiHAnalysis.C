//Read histograms_diH_studiesBtagging and draw a histogram

#include "TNtuple.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <algorithm>
#include "TString.h"


void DiHAnalysis(){
  
  //Open a file, save the ntuple and close the file
  TFile *in_file = TFile::Open("histograms_diH_studiesBtagging6.root");
  
 
  TTree* my_tuple = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/gghh_m125_8TeV",
  						      "TTree");
 
  TTree* my_tupleZH = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/zh_m125_8TeV",
  						      "TTree");
 
  TTree* my_tupleWH = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/wh_m125_8TeV",
  						      "TTree");

  TTree* my_tupleGGH = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/ggh_m125_8TeV",
  						      "TTree");

  TTree* my_tupleVBF = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/vbf_m125_8TeV",
  						      "TTree");

  TTree* my_tupleTTH = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/tth_m125_8TeV",
  						      "TTree");

  //Prints only the number of entries
  gStyle->SetOptStat("");

  //Fix the csv Cut (0.244, 0.679, 0.898)
  float csvCut ;
  csvCut = 0.0;

  //Smallest Cut
  float csvCut1 ;
  csvCut1 = 0.0;
  //Biggest Cut
  float csvCut2 ;
  csvCut2 = 0.0;

  char Conditions = "(nJets)<=3";

  //Create the Histograms
  //Have to set the appropriate boundaries
  TH1F* hsignificance=new TH1F("significance","Significance;S/sqrt(B);",
			 5,//Number of bins
			 110,//Lower X Boundary
			 130);//Upper X Boundary
  hsignificance->SetFillColor(kBlue-6);  

  TH1F* hdiphopt=new TH1F("diphopt","Di-photon Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 700);//Upper X Boundary
  hdiphopt->SetLineColor(kBlue-6);

  TH1F* hpho1pt=new TH1F("pho1pt","Photon 1 Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hpho1pt->SetLineColor(kBlue-6);

  TH1F* hpho2pt=new TH1F("pho2pt","Photon 2 Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hpho2pt->SetLineColor(kBlue-6);

  TH1F* hdiphoZHpt=new TH1F("diphopt","Di-photon Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 700);//Upper X Boundary
  hdiphoZHpt->SetLineColor(kRed-6);

  TH1F* hpho1ZHpt=new TH1F("pho1pt","Photon 1 Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hpho1pt->SetLineColor(kRed-6);

  TH1F* hpho2ZHpt=new TH1F("pho2pt","Photon 2 Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hpho2pt->SetLineColor(kRed-6);

  TH1F* hdijetpt=new TH1F("dijetpt","Di-jet Momentum;Pt;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hdijetpt->SetLineColor(kGreen-6);


  TH1F* hdijetZHpt=new TH1F("dijetpt","Di-jet Momentum;Pt;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hdijetZHpt->SetLineColor(kGreen);

  TH1F* hdijetptBtag=new TH1F("dijetptBtag","Di-jet Momentum after Btagging;Pt;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hdijetptBtag->SetFillColor(kGreen-6);

  TH1F* hdivisionbis1=new TH1F("hdivisionbis1","Jet1Btag/All;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hdivisionbis1->SetFillColor(kGreen-6);

  TH1F* hdivisionbis2=new TH1F("hdivisionbis2","Jet2Btag/All;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hdivisionbis2->SetFillColor(kGreen-6);

  TH1F* hjetPt=new TH1F("jetPt","Jet Momentum;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 160);//Upper X Boundary
  hjetPt->SetLineColor(kGreen-6);
  hjetPt->Sumw2();

  TH1F* hjetPtBtag=new TH1F("jetPtBtag","Jet Momentum after B-tagging;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 160);//Upper X Boundary
  hjetPtBtag->SetFillColor(kGreen-6);
  hjetPtBtag->Sumw2();

  TH1F* hdivisionbis=new TH1F("hdivisionbis","Efficiency of the b-cut;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 160);//Upper X Boundary
  hdivisionbis->SetFillColor(kGreen-6);
  hdivisionbis->Sumw2();

  TH1F* hjetZHPt=new TH1F("jetPt","Jet Momentum;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjetZHPt->SetLineColor(kGreen);  

  TH1F* hjet1PtBtag=new TH1F("jet1PtBtag","Jet1 Momentum after B-tagging;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet1PtBtag->SetFillColor(kGreen-6);  

  TH1F* hjet2PtBtag=new TH1F("jet2PtBtag","Jet2 Momentum after B-tagging;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet2PtBtag->SetFillColor(kGreen-6);

  TH1F* hjet1Pt=new TH1F("jet1Pt","Jet 1 Momentum;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet1Pt->SetLineColor(kGreen-6);

  TH1F* hjet2Pt=new TH1F("jet2Pt","Jet 2 Momentum;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet2Pt->SetLineColor(kGreen-6);

  TH1F* hjet1recoPt=new TH1F("jet1recoPt","Jet 1 Reconstructed Momentum (with trick);Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet1recoPt->SetLineColor(kRed-6);

  TH1F* hjet2recoPt=new TH1F("jet2recoPt","Jet 2 Reconstructed Momentum (with trick);Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet2recoPt->SetLineColor(kRed-6);

  TH1F* hjet1recoPtBtag=new TH1F("jet1recoPtBtag","Jet 1 Reconstructed Momentum (with trick after Btagging);Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet1recoPtBtag->SetLineColor(kRed-6);

  TH1F* hjet2recoPtBtag=new TH1F("jet2recoPtBtag","Jet 2 Reconstructed Momentum (with trick after Btagging);Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet2recoPtBtag->SetLineColor(kRed-6);

  TH1F* hjet1ZHPt=new TH1F("ZHjet1Pt","Jet 1 Momentum ZH;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet1ZHPt->SetLineColor(kGreen);

  TH1F* hjet2ZHPt=new TH1F("ZHjet2Pt","Jet 2 Momentum ZH;Pt;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet2ZHPt->SetLineColor(kGreen);

  //Histo for the reco-gen Pt for jet 1

  TH1F* hjet1recogenPt=new TH1F("jet1genPt","Reconstructed - Generated Jet 1 Momentum;Pt;",
			 100,//Number of bins
			 -100,//Lower X Boundary
			 100);//Upper X Boundary
  hjet1recogenPt->SetFillColor(kGreen-6);

  //Histo for the reco-gen Pt for jet 2

  TH1F* hjet2recogenPt=new TH1F("jet2Pt","Reconstructed - Generated Jet 2 Momentum;Pt;",
			 100,//Number of bins
			 -100,//Lower X Boundary
			 100);//Upper X Boundary
  hjet2recogenPt->SetFillColor(kGreen-6);

  TH1F* hdiphoEta=new TH1F("diphoEta","Di-photon Eta;Eta;",
			 100,//Number of bins
			 -6,//Lower X Boundary
			 6);//Upper X Boundary
  hdiphoEta->SetFillColor(kBlue-6);

  TH1F* hpho1Eta=new TH1F("pho1Eta","Photon 1 Eta;Eta;",
			 100,//Number of bins
			 -6,//Lower X Boundary
			 6);//Upper X Boundary
  hpho1Eta->SetFillColor(kBlue-6);

  TH1F* hpho2Eta=new TH1F("pho2Eta","Photon 2 Eta;Eta;",
			 100,//Number of bins
			 -6,//Lower X Boundary
			 6);//Upper X Boundary
  hpho2Eta->SetFillColor(kBlue-6);

  TH1F* hdijetEta=new TH1F("dijetEta","Di-jet Eta; Eta ;",
			100,
			-3,
			3);//Upper X Boundary
  hdijetEta->SetFillColor(kGreen-6);

  TH1F* hjet1Eta=new TH1F("jet1Eta","Jet1 Eta; Eta ;",
			100,
			-3,
			3);//Upper X Boundary
  hjet1Eta->SetFillColor(kGreen-6);

  TH1F* hjet2Eta=new TH1F("jet2Eta","Jet2 Eta; Eta ;",
			100,
			-3,
			3);//Upper X Boundary
  hjet2Eta->SetFillColor(kGreen-6); 

  TH1F* hdiphoM=new TH1F("diphoM","Di-photon Mass;Mass;",
			 100,//Number of bins
			 100,//Lower X Boundary
			 150);//Upper X Boundary
  hdiphoM->SetFillColor(kBlue-6);

  TH1F* hbkg=new TH1F("Bkg","Di-jet Mass Bkg;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hbkg->SetFillColor(kYellow);

  TH1F* hmj1j2=new TH1F("mj1mj2GGHH","Di-jet MassGGHH;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2->SetLineColor(kGreen-6);

  TH1F* hdiphoMHH=new TH1F("diphoMHH","Di-photon Mass HH;Mass;",
			 100,//Number of bins
			 100,//Lower X Boundary
			 150);//Upper X Boundary
  hdiphoMHH->SetFillColor(kViolet);

  TH1F* hdiphoMZH=new TH1F("diphoMZH","Di-photon Mass ZH;Mass;",
			 100,//Number of bins
			 100,//Lower X Boundary
			 150);//Upper X Boundary
  hdiphoMZH->SetFillColor(kGreen);

  TH1F* hdiphoMWH=new TH1F("diphoMWH","Di-photon Mass WH;Mass;",
			 100,//Number of bins
			 100,//Lower X Boundary
			 150);//Upper X Boundary
  hdiphoMWH->SetFillColor(kRed);

  TH1F* hdiphoMGGH=new TH1F("diphoMGGH","Di-photon Mass GGH;Mass;",
			 100,//Number of bins
			 100,//Lower X Boundary
			 150);//Upper X Boundary
  hdiphoMGGH->SetFillColor(kBlue-6);

  TH1F* hdiphoMGGHCuts=new TH1F("diphoMGGHCuts","Di-photon Mass GGH;Mass;",
			 100,//Number of bins
			 100,//Lower X Boundary
			 150);//Upper X Boundary
  hdiphoMGGHCuts->SetFillColor(kBlue-6);

  TH1F* hdiphoMTTH=new TH1F("diphoMTTH","Di-photon Mass TTH;Mass;",
			 100,//Number of bins
			 100,//Lower X Boundary
			 150);//Upper X Boundary
  hdiphoMTTH->SetFillColor(kOrange);

  TH1F* hmj1j2reco=new TH1F("mj1mj2GGHH","Di-jet Reconstructed MassGGHH;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2reco->SetFillColor(kViolet);

  TH1F* hmj1j2ZH=new TH1F("mj1mj2ZH","Di-jetZH Mass;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2ZH->SetFillColor(kGreen);

  TH1F* hmj1j2ZHBMatched=new TH1F("mj1mj2ZHBMatched","Di-jetZH BMatched Mass;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2ZHBMatched->SetFillColor(kGreen+3);

  TH1F* hmj1j2WH=new TH1F("mj1mj2WH","Di-jetWH Mass;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2WH->SetFillColor(kRed);

  TH1F* hmj1j2GGH=new TH1F("mj1mj2GGH","Di-jet MassGGH;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2GGH->SetFillColor(kBlue-6);

  TH1F* hmj1j2GGHCuts=new TH1F("mj1mj2GGHCuts","Di-jet MassGGH;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2GGHCuts->SetFillColor(kBlue-6);

  TH1F* hmj1j2VBF=new TH1F("mj1mj2VBF","Di-jet MassVBF;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2VBF->SetFillColor(kBlue);


  TH1F* hmj1j2TTH=new TH1F("mj1mj2TTH","Di-jet MassTTH;Mass;",
			 60,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2TTH->SetFillColor(kOrange);

  TH1F* hjet3=new TH1F("jet3","Jet3;;",
			 11,//Number of bins
			 -1,//Lower X Boundary
			 11);//Upper X Boundary
  hjet3->SetFillColor(kCyan-6);

  TH1F* hcsvBtag1=new TH1F("csvBtag1","csvBtag1;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 1);//Upper X Boundary
  hcsvBtag1->SetFillColor(kCyan-6);

  TH1F* hcsvBtag2=new TH1F("csvBtag2","csvBtag2;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 1);//Upper X Boundary
  hcsvBtag2->SetFillColor(kCyan-6);

  TH1F* hcsvBtag3=new TH1F("csvBtag3","csvBtag3;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 1);//Upper X Boundary
  hcsvBtag3->SetFillColor(kCyan-6);

  TH1F* hcsvMvaBtag1=new TH1F("csvMvaBtag1","csvMvaBtag1;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 1);//Upper X Boundary
  hcsvMvaBtag1->SetFillColor(kCyan-6);

  TH1F* hcsvMvaBtag2=new TH1F("csvMvaBtag2","csvMvaBtag2;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 1);//Upper X Boundary
  hcsvMvaBtag2->SetFillColor(kCyan-6);

  TH1F* hcsvMvaBtag3=new TH1F("csvMvaBtag3","csvMvaBtag3;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 1);//Upper X Boundary
  hcsvMvaBtag3->SetFillColor(kCyan-6);

  TH1F* hjetProbBtag1=new TH1F("jetProbBtag1","jetProbBtag1;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 2);//Upper X Boundary
  hjetProbBtag1->SetFillColor(kCyan-6);

  TH1F* hjetProbBtag2=new TH1F("jetProbBtag2","jetProbBtag2;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 2);//Upper X Boundary
  hjetProbBtag2->SetFillColor(kCyan-6);

  TH1F* hjetProbBtag3=new TH1F("jetProbBtag3","jetProbBtag3;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 2);//Upper X Boundary
  hjetProbBtag3->SetFillColor(kCyan-6);

  TH1F* htcheBtag1=new TH1F("tcheBtag1","tcheBtag1;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 50);//Upper X Boundary
  htcheBtag1->SetFillColor(kCyan-6);

  TH1F* htcheBtag2=new TH1F("tcheBtag2","tcheBtag2;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 50);//Upper X Boundary
  htcheBtag2->SetFillColor(kCyan-6);

  TH1F* htcheBtag3=new TH1F("tcheBtag3","tcheBtag3;;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 50);//Upper X Boundary
  htcheBtag3->SetFillColor(kCyan-6);

  TH1F* hjet1isBMatched=new TH1F("jet1isBMatched","Matched Jet1;Match;",
			 3,//Number of bins
			 0,//Lower X Boundary
			 1.2);//Upper X Boundary
  hjet1isBMatched->SetFillColor(kOrange-6);

  TH1F* hjet2isBMatched=new TH1F("jet2isBMatched","Matched Jet2;Match;",
			 3,//Number of bins
			 0,//Lower X Boundary
			 1.2);//Upper X Boundary
  hjet2isBMatched->SetFillColor(kOrange-6);
  /*
  TH1F* hjet1isMatched=new TH1F("jet1isMatched","Matched Jet1;Match;",
			 3,//Number of bins
			 0,//Lower X Boundary
			 1.2);//Upper X Boundary
  hjet1isMatched->SetFillColor(kOrange-6);

  TH1F* hjet2isMatched=new TH1F("jet2isMatched","Matched Jet2;Match;",
			 3,//Number of bins
			 0,//Lower X Boundary
			 1.2);//Upper X Boundary
  hjet2isMatched->SetFillColor(kOrange-6);
  */

  TH1F* hDeltaRHH=new TH1F("DeltaRHH","Delta R;Delta R;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 3);//Upper X Boundary
  hDeltaRHH->SetLineColor(kGreen-6);

  TH1F* hDeltaRZH=new TH1F("DeltaRZH","DeltaR;DeltaR;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 3);//Upper X Boundary
  hDeltaRZH->SetLineColor(kGreen);

  TH1F* hDeltaRWH=new TH1F("DeltaRWH","DeltaR;DeltaR;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 3);//Upper X Boundary
  hDeltaRWH->SetLineColor(kRed);

  TH1F* hDeltaRGGH=new TH1F("DeltaRGGH","DeltaR;DeltaR;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 3);//Upper X Boundary
  hDeltaRGGH->SetLineColor(kBlue-6);

  TH1F* hDeltaRVBF=new TH1F("DeltaRVBF","DeltaR;DeltaR;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 3);//Upper X Boundary
  hDeltaRVBF->SetLineColor(kBlue);

  TH1F* hDeltaRTTH=new TH1F("DeltaRTTH","DeltaR;DeltaR;",
			 11,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hDeltaRTTH->SetLineColor(kOrange);

 TH1F* hnJetsHH=new TH1F("nJetsHH","nJets HH;nJets;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary 
  hnJetsHH->SetLineColor(kViolet); 

  TH1F* hnJetsZH=new TH1F("nJetsZH","nJets ZH;nJets;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hnJetsZH->SetLineColor(kGreen); 

  TH1F* hnJetsWH=new TH1F("nJetsWH","nJets WH;nJets;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hnJetsWH->SetLineColor(kRed);

  TH1F* hnJetsGGH=new TH1F("nJetsGGH","nJets GGH;nJets;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hnJetsGGH->SetLineColor(kBlue-6);


  TH1F* hnJetsTTH=new TH1F("nJetsTTH","nJets TTH;nJets;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hnJetsTTH->SetLineColor(kOrange);

  TH1F* hjet1PtRankHH=new TH1F("Jet1PtRankHH","Jet 1 Pt Rank HH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet1PtRankHH->SetFillColor(kViolet);

  TH1F* hjet2PtRankHH=new TH1F("Jet2PtRankHH","Jet 2 Pt Rank HH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet2PtRankHH->SetFillColor(kViolet);

  TH1F* hjet3PtRankHH=new TH1F("Jet3PtRankHH","Jet 3 Pt Rank HH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet3PtRankHH->SetFillColor(kViolet);

  TH1F* hjet4PtRankHH=new TH1F("Jet4PtRankHH","Jet 4 Pt Rank HH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet4PtRankHH->SetFillColor(kViolet);

  TH1F* hjet1csvRankHH=new TH1F("Jet1csvRankHH","Jet 1 csv Rank HH;Csv Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet1csvRankHH->SetFillColor(kViolet);

  TH1F* hjet2csvRankHH=new TH1F("Jet2csvRankHH","Jet 2 csv Rank HH;Csv Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet2csvRankHH->SetFillColor(kViolet);

  TH1F* hjet3csvRankHH=new TH1F("Jet3csvRankHH","Jet 3 csv Rank HH;Csv Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet3csvRankHH->SetFillColor(kViolet);

  TH1F* hjet4csvRankHH=new TH1F("Jet4csvRankHH","Jet 4 csv Rank HH;Csv Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet4csvRankHH->SetFillColor(kViolet);


  TH1F* hjet1PtRankZH=new TH1F("Jet1PtRankZH","Jet 1 Pt Rank ZH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet1PtRankZH->SetLineColor(kGreen);

  TH1F* hjet2PtRankZH=new TH1F("Jet2PtRankZH","Jet 2 Pt Rank ZH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet2PtRankZH->SetLineColor(kGreen);

  TH1F* hjet3PtRankZH=new TH1F("Jet3PtRankZH","Jet 3 Pt Rank ZH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet3PtRankZH->SetLineColor(kGreen);

  TH1F* hjet4PtRankZH=new TH1F("Jet4PtRankZH","Jet 4 Pt Rank ZH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet4PtRankZH->SetLineColor(kGreen);

  TH1F* hjet1PtRankWH=new TH1F("Jet1PtRankWH","Jet 1 Pt Rank WH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet1PtRankWH->SetLineColor(kRed);

  TH1F* hjet2PtRankWH=new TH1F("Jet2PtRankWH","Jet 2 Pt Rank WH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet2PtRankWH->SetLineColor(kRed);

  TH1F* hjet3PtRankWH=new TH1F("Jet3PtRankWH","Jet 3 Pt Rank WH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet3PtRankWH->SetLineColor(kRed);

  TH1F* hjet4PtRankWH=new TH1F("Jet4PtRankWH","Jet 4 Pt Rank WH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet4PtRankWH->SetLineColor(kRed);

  TH1F* hjet1PtRankGGH=new TH1F("Jet1PtRankGGH","Jet 1 Pt Rank GGH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet1PtRankGGH->SetLineColor(kBlue-6);

  TH1F* hjet2PtRankGGH=new TH1F("Jet2PtRankGGH","Jet 2 Pt Rank GGH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet2PtRankGGH->SetLineColor(kBlue-6);

  TH1F* hjet3PtRankGGH=new TH1F("Jet3PtRankGGH","Jet 3 Pt Rank GGH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet3PtRankGGH->SetLineColor(kBlue-6);

  TH1F* hjet4PtRankGGH=new TH1F("Jet4PtRankGGH","Jet 4 Pt Rank GGH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet4PtRankGGH->SetLineColor(kBlue-6);

  TH1F* hjet1PtRankTTH=new TH1F("Jet1PtRankTTH","Jet 1 Pt Rank TTH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet1PtRankTTH->SetLineColor(kOrange);

  TH1F* hjet2PtRankTTH=new TH1F("Jet2PtRankTTH","Jet 2 Pt Rank TTH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet2PtRankTTH->SetLineColor(kOrange);

  TH1F* hjet3PtRankTTH=new TH1F("Jet3PtRankTTH","Jet 3 Pt Rank TTH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet3PtRankTTH->SetLineColor(kOrange);

  TH1F* hjet4PtRankTTH=new TH1F("Jet4PtRankTTH","Jet 4 Pt Rank TTH;Pt Rank;",
			 10,//Number of bins
			 0,//Lower X Boundary
			 10);//Upper X Boundary
  hjet4PtRankTTH->SetLineColor(kOrange);

  //Create the fit functions to be modified with the Breit Wigner function
  //gdiphoM = new TF1("gdiphoM","2*sqrt(2)*[0]*[1]*sqrt([0]*[0]*([0]*[0]+[1]*[1]))/(3.1415*sqrt([0]*[0]+sqrt([0]*[0]*([0]*[0]+[1]*[1]))))/((x*x-[0]*[0])*(x*x-[0]*[0])+[0]*[0]*[1]*[1])",90,160);
  //gdiphoM->SetParameters(125,11.7);
  //gmj1j2 = new TF1("gmj1j2","2*sqrt(2)*[0]*[1]*sqrt([0]*[0]*([0]*[0]+[1]*[1]))/(3.1415*sqrt([0]*[0]+sqrt([0]*[0]*([0]*[0]+[1]*[1]))))/((x*x-[0]*[0])*(x*x-[0]*[0])+[0]*[0]*[1]*[1])",50,110);
  gdiphoM = new TF1("gdiphoM","gaus",120,130);
  gmj1j2 = new TF1("gmj1j2","gaus",100,140);
  gjet1recogenPt = new TF1 ("gjet1recogenPt","gaus",-20,20);
  gjet2recogenPt = new TF1 ("gjet2recogenPt","gaus",-20,20);
 
  TLorentzVector * jet1p4,* jet2p4,* jet3p4;

  float pho1pt, pho2pt, pho1Eta, pho2Eta, pho1Phi, pho2Phi, diphoM, diphoEta, diphopt,jet1Eta,jet2Eta, dijetEta, jet1Pt, jet2Pt,jet1genPt, jet2genPt, mj1j2, numJet1Matched, numJet2Matched, numDijetMatched, csvBtag1, csvBtag2, csvBtag3, csvMvaBtag1, csvMvaBtag2, csvMvaBtag3, jetProbBtag1, jetProbBtag2, jetProbBtag3, tcheBtag1, tcheBtag2, tcheBtag3, weight;

  bool jet1isMatched, jet2isMatched, jet1isBMatched, jet2isBMatched, jet3isBMatched, jet4isBMatched;

  int jet3, nJets, jet1PtRank, jet2PtRank, jet3PtRank, jet4PtRank;

  numJet1Matched = 0;
  numJet2Matched = 0;
  numDijetMatched = 0;
  

  //We select the loaves to be read
  my_tuple->SetBranchAddress("pho1pt",&pho1pt);
  my_tuple->SetBranchAddress("pho2pt",&pho2pt);
  my_tuple->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tuple->SetBranchAddress("pho2Eta",&pho2Eta);
  my_tuple->SetBranchAddress("pho1Phi",&pho1Phi);
  my_tuple->SetBranchAddress("pho2Phi",&pho2Phi);
  my_tuple->SetBranchAddress("diphoM",&diphoM);
  my_tuple->SetBranchAddress("diphoEta",&diphoEta);
  my_tuple->SetBranchAddress("diphopt",&diphopt);
  my_tuple->SetBranchAddress("dijetEta",&dijetEta);
  my_tuple->SetBranchAddress("jet1Pt",&jet1Pt);
  my_tuple->SetBranchAddress("jet2Pt",&jet2Pt);
  my_tuple->SetBranchAddress("jet1p4",&jet1p4);
  my_tuple->SetBranchAddress("jet2p4",&jet2p4);
  my_tuple->SetBranchAddress("jet3p4",&jet3p4);
  my_tuple->SetBranchAddress("jet1genPt",&jet1genPt);
  my_tuple->SetBranchAddress("jet2genPt",&jet2genPt);
  my_tuple->SetBranchAddress("jet1Eta",&jet1Eta);
  my_tuple->SetBranchAddress("jet2Eta",&jet2Eta);
  my_tuple->SetBranchAddress("mj1j2",&mj1j2);
  my_tuple->SetBranchAddress("jet3",&jet3);
  my_tuple->SetBranchAddress("jet1isMatched",&jet1isMatched);
  my_tuple->SetBranchAddress("jet2isMatched",&jet2isMatched);
  my_tuple->SetBranchAddress("jet1isBMatched",&jet1isBMatched);
  my_tuple->SetBranchAddress("jet2isBMatched",&jet2isBMatched);
  my_tuple->SetBranchAddress("jet3isBMatched",&jet3isBMatched);
  my_tuple->SetBranchAddress("jet4isBMatched",&jet4isBMatched);
  my_tuple->SetBranchAddress("csvBtag1",&csvBtag1); 
  my_tuple->SetBranchAddress("csvBtag2",&csvBtag2); 
  my_tuple->SetBranchAddress("csvBtag3",&csvBtag3);  
  my_tuple->SetBranchAddress("csvMvaBtag1",&csvMvaBtag1); 
  my_tuple->SetBranchAddress("csvMvaBtag2",&csvMvaBtag2); 
  my_tuple->SetBranchAddress("csvMvaBtag3",&csvMvaBtag3); 
  my_tuple->SetBranchAddress("jetProbBtag1",&jetProbBtag1); 
  my_tuple->SetBranchAddress("jetProbBtag2",&jetProbBtag2); 
  my_tuple->SetBranchAddress("jetProbBtag3",&jetProbBtag3); 
  my_tuple->SetBranchAddress("tcheBtag1",&tcheBtag1); 
  my_tuple->SetBranchAddress("tcheBtag2",&tcheBtag2); 
  my_tuple->SetBranchAddress("tcheBtag3",&tcheBtag3);
  my_tuple->SetBranchAddress("weight",&weight);
  my_tuple->SetBranchAddress("nJets",&nJets);
  my_tuple->SetBranchAddress("jet1PtRank",&jet1PtRank);
  my_tuple->SetBranchAddress("jet2PtRank",&jet2PtRank);
  my_tuple->SetBranchAddress("jet3PtRank",&jet3PtRank);
  my_tuple->SetBranchAddress("jet4PtRank",&jet4PtRank);

  my_tupleZH->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleZH->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleZH->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleZH->SetBranchAddress("pho2Eta",&pho2Eta);
  my_tupleZH->SetBranchAddress("pho1Phi",&pho1Phi);
  my_tupleZH->SetBranchAddress("pho2Phi",&pho2Phi);
  my_tupleZH->SetBranchAddress("diphoM",&diphoM);
  my_tupleZH->SetBranchAddress("diphoEta",&diphoEta);
  my_tupleZH->SetBranchAddress("diphopt",&diphopt);
  my_tupleZH->SetBranchAddress("dijetEta",&dijetEta);
  my_tupleZH->SetBranchAddress("jet1Pt",&jet1Pt);
  my_tupleZH->SetBranchAddress("jet2Pt",&jet2Pt);
  my_tupleZH->SetBranchAddress("jet1p4",&jet1p4);
  my_tupleZH->SetBranchAddress("jet2p4",&jet2p4);
  my_tupleZH->SetBranchAddress("jet3p4",&jet3p4);
  my_tupleZH->SetBranchAddress("jet1genPt",&jet1genPt);
  my_tupleZH->SetBranchAddress("jet2genPt",&jet2genPt);
  my_tupleZH->SetBranchAddress("jet1Eta",&jet1Eta);
  my_tupleZH->SetBranchAddress("jet2Eta",&jet2Eta);
  my_tupleZH->SetBranchAddress("mj1j2",&mj1j2);
  my_tupleZH->SetBranchAddress("jet3",&jet3);
  my_tupleZH->SetBranchAddress("jet1isMatched",&jet1isMatched);
  my_tupleZH->SetBranchAddress("jet2isMatched",&jet2isMatched);
  my_tupleZH->SetBranchAddress("jet1isBMatched",&jet1isBMatched);
  my_tupleZH->SetBranchAddress("jet2isBMatched",&jet2isBMatched);
  my_tupleZH->SetBranchAddress("csvBtag1",&csvBtag1); 
  my_tupleZH->SetBranchAddress("csvBtag2",&csvBtag2); 
  my_tupleZH->SetBranchAddress("csvBtag3",&csvBtag3);  
  my_tupleZH->SetBranchAddress("csvMvaBtag1",&csvMvaBtag1); 
  my_tupleZH->SetBranchAddress("csvMvaBtag2",&csvMvaBtag2); 
  my_tupleZH->SetBranchAddress("csvMvaBtag3",&csvMvaBtag3); 
  my_tupleZH->SetBranchAddress("jetProbBtag1",&jetProbBtag1); 
  my_tupleZH->SetBranchAddress("jetProbBtag2",&jetProbBtag2); 
  my_tupleZH->SetBranchAddress("jetProbBtag3",&jetProbBtag3); 
  my_tupleZH->SetBranchAddress("tcheBtag1",&tcheBtag1); 
  my_tupleZH->SetBranchAddress("tcheBtag2",&tcheBtag2); 
  my_tupleZH->SetBranchAddress("tcheBtag3",&tcheBtag3);
  my_tupleZH->SetBranchAddress("weight",&weight);
  my_tupleZH->SetBranchAddress("nJets",&nJets);
  my_tupleZH->SetBranchAddress("jet1PtRank",&jet1PtRank);
  my_tupleZH->SetBranchAddress("jet2PtRank",&jet2PtRank);
  my_tupleZH->SetBranchAddress("jet3PtRank",&jet3PtRank);
  my_tupleZH->SetBranchAddress("jet4PtRank",&jet4PtRank);

  my_tupleWH->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleWH->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleWH->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleWH->SetBranchAddress("pho2Eta",&pho2Eta);
  my_tupleWH->SetBranchAddress("pho1Phi",&pho1Phi);
  my_tupleWH->SetBranchAddress("pho2Phi",&pho2Phi);
  my_tupleWH->SetBranchAddress("diphoM",&diphoM);
  my_tupleWH->SetBranchAddress("diphoEta",&diphoEta);
  my_tupleWH->SetBranchAddress("diphopt",&diphopt);
  my_tupleWH->SetBranchAddress("dijetEta",&dijetEta);
  my_tupleWH->SetBranchAddress("jet1Pt",&jet1Pt);
  my_tupleWH->SetBranchAddress("jet2Pt",&jet2Pt);
  my_tupleWH->SetBranchAddress("jet1p4",&jet1p4);
  my_tupleWH->SetBranchAddress("jet2p4",&jet2p4);
  my_tupleWH->SetBranchAddress("jet3p4",&jet3p4);
  my_tupleWH->SetBranchAddress("jet1genPt",&jet1genPt);
  my_tupleWH->SetBranchAddress("jet2genPt",&jet2genPt);
  my_tupleWH->SetBranchAddress("jet1Eta",&jet1Eta);
  my_tupleWH->SetBranchAddress("jet2Eta",&jet2Eta);
  my_tupleWH->SetBranchAddress("mj1j2",&mj1j2);
  my_tupleWH->SetBranchAddress("jet3",&jet3);
  my_tupleWH->SetBranchAddress("jet1isMatched",&jet1isMatched);
  my_tupleWH->SetBranchAddress("jet2isMatched",&jet2isMatched);
  my_tupleWH->SetBranchAddress("csvBtag1",&csvBtag1); 
  my_tupleWH->SetBranchAddress("csvBtag2",&csvBtag2); 
  my_tupleWH->SetBranchAddress("csvBtag3",&csvBtag3);  
  my_tupleWH->SetBranchAddress("csvMvaBtag1",&csvMvaBtag1); 
  my_tupleWH->SetBranchAddress("csvMvaBtag2",&csvMvaBtag2); 
  my_tupleWH->SetBranchAddress("csvMvaBtag3",&csvMvaBtag3); 
  my_tupleWH->SetBranchAddress("jetProbBtag1",&jetProbBtag1); 
  my_tupleWH->SetBranchAddress("jetProbBtag2",&jetProbBtag2); 
  my_tupleWH->SetBranchAddress("jetProbBtag3",&jetProbBtag3); 
  my_tupleWH->SetBranchAddress("tcheBtag1",&tcheBtag1); 
  my_tupleWH->SetBranchAddress("tcheBtag2",&tcheBtag2); 
  my_tupleWH->SetBranchAddress("tcheBtag3",&tcheBtag3);
  my_tupleWH->SetBranchAddress("weight",&weight);
  my_tupleWH->SetBranchAddress("nJets",&nJets);
  my_tupleWH->SetBranchAddress("jet1PtRank",&jet1PtRank);
  my_tupleWH->SetBranchAddress("jet2PtRank",&jet2PtRank);
  my_tupleWH->SetBranchAddress("jet3PtRank",&jet3PtRank);
  my_tupleWH->SetBranchAddress("jet4PtRank",&jet4PtRank);

  my_tupleGGH->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleGGH->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleGGH->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleGGH->SetBranchAddress("pho2Eta",&pho2Eta);
  my_tupleGGH->SetBranchAddress("pho1Phi",&pho1Phi);
  my_tupleGGH->SetBranchAddress("pho2Phi",&pho2Phi);
  my_tupleGGH->SetBranchAddress("diphoM",&diphoM);
  my_tupleGGH->SetBranchAddress("diphoEta",&diphoEta);
  my_tupleGGH->SetBranchAddress("diphopt",&diphopt);
  my_tupleGGH->SetBranchAddress("dijetEta",&dijetEta);
  my_tupleGGH->SetBranchAddress("jet1Pt",&jet1Pt);
  my_tupleGGH->SetBranchAddress("jet2Pt",&jet2Pt);
  my_tupleGGH->SetBranchAddress("jet1p4",&jet1p4);
  my_tupleGGH->SetBranchAddress("jet2p4",&jet2p4);
  my_tupleGGH->SetBranchAddress("jet3p4",&jet3p4);
  my_tupleGGH->SetBranchAddress("jet1genPt",&jet1genPt);
  my_tupleGGH->SetBranchAddress("jet2genPt",&jet2genPt);
  my_tupleGGH->SetBranchAddress("jet1Eta",&jet1Eta);
  my_tupleGGH->SetBranchAddress("jet2Eta",&jet2Eta);
  my_tupleGGH->SetBranchAddress("mj1j2",&mj1j2);
  my_tupleGGH->SetBranchAddress("jet3",&jet3);
  my_tupleGGH->SetBranchAddress("jet1isMatched",&jet1isMatched);
  my_tupleGGH->SetBranchAddress("jet2isMatched",&jet2isMatched);
  my_tupleGGH->SetBranchAddress("csvBtag1",&csvBtag1); 
  my_tupleGGH->SetBranchAddress("csvBtag2",&csvBtag2); 
  my_tupleGGH->SetBranchAddress("csvBtag3",&csvBtag3);  
  my_tupleGGH->SetBranchAddress("csvMvaBtag1",&csvMvaBtag1); 
  my_tupleGGH->SetBranchAddress("csvMvaBtag2",&csvMvaBtag2); 
  my_tupleGGH->SetBranchAddress("csvMvaBtag3",&csvMvaBtag3); 
  my_tupleGGH->SetBranchAddress("jetProbBtag1",&jetProbBtag1); 
  my_tupleGGH->SetBranchAddress("jetProbBtag2",&jetProbBtag2); 
  my_tupleGGH->SetBranchAddress("jetProbBtag3",&jetProbBtag3); 
  my_tupleGGH->SetBranchAddress("tcheBtag1",&tcheBtag1); 
  my_tupleGGH->SetBranchAddress("tcheBtag2",&tcheBtag2); 
  my_tupleGGH->SetBranchAddress("tcheBtag3",&tcheBtag3);
  my_tupleGGH->SetBranchAddress("weight",&weight);
  my_tupleGGH->SetBranchAddress("nJets",&nJets);
  my_tupleGGH->SetBranchAddress("jet1PtRank",&jet1PtRank);
  my_tupleGGH->SetBranchAddress("jet2PtRank",&jet2PtRank);
  my_tupleGGH->SetBranchAddress("jet3PtRank",&jet3PtRank);
  my_tupleGGH->SetBranchAddress("jet4PtRank",&jet4PtRank);

  my_tupleVBF->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleVBF->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleVBF->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleVBF->SetBranchAddress("pho2Eta",&pho2Eta);
  my_tupleVBF->SetBranchAddress("pho1Phi",&pho1Phi);
  my_tupleVBF->SetBranchAddress("pho2Phi",&pho2Phi);
  my_tupleVBF->SetBranchAddress("diphoM",&diphoM);
  my_tupleVBF->SetBranchAddress("diphoEta",&diphoEta);
  my_tupleVBF->SetBranchAddress("diphopt",&diphopt);
  my_tupleVBF->SetBranchAddress("dijetEta",&dijetEta);
  my_tupleVBF->SetBranchAddress("jet1Pt",&jet1Pt);
  my_tupleVBF->SetBranchAddress("jet2Pt",&jet2Pt);
  my_tupleVBF->SetBranchAddress("jet1p4",&jet1p4);
  my_tupleVBF->SetBranchAddress("jet2p4",&jet2p4);
  my_tupleVBF->SetBranchAddress("jet3p4",&jet3p4);
  my_tupleVBF->SetBranchAddress("jet1genPt",&jet1genPt);
  my_tupleVBF->SetBranchAddress("jet2genPt",&jet2genPt);
  my_tupleVBF->SetBranchAddress("jet1Eta",&jet1Eta);
  my_tupleVBF->SetBranchAddress("jet2Eta",&jet2Eta);
  my_tupleVBF->SetBranchAddress("mj1j2",&mj1j2);
  my_tupleVBF->SetBranchAddress("jet3",&jet3);
  my_tupleVBF->SetBranchAddress("jet1isMatched",&jet1isMatched);
  my_tupleVBF->SetBranchAddress("jet2isMatched",&jet2isMatched);
  my_tupleVBF->SetBranchAddress("csvBtag1",&csvBtag1); 
  my_tupleVBF->SetBranchAddress("csvBtag2",&csvBtag2); 
  my_tupleVBF->SetBranchAddress("csvBtag3",&csvBtag3);  
  my_tupleVBF->SetBranchAddress("csvMvaBtag1",&csvMvaBtag1); 
  my_tupleVBF->SetBranchAddress("csvMvaBtag2",&csvMvaBtag2); 
  my_tupleVBF->SetBranchAddress("csvMvaBtag3",&csvMvaBtag3); 
  my_tupleVBF->SetBranchAddress("jetProbBtag1",&jetProbBtag1); 
  my_tupleVBF->SetBranchAddress("jetProbBtag2",&jetProbBtag2); 
  my_tupleVBF->SetBranchAddress("jetProbBtag3",&jetProbBtag3); 
  my_tupleVBF->SetBranchAddress("tcheBtag1",&tcheBtag1); 
  my_tupleVBF->SetBranchAddress("tcheBtag2",&tcheBtag2); 
  my_tupleVBF->SetBranchAddress("tcheBtag3",&tcheBtag3);
  my_tupleVBF->SetBranchAddress("weight",&weight);
  my_tupleVBF->SetBranchAddress("nJets",&nJets);

  my_tupleTTH->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleTTH->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleTTH->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleTTH->SetBranchAddress("pho2Eta",&pho2Eta);
  my_tupleTTH->SetBranchAddress("pho1Phi",&pho1Phi);
  my_tupleTTH->SetBranchAddress("pho2Phi",&pho2Phi);
  my_tupleTTH->SetBranchAddress("diphoM",&diphoM);
  my_tupleTTH->SetBranchAddress("diphoEta",&diphoEta);
  my_tupleTTH->SetBranchAddress("diphopt",&diphopt);
  my_tupleTTH->SetBranchAddress("dijetEta",&dijetEta);
  my_tupleTTH->SetBranchAddress("jet1Pt",&jet1Pt);
  my_tupleTTH->SetBranchAddress("jet2Pt",&jet2Pt);
  my_tupleTTH->SetBranchAddress("jet1p4",&jet1p4);
  my_tupleTTH->SetBranchAddress("jet2p4",&jet2p4);
  my_tupleTTH->SetBranchAddress("jet3p4",&jet3p4);
  my_tupleTTH->SetBranchAddress("jet1genPt",&jet1genPt);
  my_tupleTTH->SetBranchAddress("jet2genPt",&jet2genPt);
  my_tupleTTH->SetBranchAddress("jet1Eta",&jet1Eta);
  my_tupleTTH->SetBranchAddress("jet2Eta",&jet2Eta);
  my_tupleTTH->SetBranchAddress("mj1j2",&mj1j2);
  my_tupleTTH->SetBranchAddress("jet3",&jet3);
  my_tupleTTH->SetBranchAddress("jet1isMatched",&jet1isMatched);
  my_tupleTTH->SetBranchAddress("jet2isMatched",&jet2isMatched);
  my_tupleTTH->SetBranchAddress("csvBtag1",&csvBtag1); 
  my_tupleTTH->SetBranchAddress("csvBtag2",&csvBtag2); 
  my_tupleTTH->SetBranchAddress("csvBtag3",&csvBtag3);  
  my_tupleTTH->SetBranchAddress("csvMvaBtag1",&csvMvaBtag1); 
  my_tupleTTH->SetBranchAddress("csvMvaBtag2",&csvMvaBtag2); 
  my_tupleTTH->SetBranchAddress("csvMvaBtag3",&csvMvaBtag3); 
  my_tupleTTH->SetBranchAddress("jetProbBtag1",&jetProbBtag1); 
  my_tupleTTH->SetBranchAddress("jetProbBtag2",&jetProbBtag2); 
  my_tupleTTH->SetBranchAddress("jetProbBtag3",&jetProbBtag3); 
  my_tupleTTH->SetBranchAddress("tcheBtag1",&tcheBtag1); 
  my_tupleTTH->SetBranchAddress("tcheBtag2",&tcheBtag2); 
  my_tupleTTH->SetBranchAddress("tcheBtag3",&tcheBtag3);
  my_tupleTTH->SetBranchAddress("weight",&weight);
  my_tupleTTH->SetBranchAddress("nJets",&nJets);
  my_tupleTTH->SetBranchAddress("jet1PtRank",&jet1PtRank);
  my_tupleTTH->SetBranchAddress("jet2PtRank",&jet2PtRank);
  my_tupleTTH->SetBranchAddress("jet3PtRank",&jet3PtRank);
  my_tupleTTH->SetBranchAddress("jet4PtRank",&jet4PtRank);
  
  for (int irow=0;irow<my_tupleZH->GetEntries();++irow){
    my_tupleZH->GetEntry(irow);
        float jet1recoPt = (jet1Pt-jet1genPt)*0.9+jet1genPt;
        float jet2recoPt = (jet2Pt-jet2genPt)*0.9+jet2genPt;

	TLorentzVector  jet1recop4 = *jet1p4;
	jet1recop4.SetPx((jet1recop4.Px())*jet1recoPt/jet1Pt);
	jet1recop4.SetPy((jet1recop4.Py())*jet1recoPt/jet1Pt);
	jet1recop4.SetPz((jet1recop4.Pz())*jet1recoPt/jet1Pt);
	jet1recop4.SetE((jet1recop4.E())*jet1recoPt/jet1Pt);
	TLorentzVector  jet2recop4 = *jet2p4;
	jet2recop4.SetPx((jet2recop4.Px())*jet2recoPt/jet2Pt);
	jet2recop4.SetPy((jet2recop4.Py())*jet2recoPt/jet2Pt);
	jet2recop4.SetPz((jet2recop4.Pz())*jet2recoPt/jet2Pt);
	jet2recop4.SetE((jet2recop4.E())*jet2recoPt/jet2Pt);
	TLorentzVector jetSumrecop4 = jet1recop4 + jet2recop4;

    if ((pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
//	(jet3) < 0 &&
//	(nJets)<=3 &&
	(pho1Eta) < 2.5 &&
	(pho1Eta) > -2.5 &&
	(pho2Eta) < 2.5 &&
	(pho2Eta) > -2.5 &&
	(jet1recop4.Pt()) > 40 &&
	(jet2recop4.Pt()) > 40 &&
	(jet1Eta) < 2.1 &&
	(jet1Eta) > -2.1 &&
	(jet2Eta) < 2.1 &&
	(jet2Eta) > -2.1
//	jetSumrecop4.M()> 108 &&
//	jetSumrecop4.M()< 138
	
	)
    {	hdijetZHpt->Fill(jet1Pt+jet2Pt);
	hjetZHPt->Fill(jet1Pt);
	hjetZHPt->Fill(jet2Pt);
	hdiphoZHpt->Fill(diphopt);
	hpho1ZHpt->Fill(pho1pt);
	hpho2ZHpt->Fill(pho2pt);
	hjet1ZHPt->Fill(jet1Pt);
	hjet2ZHPt->Fill(jet2Pt);


	//Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2ZH->Fill(jetSumrecop4.M(),weight);
        hDeltaRZH->Fill(sqrt(asin(sin(pho2Phi-pho1Phi))*asin(sin(pho2Phi-pho1Phi))+(pho2Eta-pho1Eta)*(pho2Eta-pho1Eta)));
	hdiphoMZH->Fill(diphoM,weight);
	hnJetsZH->Fill(nJets,weight);

	
	if ((jet1isBMatched)==1 &&
	    (jet2isBMatched)==1)
	{hmj1j2ZHBMatched->Fill(jetSumrecop4.M(),weight);
	}

     
    }

  }
  
  for (int irow=0;irow<my_tupleWH->GetEntries();++irow){
    my_tupleWH->GetEntry(irow);
        float jet1recoPt = (jet1Pt-jet1genPt)*0.9+jet1genPt;
        float jet2recoPt = (jet2Pt-jet2genPt)*0.9+jet2genPt;

	TLorentzVector  jet1recop4 = *jet1p4;
	jet1recop4.SetPx((jet1recop4.Px())*jet1recoPt/jet1Pt);
	jet1recop4.SetPy((jet1recop4.Py())*jet1recoPt/jet1Pt);
	jet1recop4.SetPz((jet1recop4.Pz())*jet1recoPt/jet1Pt);
	jet1recop4.SetE((jet1recop4.E())*jet1recoPt/jet1Pt);
	TLorentzVector  jet2recop4 = *jet2p4;
	jet2recop4.SetPx((jet2recop4.Px())*jet2recoPt/jet2Pt);
	jet2recop4.SetPy((jet2recop4.Py())*jet2recoPt/jet2Pt);
	jet2recop4.SetPz((jet2recop4.Pz())*jet2recoPt/jet2Pt);
	jet2recop4.SetE((jet2recop4.E())*jet2recoPt/jet2Pt);
	TLorentzVector jetSumrecop4 = jet1recop4 + jet2recop4;

    if ((pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
//	(jet3) < 0 &&
//	(nJets)<=3 &&      
	(pho1Eta) < 2.5 &&
	(pho1Eta) > -2.5 &&
	(pho2Eta) < 2.5 &&
	(pho2Eta) > -2.5 &&
	(jet1recop4.Pt()) > 40 &&
	(jet2recop4.Pt()) > 40 &&
	(jet1Eta) < 2.1 &&
	(jet1Eta) > -2.1 &&
	(jet2Eta) < 2.1 &&
	(jet2Eta) > -2.1
//	jetSumrecop4.M()> 108 &&
//	jetSumrecop4.M()< 138
	
	)
      { //Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2WH->Fill(jetSumrecop4.M(),weight);
        hDeltaRWH->Fill(sqrt(asin(sin(pho2Phi-pho1Phi))*asin(sin(pho2Phi-pho1Phi))+(pho2Eta-pho1Eta)*(pho2Eta-pho1Eta)));
	hdiphoMWH->Fill(diphoM,weight);
	hnJetsWH->Fill(nJets,weight);

    }

  }

  
  for (int irow=0;irow<my_tupleGGH->GetEntries();++irow){
    my_tupleGGH->GetEntry(irow);
        float jet1recoPt = (jet1Pt-jet1genPt)*0.9+jet1genPt;
        float jet2recoPt = (jet2Pt-jet2genPt)*0.9+jet2genPt;

	TLorentzVector  jet1recop4 = *jet1p4;
	jet1recop4.SetPx((jet1recop4.Px())*jet1recoPt/jet1Pt);
	jet1recop4.SetPy((jet1recop4.Py())*jet1recoPt/jet1Pt);
	jet1recop4.SetPz((jet1recop4.Pz())*jet1recoPt/jet1Pt);
	jet1recop4.SetE((jet1recop4.E())*jet1recoPt/jet1Pt);
	TLorentzVector  jet2recop4 = *jet2p4;
	jet2recop4.SetPx((jet2recop4.Px())*jet2recoPt/jet2Pt);
	jet2recop4.SetPy((jet2recop4.Py())*jet2recoPt/jet2Pt);
	jet2recop4.SetPz((jet2recop4.Pz())*jet2recoPt/jet2Pt);
	jet2recop4.SetE((jet2recop4.E())*jet2recoPt/jet2Pt);
	TLorentzVector jetSumrecop4 = jet1recop4 + jet2recop4;

    if ((pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
//	(jet3) < 0 &&
//	(nJets)<=3 &&
	(pho1Eta) < 2.5 &&
	(pho1Eta) > -2.5 &&
	(pho2Eta) < 2.5 &&
	(pho2Eta) > -2.5 &&
	(jet1recop4.Pt()) > 40 &&
	(jet2recop4.Pt()) > 40 &&
	(jet1Eta) < 2.1 &&
	(jet1Eta) > -2.1 &&
	(jet2Eta) < 2.1 &&
	(jet2Eta) > -2.1 
//	jetSumrecop4.M()> 108 &&
//	jetSumrecop4.M()< 138
	
	)
      { hmj1j2GGHCuts->Fill(jetSumrecop4.M(),weight);
	hdiphoMGGHCuts->Fill(diphoM,weight);

        //Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2GGH->Fill(jetSumrecop4.M(),weight);
        hDeltaRGGH->Fill(sqrt(asin(sin(pho2Phi-pho1Phi))*asin(sin(pho2Phi-pho1Phi))+(pho2Eta-pho1Eta)*(pho2Eta-pho1Eta)));
	hdiphoMGGH->Fill(diphoM,weight);
	hnJetsGGH->Fill(nJets,weight);
	hjet1PtRankGGH->Fill(jet1PtRank);
	hjet2PtRankGGH->Fill(jet2PtRank);
	hjet3PtRankGGH->Fill(jet3PtRank);
	hjet4PtRankGGH->Fill(jet4PtRank);
    }

  }

  
  for (int irow=0;irow<my_tupleVBF->GetEntries();++irow){
    my_tupleVBF->GetEntry(irow);

        float jet1recoPt = (jet1Pt-jet1genPt)*0.9+jet1genPt;
	float jet2recoPt = (jet2Pt-jet2genPt)*0.9+jet2genPt;

	TLorentzVector  jet1recop4 = *jet1p4;
	jet1recop4.SetPx((jet1recop4.Px())*jet1recoPt/jet1Pt);
	jet1recop4.SetPy((jet1recop4.Py())*jet1recoPt/jet1Pt);
	jet1recop4.SetPz((jet1recop4.Pz())*jet1recoPt/jet1Pt);
	jet1recop4.SetE((jet1recop4.E())*jet1recoPt/jet1Pt);
	TLorentzVector  jet2recop4 = *jet2p4;
	jet2recop4.SetPx((jet2recop4.Px())*jet2recoPt/jet2Pt);
	jet2recop4.SetPy((jet2recop4.Py())*jet2recoPt/jet2Pt);
	jet2recop4.SetPz((jet2recop4.Pz())*jet2recoPt/jet2Pt);
	jet2recop4.SetE((jet2recop4.E())*jet2recoPt/jet2Pt);
	TLorentzVector jetSumrecop4 = jet1recop4 + jet2recop4;

    if ((pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
//	(jet3) < 0 &&
	(pho1Eta) < 2.5 &&
	(pho1Eta) > -2.5 &&
	(pho2Eta) < 2.5 &&
	(pho2Eta) > -2.5 &&
	(jet1recop4.Pt()) > 40 &&
	(jet2recop4.Pt()) > 40 &&
	(jet1Eta) < 2.1 &&
	(jet1Eta) > -2.1 &&
	(jet2Eta) < 2.1 &&
	(jet2Eta) > -2.1
	       
	)
      {

        //Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2VBF->Fill(jetSumrecop4.M(),weight);
        hDeltaRVBF->Fill(sqrt(asin(sin(pho2Phi-pho1Phi))*asin(sin(pho2Phi-pho1Phi))+(pho2Eta-pho1Eta)*(pho2Eta-pho1Eta)));
    }

  }


  for (int irow=0;irow<my_tupleTTH->GetEntries();++irow){
    my_tupleTTH->GetEntry(irow);

        float jet1recoPt = (jet1Pt-jet1genPt)*0.9+jet1genPt;
	float jet2recoPt = (jet2Pt-jet2genPt)*0.9+jet2genPt;

	TLorentzVector  jet1recop4 = *jet1p4;
	jet1recop4.SetPx((jet1recop4.Px())*jet1recoPt/jet1Pt);
	jet1recop4.SetPy((jet1recop4.Py())*jet1recoPt/jet1Pt);
	jet1recop4.SetPz((jet1recop4.Pz())*jet1recoPt/jet1Pt);
	jet1recop4.SetE((jet1recop4.E())*jet1recoPt/jet1Pt);
	TLorentzVector  jet2recop4 = *jet2p4;
	jet2recop4.SetPx((jet2recop4.Px())*jet2recoPt/jet2Pt);
	jet2recop4.SetPy((jet2recop4.Py())*jet2recoPt/jet2Pt);
	jet2recop4.SetPz((jet2recop4.Pz())*jet2recoPt/jet2Pt);
	jet2recop4.SetE((jet2recop4.E())*jet2recoPt/jet2Pt);
	TLorentzVector jetSumrecop4 = jet1recop4 + jet2recop4;

    if ((pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
//	(jet3) < 0 &&
//	(nJets)<=3 &&
	(pho1Eta) < 2.5 &&
	(pho1Eta) > -2.5 &&
	(pho2Eta) < 2.5 &&
	(pho2Eta) > -2.5 &&
	(jet1recop4.Pt()) > 40 &&
	(jet2recop4.Pt()) > 40 &&
	(jet1Eta) < 2.1 &&
	(jet1Eta) > -2.1 &&
	(jet2Eta) < 2.1 &&
	(jet2Eta) > -2.1
//	jetSumrecop4.M()> 108 &&
//	jetSumrecop4.M()< 138
	
	)
      {

        //Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2TTH->Fill(jetSumrecop4.M(),weight);
        hDeltaRTTH->Fill(sqrt(asin(sin(pho2Phi-pho1Phi))*asin(sin(pho2Phi-pho1Phi))+(pho2Eta-pho1Eta)*(pho2Eta-pho1Eta)));
	hdiphoMTTH->Fill(diphoM,weight);
	hnJetsTTH->Fill(nJets,weight);
	hjet1PtRankTTH->Fill(jet1PtRank);
	hjet2PtRankTTH->Fill(jet2PtRank);
	hjet3PtRankTTH->Fill(jet3PtRank);
	hjet4PtRankTTH->Fill(jet4PtRank);
    }

  }
//#######################################################################
  

  //Fill Histograms
  for (int irow=0;irow<my_tuple->GetEntries();++irow){
    my_tuple->GetEntry(irow);

    float jet1recoPt = (jet1Pt-jet1genPt)*0.9+jet1genPt;
    float jet2recoPt = (jet2Pt-jet2genPt)*0.9+jet2genPt;

	TLorentzVector  jet1recop4 = *jet1p4;
	jet1recop4.SetPx((jet1recop4.Px())*jet1recoPt/jet1Pt);
	jet1recop4.SetPy((jet1recop4.Py())*jet1recoPt/jet1Pt);
	jet1recop4.SetPz((jet1recop4.Pz())*jet1recoPt/jet1Pt);
	jet1recop4.SetE((jet1recop4.E())*jet1recoPt/jet1Pt);
	TLorentzVector  jet2recop4 = *jet2p4;
	jet2recop4.SetPx((jet2recop4.Px())*jet2recoPt/jet2Pt);
	jet2recop4.SetPy((jet2recop4.Py())*jet2recoPt/jet2Pt);
	jet2recop4.SetPz((jet2recop4.Pz())*jet2recoPt/jet2Pt);
	jet2recop4.SetE((jet2recop4.E())*jet2recoPt/jet2Pt);
	TLorentzVector jetSumrecop4 = jet1recop4 + jet2recop4;

    if (

	    
	//Cuts
	//(mj1j2) > 130 &&
	//(jet3) <0 &&
	//(jet1isMatched)==1 &&
	//(jet2isMatched)==1 &&
	//(jetProbBtag1)>0.275 &&
	//(jetProbBtag2)>0.275 &&
	//(csvBtag3)>0.898 &&
	//(csvMvaBtag1)>csvCut &&
	//(csvMvaBtag2)>0.679 &&
	//(jet1Pt-jet1genPt)>(20)&&
	//(jet1Pt-jet1genPt)<0 &&
	//(jet2Pt-jet2genPt)>(20)&&
	//(jet2Pt-jet2genPt)<0 &&
	(pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
//	(jet3) < 0 &&
//	(nJets)<=3 &&
	(pho1Eta) < 2.5 &&
	(pho1Eta) > -2.5 &&
	(pho2Eta) < 2.5 &&
	(pho2Eta) > -2.5 &&
	(jet1recop4.Pt()) > 40 &&
	(jet2recop4.Pt()) > 40 &&
	(jet1Eta) < 2.1 &&
	(jet1Eta) > -2.1 &&
	(jet2Eta) < 2.1 &&
	(jet2Eta) > -2.1
//	jetSumrecop4.M()> 108 &&
//	jetSumrecop4.M()< 138
	
	
	)



      { //Remplissage des histogrammes
	hpho1pt->Fill(pho1pt);
	hpho2pt->Fill(pho2pt);
	hdiphopt->Fill(diphopt);
	hpho1Eta->Fill(pho1Eta);
	hpho2Eta->Fill(pho2Eta);
	hdiphoEta->Fill(diphoEta);
	hdiphoM->Fill(diphoM,weight);
	hdijetpt->Fill(jet1Pt+jet2Pt);
	hjet1Pt->Fill(jet1Pt);
	hjet2Pt->Fill(jet2Pt);
	hjet1recoPt->Fill(jet1recoPt);
	hjet2recoPt->Fill(jet2recoPt);
	hjetPt->Fill(jet1Pt);
	hjetPt->Fill(jet2Pt);	

	if ((csvBtag1)>csvCut)
	{	hjetPtBtag->Fill(jet1Pt);
		hdivisionbis->Fill(jet1Pt);
	}


	if ((csvBtag2)>csvCut)
	{	hjetPtBtag->Fill(jet2Pt);
		hdivisionbis->Fill(jet2Pt);
	}

	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;

	hjet1recoPtBtag->Fill((jet1Pt-jet1genPt)*0.9+jet1genPt);
	hjet2recoPtBtag->Fill((jet2Pt-jet2genPt)*0.9+jet2genPt);	
	hjet1recogenPt->Fill(jet1Pt-jet1genPt);
	hjet2recogenPt->Fill(jet2Pt-jet2genPt);	
	hdijetptBtag->Fill(jet1Pt+jet2Pt);
	hjet1Eta->Fill(jet1Eta);
	hjet2Eta->Fill(jet2Eta);
	hdijetEta->Fill(dijetEta);
	hmj1j2->Fill(mj1j2,weight);
	hmj1j2reco->Fill(jetSumrecop4.M(),weight);
	hdiphoMHH->Fill(diphoM,weight);
	hnJetsHH->Fill(nJets,weight);
	if ((jet1isBMatched)==1){
	hjet1PtRankHH->Fill(jet1PtRank);
	}
	if ((jet2isBMatched)==1){
	hjet2PtRankHH->Fill(jet2PtRank);
	}
	if ((jet3isBMatched)==1){
	hjet3PtRankHH->Fill(jet3PtRank);
	}
	if ((jet4isBMatched)==1){
	hjet4PtRankHH->Fill(jet4PtRank);
	}
        hDeltaRHH->Fill(sqrt(asin(sin(pho2Phi-pho1Phi))*asin(sin(pho2Phi-pho1Phi))+(pho2Eta-pho1Eta)*(pho2Eta-pho1Eta)));
	hjet3->Fill(jet3);
	hcsvBtag1->Fill(csvBtag1);
	hcsvBtag2->Fill(csvBtag2);
	hcsvBtag3->Fill(csvBtag3);
	hcsvMvaBtag1->Fill(csvMvaBtag1);
	hcsvMvaBtag2->Fill(csvMvaBtag2);
	hcsvMvaBtag3->Fill(csvMvaBtag3);
	hjetProbBtag1->Fill(jetProbBtag1);
	hjetProbBtag2->Fill(jetProbBtag2);
	hjetProbBtag3->Fill(jetProbBtag3);
	htcheBtag1->Fill(tcheBtag1);
	htcheBtag2->Fill(tcheBtag2);
	htcheBtag3->Fill(tcheBtag3);
	
	if (jet1PtRank == 0 && (jet1isBMatched)==1){
		hjet1csvRankHH->Fill(0);
	}

	if (jet1PtRank == 1 && (jet1isBMatched)==1){
		hjet2csvRankHH->Fill(0);
	}
	if (jet1PtRank == 2 && (jet1isBMatched)==1){
		hjet3csvRankHH->Fill(0);
	}
	if (jet1PtRank == 3 && (jet1isBMatched)==1){
		hjet4csvRankHH->Fill(0);
	}
	if (jet2PtRank == 0 && (jet2isBMatched)==1){
		hjet1csvRankHH->Fill(1);
	}

	if (jet2PtRank == 1 && (jet2isBMatched)==1){
		hjet2csvRankHH->Fill(1);
	}
	if (jet2PtRank == 2 && (jet2isBMatched)==1){
		hjet3csvRankHH->Fill(1);
	}
	if (jet2PtRank == 3 && (jet2isBMatched)==1){
		hjet4csvRankHH->Fill(1);
	}
	if (jet3PtRank == 0 && (jet3isBMatched)==1){
		hjet1csvRankHH->Fill(2);
	}

	if (jet3PtRank == 1 && (jet3isBMatched)==1){
		hjet2csvRankHH->Fill(2);
	}
	if (jet3PtRank == 2 && (jet3isBMatched)==1){
		hjet3csvRankHH->Fill(2);
	}
	if (jet3PtRank == 3 && (jet3isBMatched)==1){
		hjet4csvRankHH->Fill(2);
	}
	if (jet4PtRank == 0 && (jet4isBMatched)==1){
		hjet1csvRankHH->Fill(3);
	}

	if (jet4PtRank == 1 && (jet4isBMatched)==1){
		hjet2csvRankHH->Fill(3);
	}
	if (jet4PtRank == 2 && (jet4isBMatched)==1){
		hjet3csvRankHH->Fill(3);
	}
	if (jet4PtRank == 3 && (jet4isBMatched)==1){
		hjet4csvRankHH->Fill(3);
	}
	/*
	//Count the number of matched jets

	
	hjet1isMatched->Fill(jet1isMatched);
	hjet2isMatched->Fill(jet2isMatched);
	
	
	if (jet1isMatched == 1){
	  numJet1Matched = numJet1Matched+1;
	}
	

	if (jet2isMatched == 1){
	  numJet2Matched = numJet2Matched+1;
	}

	if (jet1isMatched == 1 && jet2isMatched){
	  numDijetMatched = numDijetMatched+1;
	}
	*/
    }

  }

  
  //Print the number of entries of the tree, the number of entries after cuts, and the percentage
  float NentriesTree, NentriesHisto, NentriesBtag, PercentageCuts, PercentageBtag;
  NentriesTree = my_tuple-> GetEntries();
  NentriesHisto = hdiphopt-> GetEntries();
  NentriesBtag = hcsvMvaBtag1->GetEntries();
  PercentageCuts = NentriesHisto/NentriesTree*100;
  PercentageBtag = NentriesBtag/NentriesHisto*100;
  cout <<"Number of events : "<<NentriesTree<<"\n"<<
    "Number of selected events after Basic Cuts : "<<NentriesHisto<<"\n"<<
    "Number of selected events after Btagging : "<<NentriesBtag<<"\n"<<
    "Percentage of selected events : "<<PercentageCuts<<"%"<<"\n"<<
    "Percentage of Btagged events over selected events : "<<PercentageBtag<<"%"<<endl;



  /*
  //Print the number of matched jets after cuts over the number of generated jets after cuts
  float PercentageJet1Matched, PercentageJet2Matched, PercentageDijetMatched;
  PercentageJet1Matched = numJet1Matched/NentriesHisto*100;
  PercentageJet2Matched = numJet2Matched/NentriesHisto*100;
  PercentageDijetMatched = numDijetMatched/NentriesHisto*100;
  cout <<"Percentage of matched jet1 : "<<PercentageJet1Matched<<"%"<<"\n"<<
    "Percentage of matched jet2 : "<<PercentageJet2Matched<<"%"<<"\n"<<
    "Percentage of matched Di-jet : "<<PercentageDijetMatched<<"%"<<endl;
  */

  //Draw Histograms

  /*
  TCanvas* cphot =new TCanvas("cphot","Photon Analysis",0,0,1000,350);

  //Here is the color of the pads
  cphot->SetFillColor(0);

  cphot->Divide(3);

  cphot->cd(1);
  //Here is the color of the background
  cphot->SetFillColor(kBlue-10);
  hdiphopt->Draw();

  cphot->cd(2);
  hdiphoEta->Draw();

  cphot->cd(3);
  hdiphoM->Draw();
  hdiphoM->Fit("gdiphoM","");
  

  TCanvas* cjet =new TCanvas("cjet","Jet Analysis",0,350,1000,350);
  //Here is the color of the pads
  cjet->SetFillColor(0);  
  
  cjet->Divide(3);

  cjet->cd(1);
  //Here is the color of the background
  cjet->SetFillColor(kGreen-10);
  hdijetpt->Draw();

  cjet->cd(2);
  hdijetEta->Draw();

  cjet->cd(3);
  hmj1j2->Draw();
  hmj1j2->Fit("gmj1j2","R");

  TCanvas* cpho12 = new TCanvas("cpho12","Jet Analysis",0,0,650,650);
  cpho12->Divide(2,2);
  cpho12->cd(1);
  hpho1pt->Draw();
  cpho12->cd(2);
  hpho2pt->Draw();
  cpho12->cd(3);
  hpho1Eta->Draw();
  cpho12->cd(4);
  hpho2Eta->Draw();
  

  TCanvas* cjet12 = new TCanvas("cjet12","Jet Analysis",650,0,650,650);
  cjet12->Divide(2,2);
  cjet12->cd(1);
  hjet1Pt->Draw();
  cjet12->cd(2);
  hjet2Pt->Draw();
  cjet12->cd(3);
  hjet1Eta->Draw();
  cjet12->cd(4);
  hjet2Eta->Draw();



  TCanvas* cRecoGen = new TCanvas("cRecoGen","Reconstructed Jet Pt - Generated Jet Pt",100,100,700,350);
  cRecoGen->Divide(2);
  cRecoGen->cd(1);
  hjet1recogenPt->Draw();
  hjet1recogenPt->Fit("gjet1recogenPt","R");
  cRecoGen->cd(2);
  hjet2recogenPt->Draw();
  hjet2recogenPt->Fit("gjet2recogenPt","R");
*/

  TCanvas* cComparePt = new TCanvas("cComparePt","ZH and GGHH Pt comparision",100,100,800,800);
   float NormalisationK ;
   NormalisationK = (hdiphopt->GetEntries())/(hdiphoZHpt->GetEntries());
   hdiphoZHpt->Scale(NormalisationK);
  cComparePt->Divide(2);
// cComparePt->cd(1);
//  hdiphopt->Draw();
//  hdiphoZHpt->Draw("same");

  cComparePt->cd(1);
  hpho1ZHpt->Scale(NormalisationK);
  hpho1ZHpt->Draw();
  hpho1pt->Draw("same");

 TLegend *legpho1 = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legpho1->SetLineColor(1);
  legpho1->SetLineStyle(1);
  legpho1->SetLineWidth(1);
  legpho1->SetFillColor(0);
  legpho1->SetFillStyle(1001);
  legpho1->AddEntry(hpho1ZHpt,"ZH", "l");
  legpho1->AddEntry(hpho1pt,"HH", "l");
  legpho1->Draw();


  cComparePt->cd(2);
  hpho2ZHpt->Scale(NormalisationK);
  hpho2pt->Draw();
  hpho2ZHpt->Draw("same");

 TLegend *legpho2 = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legpho2->SetLineColor(1);
  legpho2->SetLineStyle(1);
  legpho2->SetLineWidth(1);
  legpho2->SetFillColor(0);
  legpho2->SetFillStyle(1001);
  legpho2->AddEntry(hpho2ZHpt,"ZH", "l");
  legpho2->AddEntry(hpho2pt,"HH", "l");
  legpho2->Draw();

  TCanvas* cMassJet3 = new TCanvas("cMassJet3","Mass and Jet3",100,100,800,800);
  cMassJet3->Divide(2,2);
  cMassJet3->cd(1);
  hmj1j2reco->Draw();
  //hmj1j2reco->Fit("gmj1j2","R");
  hmj1j2->Draw("same");  
  cMassJet3->cd(2);
  hdiphoM->Draw();
  cMassJet3->cd(3);
  hcsvBtag1->Draw();
  cMassJet3->cd(4);
  hcsvBtag2->Draw();

  TCanvas* cPtJet = new TCanvas("cPtJet","Efficiency after b-cut",100,100,1200,800);
/*  cPtJet->Divide(3,2);
  cPtJet->cd(1);
  //hjet1recoPt->Draw();
  hjet1Pt->Draw();
  cPtJet->cd(2); 
  hjet1PtBtag->Draw();
  cPtJet->cd(3);
  hdivisionbis1->Divide(hjet1Pt);
  hdivisionbis1->Draw();
  cPtJet->cd(4);
  hjet2Pt->Draw();
  //hjet2recoPt->Draw("same");
  cPtJet->cd(5); 
  hjet2PtBtag->Draw();
  cPtJet->cd(6);
  hdivisionbis2->Divide(hjet2Pt);
  hdivisionbis2->Draw();
*/
  TH1F*ratio = hdivisionbis-> Clone();
  ratio-> Reset();
  ratio-> Divide( hdivisionbis, hjetPt ,1 ,1 ,"B");
  ratio-> SetFillColor(kGreen-6);
  ratio-> Draw("e");

  TCanvas* cMassJet = new TCanvas("cMassJet","Mass",100,100,800,800);

  THStack *hs = new THStack("hs","Di-jet Mass");

//Rescale GGH
   float NormalisationConst ;
   NormalisationConst = (hmj1j2GGH->GetEntries())/(hmj1j2GGHCuts->GetEntries());
   hmj1j2GGHCuts->Scale(NormalisationConst);

   hs->Add(hmj1j2GGHCuts);
   hs->Add(hmj1j2WH);
   hs->Add(hmj1j2ZH);
   hs->Add(hmj1j2TTH);
   //hs->Add(hmj1j2VBF);
   hs->Draw();
   hmj1j2reco->Draw("same");

 TLegend *leg = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  leg->AddEntry(hmj1j2GGHCuts,"GGH", "f");
  leg->AddEntry(hmj1j2WH,"WH", "f");
  leg->AddEntry(hmj1j2ZH,"ZH", "f");
  leg->AddEntry(hmj1j2TTH,"TTH", "f");
  leg->AddEntry(hmj1j2reco,"HH", "f");

  leg->Draw();

/*
  TCanvas* cMassZHJet = new TCanvas("cMassZHJet","Mass",100,100,800,800);
  TLegend *legZH = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legZH->SetLineColor(1);
  legZH->SetLineStyle(1);
  legZH->SetLineWidth(1);
  legZH->SetFillColor(0);
  legZH->SetFillStyle(1001);

  legZH->AddEntry(hmj1j2ZH,"All selected ZH events", "f");
  legZH->AddEntry(hmj1j2ZHBMatched,"BMatched ZH events", "f");

   hmj1j2ZH->Draw();
   hmj1j2ZHBMatched->Draw("same");
*/

/*
  TCanvas* cDeltaR = new TCanvas("cDeltaR","DeltaR",100,100,800,800);
  hDeltaRHH->Scale(0.6);
  hDeltaRHH->Draw();
  hDeltaRZH->Scale(0.5);
  hDeltaRZH->Draw("same");
  hDeltaRWH->Scale(0.3);
  hDeltaRWH->Draw("same");
  hDeltaRGGH->Draw("same");
  hDeltaRTTH->Draw("same");

 TLegend *legDeltaR = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legDeltaR->SetLineColor(1);
  legDeltaR->SetLineStyle(1);
  legDeltaR->SetLineWidth(1);
  legDeltaR->SetFillColor(0);
  legDeltaR->SetFillStyle(1001);
     
  legDeltaR->AddEntry(hDeltaRGGH,"GGH", "l");
  legDeltaR->AddEntry(hDeltaRWH,"WH", "l");
  legDeltaR->AddEntry(hDeltaRZH,"ZH", "l");
  legDeltaR->AddEntry(hDeltaRTTH,"TTH", "l");
  legDeltaR->AddEntry(hDeltaRHH,"HH", "l");

  legDeltaR->Draw();
*/


  TCanvas* cMassVerifJet = new TCanvas("cMassVerifJet","Mass",100,100,800,800);  
//Filling Bkg histogramm
  hbkg->Add(hmj1j2ZH);
  hbkg->Add(hmj1j2TTH);
  hbkg->Add(hmj1j2GGHCuts);
  hbkg->Add(hmj1j2WH);
  hbkg->Draw();


  int bin1 = hbkg->FindBin(110);
  int bin2 = hbkg->FindBin(140);
  float NumBkg = hbkg->Integral(bin1,bin2);
  float NumEvts = hmj1j2reco->Integral(bin1,bin2);
  float Significance = NumEvts/sqrt(NumBkg);
  float Num = hbkg->Integral();
  float NumZH = hmj1j2ZH->Integral();
  float NumTTH = hmj1j2TTH->Integral();
  float NumZHWindow = hmj1j2ZH->Integral(bin1,bin2);
  float NumWHWindow = hmj1j2WH->Integral(bin1,bin2);
  float NumTTHWindow = hmj1j2TTH->Integral(bin1,bin2);
  float NumGGHWindow = hmj1j2GGHCuts->Integral(bin1,bin2);
  float NumZHBMatched = hmj1j2ZHBMatched->Integral();
  float NumZHBMatchedWindow = hmj1j2ZHBMatched->Integral(bin1,bin2);


  cout <<"Number of background events between 105 and 130 GeV : "<<NumBkg<<"\n"<<
    "Number of HH events between 110 and 140GeV : "<<NumEvts<<"\n"<<
    "Number  events between 0 and 300GeV : "<<Num<<"\n"<<
    "Number of ZH events between 0 and 300GeV : "<<NumZH<<"\n"<<
    "Number of BMatched ZH events between 0 and 300GeV : "<<NumZHBMatched<<"\n"<<
    "Number of TTH events between 0 and 300GeV : "<<NumTTH<<"\n"<<
    "Number of ZH events between 110 and 140GeV : "<<NumZHWindow<<"\n"<<
    "Number of WH events between 110 and 140GeV : "<<NumWHWindow<<"\n"<<
    "Number of TTH events between 110 and 140GeV : "<<NumTTHWindow<<"\n"<<
    "Number of GGH events between 110 and 140GeV : "<<NumGGHWindow<<"\n"<<
    "Number of BMatched ZH events between 110 and 140GeV : "<<NumZHBMatchedWindow<<"\n"<<
    "Number of BMatched ZH events over ZH events between 110 and 140GeV : "<<NumZHBMatchedWindow/NumZHWindow<<"\n"<<
    "Smallest B Tag : "<<csvCut1<<"\n"<<
    "Biggest B Tag : "<<csvCut2<<"\n"<<
    "Significance : "<<Significance<<endl;

  /*
  TCanvas* cMatched =new TCanvas("cMatched","MatchedJets",100,100,800,350);
  //Here is the color of the pads
  cMatched->SetFillColor(0);  
  
  cMatched->Divide(2);

  cMatched->cd(1);
  //Here is the color of the background
  cMatched->SetFillColor(kOrange-10);
  float scale1;
  scale1 = hjet1isMatched->GetEntries();
  hjet1isMatched->Scale(1/scale1);
  hjet1isMatched->Draw();

  cMatched->cd(2);
  float scale2;
  scale2 = hjet2isMatched->GetEntries();
  hjet2isMatched->Scale(1/scale2);
  hjet2isMatched->Draw();
  */
  TCanvas* cnJets = new TCanvas("cnJets","nJets",100,100,800,800);
  hnJetsTTH->Draw();
  hnJetsZH->Draw("same");
  hnJetsHH->Draw("same");
  hnJetsWH->Draw("same");
  hnJetsGGH->Draw("same");

 TLegend *legnJets = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legnJets->SetLineColor(1);
  legnJets->SetLineStyle(1);
  legnJets->SetLineWidth(1);
  legnJets->SetFillColor(0);
  legnJets->SetFillStyle(1001);
    	  
  legnJets->AddEntry(hnJetsGGH,"GGH", "l");
  legnJets->AddEntry(hnJetsWH,"WH", "l");
  legnJets->AddEntry(hnJetsZH,"ZH", "l");
  legnJets->AddEntry(hnJetsTTH,"TTH", "l");
  legnJets->AddEntry(hnJetsHH,"HH", "l");
    	  
  legnJets->Draw();



  TCanvas* cnJetsInt = new TCanvas("cnJetsInt","nJets Normalized",100,100,800,800);
  TH1F* hnJetsnormalizedGGH = hnJetsGGH->Clone();
  hnJetsnormalizedGGH->Scale(1/hnJetsnormalizedGGH->Integral());
  hnJetsnormalizedGGH->Draw();
  TH1F* hnJetsnormalizedZH = hnJetsZH->Clone(); 
  hnJetsnormalizedZH->Scale(1/hnJetsnormalizedZH->Integral());
  hnJetsnormalizedZH->Draw("same");
  TH1F* hnJetsnormalizedHH = hnJetsHH->Clone();
  hnJetsnormalizedHH->Scale(1/hnJetsnormalizedHH->Integral());
  hnJetsnormalizedHH->Draw("same");
  TH1F* hnJetsnormalizedWH = hnJetsWH->Clone();
  hnJetsnormalizedWH->Scale(1/hnJetsnormalizedWH->Integral());
  hnJetsnormalizedWH->Draw("same");
  TH1F* hnJetsnormalizedTTH = hnJetsTTH->Clone();
  hnJetsnormalizedTTH->Scale(1/hnJetsnormalizedTTH->Integral());
  hnJetsnormalizedTTH->Draw("same");

 TLegend *legnJetsInt = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legnJetsInt->SetLineColor(1);
  legnJetsInt->SetLineStyle(1);
  legnJetsInt->SetLineWidth(1);
  legnJetsInt->SetFillColor(0);
  legnJetsInt->SetFillStyle(1001);
    	  
  legnJetsInt->AddEntry(hnJetsGGH,"GGH", "l");
  legnJetsInt->AddEntry(hnJetsWH,"WH", "l");
  legnJetsInt->AddEntry(hnJetsZH,"ZH", "l");
  legnJetsInt->AddEntry(hnJetsTTH,"TTH", "l");
  legnJetsInt->AddEntry(hnJetsHH,"HH", "l");
    	  
  legnJetsInt->Draw();


  TCanvas* cMassPho = new TCanvas("cMassPho","DiPhotonMass",100,100,800,800);

  THStack *hsPho = new THStack("hsPho","Di-photon Mass");

//Rescale GGH
   float NormalisationConstPho ;
   NormalisationConstPho = (hdiphoMGGH->GetEntries())/(hdiphoMGGHCuts->GetEntries());
   hdiphoMGGHCuts->Scale(NormalisationConstPho);

   hsPho->Add(hdiphoMGGHCuts);
   hsPho->Add(hdiphoMWH);
   hsPho->Add(hdiphoMZH);
   hsPho->Add(hdiphoMTTH);
   hsPho->Add(hdiphoMHH);
   hsPho->Draw();

 TLegend *legPho = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legPho->SetLineColor(1);
  legPho->SetLineStyle(1);
  legPho->SetLineWidth(1);
  legPho->SetFillColor(0);
  legPho->SetFillStyle(1001);
     
  legPho->AddEntry(hdiphoMGGHCuts,"GGH", "f");
  legPho->AddEntry(hdiphoMWH,"WH", "f");
  legPho->AddEntry(hdiphoMZH,"ZH", "f");
  legPho->AddEntry(hdiphoMTTH,"TTH", "f");
  legPho->AddEntry(hdiphoMHH,"HH", "f");
     
  legPho->Draw();


  TCanvas* cJetPtRank = new TCanvas("cJetPtRank","Jets Pt Rank",100,100,800,800);
  cJetPtRank->Divide(2,2);
  cJetPtRank->cd(1);
  hjet1PtRankHH->Draw();
//  hjet1PtRankZH->Draw("same");
//  hjet1PtRankTTH->Draw("same");
//  hjet1PtRankWH->Draw("same");
//  hjet1PtRankGGH->Draw("same");

 TLegend *legJetPtRank = new TLegend(0.5604027,0.6384615,0.8892617,0.8916084,NULL,"brNDC");
//  leg->SetTextFont(62);
  legJetPtRank->SetLineColor(1);
  legJetPtRank->SetLineStyle(1);
  legJetPtRank->SetLineWidth(1);
  legJetPtRank->SetFillColor(0);
  legJetPtRank->SetFillStyle(1001);
     
//  legJetPtRank->AddEntry(hjet1PtRankGGH,"GGH", "l");
//  legJetPtRank->AddEntry(hjet1PtRankWH,"WH", "l");
//  legJetPtRank->AddEntry(hjet1PtRankZH,"ZH", "l");
//  legJetPtRank->AddEntry(hjet1PtRankTTH,"TTH", "l");
//  legJetPtRank->AddEntry(hjet1PtRankHH,"HH", "f");
     
//  legJetPtRank->Draw();
  
  cJetPtRank->cd(2);
  hjet2PtRankHH->Draw();
//  hjet2PtRankZH->Draw("same");
//  hjet2PtRankTTH->Draw("same");
//  hjet2PtRankWH->Draw("same");
//  hjet2PtRankGGH->Draw("same");
//  legJetPtRank->Draw();

  cJetPtRank->cd(3);
  hjet3PtRankHH->Draw();
//  hjet3PtRankZH->Draw("same");
//  hjet3PtRankTTH->Draw("same");
//  hjet3PtRankWH->Draw("same");
//  hjet3PtRankGGH->Draw("same");
//  legJetPtRank->Draw();

  cJetPtRank->cd(4);
  hjet4PtRankHH->Draw();
//  hjet4PtRankZH->Draw("same");
//  hjet4PtRankTTH->Draw("same");
//  hjet4PtRankWH->Draw("same");
//  hjet4PtRankGGH->Draw("same");
//  legJetPtRank->Draw();


  TCanvas* cJetcsvRank = new TCanvas("cJetcsvRank","Jets Csv Rank",100,100,800,800);
  cJetcsvRank->Divide(2,2);
  cJetcsvRank->cd(1);
  hjet1csvRankHH->Draw();
  cJetcsvRank->cd(2);
  hjet2csvRankHH->Draw();
  cJetcsvRank->cd(3);
  hjet3csvRankHH->Draw();
  cJetcsvRank->cd(4);
  hjet4csvRankHH->Draw();

/*
  TH2F* hSignificance=new TH2F("Significance","Significance",
			 3,//Number of bins
			 0,//Lower X Boundary
			 3,
			 3,
			 0,
			 3);//Upper X Boundary
  hSignificance->Fill(0,0,5.13);
  hSignificance->Fill(0,1,5.91);
  hSignificance->Fill(0,2,5.75);
  hSignificance->Fill(1,1,5.73);
  hSignificance->Fill(1,2,5.68);
  hSignificance->Fill(2,2,3.86);


  TCanvas* cSignificance = new TCanvas("cSignificance","Significance",100,100,800,800);
  hSignificance->Draw("COLORZ,TEXT");
*/  

}
