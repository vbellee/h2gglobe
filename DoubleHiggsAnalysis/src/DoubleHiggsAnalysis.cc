#include "../interface/DoubleHiggsAnalysis.h"

#include "../../JetAnalysis/interface/JetHandler.h"

#include "Sorters.h"
#include "PhotonReducedInfo.h"
#include <iostream>
#include <algorithm>

#include "CMGTools/External/interface/PileupJetIdentifier.h"

#define PADEBUG 0 

using namespace std;

// ----------------------------------------------------------------------------------------------------
DoubleHiggsTreeVariables::DoubleHiggsTreeVariables() : 
    entry(0),		
    weight(0),		
    sampleweight(0),		
    pho1pt(0),		
    pho2pt(0),		
    diphopt(0),		
    diphoM(0),		
    diphoEta(999),	
    dijetEta(999),
    jet1p4(new TLorentzVector(0,0,0,0)),
    jet2p4(new TLorentzVector(0,0,0,0)),
    jet3p4(new TLorentzVector(0,0,0,0)),
    jet4p4(new TLorentzVector(0,0,0,0)),
    jet1isMatched(false),	
    jet2isMatched(false),
    jet3isMatched(false),	
    jet4isMatched(false),	
    jet1isBMatched(false),	
    jet2isBMatched(false),	
    jet3isBMatched(false),	
    jet4isBMatched(false),	
    jet1genPt(0),	
    jet2genPt(0),	
    jet3genPt(0),	
    jet4genPt(0),	
    jet1genDr(0),	
    jet2genDr(0),	
    jet3genDr(0),	
    jet4genDr(0),	
    jet1Pt(0),		
    jet2Pt(0),	
    jet1PtRank(-1),		
    jet2PtRank(-1),
    jet3PtRank(-1),		
    jet4PtRank(-1),		
    jet1Eta(999),		
    jet2Eta(999),		
    zepp(999),		
    mj1j2(-999),		
    dphi(999),		
    dphiJJ(999),		
    dphiJJ2(999),		
    deltaEta3(999),	
    jet1PileupID(0),	
    jet2PileupID(0),	
    isSignal(false),	
    mctype(0),		
    diphomva(-999),	
    pho1Eta(999),		
    pho2Eta(999),		
    pho1Phi(999),		
    pho2Phi(999),		
    pho1scEta(999),		
    pho2scEta(999),		
    pho1r9(999),		
    pho2r9(999),		
    pho1idMva(-999),	
    pho2idMva(-999),	
    pho1sE(999),	
    pho2sE(999),	
    pho1sEsmear(999),	
    pho2sEsmear(999),	
    diphosM(999),	
    diphosMwv(999),	
    diphovtxProb(-1),
    nJets(0),
    jet1(-1),
    jet2(-1),
    jet3(-1),
    jet4(-1),
    pho1Matched(false), pho2Matched(false),corrVeretx(false),
    pho1CiC(-1),pho2CiC(-1), diphoMVA(-999.),
    csvBtag1(-999),
    csvBtag2(-999),
    csvBtag3(-999),
    csvMvaBtag1(-999),
    csvMvaBtag2(-999),
    csvMvaBtag3(-999),
    jetProbBtag1(-999),
    jetProbBtag2(-999),
    jetProbBtag3(-999),
    tcheBtag1(-999),
    tcheBtag2(-999),
    tcheBtag3(-999)



{}

// ----------------------------------------------------------------------------------------------------
DoubleHiggsAnalysis::DoubleHiggsAnalysis()  
{
    name_ = "DoubleHiggsAnalysis";

    recomputeJetId = false;
    expoMatching   = false;
    dumpFlatTree   = false;
    requireTwoJets = true;
    
    flatTree_ = 0;
    outputFile_ = 0;
    
    bookDoubleHiggs = true;
}

// ----------------------------------------------------------------------------------------------------
DoubleHiggsAnalysis::~DoubleHiggsAnalysis() 
{
}

