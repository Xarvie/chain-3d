// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoConnect.proto

#include "ProtoConnect.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

class Proto19999997DefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Proto19999997> _instance;
} _Proto19999997_default_instance_;
class Proto19999998DefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Proto19999998> _instance;
} _Proto19999998_default_instance_;
static void InitDefaultsProto19999997_ProtoConnect_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_Proto19999997_default_instance_;
    new (ptr) ::Proto19999997();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Proto19999997::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_Proto19999997_ProtoConnect_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsProto19999997_ProtoConnect_2eproto}, {}};

static void InitDefaultsProto19999998_ProtoConnect_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_Proto19999998_default_instance_;
    new (ptr) ::Proto19999998();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Proto19999998::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_Proto19999998_ProtoConnect_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsProto19999998_ProtoConnect_2eproto}, {}};

void InitDefaults_ProtoConnect_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_Proto19999997_ProtoConnect_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_Proto19999998_ProtoConnect_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_ProtoConnect_2eproto[2];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_ProtoConnect_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_ProtoConnect_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_ProtoConnect_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::Proto19999997, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::Proto19999997, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Proto19999997, sid_),
  PROTOBUF_FIELD_OFFSET(::Proto19999997, robot_id_),
  0,
  1,
  PROTOBUF_FIELD_OFFSET(::Proto19999998, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::Proto19999998, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Proto19999998, sid_),
  PROTOBUF_FIELD_OFFSET(::Proto19999998, ip_),
  PROTOBUF_FIELD_OFFSET(::Proto19999998, port_),
  PROTOBUF_FIELD_OFFSET(::Proto19999998, robot_id_),
  1,
  0,
  2,
  3,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::Proto19999997)},
  { 9, 18, sizeof(::Proto19999998)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::_Proto19999997_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::_Proto19999998_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_ProtoConnect_2eproto = {
  {}, AddDescriptors_ProtoConnect_2eproto, "ProtoConnect.proto", schemas,
  file_default_instances, TableStruct_ProtoConnect_2eproto::offsets,
  file_level_metadata_ProtoConnect_2eproto, 2, file_level_enum_descriptors_ProtoConnect_2eproto, file_level_service_descriptors_ProtoConnect_2eproto,
};

const char descriptor_table_protodef_ProtoConnect_2eproto[] =
  "\n\022ProtoConnect.proto\".\n\rProto19999997\022\013\n"
  "\003sid\030\001 \001(\005\022\020\n\010robot_id\030\002 \001(\005\"H\n\rProto199"
  "99998\022\013\n\003sid\030\001 \001(\005\022\n\n\002ip\030\002 \001(\t\022\014\n\004port\030\003"
  " \001(\005\022\020\n\010robot_id\030\004 \001(\005"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_ProtoConnect_2eproto = {
  false, InitDefaults_ProtoConnect_2eproto, 
  descriptor_table_protodef_ProtoConnect_2eproto,
  "ProtoConnect.proto", &assign_descriptors_table_ProtoConnect_2eproto, 142,
};

void AddDescriptors_ProtoConnect_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_ProtoConnect_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_ProtoConnect_2eproto = []() { AddDescriptors_ProtoConnect_2eproto(); return true; }();

// ===================================================================

void Proto19999997::InitAsDefaultInstance() {
}
class Proto19999997::HasBitSetters {
 public:
  static void set_has_sid(Proto19999997* msg) {
    msg->_has_bits_[0] |= 0x00000001u;
  }
  static void set_has_robot_id(Proto19999997* msg) {
    msg->_has_bits_[0] |= 0x00000002u;
  }
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Proto19999997::kSidFieldNumber;
const int Proto19999997::kRobotIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Proto19999997::Proto19999997()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Proto19999997)
}
Proto19999997::Proto19999997(const Proto19999997& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&sid_, &from.sid_,
    static_cast<size_t>(reinterpret_cast<char*>(&robot_id_) -
    reinterpret_cast<char*>(&sid_)) + sizeof(robot_id_));
  // @@protoc_insertion_point(copy_constructor:Proto19999997)
}

