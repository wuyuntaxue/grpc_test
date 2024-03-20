#include <iostream>
#include "grpcpp/grpcpp.h"
#include "service_test_message/service_test.grpc.pb.h"
#include "service_test_message/service_test.pb.h"

class GrouteGuideClient {
public:
    GrouteGuideClient(std::shared_ptr<grpc::Channel> channel) : _stub(RouteGuide::NewStub(channel)) {}

    void TestGetFeature() {
        Point req;
        Feature rsp;

        req.set_latitude(32);
        req.set_longitude(47);

        grpc::ClientContext context;
        grpc::Status status = _stub->GetFeature(&context, req, &rsp);
        if (status.ok()) {
            std::cout << "GetFeature ok" << std::endl;
            std::cout << rsp.DebugString() << std::endl;
        } else {
            std::cout << "GetFeature failed, " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<RouteGuide::Stub> _stub;
};

int main() {
    std::string address("0.0.0.0:50051");
    GrouteGuideClient client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));

    client.TestGetFeature();
    return 0;
}