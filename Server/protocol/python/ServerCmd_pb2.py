# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)



DESCRIPTOR = descriptor.FileDescriptor(
  name='ServerCmd.proto',
  package='scmd',
  serialized_pb='\n\x0fServerCmd.proto\x12\x04scmd\"%\n\x11RequestStopServer\x12\x10\n\x08serverId\x18\x01 \x01(\r')




_REQUESTSTOPSERVER = descriptor.Descriptor(
  name='RequestStopServer',
  full_name='scmd.RequestStopServer',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='serverId', full_name='scmd.RequestStopServer.serverId', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=25,
  serialized_end=62,
)

DESCRIPTOR.message_types_by_name['RequestStopServer'] = _REQUESTSTOPSERVER

class RequestStopServer(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _REQUESTSTOPSERVER
  
  # @@protoc_insertion_point(class_scope:scmd.RequestStopServer)

# @@protoc_insertion_point(module_scope)
