Optimization Framework To HDF5 Converter
----------------------------------------

This converts ROOT files from the b-tagging optimization framework
into HDF5 files for use with DL1 / IPRNN / whatever algorithm.

#### Setup ####

Run the following to set up for the first time:

```bash
git clone git@github.com:dguest/btag2hdf5.git
cd btag2hdf5
. setup.sh
make
```

After building all the libraries _should_ be permanently linked to
CVMFS (thanks to some `-rpath` magic). There's no need to run the
setup script next time you log in.
