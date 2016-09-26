#include "Options.hh"
#include "Jets.hh"
#include "SmartChain.hh"
#include "HDF5Writer.hh"
#include "constants.hh"
#include "unshittify.hh"
#include "select_jet.hh"
#include "math.hh"
#include "get_tree.hh"

#include "H5Cpp.h"

#include <iostream>
#include <limits>

const std::string DESCRIPTION = (
  "Dump High-level information on jets to HDF5"
  );

namespace {
  h5::HighLevelBTag get_btagging(const Jet& jet) {
    h5::HighLevelBTag btag;
#define COPY(var) btag.var = jet.jet_ ## var
    COPY(pt);
    COPY(eta);

    COPY(ip3d_pb);
    COPY(ip3d_pc);
    COPY(ip3d_pu);

    COPY(sv1_Nvtx);
    COPY(sv1_ntrkv);
    COPY(sv1_n2t);
    COPY(sv1_m);
    COPY(sv1_efc);
    COPY(sv1_normdist);
    COPY(sv1_dR);
    COPY(sv1_Lxy);
    COPY(sv1_Lxyz);

    // Jetfitter
    COPY(jf_m);
    COPY(jf_efc);
    COPY(jf_deta);
    COPY(jf_dphi);
    COPY(jf_sig3d);
    COPY(jf_nvtx);
    COPY(jf_ntrkAtVx);
    COPY(jf_nvtx1t);
    COPY(jf_n2t);
    COPY(jf_VTXsize);

    // labeling
    COPY(truthflav);
    COPY(LabDr_HadF);

#undef COPY

    return btag;
  }
}

// _____________________________________________________________________
// main function

int main(int argc, char* argv[]) {
  unshittify();
  // required library calls
  H5::Exception::dontPrint();

  // load info
  const auto opts = get_opts(argc, argv, DESCRIPTION);
  SmartChain chain(get_tree(opts.input_files.at(0)));
  for (const auto& in: opts.input_files) {
    chain.add(in);
  }
  Jets jets(chain);
  int n_entries = chain.GetEntries();
  if (opts.verbose) std::cout << "entires: " << n_entries << std::endl;

  H5::H5File out_file(opts.output_file, H5F_ACC_TRUNC);
  h5::Writer1d<h5::HighLevelBTag> jet_ds(out_file, "jets", 256);

  for (int iii = 0; iii < n_entries; iii++) {
    chain.GetEntry(iii);
    int n_jets = jets.size();
    for (int jjj = 0; jjj < n_jets; jjj++) {
      auto jet = jets.getJet(jjj);
      if (! select_fat_jet(jet) ) continue;
      // double weight = opts.weight * jet.mc_event_weight;
      jet_ds.add_jet(get_btagging(jet));
    }
  }
  jet_ds.flush();
  jet_ds.close();
}
