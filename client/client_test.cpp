#include "grpcpp/grpcpp.h"
#include "service_test_message/service_test.grpc.pb.h"
#include "service_test_message/service_test.pb.h"

#include <iostream>

class GrouteGuideClient {
public:
    GrouteGuideClient(std::shared_ptr<grpc::Channel> channel)
        : _stub(RouteGuide::NewStub(channel)) {}

    void TestGetFeature() {
        Point   req;
        Feature rsp;

        req.set_latitude(32);
        req.set_longitude(47);

        grpc::ClientContext context;
        grpc::Status        status = _stub->GetFeature(&context, req, &rsp);
        if (status.ok()) {
            std::cout << "GetFeature ok" << std::endl;
            std::cout << rsp.DebugString() << std::endl;
        } else {
            std::cout << "GetFeature failed, " << status.error_message() << std::endl;
        }
    }

    void TestGetListFeature() {

        // 请求参数，赋值用来演示
        Rectangle req;
        req.mutable_hi()->set_latitude(80);
        req.mutable_hi()->set_longitude(47);
        req.mutable_lo()->set_latitude(10);
        req.mutable_lo()->set_longitude(37);

        grpc::ClientContext context; // 上下文

        // 调用方法得到reader对象
        std::unique_ptr<grpc::ClientReader<Feature>> reader = _stub->ListFeatures(&context, req);

        Feature rsqMsg;
        // 使用reader连续/多次读取数据，赋值到rsqMsg中，直到读取完成
        while (reader->Read(&rsqMsg)) {
            std::cout << "read: {\n" << rsqMsg.DebugString() << "}" << std::endl;
        }

        // 判断读取状态
        if (!reader->Finish().ok()) {
            std::cout << "read failed" << std::endl;
        } else {
            std::cout << "read done" << std::endl;
        }
    }

private:
    std::unique_ptr<RouteGuide::Stub> _stub;
};

int main() {
    std::string address("0.0.0.0:50051");
    GrouteGuideClient client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials())); // 创建通道

    client.TestGetFeature();
    std::cout << "-------------------------" << std::endl;
    client.TestGetListFeature();
    return 0;
}