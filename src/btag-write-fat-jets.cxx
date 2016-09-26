#include "Options.hh"
#include "Jets.hh"
#include "SmartChain.hh"
#include "HDF5Writer.hh"
#include "constants.hh"
#include "unshittify.hh"
#include "select_jet.hh"
#include "math.hh"
#include "get_tree.hh"
#include "hdf5_object_builders.hh"

#include "H5Cpp.h"

#include <iostream>
#include <limits>

const std::string DESCRIPTION = (
  "Dump information for jets to HDF5"
  );

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
  size_t csize = opts.chunk_size;

  H5::H5File out_file(opts.output_file, H5F_ACC_TRUNC);
  h5::Writer<h5::Cluster> cluster_ds(out_file, "clusters", 20, csize);
  h5::Writer<h5::Track> track_ds(out_file, "tracks", 20, csize);
  h5::Writer1d<h5::Jet> jet_ds(out_file, "jets", csize);

  for (int iii = 0; iii < n_entries; iii++) {
    chain.GetEntry(iii);
    int n_jets = jets.size();
    for (int jjj = 0; jjj < n_jets; jjj++) {
      auto jet = jets.getJet(jjj);
      if (! select_fat_jet(jet) ) continue;
      double weight = opts.weight * jet.mc_event_weight;
      const auto clusters = get_clusters(jet);
      cluster_ds.add_jet(clusters);
      const auto tracks = get_tracks(jet);
      track_ds.add_jet(tracks);
      h5::Jet hjet{jet.jet_pt, jet.jet_eta};
      hjet.weight = weight;
      jet_ds.add_jet(hjet);
    }
  }
  cluster_ds.flush();
  cluster_ds.close();
  track_ds.flush();
  track_ds.close();
  jet_ds.flush();
  jet_ds.close();
}
