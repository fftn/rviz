TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
QT += widgets

INCLUDEPATH += ../src/
INCLUDEPATH += ../src/include
INCLUDEPATH += ../src/rviz
INCLUDEPATH += ../src/utils
INCLUDEPATH += ../src/rviz/robot
INCLUDEPATH += ../3rdlibs/
INCLUDEPATH += ../3rdlibs/OGRE/include/
INCLUDEPATH += ../3rdlibs/yaml-cpp/include/


QMAKE_LFLAGS += "-Wl,-rpath,../lib/share"
LIBS += -L../3rdlibs/lib
LIBS += -L../3rdlibs/OGRE/lib/
#LIBS += -L/home/fft/Downloads/ogre-1-9-0/buildqt/lib
LIBS += -L../3rdlibs/yaml-cpp/libs/
LIBS += -L../3rdlibs/image-transport/lib/
LIBS += -lmostime -L../src/target/lib
LIBS += -lactionlib
LIBS += -lrosconsole
LIBS += -lroscpp_serialization
LIBS += -lroscpp
LIBS += -lroslib
LIBS += -lfreeimage -L../3rdlibs/freeimage/lib
LIBS += -limage_transport
LIBS += -lclass_loader
LIBS += -lxmlrpcpp
LIBS += -L../lib/manual
LIBS += -L../lib/3pl -lresource_retriever -lmessage_filters -lconsole_bridge -ltf2
LIBS += -L../lib/cmake -limage_transport -ltf2_ros
LIBS += -lX11
LIBS += -lboost_thread -lboost_filesystem -lboost_program_options
LIBS += -ltinyxml -ltinyxml2
#LIBS += -lOgreOverlay_d -lOgreMain_d -lOgreProperty_d -lOgreRTShaderSystem_d -lOgreTerrain_d -lOgreVolume_d -lOgrePaging_d
LIBS += -lOgreOverlay -lOgreMain -lOgreProperty -lOgreRTShaderSystem -lOgreTerrain -lOgreVolume -lOgrePaging
LIBS += -lassimp -lyaml-cpp
LIBS += -ltf2 -ltf2_ros
LIBS += -ljpegxr -ljxrglue -L../3rdlibs/jxr/lib/
LIBS += -lzzip  -L../3rdlibs/zzip/lib/


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
    ../src/rviz/properties/property.cpp \
    ../src/rviz/properties/status_property.cpp \
    ../src/rviz/properties/status_list.cpp \
    \
    ../src/rviz/robot/robot.cpp \
    ../src/rviz/robot/robot_joint.cpp \
    ../src/rviz/robot/robot_link.cpp \
    ../src/rviz/robot/tf_link_updater.cpp \
    ../src/rviz/selection/selection_handler.cpp \
    ../src/rviz/selection/selection_manager.cpp \
#    ../src/rviz/default_plugin/view_controllers/fixed_orientation_ortho_view_controller.cpp \
#    ../src/rviz/default_plugin/view_controllers/fps_view_controller.cpp \
#    ../src/rviz/default_plugin/view_controllers/orbit_view_controller.cpp \
#    ../src/rviz/default_plugin/view_controllers/frame_view_controller.cpp \
#    ../src/rviz/default_plugin/view_controllers/third_person_follower_view_controller.cpp \
#    ../src/rviz/default_plugin/view_controllers/xy_orbit_view_controller.cpp \
    \
    ../src/rviz/properties/color_property.cpp \
    ../src/rviz/properties/combo_box.cpp \
    ../src/rviz/properties/display_visibility_property.cpp \
    ../src/rviz/properties/editable_combo_box.cpp \
    ../src/rviz/properties/editable_enum_property.cpp \
    ../src/rviz/properties/enum_property.cpp \
    ../src/rviz/properties/float_property.cpp \
    ../src/rviz/properties/int_property.cpp \
    ../src/rviz/properties/line_edit_with_button.cpp \
    ../src/rviz/properties/parse_color.cpp \
    ../src/rviz/properties/property_tree_delegate.cpp \
    ../src/rviz/properties/property_tree_model.cpp \
    ../src/rviz/properties/property_tree_widget.cpp \
    ../src/rviz/properties/ros_topic_property.cpp \
    ../src/rviz/properties/splitter_handle.cpp \
    ../src/rviz/properties/string_property.cpp \
    \
    ../src/rviz/env_config.cpp \
    ../src/rviz/ogre_helpers/apply_visibility_bits.cpp \
    ../src/rviz/ogre_helpers/arrow.cpp \
    ../src/rviz/ogre_helpers/axes.cpp \
    ../src/rviz/ogre_helpers/billboard_line.cpp \
    ../src/rviz/ogre_helpers/camera_base.cpp \
    ../src/rviz/ogre_helpers/grid.cpp \
    ../src/rviz/ogre_helpers/initialization.cpp \
    ../src/rviz/ogre_helpers/line.cpp \
    ../src/rviz/ogre_helpers/mesh_shape.cpp \
    ../src/rviz/ogre_helpers/movable_text.cpp \
    ../src/rviz/ogre_helpers/object.cpp \
    ../src/rviz/ogre_helpers/ogre_logging.cpp \
    ../src/rviz/ogre_helpers/ogre_render_queue_clearer.cpp \
    ../src/rviz/ogre_helpers/orbit_camera.cpp \
    ../src/rviz/ogre_helpers/orthographic.cpp \
    ../src/rviz/ogre_helpers/point_cloud.cpp \
    ../src/rviz/ogre_helpers/qt_ogre_render_window.cpp \
    ../src/rviz/ogre_helpers/render_system.cpp \
    ../src/rviz/ogre_helpers/render_widget.cpp \
    ../src/rviz/ogre_helpers/shape.cpp \

