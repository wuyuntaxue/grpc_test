#!/bin/bash
SCRIPT_PATH=$(cd ../; pwd)

PROTOC_PATH="$SCRIPT_PATH"/3rdparty/grpc-1.62.1/bin

export LD_LIBRARY_PATH="$SCRIPT_PATH"/3rdparty/grpc-1.62.1/lib/

"$PROTOC_PATH"/protoc --grpc_out=./service_test_message/ --plugin=protoc-gen-grpc="$PROTOC_PATH"/grpc_cpp_plugin ./service_test.proto

"$PROTOC_PATH"/protoc --cpp_out=./service_test_message/ ./service_test.proto

cd -