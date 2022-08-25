// Generated by gencpp from file tf2_msgs/TFMessage.msg
// DO NOT EDIT!


#ifndef TF2_MSGS_MESSAGE_TFMESSAGE_H
#define TF2_MSGS_MESSAGE_TFMESSAGE_H


#include <string>
#include <vector>
#include <map>

#include "mos_types.h"
#include "mos_serialization.h"
#include "mos_builtin_message_traits.h"
#include "mos_message_operations.h"

#include "mos_geometry_msgs/TransformStamped.h"

namespace tf2_msgs
{
template <class ContainerAllocator>
struct TFMessage_
{
  typedef TFMessage_<ContainerAllocator> Type;

  TFMessage_()
    : transforms()  {
    }
  TFMessage_(const ContainerAllocator& _alloc)
    : transforms(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::geometry_msgs::TransformStamped_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::TransformStamped_<ContainerAllocator> >::other >  _transforms_type;
  _transforms_type transforms;





  typedef boost::shared_ptr< ::tf2_msgs::TFMessage_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::tf2_msgs::TFMessage_<ContainerAllocator> const> ConstPtr;

}; // struct TFMessage_

typedef ::tf2_msgs::TFMessage_<std::allocator<void> > TFMessage;

typedef boost::shared_ptr< ::tf2_msgs::TFMessage > TFMessagePtr;
typedef boost::shared_ptr< ::tf2_msgs::TFMessage const> TFMessageConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::tf2_msgs::TFMessage_<ContainerAllocator> & v)
{
mos::message_operations::Printer< ::tf2_msgs::TFMessage_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::tf2_msgs::TFMessage_<ContainerAllocator1> & lhs, const ::tf2_msgs::TFMessage_<ContainerAllocator2> & rhs)
{
  return lhs.transforms == rhs.transforms;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::tf2_msgs::TFMessage_<ContainerAllocator1> & lhs, const ::tf2_msgs::TFMessage_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace tf2_msgs

namespace mos
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::tf2_msgs::TFMessage_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tf2_msgs::TFMessage_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::tf2_msgs::TFMessage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::tf2_msgs::TFMessage_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tf2_msgs::TFMessage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tf2_msgs::TFMessage_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::tf2_msgs::TFMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "94810edda583a504dfda3829e70d7eec";
  }

  static const char* value(const ::tf2_msgs::TFMessage_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x94810edda583a504ULL;
  static const uint64_t static_value2 = 0xdfda3829e70d7eecULL;
};

template<class ContainerAllocator>
struct DataType< ::tf2_msgs::TFMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "tf2_msgs/TFMessage";
  }

  static const char* value(const ::tf2_msgs::TFMessage_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::tf2_msgs::TFMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/TransformStamped[] transforms\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/TransformStamped\n"
"# This expresses a transform from coordinate frame header.frame_id\n"
"# to the coordinate frame child_frame_id\n"
"#\n"
"# This message is mostly used by the \n"
"# <a href=\"http://wiki.move-new.com/tf\">tf</a> package. \n"
"# See its documentation for more information.\n"
"\n"
"Header header\n"
"string child_frame_id # the frame id of the child frame\n"
"Transform transform\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Transform\n"
"# This represents the transform between two coordinate frames in free space.\n"
"\n"
"Vector3 translation\n"
"Quaternion rotation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
;
  }

  static const char* value(const ::tf2_msgs::TFMessage_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace mos

namespace mos
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::tf2_msgs::TFMessage_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.transforms);
    }

    MOS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TFMessage_

} // namespace serialization
} // namespace mos

namespace mos
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::tf2_msgs::TFMessage_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::tf2_msgs::TFMessage_<ContainerAllocator>& v)
  {
    s << indent << "transforms[]" << std::endl;
    for (size_t i = 0; i < v.transforms.size(); ++i)
    {
      s << indent << "  transforms[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::TransformStamped_<ContainerAllocator> >::stream(s, indent + "    ", v.transforms[i]);
    }
  }
};

} // namespace message_operations
} // namespace mos

#endif // TF2_MSGS_MESSAGE_TFMESSAGE_H
