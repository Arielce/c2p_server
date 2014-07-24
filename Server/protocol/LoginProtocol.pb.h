// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LoginProtocol.proto

#ifndef PROTOBUF_LoginProtocol_2eproto__INCLUDED
#define PROTOBUF_LoginProtocol_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace login {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_LoginProtocol_2eproto();
void protobuf_AssignDesc_LoginProtocol_2eproto();
void protobuf_ShutdownFile_LoginProtocol_2eproto();

class SRequestVerifyToken;
class SResponseVerifyToken;

// ===================================================================

class SRequestVerifyToken : public ::google::protobuf::Message {
 public:
  SRequestVerifyToken();
  virtual ~SRequestVerifyToken();
  
  SRequestVerifyToken(const SRequestVerifyToken& from);
  
  inline SRequestVerifyToken& operator=(const SRequestVerifyToken& from) {
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
  static const SRequestVerifyToken& default_instance();
  
  void Swap(SRequestVerifyToken* other);
  
  // implements Message ----------------------------------------------
  
  SRequestVerifyToken* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SRequestVerifyToken& from);
  void MergeFrom(const SRequestVerifyToken& from);
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
  
  // optional string token = 2;
  inline bool has_token() const;
  inline void clear_token();
  static const int kTokenFieldNumber = 2;
  inline const ::std::string& token() const;
  inline void set_token(const ::std::string& value);
  inline void set_token(const char* value);
  inline void set_token(const char* value, size_t size);
  inline ::std::string* mutable_token();
  inline ::std::string* release_token();
  
  // @@protoc_insertion_point(class_scope:login.SRequestVerifyToken)
 private:
  inline void set_has_ptname();
  inline void clear_has_ptname();
  inline void set_has_token();
  inline void clear_has_token();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* ptname_;
  ::std::string* token_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_LoginProtocol_2eproto();
  friend void protobuf_AssignDesc_LoginProtocol_2eproto();
  friend void protobuf_ShutdownFile_LoginProtocol_2eproto();
  
  void InitAsDefaultInstance();
  static SRequestVerifyToken* default_instance_;
};
// -------------------------------------------------------------------

class SResponseVerifyToken : public ::google::protobuf::Message {
 public:
  SResponseVerifyToken();
  virtual ~SResponseVerifyToken();
  
  SResponseVerifyToken(const SResponseVerifyToken& from);
  
  inline SResponseVerifyToken& operator=(const SResponseVerifyToken& from) {
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
  static const SResponseVerifyToken& default_instance();
  
  void Swap(SResponseVerifyToken* other);
  
  // implements Message ----------------------------------------------
  
  SResponseVerifyToken* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SResponseVerifyToken& from);
  void MergeFrom(const SResponseVerifyToken& from);
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
  
  // optional uint32 errCode = 2;
  inline bool has_errcode() const;
  inline void clear_errcode();
  static const int kErrCodeFieldNumber = 2;
  inline ::google::protobuf::uint32 errcode() const;
  inline void set_errcode(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:login.SResponseVerifyToken)
 private:
  inline void set_has_ptname();
  inline void clear_has_ptname();
  inline void set_has_errcode();
  inline void clear_has_errcode();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* ptname_;
  ::google::protobuf::uint32 errcode_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_LoginProtocol_2eproto();
  friend void protobuf_AssignDesc_LoginProtocol_2eproto();
  friend void protobuf_ShutdownFile_LoginProtocol_2eproto();
  
  void InitAsDefaultInstance();
  static SResponseVerifyToken* default_instance_;
};
// ===================================================================


// ===================================================================

// SRequestVerifyToken

// optional string ptName = 1;
inline bool SRequestVerifyToken::has_ptname() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SRequestVerifyToken::set_has_ptname() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SRequestVerifyToken::clear_has_ptname() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SRequestVerifyToken::clear_ptname() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    ptname_->clear();
  }
  clear_has_ptname();
}
inline const ::std::string& SRequestVerifyToken::ptname() const {
  return *ptname_;
}
inline void SRequestVerifyToken::set_ptname(const ::std::string& value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SRequestVerifyToken::set_ptname(const char* value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SRequestVerifyToken::set_ptname(const char* value, size_t size) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SRequestVerifyToken::mutable_ptname() {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  return ptname_;
}
inline ::std::string* SRequestVerifyToken::release_ptname() {
  clear_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ptname_;
    ptname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string token = 2;
inline bool SRequestVerifyToken::has_token() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SRequestVerifyToken::set_has_token() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SRequestVerifyToken::clear_has_token() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SRequestVerifyToken::clear_token() {
  if (token_ != &::google::protobuf::internal::kEmptyString) {
    token_->clear();
  }
  clear_has_token();
}
inline const ::std::string& SRequestVerifyToken::token() const {
  return *token_;
}
inline void SRequestVerifyToken::set_token(const ::std::string& value) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(value);
}
inline void SRequestVerifyToken::set_token(const char* value) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(value);
}
inline void SRequestVerifyToken::set_token(const char* value, size_t size) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SRequestVerifyToken::mutable_token() {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  return token_;
}
inline ::std::string* SRequestVerifyToken::release_token() {
  clear_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = token_;
    token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// SResponseVerifyToken

// optional string ptName = 1;
inline bool SResponseVerifyToken::has_ptname() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SResponseVerifyToken::set_has_ptname() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SResponseVerifyToken::clear_has_ptname() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SResponseVerifyToken::clear_ptname() {
  if (ptname_ != &::google::protobuf::internal::kEmptyString) {
    ptname_->clear();
  }
  clear_has_ptname();
}
inline const ::std::string& SResponseVerifyToken::ptname() const {
  return *ptname_;
}
inline void SResponseVerifyToken::set_ptname(const ::std::string& value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SResponseVerifyToken::set_ptname(const char* value) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(value);
}
inline void SResponseVerifyToken::set_ptname(const char* value, size_t size) {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  ptname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SResponseVerifyToken::mutable_ptname() {
  set_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    ptname_ = new ::std::string;
  }
  return ptname_;
}
inline ::std::string* SResponseVerifyToken::release_ptname() {
  clear_has_ptname();
  if (ptname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ptname_;
    ptname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional uint32 errCode = 2;
inline bool SResponseVerifyToken::has_errcode() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SResponseVerifyToken::set_has_errcode() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SResponseVerifyToken::clear_has_errcode() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SResponseVerifyToken::clear_errcode() {
  errcode_ = 0u;
  clear_has_errcode();
}
inline ::google::protobuf::uint32 SResponseVerifyToken::errcode() const {
  return errcode_;
}
inline void SResponseVerifyToken::set_errcode(::google::protobuf::uint32 value) {
  set_has_errcode();
  errcode_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace login

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_LoginProtocol_2eproto__INCLUDED