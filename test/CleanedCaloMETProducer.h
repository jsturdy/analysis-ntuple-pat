#ifndef CleanedCaloMETProducer_h
#define CleanedCaloMETProducer_h

/** \class CleanedCaloMETProducer
 *
 * Producer for use in CMSSW_3_5_X.
 * In this release, cleaning for ECAL spikes is performed
 * using the so-called "swiss cross" to identify unphysically
 * isolated ECAL rechits.  These rechits are given a severity
 * level flag kWeird and are not used to reconstruct calotowers.
 * Thus, caloMET and tcMET have this cleaning performed upstream.
 * However, no cleaning is performed by default for HF spikes or
 * other noise in the HB/HE or ECAL.
 *
 * This producer takes caloMET from the event and performs some
 * basic cleaning for HF spikes as well as noise in the HB/HE
 * and ECAL.
 *
 * \author F.Golf
 *
 * \version 1st Version 19 April 2010
 ***************************************************************/

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETFwd.h"
#include "DataFormats/METReco/interface/CommonMETData.h"
#include "DataFormats/METReco/interface/SpecificCaloMETData.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/SortedCollection.h"

//
// class declaration
//

class CleanedCaloMETProducer : public edm::EDProducer {
   public:
      explicit CleanedCaloMETProducer(const edm::ParameterSet&);
      ~CleanedCaloMETProducer();

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
     double met_x, met_y, sumet;
     double maxEtInEmTowers;
     double maxEtInHadTowers;
     double hadEtInHO;
     double hadEtInHB;
     double hadEtInHF;
     double hadEtInHE;
     double emEtInEB;
     double emEtInEE;
     double emEtInHF;
     double etFractionHadronic;
     double etFractionEm;
     double metSignificance;
     double caloMETInpHF;
     double caloMETInmHF;
     double caloSETInpHF;
     double caloSETInmHF;
     double caloMETPhiInpHF;
     double caloMETPhiInmHF;         

     edm::InputTag calometInputTag_;
     edm::InputTag caloTowerInputTag_;
     edm::InputTag ebRechitInputTag_;
     edm::InputTag eeRechitInputTag_;
     edm::InputTag jetInputTag_;
     edm::InputTag jetIDinputTag_;
     std::string alias_;

     edm::Handle<EcalRecHitCollection> ebRechitHandle;
     edm::Handle<EcalRecHitCollection> eeRechitHandle;
     edm::Handle<edm::View<reco::CaloJet> > jetHandle;
     edm::Handle<reco::JetIDValueMap> jetIDhandle;

     const EcalRecHitCollection* recHitsEB;
     const EcalRecHitCollection* recHitsEE;
     EcalClusterTools clusterTools;

     bool useHFcorrection_;
     bool useECALcorrection_;
     bool useHCALcorrection_;

     std::vector<CaloTowerDetId> listOfTowers;

     bool isHFspike (const CaloTower);
     bool failsECALtiming (const CaloTower, const DetId&);
     bool isHCALnoise (const reco::CaloJet, const unsigned int);
     void correctCaloMETforHFspike (const CaloTower);
     void correctCaloMETforECALspike (const CaloTower, const DetId&);
     void correctCaloMETforHCALnoise (const reco::CaloJet);
};

#endif
