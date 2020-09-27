RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo "Starting Tests ..."

NUM_TESTS=0
NUM_PASSED=0

run_test(){
  $DB_RUN -c $1 -- $2 $3
  return $?
}

run_py_test(){

  python $1 $DYNAMORIO_DIR/install/bin32/drrun $2 $3 $4
  return $?
}

check_result(){
  bname=$(basename $1)
  NUM_PASSED=$((NUM_PASSED + 1))
  run_test $1 $2 "$3"
  if [ $? -eq 0 ]
  then
    NUM_PASSED=$((NUM_PASSED + 1))
    echo -e "${GREEN}$bname test passed!${NC}"
    return 1
  else
    echo -e "${RED}$bname test failed!${NC}"
    exit
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


cd $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build

check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test2.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test3.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test4.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test5.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test6.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test7.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test8.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test9.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test10.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test11.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test12.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test13.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test14.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test15.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test16.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test17.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test18.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test19.so ib_mod_slicer_app ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test20.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test21.so ib_mod_slicer_app ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test22.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test24.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test25.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test26.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test27.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test28.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test29.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test30.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test32.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test33.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test34.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test35.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test36.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test37.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test38.so echo ""
check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_instrumentation_bunny_test39.so echo ""

check_result $INSTRUMENTATION_BUNNY_DIR/src/unit_tests/build/libib_option_test.so echo ""
