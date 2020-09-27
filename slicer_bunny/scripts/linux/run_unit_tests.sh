RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo "Starting Tests ..."

NUM_TESTS=0
NUM_PASSED=0

run_test(){
  $DYNAMORIO_DIR/install/bin32/drrun -max_bb_instrs 5 -syntax_intel -c $1 -- $2 $3
  return $?
}

run_py_test(){
  python $1 $DYNAMORIO_DIR/install/bin32/drrun $2 $3 $4
  return $?
}

check_result(){
  bname=$(basename $1)
  NUM_PASSED=$((NUM_PASSED + 1))
  run_test $1 $2 $3
  if [ $? -eq 0 ]
  then
    NUM_PASSED=$((NUM_PASSED + 1))
    echo -e "${GREEN}$bname test passed!${NC}"
    return 1
  else
    echo -e "${RED}$bname test failed!${NC}"
    return 0
  fi
}

check_py_result(){
  bname=$(basename $2)
  NUM_PASSED=$((NUM_PASSED + 1))
  run_py_test $1 $2 $3 $4
  if [ $? -eq 0 ]
  then
    NUM_PASSED=$((NUM_PASSED + 1))
    echo -e "${GREEN}$bname test passed!${NC}"
    return 1
  else
    echo -e "${RED}$bname test failed!${NC}"
    return 0
  fi
}

cd $SLICER_BUNNY_DIR/src/unit_tests/build

check_result $SLICER_BUNNY_DIR/src/unit_tests/build/libsb_pc_slicer_test.so echo ""
check_result $SLICER_BUNNY_DIR/src/unit_tests/build/libsb_mod_slicer_test.so echo

