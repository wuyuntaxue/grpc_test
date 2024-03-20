set(DEMO_NAME "server_test")

aux_source_directory("${PROJECT_SOURCE_DIR}/server/" SERVER_SRCS)
aux_source_directory("${PROJECT_SOURCE_DIR}/proto/service_test_message/" PROTOBUF_SRCS)

add_executable(${DEMO_NAME} ${SERVER_SRCS} ${PROTOBUF_SRCS})

#链接库
target_link_libraries(${DEMO_NAME} PUBLIC -lpthread -lprotobuf -lgrpc++ -lgrpc)

#头文件查找目录
target_include_directories(${DEMO_NAME} PUBLIC
                            "${PROJECT_SOURCE_DIR}/server"
                            "${PROJECT_SOURCE_DIR}/3rdparty/grpc-1.62.1/include"
                            "${PROJECT_SOURCE_DIR}/proto"
                            )