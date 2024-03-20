#include <iostream>
#include <string>
#include "grpcpp/grpcpp.h"
#include "service_test_message/service_test.grpc.pb.h"
#include "service_test_message/service_test.pb.h"


class RouteGuideImpl : public RouteGuide::Service {
    /**
     * @brief 需要实现的方法，
     * 
     * @param context server上下文
     * @param request 客户端的请求，对应proto定义方法时的参数
     * @param response 服务端的回复，对应proto定义方法时的返回值
     * @return grpc::Status 
     */
    virtual grpc::Status GetFeature(grpc::ServerContext* context, const Point* request, Feature* response) {
        std::cout << "GetFeature, request: {\n" << request->DebugString() << "}" << std::endl;
        response->set_name(std::to_string(count));
        count++;
        return grpc::Status::OK;
    }

private:
    unsigned int count = 0;
};

int main() {
    std::string address("0.0.0.0:50051");
    RouteGuideImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "server listen on " << address << std::endl;

    server->Wait();

    return 0;
}