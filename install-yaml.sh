#! /bin/bash

set -e

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root"
   exit 1
fi

cd /tmp
if [ ! -d "yaml-cpp" ]; then
  git clone https://github.com/jbeder/yaml-cpp.git
fi

cd yaml-cpp
mkdir -p build
cd build
cmake ../
make

cp -r ../include/yaml-cpp /usr/local/include/yaml-cpp
echo "Copied include headers into /usr/local/include/yaml-cpp"
cp libyaml-cpp.a /usr/local/lib/
echo "Copied static lib to /usr/local/lib/libyaml-cpp.a"
echo "Done."