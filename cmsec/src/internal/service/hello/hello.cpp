#include "hello.h"

grpc::Status hello::SayHello(::grpc::ServerContext* context, const::example::HelloRequest* request,
	::example::HelloReply* response)
{
	std::cout << request->name() << std::endl;

	response->set_message("aaaaaa");

	return grpc::Status();
}
