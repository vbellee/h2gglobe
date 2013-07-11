//Read histograms_diH_studiesBtagging and draw a histogram

#include "TNtuple.h"
#include "TFile.h"
#include "TLorentzVector.h"

void DiHAnalysis(){
  
  //Open a file, save the ntuple and close the file
  TFile *in_file = TFile::Open("histograms_diH_studiesBtagging.root");
  
 
  TTree* my_tuple = (TTree*) in_file->GetObjectChecked("doubleHiggsAnalysis/wzh_m125_8TeV",
  						      "TTree");
 

  //Prints only the number of entries
  gStyle->SetOptStat("");

  //Create the Histograms
  //Have to set the appropriate boundaries
  TH1F* hdiphopt=new TH1F("diphopt","Di-photon Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 700);//Upper X Boundary
  hdiphopt->SetFillColor(kBlue-6);

  TH1F* hpho1pt=new TH1F("pho1pt","Photon 1 Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hpho1pt->SetFillColor(kBlue-6);

  TH1F* hpho2pt=new TH1F("pho2pt","Photon 2 Momentum;Photon Momentum;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hpho2pt->SetFillColor(kBlue-6);

  TH1F* hdijetpt=new TH1F("dijetpt","Di-jet Momentum;Pt;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hdijetpt->SetFillColor(kGreen-6);

  TH1F* hjet1Pt=new TH1F("jet1Pt","Jet 1 Momentum;Pt;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet1Pt->SetFillColor(kGreen-6);

  TH1F* hjet2Pt=new TH1F("jet2Pt","Jet 2 Momentum;Pt;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 500);//Upper X Boundary
  hjet2Pt->SetFillColor(kGreen-6);

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

  TH1F* hmj1j2=new TH1F("mj1mj2","Di-jet Mass;Mass;",
			 100,//Number of bins
			 0,//Lower X Boundary
			 300);//Upper X Boundary
  hmj1j2->SetFillColor(kGreen-6);

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

  //Create the fit functions
  gdiphoM = new TF1("gdiphoM","gaus",120,130);
  gmj1j2 = new TF1("gmj1j2","gaus",50,110);
  gjet1recogenPt = new TF1 ("gjet1recogenPt","gaus",-20,20);
  gjet2recogenPt = new TF1 ("gjet2recogenPt","gaus",-20,20);
 
 

  float pho1pt, pho2pt, pho1Eta, pho2Eta, diphoM, diphoEta, diphopt,jet1Eta,jet2Eta, dijetEta, jet1Pt, jet2Pt,jet1genPt, jet2genPt, mj1j2,jet1isMatched, jet2isMatched, numJet1Matched, numJet2Matched, numDijetMatched, csvBtag1, csvBtag2, csvBtag3, csvMvaBtag1, csvMvaBtag2, csvMvaBtag3;

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
  

  //Fill Histograms
  for (int irow=0;irow<my_tuple->GetEntries();++irow){
    my_tuple->GetEntry(irow);
    if (
	//Cuts
	//(mj1j2) > 130 &&
	(jet3) <0 &&
	(jet1isMatched)==1 &&
	(jet2isMatched)==1 &&
	(csvBtag1)>0.679 &&
	(csvBtag2)>0.679 &&
	//(csvBtag3)>0.898 &&
	//(csvMvaBtag1)>0.244 &&
	//(csvMvaBtag2)>0.679 &&
	//(jet1Pt-jet1genPt)>(20)&&
	//(jet1Pt-jet1genPt)<0 &&
	//(jet2Pt-jet2genPt)>(20)&&
	//(jet2Pt-jet2genPt)<0 &&
	(pho1pt/diphoM) > (1/3) &&
	(pho2pt/diphoM) > (25/120)&&
	(pho1Eta) < 5 &&
	(pho1Eta) > -5 &&
	(pho2Eta) < 5 &&
	(pho2Eta) > -5 &&
	(jet1Pt) > 30 &&
	//(jet1Pt) < 150 &&
	(jet2Pt) > 20 &&
	//(jet2Pt) < 100 &&
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

	hjet1Pt->Fill(jet1Pt);
	hjet2Pt->Fill(jet2Pt);
	hjet1recogenPt->Fill(jet1Pt-jet1genPt);
	hjet2recogenPt->Fill(jet2Pt-jet2genPt);	
	hdijetpt->Fill(jet1Pt+jet2Pt);
	hjet1Eta->Fill(jet1Eta);
	hjet2Eta->Fill(jet2Eta);
	hdijetEta->Fill(dijetEta);
	hmj1j2->Fill(mj1j2);
	hjet3->Fill(jet3);
	hcsvBtag1->Fill(csvBtag1);
	hcsvBtag2->Fill(csvBtag2);
	hcsvBtag3->Fill(csvBtag3);
	hcsvMvaBtag1->Fill(csvMvaBtag1);
	hcsvMvaBtag2->Fill(csvMvaBtag2);
	hcsvMvaBtag3->Fill(csvMvaBtag3);
	
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
  float NentriesTree, NentriesHisto, Percentage;
  NentriesTree = my_tuple-> GetEntries();
  NentriesHisto = hdiphopt-> GetEntries();
  Percentage = NentriesHisto/NentriesTree*100;
  cout <<"Number of events : "<<NentriesTree<<"\n"<<
    "Number of selected events : "<<NentriesHisto<<"\n"<<
    "Percentage of selected events : "<<Percentage<<"%"<<endl;

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
  hdiphoM->Fit("gdiphoM","R");
  

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


/*
  TCanvas* cRecoGen = new TCanvas("cRecoGen","Reconstructed Jet Pt - Generated Jet Pt",100,100,700,350);
  cRecoGen->Divide(2);
  cRecoGen->cd(1);
  hjet1recogenPt->Draw();
  hjet1recogenPt->Fit("gjet1recogenPt","R");
  cRecoGen->cd(2);
  hjet2recogenPt->Draw();
  hjet2recogenPt->Fit("gjet2recogenPt","R");
*/

  TCanvas* cMassJet3 = new TCanvas("cMassJet3","Mass and Jet3",100,100,700,350);
  cMassJet3->Divide(3);
  cMassJet3->cd(1);
  hmj1j2->Draw();
  cMassJet3->cd(2);
  hjet3->Draw();
  cMassJet3->cd(3);
  hcsvBtag1->Draw();

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

}
