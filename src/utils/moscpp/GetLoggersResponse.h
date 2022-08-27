// Generated by gencpp from file moscpp/GetLoggersResponse.msg
// DO NOT EDIT!


#ifndef MOSCPP_MESSAGE_GETLOGGERSRESPONSE_H
#define MOSCPP_MESSAGE_GETLOGGERSRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include "mos_types.h"
#include "mos_serialization.h"
#include "mos_builtin_message_traits.h"
#include "mos_message_operations.h"

#include "moscpp/Logger.h"

namespace moscpp
{
template <class ContainerAllocator>
struct GetLoggersResponse_
{
  typedef GetLoggersResponse_<ContainerAllocator> Type;

  GetLoggersResponse_()
    : loggers()  {
    }
  GetLoggersResponse_(const ContainerAllocator& _alloc)
    : loggers(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::moscpp::Logger_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::moscpp::Logger_<ContainerAllocator> >::other >  _loggers_type;
  _loggers_type loggers;





  typedef boost::shared_ptr< ::moscpp::GetLoggersResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::moscpp::GetLoggersResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GetLoggersResponse_

typedef ::moscpp::GetLoggersResponse_<std::allocator<void> > GetLoggersResponse;

typedef boost::shared_ptr< ::moscpp::GetLoggersResponse > GetLoggersResponsePtr;
typedef boost::shared_ptr< ::moscpp::GetLoggersResponse const> GetLoggersResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::moscpp::GetLoggersResponse_<ContainerAllocator> & v)
{
mos::message_operations::Printer< ::moscpp::GetLoggersResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::moscpp::GetLoggersResponse_<ContainerAllocator1> & lhs, const ::moscpp::GetLoggersResponse_<ContainerAllocator2> & rhs)
{
  return lhs.loggers == rhs.loggers;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::moscpp::GetLoggersResponse_<ContainerAllocator1> & lhs, const ::moscpp::GetLoggersResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace moscpp

namespace mos
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::moscpp::GetLoggersResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::moscpp::GetLoggersResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::moscpp::GetLoggersResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "32e97e85527d4678a8f9279894bb64b0";
  }

  static const char* value(const ::moscpp::GetLoggersResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x32e97e85527d4678ULL;
  static const uint64_t static_value2 = 0xa8f9279894bb64b0ULL;
};

template<class ContainerAllocator>
struct DataType< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "moscpp/GetLoggersResponse";
  }

  static const char* value(const ::moscpp::GetLoggersResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Logger[] loggers\n"
"\n"
"================================================================================\n"
"MSG: moscpp/Logger\n"
"string name\n"
"string level\n"
;
  }

  static const char* value(const ::moscpp::GetLoggersResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace mos

namespace mos
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.loggers);
    }

    MOS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetLoggersResponse_

} // namespace serialization
} // namespace mos

namespace mos
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::moscpp::GetLoggersResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::moscpp::GetLoggersResponse_<ContainerAllocator>& v)
  {
    s << indent << "loggers[]" << std::endl;
    for (size_t i = 0; i < v.loggers.size(); ++i)
    {
      s << indent << "  loggers[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::moscpp::Logger_<ContainerAllocator> >::stream(s, indent + "    ", v.loggers[i]);
    }
  }
};

} // namespace message_operations
} // namespace mos

#endif // MOSCPP_MESSAGE_GETLOGGERSRESPONSE_H