// ----------------------------------------------------------------------------------------------------
void DoubleHiggsAnalysis::Term(LoopAll& l) 
{
    if( dumpFlatTree ) {
	//// if( outputFile_ ) {
	////     outputFile_->cd();
	//// } else {
	////     l.outputFile->cd();
	//// }
	//// flatTree_->Write();
	//// if( outputFile_ ) {
	////     outputFile_->Close();
	//// }
    }
}

// ----------------------------------------------------------------------------------------------------
void DoubleHiggsAnalysis::Init(LoopAll& l) 
{  
    if( l.runZeeValidation ) {
	leadEtCut = 15;
	subleadEtCut = 15;
	leadEtVBFCut = 15.;
	subleadEtVBFCut = 15.;
	massMin = 60, massMax = 120.;
	applyPtoverM = false;
    }
    

    MassFactorizedMvaAnalysis::Init(l);
    if( jetHandler_ == 0 ) {
    	jetHandler_ = new JetHandler(jetHandlerCfg, l);
    }

    if( dumpFlatTree ) {
	if( flatTree_ == 0 ) { 
	    //// outputFile_ = TFile::Open("doubleHiggsAnalysisTree_"+l.histFileName,"recreate");
	    //// flatTree_ = new TTree("flatTree","flatTree");
	    l.InitTrees("doubleHiggsAnalysis");
	    tree_.entry = 0;
	}
	
	//// tree_.jet3p4 = 0; tree_.jet2p4 = 0; tree_.jet1p4 = 0;
	delete default_.jet1p4; delete default_.jet2p4; delete default_.jet3p4;
	default_.jet1p4 = tree_.jet1p4; default_.jet2p4 = tree_.jet2p4;  default_.jet3p4 = tree_.jet3p4;
	l.BookExternalTreeBranch( "entry",         &tree_.entry, "doubleHiggsAnalysis" );         
	l.BookExternalTreeBranch( "weight",        &tree_.weight, "doubleHiggsAnalysis" );         
	l.BookExternalTreeBranch( "sampleweight",  &tree_.sampleweight, "doubleHiggsAnalysis" );         
	l.BookExternalTreeBranch( "pho1pt",        &tree_.pho1pt, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "pho2pt",        &tree_.pho2pt, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "diphopt",       &tree_.diphopt, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "diphoM",        &tree_.diphoM, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "diphoEta",      &tree_.diphoEta, "doubleHiggsAnalysis" );      
	l.BookExternalTreeBranch( "dijetEta",      &tree_.dijetEta, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch("jet4p4",&(tree_.jet4p4),32000,0, "doubleHiggsAnalysis");     
	l.BookExternalTreeBranch("jet3p4",&(tree_.jet3p4),32000,0, "doubleHiggsAnalysis");
	l.BookExternalTreeBranch("jet2p4",&(tree_.jet2p4),32000,0, "doubleHiggsAnalysis");
	l.BookExternalTreeBranch("jet1p4",&(tree_.jet1p4),32000,0, "doubleHiggsAnalysis");
	l.BookExternalTreeBranch( "nJets",          &tree_.nJets, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet1",          &tree_.jet1, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet2",          &tree_.jet2, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet3",          &tree_.jet3, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet4",          &tree_.jet4, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet1isMatched", &tree_.jet1isMatched, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet2isMatched", &tree_.jet2isMatched, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "jet3isMatched", &tree_.jet3isMatched, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet4isMatched", &tree_.jet4isMatched, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "jet1isBMatched", &tree_.jet1isBMatched, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet2isBMatched", &tree_.jet2isBMatched, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet3isBMatched", &tree_.jet3isBMatched, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet4isBMatched", &tree_.jet4isBMatched, "doubleHiggsAnalysis" ); 
	l.BookExternalTreeBranch( "jet1genPt",     &tree_.jet1genPt, "doubleHiggsAnalysis" );     
	l.BookExternalTreeBranch( "jet2genPt",     &tree_.jet2genPt, "doubleHiggsAnalysis" );    
	l.BookExternalTreeBranch( "jet3genPt",     &tree_.jet3genPt, "doubleHiggsAnalysis" );     
	l.BookExternalTreeBranch( "jet4genPt",     &tree_.jet4genPt, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "jet1genDr",     &tree_.jet1genDr, "doubleHiggsAnalysis" );     
	l.BookExternalTreeBranch( "jet2genDr",     &tree_.jet2genDr, "doubleHiggsAnalysis" );     
	l.BookExternalTreeBranch( "jet3genDr",     &tree_.jet3genDr, "doubleHiggsAnalysis" );     
	l.BookExternalTreeBranch( "jet4genDr",     &tree_.jet4genDr, "doubleHiggsAnalysis" );   
	l.BookExternalTreeBranch( "jet1Pt",        &tree_.jet1Pt, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "jet2Pt",        &tree_.jet2Pt, "doubleHiggsAnalysis" );    
	l.BookExternalTreeBranch( "jet1PtRank",        &tree_.jet1PtRank, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "jet2PtRank",        &tree_.jet2PtRank, "doubleHiggsAnalysis" );   
	l.BookExternalTreeBranch( "jet3PtRank",        &tree_.jet3PtRank, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "jet4PtRank",        &tree_.jet4PtRank, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "jet1Eta",       &tree_.jet1Eta, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "jet2Eta",       &tree_.jet2Eta, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "zepp",          &tree_.zepp, "doubleHiggsAnalysis" );          
	l.BookExternalTreeBranch( "mj1j2",         &tree_.mj1j2, "doubleHiggsAnalysis" );         
	l.BookExternalTreeBranch( "dphi",          &tree_.dphi, "doubleHiggsAnalysis" );          
	l.BookExternalTreeBranch( "dphiJJ",        &tree_.dphiJJ, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "dphiJJ2",       &tree_.dphiJJ2, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "deltaEta3",     &tree_.deltaEta3, "doubleHiggsAnalysis" );     
	l.BookExternalTreeBranch( "jet1PileupID",  &tree_.jet1PileupID, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "jet2PileupID",  &tree_.jet2PileupID, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "isSignal",      &tree_.isSignal, "doubleHiggsAnalysis" );      
	l.BookExternalTreeBranch( "mctype",        &tree_.mctype, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "diphomva",      &tree_.diphomva, "doubleHiggsAnalysis" );      
	l.BookExternalTreeBranch( "pho1energy",       &tree_.pho1energy, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho2energy",       &tree_.pho2energy, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho1Eta",       &tree_.pho1Eta, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho2Eta",       &tree_.pho2Eta, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho1Phi",       &tree_.pho1Phi, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho2Phi",       &tree_.pho2Phi, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho1scEta",       &tree_.pho1scEta, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho2scEta",       &tree_.pho2scEta, "doubleHiggsAnalysis" );       
	l.BookExternalTreeBranch( "pho1r9",        &tree_.pho1r9, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "pho2r9",        &tree_.pho2r9, "doubleHiggsAnalysis" );        
	l.BookExternalTreeBranch( "pho1idMva",     &tree_.pho1idMva, "doubleHiggsAnalysis" );    
	l.BookExternalTreeBranch( "pho2idMva",     &tree_.pho2idMva, "doubleHiggsAnalysis" );    
	l.BookExternalTreeBranch( "pho1sE",   &tree_.pho1sE, "doubleHiggsAnalysis" );   
	l.BookExternalTreeBranch( "pho2sE",   &tree_.pho2sE, "doubleHiggsAnalysis" );   
	l.BookExternalTreeBranch( "pho1sEsmear",   &tree_.pho1sEsmear, "doubleHiggsAnalysis" );   
	l.BookExternalTreeBranch( "pho2sEsmear",   &tree_.pho2sEsmear, "doubleHiggsAnalysis" );   
	l.BookExternalTreeBranch( "diphosM",  &tree_.diphosM, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "diphosMwv",&tree_.diphosMwv, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "diphovtxProb",  &tree_.diphovtxProb, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "pho1Matched",  &tree_.pho1Matched, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "pho2Matched",  &tree_.pho2Matched, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "corrVeretx",  &tree_.corrVeretx, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "pho1CiC",  &tree_.pho1CiC, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "pho2CiC",  &tree_.pho2CiC, "doubleHiggsAnalysis" );  
	l.BookExternalTreeBranch( "diphoMVA",  &tree_.diphoMVA, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "csvBtag1",  &tree_.csvBtag1, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "csvBtag2",  &tree_.csvBtag2, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "csvBtag3",  &tree_.csvBtag3, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "csvBtag4",  &tree_.csvBtag4, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "csvMvaBtag1",  &tree_.csvMvaBtag1, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "csvMvaBtag2",  &tree_.csvMvaBtag2, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "csvMvaBtag3",  &tree_.csvMvaBtag3, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "jetProbBtag1",  &tree_.jetProbBtag1, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "jetProbBtag2",  &tree_.jetProbBtag2, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "jetProbBtag3",  &tree_.jetProbBtag3, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "tcheBtag1",  &tree_.tcheBtag1, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "tcheBtag2",  &tree_.tcheBtag2, "doubleHiggsAnalysis" );
	l.BookExternalTreeBranch( "tcheBtag3",  &tree_.tcheBtag3, "doubleHiggsAnalysis" );
  
   }
}

// ----------------------------------------------------------------------------------------------------
void DoubleHiggsAnalysis::ReducedOutputTree(LoopAll &l, TTree * outputTree) 
{
    /// dumpFlatTree=true;
    /// flatTree_ = new TTree("flatTree","flatTree");
}

// ----------------------------------------------------------------------------------------------------
void DoubleHiggsAnalysis::FillReductionVariables(LoopAll& l, int jentry)
{
}
   
// ----------------------------------------------------------------------------------------------------
bool DoubleHiggsAnalysis::SelectEventsReduction(LoopAll&, int)
{
    return true;
}

//void switchJetIdVertex(LoopAll &l, int ivtx) ;

// ----------------------------------------------------------------------------------------------------
bool DoubleHiggsAnalysis::AnalyseEvent(LoopAll& l, Int_t jentry, float weight, TLorentzVector & gP4, float & mass, float & evweight, 
				 int & category, int & diphoton_id,
				 bool & isCorrectVertex,
				 float &kinematic_bdtout,
				 bool isSyst, 
				 float syst_shift, bool skipSelection,
				 BaseGenLevelSmearer *genSys, BaseSmearer *phoSys, BaseDiPhotonSmearer * diPhoSys)
{
    assert( isSyst || ! skipSelection );
    
    int cur_type = l.itype[l.current];
    /// diphoton_id = -1;
    
    std::pair<int,int> diphoton_index;
   
    // do gen-level dependent first (e.g. k-factor); only for signal
    genLevWeight=1.;
    if(cur_type!=0 ) {
	applyGenLevelSmearings(genLevWeight,gP4,l.pu_n,cur_type,genSys,syst_shift);
    }

    // event selection
    if( ! skipSelection ) {
	
	// first apply corrections and smearing on the single photons 
	smeared_pho_energy.clear(); smeared_pho_energy.resize(l.pho_n,0.); 
	smeared_pho_r9.clear();     smeared_pho_r9.resize(l.pho_n,0.); 
	smeared_pho_weight.clear(); smeared_pho_weight.resize(l.pho_n,1.);
	applySinglePhotonSmearings(smeared_pho_energy, smeared_pho_r9, smeared_pho_weight, cur_type, l, energyCorrected, energyCorrectedError,
				   phoSys, syst_shift);

	// inclusive category di-photon selection
	// FIXME pass smeared R9
	diphoton_id = l.DiphotonMITPreSelection(leadEtCut,subleadEtCut,phoidMvaCut,applyPtoverM, &smeared_pho_energy[0] ); ///??? serve ???
    	
	// Exclusive Modes
	int diphotonVBF_id = -1;
	int diphotonVHhad_id = -1;
	int diphotonVHlep_id = -1;
	VHmuevent = false;
	VHelevent = false;
	VBFevent = false;
	VHhadevent = false;
	
	//// // preselection 
	//// diphotonVBF_id = l.DiphotonMITPreSelection(leadEtVBFCut,subleadEtVBFCut,phoidMvaCut,applyPtoverM, &smeared_pho_energy[0] );
	//// diphoton_id = diphotonVBF_id; 
	
	if( diphoton_id == -1 ) { return false; }
	
	/// l.RescaleJetEnergy();
	/// postProcessJets(l,l.dipho_vtxind[diphoton_id]);
		
	TLorentzVector lead_p4, sublead_p4, Higgs;
	float lead_r9, sublead_r9;
	TVector3 * vtx;
	category = 0;
	fillDiphoton(lead_p4, sublead_p4, Higgs, lead_r9, sublead_r9, vtx, &smeared_pho_energy[0], l, diphoton_id);  
	if( Higgs.M() < massMin || Higgs.M() > massMax )  { return false; }
	
	
	// ---- evaluate dipho MVA
	diphoton_index = std::make_pair( l.dipho_leadind[diphoton_id],  l.dipho_subleadind[diphoton_id] );
	evweight = weight * smeared_pho_weight[diphoton_index.first] * smeared_pho_weight[diphoton_index.second] * genLevWeight;
	
        // Mass Resolution of the Event
        massResolutionCalculator->Setup(l,&photonInfoCollection[diphoton_index.first],&photonInfoCollection[diphoton_index.second],diphoton_id,eSmearPars,nR9Categories,nEtaCategories,beamspotSigma);
        float vtx_mva  = l.vtx_std_evt_mva->at(diphoton_id);
        sigmaMrv = massResolutionCalculator->massResolutionEonly();
        sigmaMwv = massResolutionCalculator->massResolutionWrongVtx();
        float sigmaMeonly = massResolutionCalculator->massResolutionEonly();
        // easy to calculate vertex probability from vtx mva output
        float vtxProb   = 1.-0.49*(vtx_mva+1.0); 

        float phoid_mvaout_lead = ( dataIs2011 ? 
				    l.photonIDMVA(diphoton_index.first,l.dipho_vtxind[diphoton_id],
						  lead_p4,bdtTrainingPhilosophy.c_str()) :
				    l.photonIDMVANew(diphoton_index.first,l.dipho_vtxind[diphoton_id],
						     lead_p4,bdtTrainingPhilosophy.c_str()) );
        float phoid_mvaout_sublead = ( dataIs2011 ? 
				       l.photonIDMVA(diphoton_index.second,l.dipho_vtxind[diphoton_id],
						     sublead_p4,bdtTrainingPhilosophy.c_str()) : 
				       l.photonIDMVANew(diphoton_index.second,l.dipho_vtxind[diphoton_id],
							sublead_p4,bdtTrainingPhilosophy.c_str()) );
	// apply di-photon level smearings and corrections
        int selectioncategory = l.DiphotonCategory(diphoton_index.first,diphoton_index.second,Higgs.Pt(),nEtaCategories,nR9Categories,0);
        if( cur_type != 0 && doMCSmearing ) {
	    applyDiPhotonSmearings(Higgs, *vtx, selectioncategory, cur_type, *((TVector3*)l.gv_pos->At(0)), evweight, 
				   phoid_mvaout_lead,phoid_mvaout_sublead,
				   diPhoSys, syst_shift);
            isCorrectVertex=(*vtx- *((TVector3*)l.gv_pos->At(0))).Mag() < 1.;
        }

	float diphobdt_output = l.diphotonMVA(diphoton_index.first,diphoton_index.second,l.dipho_vtxind[diphoton_id] ,
					      vtxProb,lead_p4,sublead_p4,sigmaMrv,sigmaMwv,sigmaMeonly,
					      bdtTrainingPhilosophy.c_str(),
					      phoid_mvaout_lead,phoid_mvaout_sublead);
	
		
	// clean and sort jets by csv but also save the pt sorting
	std::vector<int> sorted_jets, pt_sorted_jets;
	for(int ijet=0; ijet<l.jet_algoPF1_n; ++ijet) { 
	    TLorentzVector * p4 = (TLorentzVector*)l.jet_algoPF1_p4->At(ijet);
	    if( p4->Pt() < 30 || fabs(p4->Eta()) > 2.4 ) { continue; }
	    if( p4->DeltaR(lead_p4) > 0.5 && p4->DeltaR(sublead_p4) > 0.5 && p4->Pt() > 20. ) {
		sorted_jets.push_back(ijet);
		pt_sorted_jets.push_back(ijet);
	    }
	}
	std::sort(sorted_jets.begin(),sorted_jets.end(),
		  SimpleSorter<float,std::greater<float> >(l.jet_algoPF1_csvBtag) );
	std::sort(pt_sorted_jets.begin(),pt_sorted_jets.end(),
		  ClonesSorter<TLorentzVector,double,std::greater<double> >(l.jet_algoPF1_p4,&TLorentzVector::Pt)); 
	
	//// switchJetIdVertex( l, l.dipho_vtxind[diphoton_id] );
	
	/// select fourhighestcsv jets passing loose PU jet Id
	int ijet1 = -1, rank1 =-1;
	int ijet2 = -1, rank2 =-1;
	int ijet3 = -1, rank3 =-1;
	int ijet4 = -1, rank4 =-1;
	for(size_t itjet=0; itjet<sorted_jets.size(); ++itjet ) {
	    int ijet = sorted_jets[itjet];
	    jetHandler_->computeWp(ijet,l.dipho_vtxind[diphoton_id]);
	    int puwp = (*l.jet_algoPF1_cutbased_wp_level_ext)[ijet][l.dipho_vtxind[diphoton_id]];
	    bool PUjetId = PileupJetIdentifier::passJetId(puwp, PileupJetIdentifier::kLoose);

	    int rank = std::find(pt_sorted_jets.begin(),pt_sorted_jets.end(),ijet)-pt_sorted_jets.begin();
	    if ( PUjetId && ijet1<0 ) {ijet1 = ijet;      rank1 =rank;}
	    else if ( PUjetId && ijet2<0 ) {ijet2 = ijet; rank2 =rank;}
            else if ( PUjetId && ijet3<0 ) {ijet3 = ijet; rank3 =rank;}
	    else if ( PUjetId && ijet4<0 ) {ijet4 = ijet; rank4 =rank;}
	    else if ( ijet4>= 0 ) { break; }
	}
	
	if(ijet1>=0) { *(tree_.jet1p4) = *(TLorentzVector*)l.jet_algoPF1_p4->At(ijet1); }
	if(ijet2>=0) { *(tree_.jet2p4) = *(TLorentzVector*)l.jet_algoPF1_p4->At(ijet2); }
	if(ijet3>=0) { *(tree_.jet3p4) = *(TLorentzVector*)l.jet_algoPF1_p4->At(ijet3); }
	if(ijet4>=0) { *(tree_.jet4p4) = *(TLorentzVector*)l.jet_algoPF1_p4->At(ijet4); }
	
	TLorentzVector sumj1;
	TLorentzVector sumj2;
	TLorentzVector dijet;
	
	TLorentzVector diphoton = lead_p4+sublead_p4;
	
	TLorentzVector & jet1( *(tree_.jet1p4)  );
	TLorentzVector & jet2( *(tree_.jet2p4)  );
	TLorentzVector & jet3( *(tree_.jet3p4)  );
	TLorentzVector & jet4( *(tree_.jet4p4)  );
	
	if( ijet1 >= 0 && ijet2 >= 0) {

	    dijet = jet1 + jet2;
	    //--- compute dphiJJ2 [http://arxiv.org/pdf/1001.3822.pdf]
	    sumj1.SetPxPyPzE(0.,0.,0.,0.);
	    sumj2.SetPxPyPzE(0.,0.,0.,0.);
	    for(size_t itjet=0; itjet<sorted_jets.size(); ++itjet ) {
		int ijet = sorted_jets[itjet];
		bool PUjetId = PileupJetIdentifier::passJetId(l.jet_algoPF1_simple_wp_level[ijet], PileupJetIdentifier::kLoose);
		if (PUjetId==false) continue;
		TLorentzVector* jet = (TLorentzVector*)l.jet_algoPF1_p4->At(ijet);
		if ( jet->Eta() < diphoton.Eta() ) sumj1 = sumj1 + (*jet);
		if ( jet->Eta() > diphoton.Eta() ) sumj2 = sumj1 + (*jet);
	    }
	} else if( requireTwoJets ) {
	    return false;
	}

	// now dump variables in a flat tree
	if( dumpFlatTree ) {
	    tree_ = default_;
	    
	    tree_.entry         = l.event;
	    tree_.weight        = evweight;
	    tree_.sampleweight  = l.weight;
	    tree_.pho1pt        = lead_p4.Pt();
	    tree_.pho2pt        = sublead_p4.Pt();
	    tree_.diphopt       = diphoton.Pt();
	    tree_.diphoM        = diphoton.M();
	    tree_.diphoEta      = diphoton.Eta();
	    tree_.diphomva      = diphobdt_output;
	    
	    tree_.nJets = sorted_jets.size();
	    
	    tree_.jet1 = ijet1;
	    tree_.jet2 = ijet2;
	    tree_.jet3 = ijet3;
	    tree_.jet4 = ijet4;
	    
	    if( ijet1 >= 0 ) {
		tree_.jet1isMatched = l.jet_algoPF1_genMatched[ijet1];
		tree_.jet1isBMatched = l.jet_algoPF1_bgenMatched[ijet1];
		tree_.jet1genPt     = l.jet_algoPF1_genPt[ijet1];
		tree_.jet1genDr     = l.jet_algoPF1_genDr[ijet1];
		tree_.jet1PileupID  = PileupJetIdentifier::passJetId(l.jet_algoPF1_simple_wp_level[ijet1], PileupJetIdentifier::kLoose);
		tree_.jet1Pt        = jet1.Pt();
		tree_.jet1Eta       = jet1.Eta();

		//Entries added 08/07/2013
		tree_.csvBtag1 = l.jet_algoPF1_csvBtag[ijet1];
		tree_.csvMvaBtag1 = l.jet_algoPF1_csvMvaBtag[ijet1];
		tree_.jetProbBtag1 = l.jet_algoPF1_jetProbBtag[ijet1];
		tree_.tcheBtag1 = l.jet_algoPF1_tcheBtag[ijet1];
		tree_.jet1PtRank =rank1;
	    }
	    if( ijet2 >= 0 ) {
		tree_.jet2isMatched = l.jet_algoPF1_genMatched[ijet2];
		tree_.jet2isBMatched = l.jet_algoPF1_bgenMatched[ijet2];
		tree_.jet2genPt     = l.jet_algoPF1_genPt[ijet2];
		tree_.jet2genDr     = l.jet_algoPF1_genDr[ijet2];
		tree_.jet2PileupID  = PileupJetIdentifier::passJetId(l.jet_algoPF1_simple_wp_level[ijet2], PileupJetIdentifier::kLoose);
		tree_.jet2Pt        = jet2.Pt();
		tree_.jet2Eta       = jet2.Eta();

		//Entries added 08/07/2013
		tree_.csvBtag2 = l.jet_algoPF1_csvBtag[ijet2];
		tree_.csvMvaBtag2 = l.jet_algoPF1_csvMvaBtag[ijet2];
		tree_.jetProbBtag2 = l.jet_algoPF1_jetProbBtag[ijet2];
		tree_.tcheBtag2 = l.jet_algoPF1_tcheBtag[ijet2];
		tree_.jet2PtRank =rank2;


	    }
	    
	    if( ijet1 >= 0 && ijet2 >= 0 ) {
		tree_.zepp          = fabs(diphoton.Eta() - 0.5*(jet1.Eta() + jet2.Eta())); 
		tree_.mj1j2         = dijet.M();
		tree_.dphi          = fabs(diphoton.DeltaPhi(dijet));
		tree_.dijetEta      = dijet.Eta();
		tree_.dphiJJ        = fabs(jet1.DeltaPhi(jet2));
		tree_.dphiJJ2       = fabs(sumj1.DeltaPhi(sumj2));
	    }


	    //Entries added 08/07/2013
	    if( ijet3 >= 0 ) {
		tree_.jet3isMatched = l.jet_algoPF1_genMatched[ijet3];
		tree_.jet3isBMatched = l.jet_algoPF1_bgenMatched[ijet3];
		tree_.jet3genPt     = l.jet_algoPF1_genPt[ijet3];
		tree_.jet3genDr     = l.jet_algoPF1_genDr[ijet3];
		tree_.csvBtag3 = l.jet_algoPF1_csvBtag[ijet3];
		tree_.csvMvaBtag3 = l.jet_algoPF1_csvMvaBtag[ijet3];
		tree_.jetProbBtag3 = l.jet_algoPF1_jetProbBtag[ijet3];
		tree_.tcheBtag3 = l.jet_algoPF1_tcheBtag[ijet3];
		tree_.jet3PtRank =rank3;
	    }

	    if( ijet4 >= 0 ) {
		tree_.jet4isMatched = l.jet_algoPF1_genMatched[ijet4];
		tree_.jet4isBMatched = l.jet_algoPF1_bgenMatched[ijet4];
		tree_.jet4genPt     = l.jet_algoPF1_genPt[ijet4];
		tree_.jet4genDr     = l.jet_algoPF1_genDr[ijet4];
		tree_.csvBtag4 = l.jet_algoPF1_csvBtag[ijet4];
		tree_.jet4PtRank =rank4;
	    }	    


	    
	    tree_.pho1energy      = lead_p4.E();
	    tree_.pho2energy      = sublead_p4.E();
	    tree_.pho1Eta         = lead_p4.Eta();
	    tree_.pho2Eta         = sublead_p4.Eta();
	    tree_.pho1Phi         = lead_p4.Phi();
	    tree_.pho2Phi         = sublead_p4.Phi();
	    tree_.pho1scEta         = (float)((TVector3*)l.sc_xyz->At(l.pho_scind[diphoton_index.first]))->Eta();
	    tree_.pho2scEta         = (float)((TVector3*)l.sc_xyz->At(l.pho_scind[diphoton_index.second]))->Eta();
	    tree_.pho1r9          = lead_r9;
	    tree_.pho2r9          = sublead_r9;
	    tree_.pho1idMva       = phoid_mvaout_lead;
	    tree_.pho2idMva       = phoid_mvaout_sublead;
	    tree_.pho1sE     = massResolutionCalculator->leadPhotonResolutionNoSmear();
	    tree_.pho2sE     = massResolutionCalculator->subleadPhotonResolutionNoSmear();
	    tree_.pho1sEsmear= massResolutionCalculator->leadPhotonResolution();   
	    tree_.pho2sEsmear= massResolutionCalculator->subleadPhotonResolution();
	    tree_.diphosM         = sigmaMrv;
	    tree_.diphosMwv       = sigmaMwv;
	    tree_.diphovtxProb    = vtxProb;
	    tree_.pho1Matched         = l.pho_genmatched[diphoton_index.first];
	    tree_.pho2Matched         = l.pho_genmatched[diphoton_index.second];
	    std::vector<std::vector<bool> > ph_passcut;
	    tree_.pho1CiC             = l.PhotonCiCSelectionLevel(diphoton_index.first,  l.dipho_vtxind[diphoton_id], ph_passcut, 4, 0, &smeared_pho_energy[0] );
	    tree_.pho2CiC             = l.PhotonCiCSelectionLevel(diphoton_index.second, l.dipho_vtxind[diphoton_id], ph_passcut, 4, 0, &smeared_pho_energy[0] );

	    if (ijet3 > 0 ) {
		tree_.deltaEta3 = fabs(jet3.Eta() - 0.5*(jet1.Eta() + jet2.Eta())); 
	    }
	    tree_.isSignal  = (cur_type < 0);
	    tree_.mctype    = cur_type;
	    tree_.diphoMVA  = diphobdt_output;
	    tree_.corrVeretx = isCorrectVertex;

	    l.FillTreeContainer();

	    fillControlPlots(lead_p4, sublead_p4, Higgs, lead_r9, sublead_r9, diphoton_id,
			     category, isCorrectVertex, evweight, vtx, l, 0, -1, 0, -1 );
	}
	return false;
    }
    
    return false;
}

// Local Variables:
// mode: c++
// c-basic-offset: 4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
