# setup script for HDF5 dumper
setupATLAS -q

# -- get boost --
localSetupBoost boost-1.60.0-python2.7-x86_64-slc6-gcc49 -q
# required by makefile
export BOOST_PATH=$ALRB_BOOST_ROOT

# -- get root --
localSetupROOT -q

# -- get HDF5 --
lsetup hdf5 -q
export HDF_PATH=$ALRB_HDF5_PATH
