package com.message;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MessageHeader {
	public int nMsgSize;
	public int nMsgCmd;
	public int nReserved;
	
	static public byte[] toBytes(MessageHeader header) {
		ByteBuffer bb = ByteBuffer.allocate(12); 
		bb.order(ByteOrder.LITTLE_ENDIAN);					// Ê¹ÓÃlittle¡ªendian
		
	    bb.putInt(header.nMsgSize);
	    bb.putInt(header.nMsgCmd);
	    bb.putInt(0xA1B2C3D4);	
	    
	    return bb.array();
	}
}
