// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "DataServer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace gtod {

namespace {

const ::google::protobuf::Descriptor* SRequestRoleData_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SRequestRoleData_reflection_ = NULL;
const ::google::protobuf::Descriptor* SResponseRoleData_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SResponseRoleData_reflection_ = NULL;
const ::google::protobuf::Descriptor* SRequestSaveRoleData_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SRequestSaveRoleData_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_DataServer_2eproto() {
  protobuf_AddDesc_DataServer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "DataServer.proto");
  GOOGLE_CHECK(file != NULL);
  SRequestRoleData_descriptor_ = file->message_type(0);
  static const int SRequestRoleData_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SRequestRoleData, ptname_),
  };
  SRequestRoleData_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SRequestRoleData_descriptor_,
      SRequestRoleData::default_instance_,
      SRequestRoleData_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SRequestRoleData, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SRequestRoleData, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SRequestRoleData));
  SResponseRoleData_descriptor_ = file->message_type(1);
  static const int SResponseRoleData_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SResponseRoleData, roledata_),
  };
  SResponseRoleData_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SResponseRoleData_descriptor_,
      SResponseRoleData::default_instance_,
      SResponseRoleData_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SResponseRoleData, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SResponseRoleData, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SResponseRoleData));
  SRequestSaveRoleData_descriptor_ = file->message_type(2);
  static const int SRequestSaveRoleData_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SRequestSaveRoleData, ptname_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SRequestSaveRoleData, roledata_),
  };
  SRequestSaveRoleData_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SRequestSaveRoleData_descriptor_,
      SRequestSaveRoleData::default_instance_,
      SRequestSaveRoleData_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SRequestSaveRoleData, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SRequestSaveRoleData, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SRequestSaveRoleData));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_DataServer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SRequestRoleData_descriptor_, &SRequestRoleData::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SResponseRoleData_descriptor_, &SResponseRoleData::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SRequestSaveRoleData_descriptor_, &SRequestSaveRoleData::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_DataServer_2eproto() {
  delete SRequestRoleData::default_instance_;
  delete SRequestRoleData_reflection_;
  delete SResponseRoleData::default_instance_;
  delete SResponseRoleData_reflection_;
  delete SRequestSaveRoleData::default_instance_;
  delete SRequestSaveRoleData_reflection_;
}

void protobuf_AddDesc_DataServer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::roledata::protobuf_AddDesc_RoleData_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020DataServer.proto\022\004gtod\032\016RoleData.proto"
    "\"\"\n\020SRequestRoleData\022\016\n\006ptName\030\001 \001(\t\"@\n\021"
    "SResponseRoleData\022+\n\010roleData\030\001 \001(\0132\031.ro"
    "ledata.PBRoleTotalInfo\"S\n\024SRequestSaveRo"
    "leData\022\016\n\006ptName\030\001 \001(\t\022+\n\010roleData\030\002 \001(\013"
    "2\031.roledata.PBRoleTotalInfo", 227);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "DataServer.proto", &protobuf_RegisterTypes);
  SRequestRoleData::default_instance_ = new SRequestRoleData();
  SResponseRoleData::default_instance_ = new SResponseRoleData();
  SRequestSaveRoleData::default_instance_ = new SRequestSaveRoleData();
  SRequestRoleData::default_instance_->InitAsDefaultInstance();
  SResponseRoleData::default_instance_->InitAsDefaultInstance();
  SRequestSaveRoleData::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_DataServer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_DataServer_2eproto {
  StaticDescriptorInitializer_DataServer_2eproto() {
    protobuf_AddDesc_DataServer_2eproto();
  }
} static_descriptor_initializer_DataServer_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int SRequestRoleData::kPtNameFieldNumber;
#endif  // !_MSC_VER

SRequestRoleData::SRequestRoleData()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SRequestRoleData::InitAsDefaultInstance() {
}

SRequestRoleData::SRequestRoleData(const SRequestRoleData& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SRequestRoleData::SharedCtor() {
  _cached_size_ = 0;
  ptname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SRequestRoleData::~SRequestRoleData() {
  SharedDtor();
}

void SRequestRoleData::SharedDtor() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    delete ptname_;
  }
  if (this != default_instance_) {
  }
}

void SRequestRoleData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SRequestRoleData::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SRequestRoleData_descriptor_;
}

const SRequestRoleData& SRequestRoleData::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_DataServer_2eproto();  return *default_instance_;
}

SRequestRoleData* SRequestRoleData::default_instance_ = NULL;

SRequestRoleData* SRequestRoleData::New() const {
  return new SRequestRoleData;
}

