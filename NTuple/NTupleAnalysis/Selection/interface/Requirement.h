#ifndef IPHC_Requirement_h
#define IPHC_Requirement_h

// STL headers
#include <memory>
#include <vector>
#include <string>

class Selection;
class AnalysisEnvironmentLoader;

//! \class Requirement
class Requirement
{

  // -------------------------------------------------------------
  //                       method members
  // -------------------------------------------------------------
 public:

  friend class Selection;
  friend class AnalysisEnvironmentLoader;

  //! Constructor without argument
  Requirement();

  //! Destructor
  ~Requirement()
  {}

  //! Set electron requirements
  void SetElectronRequirements(float PtThr, float EtaThr,
                               float RelIsoThr, float D0Thr,
                               float VertexMatchThr_, float ElectronETSCThr,
                               float DRemuThr);

  //! Set muon requirements
  void SetMuonRequirements(float PtThr, float EtaThr,
                           float RelIsoThr, float D0Thr,
                           float VertexMatchThr_, float NValidHitsThr,
                           float NValidTkHitsThr, float Chi2Thr);

  //! Set tau requirements
  void SetTauRequirements(float PtThr, float EtaThr,
                          float VertexMatchThr_,
                          float LeadTrkPtThr);

  //! Set jet requirements
  void SetJetRequirements(float PtThr, float EtaThr);

  //! Set MET requirements
  void SetMETRequirements(float PtThr);     

  //! Set vertex requirements
  void SetVertexRequirements(float VertexNdofThr, float VertexZThr,
                             float VertexRhoThr);
   

  // -------------------------------------------------------------
  //                        data members
  // -------------------------------------------------------------
 private:

  //! Muon requirements
  float MuonPtThreshold_;
  float MuonEtaThreshold_;
  float MuonRelIso_;
  float MuonNofValidTrHits_;
  float MuonNofValidHits_;
  float MuonD0Cut_;
  float MuonNormChi2_;
  float MuonVertexMatchThr_;

  //! Electron requirements
  float ElectronPtThreshold_;
  float ElectronEtaThreshold_;
  float ElectronRelIso_;
  float ElectronD0Cut_;
  float ElectronVertexMatchThr_;
  float ElectronETSCThr_;
  float DRemuThr_;

  //! Tau requirements
  float TauPtThreshold_;
  float TauEtaThreshold_;
  float TauLeadTrkPtCut_;
  float TauVertexMatchThr_;

  //! Vertex requirements
  float VertexNdofThr_;
  float VertexZThr_;
  float VertexRhoThr_;

  //! Jet requirements
  float JetPtThreshold_;
  float JetEtaThreshold_;

  //! MET
  float METThreshold_;
};

#endif
