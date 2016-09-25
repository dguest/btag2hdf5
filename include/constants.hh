#ifndef CONSTANTS_HH
#define CONSTANTS_HH

// use base units of MeV to make stuff more consistent with ATLAS

static const char* BASE_UNITS = "MeV";
const double MeV = 1.0;
const double GeV = 1000*MeV;
const double TeV = 1000*GeV;

static const char* BASE_LENGTH = "mm";
const double mm = 1.0;
const double cm = 10*mm;

// various other constants
const double D0_THRESHOLD = 1.8; // track counting significance
const double PT_REWEIGHT_MAX = 1000*GeV;

#endif
