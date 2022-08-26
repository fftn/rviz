// Generated by gencpp from file moscpp/SetLoggerLevelResponse.msg
// DO NOT EDIT!


#ifndef MOSCPP_MESSAGE_SETLOGGERLEVELRESPONSE_H
#define MOSCPP_MESSAGE_SETLOGGERLEVELRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include "mos_types.h"
#include "mos_serialization.h"
#include "mos_builtin_message_traits.h"
#include "mos_message_operations.h"


namespace moscpp
{
template <class ContainerAllocator>
struct SetLoggerLevelResponse_
{
  typedef SetLoggerLevelResponse_<ContainerAllocator> Type;

  SetLoggerLevelResponse_()
    {
    }
  SetLoggerLevelResponse_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SetLoggerLevelResponse_

typedef ::moscpp::SetLoggerLevelResponse_<std::allocator<void> > SetLoggerLevelResponse;

typedef boost::shared_ptr< ::moscpp::SetLoggerLevelResponse > SetLoggerLevelResponsePtr;
typedef boost::shared_ptr< ::moscpp::SetLoggerLevelResponse const> SetLoggerLevelResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> & v)
{
mos::message_operations::Printer< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace moscpp

namespace mos
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::moscpp::SetLoggerLevelResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "moscpp/SetLoggerLevelResponse";
  }

  static const char* value(const ::moscpp::SetLoggerLevelResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::moscpp::SetLoggerLevelResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace mos

namespace mos
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    MOS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetLoggerLevelResponse_

} // namespace serialization
} // namespace mos

namespace mos
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::moscpp::SetLoggerLevelResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::moscpp::SetLoggerLevelResponse_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace mos

#endif // MOSCPP_MESSAGE_SETLOGGERLEVELRESPONSE_H
