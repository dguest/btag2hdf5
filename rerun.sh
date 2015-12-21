#!/usr/bin/env bash

set -eu

# check inputs
function _usage() {
    echo "usage: ${0##*/} <input file>"
}

if (( $# < 1 )); then
    _usage
    exit 1
fi

# define inputs
INPUT=$1
KIN="kinematics.h5"
RW="reweight.h5"
HISTS="hists.h5"
PLOTS="plots"

HERE=$(dirname $(which $0))

#define routines
FILL_RW=$HERE/bin/btag-distributions-pt-eta
FILL_OTHER=$HERE/bin/btag-distributions-other
MAKE_RW=$HERE/scripts/btag-make-reweight-hists.py
DRAW_OTHER=$HERE/scripts/btag-draw-hists.py

function need_new() {
    if [[ ! -f $1 ]]; then
        return 0
    fi
    local DEP
    for DEP in ${@:2}; do
        if [[ $DEP -nt $1 ]]; then
            return 0
        fi
    done
    return 1
}



if need_new $KIN $INPUT $FILL_RW; then
    echo "filling RW hists"
    $FILL_RW -f $INPUT -o $KIN
fi
if need_new $RW $KIN $MAKE_RW; then
    echo "building RW hists"
    $MAKE_RW $KIN $RW
fi

function draw() {
    echo "drawing..."
    $DRAW_OTHER $HISTS
}

if need_new $HISTS $INPUT $RW $FILL_OTHER; then
    echo "building other hists"
    $FILL_OTHER -f $INPUT -o $HISTS
    draw
fi
if [[ $DRAW_OTHER -nt $HISTS || ! -d $PLOTS  ]] ; then
    draw
fi