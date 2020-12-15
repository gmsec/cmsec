#!/bin/bash -x 

# install
# sudo apt-get install build-essential autoconf libtool pkg-config
# sudo apt-get install cmake
# sudo apt-get install clang-5.0 libc++-dev
git clone https://github.com/grpc/grpc.git
cd grpc
git submodule update --init # 获取gRPC的依赖组件
mkdir -p build_grpc
cd build_grpc
# cmake -DCMAKE_INSTALL_PREFIX:PATH=./output/grpc -DgRPC_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=ON -DgRPC_INSTALL=ON ..  #代码生成目录 so
cmake -DCMAKE_INSTALL_PREFIX:PATH=./output/grpc -DgRPC_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=ON ..  #代码生成目录 lib
make
sudo make install
cp -rf ./output/grpc/bin/grpc_cpp_plugin $GOPATH/bin
#cp -rf ./output/grpc/bin/protoc $GOPATH/bin

echo "SUCCESS output file:./grpc/build_grpc/output/grpc"
#end