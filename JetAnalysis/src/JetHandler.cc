#include "JetAnalysis/interface/JetHandler.h"
#include "LoopAll.h"

// ---------------------------------------------------------------------------------------------------------------
JetHandler::JetHandler(const std::string & cfg, LoopAll & l):
    l_(l)
{
    myPset = edm::readPSetsFrom(cfg);
    
    cutbased = new PileupJetIdAlgo(myPset->getParameter<edm::ParameterSet>("cutbased"));
    simple   = new PileupJetIdAlgo(myPset->getParameter<edm::ParameterSet>("simple"));
    full     = new PileupJetIdAlgo(myPset->getParameter<edm::ParameterSet>("full"));
    
    jecCorData_ = 0;
    jecCorMc_   = 0;
    jecUnc_     = 0;
    edm::ParameterSet jec = myPset->getParameter<edm::ParameterSet>("jec");
    std::vector<std::string> dataJEC = jec.getParameter<std::vector<std::string> >("data");
    std::vector<std::string> mcJEC   = jec.getParameter<std::vector<std::string> >("mc");
    std::string                unc   = jec.getParameter<std::string>("unc");
    
    for(std::vector<std::string>::iterator corr = dataJEC.begin(); corr!=dataJEC.end(); ++corr) {
	std::cout << "JetHandler JEC data " << *corr << std::endl;
    	jetCorParsData_.push_back( JetCorrectorParameters(*corr) );
    }
    for(std::vector<std::string>::iterator corr = mcJEC.begin(); corr!=mcJEC.end(); ++corr) {
	std::cout << "JetHandler JEC MC " << *corr << std::endl;
    	jetCorParsMc_.push_back( JetCorrectorParameters(*corr) );
    }
    
    if( ! jetCorParsData_.empty() ) {
	std::cout << "Booking JEC data " << std::endl;
    	jecCorData_ = new FactorizedJetCorrector(jetCorParsData_);
    }
    if( ! jetCorParsMc_.empty() ) {
	std::cout << "Booking JEC MC " << std::endl;
    	jecCorMc_ = new FactorizedJetCorrector(jetCorParsMc_);
    }
    if( ! unc.empty() ) { 
	std::cout << "Booking JEC uncertainties " << unc << std::endl;
	JetCorrectorParameters params (unc, "");
	jecUnc_ = new JetCorrectionUncertainty( params );
    }

    edm::ParameterSet jer = myPset->getParameter<edm::ParameterSet>("jer");
    jerEtaBins_  = jer.getParameter<std::vector<double> >("etaBins");
    jerResSf_    = jer.getParameter<std::vector<double> >("resSf");
    jerResSfErr_ = jer.getParameter<std::vector<double> >("resSfErr");


    jetResponseChange = new JetResponseChange("aux/JetResponseVsEta.root");
    nLumiBins_ = 0;

}

// ---------------------------------------------------------------------------------------------------------------
JetHandler::~JetHandler()
{
    delete cutbased;
    delete simple;
    delete full;
    
    if( jecCorData_ != 0 ) { delete jecCorData_; }
    if( jecCorMc_ != 0 )   { delete jecCorMc_;   }
    if( jecUnc_ != 0 )     { delete jecUnc_;   }
}

// ---------------------------------------------------------------------------------------------------------------
float dz(TLorentzVector * tkp4, TVector3 * tkpos, TVector3 * vtxpos)
{
    return fabs( (tkpos->Z()-vtxpos->Z()) - 
		 ( (tkpos->X()-vtxpos->X())*tkp4->Px() + (tkpos->Y()-vtxpos->Y())*tkp4->Py() )/tkp4->Pt() * tkp4->Pz()/tkp4->Pt() );
}

