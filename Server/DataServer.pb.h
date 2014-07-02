// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataServer.proto

#ifndef PROTOBUF_DataServer_2eproto__INCLUDED
#define PROTOBUF_DataServer_2eproto__INCLUDED

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

namespace gtod {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_DataServer_2eproto();
void protobuf_AssignDesc_DataServer_2eproto();
void protobuf_ShutdownFile_DataServer_2eproto();

class SRequestRoleData;
class SResponseRoleData;
class SRequestSaveRoleData;

// ===================================================================

class SRequestRoleData : public ::google::protobuf::Message {
 public:
  SRequestRoleData();
  virtual ~SRequestRoleData();
  
  SRequestRoleData(const SRequestRoleData& from);
  
  inline SRequestRoleData& operator=(const SRequestRoleData& from) {
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
  static const SRequestRoleData& default_instance();
  
  void Swap(SRequestRoleData* other);
  
  // implements Message ----------------------------------------------
  
  SRequestRoleData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SRequestRoleData& from);
  void MergeFrom(const SRequestRoleData& from);
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
  
  // @@protoc_insertion_point(class_scope:gtod.SRequestRoleData)
 private:
  inline void set_has_ptname();
  inline void clear_has_ptname();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* ptname_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataServer_2eproto();
  friend void protobuf_AssignDesc_DataServer_2eproto();
  friend void protobuf_ShutdownFile_DataServer_2eproto();
  
  void InitAsDefaultInstance();
  static SRequestRoleData* default_instance_;
};
// -------------------------------------------------------------------

class SResponseRoleData : public ::google::protobuf::Message {
 public:
  SResponseRoleData();
  virtual ~SResponseRoleData();
  
  SResponseRoleData(const SResponseRoleData& from);
  
  inline SResponseRoleData& operator=(const SResponseRoleData& from) {
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
  static const SResponseRoleData& default_instance();
  
  void Swap(SResponseRoleData* other);
  
  // implements Message ----------------------------------------------
  
  SResponseRoleData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SResponseRoleData& from);
  void MergeFrom(const SResponseRoleData& from);
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
  
  // optional .roledata.PBRoleTotalInfo roleData = 1;
  inline bool has_roledata() const;
  inline void clear_roledata();
  static const int kRoleDataFieldNumber = 1;
  inline const ::roledata::PBRoleTotalInfo& roledata() const;
  inline ::roledata::PBRoleTotalInfo* mutable_roledata();
  inline ::roledata::PBRoleTotalInfo* release_roledata();
  
  // @@protoc_insertion_point(class_scope:gtod.SResponseRoleData)
 private:
  inline void set_has_roledata();
  inline void clear_has_roledata();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::roledata::PBRoleTotalInfo* roledata_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataServer_2eproto();
  friend void protobuf_AssignDesc_DataServer_2eproto();
  friend void protobuf_ShutdownFile_DataServer_2eproto();
  
  void InitAsDefaultInstance();
  static SResponseRoleData* default_instance_;
};
// -------------------------------------------------------------------

class SRequestSaveRoleData : public ::google::protobuf::Message {
 public:
  SRequestSaveRoleData();
  virtual ~SRequestSaveRoleData();
  
  SRequestSaveRoleData(const SRequestSaveRoleData& from);
  
  inline SRequestSaveRoleData& operator=(const SRequestSaveRoleData& from) {
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
  static const SRequestSaveRoleData& default_instance();
  
  void Swap(SRequestSaveRoleData* other);
  
  // implements Message ----------------------------------------------
  
  SRequestSaveRoleData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SRequestSaveRoleData& from);
  void MergeFrom(const SRequestSaveRoleData& from);
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
  
  // optional .roledata.PBRoleTotalInfo roleData = 2;
  inline bool has_roledata() const;
  inline void clear_roledata();
  static const int kRoleDataFieldNumber = 2;
  inline const ::roledata::PBRoleTotalInfo& roledata() const;
  inline ::roledata::PBRoleTotalInfo* mutable_roledata();
  inline ::roledata::PBRoleTotalInfo* release_roledata();
  
