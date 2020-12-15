#ifndef _GRPC_SERVER_H_
#define _GRPC_SERVER_H_

#define GPR_LINUX_LOG 1


#include <grpcpp/grpcpp.h>

class GrpcServer final {
public:
	~GrpcServer();
	void Run(); // 开始运行
	bool RegisterService(grpc::Service& server);// 注册服务
	bool Start();
	bool Stop(); // 停止
private:
	grpc::ServerBuilder m_builder;
	std::unique_ptr<grpc::Server> m_server;
};
#endif