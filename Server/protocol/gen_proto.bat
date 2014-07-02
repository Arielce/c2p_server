.\protoc.exe GameProtocol.proto --cpp_out=./
.\protoc.exe RoleData.proto --cpp_out=./
.\protoc.exe DataServer.proto --cpp_out=./
.\protoc.exe LobbyProtocol.proto --cpp_out=./
.\protoc.exe ServerCmd.proto --cpp_out=./

.\protoc.exe GameProtocol.proto --python_out=./python/
.\protoc.exe RoleData.proto --python_out=./python/
.\protoc.exe DataServer.proto --python_out=./python/
.\protoc.exe LobbyProtocol.proto --python_out=./python/
.\protoc.exe ServerCmd.proto --python_out=./python/

pause()