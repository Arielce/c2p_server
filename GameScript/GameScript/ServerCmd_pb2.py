# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)



DESCRIPTOR = descriptor.FileDescriptor(
  name='ServerCmd.proto',
  package='scmd',
  serialized_pb='\n\x0fServerCmd.proto\x12\x04scmd\"%\n\x11RequestStopServer\x12\x10\n\x08serverId\x18\x01 \x01(\r\"7\n\x11RequestReloadConf\x12\x10\n\x08serverId\x18\x01 \x01(\r\x12\x10\n\x08\x63onfFile\x18\x02 \x01(\t\"%\n\x12ResponseReloadConf\x12\x0f\n\x07\x65rrCode\x18\x01 \x01(\r')




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


_REQUESTRELOADCONF = descriptor.Descriptor(
  name='RequestReloadConf',
  full_name='scmd.RequestReloadConf',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='serverId', full_name='scmd.RequestReloadConf.serverId', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='confFile', full_name='scmd.RequestReloadConf.confFile', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  serialized_start=64,
  serialized_end=119,
)


_RESPONSERELOADCONF = descriptor.Descriptor(
  name='ResponseReloadConf',
  full_name='scmd.ResponseReloadConf',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='errCode', full_name='scmd.ResponseReloadConf.errCode', index=0,
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
  serialized_start=121,
  serialized_end=158,
)

DESCRIPTOR.message_types_by_name['RequestStopServer'] = _REQUESTSTOPSERVER
DESCRIPTOR.message_types_by_name['RequestReloadConf'] = _REQUESTRELOADCONF
DESCRIPTOR.message_types_by_name['ResponseReloadConf'] = _RESPONSERELOADCONF

class RequestStopServer(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _REQUESTSTOPSERVER
  
  # @@protoc_insertion_point(class_scope:scmd.RequestStopServer)

class RequestReloadConf(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _REQUESTRELOADCONF
  
  # @@protoc_insertion_point(class_scope:scmd.RequestReloadConf)

class ResponseReloadConf(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _RESPONSERELOADCONF
  
  # @@protoc_insertion_point(class_scope:scmd.ResponseReloadConf)

# @@protoc_insertion_point(module_scope)