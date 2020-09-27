cd $PATH_BUNNY_DIR/tools/db_fuzz/src

rm -rf build
mkdir build
cd build

if [ "$1" == "x86_32" ] ; then
  export CXXFLAGS=-m32
  export CFLAGS=-m32
  is_x86_32="true"
elif [ "$1" == "x86_64" ] ; then
  is_x86_32="false"
else
  echo "No Architecture specified at parameter 1! Exiting with error";
  exit 1;
fi

cmake -DCMAKE_BUILD_TYPE=$2 -DDynamoRIO_DIR=$DYNAMORIO_DIR/install/cmake/ -DDYNAMORIO_SOURCE_DIR=$DYNAMORIO_DIR -DDrMemoryFramework_DIR=$DRMEMORY_DIR/install/drmf -DPATH_BUNNY_DIR=$PATH_BUNNY_DIR -DTAINT_BUNNY_DIR=$TAINT_BUNNY_DIR -DUTILITY_BUNNY_DIR=$UTILITY_BUNNY_DIR -DSLICER_BUNNY_DIR=$SLICER_BUNNY_DIR -DINSTRUMENTATION_BUNNY_DIR=$INSTRUMENTATION_BUNNY_DIR  ..
make -j 4


