// ptResolution.C
// root -l -b -q 'ptResolution.C("../full_chain_simple/acts_simulation_output/sim_pythia_pp/")'

#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

void ptResolution(const char* inputPath = "../full_chain_simple/acts_simulation_output/sim_pythia_pp/")
{
  // ---- open file & tree ----
  std::string fileName = std::string(inputPath) + "/tracksummary_ambi.root";
  TFile* f = TFile::Open(fileName.c_str(), "READ");
  if (!f || f->IsZombie()) {
    std::cerr << "Error: cannot open file " << fileName << std::endl;
    return;
  }

  TTree* tree = dynamic_cast<TTree*>(f->Get("tracksummary"));
  if (!tree) {
    std::cerr << "Error: TTree 'tracksummary' not found in " << fileName << std::endl;
    f->Close();
    return;
  }

  std::cout << "Using track summary file: " << fileName << std::endl;

  // ---- set up TTreeReader ----
  TTreeReader reader(tree);
  TTreeReaderValue<std::vector<float>> t_pT(reader, "t_pT");
  TTreeReaderValue<std::vector<float>> eQOP_fit(reader, "eQOP_fit");
  TTreeReaderValue<std::vector<float>> eTHETA_fit(reader, "eTHETA_fit");
  TTreeReaderValue<std::vector<bool>> hasFittedParams(reader, "hasFittedParams");

  // ---- histograms ----
  const int nPtBins = 20;
  const double ptMin = 0.0;
  const double ptMax = 10.0;

  // 2D: truth pT vs relative residual
  TH2F* h2_ptRelRes = new TH2F("h2_ptRelRes",
                               ";truth p_{T} [GeV];(p_{T}^{fit}-p_{T}^{true})/p_{T}^{true}",
                               nPtBins, ptMin, ptMax,
                               200, -0.5, 0.5);

  // 1D: sigma(ΔpT/pT) vs pT
  TH1D* h_sigma = new TH1D("h_sigma",
                           ";truth p_{T} [GeV];#sigma(#Delta p_{T}/p_{T})",
                           nPtBins, ptMin, ptMax);

  // ---- event loop ----
  Long64_t nEntries = tree->GetEntries();
  std::cout << "Entries in tree: " << nEntries << std::endl;

  while (reader.Next()) {
    const auto& ptVec = *t_pT;
    const auto& qopVec = *eQOP_fit;     // q/p
    const auto& thetaVec = *eTHETA_fit; // theta
    const auto& hasVec = *hasFittedParams;

    size_t nTracks = ptVec.size();
    for (size_t i = 0; i < nTracks; ++i) {
      if (!hasVec[i])
        continue;

      double pt_true = ptVec[i];
      if (pt_true <= 0.)
        continue;

      double qop = qopVec[i];
      double theta = thetaVec[i];

      // p = 1 / |q/p|
      double p_fit = 1.0 / std::fabs(qop);
      double pt_fit = p_fit * std::sin(theta);

      double rel = (pt_fit - pt_true) / pt_true; // ΔpT/pT

      h2_ptRelRes->Fill(pt_true, rel);
    }
  }

  // ---- compute σ(ΔpT/pT) per pT bin ----
  for (int ix = 1; ix <= nPtBins; ++ix) {
    // project on Y for this pT bin
    TH1D* projY = h2_ptRelRes->ProjectionY(Form("projY_bin%d", ix), ix, ix);
    if (projY->GetEntries() < 2) {
      delete projY;
      continue;
    }
    double sigma = projY->GetRMS();
    double sigmaErr = projY->GetRMSError(); // ROOT’s estimate of RMS error

    h_sigma->SetBinContent(ix, sigma);
    h_sigma->SetBinError(ix, sigmaErr);

    delete projY;
  }

  // ---- draw & save ----
  TCanvas* c = new TCanvas("c_ptRes", "pT resolution", 900, 900);
  c->Divide(1, 2);

  c->cd(1);
  gPad->SetRightMargin(0.15);
  h2_ptRelRes->Draw("COLZ");

  c->cd(2);
  h_sigma->SetMarkerStyle(20);
  h_sigma->Draw("E1");

  std::string outPng = std::string(inputPath) + "/pt_resolution_root.png";
  c->SaveAs(outPng.c_str());
  std::cout << "Saved plot to " << outPng << std::endl;

  // also save histograms to a ROOT file
  std::string outRoot = std::string(inputPath) + "/pt_resolution.root";
  TFile* fout = TFile::Open(outRoot.c_str(), "RECREATE");
  h2_ptRelRes->Write();
  h_sigma->Write();
  fout->Close();
  std::cout << "Saved histograms to " << outRoot << std::endl;
}
