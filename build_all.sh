#!/usr/bin/env bash
bash $BUNNY_HACKERS_DIR/scripts/dynamorio/linux/build_dr.sh $1 $2
bash $BUNNY_HACKERS_DIR/scripts/drmemory/linux/build_drmemory.sh $1 $2
bash $BUNNY_HACKERS_DIR/build_bunnies.sh $1 $2
