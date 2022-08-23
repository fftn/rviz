// Generated by gencpp from file geometry_msgs/Pose.msg
// DO NOT EDIT!


#ifndef GEOMETRY_MSGS_MESSAGE_POSE_H
#define GEOMETRY_MSGS_MESSAGE_POSE_H


#include <string>
#include <vector>
#include <map>

#include <mos_types.h>
#include <mos_serialization.h>
#include <mos_builtin_message_traits.h>
#include "mos_message_operations.h"

#include <mos_geometry_msgs/Point.h>
#include <mos_geometry_msgs/Quaternion.h>

namespace geometry_msgs
{
template <class ContainerAllocator>
struct Pose_
{
  typedef Pose_<ContainerAllocator> Type;

  Pose_()
    : position()
    , orientation()  {
    }
  Pose_(const ContainerAllocator& _alloc)
    : position(_alloc)
    , orientation(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _position_type;
  _position_type position;

   typedef  ::geometry_msgs::Quaternion_<ContainerAllocator>  _orientation_type;
  _orientation_type orientation;





  typedef boost::shared_ptr< ::geometry_msgs::Pose_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::geometry_msgs::Pose_<ContainerAllocator> const> ConstPtr;

}; // struct Pose_

typedef ::geometry_msgs::Pose_<std::allocator<void> > Pose;

typedef boost::shared_ptr< ::geometry_msgs::Pose > PosePtr;
typedef boost::shared_ptr< ::geometry_msgs::Pose const> PoseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::geometry_msgs::Pose_<ContainerAllocator> & v)
{
mos::message_operations::Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace geometry_msgs

namespace mos
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::geometry_msgs::Pose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::geometry_msgs::Pose_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::geometry_msgs::Pose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::geometry_msgs::Pose_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::geometry_msgs::Pose_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::geometry_msgs::Pose_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::geometry_msgs::Pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e45d45a5a1ce597b249e23fb30fc871f";
  }

  static const char* value(const ::geometry_msgs::Pose_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe45d45a5a1ce597bULL;
  static const uint64_t static_value2 = 0x249e23fb30fc871fULL;
};

template<class ContainerAllocator>
struct DataType< ::geometry_msgs::Pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/Pose";
  }

  static const char* value(const ::geometry_msgs::Pose_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::geometry_msgs::Pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
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

  static const char* value(const ::geometry_msgs::Pose_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace mos

namespace mos
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::geometry_msgs::Pose_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.position);
      stream.next(m.orientation);
    }

    MOS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Pose_

} // namespace serialization
} // namespace mos

namespace mos
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::geometry_msgs::Pose_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::geometry_msgs::Pose_<ContainerAllocator>& v)
  {
    s << indent << "position: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.position);
    s << indent << "orientation: ";
    s << std::endl;
    Printer< ::geometry_msgs::Quaternion_<ContainerAllocator> >::stream(s, indent + "  ", v.orientation);
  }
};

} // namespace message_operations
} // namespace mos

#endif // GEOMETRY_MSGS_MESSAGE_POSE_H