void SRequestRoleData::Clear() {
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

bool SRequestRoleData::MergePartialFromCodedStream(
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

void SRequestRoleData::SerializeWithCachedSizes(
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

::google::protobuf::uint8* SRequestRoleData::SerializeWithCachedSizesToArray(
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

int SRequestRoleData::ByteSize() const {
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

void SRequestRoleData::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SRequestRoleData* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SRequestRoleData*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SRequestRoleData::MergeFrom(const SRequestRoleData& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ptname()) {
      set_ptname(from.ptname());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SRequestRoleData::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SRequestRoleData::CopyFrom(const SRequestRoleData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SRequestRoleData::IsInitialized() const {
  
  return true;
}

void SRequestRoleData::Swap(SRequestRoleData* other) {
  if (other != this) {
    std::swap(ptname_, other->ptname_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SRequestRoleData::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SRequestRoleData_descriptor_;
  metadata.reflection = SRequestRoleData_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int SResponseRoleData::kRoleDataFieldNumber;
#endif  // !_MSC_VER

SResponseRoleData::SResponseRoleData()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SResponseRoleData::InitAsDefaultInstance() {
  roledata_ = const_cast< ::roledata::PBRoleTotalInfo*>(&::roledata::PBRoleTotalInfo::default_instance());
}

SResponseRoleData::SResponseRoleData(const SResponseRoleData& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SResponseRoleData::SharedCtor() {
  _cached_size_ = 0;
  roledata_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SResponseRoleData::~SResponseRoleData() {
  SharedDtor();
}

void SResponseRoleData::SharedDtor() {
  if (this != default_instance_) {
    delete roledata_;
  }
}

void SResponseRoleData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SResponseRoleData::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SResponseRoleData_descriptor_;
}

const SResponseRoleData& SResponseRoleData::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_DataServer_2eproto();  return *default_instance_;
}

SResponseRoleData* SResponseRoleData::default_instance_ = NULL;

SResponseRoleData* SResponseRoleData::New() const {
  return new SResponseRoleData;
}

void SResponseRoleData::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_roledata()) {
      if (roledata_ != NULL) roledata_->::roledata::PBRoleTotalInfo::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SResponseRoleData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .roledata.PBRoleTotalInfo roleData = 1;
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

void SResponseRoleData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .roledata.PBRoleTotalInfo roleData = 1;
  if (has_roledata()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->roledata(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SResponseRoleData::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .roledata.PBRoleTotalInfo roleData = 1;
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

int SResponseRoleData::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .roledata.PBRoleTotalInfo roleData = 1;
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

void SResponseRoleData::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SResponseRoleData* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SResponseRoleData*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SResponseRoleData::MergeFrom(const SResponseRoleData& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_roledata()) {
      mutable_roledata()->::roledata::PBRoleTotalInfo::MergeFrom(from.roledata());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SResponseRoleData::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SResponseRoleData::CopyFrom(const SResponseRoleData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SResponseRoleData::IsInitialized() const {
  
  return true;
}

void SResponseRoleData::Swap(SResponseRoleData* other) {
  if (other != this) {
    std::swap(roledata_, other->roledata_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SResponseRoleData::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SResponseRoleData_descriptor_;
  metadata.reflection = SResponseRoleData_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int SRequestSaveRoleData::kPtNameFieldNumber;
const int SRequestSaveRoleData::kRoleDataFieldNumber;
#endif  // !_MSC_VER

SRequestSaveRoleData::SRequestSaveRoleData()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SRequestSaveRoleData::InitAsDefaultInstance() {
  roledata_ = const_cast< ::roledata::PBRoleTotalInfo*>(&::roledata::PBRoleTotalInfo::default_instance());
}

SRequestSaveRoleData::SRequestSaveRoleData(const SRequestSaveRoleData& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SRequestSaveRoleData::SharedCtor() {
  _cached_size_ = 0;
  ptname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  roledata_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SRequestSaveRoleData::~SRequestSaveRoleData() {
  SharedDtor();
}

void SRequestSaveRoleData::SharedDtor() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    delete ptname_;
  }
  if (this != default_instance_) {
    delete roledata_;
  }
}

void SRequestSaveRoleData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SRequestSaveRoleData::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SRequestSaveRoleData_descriptor_;
}

const SRequestSaveRoleData& SRequestSaveRoleData::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_DataServer_2eproto();  return *default_instance_;
}

SRequestSaveRoleData* SRequestSaveRoleData::default_instance_ = NULL;

SRequestSaveRoleData* SRequestSaveRoleData::New() const {
  return new SRequestSaveRoleData;
}

void SRequestSaveRoleData::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_ptname()) {
      if (ptname_ != &::google::protobuf::internal::kEmptyString) {
        ptname_->clear();
      }
    }
    if (has_roledata()) {
      if (roledata_ != NULL) roledata_->::roledata::PBRoleTotalInfo::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SRequestSaveRoleData::MergePartialFromCodedStream(
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
        if (input->ExpectTag(18)) goto parse_roleData;
        break;
      }
      
      // optional .roledata.PBRoleTotalInfo roleData = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_roleData:
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

void SRequestSaveRoleData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string ptName = 1;
  if (has_ptname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->ptname().data(), this->ptname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->ptname(), output);
  }
  
  // optional .roledata.PBRoleTotalInfo roleData = 2;
  if (has_roledata()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->roledata(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SRequestSaveRoleData::SerializeWithCachedSizesToArray(
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
  
  // optional .roledata.PBRoleTotalInfo roleData = 2;
  if (has_roledata()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->roledata(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int SRequestSaveRoleData::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string ptName = 1;
    if (has_ptname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->ptname());
    }
    
    // optional .roledata.PBRoleTotalInfo roleData = 2;
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

void SRequestSaveRoleData::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SRequestSaveRoleData* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SRequestSaveRoleData*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SRequestSaveRoleData::MergeFrom(const SRequestSaveRoleData& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ptname()) {
      set_ptname(from.ptname());
    }
    if (from.has_roledata()) {
      mutable_roledata()->::roledata::PBRoleTotalInfo::MergeFrom(from.roledata());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SRequestSaveRoleData::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SRequestSaveRoleData::CopyFrom(const SRequestSaveRoleData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SRequestSaveRoleData::IsInitialized() const {
  
  return true;
}

void SRequestSaveRoleData::Swap(SRequestSaveRoleData* other) {
  if (other != this) {
    std::swap(ptname_, other->ptname_);
    std::swap(roledata_, other->roledata_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SRequestSaveRoleData::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SRequestSaveRoleData_descriptor_;
  metadata.reflection = SRequestSaveRoleData_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gtod

// @@protoc_insertion_point(global_scope)
