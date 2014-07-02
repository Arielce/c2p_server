protoc GameProtocol.proto --cpp_out=./
protoc RoleData.proto --cpp_out=./
protoc LobbyProtocol.proto --cpp_out=./
protoc DataServer.proto --cpp_out=./

cp GameProtocol.pb.h ../GameServer/GameProtocol.pb.h
cp GameProtocol.pb.cc ../GameServer/GameProtocol.pb.cpp
cp RoleData.pb.h ../GameServer/RoleData.pb.h
cp RoleData.pb.cc ../GameServer/RoleData.pb.cpp
cp LobbyProtocol.pb.h ../GameServer/LobbyProtocol.pb.h
cp LobbyProtocol.pb.cc ../GameServer/LobbyProtocol.pb.cpp
cp DataServer.pb.h ../GameServer/DataServer.pb.h
cp DataServer.pb.cc ../GameServer/DataServer.pb.cpp

cp GameProtocol.pb.h ../DataServer/GameProtocol.pb.h
cp GameProtocol.pb.cc ../DataServer/GameProtocol.pb.cpp
cp RoleData.pb.h ../DataServer/RoleData.pb.h
cp RoleData.pb.cc ../DataServer/RoleData.pb.cpp
cp LobbyProtocol.pb.h ../DataServer/LobbyProtocol.pb.h
cp LobbyProtocol.pb.cc ../DataServer/LobbyProtocol.pb.cpp
cp DataServer.pb.h ../DataServer/DataServer.pb.h
cp DataServer.pb.cc ../DataServer/DataServer.pb.cpp

cp GameProtocol.pb.h ../LobbyServer/GameProtocol.pb.h
cp GameProtocol.pb.cc ../LobbyServer/GameProtocol.pb.cpp
cp RoleData.pb.h ../LobbyServer/RoleData.pb.h
cp RoleData.pb.cc ../LobbyServer/RoleData.pb.cpp
cp LobbyProtocol.pb.h ../LobbyServer/LobbyProtocol.pb.h
cp LobbyProtocol.pb.cc ../LobbyServer/LobbyProtocol.pb.cpp
cp DataServer.pb.h ../LobbyServer/DataServer.pb.h
cp DataServer.pb.cc ../LobbyServer/DataServer.pb.cpp

