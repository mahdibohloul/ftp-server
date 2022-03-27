cmake_minimum_required(VERSION 3.21)
project(ftp_server)
set(CMAKE_CXX_STANDARD 20)

add_executable(
        ftp_server
        src/server.cpp
        src/infrastructure/server/Server.cpp
        src/infrastructure/time/TimeService.cpp
        src/infrastructure/logger/Logger.cpp
        src/infrastructure/logger/LoggerFactory.cpp
        src/infrastructure/config/ServerConfig.cpp
        src/domain/user/models/User.cpp
        src/domain/user/repositories/UserRepository.cpp
        src/domain/user/services/UserService.cpp
        src/infrastructure/socket/WebSocket.cpp
        src/infrastructure/socket/WebSocket.hpp
        src/framework/router/Router.cpp src/framework/router/Router.hpp
        src/infrastructure/workContext/WorkContext.cpp
        src/infrastructure/workContext/WorkContext.hpp
        src/framework/handler/Handler.hpp src/framework/handler/AuthenticationHandler.cpp
        src/framework/handler/AuthenticationHandler.hpp src/framework/handler/Handler.cpp
        src/framework/handler/FileHandler.cpp src/framework/handler/FileHandler.hpp
        src/domain/directory/models/Directory.cpp src/domain/directory/models/Directory.hpp
        src/domain/file/models/GrantedFile.cpp
        src/domain/file/models/GrantedFile.hpp src/domain/user/models/Role.hpp src/domain/file/repositories/GrantedFileRepository.cpp src/domain/file/repositories/GrantedFileRepository.hpp src/infrastructure/repository/Repository.cpp src/infrastructure/repository/Repository.hpp src/infrastructure/BaseEntity.hpp src/infrastructure/BaseEntity.cpp src/domain/file/services/GrantedFileService.cpp src/domain/file/services/GrantedFileService.hpp)
