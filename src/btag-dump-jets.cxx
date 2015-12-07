#include "FileCLI.hh"
#include "Jets.hh"
#include "SmartChain.hh"
#include "JetLabels.hh"

#include "TROOT.h"

#include <iostream>
#include <limits>

// const double GeV = 1000;
// const double MAX_PT = 1000*GeV;


// _____________________________________________________________________
// class implementation


// _____________________________________________________________________
// main function

int main(int argc, char* argv[]) {
  gROOT->ProcessLine("#include <vector>");
  FileCLI cli(argc, argv);

  SmartChain chain("bTag_AntiKt4EMTopoJets");
  for (const auto& in: cli.in_files()) {
    chain.add(in);
  }
  Jets jets(chain);
  int n_entries = chain.GetEntries();
  std::cout << n_entries << " entries in chain" << std::endl;

  OutJet<JetLabels> labels;
  std::cout << labels << std::endl;

  for (int iii = 0; iii < 10; iii++) {
    chain.GetEntry(iii);
    int n_jets = jets.size();
    for (int jjj = 0; jjj < n_jets; jjj++) {
      auto jet = jets.getJet(jjj);
      std::cout << jet << std::endl;
    }
  }
}
