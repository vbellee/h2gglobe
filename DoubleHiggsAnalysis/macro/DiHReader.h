//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul  1 11:23:19 2013 by ROOT version 5.32/00
// from TTree wzh_m125_8TeV/wzh_m125_8TeV
// found on file: /afs/cern.ch/work/m/musella/public/hgg/double_h/histograms_diH_studies.root
//////////////////////////////////////////////////////////

#ifndef DiHReader_h
#define DiHReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class DiHReader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           entry;
   Float_t         weight;
   Float_t         sampleweight;
   Float_t         pho1pt;
   Float_t         pho2pt;
   Float_t         diphopt;
   Float_t         diphoM;
   Float_t         diphoEta;
   Float_t         dijetEta;
   TLorentzVector  *jet3p4;
   TLorentzVector  *jet2p4;
   TLorentzVector  *jet1p4;
   Int_t           jet1;
   Int_t           jet2;
   Int_t           jet3;
   Float_t         jet1isMatched;
   Float_t         jet2isMatched;
   Float_t         jet1genPt;
   Float_t         jet2genPt;
   Float_t         jet1genDr;
   Float_t         jet2genDr;
   Float_t         jet1Pt;
   Float_t         jet2Pt;
   Float_t         jet1Eta;
   Float_t         jet2Eta;
   Float_t         zepp;
   Float_t         mj1j2;
   Float_t         dphi;
   Float_t         dphiJJ;
   Float_t         dphiJJ2;
   Float_t         deltaEta3;
   Bool_t          jet1PileupID;
   Bool_t          jet2PileupID;
   Bool_t          isSignal;
   Int_t           mctype;
   Float_t         diphomva;
   Float_t         pho1energy;
   Float_t         pho2energy;
   Float_t         pho1Eta;
   Float_t         pho2Eta;
   Float_t         pho1Phi;
   Float_t         pho2Phi;
   Float_t         pho1scEta;
   Float_t         pho2scEta;
   Float_t         pho1r9;
   Float_t         pho2r9;
   Float_t         pho1idMva;
   Float_t         pho2idMva;
   Float_t         pho1sE;
   Float_t         pho2sE;
   Float_t         pho1sEsmear;
   Float_t         pho2sEsmear;
   Float_t         diphosM;
   Float_t         diphosMwv;
   Float_t         diphovtxProb;
   Bool_t          pho1Matched;
   Bool_t          pho2Matched;
   Bool_t          corrVeretx;
   Int_t           pho1CiC;
   Int_t           pho2CiC;
   Float_t         diphoMVA;

   // List of branches
   TBranch        *b_entry;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_sampleweight;   //!
   TBranch        *b_pho1pt;   //!
   TBranch        *b_pho2pt;   //!
   TBranch        *b_diphopt;   //!
   TBranch        *b_diphoM;   //!
   TBranch        *b_diphoEta;   //!
   TBranch        *b_dijetEta;   //!
   TBranch        *b_jet3p4;   //!
   TBranch        *b_jet2p4;   //!
   TBranch        *b_jet1p4;   //!
   TBranch        *b_jet1;   //!
   TBranch        *b_jet2;   //!
   TBranch        *b_jet3;   //!
   TBranch        *b_jet1isMatched;   //!
   TBranch        *b_jet2isMatched;   //!
   TBranch        *b_jet1genPt;   //!
   TBranch        *b_jet2genPt;   //!
   TBranch        *b_jet1genDr;   //!
   TBranch        *b_jet2genDr;   //!
   TBranch        *b_jet1Pt;   //!
   TBranch        *b_jet2Pt;   //!
   TBranch        *b_jet1Eta;   //!
   TBranch        *b_jet2Eta;   //!
   TBranch        *b_zepp;   //!
   TBranch        *b_mj1j2;   //!
   TBranch        *b_dphi;   //!
   TBranch        *b_dphiJJ;   //!
   TBranch        *b_dphiJJ2;   //!
   TBranch        *b_deltaEta3;   //!
   TBranch        *b_jet1PileupID;   //!
   TBranch        *b_jet2PileupID;   //!
   TBranch        *b_isSignal;   //!
   TBranch        *b_mctype;   //!
   TBranch        *b_diphomva;   //!
   TBranch        *b_pho1energy;   //!
   TBranch        *b_pho2energy;   //!
   TBranch        *b_pho1Eta;   //!
   TBranch        *b_pho2Eta;   //!
   TBranch        *b_pho1Phi;   //!
   TBranch        *b_pho2Phi;   //!
   TBranch        *b_pho1scEta;   //!
   TBranch        *b_pho2scEta;   //!
   TBranch        *b_pho1r9;   //!
   TBranch        *b_pho2r9;   //!
   TBranch        *b_pho1idMva;   //!
   TBranch        *b_pho2idMva;   //!
   TBranch        *b_pho1sE;   //!
   TBranch        *b_pho2sE;   //!
   TBranch        *b_pho1sEsmear;   //!
   TBranch        *b_pho2sEsmear;   //!
   TBranch        *b_diphosM;   //!
   TBranch        *b_diphosMwv;   //!
   TBranch        *b_diphovtxProb;   //!
   TBranch        *b_pho1Matched;   //!
   TBranch        *b_pho2Matched;   //!
   TBranch        *b_corrVeretx;   //!
   TBranch        *b_pho1CiC;   //!
   TBranch        *b_pho2CiC;   //!
   TBranch        *b_diphoMVA;   //!

   DiHReader(TTree *tree=0);
   virtual ~DiHReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DiHReader_cxx
