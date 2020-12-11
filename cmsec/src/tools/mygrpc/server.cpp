#include "server.h"
//#include <grpcpp/grpcpp.h>
//#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

GrpcServer::~GrpcServer()
{
}

void GrpcServer::Run()
{
	std::string server_address("0.0.0.0:50051");

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	
	// Listen on the given address without any authentication mechanism.
	m_builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	
	// Finally assemble the server.
	m_server = std::move(m_builder.BuildAndStart());
	//std::unique_ptr<grpc::Server> server(m_builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	m_server->Wait();
	
}

bool GrpcServer::RegisterService(grpc::Service& service)
{
	m_builder.RegisterService(&service);
	return false;
}

bool GrpcServer::Start()
{
	std::thread t1(std::bind(&GrpcServer::Run, this));
	t1.detach();
	return true;
}

bool GrpcServer::Stop()
{
	m_server->Shutdown();
	return false;
}
