#!/usr/bin/env bash
bash $UTILITY_BUNNY_DIR/scripts/linux/clean_utility_bunny.sh
bash $UTILITY_BUNNY_DIR/scripts/linux/build_utility_bunny.sh $1 $2

bash $SLICER_BUNNY_DIR/scripts/linux/clean_slicer_bunny.sh
bash $SLICER_BUNNY_DIR/scripts/linux/build_slicer_bunny.sh $1 $2

bash $INSTRUMENTATION_BUNNY_DIR/scripts/linux/clean_instrumentation_bunny.sh
bash $INSTRUMENTATION_BUNNY_DIR/scripts/linux/build_instrumentation_bunny.sh $1 $2

bash $TAINT_BUNNY_DIR/scripts/linux/clean_taint_bunny.sh
bash $TAINT_BUNNY_DIR/scripts/linux/build_taint_bunny.sh $1 $2

bash $PATH_BUNNY_DIR/scripts/linux/clean_path_bunny.sh
bash $PATH_BUNNY_DIR/scripts/linux/build_path_bunny.sh $1 $2

bash $CFI_BUNNY_DIR/scripts/linux/clean_cfi_bunny.sh
bash $CFI_BUNNY_DIR/scripts/linux/build_cfi_bunny.sh $1 $2

bash $VULNERABILITY_BUNNY_DIR/scripts/linux/clean_vulnerability_bunny.sh
bash $VULNERABILITY_BUNNY_DIR/scripts/linux/build_vulnerability_bunny.sh $1 $2

