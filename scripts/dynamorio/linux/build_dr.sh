git clone https://github.com/johnfxgalea/dynamorio.git $DYNAMORIO_DIR

cd $DYNAMORIO_DIR
git checkout my_mods
git checkout 6a5a9f60a63ee922f053217202c815f76d0149de


rm -rf build
rm -rf install
mkdir build
mkdir install
cd build

if [ "$1" = "x86_32" ] ; then
  export CXXFLAGS=-m32
  export CFLAGS=-m32
fi

echo $2

if [ "$2" = "Debug" ] ; then
  cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../install -DDrMemoryFramework_DIR=$DRMEMORY_DIR/install/drmf  -DDEBUG=ON ..
  make -j 4
  make install
  echo "Build in Debug Mode"

else
  cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../install ..
  make -j 4
  make install
  echo "NOT in Debug Mode"
fi

cd $DYNAMORIO_DIR/api/samples
mkdir build
cd build
cmake -DX86_32=true -DCMAKE_BUILD_TYPE=Release -DDynamoRIO_DIR=$DYNAMORIO_DIR/install/cmake/ -DDYNAMORIO_SOURCE_DIR=$DYNAMORIO_DIR -DCMAKE_INSTALL_PREFIX=`pwd`/../install ..
make -j 4