void Proto19999997::SharedCtor() {
  ::memset(&sid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&robot_id_) -
      reinterpret_cast<char*>(&sid_)) + sizeof(robot_id_));
}

Proto19999997::~Proto19999997() {
  // @@protoc_insertion_point(destructor:Proto19999997)
  SharedDtor();
}

void Proto19999997::SharedDtor() {
}

void Proto19999997::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Proto19999997& Proto19999997::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_Proto19999997_ProtoConnect_2eproto.base);
  return *internal_default_instance();
}


void Proto19999997::Clear() {
// @@protoc_insertion_point(message_clear_start:Proto19999997)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&sid_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&robot_id_) -
        reinterpret_cast<char*>(&sid_)) + sizeof(robot_id_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Proto19999997::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<Proto19999997*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // optional int32 sid = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_sid(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // optional int32 robot_id = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        msg->set_robot_id(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool Proto19999997::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Proto19999997)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 sid = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {
          HasBitSetters::set_has_sid(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 robot_id = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {
          HasBitSetters::set_has_robot_id(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &robot_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Proto19999997)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Proto19999997)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Proto19999997::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Proto19999997)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 sid = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->sid(), output);
  }

  // optional int32 robot_id = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->robot_id(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Proto19999997)
}

::google::protobuf::uint8* Proto19999997::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Proto19999997)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 sid = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->sid(), target);
  }

  // optional int32 robot_id = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->robot_id(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Proto19999997)
  return target;
}

size_t Proto19999997::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Proto19999997)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional int32 sid = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->sid());
    }

    // optional int32 robot_id = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->robot_id());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Proto19999997::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Proto19999997)
  GOOGLE_DCHECK_NE(&from, this);
  const Proto19999997* source =
      ::google::protobuf::DynamicCastToGenerated<Proto19999997>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Proto19999997)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Proto19999997)
    MergeFrom(*source);
  }
}

void Proto19999997::MergeFrom(const Proto19999997& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Proto19999997)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      sid_ = from.sid_;
    }
    if (cached_has_bits & 0x00000002u) {
      robot_id_ = from.robot_id_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void Proto19999997::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Proto19999997)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Proto19999997::CopyFrom(const Proto19999997& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Proto19999997)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Proto19999997::IsInitialized() const {
  return true;
}

void Proto19999997::Swap(Proto19999997* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Proto19999997::InternalSwap(Proto19999997* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(sid_, other->sid_);
  swap(robot_id_, other->robot_id_);
}

::google::protobuf::Metadata Proto19999997::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_ProtoConnect_2eproto);
  return ::file_level_metadata_ProtoConnect_2eproto[kIndexInFileMessages];
}


// ===================================================================

void Proto19999998::InitAsDefaultInstance() {
}
class Proto19999998::HasBitSetters {
 public:
  static void set_has_sid(Proto19999998* msg) {
    msg->_has_bits_[0] |= 0x00000002u;
  }
  static void set_has_ip(Proto19999998* msg) {
    msg->_has_bits_[0] |= 0x00000001u;
  }
  static void set_has_port(Proto19999998* msg) {
    msg->_has_bits_[0] |= 0x00000004u;
  }
  static void set_has_robot_id(Proto19999998* msg) {
    msg->_has_bits_[0] |= 0x00000008u;
  }
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Proto19999998::kSidFieldNumber;
const int Proto19999998::kIpFieldNumber;
const int Proto19999998::kPortFieldNumber;
const int Proto19999998::kRobotIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Proto19999998::Proto19999998()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Proto19999998)
}
Proto19999998::Proto19999998(const Proto19999998& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ip_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_ip()) {
    ip_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.ip_);
  }
  ::memcpy(&sid_, &from.sid_,
    static_cast<size_t>(reinterpret_cast<char*>(&robot_id_) -
    reinterpret_cast<char*>(&sid_)) + sizeof(robot_id_));
  // @@protoc_insertion_point(copy_constructor:Proto19999998)
}

void Proto19999998::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_Proto19999998_ProtoConnect_2eproto.base);
  ip_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&sid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&robot_id_) -
      reinterpret_cast<char*>(&sid_)) + sizeof(robot_id_));
}

