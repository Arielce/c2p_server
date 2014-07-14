package com.message;

import java.nio.ByteBuffer;

public class MessageHeader {
	public int nMsgSize;
	public int nMsgCmd;
	public int nReserved;
	
	static public byte[] toBytes(MessageHeader header) {
		ByteBuffer bb = ByteBuffer.allocate(12); 
	    bb.putInt(header.nMsgSize);
	    bb.putInt(header.nMsgCmd);
	    bb.putInt(0xA1B2C3D4);
	    return ToLE(bb.array());
	}
	
	static private void swap(byte b1, byte b2) {
		byte temp = b1;
		b1 = b2;
		b2 = temp;
	}
	
	// ×ª»»³Élittle-end
	static private byte[] ToLE(byte[] bytes) {
		byte[] LEBytes = new byte[bytes.length]; 
		LEBytes[0] = bytes[3];
		LEBytes[1] = bytes[2];
		LEBytes[2] = bytes[1];
		LEBytes[3] = bytes[0];
		
		LEBytes[4] = bytes[7];
		LEBytes[5] = bytes[6];
		LEBytes[6] = bytes[5];
		LEBytes[7] = bytes[4];
		
		LEBytes[8] = bytes[11];
		LEBytes[9] = bytes[10];
		LEBytes[10] = bytes[9];
		LEBytes[11] = bytes[8];
		
		return LEBytes;
	}
}
