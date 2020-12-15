#include <cstdio>
#include <tools/mygrpc/server.h>
#include <tools/tools.h>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <internal/service/hello/hello.h>

void Close(GrpcServer & server) {
#ifdef _WIN32
    ::Sleep(10000);
#else
    sleep(10);
#endif
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
#ifdef _WIN32
    ::Sleep(20000);
#else
    sleep(20);
#endif
    return 0;
}