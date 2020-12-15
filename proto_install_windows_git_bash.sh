#!/bin/bash -x 


# install protoc-gen-grpc
git clone https://github.com/grpc/grpc.git
cd grpc
git submodule update --init # 获取gRPC的依赖组件
mkdir build_grpc
cd build_grpc
cmake -DCMAKE_INSTALL_PREFIX:PATH=./output/grpc .. #代码生成目录
cmake --build . --config Debug
cmake --build . --config Release
msbuild.exe -p:configuration=Release -p:platform=x64 -p:PreferredToolArchitecture=x64 -t:build INSTALL.vcxproj
#msbuild.exe -p:configuration=Release -p:platform=x64 -p:PreferredToolArchitecture=x64 -t:build INSTALL.vcxproj
cp -r ./Release/grpc_cpp_plugin.exe $GOPATH/bin

../../open.bat output

# chmod +x $GOPATH/bin/protoc 

echo "SUCCESS"
#end