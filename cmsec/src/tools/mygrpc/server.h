#ifndef _GRPC_SERVER_H_
#define _GRPC_SERVER_H_

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