// ---------------------------------------------------------------------------------------------------------------
void JetHandler::computeBetas(int ijet, int vtx)
{
    float sumTkPt = 0.;
    if( (*l_.jet_algoPF1_beta_ext)[ijet].size() <= vtx ) {
	(*l_.jet_algoPF1_beta_ext)[ijet].resize(vtx+1);
	(*l_.jet_algoPF1_betaStar_ext)[ijet].resize(vtx+1);
	(*l_.jet_algoPF1_betaStarClassic_ext)[ijet].resize(vtx+1);
    }

    float & beta = (*l_.jet_algoPF1_beta_ext)[ijet][vtx];
    float & betaStar = (*l_.jet_algoPF1_betaStar_ext)[ijet][vtx];
    float & betaStarClassic = (*l_.jet_algoPF1_betaStarClassic_ext)[ijet][vtx];

    /// std::cout << "JetHandler::computeBetas before " << ijet << " " << vtx << " " << beta << " " << betaStar << " " << betaStarClassic << std::endl;
    beta = 0., betaStar = 0., betaStarClassic = 0.;

    const std::vector<unsigned short> & vtx_tracks = (*l_.vtx_std_tkind)[vtx];
    TVector3 * vtxpos = (TVector3*)l_.vtx_std_xyz->At(vtx);
    
    const std::vector<unsigned short> & jet_tracks = (*l_.jet_algoPF1_tkind)[ijet];
    for(std::vector<unsigned short>::const_iterator itrack=jet_tracks.begin(); itrack!=jet_tracks.end(); ++itrack ) {
	bool inVtx0 = find( vtx_tracks.begin(),  vtx_tracks.end(), *itrack ) != vtx_tracks.end();
	bool inAnyOther = false;
	
	TVector3 * tkpos= (TVector3 *) l_.tk_vtx_pos->At(*itrack);
	TLorentzVector * tkp4= (TLorentzVector *) l_.tk_p4->At(*itrack);
	float tkpt = tkp4->Pt();
	
	float dZ0 = dz(tkp4, tkpos, vtxpos);
	float dZ = dZ0;
	
	for(int ivtx=0; ivtx<l_.vtx_std_n; ++ivtx) {
	    bool isVtx0 = (ivtx == vtx);
	    if( ! isVtx0 && ! inAnyOther ) {
		const std::vector<unsigned short> & ivtx_tracks = (*l_.vtx_std_tkind)[ivtx];
		inAnyOther = find( ivtx_tracks.begin(),  ivtx_tracks.end(), *itrack ) != ivtx_tracks.end();
	    }
	    TVector3 * ivtxpos = (TVector3*)l_.vtx_std_xyz->At(ivtx);
	    dZ = std::min(dZ, dz(tkp4, tkpos, ivtxpos));
	}
	
	sumTkPt += tkpt;
	if( ! inVtx0 && inAnyOther ) {
	    betaStarClassic += tkpt; 
	}
	if( dZ0 < 0.2 ) {
	    beta += tkpt;
	} else if( dZ < 0.2 ) {
	    betaStar += tkpt;
	}
    }
    
    if( sumTkPt != 0. ) {
	beta     /= sumTkPt;
	betaStar /= sumTkPt;
	betaStarClassic /= sumTkPt;
    } else {
	assert( beta == 0. && betaStar == 0. && betaStarClassic == 0. );
    }

    /// std::cout << "JetHandler::computeBetas after "  << ijet << " " << vtx << " " << beta << " " << betaStar << " " << betaStarClassic << std::endl;
    
}

#define BOOK_BRANCH(TREE, VARIABLE) TREE -> Branch( # VARIABLE, \
						    full->getVariables().find(# VARIABLE)->second.first, # VARIABLE "/F" )

// ---------------------------------------------------------------------------------------------------------------
void JetHandler::bookFlatTree(TTree * tree)
{
    BOOK_BRANCH(tree, dRMean         );
    BOOK_BRANCH(tree, frac01         );
    BOOK_BRANCH(tree, frac02         );
    BOOK_BRANCH(tree, frac03         );
    BOOK_BRANCH(tree, frac04         );
    BOOK_BRANCH(tree, frac05         );
    BOOK_BRANCH(tree, frac06         );
    BOOK_BRANCH(tree, frac07         );
    BOOK_BRANCH(tree, nNeutrals      );
    BOOK_BRANCH(tree, beta           );
    BOOK_BRANCH(tree, betaStar       );
    BOOK_BRANCH(tree, dZ             );
    BOOK_BRANCH(tree, nCharged       );
    BOOK_BRANCH(tree, dR2Mean        );
    BOOK_BRANCH(tree, betaStarClassic);
    BOOK_BRANCH(tree, jetPt	     );
    BOOK_BRANCH(tree, jetEta	     );
    BOOK_BRANCH(tree, nvtx           );
}

// ---------------------------------------------------------------------------------------------------------------
void JetHandler::fillFromJet(int ijet, int ivtx)
{
    TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);
    
    internalId_.dRMean         (l_.jet_algoPF1_dRMean             [ijet]);
    internalId_.frac01         (l_.jet_algoPF1_frac01             [ijet]);
    internalId_.frac02         (l_.jet_algoPF1_frac02             [ijet]);
    internalId_.frac03         (l_.jet_algoPF1_frac03             [ijet]);
    internalId_.frac04         (l_.jet_algoPF1_frac04             [ijet]);
    internalId_.frac05         (l_.jet_algoPF1_frac05             [ijet]);
    internalId_.frac06         (l_.jet_algoPF1_frac06             [ijet]);
    internalId_.frac07         (l_.jet_algoPF1_frac07             [ijet]);
    internalId_.nNeutrals      (l_.jet_algoPF1_nNeutrals          [ijet]);
    internalId_.beta           ((*l_.jet_algoPF1_beta_ext)        [ijet][ivtx]);
    internalId_.betaStar       ((*l_.jet_algoPF1_betaStar_ext)    [ijet][ivtx]);
    internalId_.dZ             (l_.jet_algoPF1_dZ                 [ijet]);
    internalId_.nCharged       (l_.jet_algoPF1_nCharged           [ijet]);
    internalId_.dR2Mean        (l_.jet_algoPF1_dR2Mean            [ijet]);
    internalId_.betaStarClassic((*l_.jet_algoPF1_betaStarClassic_ext)[ijet][ivtx]);
    
    internalId_.jetPt(p4->Pt());
    internalId_.jetEta(p4->Eta());
    internalId_.nvtx(l_.vtx_std_n);
    
    full->set(internalId_);
}

