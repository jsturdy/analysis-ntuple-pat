// -*- C++ -*-
//
// Package:    CleanedCaloMETProducer
// Class:      CleanedCaloMETProducer
// 
/**\class CleanedCaloMETProducer CleanedCaloMETProducer.cc TCMETcleaned357/CleanedTCMETProducer/src/CleanedCaloMETProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// user include files
#include "TCMETcleaned357/CleanedTCMETProducer/interface/CleanedCaloMETProducer.h"

//
// constructors and destructor
//
CleanedCaloMETProducer::CleanedCaloMETProducer (const edm::ParameterSet& iConfig)
{
     // get configuration parameters
     calometInputTag_     = iConfig.getParameter<edm::InputTag>("calometInputTag"    );
     caloTowerInputTag_ = iConfig.getParameter<edm::InputTag>("caloTowerInputTag");
     ebRechitInputTag_  = iConfig.getParameter<edm::InputTag>("ebRechitInputTag" );
     eeRechitInputTag_  = iConfig.getParameter<edm::InputTag>("eeRechitInputTag" );
     jetInputTag_       = iConfig.getParameter<edm::InputTag>("jetInputTag"      );
     jetIDinputTag_     = iConfig.getParameter<edm::InputTag>("jetIDinputTag"    );
     alias_             = iConfig.getParameter<std::string>  ("alias"            );

     useHFcorrection_   = iConfig.getParameter<bool>("useHFcorrection"  );
     useECALcorrection_ = iConfig.getParameter<bool>("useECALcorrection");
     useHCALcorrection_ = iConfig.getParameter<bool>("useHCALcorrection");

     recHitsEB = 0;
     recHitsEE = 0;

     listOfTowers.clear();

     produces<reco::CaloMETCollection> ().setBranchAlias(alias_.c_str());
}

CleanedCaloMETProducer::~CleanedCaloMETProducer ()
{
}

//
// member functions
//

// ------------ method called to produce the data  ------------
void CleanedCaloMETProducer::produce (edm::Event& iEvent, const edm::EventSetup& iSetup)
{
     // create holder for collection
     std::auto_ptr<reco::CaloMETCollection> caloMETcollection;
     caloMETcollection.reset(new reco::CaloMETCollection);

     // get input collections
     edm::Handle<reco::CaloMETCollection> calometHandle;
     iEvent.getByLabel(calometInputTag_    , calometHandle    );

     edm::Handle<CaloTowerCollection> caloTowerHandle;
     iEvent.getByLabel(caloTowerInputTag_, caloTowerHandle);

     iEvent.getByLabel(jetIDinputTag_    , jetIDhandle    );
     iEvent.getByLabel(jetInputTag_      , jetHandle      );

     iEvent.getByLabel(ebRechitInputTag_ , ebRechitHandle );
     recHitsEB = ebRechitHandle.product();

     iEvent.getByLabel(eeRechitInputTag_ , eeRechitHandle );
     recHitsEE = eeRechitHandle.product();

     //initialize caloMET variables
     met_x = (calometHandle->front()).px();
     met_y = (calometHandle->front()).py();
     sumet = (calometHandle->front()).sumEt();

     maxEtInEmTowers    = (calometHandle->front()).maxEtInEmTowers();
     maxEtInHadTowers   = (calometHandle->front()).maxEtInHadTowers();
     hadEtInHO          = (calometHandle->front()).hadEtInHO();
     hadEtInHB          = (calometHandle->front()).hadEtInHB();
     hadEtInHF          = (calometHandle->front()).hadEtInHF();
     hadEtInHE          = (calometHandle->front()).hadEtInHE();
     emEtInEB           = (calometHandle->front()).emEtInEB();
     emEtInEE           = (calometHandle->front()).emEtInEE();
     emEtInHF           = (calometHandle->front()).emEtInHF();
     etFractionHadronic = (calometHandle->front()).etFractionHadronic();
     etFractionEm       = (calometHandle->front()).emEtFraction();
     metSignificance    = (calometHandle->front()).metSignificance();
     caloMETInpHF       = (calometHandle->front()).CaloMETInpHF();
     caloMETInmHF       = (calometHandle->front()).CaloMETInmHF();
     caloSETInpHF       = (calometHandle->front()).CaloSETInpHF();
     caloSETInmHF       = (calometHandle->front()).CaloSETInmHF();
     caloMETPhiInpHF    = (calometHandle->front()).CaloMETPhiInpHF();
     caloMETPhiInmHF    = (calometHandle->front()).CaloMETPhiInmHF();

     /* Correct caloMET for HF spikes.  HF towers
      * are identified as spikes if they have
      * ET > 5 GeV and alpha < -0.8 || alpha > 0.99
      * where alpha = (L-S) / (L+S) and L,S are the
      * energy in the long and short fibers, respectivley.
      ***************************************************/
     listOfTowers.clear();
     for (CaloTowerCollection::const_iterator citer = caloTowerHandle->begin(); citer != caloTowerHandle->end(); ++citer)
     {
	  if (useHFcorrection_)
	  {
	       if (isHFspike(*citer))
	       {	       
		    correctCaloMETforHFspike(*citer);
		    continue;
	       }
	  }
	  /* Correct caloMET using ECAL timing.  Spikes
	   * are identified as rechits with ET > 5. GeV
	   * and out of time by at least 3 ns.
	   ***************************************************/
	  if (useECALcorrection_)
	  {
	       const std::vector<DetId> &towerDetIds = citer->constituents();

	       for (unsigned int idet = 0; idet < towerDetIds.size(); ++idet)
	       {
		    if (failsECALtiming(*citer, towerDetIds[idet]))
		    {
			 correctCaloMETforECALspike(*citer, towerDetIds[idet]);
			 listOfTowers.push_back(citer->id());
			 continue;
		    }
	       } // end loop over rechits
	  }
     } // end loop over towers

     /* Correct caloMET for HCAL noise using jet ID.
      * Here we use the loose jet ID as defined in
      * JME-09-008.  These criteria define a jet as 
      * as bad if the jet has PT > 5. GeV and fails 
      * any of the following:
      * 1. EMF > 0.01
      * 2. fHPD < 0.98
      * 3. n90Hits > 1
      ***************************************************/
     if (useHCALcorrection_)
     {
	  for (edm::View<reco::CaloJet>::const_iterator jiter = jetHandle->begin(); jiter != jetHandle->end(); ++jiter)
	  {
	       const unsigned int index = jiter - jetHandle->begin();
	       if (!isHCALnoise(*jiter, index))
		    continue;

	       correctCaloMETforHCALnoise(*jiter);
	  }
     }

     // fill caloMET object
     SpecificCaloMETData SpecificCaloMETdata;
     SpecificCaloMETdata.MaxEtInEmTowers    = maxEtInEmTowers;
     SpecificCaloMETdata.MaxEtInHadTowers   = maxEtInHadTowers;
     SpecificCaloMETdata.HadEtInHO          = hadEtInHO;
     SpecificCaloMETdata.HadEtInHB          = hadEtInHB;
     SpecificCaloMETdata.HadEtInHF          = hadEtInHF;
     SpecificCaloMETdata.HadEtInHE          = hadEtInHE;
     SpecificCaloMETdata.EmEtInEB           = emEtInEB;
     SpecificCaloMETdata.EmEtInEE           = emEtInEE;
     SpecificCaloMETdata.EmEtInHF           = emEtInHF;
     double totalHad = hadEtInHO + hadEtInHE + hadEtInHB + hadEtInHF;
     double totalEm =  emEtInEB + emEtInEE + emEtInHF;
     SpecificCaloMETdata.EtFractionHadronic = totalHad/(totalHad+totalEm);
     SpecificCaloMETdata.EtFractionEm       = totalEm/(totalHad+totalEm);
     SpecificCaloMETdata.METSignificance    = metSignificance;
     SpecificCaloMETdata.CaloMETInpHF       = caloMETInpHF;
     SpecificCaloMETdata.CaloMETInmHF       = caloMETInmHF;
     SpecificCaloMETdata.CaloSETInpHF       = caloSETInpHF;
     SpecificCaloMETdata.CaloSETInmHF       = caloSETInmHF;
     SpecificCaloMETdata.CaloMETPhiInpHF    = caloMETPhiInpHF;
     SpecificCaloMETdata.CaloMETPhiInmHF    = caloMETPhiInmHF;

     CommonMETData CaloMETdata;
     CaloMETdata.mex   = met_x;
     CaloMETdata.mey   = met_y;
     CaloMETdata.mez   = 0.;
     CaloMETdata.met   = sqrt(met_x * met_x + met_y * met_y);
     CaloMETdata.sumet = sumet;
     CaloMETdata.phi   = atan2(met_y, met_x);

     math::XYZTLorentzVector p4(CaloMETdata.mex, CaloMETdata.mey, CaloMETdata.mez, CaloMETdata.met);
     math::XYZPointD vtx(0., 0., 0.);
     reco::CaloMET calomet(SpecificCaloMETdata, CaloMETdata.sumet, p4, vtx);

     caloMETcollection->push_back(calomet);
     iEvent.put(caloMETcollection);

} // end produce()

