// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ServerCmd.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace scmd {

namespace {

const ::google::protobuf::Descriptor* RequestStopServer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RequestStopServer_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ServerCmd_2eproto() {
  protobuf_AddDesc_ServerCmd_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ServerCmd.proto");
  GOOGLE_CHECK(file != NULL);
  RequestStopServer_descriptor_ = file->message_type(0);
  static const int RequestStopServer_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RequestStopServer, serverid_),
  };
  RequestStopServer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RequestStopServer_descriptor_,
      RequestStopServer::default_instance_,
      RequestStopServer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RequestStopServer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RequestStopServer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RequestStopServer));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ServerCmd_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RequestStopServer_descriptor_, &RequestStopServer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ServerCmd_2eproto() {
  delete RequestStopServer::default_instance_;
  delete RequestStopServer_reflection_;
}

void protobuf_AddDesc_ServerCmd_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017ServerCmd.proto\022\004scmd\"%\n\021RequestStopSe"
    "rver\022\020\n\010serverId\030\001 \001(\r", 62);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ServerCmd.proto", &protobuf_RegisterTypes);
  RequestStopServer::default_instance_ = new RequestStopServer();
  RequestStopServer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ServerCmd_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ServerCmd_2eproto {
  StaticDescriptorInitializer_ServerCmd_2eproto() {
    protobuf_AddDesc_ServerCmd_2eproto();
  }
} static_descriptor_initializer_ServerCmd_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int RequestStopServer::kServerIdFieldNumber;
#endif  // !_MSC_VER

RequestStopServer::RequestStopServer()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RequestStopServer::InitAsDefaultInstance() {
}

RequestStopServer::RequestStopServer(const RequestStopServer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RequestStopServer::SharedCtor() {
  _cached_size_ = 0;
  serverid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RequestStopServer::~RequestStopServer() {
  SharedDtor();
}

void RequestStopServer::SharedDtor() {
  if (this != default_instance_) {
  }
}

void RequestStopServer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RequestStopServer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RequestStopServer_descriptor_;
}

const RequestStopServer& RequestStopServer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ServerCmd_2eproto();  return *default_instance_;
}

RequestStopServer* RequestStopServer::default_instance_ = NULL;

RequestStopServer* RequestStopServer::New() const {
  return new RequestStopServer;
}

void RequestStopServer::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    serverid_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RequestStopServer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 serverId = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &serverid_)));
          set_has_serverid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void RequestStopServer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 serverId = 1;
  if (has_serverid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->serverid(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RequestStopServer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 serverId = 1;
  if (has_serverid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->serverid(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RequestStopServer::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 serverId = 1;
    if (has_serverid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->serverid());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void RequestStopServer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RequestStopServer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RequestStopServer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RequestStopServer::MergeFrom(const RequestStopServer& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_serverid()) {
      set_serverid(from.serverid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RequestStopServer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RequestStopServer::CopyFrom(const RequestStopServer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RequestStopServer::IsInitialized() const {
  
  return true;
}

void RequestStopServer::Swap(RequestStopServer* other) {
  if (other != this) {
    std::swap(serverid_, other->serverid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RequestStopServer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RequestStopServer_descriptor_;
  metadata.reflection = RequestStopServer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace scmd

// @@protoc_insertion_point(global_scope)
