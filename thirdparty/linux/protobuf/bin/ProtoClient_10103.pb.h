// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoClient_10103.proto

#ifndef PROTOBUF_INCLUDED_ProtoClient_5f10103_2eproto
#define PROTOBUF_INCLUDED_ProtoClient_5f10103_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "ProtoPublic.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ProtoClient_5f10103_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_ProtoClient_5f10103_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_ProtoClient_5f10103_2eproto();
class Proto10103001;
class Proto10103001DefaultTypeInternal;
extern Proto10103001DefaultTypeInternal _Proto10103001_default_instance_;
class Proto10103003;
class Proto10103003DefaultTypeInternal;
extern Proto10103003DefaultTypeInternal _Proto10103003_default_instance_;
class Proto80103002;
class Proto80103002DefaultTypeInternal;
extern Proto80103002DefaultTypeInternal _Proto80103002_default_instance_;
namespace google {
namespace protobuf {
template<> ::Proto10103001* Arena::CreateMaybeMessage<::Proto10103001>(Arena*);
template<> ::Proto10103003* Arena::CreateMaybeMessage<::Proto10103003>(Arena*);
template<> ::Proto80103002* Arena::CreateMaybeMessage<::Proto80103002>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class Proto10103001 :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Proto10103001) */ {
 public:
  Proto10103001();
  virtual ~Proto10103001();

  Proto10103001(const Proto10103001& from);

  inline Proto10103001& operator=(const Proto10103001& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Proto10103001(Proto10103001&& from) noexcept
    : Proto10103001() {
    *this = ::std::move(from);
  }

  inline Proto10103001& operator=(Proto10103001&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Proto10103001& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Proto10103001* internal_default_instance() {
    return reinterpret_cast<const Proto10103001*>(
               &_Proto10103001_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Proto10103001* other);
  friend void swap(Proto10103001& a, Proto10103001& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Proto10103001* New() const final {
    return CreateMaybeMessage<Proto10103001>(nullptr);
  }

  Proto10103001* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Proto10103001>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Proto10103001& from);
  void MergeFrom(const Proto10103001& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Proto10103001* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 type = 1;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Proto10103001)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 type_;
  friend struct ::TableStruct_ProtoClient_5f10103_2eproto;
};
// -------------------------------------------------------------------

class Proto80103002 :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Proto80103002) */ {
 public:
  Proto80103002();
  virtual ~Proto80103002();

  Proto80103002(const Proto80103002& from);

  inline Proto80103002& operator=(const Proto80103002& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Proto80103002(Proto80103002&& from) noexcept
    : Proto80103002() {
    *this = ::std::move(from);
  }

  inline Proto80103002& operator=(Proto80103002&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Proto80103002& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Proto80103002* internal_default_instance() {
    return reinterpret_cast<const Proto80103002*>(
               &_Proto80103002_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Proto80103002* other);
  friend void swap(Proto80103002& a, Proto80103002& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Proto80103002* New() const final {
    return CreateMaybeMessage<Proto80103002>(nullptr);
  }

  Proto80103002* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Proto80103002>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Proto80103002& from);
  void MergeFrom(const Proto80103002& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Proto80103002* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .ProtoItem item_list = 2;
  int item_list_size() const;
  void clear_item_list();
  static const int kItemListFieldNumber = 2;
  ::ProtoItem* mutable_item_list(int index);
  ::google::protobuf::RepeatedPtrField< ::ProtoItem >*
      mutable_item_list();
  const ::ProtoItem& item_list(int index) const;
  ::ProtoItem* add_item_list();
  const ::google::protobuf::RepeatedPtrField< ::ProtoItem >&
      item_list() const;

  // optional int32 type = 1;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Proto80103002)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ProtoItem > item_list_;
  ::google::protobuf::int32 type_;
  friend struct ::TableStruct_ProtoClient_5f10103_2eproto;
};
// -------------------------------------------------------------------

class Proto10103003 :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Proto10103003) */ {
 public:
  Proto10103003();
  virtual ~Proto10103003();

  Proto10103003(const Proto10103003& from);

  inline Proto10103003& operator=(const Proto10103003& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Proto10103003(Proto10103003&& from) noexcept
    : Proto10103003() {
    *this = ::std::move(from);
  }

  inline Proto10103003& operator=(Proto10103003&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Proto10103003& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Proto10103003* internal_default_instance() {
    return reinterpret_cast<const Proto10103003*>(
               &_Proto10103003_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Proto10103003* other);
  friend void swap(Proto10103003& a, Proto10103003& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Proto10103003* New() const final {
    return CreateMaybeMessage<Proto10103003>(nullptr);
  }

  Proto10103003* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Proto10103003>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Proto10103003& from);
  void MergeFrom(const Proto10103003& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Proto10103003* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 type = 1;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Proto10103003)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 type_;
  friend struct ::TableStruct_ProtoClient_5f10103_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Proto10103001

// optional int32 type = 1;
inline bool Proto10103001::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Proto10103001::clear_type() {
  type_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::google::protobuf::int32 Proto10103001::type() const {
  // @@protoc_insertion_point(field_get:Proto10103001.type)
  return type_;
}
inline void Proto10103001::set_type(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  type_ = value;
  // @@protoc_insertion_point(field_set:Proto10103001.type)
}

// -------------------------------------------------------------------

// Proto80103002

// optional int32 type = 1;
inline bool Proto80103002::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Proto80103002::clear_type() {
  type_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::google::protobuf::int32 Proto80103002::type() const {
  // @@protoc_insertion_point(field_get:Proto80103002.type)
  return type_;
}
inline void Proto80103002::set_type(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  type_ = value;
  // @@protoc_insertion_point(field_set:Proto80103002.type)
}

// repeated .ProtoItem item_list = 2;
inline int Proto80103002::item_list_size() const {
  return item_list_.size();
}
inline ::ProtoItem* Proto80103002::mutable_item_list(int index) {
  // @@protoc_insertion_point(field_mutable:Proto80103002.item_list)
  return item_list_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoItem >*
Proto80103002::mutable_item_list() {
  // @@protoc_insertion_point(field_mutable_list:Proto80103002.item_list)
  return &item_list_;
}
inline const ::ProtoItem& Proto80103002::item_list(int index) const {
  // @@protoc_insertion_point(field_get:Proto80103002.item_list)
  return item_list_.Get(index);
}
inline ::ProtoItem* Proto80103002::add_item_list() {
  // @@protoc_insertion_point(field_add:Proto80103002.item_list)
  return item_list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoItem >&
Proto80103002::item_list() const {
  // @@protoc_insertion_point(field_list:Proto80103002.item_list)
  return item_list_;
}

// -------------------------------------------------------------------

// Proto10103003

// optional int32 type = 1;
inline bool Proto10103003::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Proto10103003::clear_type() {
  type_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::google::protobuf::int32 Proto10103003::type() const {
  // @@protoc_insertion_point(field_get:Proto10103003.type)
  return type_;
}
inline void Proto10103003::set_type(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  type_ = value;
  // @@protoc_insertion_point(field_set:Proto10103003.type)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_ProtoClient_5f10103_2eproto