// ---------------------------------------------------------------------------------------------------------------
void JetHandler::computeMva(int ijet, int ivtx)
{
    fillFromJet(ijet,ivtx);
    if( (*l_.jet_algoPF1_full_mva_ext)[ijet].size() <= ivtx ) {
	(*l_.jet_algoPF1_full_mva_ext)[ijet].resize(ivtx+1);
	(*l_.jet_algoPF1_full_wp_level_ext)[ijet].resize(ivtx+1);
	(*l_.jet_algoPF1_simple_mva_ext)[ijet].resize(ivtx+1);
	(*l_.jet_algoPF1_simple_wp_level_ext)[ijet].resize(ivtx+1);
	(*l_.jet_algoPF1_cutbased_wp_level_ext)[ijet].resize(ivtx+1);
    }

    
    // full->set(internalId_);
    PileupJetIdentifier fullId = full->computeMva();
    (*l_.jet_algoPF1_full_mva_ext)[ijet][ivtx] = fullId.mva();
    (*l_.jet_algoPF1_full_wp_level_ext)[ijet][ivtx] = fullId.idFlag();

    simple->set(internalId_);
    PileupJetIdentifier simpleId = simple->computeMva();
    (*l_.jet_algoPF1_simple_mva_ext)[ijet][ivtx] = simpleId.mva();
    (*l_.jet_algoPF1_simple_wp_level_ext)[ijet][ivtx] = simpleId.idFlag();
    
    TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);
    (*l_.jet_algoPF1_cutbased_wp_level_ext)[ijet][ivtx] 
	= cutbased->computeCutIDflag( (*l_.jet_algoPF1_betaStarClassic_ext)[ijet][ivtx], 
				      l_.jet_algoPF1_dR2Mean[ijet], 
				      l_.vtx_std_n,
				      p4->Pt(), p4->Eta() );
}

// ---------------------------------------------------------------------------------------------------------------
void JetHandler::computeWp(int ijet, int ivtx)
{
    if( ivtx >= l_.jet_algoPF1_nvtx ) { return; }

    TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);

    //// if( (*l_.jet_algoPF1_full_mva_ext)[ijet].size() <= ivtx ) {
    //// 	(*l_.jet_algoPF1_full_mva_ext)[ijet].resize(ivtx+1);
    //// 	(*l_.jet_algoPF1_full_wp_level_ext)[ijet].resize(ivtx+1);
    //// 	(*l_.jet_algoPF1_simple_mva_ext)[ijet].resize(ivtx+1);
    //// 	(*l_.jet_algoPF1_simple_wp_level_ext)[ijet].resize(ivtx+1);
    //// 	(*l_.jet_algoPF1_cutbased_wp_level_ext)[ijet].resize(ivtx+1);
    //// }
    
    if( l_.jet_algoPF1_cutbased_wp_level_ext == 0 ) {
	l_.jet_algoPF1_cutbased_wp_level_ext = new std::vector<std::vector<int> > (l_.jet_algoPF1_n,std::vector<int>(0));
    }
    if( (*l_.jet_algoPF1_cutbased_wp_level_ext)[ijet].size() <= ivtx ) { 
	(*l_.jet_algoPF1_cutbased_wp_level_ext)[ijet].resize(ivtx+1); 
    }

    //// (*l_.jet_algoPF1_full_wp_level_ext)[ijet][ivtx] 
    //// 	= full->computeIDflag( (*l_.jet_algoPF1_full_mva_ext)[ijet][ivtx], (float)p4->Pt(), (float)p4->Eta());
    //// 
    //// (*l_.jet_algoPF1_simple_wp_level_ext)[ijet][ivtx] 
    //// 	= simple->computeIDflag( (*l_.jet_algoPF1_simple_mva_ext)[ijet][ivtx], (float)p4->Pt(), (float)p4->Eta());
    

    (*l_.jet_algoPF1_cutbased_wp_level_ext)[ijet][ivtx] 
	= cutbased->computeCutIDflag( ( ivtx == 0 ? l_.jet_algoPF1_betaStarClassic[ijet] :  (*l_.jet_algoPF1_betaStarClassic_ext)[ijet][ivtx] ), 
				      l_.jet_algoPF1_dR2Mean[ijet], 
				      l_.vtx_std_n,
				      p4->Pt(), p4->Eta() );

    //////// }
}