  // @@protoc_insertion_point(class_scope:gtod.SRequestSaveRoleData)
 private:
  inline void set_has_ptname();
  inline void clear_has_ptname();
  inline void set_has_roledata();
  inline void clear_has_roledata();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* ptname_;
  ::roledata::PBRoleTotalInfo* roledata_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataServer_2eproto();
  friend void protobuf_AssignDesc_DataServer_2eproto();
  friend void protobuf_ShutdownFile_DataServer_2eproto();
  
  void InitAsDefaultInstance();
  static SRequestSaveRoleData* default_instance_;
};
// ===================================================================


// ===================================================================

// SRequestRoleData

// optional string ptName = 1;
inline bool SRequestRoleData::has_ptname() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SRequestRoleData::set_has_ptname() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SRequestRoleData::clear_has_ptname() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SRequestRoleData::clear_ptname() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    ptname_->clear();
  }
  clear_has_ptname();
}
inline const ::std::string& SRequestRoleData::ptname() const {
  return *ptname_;
}
inline void SRequestRoleData::set_ptname(const ::std::string& value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SRequestRoleData::set_ptname(const char* value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SRequestRoleData::set_ptname(const char* value, size_t size) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SRequestRoleData::mutable_ptname() {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  return ptname_;
}
inline ::std::string* SRequestRoleData::release_ptname() {
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

// SResponseRoleData

// optional .roledata.PBRoleTotalInfo roleData = 1;
inline bool SResponseRoleData::has_roledata() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SResponseRoleData::set_has_roledata() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SResponseRoleData::clear_has_roledata() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SResponseRoleData::clear_roledata() {
  if (roledata_ != NULL) roledata_->::roledata::PBRoleTotalInfo::Clear();
  clear_has_roledata();
}
inline const ::roledata::PBRoleTotalInfo& SResponseRoleData::roledata() const {
  return roledata_ != NULL ? *roledata_ : *default_instance_->roledata_;
}
inline ::roledata::PBRoleTotalInfo* SResponseRoleData::mutable_roledata() {
  set_has_roledata();
  if (roledata_ == NULL) roledata_ = new ::roledata::PBRoleTotalInfo;
  return roledata_;
}
inline ::roledata::PBRoleTotalInfo* SResponseRoleData::release_roledata() {
  clear_has_roledata();
  ::roledata::PBRoleTotalInfo* temp = roledata_;
  roledata_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// SRequestSaveRoleData

// optional string ptName = 1;
inline bool SRequestSaveRoleData::has_ptname() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SRequestSaveRoleData::set_has_ptname() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SRequestSaveRoleData::clear_has_ptname() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SRequestSaveRoleData::clear_ptname() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    ptname_->clear();
  }
  clear_has_ptname();
}
inline const ::std::string& SRequestSaveRoleData::ptname() const {
  return *ptname_;
}
inline void SRequestSaveRoleData::set_ptname(const ::std::string& value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SRequestSaveRoleData::set_ptname(const char* value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SRequestSaveRoleData::set_ptname(const char* value, size_t size) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SRequestSaveRoleData::mutable_ptname() {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  return ptname_;
}
inline ::std::string* SRequestSaveRoleData::release_ptname() {
  clear_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ptname_;
    ptname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional .roledata.PBRoleTotalInfo roleData = 2;
inline bool SRequestSaveRoleData::has_roledata() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SRequestSaveRoleData::set_has_roledata() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SRequestSaveRoleData::clear_has_roledata() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SRequestSaveRoleData::clear_roledata() {
  if (roledata_ != NULL) roledata_->::roledata::PBRoleTotalInfo::Clear();
  clear_has_roledata();
}
inline const ::roledata::PBRoleTotalInfo& SRequestSaveRoleData::roledata() const {
  return roledata_ != NULL ? *roledata_ : *default_instance_->roledata_;
}
inline ::roledata::PBRoleTotalInfo* SRequestSaveRoleData::mutable_roledata() {
  set_has_roledata();
  if (roledata_ == NULL) roledata_ = new ::roledata::PBRoleTotalInfo;
  return roledata_;
}
inline ::roledata::PBRoleTotalInfo* SRequestSaveRoleData::release_roledata() {
  clear_has_roledata();
  ::roledata::PBRoleTotalInfo* temp = roledata_;
  roledata_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gtod

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DataServer_2eproto__INCLUDED
