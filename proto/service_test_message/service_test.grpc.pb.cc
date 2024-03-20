// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: service_test.proto

#include "service_test.pb.h"
#include "service_test.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>

static const char* RouteGuide_method_names[] = {
  "/RouteGuide/GetFeature",
  "/RouteGuide/ListFeatures",
};

std::unique_ptr< RouteGuide::Stub> RouteGuide::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< RouteGuide::Stub> stub(new RouteGuide::Stub(channel, options));
  return stub;
}

RouteGuide::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GetFeature_(RouteGuide_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ListFeatures_(RouteGuide_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::Status RouteGuide::Stub::GetFeature(::grpc::ClientContext* context, const ::Point& request, ::Feature* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Point, ::Feature, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetFeature_, context, request, response);
}

void RouteGuide::Stub::async::GetFeature(::grpc::ClientContext* context, const ::Point* request, ::Feature* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Point, ::Feature, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetFeature_, context, request, response, std::move(f));
}

void RouteGuide::Stub::async::GetFeature(::grpc::ClientContext* context, const ::Point* request, ::Feature* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetFeature_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Feature>* RouteGuide::Stub::PrepareAsyncGetFeatureRaw(::grpc::ClientContext* context, const ::Point& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Feature, ::Point, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetFeature_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Feature>* RouteGuide::Stub::AsyncGetFeatureRaw(::grpc::ClientContext* context, const ::Point& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetFeatureRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReader< ::Feature>* RouteGuide::Stub::ListFeaturesRaw(::grpc::ClientContext* context, const ::Rectangle& request) {
  return ::grpc::internal::ClientReaderFactory< ::Feature>::Create(channel_.get(), rpcmethod_ListFeatures_, context, request);
}

void RouteGuide::Stub::async::ListFeatures(::grpc::ClientContext* context, const ::Rectangle* request, ::grpc::ClientReadReactor< ::Feature>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::Feature>::Create(stub_->channel_.get(), stub_->rpcmethod_ListFeatures_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::Feature>* RouteGuide::Stub::AsyncListFeaturesRaw(::grpc::ClientContext* context, const ::Rectangle& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::Feature>::Create(channel_.get(), cq, rpcmethod_ListFeatures_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::Feature>* RouteGuide::Stub::PrepareAsyncListFeaturesRaw(::grpc::ClientContext* context, const ::Rectangle& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::Feature>::Create(channel_.get(), cq, rpcmethod_ListFeatures_, context, request, false, nullptr);
}

RouteGuide::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RouteGuide_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RouteGuide::Service, ::Point, ::Feature, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](RouteGuide::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Point* req,
             ::Feature* resp) {
               return service->GetFeature(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RouteGuide_method_names[1],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< RouteGuide::Service, ::Rectangle, ::Feature>(
          [](RouteGuide::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Rectangle* req,
             ::grpc::ServerWriter<::Feature>* writer) {
               return service->ListFeatures(ctx, req, writer);
             }, this)));
}

RouteGuide::Service::~Service() {
}

::grpc::Status RouteGuide::Service::GetFeature(::grpc::ServerContext* context, const ::Point* request, ::Feature* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status RouteGuide::Service::ListFeatures(::grpc::ServerContext* context, const ::Rectangle* request, ::grpc::ServerWriter< ::Feature>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


