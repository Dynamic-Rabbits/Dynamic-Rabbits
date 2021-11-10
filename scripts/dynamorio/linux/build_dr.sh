git clone https://github.com/johnfxgalea/dynamorio.git $DYNAMORIO_DIR

cd $DYNAMORIO_DIR
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

