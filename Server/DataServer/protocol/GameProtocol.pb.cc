// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GameProtocol.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ctos {

namespace {

const ::google::protobuf::Descriptor* RequestRoleData_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RequestRoleData_reflection_ = NULL;
const ::google::protobuf::Descriptor* ResponseRoleData_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ResponseRoleData_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_GameProtocol_2eproto() {
  protobuf_AddDesc_GameProtocol_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "GameProtocol.proto");
  GOOGLE_CHECK(file != NULL);
  RequestRoleData_descriptor_ = file->message_type(0);
  static const int RequestRoleData_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RequestRoleData, ptname_),
  };
  RequestRoleData_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RequestRoleData_descriptor_,
      RequestRoleData::default_instance_,
      RequestRoleData_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RequestRoleData, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RequestRoleData, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RequestRoleData));
  ResponseRoleData_descriptor_ = file->message_type(1);
  static const int ResponseRoleData_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResponseRoleData, roledata_),
  };
  ResponseRoleData_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ResponseRoleData_descriptor_,
      ResponseRoleData::default_instance_,
      ResponseRoleData_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResponseRoleData, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResponseRoleData, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ResponseRoleData));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_GameProtocol_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RequestRoleData_descriptor_, &RequestRoleData::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ResponseRoleData_descriptor_, &ResponseRoleData::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_GameProtocol_2eproto() {
  delete RequestRoleData::default_instance_;
  delete RequestRoleData_reflection_;
  delete ResponseRoleData::default_instance_;
  delete ResponseRoleData_reflection_;
}

void protobuf_AddDesc_GameProtocol_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::roledata::protobuf_AddDesc_RoleData_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022GameProtocol.proto\022\004ctos\032\016RoleData.pro"
    "to\"!\n\017RequestRoleData\022\016\n\006ptName\030\001 \001(\t\">\n"
    "\020ResponseRoleData\022*\n\010roleData\030\001 \001(\0132\030.ro"
    "ledata.PBRoleBaseInfo", 141);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "GameProtocol.proto", &protobuf_RegisterTypes);
  RequestRoleData::default_instance_ = new RequestRoleData();
  ResponseRoleData::default_instance_ = new ResponseRoleData();
  RequestRoleData::default_instance_->InitAsDefaultInstance();
  ResponseRoleData::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GameProtocol_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GameProtocol_2eproto {
  StaticDescriptorInitializer_GameProtocol_2eproto() {
    protobuf_AddDesc_GameProtocol_2eproto();
  }
} static_descriptor_initializer_GameProtocol_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int RequestRoleData::kPtNameFieldNumber;
#endif  // !_MSC_VER

RequestRoleData::RequestRoleData()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RequestRoleData::InitAsDefaultInstance() {
}

RequestRoleData::RequestRoleData(const RequestRoleData& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RequestRoleData::SharedCtor() {
  _cached_size_ = 0;
  ptname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RequestRoleData::~RequestRoleData() {
  SharedDtor();
}

void RequestRoleData::SharedDtor() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    delete ptname_;
  }
  if (this != default_instance_) {
  }
}

void RequestRoleData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RequestRoleData::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RequestRoleData_descriptor_;
}

const RequestRoleData& RequestRoleData::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GameProtocol_2eproto();  return *default_instance_;
}

RequestRoleData* RequestRoleData::default_instance_ = NULL;

RequestRoleData* RequestRoleData::New() const {
  return new RequestRoleData;
}

void RequestRoleData::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_ptname()) {
      if (ptname_ != &::google::protobuf::internal::kEmptyString) {
        ptname_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RequestRoleData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string ptName = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_ptname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->ptname().data(), this->ptname().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
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

void RequestRoleData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string ptName = 1;
  if (has_ptname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->ptname().data(), this->ptname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->ptname(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RequestRoleData::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string ptName = 1;
  if (has_ptname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->ptname().data(), this->ptname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->ptname(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RequestRoleData::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string ptName = 1;
    if (has_ptname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->ptname());
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

void RequestRoleData::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RequestRoleData* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RequestRoleData*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RequestRoleData::MergeFrom(const RequestRoleData& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ptname()) {
      set_ptname(from.ptname());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RequestRoleData::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RequestRoleData::CopyFrom(const RequestRoleData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RequestRoleData::IsInitialized() const {
  
  return true;
}

void RequestRoleData::Swap(RequestRoleData* other) {
  if (other != this) {
    std::swap(ptname_, other->ptname_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RequestRoleData::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RequestRoleData_descriptor_;
  metadata.reflection = RequestRoleData_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ResponseRoleData::kRoleDataFieldNumber;
#endif  // !_MSC_VER

ResponseRoleData::ResponseRoleData()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ResponseRoleData::InitAsDefaultInstance() {
  roledata_ = const_cast< ::roledata::PBRoleBaseInfo*>(&::roledata::PBRoleBaseInfo::default_instance());
}

ResponseRoleData::ResponseRoleData(const ResponseRoleData& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ResponseRoleData::SharedCtor() {
  _cached_size_ = 0;
  roledata_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ResponseRoleData::~ResponseRoleData() {
  SharedDtor();
}

void ResponseRoleData::SharedDtor() {
  if (this != default_instance_) {
    delete roledata_;
  }
}

void ResponseRoleData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ResponseRoleData::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ResponseRoleData_descriptor_;
}

const ResponseRoleData& ResponseRoleData::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GameProtocol_2eproto();  return *default_instance_;
}

ResponseRoleData* ResponseRoleData::default_instance_ = NULL;

ResponseRoleData* ResponseRoleData::New() const {
  return new ResponseRoleData;
}

void ResponseRoleData::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_roledata()) {
      if (roledata_ != NULL) roledata_->::roledata::PBRoleBaseInfo::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ResponseRoleData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .roledata.PBRoleBaseInfo roleData = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_roledata()));
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

void ResponseRoleData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .roledata.PBRoleBaseInfo roleData = 1;
  if (has_roledata()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->roledata(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ResponseRoleData::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .roledata.PBRoleBaseInfo roleData = 1;
  if (has_roledata()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->roledata(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ResponseRoleData::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .roledata.PBRoleBaseInfo roleData = 1;
    if (has_roledata()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->roledata());
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

void ResponseRoleData::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ResponseRoleData* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ResponseRoleData*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ResponseRoleData::MergeFrom(const ResponseRoleData& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_roledata()) {
      mutable_roledata()->::roledata::PBRoleBaseInfo::MergeFrom(from.roledata());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ResponseRoleData::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResponseRoleData::CopyFrom(const ResponseRoleData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResponseRoleData::IsInitialized() const {
  
  return true;
}

void ResponseRoleData::Swap(ResponseRoleData* other) {
  if (other != this) {
    std::swap(roledata_, other->roledata_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ResponseRoleData::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ResponseRoleData_descriptor_;
  metadata.reflection = ResponseRoleData_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ctos

// @@protoc_insertion_point(global_scope)
