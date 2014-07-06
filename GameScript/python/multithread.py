import socket
import time
import struct
import thread
import GameProtocol_pb2
import ClientProtocol

##
count_lock = thread.allocate_lock()

count = 50000
def run():
    global count
    print "thread start"
    
    while True:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
        #sock.connect(('192.168.20.134', 8500))
        sock.connect(('192.168.1.34', 8500))

        count_lock.acquire()
        count += 1
        if count % 100 == 0:
            print count
        count_lock.release()
        
        ClientProtocol.RequestCreateRole(sock, 'test' + str(count), 'test' + str(count))
        ClientProtocol.RequestRoleData(sock, 'test' + str(count))
        
        print 'test' + str(count)
        sock.close()
        #time.sleep(1000)

def doTest():
    i = 0
    while i < 10:
        i = i + 1
        print "create new thread"
        try:
            thread.start_new_thread(run, ())
        except Exception as e:
            print e
        print "after create new thread"

if __name__ == "__main__":
    doTest()    
    time.sleep(1000000)