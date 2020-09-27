BASE_DUP_COUNT=3
BASE_SIZE=2
BASE_STAT_HIT_COUNT=1000
BASE_HIT_COUNT=10000
BASE_BB_IN_OUT_RATIO=1.1
BASE_POP=2

TIMEFORMAT=%R

run_test(){
    $DB_RUN -c $TAINT_BUNNY_DIR/tools/taint_dummy/src/build/libtaint_raw_fp_dummy.so $1 $2 $3 $4 $5 -- $6 $7 $8 $9 ${10} ${11} ${12}
}

rm -rf combo_tests
mkdir combo_tests
cd combo_tests


if [ "$1" = "DUP" ]; then
    mkdir dup_tests
    for i in `seq 1 10`;
    do
        MYTIME=$({ time run_test $i $BASE_SIZE $BASE_STAT_HIT_COUNT $BASE_HIT_COUNT $BASE_BB_IN_OUT_RATIO $BASE_POP $2 $3 $4 $5 $6 $7 $8 > ./dup_tests/test_$i 2>&1 ; } 2> /dev/stdout)
        echo "$i $MYTIME $2"
    done
fi

if [ "$1" = "SIZE" ]; then
    mkdir size_tests
    for i in `seq 2 8`;
    do
       MYTIME=$({ time run_test $BASE_DUP_COUNT $i $BASE_STAT_HIT_COUNT $BASE_HIT_COUNT $BASE_BB_IN_OUT_RATIO $BASE_POP $2 $3 $4 $5 $6 $7 $8 > ./size_tests/test_$i 2>&1 ; } 2> /dev/stdout)
       echo "$i $MYTIME $2"
    done
fi

if [ "$1" = "STATIC_HIT" ]; then
    mkdir stat_hit_tests
    for i in `seq 1 3`;
    do
       exp_size=$((10**$i))
       MYTIME=$({ time run_test $BASE_DUP_COUNT $BASE_SIZE $exp_size $BASE_HIT_COUNT $BASE_BB_IN_OUT_RATIO $BASE_POP $2 $3 $4 $5 $6 $7 $8 > ./stat_hit_tests/test_$i 2>&1 ; } 2> /dev/stdout)
       echo "$exp_size $MYTIME $2"
    done
fi

if [ "$1" = "HIT" ]; then
    mkdir hit_tests
    for i in `seq 1 4`;
    do
       exp_size=$((10**$i))
       MYTIME=$({ time run_test $BASE_DUP_COUNT $BASE_SIZE $BASE_STAT_HIT_COUNT $exp_size $BASE_BB_IN_OUT_RATIO $BASE_POP $2 $3 $4 $5 $6 $7 $8 > ./hit_tests/test_$i 2>&1 ; } 2> /dev/stdout) 
       echo "$exp_size $MYTIME $2"
    done
fi

if [ "$1" = "INOUT" ]; then
    mkdir inout_tests
    for i in `seq 0.6 0.2 1.6`;
    do
        THRESHOLD=$(echo print 1/$i | perl)
        MYTIME=$({ time run_test $BASE_DUP_COUNT $BASE_SIZE $BASE_STAT_HIT_COUNT $BASE_HIT_COUNT $THRESHOLD $BASE_POP $2 $3 $4 $5 $6 $7 $8 > ./inout_tests/test_$i 2>&1 ; } 2> /dev/stdout) 
        echo "$THRESHOLD $MYTIME $2"
    done
fi

if [ "$1" = "POP" ]; then
    mkdir pop_tests
    for i in `seq 1 4`;
    do
        MYTIME=$({ time run_test $BASE_DUP_COUNT $BASE_SIZE $BASE_STAT_HIT_COUNT $BASE_HIT_COUNT $BASE_BB_IN_OUT_RATIO $i $2 $3 $4 $5 $6 $7 $8 > ./pop_tests/test_$i 2>&1 ; } 2> /dev/stdout)
        echo "$i $MYTIME $2"
    done
fi

grep -rn . -e "ASSERT"