// ------------ method called once each job just before starting event loop  ------------
void CleanedCaloMETProducer::beginJob ()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void CleanedCaloMETProducer::endJob ()
{
}

// ---------determine if tower is an HF spike--------------
bool CleanedCaloMETProducer::isHFspike (const CaloTower citer)
{
     // require tower to be in HF
     const std::vector<DetId>& detids = citer.constituents();
     bool isHCAL = false;
     unsigned int detidx = 999999;
     for (unsigned int idx = 0; idx < detids.size(); ++idx)
     {
	  if (detids[idx].det() == DetId::Hcal) {
	       isHCAL = true;
	       detidx = idx;
	  }
     }

     if (!isHCAL)
	  return false;

     HcalSubdetector subdet = (HcalSubdetector(detids[detidx].subdetId()));
     if (subdet != HcalForward)
	  return false;

     // require ET > 5. GeV
     double et = citer.emEt() + citer.hadEt();
     if (et < 5.)
	  return false;

     // require alpha < -0.8 || alpha > 0.99
     double alpha = citer.emEt() / et;
     if (alpha > -0.8 && alpha < 0.99)
	  return false;

     return true;
}

// ---------determine if ECAL rechit is bad using timing--------------
bool CleanedCaloMETProducer::failsECALtiming (const CaloTower citer, const DetId& detid)
{
     if (detid.det() != DetId::Ecal)
	  return false;

     if (detid.subdetId() == EcalEndcap)
     {
	  double energy = clusterTools.recHitEnergy(detid, recHitsEE);
	  double et     = energy / cosh(citer.eta());

	  if (et < 5.)
	       return false;

	  EcalRecHitCollection::const_iterator iter = recHitsEE->find(detid);
	  double time = iter->time();

	  if (fabs(time) < 3.)
	       return false;

	  return true;
     } // end EcalEndcap section

     if (detid.subdetId() == EcalBarrel)
     {
	  double energy = clusterTools.recHitEnergy(detid, recHitsEB);
	  double eta    = EBDetId::approxEta(detid);
	  double et     = energy / cosh(eta);

	  if (et < 5.)
	       return false;

	  EcalRecHitCollection::const_iterator iter = recHitsEB->find(detid);
	  double time = iter->time();

	  if (fabs(time) < 3.)
	       return false;

	  return true;
     } // end EcalBarrel section

     return false;
} // end failsECALtiming

