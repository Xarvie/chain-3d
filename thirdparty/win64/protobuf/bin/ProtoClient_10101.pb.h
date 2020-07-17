// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoClient_10101.proto

#ifndef PROTOBUF_INCLUDED_ProtoClient_5f10101_2eproto
#define PROTOBUF_INCLUDED_ProtoClient_5f10101_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_ProtoClient_5f10101_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_ProtoClient_5f10101_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_ProtoClient_5f10101_2eproto();
class Proto80101001;
class Proto80101001DefaultTypeInternal;
extern Proto80101001DefaultTypeInternal _Proto80101001_default_instance_;
namespace google {
namespace protobuf {
template<> ::Proto80101001* Arena::CreateMaybeMessage<::Proto80101001>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class Proto80101001 :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Proto80101001) */ {
 public:
  Proto80101001();
  virtual ~Proto80101001();

  Proto80101001(const Proto80101001& from);

  inline Proto80101001& operator=(const Proto80101001& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Proto80101001(Proto80101001&& from) noexcept
    : Proto80101001() {
    *this = ::std::move(from);
  }

  inline Proto80101001& operator=(Proto80101001&& from) noexcept {
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
  static const Proto80101001& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Proto80101001* internal_default_instance() {
    return reinterpret_cast<const Proto80101001*>(
               &_Proto80101001_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Proto80101001* other);
  friend void swap(Proto80101001& a, Proto80101001& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Proto80101001* New() const final {
    return CreateMaybeMessage<Proto80101001>(nullptr);
  }

  Proto80101001* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Proto80101001>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Proto80101001& from);
  void MergeFrom(const Proto80101001& from);
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
  void InternalSwap(Proto80101001* other);
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

  // optional string server_prev = 6;
  bool has_server_prev() const;
  void clear_server_prev();
  static const int kServerPrevFieldNumber = 6;
  const ::std::string& server_prev() const;
  void set_server_prev(const ::std::string& value);
  #if LANG_CXX11
  void set_server_prev(::std::string&& value);
  #endif
  void set_server_prev(const char* value);
  void set_server_prev(const char* value, size_t size);
  ::std::string* mutable_server_prev();
  ::std::string* release_server_prev();
  void set_allocated_server_prev(::std::string* server_prev);

  // optional .ProtoShowRole show = 2;
  bool has_show() const;
  void clear_show();
  static const int kShowFieldNumber = 2;
  const ::ProtoShowRole& show() const;
  ::ProtoShowRole* release_show();
  ::ProtoShowRole* mutable_show();
  void set_allocated_show(::ProtoShowRole* show);

  // optional int64 id = 1;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::int64 id() const;
  void set_id(::google::protobuf::int64 value);

  // optional double exp = 3;
  bool has_exp() const;
  void clear_exp();
  static const int kExpFieldNumber = 3;
  double exp() const;
  void set_exp(double value);

  // optional int32 open_days = 4;
  bool has_open_days() const;
  void clear_open_days();
  static const int kOpenDaysFieldNumber = 4;
  ::google::protobuf::int32 open_days() const;
  void set_open_days(::google::protobuf::int32 value);

  // optional int32 create_days = 5;
  bool has_create_days() const;
  void clear_create_days();
  static const int kCreateDaysFieldNumber = 5;
  ::google::protobuf::int32 create_days() const;
  void set_create_days(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Proto80101001)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr server_prev_;
  ::ProtoShowRole* show_;
  ::google::protobuf::int64 id_;
  double exp_;
  ::google::protobuf::int32 open_days_;
  ::google::protobuf::int32 create_days_;
  friend struct ::TableStruct_ProtoClient_5f10101_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Proto80101001

// optional int64 id = 1;
inline bool Proto80101001::has_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Proto80101001::clear_id() {
  id_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000004u;
}
inline ::google::protobuf::int64 Proto80101001::id() const {
  // @@protoc_insertion_point(field_get:Proto80101001.id)
  return id_;
}
inline void Proto80101001::set_id(::google::protobuf::int64 value) {
  _has_bits_[0] |= 0x00000004u;
  id_ = value;
  // @@protoc_insertion_point(field_set:Proto80101001.id)
}

// optional .ProtoShowRole show = 2;
inline bool Proto80101001::has_show() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline const ::ProtoShowRole& Proto80101001::show() const {
  const ::ProtoShowRole* p = show_;
  // @@protoc_insertion_point(field_get:Proto80101001.show)
  return p != nullptr ? *p : *reinterpret_cast<const ::ProtoShowRole*>(
      &::_ProtoShowRole_default_instance_);
}
inline ::ProtoShowRole* Proto80101001::release_show() {
  // @@protoc_insertion_point(field_release:Proto80101001.show)
  _has_bits_[0] &= ~0x00000002u;
  ::ProtoShowRole* temp = show_;
  show_ = nullptr;
  return temp;
}
inline ::ProtoShowRole* Proto80101001::mutable_show() {
  _has_bits_[0] |= 0x00000002u;
  if (show_ == nullptr) {
    auto* p = CreateMaybeMessage<::ProtoShowRole>(GetArenaNoVirtual());
    show_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Proto80101001.show)
  return show_;
}
inline void Proto80101001::set_allocated_show(::ProtoShowRole* show) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(show_);
  }
  if (show) {
    ::google::protobuf::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      show = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, show, submessage_arena);
    }
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  show_ = show;
  // @@protoc_insertion_point(field_set_allocated:Proto80101001.show)
}

// optional double exp = 3;
inline bool Proto80101001::has_exp() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Proto80101001::clear_exp() {
  exp_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline double Proto80101001::exp() const {
  // @@protoc_insertion_point(field_get:Proto80101001.exp)
  return exp_;
}
inline void Proto80101001::set_exp(double value) {
  _has_bits_[0] |= 0x00000008u;
  exp_ = value;
  // @@protoc_insertion_point(field_set:Proto80101001.exp)
}

// optional int32 open_days = 4;
inline bool Proto80101001::has_open_days() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Proto80101001::clear_open_days() {
  open_days_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline ::google::protobuf::int32 Proto80101001::open_days() const {
  // @@protoc_insertion_point(field_get:Proto80101001.open_days)
  return open_days_;
}
inline void Proto80101001::set_open_days(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000010u;
  open_days_ = value;
  // @@protoc_insertion_point(field_set:Proto80101001.open_days)
}

// optional int32 create_days = 5;
inline bool Proto80101001::has_create_days() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Proto80101001::clear_create_days() {
  create_days_ = 0;
  _has_bits_[0] &= ~0x00000020u;
}
inline ::google::protobuf::int32 Proto80101001::create_days() const {
  // @@protoc_insertion_point(field_get:Proto80101001.create_days)
  return create_days_;
}
inline void Proto80101001::set_create_days(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000020u;
  create_days_ = value;
  // @@protoc_insertion_point(field_set:Proto80101001.create_days)
}

// optional string server_prev = 6;
inline bool Proto80101001::has_server_prev() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Proto80101001::clear_server_prev() {
  server_prev_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::std::string& Proto80101001::server_prev() const {
  // @@protoc_insertion_point(field_get:Proto80101001.server_prev)
  return server_prev_.GetNoArena();
}
inline void Proto80101001::set_server_prev(const ::std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  server_prev_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Proto80101001.server_prev)
}
#if LANG_CXX11
inline void Proto80101001::set_server_prev(::std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  server_prev_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Proto80101001.server_prev)
}
#endif
inline void Proto80101001::set_server_prev(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  server_prev_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Proto80101001.server_prev)
}
inline void Proto80101001::set_server_prev(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  server_prev_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Proto80101001.server_prev)
}
inline ::std::string* Proto80101001::mutable_server_prev() {
  _has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_mutable:Proto80101001.server_prev)
  return server_prev_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Proto80101001::release_server_prev() {
  // @@protoc_insertion_point(field_release:Proto80101001.server_prev)
  if (!has_server_prev()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return server_prev_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Proto80101001::set_allocated_server_prev(::std::string* server_prev) {
  if (server_prev != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  server_prev_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), server_prev);
  // @@protoc_insertion_point(field_set_allocated:Proto80101001.server_prev)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_ProtoClient_5f10101_2eproto
