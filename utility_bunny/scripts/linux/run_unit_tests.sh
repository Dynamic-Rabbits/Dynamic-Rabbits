kill -9 $(lsof -t -i:8888)
kill -9 $(lsof -t -i:7717)

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
    exit
  fi
}

cd $UTILITY_BUNNY_DIR/src/unit_tests/build

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_dataflow_analysis.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_dataflow_tests.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_dataflow_in_out.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_dataflow_constant_analysis.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/liballocator_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/liballocator_test2.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libspinlock_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_bdd_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_bitvector_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_pinstr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_shift_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_misc_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_generic_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_complex_arithmetic_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_srcdst_src_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_transfer_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_ptr_arith_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_xinstr_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_rep_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_cti_instr_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_comparison_instr_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_instrum_insert_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_bdd_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_bitvector_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_buf_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_list_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_lp_hashmap_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_lp_hashmap_test2.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_tk_lp_hashmap_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_tk_lp_hashmap_test2.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_tk_arraymap_test2.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_intptr_hashmap_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_str_hashmap_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_intptr_hashset_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_str_hashset_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_splaytree_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_env_var_input_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_env_test_app "okay"
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_env_var_input_test2.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_env_test_app2 "okay"
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_env_var_input_test3.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_env_test_app2 "okay"
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_env_var_input_test4.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_env_test_app2 "okay"
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_env_var_input_option_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_string_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_option_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test2.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test3.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test2.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test3.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test4.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test5.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app2
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test6.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app3
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test7.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app4
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test8.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app5
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test9.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app6
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test10.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test11.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app7
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_input_test12.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_file_test_app8

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_cl_arg_input_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_cl_arg_test_app 
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_cl_arg_input_test2.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_cl_arg_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_cl_arg_input_test3.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_cl_arg_test_app "Test"
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_cl_arg_input_test4.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_cl_arg_test_app "Test1 Test2"
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_cl_arg_input_test5.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_cl_arg_test_app "Test1 Test2"
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_cl_arg_input_test6.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_cl_arg_test_app "Test1 Test2"

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_alloc_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_alloc_test_app
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_alloc_test2.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_alloc_test_app2
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_alloc_test3.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_alloc_test_app3

check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app2
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test2.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app3
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test3.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app4
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver2.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test4.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app5
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test5.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver3.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test6.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app6
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver3.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test7.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app6
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver3.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test8.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app6
check_py_result $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_driver3.py $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_socket_input_test9.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_socket_test_app6

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_dealloc_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_dealloc_test_app

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_realloc_test.so $UTILITY_BUNNY_DIR/src/unit_tests/build/ub_realloc_test_app

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_ip_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_input_buf_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_loc_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_eflags_test.so echo ""
check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_register_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_file_reader_test.so echo ""

check_result $UTILITY_BUNNY_DIR/src/unit_tests/build/libub_bit_checker_test.so echo ""
