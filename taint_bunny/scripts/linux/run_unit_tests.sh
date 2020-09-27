RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo "Starting Tests ..."

NUM_TESTS=0
NUM_PASSED=0

run_test(){
  $DB_RUN -c $1 -- $2 $3 $4 $5
  return $?
}

run_py_test(){
  python $1 $DYNAMORIO_DIR/install/bin32/drrun $2 $3 $4 $5
  return $?
}

check_result(){
  bname=$(basename $1)
  NUM_PASSED=$((NUM_PASSED + 1))
  run_test $1 $2 "$3" $4 $5
  if [ $? -eq 0 ]
  then
    NUM_PASSED=$((NUM_PASSED + 1))
    echo -e "${GREEN}$bname test passed!${NC}"
    return 1
  else
    echo -e "${RED}$bname test failed!${NC}"
   #return 0
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
    exit
  fi
}

run_checker_tests(){
  check_result $1 program1 crash.txt
  check_result $1 program3 crash.txt
  check_result $1 program4 crash.txt
  check_result $1 program5 crash.txt
  check_result $1 program6 crash.txt
  check_result $1 program7 crash.txt
  check_result $1 program8 crash.txt

  check_result $1 wget --help

  check_result $1 echo "John FX Galea"

  check_result $1 cat my_name.txt

  rm -f crash_temp.txt.bz2
  cp crash.txt crash_temp.txt
  check_result $1 bzip2 crash_temp.txt

  #LONG TESTS
  check_result $1 php phptest2.php

  check_result $1 php phptest.php

  check_result $1 file /dev/null

  check_result $1 convert my_boat.png my_boat.jpg
}

run_checker_annotation_tests(){

  check_result $1 program18 crash.txt
}

run_dummy_tests(){

  $DB_RUN -c $1 $2 $3 $4 $5 $6 -- cp crash.txt crash2.txt

  rm crash_temp.txt.bz2
  cp crash.txt crash_temp.txt
  $DB_RUN -c $1 $2 $3 $4 $5 $6 -- bzip2 crash_temp.txt

  $DB_RUN -c $1 $2 $3 $4 $5 $6 -- convert my_boat.png my_boat.jpg

  $DB_RUN -c $1 $2 $3 $4 $5 $6 -- php7.2 phptest2.php
}

cd $TAINT_BUNNY_DIR/src/unit_tests/build

echo "Running Deep Unit tests"

check_result $TAINT_BUNNY_DIR/src/unit_tests/build/libtb_cc_ta_test.so echo ""
check_result $TAINT_BUNNY_DIR/src/unit_tests/build/libtb_bunny_test.so echo ""
check_result $TAINT_BUNNY_DIR/src/unit_tests/build/libtb_cc_map_test.so echo ""
check_result $TAINT_BUNNY_DIR/src/unit_tests/build/libtb_map_driver_test.so echo ""
check_result $TAINT_BUNNY_DIR/src/unit_tests/build/libcc_taint_policies_test.so echo ""

echo "Running applications"

run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker2.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker3.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker4.so

#run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker5.so
#run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker6.so

run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker7.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker8.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker9.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker10.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker11.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker12.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker13.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker14.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker15.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker16.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker17.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker18.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker19.so
run_checker_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker20.so

echo "Running annotation tests"

run_checker_annotation_tests $TAINT_BUNNY_DIR/src/unit_tests/build/libstack_checker21.so

echo "Running dummy tests - no test status printed - just checking if they crash."

run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_cc_dummy.so dummy 0
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_cc_dummy.so id 0
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_cc_dummy.so bitwise 0
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_cc_dummy.so bitvect 0

run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_raw_dummy.so dummy 0
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_raw_dummy.so id 0
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_raw_dummy.so bitwise 0

run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_simd_dummy.so dummy  0
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_simd_dummy.so id  0
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_simd_dummy.so bitwise  0

run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_raw_dummy.so dummy 1
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_raw_dummy.so id 1
run_dummy_tests $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_raw_dummy.so bitwise 1

