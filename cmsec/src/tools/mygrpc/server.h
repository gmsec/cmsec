#ifndef _GRPC_SERVER_H_
#define _GRPC_SERVER_H_

#define GPR_LINUX_LOG 1


#include <grpcpp/grpcpp.h>

class GrpcServer final {
public:
	~GrpcServer();
	void Run(); // ��ʼ����
	bool RegisterService(grpc::Service& server);// ע�����
	bool Start();
	bool Stop(); // ֹͣ
private:
	grpc::ServerBuilder m_builder;
	std::unique_ptr<grpc::Server> m_server;
};
#endif