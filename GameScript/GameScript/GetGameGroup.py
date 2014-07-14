import socket
import time
import struct
import GameProtocol_pb2
import ClientProtocol

lobby_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
lobby_sock.connect(('127.0.0.1', 8800))

gamegroupack = ClientProtocol.RequestGameGroup(lobby_sock)
print gamegroupack