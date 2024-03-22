#include "grpcpp/grpcpp.h"
#include "service_test_message/service_test.grpc.pb.h"
#include "service_test_message/service_test.pb.h"

#include <iostream>
#include <string>
#include <thread>
#include <vector>

class RouteGuideImpl : public RouteGuide::Service {
public:
    RouteGuideImpl() {
        nameVec = {"zhao", "qian", "sun", "li", "zhou", "wu", "zheng", "wang"};
    }

public:
    /**
     * @brief 需要实现的方法，简单RPC（客户端发起请求，服务端回复）
     *
     * @param context server上下文
     * @param request 客户端的请求，对应proto定义方法时的参数
     * @param response 服务端的回复，对应proto定义方法时的返回值
     * @return grpc::Status
     */
    virtual grpc::Status GetFeature(grpc::ServerContext *context, const Point *request, Feature *response) {
        std::cout << "GetFeature, request: {\n" << request->DebugString() << "}" << std::endl;
        response->set_name(std::to_string(count));
        count++;
        return grpc::Status::OK;
    }

    /**
     * @brief 服务端流式RPC （客户端发起请求，服务端连续/多次回应，客户端连续读取，直至写入/读取完成）
     *
     * @param context 上下文
     * @param request 客户端的请求
     * @param writer writer模板对象，用于向客户端多次传输数据
     * @return grpc::Status
     */
    virtual grpc::Status ListFeatures(grpc::ServerContext *context, const ::Rectangle *request,
                                      grpc::ServerWriter<::Feature> *writer) {

        std::cout << "request: {\n" << request->DebugString() << "}" << std::endl;
        for (auto &name : nameVec) {
            Feature res;
            res.set_name(name);
            res.mutable_location()->set_latitude(count);
            res.mutable_location()->set_longitude(count);

            writer->Write(res); // 写入
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            count++;
        }
        std::cout << "write done" << std::endl; // 写入完成
        return grpc::Status::OK;
    }

    /**
     * @brief 客户端流式RPC （客户端发起连接，多次/连续发送请求，服务端连续读取，直至写入/读取完成）
     *
     * @param context
     * @param reader reader模板对象，用来读取客户端发来的数据
     * @param response 给客户端的回复
     * @return grpc::Status
     */
    virtual grpc::Status RecordRoute(grpc::ServerContext *context, grpc::ServerReader<::Point> *reader,
                                     ::RouteSummary *response) {
        ::Point      pMsg;
        unsigned int tmpCount = 0;
        while (reader->Read(&pMsg)) {
            std::cout << "read: {\n" << pMsg.DebugString() << "}" << std::endl;
            tmpCount++;
        }

        response->set_point_count(tmpCount);
        return grpc::Status::OK;
    }

    /**
     * @brief 双向流
     *
     * @param context
     * @param stream 读写流，读写的数据类型为其中的模板参数
     * @return grpc::Status
     */
    virtual grpc::Status RouteChat(grpc::ServerContext                              *context,
                                   grpc::ServerReaderWriter<::Feature, ::RouteNote> *stream) {

        // 这里的逻辑是读到一次数据，向客户端发送两次数据
        unsigned int tmpCount = 0;
        RouteNote    readmsg;
        while (stream->Read(&readmsg)) {
            std::string rspMsg;
            if (!readmsg.message().compare("hello")) {
                std::cout << "read hello" << std::endl;
            } else if (!readmsg.message().compare("test")) {
                std::cout << "read test" << std::endl;
            } else {
                std::cout << "read other: " << readmsg.message() << std::endl;
            }

            rspMsg = "recv ";
            rspMsg.append(readmsg.message()).append(", ");
            rspMsg.append(std::to_string(tmpCount));

            Feature feat;
            feat.set_name(rspMsg + "a");
            stream->Write(feat);

            feat.set_name(rspMsg + "b");
            stream->Write(feat);
            tmpCount++;
        }

        std::cout << "stream read done" << std::endl;
        return grpc::Status::OK;
    }

private:
    unsigned int             count = 1;
    std::vector<std::string> nameVec;
};

int main() {
    std::string    address("0.0.0.0:50051");
    RouteGuideImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "server listen on " << address << std::endl;

    server->Wait();
    return 0;
}