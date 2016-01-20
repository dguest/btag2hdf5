#ifndef CONSTANTS_HH
#define CONSTANTS_HH

// use base units of GeV to make stuff more consistent with Delphes /
// easier to read
static const char* BASE_UNITS = "GeV";
const double MeV = 0.001;
const double GeV = 1000*MeV;
const double D0_THRESHOLD = 1.8; // track counting significance
const double PT_REWEIGHT_MAX = 1000*GeV;
const int PT_REWEIGHT_NBINS = 100;

// constant IO stuff
static const char*  REWEIGHT_FILE = "reweight.h5";

#endif