// ---------determine if ECAL rechit is bad using timing--------------
bool CleanedCaloMETProducer::isHCALnoise (const reco::CaloJet jiter, const unsigned int index)
{
     // only consider jets in barrel since we are interesting in cleaning HB/HE noise
     if (fabs(jiter.eta()) > 2.55)
	  return false;

     if (jiter.et() < 5.)
	  return false;

     std::vector<CaloTowerPtr> jetTowers = jiter.getCaloConstituents();
     for (std::vector<CaloTowerPtr>::const_iterator titer = jetTowers.begin(); titer != jetTowers.end(); ++titer)
     {
	  const CaloTowerDetId jtid = (*(*titer)).id();

	  for (unsigned int eidx = 0; eidx < listOfTowers.size(); ++eidx)
	  {
	       if (listOfTowers[eidx] == jtid)
		    return false;
	  }
     }

     if (jiter.emEnergyFraction() < 0.01)
	  return true;

     edm::RefToBase<reco::CaloJet> jetRef = jetHandle->refAt(index);
     reco::JetID jetID = (*jetIDhandle)[jetRef];

     if (jetID.fHPD > 0.98)
	  return true;

     if (jetID.n90Hits < 2)
	  return true;

     return false;
} // end isHCALnoise

// ---------correct caloMET for HF spike--------------
void CleanedCaloMETProducer::correctCaloMETforHFspike (const CaloTower citer)
{
     double et  = citer.emEt() + citer.hadEt();
     double phi = citer.phi();

     met_x += et * cos(phi);
     met_y += et * sin(phi);
     sumet -= et;
     
     hadEtInHF -= citer.hadEt();
     emEtInHF  -= citer.emEt();

     if (citer.eta() > 0) {
       caloMETInpHF    += et;
       caloSETInpHF    -= et;
       //caloMETPhiInpHF;
     }
     else {
       caloMETInmHF    += et;
       caloSETInmHF    -= et;
       //caloMETPhiInmHF;
     }
     //maxEtInEmTowers;
     //maxEtInHadTowers;
} 

// ---------correct caloMET for ECAL spike--------------
void CleanedCaloMETProducer::correctCaloMETforECALspike (const CaloTower citer, const DetId& detid)
{
     if (detid.subdetId() == EcalBarrel)
     {
	  double eta    = EBDetId::approxEta(detid);
	  double energy = clusterTools.recHitEnergy(detid, recHitsEB);
	  double et     = energy / cosh(eta);

	  met_x += et * cos(citer.phi());
	  met_y += et * sin(citer.phi());
	  sumet -= et;
	  //maxEtInEmTowers;
	  //maxEtInHadTowers;
     } // end EcalBarrel section

     else if (detid.subdetId() == EcalEndcap)
     {
	  double eta    = citer.eta();
	  double energy = clusterTools.recHitEnergy(detid, recHitsEE);
	  double et     = energy / cosh(eta);

	  met_x += et * cos(citer.phi());
	  met_y += et * sin(citer.phi());
	  sumet -= et;
	  //maxEtInEmTowers;
	  //maxEtInHadTowers;
     } // end EcalEndcap section
}

// ---------correct caloMET for ECAL spike--------------
void CleanedCaloMETProducer::correctCaloMETforHCALnoise (const reco::CaloJet jiter)
{
     met_x += jiter.px();
     met_y += jiter.py();
     sumet -= jiter.et();
}

//define this as a plug-in
DEFINE_FWK_MODULE(CleanedCaloMETProducer);
