// Generated by gencpp from file rviz/SendFilePath.msg
// DO NOT EDIT!


#ifndef RVIZ_MESSAGE_SENDFILEPATH_H
#define RVIZ_MESSAGE_SENDFILEPATH_H

#include <ros/service_traits.h>


#include <rviz/SendFilePathRequest.h>
#include <rviz/SendFilePathResponse.h>


namespace rviz
{

struct SendFilePath
{

typedef SendFilePathRequest Request;
typedef SendFilePathResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct SendFilePath
} // namespace rviz


namespace mos
{
namespace service_traits
{


template<>
struct MD5Sum< ::rviz::SendFilePath > {
  static const char* value()
  {
    return "92f17244ff295b327b62c307fafe751b";
  }

  static const char* value(const ::rviz::SendFilePath&) { return value(); }
};

template<>
struct DataType< ::rviz::SendFilePath > {
  static const char* value()
  {
    return "rviz/SendFilePath";
  }

  static const char* value(const ::rviz::SendFilePath&) { return value(); }
};


// service_traits::MD5Sum< ::rviz::SendFilePathRequest> should match
// service_traits::MD5Sum< ::rviz::SendFilePath >
template<>
struct MD5Sum< ::rviz::SendFilePathRequest>
{
  static const char* value()
  {
    return MD5Sum< ::rviz::SendFilePath >::value();
  }
  static const char* value(const ::rviz::SendFilePathRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::rviz::SendFilePathRequest> should match
// service_traits::DataType< ::rviz::SendFilePath >
template<>
struct DataType< ::rviz::SendFilePathRequest>
{
  static const char* value()
  {
    return DataType< ::rviz::SendFilePath >::value();
  }
  static const char* value(const ::rviz::SendFilePathRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::rviz::SendFilePathResponse> should match
// service_traits::MD5Sum< ::rviz::SendFilePath >
template<>
struct MD5Sum< ::rviz::SendFilePathResponse>
{
  static const char* value()
  {
    return MD5Sum< ::rviz::SendFilePath >::value();
  }
  static const char* value(const ::rviz::SendFilePathResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::rviz::SendFilePathResponse> should match
// service_traits::DataType< ::rviz::SendFilePath >
template<>
struct DataType< ::rviz::SendFilePathResponse>
{
  static const char* value()
  {
    return DataType< ::rviz::SendFilePath >::value();
  }
  static const char* value(const ::rviz::SendFilePathResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace mos

#endif // RVIZ_MESSAGE_SENDFILEPATH_H
