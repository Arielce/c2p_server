import socket
import time
import struct
import thread



count = 0
count_lock = thread.allocate_lock()

def run():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
    sock.connect(('192.168.1.34', 8500))
    
    global count
    while True:
        long_body = 'abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890'
        body = long_body
        header = struct.pack('iii', 12+len(body), 0x0001, 0)
        sock.send(header+body)
        pbstr = sock.recv(1024)
        
        count_lock.acquire()
        count += 1
        if count % 10000 == 0:
            print count
        count_lock.release()
        
    sock.close()  


def doTest():
    try:
        i = 0
        while i < 10:
            i = i + 1
            try:
                thread.start_new_thread(run, ())
            except:
                print "error"
    except:
        print "error"

if __name__=='__main__':
    doTest()
    time.sleep(1000000)