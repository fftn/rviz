CXX = g++

CXX_FLAGS = -fPIC

CXX_DEFINES = -DBOOST_ALL_NO_LIB -DBOOST_ATOMIC_DYN_LINK -DBOOST_DATE_TIME_DYN_LINK -DBOOST_SYSTEM_DYN_LINK -DBOOST_THREAD_DYN_LINK -DROS_BUILD_SHARED_LIBS=1 -Dmostime_EXPORTS

CXX_INCLUDES = -I../../include -I../../ -I./

LIBS = -L../../share/ -lboost_date_time -lboost_system -lboost_thread -lboost_atomic -lrt -lpthread

DESTDIR = ../../target

default: libmostime.so

libmostime.so:  mos_duration.cpp.o mos_rate.cpp.o mos_time.cpp.o
	$(CXX) -fPIC -shared -Wl,-soname,libmostime.so -o libmostime.so mos_duration.cpp.o mos_rate.cpp.o mos_time.cpp.o  $(LIBS)

mos_duration.cpp.o:  mos_duration.cpp
	$(CXX) $(CXX_DEFINES) $(CXX_FLAGS) $(CXX_INCLUDES) -o mos_duration.cpp.o -c mos_duration.cpp

mos_rate.cpp.o:  mos_rate.cpp
	$(CXX) $(CXX_DEFINES) $(CXX_FLAGS) $(CXX_INCLUDES) -o mos_rate.cpp.o -c mos_rate.cpp

mos_time.cpp.o:  mos_time.cpp
	$(CXX) $(CXX_DEFINES) $(CXX_FLAGS) $(CXX_INCLUDES) -o mos_time.cpp.o -c mos_time.cpp

install: libmostime.so
	install -d $(DESTDIR)/lib/
	install -m 644 libmostime.so $(DESTDIR)/lib/

clean: 
	$(RM) libmostime.so *.o *~ 