Proto19999998::~Proto19999998() {
  // @@protoc_insertion_point(destructor:Proto19999998)
  SharedDtor();
}

void Proto19999998::SharedDtor() {
  ip_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void Proto19999998::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Proto19999998& Proto19999998::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_Proto19999998_ProtoConnect_2eproto.base);
  return *internal_default_instance();
}


void Proto19999998::Clear() {
// @@protoc_insertion_point(message_clear_start:Proto19999998)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ip_.ClearNonDefaultToEmptyNoArena();
  }
  if (cached_has_bits & 0x0000000eu) {
    ::memset(&sid_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&robot_id_) -
        reinterpret_cast<char*>(&sid_)) + sizeof(robot_id_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Proto19999998::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<Proto19999998*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // optional int32 sid = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_sid(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // optional string ip = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName("Proto19999998.ip");
        object = msg->mutable_ip();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8Verify;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8Verify(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      // optional int32 port = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 24) goto handle_unusual;
        msg->set_port(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // optional int32 robot_id = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 32) goto handle_unusual;
        msg->set_robot_id(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool Proto19999998::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Proto19999998)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 sid = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {
          HasBitSetters::set_has_sid(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string ip = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_ip()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->ip().data(), static_cast<int>(this->ip().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "Proto19999998.ip");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 port = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (24 & 0xFF)) {
          HasBitSetters::set_has_port(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &port_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 robot_id = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (32 & 0xFF)) {
          HasBitSetters::set_has_robot_id(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &robot_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Proto19999998)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Proto19999998)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Proto19999998::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Proto19999998)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 sid = 1;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->sid(), output);
  }

  // optional string ip = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->ip().data(), static_cast<int>(this->ip().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "Proto19999998.ip");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->ip(), output);
  }

  // optional int32 port = 3;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->port(), output);
  }

  // optional int32 robot_id = 4;
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->robot_id(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Proto19999998)
}

::google::protobuf::uint8* Proto19999998::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Proto19999998)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 sid = 1;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->sid(), target);
  }

  // optional string ip = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->ip().data(), static_cast<int>(this->ip().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "Proto19999998.ip");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->ip(), target);
  }

  // optional int32 port = 3;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->port(), target);
  }

  // optional int32 robot_id = 4;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->robot_id(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Proto19999998)
  return target;
}

size_t Proto19999998::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Proto19999998)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional string ip = 2;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->ip());
    }

    // optional int32 sid = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->sid());
    }

    // optional int32 port = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->port());
    }

    // optional int32 robot_id = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->robot_id());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Proto19999998::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Proto19999998)
  GOOGLE_DCHECK_NE(&from, this);
  const Proto19999998* source =
      ::google::protobuf::DynamicCastToGenerated<Proto19999998>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Proto19999998)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Proto19999998)
    MergeFrom(*source);
  }
}

void Proto19999998::MergeFrom(const Proto19999998& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Proto19999998)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      ip_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.ip_);
    }
    if (cached_has_bits & 0x00000002u) {
      sid_ = from.sid_;
    }
    if (cached_has_bits & 0x00000004u) {
      port_ = from.port_;
    }
    if (cached_has_bits & 0x00000008u) {
      robot_id_ = from.robot_id_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void Proto19999998::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Proto19999998)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Proto19999998::CopyFrom(const Proto19999998& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Proto19999998)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Proto19999998::IsInitialized() const {
  return true;
}

void Proto19999998::Swap(Proto19999998* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Proto19999998::InternalSwap(Proto19999998* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ip_.Swap(&other->ip_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(sid_, other->sid_);
  swap(port_, other->port_);
  swap(robot_id_, other->robot_id_);
}

::google::protobuf::Metadata Proto19999998::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_ProtoConnect_2eproto);
  return ::file_level_metadata_ProtoConnect_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::Proto19999997* Arena::CreateMaybeMessage< ::Proto19999997 >(Arena* arena) {
  return Arena::CreateInternal< ::Proto19999997 >(arena);
}
template<> PROTOBUF_NOINLINE ::Proto19999998* Arena::CreateMaybeMessage< ::Proto19999998 >(Arena* arena) {
  return Arena::CreateInternal< ::Proto19999998 >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
