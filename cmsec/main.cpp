#include <cstdio>
#include <tools/mygrpc/server.h>
#include <tools/tools.h>
#include <thread>
#include <windows.h>
#include <internal/service/hello/hello.h>

void Close(GrpcServer & server) {
    ::Sleep(10000);
    server.Stop();
}

int main()
{
    MEMORY_CHICK;
    hello he;


    GrpcServer server;
    server.RegisterService(he);
    server.Run();


    std::cout << MyTools::GetCurrentDate() << std::endl;
    ::Sleep(20000);
    return 0;
}