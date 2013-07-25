//Read histograms_diH_studiesBtagging and draw a histogram

#include "TNtuple.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <algorithm>



void DiHAnalysis(){
  
  //Open a file, save the ntuple and close the file
  TFile *in_file = TFile::Open("histograms_diH_studiesBtagging2.root");
  
 
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

  //Prints only the number of entries
  gStyle->SetOptStat("");

  //Fix the csv Cut (0.244, 0.679, 0.898)
  float csvCut ;
  csvCut = 0;

  //Smallest Cut
  float csvCut1 ;
  csvCut1 = 0.0;
  //Biggest Cut
  float csvCut2 ;
  csvCut2 = 0.244;


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
			 500);//Upper X Boundary
  hjetPt->SetLineColor(kGreen-6);

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
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hbkg->SetFillColor(kYellow);

  TH1F* hmj1j2=new TH1F("mj1mj2GGHH","Di-jet MassGGHH;Mass;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2->SetLineColor(kGreen-6);

  TH1F* hmj1j2reco=new TH1F("mj1mj2GGHH","Di-jet Reconstructed MassGGHH;Mass;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2reco->SetLineColor(kRed-6);

  TH1F* hmj1j2ZH=new TH1F("mj1mj2ZH","Di-jetZH Mass;Mass;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2ZH->SetFillColor(kGreen);

  TH1F* hmj1j2WH=new TH1F("mj1mj2WH","Di-jetWH Mass;Mass;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2WH->SetFillColor(kRed);

  TH1F* hmj1j2GGH=new TH1F("mj1mj2GGH","Di-jet MassGGH;Mass;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2GGH->SetFillColor(kBlue-6);

  TH1F* hmj1j2GGHCuts=new TH1F("mj1mj2GGHCuts","Di-jet MassGGH;Mass;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2GGHCuts->SetFillColor(kBlue-6);

  TH1F* hmj1j2VBF=new TH1F("mj1mj2VBF","Di-jet MassVBF;Mass;",
			 50,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2VBF->SetFillColor(kBlue);

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

  //Create the fit functions to be modified with the Breit Wigner function
  //gdiphoM = new TF1("gdiphoM","2*sqrt(2)*[0]*[1]*sqrt([0]*[0]*([0]*[0]+[1]*[1]))/(3.1415*sqrt([0]*[0]+sqrt([0]*[0]*([0]*[0]+[1]*[1]))))/((x*x-[0]*[0])*(x*x-[0]*[0])+[0]*[0]*[1]*[1])",90,160);
  //gdiphoM->SetParameters(125,11.7);
  //gmj1j2 = new TF1("gmj1j2","2*sqrt(2)*[0]*[1]*sqrt([0]*[0]*([0]*[0]+[1]*[1]))/(3.1415*sqrt([0]*[0]+sqrt([0]*[0]*([0]*[0]+[1]*[1]))))/((x*x-[0]*[0])*(x*x-[0]*[0])+[0]*[0]*[1]*[1])",50,110);
  gdiphoM = new TF1("gdiphoM","gaus",120,130);
  gmj1j2 = new TF1("gmj1j2","gaus",100,140);
  gjet1recogenPt = new TF1 ("gjet1recogenPt","gaus",-20,20);
  gjet2recogenPt = new TF1 ("gjet2recogenPt","gaus",-20,20);
 
  TLorentzVector * jet1p4,* jet2p4,* jet3p4;

  float pho1pt, pho2pt, pho1Eta, pho2Eta, diphoM, diphoEta, diphopt,jet1Eta,jet2Eta, dijetEta, jet1Pt, jet2Pt,jet1genPt, jet2genPt, mj1j2, numJet1Matched, numJet2Matched, numDijetMatched, csvBtag1, csvBtag2, csvBtag3, csvMvaBtag1, csvMvaBtag2, csvMvaBtag3, jetProbBtag1, jetProbBtag2, jetProbBtag3, tcheBtag1, tcheBtag2, tcheBtag3, weight;

  bool jet1isMatched, jet2isMatched;

  int jet3;

  numJet1Matched = 0;
  numJet2Matched = 0;
  numDijetMatched = 0;
  

  //We select the loaves to be read
  my_tuple->SetBranchAddress("pho1pt",&pho1pt);
  my_tuple->SetBranchAddress("pho2pt",&pho2pt);
  my_tuple->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tuple->SetBranchAddress("pho2Eta",&pho2Eta);
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

  my_tupleZH->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleZH->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleZH->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleZH->SetBranchAddress("pho2Eta",&pho2Eta);
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

  my_tupleWH->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleWH->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleWH->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleWH->SetBranchAddress("pho2Eta",&pho2Eta);
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

  my_tupleGGH->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleGGH->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleGGH->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleGGH->SetBranchAddress("pho2Eta",&pho2Eta);
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

  my_tupleVBF->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleVBF->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleVBF->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleVBF->SetBranchAddress("pho2Eta",&pho2Eta);
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
	(jet3) < 0 &&
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
	(jet3) < 0 &&
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
      { //Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2WH->Fill(jetSumrecop4.M(),weight);

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
	(jet3) < 0 &&
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
      { hmj1j2GGHCuts->Fill(jetSumrecop4.M(),weight);

        //Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2GGH->Fill(jetSumrecop4.M(),weight);

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
	(jet3) < 0 &&
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
	(jet3) < 0 &&
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



      { //Remplissage des histogrammes
	hpho1pt->Fill(pho1pt);
	hpho2pt->Fill(pho2pt);
	hdiphopt->Fill(diphopt);
	hpho1Eta->Fill(pho1Eta);
	hpho2Eta->Fill(pho2Eta);
	hdiphoEta->Fill(diphoEta);
	hdiphoM->Fill(diphoM);
	hdijetpt->Fill(jet1Pt+jet2Pt);
	hjet1Pt->Fill(jet1Pt);
	hjet2Pt->Fill(jet2Pt);
	hjet1recoPt->Fill(jet1recoPt);
	hjet2recoPt->Fill(jet2recoPt);
	hjetPt->Fill(jet1Pt);
	hjetPt->Fill(jet2Pt);	

	if ((csvBtag1)>csvCut)
	{	hjet1PtBtag->Fill(jet1Pt);
		hdivisionbis1->Fill(jet1Pt);
	}


	if ((csvBtag2)>csvCut)
	{	hjet2PtBtag->Fill(jet2Pt);
		hdivisionbis2->Fill(jet2Pt);
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
  cComparePt->Divide(2,2);
  cComparePt->cd(1);
  hdiphopt->Draw();
  hdiphoZHpt->Draw("same");
  //cComparePt->cd(2);
  //hjetZHPt->Scale(NormalisationK);
  //hjetZHPt->Draw();
  //hjetPt->Draw("same");
  cComparePt->cd(3);
  hpho1ZHpt->Scale(NormalisationK);
  hpho1ZHpt->Draw();
  hpho1pt->Draw("same");
  cComparePt->cd(4);
  hpho2ZHpt->Scale(NormalisationK);
  hpho2pt->Draw();
  hpho2ZHpt->Draw("same");

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

  TCanvas* cPtJet = new TCanvas("cPtJet","DiJet Pt before and after Btagging",100,100,1200,800);
  cPtJet->Divide(3,2);
  cPtJet->cd(1);
  hjet1recoPt->Draw();
  hjet1Pt->Draw("same");
  cPtJet->cd(2); 
  hjet1PtBtag->Draw();
  cPtJet->cd(3);
  hdivisionbis1->Divide(hjet1Pt);
  hdivisionbis1->Draw();
  cPtJet->cd(4);
  hjet2Pt->Draw();
  hjet2recoPt->Draw("same");
  cPtJet->cd(5); 
  hjet2PtBtag->Draw();
  cPtJet->cd(6);
  hdivisionbis2->Divide(hjet2Pt);
  hdivisionbis2->Draw();

  TCanvas* cMassJet = new TCanvas("cMassJet","Mass",100,100,800,800);
  cMassJet->Divide(2,2);
  cMassJet->cd(1);
  hmj1j2GGH->Draw();
  cMassJet->cd(2);
  hmj1j2->Draw();
  hmj1j2reco->Draw("same");
  cMassJet->cd(3);
  THStack *hs = new THStack("hs","three plots");

//Rescale GGH
   float NormalisationConst ;
   NormalisationConst = (hmj1j2GGH->GetEntries())/(hmj1j2GGHCuts->GetEntries());
   hmj1j2GGHCuts->Scale(NormalisationConst);

   hs->Add(hmj1j2GGHCuts);
   hs->Add(hmj1j2WH);
   hs->Add(hmj1j2ZH);
   //hs->Add(hmj1j2VBF);
   hs->Add(hmj1j2reco);
   hs->Draw();
  cMassJet->cd(4);
  hmj1j2ZH->Draw();

  TCanvas* cMassVerifJet = new TCanvas("cMassVerifJet","Mass",100,100,800,800);  
//Filling Bkg histogramm
  hbkg->Add(hmj1j2ZH);
  hbkg->Add(hmj1j2GGHCuts);
  hbkg->Add(hmj1j2WH);
  hbkg->Draw();
  int bin1 = hbkg->TH1::FindBin(105);
  int bin2 = hbkg->TH1::FindBin(130);
  float NumBkg = hbkg->TH1::Integral(bin1,bin2);
  float NumEvts = hmj1j2reco->TH1::Integral(bin1,bin2);
  float Significance = NumEvts/sqrt(NumBkg);
  float Num = hbkg->TH1::Integral();

  cout <<"Number of background events between 105 and 130 GeV : "<<NumBkg<<"\n"<<
    "Number of HH events between 105 and 130GeV : "<<NumEvts<<"\n"<<
    "Number  events between 105 and 130GeV : "<<Num<<"\n"<<
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

  TH2F* hSignificance=new TH2F("Significance","Significance",
			 3,//Number of bins
			 0,//Lower X Boundary
			 3,
			 3,
			 0,
			 3);//Upper X Boundary
  hSignificance->Fill(0,0,0.0403);
  hSignificance->Fill(0,1,0.0443);
  hSignificance->Fill(0,2,0.043);
  hSignificance->Fill(1,1,0.0392);
  hSignificance->Fill(1,2,0.038);
  hSignificance->Fill(2,2,0.0278);


  TCanvas* cSignificance = new TCanvas("cSignificance","Significance",100,100,800,800);
  hSignificance->Draw("COLORZ,TEXT");
  

}
