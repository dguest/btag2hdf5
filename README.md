Optimization Framework To HDF5 Converter
----------------------------------------

This converts ROOT files from the b-tagging optimization framework
into HDF5 files for use with DL1 / IPRNN / whatever algorithm.

### Setup ###

Assuming you have CVMFS, you can run the following to set up for the
first time:

```bash
git clone git@github.com:dguest/btag2hdf5.git
cd btag2hdf5
. setup.sh
make
```

After building all the libraries _should_ be permanently linked to
CVMFS (thanks to some `-rpath` magic). **There should be no need to
run the setup script next time you log in.**

#### If you don't have CVMFS ####

You'll need the following:

 - ROOT: use `master` branch for 6, `root5` branch for version 5
 - boost: for `program_options`
 - HDF5: with the C++ bindings installed

### Running ###

The executables will be built as `./bin/btag-*`. For more "standard"
b-taggers, you can use `btag-write-track-jets`. For studies with fat
jets, there's also `btag-write-fat-jets`. Note that this is more
experimental.

#### Note On Selection ####

There is some standard pt, eta, and JVT selection applied to jets. For
details look in `src/select_jet.cxx`.
