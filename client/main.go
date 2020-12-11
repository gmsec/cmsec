package main

import (
	"context"
	"fmt"
	"math/rand"
	"time"

	proto "client/rpc/example"

	"client/internal/routers"
	"client/internal/service/hello"

	"github.com/gin-gonic/gin"
	"github.com/gmsec/goplugins/plugin"
	"github.com/gmsec/micro"
	"github.com/xxjwxc/public/mydoc/myswagger"
	"github.com/xxjwxc/public/mylog"
)

// StartServer service call backe
func StartServer() {
	// swagger
	myswagger.SetHost("https://localhost:8080")
	myswagger.SetBasePath("client")
	myswagger.SetSchemes(true, false)
	// -----end --

	// reg := registry.NewDNSNamingRegistry()
	// grpc 相关 初始化服务
	service := micro.NewService(
		micro.WithName("client.srv.eg1"),
		// micro.WithRegisterTTL(time.Second*30),      //指定服务注册时间
		micro.WithRegisterInterval(time.Second*15), //让服务在指定时间内重新注册
		// micro.WithRegistryNaming(reg),
	)
	h := new(hello.Hello)
	proto.RegisterHelloServer(service.Server(), h) // 服务注册
	// ----------- end

	// gin restful 相关
	router := gin.Default()
	router.Use(routers.Cors())
	v1 := router.Group("/client/api/v1")
	routers.OnInitRouter(v1, h) // 自定义初始化
	// ------ end

	plg, b := plugin.Run(plugin.WithMicro(service),
		plugin.WithGin(router),
		plugin.WithAddr(":82"))

	if b == nil {
		plg.Wait()
	}
	fmt.Println("done")
}

// StartClient 启动client 用户端
func StartClient() {
	micro.SetClientServiceAddr(proto.GetHelloName(), "127.0.0.1:50051")
	// micro.SetClientServiceName(proto.GetHelloName(), "lp.srv.eg1") // set client group
	hello := proto.GetHelloClient()
	var request proto.HelloRequest

	ctx := context.Background()
	for i := 0; i < 10; i++ {
		r := rand.Intn(500)
		request.Name = fmt.Sprintf("%v", r)
		resp, err := hello.SayHello(ctx, &request)
		if err != nil {
			mylog.Error(err)
			fmt.Println("==========err:", err)
		}
		fmt.Println(resp)
		time.Sleep(1 * time.Second)
	}
}

func main() {
	// service := micro.NewService(
	// 	micro.WithName("127.0.0.1:50051"),
	// 	// micro.WithRegisterTTL(time.Second*30),      //指定服务注册时间
	// 	micro.WithRegisterInterval(time.Second*15), //让服务在指定时间内重新注册
	// 	//micro.WithRegistryNaming(reg),
	// )
	StartClient()
	// 连接服务器
	// 开始注册
	// reg := service.Options().Registry.RegNaming
	// b := grpc.RoundRobin(reg)

	// conn, err := grpc.Dial("127.0.0.1:50051", grpc.WithInsecure(), grpc.WithBlock()) //, grpc.WithBalancer(b))
	// if err != nil {
	// 	fmt.Printf("连接服务端失败: %s", err)
	// 	return
	// }
	// defer conn.Close()

	// // 新建一个客户端
	// c := proto.NewHelloClient(conn)

	// // 调用服务端函数
	// r, err := c.SayHello(context.Background(), &proto.HelloRequest{Name: "horika"})
	// if err != nil {
	// 	fmt.Printf("调用服务端代码失败: %s", err)
	// 	return
	// }

	// fmt.Printf("调用成功: %s", r.Message)

	// StartServer() //启动服务
	//
}
