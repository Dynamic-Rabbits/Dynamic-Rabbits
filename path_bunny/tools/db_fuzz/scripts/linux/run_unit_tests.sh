echo "Starting Tests ..."

cd $PATH_BUNNY_DIR/src/unit_tests/build

$DB_RUN -c $PATH_BUNNY_DIR/tools/db_fuzz/src/build/libdb_fuzz.so -filename "input.txt" -- program1 input.txt
