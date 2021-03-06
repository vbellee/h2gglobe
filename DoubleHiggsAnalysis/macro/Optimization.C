//Read histograms_diH_studiesBtagging and draw a histogram

#include "TNtuple.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <algorithm>



void Optimization(){
  
  //Open a file, save the ntuple and close the file
  TFile *in_file = TFile::Open("histograms_diH_studiesBtagging7.root");
  
 
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

  TTree* my_tupleData = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/data",
  						      "TTree");

  //Open a file, save the ntuple and close the file
  TFile *in_file2 = TFile::Open("histograms_diH_studiesBtagging6.root");

  TTree* my_tupleTTH = (TTree*) in_file2->GetObjectChecked("doubleHiggsAnalysis/tth_m125_8TeV",
  						      "TTree");

  //Prints only the number of entries
  gStyle->SetOptStat("");

  //Fix the csv Cut (0.244, 0.679, 0.898)
  float csvCut ;
  csvCut = 0;

  //Smallest Cut
  float csvCut1 ;
  csvCut1 = 0.244;
  //Biggest Cut
  float csvCut2 ;
  csvCut2 = 0.244;

//Create the 2D histogram of the optimization
  TH2F* hOptimization=new TH2F("Significance per window considered","Significance per window considered",
			 5,//Number of bins
			 100,//Lower X Boundary
			 120,
			 5,
			 130,
			 150);//Upper X Boundary



  //Create the Histograms
  //Have to set the appropriate boundaries
  
  TH1F* hbkg=new TH1F("Bkg","Di-jet Mass Bkg;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hbkg->SetFillColor(kYellow);

  TH1F* hmj1j2HH=new TH1F("mj1mj2GGHH","Di-jet Reconstructed MassGGHH;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2HH->SetFillColor(kViolet);

  TH1F* hmj1j2ZH=new TH1F("mj1mj2ZH","Di-jetZH Mass;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2ZH->SetFillColor(kGreen);

  TH1F* hmj1j2ZHBMatched=new TH1F("mj1mj2ZHBMatched","Di-jetZH BMatched Mass;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2ZHBMatched->SetFillColor(kGreen+3);

  TH1F* hmj1j2WH=new TH1F("mj1mj2WH","Di-jetWH Mass;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2WH->SetFillColor(kRed);

  TH1F* hmj1j2GGH=new TH1F("mj1mj2GGH","Di-jet MassGGH;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2GGH->SetFillColor(kBlue-6);

  TH1F* hmj1j2GGHCuts=new TH1F("mj1mj2GGHCuts","Di-jet MassGGH;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2GGHCuts->SetFillColor(kBlue-6);

  TH1F* hmj1j2TTH=new TH1F("mj1mj2TTH","Di-jet MassTTH;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2TTH->SetFillColor(kOrange); 
 
  TH1F* hmj1j2data=new TH1F("mj1mj2data","Di-jet Mass Data;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2data->SetFillColor(kPink-6); 

  TH1F* hmj1j2dataCuts=new TH1F("mj1mj2dataCuts","Di-jet Mass Data;Mass;",
			 75,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2dataCuts->SetFillColor(kPink-6); 

 
  TLorentzVector * jet1p4,* jet2p4,* jet3p4;

  float pho1pt, pho2pt, pho1Eta, pho2Eta, pho1Phi, pho2Phi, diphoM, diphoEta, diphopt,jet1Eta,jet2Eta, dijetEta, jet1Pt, jet2Pt,jet1genPt, jet2genPt, mj1j2, numJet1Matched, numJet2Matched, numDijetMatched, csvBtag1, csvBtag2, csvBtag3, csvMvaBtag1, csvMvaBtag2, csvMvaBtag3, jetProbBtag1, jetProbBtag2, jetProbBtag3, tcheBtag1, tcheBtag2, tcheBtag3, weight;

  bool jet1isMatched, jet2isMatched, jet1isBMatched, jet2isBMatched;

  int jet3, nJets, pho1CiC,pho2CiC;

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
  my_tuple->SetBranchAddress("pho1CiC",&pho1CiC);
  my_tuple->SetBranchAddress("pho2CiC",&pho2CiC);

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
  my_tupleZH->SetBranchAddress("pho1CiC",&pho1CiC);
  my_tupleZH->SetBranchAddress("pho2CiC",&pho2CiC);

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
  my_tupleWH->SetBranchAddress("pho1CiC",&pho1CiC);
  my_tupleWH->SetBranchAddress("pho2CiC",&pho2CiC);

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
  my_tupleGGH->SetBranchAddress("pho1CiC",&pho1CiC);
  my_tupleGGH->SetBranchAddress("pho2CiC",&pho2CiC);

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
  my_tupleTTH->SetBranchAddress("pho1CiC",&pho1CiC);
  my_tupleTTH->SetBranchAddress("pho2CiC",&pho2CiC);

  my_tupleData->SetBranchAddress("pho1pt",&pho1pt);
  my_tupleData->SetBranchAddress("pho2pt",&pho2pt);
  my_tupleData->SetBranchAddress("pho1Eta",&pho1Eta);
  my_tupleData->SetBranchAddress("pho2Eta",&pho2Eta);
  my_tupleData->SetBranchAddress("pho1Phi",&pho1Phi);
  my_tupleData->SetBranchAddress("pho2Phi",&pho2Phi);
  my_tupleData->SetBranchAddress("diphoM",&diphoM);
  my_tupleData->SetBranchAddress("diphoEta",&diphoEta);
  my_tupleData->SetBranchAddress("diphopt",&diphopt);
  my_tupleData->SetBranchAddress("dijetEta",&dijetEta);
  my_tupleData->SetBranchAddress("jet1Pt",&jet1Pt);
  my_tupleData->SetBranchAddress("jet2Pt",&jet2Pt);
  my_tupleData->SetBranchAddress("jet1p4",&jet1p4);
  my_tupleData->SetBranchAddress("jet2p4",&jet2p4);
  my_tupleData->SetBranchAddress("jet3p4",&jet3p4);
  my_tupleData->SetBranchAddress("jet1genPt",&jet1genPt);
  my_tupleData->SetBranchAddress("jet2genPt",&jet2genPt);
  my_tupleData->SetBranchAddress("jet1Eta",&jet1Eta);
  my_tupleData->SetBranchAddress("jet2Eta",&jet2Eta);
  my_tupleData->SetBranchAddress("mj1j2",&mj1j2);
  my_tupleData->SetBranchAddress("jet3",&jet3);
  my_tupleData->SetBranchAddress("jet1isMatched",&jet1isMatched);
  my_tupleData->SetBranchAddress("jet2isMatched",&jet2isMatched);
  my_tupleData->SetBranchAddress("csvBtag1",&csvBtag1); 
  my_tupleData->SetBranchAddress("csvBtag2",&csvBtag2); 
  my_tupleData->SetBranchAddress("csvBtag3",&csvBtag3);  
  my_tupleData->SetBranchAddress("csvMvaBtag1",&csvMvaBtag1); 
  my_tupleData->SetBranchAddress("csvMvaBtag2",&csvMvaBtag2); 
  my_tupleData->SetBranchAddress("csvMvaBtag3",&csvMvaBtag3); 
  my_tupleData->SetBranchAddress("jetProbBtag1",&jetProbBtag1); 
  my_tupleData->SetBranchAddress("jetProbBtag2",&jetProbBtag2); 
  my_tupleData->SetBranchAddress("jetProbBtag3",&jetProbBtag3); 
  my_tupleData->SetBranchAddress("tcheBtag1",&tcheBtag1); 
  my_tupleData->SetBranchAddress("tcheBtag2",&tcheBtag2); 
  my_tupleData->SetBranchAddress("tcheBtag3",&tcheBtag3);
  my_tupleData->SetBranchAddress("weight",&weight);
  my_tupleData->SetBranchAddress("nJets",&nJets);
  my_tupleData->SetBranchAddress("pho1CiC",&pho1CiC);
  my_tupleData->SetBranchAddress("pho2CiC",&pho2CiC);
  
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
	pho1CiC>= 4 &&
	pho2CiC>= 4 &&
//	(jet3) < 0 &&
	(nJets) <= 3 &&
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
	hmj1j2ZH->Fill(jetSumrecop4.M(),weight);
     
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
	pho1CiC>= 4 &&
	pho2CiC>= 4 &&
//	(jet3) < 0 &&
	(nJets) <= 3 &&
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
	pho1CiC>= 4 &&
	pho2CiC>= 4 &&
//	(jet3) < 0 &&
	(nJets) <= 3 &&
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
	pho1CiC>= 4 &&
	pho2CiC>= 4 &&
//	(jet3) < 0 &&
	(nJets) <= 3 &&
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
	hmj1j2TTH->Fill(jetSumrecop4.M(),weight);
 
    }

  }


 for (int irow=0;irow<my_tupleData->GetEntries();++irow){
    my_tupleData->GetEntry(irow);
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

	if( (pho1CiC)<4 
	  || (pho2CiC)<4
	    || (diphoM>123 && diphoM<127)
		) continue;

    if ((pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
//	(jet3) < 0 &&
	(nJets) <= 3 &&
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
      { hmj1j2dataCuts->Fill(jetSumrecop4.M(),0.0602);

//Remplissage des histogrammes
	float csvMin;
	csvMin = min(csvBtag1,csvBtag2);
	float csvMax;
	csvMax = max(csvBtag1,csvBtag2);
	if( (csvMin)<=csvCut1 
	  || (csvMax)<= csvCut2 
		) continue;
	hmj1j2data->Fill(jetSumrecop4.M(),0.0602);
 
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
	(pho1pt/diphoM) > (1/2) &&
	(pho2pt/diphoM) > (25/120)&&
	pho1CiC>= 4 &&
	pho2CiC>= 4 &&
//	(jet3) < 0 &&
	(nJets) <= 3 &&
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
	hmj1j2HH->Fill(jetSumrecop4.M(),weight);
    }

  }

  

  //Draw Histograms

/*
  TCanvas* cMassJet = new TCanvas("cMassJet","Mass",100,100,800,800);
  cMassJet->Divide(2,2);
  cMassJet->cd(1);
  hmj1j2GGH->Draw();
  cMassJet->cd(2);
  hmj1j2HH->Draw();
  cMassJet->cd(3);
  THStack *hs = new THStack("hs","three plots");

//Rescale GGH
   float NormalisationConst ;
   NormalisationConst = (hmj1j2GGH->GetEntries())/(hmj1j2GGHCuts->GetEntries());
   hmj1j2GGHCuts->Scale(NormalisationConst);

   hs->Add(hmj1j2GGHCuts);
   hs->Add(hmj1j2WH);
   hs->Add(hmj1j2ZH);
   hs->Add(hmj1j2HH);
   hs->Draw();
  cMassJet->cd(4);
  hmj1j2ZH->Draw();
  hmj1j2ZHBMatched->Draw("same");


  TCanvas* cMassVerifJet = new TCanvas("cMassVerifJet","Mass",100,100,800,800);  
*/
//Filling Bkg histogramm

//Rescale GGH
   float NormalisationConst ;
   NormalisationConst = (hmj1j2GGH->GetEntries())/(hmj1j2GGHCuts->GetEntries());
   hmj1j2GGHCuts->Scale(NormalisationConst);

//Rescale Data
   float NormalisationConstData ;
   NormalisationConstData = (hmj1j2data->GetEntries())/(hmj1j2dataCuts->GetEntries());
   hmj1j2dataCuts->Scale(NormalisationConstData);

  hbkg->Add(hmj1j2ZH);
  hbkg->Add(hmj1j2GGHCuts);
  hbkg->Add(hmj1j2WH);
  hbkg->Add(hmj1j2TTH);
  // hbkg->Add(hmj1j2dataCuts);
  //hbkg->Draw();


  for (int ix=0;ix<6;++ix) {

	  for (int iy=0;iy<6;++iy) {

  int bin1 = hbkg->FindBin(96+4*ix);
  int bin2 = hbkg->FindBin(126+4*iy);
  float NumBkg = hbkg->Integral(bin1,bin2);
  float NumEvts = hmj1j2HH->Integral(bin1,bin2);
  float Significance = NumEvts/sqrt(NumBkg);
  float Num = hbkg->Integral();
  float NumZH = hmj1j2ZH->Integral();
  float NumZHWindow = hmj1j2ZH->Integral(bin1,bin2);
  float NumZHBMatched = hmj1j2ZHBMatched->Integral();
  float NumZHBMatchedWindow = hmj1j2ZHBMatched->Integral(bin1,bin2);

  hOptimization->Fill(96+4*ix,126+4*iy,Significance);

	  }
  }

/*
  cout <<"Number of background events between 105 and 130 GeV : "<<NumBkg<<"\n"<<
    "Number of HH events between 105 and 130GeV : "<<NumEvts<<"\n"<<
    "Number  events between 0 and 300GeV : "<<Num<<"\n"<<
    "Number of ZH events between 0 and 300GeV : "<<NumZH<<"\n"<<
    "Number of BMatched ZH events between 0 and 300GeV : "<<NumZHBMatched<<"\n"<<
    "Number of ZH events between 105 and 130GeV : "<<NumZHWindow<<"\n"<<
    "Number of BMatched ZH events between 105 and 130GeV : "<<NumZHBMatchedWindow<<"\n"<<
    "Smallest B Tag : "<<csvCut1<<"\n"<<
    "Biggest B Tag : "<<csvCut2<<"\n"<<
    "Significance : "<<Significance<<endl;

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
*/

  TCanvas* cOptimization = new TCanvas("cOptimization","Significance",100,100,800,800);
  hOptimization->Draw("COLORZ,TEXT");
  
  TCanvas* cMassJet = new TCanvas("cMassJet","Mass",100,100,800,800);
//  cMassJet->Divide(2,2);
//  cMassJet->cd(1);
//  hmj1j2GGH->Draw();
//  cMassJet->cd(2);
//  hmj1j2TTH->Draw();
//  cMassJet->cd(3);
  THStack *hs = new THStack("hs","three plots");
   hs->Add(hmj1j2GGHCuts);
   hs->Add(hmj1j2WH);
   hs->Add(hmj1j2ZH);
   //hs->Add(hmj1j2VBF);
   hs->Add(hmj1j2HH);
   hs->Add(hmj1j2TTH);
   hs->Add(hmj1j2dataCuts);
   hs->Draw();

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
  leg->AddEntry(hmj1j2HH,"HH", "f");
  leg->AddEntry(hmj1j2dataCuts,"QCD", "f");

  leg->Draw();
//  cMassJet->cd(4);
//  hmj1j2ZH->Draw();
//  hmj1j2ZHBMatched->Draw("same");

}
