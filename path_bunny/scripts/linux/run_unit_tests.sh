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

cd $PATH_BUNNY_DIR/src/unit_tests/build

check_result $PATH_BUNNY_DIR/src/unit_tests/build/libpath_test.so program1 input.txt

