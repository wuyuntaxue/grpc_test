#include "grpcpp/grpcpp.h"
#include "service_test_message/service_test.grpc.pb.h"
#include "service_test_message/service_test.pb.h"

#include <iostream>
#include <thread>

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

    void TestRecordRoute() {
        ::RouteSummary      summary; // 回复
        grpc::ClientContext context; // 上下文

        // 调用方法，得到writer
        std::unique_ptr<grpc::ClientWriter<::Point>> writer = _stub->RecordRoute(&context, &summary);

        for (int i = 0; i < 10; i++) {
            ::Point tmpP;
            tmpP.set_latitude(i);
            tmpP.set_longitude(-i);

            if (!writer->Write(tmpP)) {
                std::cout << "write failed, " << i << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        writer->WritesDone();  // 通知服务端发送完成
        if (writer->Finish().ok()) { // 判断发送状态
            std::cout << "write ok, respone: {\n" << summary.DebugString() << "}" << std::endl;
        } else {
            std::cout << "write failed" << std::endl;
        }
    }

private:
    std::unique_ptr<RouteGuide::Stub> _stub;
};

int main() {
    std::string address("0.0.0.0:50051");
    GrouteGuideClient client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials())); // 创建通道

    std::cout << "-------------------------" << std::endl;
    client.TestGetFeature();
    std::cout << "-------------------------" << std::endl;
    client.TestGetListFeature();
    std::cout << "-------------------------" << std::endl;
    client.TestRecordRoute();
    return 0;
}