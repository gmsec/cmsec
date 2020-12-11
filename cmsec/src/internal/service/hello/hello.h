#ifndef _HELLO_H_
#define _HELLO_H_
#include <example/hello.grpc.pb.h>
class hello:public example::Hello::Service
{
public:
	grpc::Status SayHello(::grpc::ServerContext* context, const ::example::HelloRequest* request, ::example::HelloReply* response);
};

#endif // !_HELLO_H_



