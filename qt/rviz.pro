TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
QT += widgets

INCLUDEPATH += ../src/
INCLUDEPATH += ../src/rviz
INCLUDEPATH += ../src/rviz/robot
INCLUDEPATH += /opt/ros/noetic/include/
INCLUDEPATH += /usr/include/OGRE/


QMAKE_LFLAGS += "-Wl,-rpath,/opt/ros/noetic/lib/"
LIBS += -L/home/fft/Qt5.14.2/5.14.2/gcc_64/lib/


LIBS += -L/opt/ros/noetic/lib/
LIBS += -lrosconsole
LIBS += -lroscpp_serialization
LIBS += -lroscpp
LIBS += -lroslib
LIBS += -lrostime
LIBS += -lboost_thread -L/usr/lib/x86_64-linux-gnu/
LIBS += -lboost_filesystem -L/usr/lib/x86_64-linux-gnu/
LIBS += -lboost_program_options
LIBS += -ltinyxml -L/usr/lib/x86_64-linux-gnu/
LIBS += -ltinyxml2
LIBS += -lOgreMain -lassimp -lyaml-cpp
LIBS += -lxmlrpcpp
LIBS += -lconsole_bridge
LIBS += -lrviz -ltf2 -ltf2_ros -lmessage_filters -lclass_loader -L/opt/ros/noetic/lib
LIBS += -limage_transport
LIBS += -lresource_retriever -L/usr/share/ewaybot/thirdpartylib/lib/ros/




SOURCES +=  ../src/rviz/main.cpp \
    \
    ../src/rviz/bit_allocator.cpp \
    ../src/rviz/config.cpp \
    ../src/rviz/add_display_dialog.cpp \
    ../src/rviz/display.cpp \
    ../src/rviz/display_factory.cpp \
    ../src/rviz/display_group.cpp \
    ../src/rviz/displays_panel.cpp \
    ../src/rviz/failed_display.cpp \
    ../src/rviz/failed_panel.cpp \
    ../src/rviz/failed_tool.cpp \
    ../src/rviz/failed_view_controller.cpp \
    ../src/rviz/frame_manager.cpp \
    ../src/rviz/frame_position_tracking_view_controller.cpp \
    ../src/rviz/geometry.cpp \
    ../src/rviz/help_panel.cpp \
    ../src/rviz/loading_dialog.cpp \
    ../src/rviz/load_resource.cpp \
    ../src/rviz/mesh_loader.cpp \
    ../src/rviz/new_object_dialog.cpp \
    ../src/rviz/panel.cpp \
    ../src/rviz/panel_dock_widget.cpp \
    ../src/rviz/panel_factory.cpp \
    ../src/rviz/preferences_dialog.cpp \
    ../src/rviz/render_panel.cpp \
    ../src/rviz/scaled_image_widget.cpp \
    ../src/rviz/screenshot_dialog.cpp \
    ../src/rviz/selection_panel.cpp \
    ../src/rviz/splash_screen.cpp \
    ../src/rviz/time_panel.cpp \
    ../src/rviz/tool.cpp \
    ../src/rviz/tool_manager.cpp \
    ../src/rviz/tool_properties_panel.cpp \
    ../src/rviz/uniform_string_stream.cpp \
    ../src/rviz/view_controller.cpp \
    ../src/rviz/view_manager.cpp \
    ../src/rviz/views_panel.cpp \
    ../src/rviz/visualization_frame.cpp \
    ../src/rviz/visualization_manager.cpp \
    ../src/rviz/visualizer_app.cpp \
    ../src/rviz/wait_for_master_dialog.cpp \
    ../src/rviz/widget_geometry_change_detector.cpp \
    ../src/rviz/yaml_config_reader.cpp \
    ../src/rviz/yaml_config_writer.cpp \
    \
    ../src/rviz/image/image_display_base.cpp \
    ../src/rviz/properties/bool_property.cpp \
    ../src/rviz/properties/color_editor.cpp \
    ../src/rviz/properties/display_group_visibility_property.cpp \
    ../src/rviz/properties/float_edit.cpp \
    ../src/rviz/properties/property_tree_with_help.cpp \
    ../src/rviz/properties/quaternion_property.cpp \
    ../src/rviz/properties/tf_frame_property.cpp \
    ../src/rviz/properties/vector_property.cpp \
    ../src/rviz/robot/robot.cpp \
    ../src/rviz/robot/robot_joint.cpp \
    ../src/rviz/robot/robot_link.cpp \
    ../src/rviz/robot/tf_link_updater.cpp \
    ../src/rviz/selection/selection_handler.cpp \
    ../src/rviz/selection/selection_manager.cpp \
