#!/bin/bash -x 

# version="3.11.4"

# # su - xxj -c "qwer"
# # download
# curl -fLo protobuf.tar.gz https://github.com/protocolbuffers/protobuf/releases/download/v${version}/protoc-${version}-win64.zip
# mkdir protobuf-${version}
# unzip -d ./protobuf-${version}/ protobuf.tar.gz
# cd protobuf-${version}

# # install
# # xattr -c ./bin/protoc
# cp -r ./bin/protoc.exe $GOPATH/bin
# cd ../
# rm -rf protobuf-${version}/
# rm -rf ./protobuf.tar.gz

# install protoc-gen-grpc
git clone https://github.com/grpc/grpc.git
cd grpc
git submodule update --init # 获取gRPC的依赖组件
mkdir build_grpc
cd build_grpc
cmake -DCMAKE_INSTALL_PREFIX:PATH=./output/grpc .. #代码生成目录
cmake --build . --config Debug
cmake --build . --config Release
msbuild.exe -p:configuration=Debug -p:platform=x64 -p:PreferredToolArchitecture=x64 -t:build INSTALL.vcxproj
#msbuild.exe -p:configuration=Release -p:platform=x64 -p:PreferredToolArchitecture=x64 -t:build INSTALL.vcxproj
cp -r ./Release/grpc_cpp_plugin.exe $GOPATH/bin

../../open.bat output

# chmod +x $GOPATH/bin/protoc 

echo "SUCCESS"
#end