// ---------------------------------------------------------------------------------------------------------------
void JetHandler::recomputeJec(int ijet, bool correct)
{
    bool data = l_.itype[l_.current] == 0;
    FactorizedJetCorrector * jecCor = ( data ? jecCorData_ : jecCorMc_ );
    TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);
    float oldPt = p4->Pt();
    float uncorrPt = p4->Pt() / l_.jet_algoPF1_erescale[ijet];
    float eta = p4->Eta();
    
    jecCor->setJetPt(uncorrPt);
    jecCor->setJetEta(eta);
    jecCor->setJetA(l_.jet_algoPF1_area[ijet]);
    jecCor->setRho(l_.rho_algo1);
    float thejec = jecCor->getCorrection();
    if( thejec < 0. ) { thejec = 0.; }
    float rescale = uncorrPt * thejec / p4->Pt();
    l_.jet_algoPF1_erescale[ijet] = thejec;
    *p4 *= rescale;
    //// if( oldPt > 20. ) {
    ////  	std::cerr << "JetHandler::recomputeJec " << uncorrPt << " " << eta << " " << l_.jet_algoPF1_area[ijet] 
    ////  		  << " " << l_.rho_algo1 << " " << thejec << " " << rescale << " " << oldPt 
    ////  		  << " " << p4->Pt() << std::endl;
    //// }
}

// ---------------------------------------------------------------------------------------------------------------
/// void JetHandler::recomputeJecEmulatingResponse(int ijet, bool correct, int entry)
void JetHandler::emulateJetResponse(int ijet)
{
    //// bool data = l_.itype[l_.current] == 0;
    //// FactorizedJetCorrector * jecCor = ( data ? jecCorData_ : jecCorMc_ );
    //// TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);
    //// float oldPt = p4->Pt();
    //// float uncorrPt = p4->Pt() / l_.jet_algoPF1_erescale[ijet];
    //// float eta = p4->Eta();
    //// 
    //// jecCor->setJetPt(uncorrPt);
    //// jecCor->setJetEta(eta);
    //// jecCor->setJetA(l_.jet_algoPF1_area[ijet]);
    //// jecCor->setRho(l_.rho_algo1);
    //// float thejec = jecCor->getCorrection();
    //// if( thejec < 0. ) { thejec = 0.; }
    //// 
    //// float response = jetResponseChange->getResponse(eta,float(entry%20)); // response change is given per fb^-1 --> do 20 bins of 1 fb-1
    //// thejec*=response;

    if( nLumiBins_ == 0 ) { nLumiBins_ = int(ceil(1.e-3*l_.intlumi_ / lumiStep_)); }

    TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);
    float emuLumi = float(abs(l_.event)%nLumiBins_)*lumiStep_;
    //// std::cout << "emulateJetResponse " << l_.event << " " << abs(l_.event)%nLumiBins_ << " " << emuLumi << std::endl;
    float response = jetResponseChange->getResponse(p4->Eta(),emuLumi); // response change is given per fb^-1 
    *p4 *= response;  
}


// ---------------------------------------------------------------------------------------------------------------
void JetHandler::applyJecUncertainty(int ijet, float shift)
{
    TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);
    double eta = p4->Eta();
    double ptCor = p4->Pt();
    
    jecUnc_->setJetEta(eta);
    jecUnc_->setJetPt(ptCor); // here you must use the CORRECTED jet pt
    double unc = shift*fabs(jecUnc_->getUncertainty(shift > 0.));
    *p4 *= 1. + unc;
}

// ---------------------------------------------------------------------------------------------------------------
void JetHandler::applyJerUncertainty(int ijet, float shift)
{
    TLorentzVector * p4 = (TLorentzVector*)l_.jet_algoPF1_p4->At(ijet);
    double eta = p4->Eta();
    double ptCor = p4->Pt();
    double genPt = l_.jet_algoPF1_genPt[ijet];

    std::vector<double>::iterator bound =  std::lower_bound( jerEtaBins_.begin(), jerEtaBins_.end(), eta );
    int bin = bound - jerEtaBins_.begin();
    double resSf = jerResSf_[bin] + shift*jerResSfErr_[bin]; 

    double jetSf=max(0.,(genPt+resSf*(ptCor-genPt)))/ptCor;
    *p4 *= jetSf;
}


// Local Variables:
// mode: c++
// c-basic-offset: 4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
