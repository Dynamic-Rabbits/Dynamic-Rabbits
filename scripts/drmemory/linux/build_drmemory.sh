git clone https://github.com/johnfxgalea/drmemory
cd drmemory

git checkout my_mods
git checkout 1cdbe394c6032ee96ca813683

make/git/devsetup.sh

rm -rf build
rm -rf install
mkdir build
mkdir install
cd build

if [ "$1" = "x86_32" ] ; then
  export CXXFLAGS=-m32
  export CFLAGS=-m32
fi

echo $DYNAMORIO_DIR

if [ "$2" = "Debug" ] ; then
  cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../install -DDynamoRIO_DIR=$DYNAMORIO_DIR/install/cmake -DCMAKE_BUILD_TYPE=Debug ..
  make -j 4
  make install
  echo "Build in Debug Mode"
else
  cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../install -DDynamoRIO_DIR=$DYNAMORIO_DIR/install/cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
  make -j 4
  make install
  echo "NOT in Debug Mode"
fi

