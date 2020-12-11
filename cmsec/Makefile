NAME := example
BUILDSHELLFILE :=`ls ../apidoc/proto/$(NAME)/*.proto | cut -d'/' -f5`
COMMSHELLFILE :=`ls ../apidoc/proto/common/*.proto | cut -d'/' -f5`

gen:
	make gen_base
	make gen_build
gen_build:# 自定义注册
	@echo "gen_build proto"
	@mkdir -p rpc/$(NAME)
	@for file in $(BUILDSHELLFILE); do \
	 echo build $$file; \
	 protoc --proto_path="../apidoc/proto/" --grpc_out=./rpc --plugin=./protoc-gen-grpc=`which grpc_cpp_plugin` $(NAME)/$$file; \
	 protoc --proto_path="../apidoc/proto/" --cpp_out=./rpc $(NAME)/$$file; \
	done;
gen_base:# 基础库
	@mkdir -p ../rpc/common
	@mkdir -p ./rpc/common
	@echo "gen proto"
	@rm -f rpc/common/*.pb.cc
	@rm -f rpc/common/*.pb.gmsec.cc
	@rm -f rpc/common/*.pb.h
	@rm -f rpc/common/*.pb.gmsec.h
	@for file in $(COMMSHELLFILE); do \
	 echo base $$file; \
	 protoc --proto_path="../apidoc/proto/" --grpc_out=../rpc --plugin=./protoc-gen-grpc=`which grpc_cpp_plugin` common/$$file; \
	 protoc --proto_path="../apidoc/proto/" --cpp_out=../rpc common/$$file; \
	done;
	@cp -rf ../rpc/common/ ./rpc #父目录向当前目录拷贝