DiHReader::DiHReader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/m/musella/public/hgg/double_h/histograms_diH_studies.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/afs/cern.ch/work/m/musella/public/hgg/double_h/histograms_diH_studies.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/afs/cern.ch/work/m/musella/public/hgg/double_h/histograms_diH_studies.root:/doubleHiggsAnalysis");
      dir->GetObject("wzh_m125_8TeV",tree);

   }
   Init(tree);
}

DiHReader::~DiHReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DiHReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DiHReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void DiHReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet3p4 = 0;
   jet2p4 = 0;
   jet1p4 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("entry", &entry, &b_entry);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("sampleweight", &sampleweight, &b_sampleweight);
   fChain->SetBranchAddress("pho1pt", &pho1pt, &b_pho1pt);
   fChain->SetBranchAddress("pho2pt", &pho2pt, &b_pho2pt);
   fChain->SetBranchAddress("diphopt", &diphopt, &b_diphopt);
   fChain->SetBranchAddress("diphoM", &diphoM, &b_diphoM);
   fChain->SetBranchAddress("diphoEta", &diphoEta, &b_diphoEta);
   fChain->SetBranchAddress("dijetEta", &dijetEta, &b_dijetEta);
   fChain->SetBranchAddress("jet3p4", &jet3p4, &b_jet3p4);
   fChain->SetBranchAddress("jet2p4", &jet2p4, &b_jet2p4);
   fChain->SetBranchAddress("jet1p4", &jet1p4, &b_jet1p4);
   fChain->SetBranchAddress("jet1", &jet1, &b_jet1);
   fChain->SetBranchAddress("jet2", &jet2, &b_jet2);
   fChain->SetBranchAddress("jet3", &jet3, &b_jet3);
   fChain->SetBranchAddress("jet1isMatched", &jet1isMatched, &b_jet1isMatched);
   fChain->SetBranchAddress("jet2isMatched", &jet2isMatched, &b_jet2isMatched);
   fChain->SetBranchAddress("jet1genPt", &jet1genPt, &b_jet1genPt);
   fChain->SetBranchAddress("jet2genPt", &jet2genPt, &b_jet2genPt);
   fChain->SetBranchAddress("jet1genDr", &jet1genDr, &b_jet1genDr);
   fChain->SetBranchAddress("jet2genDr", &jet2genDr, &b_jet2genDr);
   fChain->SetBranchAddress("jet1Pt", &jet1Pt, &b_jet1Pt);
   fChain->SetBranchAddress("jet2Pt", &jet2Pt, &b_jet2Pt);
   fChain->SetBranchAddress("jet1Eta", &jet1Eta, &b_jet1Eta);
   fChain->SetBranchAddress("jet2Eta", &jet2Eta, &b_jet2Eta);
   fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
   fChain->SetBranchAddress("mj1j2", &mj1j2, &b_mj1j2);
   fChain->SetBranchAddress("dphi", &dphi, &b_dphi);
   fChain->SetBranchAddress("dphiJJ", &dphiJJ, &b_dphiJJ);
   fChain->SetBranchAddress("dphiJJ2", &dphiJJ2, &b_dphiJJ2);
   fChain->SetBranchAddress("deltaEta3", &deltaEta3, &b_deltaEta3);
   fChain->SetBranchAddress("jet1PileupID", &jet1PileupID, &b_jet1PileupID);
   fChain->SetBranchAddress("jet2PileupID", &jet2PileupID, &b_jet2PileupID);
   fChain->SetBranchAddress("isSignal", &isSignal, &b_isSignal);
   fChain->SetBranchAddress("mctype", &mctype, &b_mctype);
   fChain->SetBranchAddress("diphomva", &diphomva, &b_diphomva);
   fChain->SetBranchAddress("pho1energy", &pho1energy, &b_pho1energy);
   fChain->SetBranchAddress("pho2energy", &pho2energy, &b_pho2energy);
   fChain->SetBranchAddress("pho1Eta", &pho1Eta, &b_pho1Eta);
   fChain->SetBranchAddress("pho2Eta", &pho2Eta, &b_pho2Eta);
   fChain->SetBranchAddress("pho1Phi", &pho1Phi, &b_pho1Phi);
   fChain->SetBranchAddress("pho2Phi", &pho2Phi, &b_pho2Phi);
   fChain->SetBranchAddress("pho1scEta", &pho1scEta, &b_pho1scEta);
   fChain->SetBranchAddress("pho2scEta", &pho2scEta, &b_pho2scEta);
   fChain->SetBranchAddress("pho1r9", &pho1r9, &b_pho1r9);
   fChain->SetBranchAddress("pho2r9", &pho2r9, &b_pho2r9);
   fChain->SetBranchAddress("pho1idMva", &pho1idMva, &b_pho1idMva);
   fChain->SetBranchAddress("pho2idMva", &pho2idMva, &b_pho2idMva);
   fChain->SetBranchAddress("pho1sE", &pho1sE, &b_pho1sE);
   fChain->SetBranchAddress("pho2sE", &pho2sE, &b_pho2sE);
   fChain->SetBranchAddress("pho1sEsmear", &pho1sEsmear, &b_pho1sEsmear);
   fChain->SetBranchAddress("pho2sEsmear", &pho2sEsmear, &b_pho2sEsmear);
   fChain->SetBranchAddress("diphosM", &diphosM, &b_diphosM);
   fChain->SetBranchAddress("diphosMwv", &diphosMwv, &b_diphosMwv);
   fChain->SetBranchAddress("diphovtxProb", &diphovtxProb, &b_diphovtxProb);
   fChain->SetBranchAddress("pho1Matched", &pho1Matched, &b_pho1Matched);
   fChain->SetBranchAddress("pho2Matched", &pho2Matched, &b_pho2Matched);
   fChain->SetBranchAddress("corrVeretx", &corrVeretx, &b_corrVeretx);
   fChain->SetBranchAddress("pho1CiC", &pho1CiC, &b_pho1CiC);
   fChain->SetBranchAddress("pho2CiC", &pho2CiC, &b_pho2CiC);
   fChain->SetBranchAddress("diphoMVA", &diphoMVA, &b_diphoMVA);
   Notify();
}

Bool_t DiHReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DiHReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DiHReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DiHReader_cxx
