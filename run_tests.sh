#!/usr/bin/env bash
bash $UTILITY_BUNNY_DIR/scripts/linux/run_unit_tests.sh

bash $SLICER_BUNNY_DIR/scripts/linux/run_unit_tests.sh

bash $INSTRUMENTATION_BUNNY_DIR/scripts/linux/run_unit_tests.sh

bash $TAINT_BUNNY_DIR/scripts/linux/run_unit_tests.sh

bash $PATH_BUNNY_DIR/scripts/linux/run_unit_tests.sh

bash $CFI_BUNNY_DIR/scripts/linux/run_unit_tests.sh

bash $VULNERABILITY_BUNNY_DIR/scripts/linux/run_unit_tests.sh
