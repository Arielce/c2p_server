// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameProtocol.proto

#ifndef PROTOBUF_GameProtocol_2eproto__INCLUDED
#define PROTOBUF_GameProtocol_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "RoleData.pb.h"
// @@protoc_insertion_point(includes)

namespace ctos {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_GameProtocol_2eproto();
void protobuf_AssignDesc_GameProtocol_2eproto();
void protobuf_ShutdownFile_GameProtocol_2eproto();

class RequestRoleData;
class ResponseRoleData;

// ===================================================================

class RequestRoleData : public ::google::protobuf::Message {
 public:
  RequestRoleData();
  virtual ~RequestRoleData();
  
  RequestRoleData(const RequestRoleData& from);
  
  inline RequestRoleData& operator=(const RequestRoleData& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const RequestRoleData& default_instance();
  
  void Swap(RequestRoleData* other);
  
  // implements Message ----------------------------------------------
  
  RequestRoleData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RequestRoleData& from);
  void MergeFrom(const RequestRoleData& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string ptName = 1;
  inline bool has_ptname() const;
  inline void clear_ptname();
  static const int kPtNameFieldNumber = 1;
  inline const ::std::string& ptname() const;
  inline void set_ptname(const ::std::string& value);
  inline void set_ptname(const char* value);
  inline void set_ptname(const char* value, size_t size);
  inline ::std::string* mutable_ptname();
  inline ::std::string* release_ptname();
  
  // @@protoc_insertion_point(class_scope:ctos.RequestRoleData)
 private:
  inline void set_has_ptname();
  inline void clear_has_ptname();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* ptname_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_GameProtocol_2eproto();
  friend void protobuf_AssignDesc_GameProtocol_2eproto();
  friend void protobuf_ShutdownFile_GameProtocol_2eproto();
  
  void InitAsDefaultInstance();
  static RequestRoleData* default_instance_;
};
// -------------------------------------------------------------------

class ResponseRoleData : public ::google::protobuf::Message {
 public:
  ResponseRoleData();
  virtual ~ResponseRoleData();
  
  ResponseRoleData(const ResponseRoleData& from);
  
  inline ResponseRoleData& operator=(const ResponseRoleData& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const ResponseRoleData& default_instance();
  
  void Swap(ResponseRoleData* other);
  
  // implements Message ----------------------------------------------
  
  ResponseRoleData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ResponseRoleData& from);
  void MergeFrom(const ResponseRoleData& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional .roledata.PBRoleBaseInfo roleData = 1;
  inline bool has_roledata() const;
  inline void clear_roledata();
  static const int kRoleDataFieldNumber = 1;
  inline const ::roledata::PBRoleBaseInfo& roledata() const;
  inline ::roledata::PBRoleBaseInfo* mutable_roledata();
  inline ::roledata::PBRoleBaseInfo* release_roledata();
  
  // @@protoc_insertion_point(class_scope:ctos.ResponseRoleData)
 private:
  inline void set_has_roledata();
  inline void clear_has_roledata();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::roledata::PBRoleBaseInfo* roledata_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_GameProtocol_2eproto();
  friend void protobuf_AssignDesc_GameProtocol_2eproto();
  friend void protobuf_ShutdownFile_GameProtocol_2eproto();
  
  void InitAsDefaultInstance();
  static ResponseRoleData* default_instance_;
};
// ===================================================================


// ===================================================================

// RequestRoleData

// optional string ptName = 1;
inline bool RequestRoleData::has_ptname() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RequestRoleData::set_has_ptname() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RequestRoleData::clear_has_ptname() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RequestRoleData::clear_ptname() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    ptname_->clear();
  }
  clear_has_ptname();
}
inline const ::std::string& RequestRoleData::ptname() const {
  return *ptname_;
}
inline void RequestRoleData::set_ptname(const ::std::string& value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void RequestRoleData::set_ptname(const char* value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void RequestRoleData::set_ptname(const char* value, size_t size) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RequestRoleData::mutable_ptname() {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  return ptname_;
}
inline ::std::string* RequestRoleData::release_ptname() {
  clear_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ptname_;
    ptname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// ResponseRoleData

// optional .roledata.PBRoleBaseInfo roleData = 1;
inline bool ResponseRoleData::has_roledata() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ResponseRoleData::set_has_roledata() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ResponseRoleData::clear_has_roledata() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ResponseRoleData::clear_roledata() {
  if (roledata_ != NULL) roledata_->::roledata::PBRoleBaseInfo::Clear();
  clear_has_roledata();
}
inline const ::roledata::PBRoleBaseInfo& ResponseRoleData::roledata() const {
  return roledata_ != NULL ? *roledata_ : *default_instance_->roledata_;
}
inline ::roledata::PBRoleBaseInfo* ResponseRoleData::mutable_roledata() {
  set_has_roledata();
  if (roledata_ == NULL) roledata_ = new ::roledata::PBRoleBaseInfo;
  return roledata_;
}
inline ::roledata::PBRoleBaseInfo* ResponseRoleData::release_roledata() {
  clear_has_roledata();
  ::roledata::PBRoleBaseInfo* temp = roledata_;
  roledata_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ctos

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GameProtocol_2eproto__INCLUDED