HEADERS += \
    ../src/rviz/add_display_dialog.h \
    ../src/rviz/display.h \
    ../src/rviz/display_group.h \
    ../src/rviz/displays_panel.h \
    ../src/rviz/failed_panel.h \
    ../src/rviz/frame_manager.h \
    ../src/rviz/frame_position_tracking_view_controller.h \
    ../src/rviz/help_panel.h \
    ../src/rviz/loading_dialog.h \
    ../src/rviz/new_object_dialog.h \
    ../src/rviz/panel.h \
    ../src/rviz/panel_dock_widget.h \
    ../src/rviz/preferences_dialog.h \
    ../src/rviz/render_panel.h \
    ../src/rviz/scaled_image_widget.h \
    ../src/rviz/screenshot_dialog.h \
    ../src/rviz/selection_panel.h \
    ../src/rviz/splash_screen.h \
    ../src/rviz/time_panel.h \
    ../src/rviz/tool.h \
    ../src/rviz/tool_manager.h \
    ../src/rviz/tool_properties_panel.h \
    ../src/rviz/view_controller.h \
    ../src/rviz/view_manager.h \
    ../src/rviz/views_panel.h \
    ../src/rviz/visualization_frame.h \
    ../src/rviz/visualization_manager.h \
    ../src/rviz/visualizer_app.h \
    ../src/rviz/wait_for_master_dialog.h \
    ../src/rviz/widget_geometry_change_detector.h \
    ../src/rviz/image/image_display_base.h \
    ../src/rviz/properties/bool_property.h \
    ../src/rviz/properties/color_editor.h \
    ../src/rviz/properties/display_group_visibility_property.h \
    ../src/rviz/properties/float_edit.h \
    ../src/rviz/properties/property_tree_with_help.h \
    ../src/rviz/properties/quaternion_property.h \
    ../src/rviz/properties/tf_frame_property.h \
    ../src/rviz/properties/vector_property.h \
    ../src/rviz/properties/property.h \
    ../src/rviz/properties/status_property.h \
    ../src/rviz/properties/status_list.h \
    ../src/rviz/robot/robot.h \
    ../src/rviz/robot/robot_joint.h \
    ../src/rviz/robot/robot_link.h \
    ../src/rviz/selection/selection_manager.h \
#    ../src/rviz/default_plugin/view_controllers/fixed_orientation_ortho_view_controller.h \
#    ../src/rviz/default_plugin/view_controllers/fps_view_controller.h \
#    ../src/rviz/default_plugin/view_controllers/orbit_view_controller.h \
#    ../src/rviz/default_plugin/view_controllers/frame_view_controller.h \
#    ../src/rviz/default_plugin/view_controllers/third_person_follower_view_controller.h \
#    ../src/rviz/default_plugin/view_controllers/xy_orbit_view_controller.h \
    ../src/rviz/properties/color_property.h \
    ../src/rviz/properties/combo_box.h \
    ../src/rviz/properties/display_visibility_property.h \
    ../src/rviz/properties/editable_combo_box.h \
    ../src/rviz/properties/editable_enum_property.h \
    ../src/rviz/properties/enum_property.h \
    ../src/rviz/properties/float_property.h \
    ../src/rviz/properties/int_property.h \
    ../src/rviz/properties/line_edit_with_button.h \
    ../src/rviz/properties/parse_color.h \
    ../src/rviz/properties/property_tree_delegate.h \
    ../src/rviz/properties/property_tree_model.h \
    ../src/rviz/properties/property_tree_widget.h \
    ../src/rviz/properties/ros_topic_property.h \
    ../src/rviz/properties/splitter_handle.h \
    ../src/rviz/properties/string_property.h \
    \
    ../src/rviz/load_resource.h \
    ../src/rviz/env_config.h \
    ../src/rviz/display_context.h \
    ../src/rviz/ogre_helpers/arrow.h \

