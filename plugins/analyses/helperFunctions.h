#ifndef helperFunctions_h
#define helperFunctions_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <TMath.h>
#include <cmath>
#include "TLorentzVector.h"

//#define M_PI = 3.1415926535897932384626

namespace helperFunctions {
  
  inline double deltaPt(double pt1, double eta1, double pt2, double eta2) {
    double dPt;
    if (fabs(eta1)<fabs(eta2))
      dPt = pt1 - pt2;
    else 
      dPt = pt2 - pt1;
    return dPt;
  }

  inline double deltaPhi(double phi1, double phi2) {
    double dPhi = phi1 - phi2;
    while (dPhi > M_PI)  dPhi -= 2*M_PI;
    while (dPhi <= -M_PI) dPhi += 2*M_PI;
    return dPhi;
  }
  
  inline double deltaPhiUnsigned(double phi1, double phi2) {
    double dPhi;
    if (phi1 < 0) phi1 += 2*M_PI;
    if (phi2 < 0) phi2 += 2*M_PI;
    if (phi1 > phi2)
      dPhi = phi1 - phi2;
    else
      dPhi = phi2 - phi1;
    while (dPhi > M_PI)  dPhi = 2*M_PI - dPhi;
    return dPhi;
  }

  inline double perpComp(double dphij12, double dphijobj) {
    //return sin((dphij12/2) + 2*M_PI - dphijobj);
    return sin((dphij12/2) + dphijobj);
  }

  inline double perpComp(double phij1, double phij2, double phiobj ) {
    return perpComp(deltaPhiUnsigned(phij1,phij2),deltaPhi(phij1,phiobj));
  }

  //Get the component of object with phi = phiobj, perpendicular to the axis bisecting 
  //objects 1 and 2
  //Define positive perpendicular component to point to the jet with smaller eta
  inline double perpComp(double phij1, double etaj1, double phij2, double etaj2, double phiobj ) {
    double dphiJ1J2;
    double dphiJObj;
    if (fabs(etaj1<etaj2)) {
      dphiJ1J2 = deltaPhiUnsigned(phij1,phij2);
      dphiJObj = deltaPhi(phij1,phiobj);
    }
    else {
      dphiJ1J2 = deltaPhiUnsigned(phij1,phij2);
      dphiJObj = deltaPhi(phij2,phiobj);
    }
    return perpComp(dphiJ1J2,dphiJObj);
  }

  //Positive parallel component points toward the smaller opening angle of the jets
  inline double paraComp(double dphij12, double dphijobj) {
    return cos((dphij12/2) + dphijobj);
  }

  inline double paraComp(double phij1, double phij2, double phiobj ) {
    return paraComp(deltaPhiUnsigned(phij1,phij2),deltaPhi(phij1,phiobj));
  }

  inline double paraComp(double phij1, double etaj1, double phij2, double etaj2, double phiobj ) {
    double dphiJ1J2;
    double dphiJObj;
    if (fabs(etaj1<etaj2)) {
      dphiJ1J2 = deltaPhiUnsigned(phij1,phij2);
      dphiJObj = deltaPhi(phij1,phiobj);
    }
    else {
      dphiJ1J2 = deltaPhiUnsigned(phij1,phij2);
      dphiJObj = deltaPhi(phij2,phiobj);
    }
    return paraComp(dphiJ1J2,dphiJObj);
  }

  inline double deltaR2(double eta1, double phi1, double eta2, double phi2) {
    double dEta = eta1 - eta2;
    double dPhi = deltaPhi(phi1, phi2);
    return dEta*dEta + dPhi*dPhi;
  }
  
  inline double deltaR(double eta1, double phi1, double eta2, double phi2) { 
    return sqrt(deltaR2(eta1, phi1, eta2, phi2));
  }
  
  inline double deltaR(double deltar2) {
    return sqrt(deltar2);
  }
  
  inline double calcMomentum(double px, double py, double pz) {
    return sqrt(px*px + py*py* + pz*pz);
  }

  inline double calcTransverseMomentum(double px, double py) {
    return sqrt(px*px + py*py);
  }

  inline double calcEta(double px, double py, double pz) {
    return 0.5*log( (calcMomentum(px,py,pz) + pz)/(calcMomentum(px,py,pz) - pz) );
  }

  inline double correctHt(double Ht, double jetpt) {
    return Ht - jetpt;
  }
 
  inline double correctMHx(double MHx, double jetpx) {
    return MHx + jetpx;
  }
 
  inline double correctMHy(double MHy, double jetpy) {
    return MHy + jetpy;
  }
 
  inline double correctMHt(double MHx, double MHy, double jetpx, double jetpy) {
    MHx += jetpx;
    MHy += jetpy;
    return sqrt(MHx*MHx + MHy*MHy);
  }
 
};

#endif

