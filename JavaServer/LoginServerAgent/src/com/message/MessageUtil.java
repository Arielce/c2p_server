package com.message;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class MessageUtil {
	//字节序转换, 转换成little-end
    public static byte[] toLH(int n) {
        byte[] b = new byte[4];
        b[0]= (byte)(n & 0xff);
        b[1]= (byte)(n >> 8 & 0xff);
        b[2]= (byte)(n >> 16 & 0xff);
        b[3]= (byte)(n >> 24 & 0xff);
        return b;
    }
    
    public static int bytes2int(byte[] bytes) {
    	int result = 0;
    	for (int i=0; i < bytes.length; i++) {
    		result = result | (bytes[i] << (i * 8));
    	}
    	return result;
    }
    
    public static byte[] toByteArray (Object obj) {      
        byte[] bytes = null;      
        ByteArrayOutputStream bos = new ByteArrayOutputStream();      
        try {        
            ObjectOutputStream oos = new ObjectOutputStream(bos);         
            oos.writeObject(obj);        
            oos.flush();         
            bytes = bos.toByteArray ();      
            oos.close();         
            bos.close();        
        } catch (IOException ex) {        
            ex.printStackTrace();   
        }      
        return bytes;    
    }   
}
