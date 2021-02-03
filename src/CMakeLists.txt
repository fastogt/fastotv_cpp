IF(OS_WINDOWS)
  SET(PLATFORM_HDRS ${PLATFORM_HDRS})
  SET(PLATFORM_SRCS ${PLATFORM_SRCS})
  SET(PLATFORM_LIBRARIES ${PLATFORM_LIBRARIES})
ELSEIF(OS_MACOSX)
  SET(PLATFORM_HDRS ${PLATFORM_HDRS})
  SET(PLATFORM_SRCS ${PLATFORM_SRCS})
  SET(PLATFORM_LIBRARIES ${PLATFORM_LIBRARIES})
ELSEIF(OS_LINUX)
  SET(PLATFORM_HDRS ${PLATFORM_HDRS})
  SET(PLATFORM_SRCS ${PLATFORM_SRCS})
  SET(PLATFORM_LIBRARIES ${PLATFORM_LIBRARIES})
ELSEIF(OS_FREEBSD)
  SET(PLATFORM_HDRS ${PLATFORM_HDRS})
  SET(PLATFORM_SRCS ${PLATFORM_SRCS})
  SET(PLATFORM_LIBRARIES ${PLATFORM_LIBRARIES})
ENDIF(OS_WINDOWS)

IF(USE_PTHREAD)
  SET(PLATFORM_LIBRARIES ${PLATFORM_LIBRARIES} pthread)
ENDIF(USE_PTHREAD)

FIND_PACKAGE(Common REQUIRED)
FIND_PACKAGE(JSON-C REQUIRED)

SET(PROTOCOL_CONFIG_GEN_PATH ${CMAKE_SOURCE_DIR}/include/fastotv/config.h)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/src/config.h.in ${PROTOCOL_CONFIG_GEN_PATH} @ONLY IMMEDIATE)

SET(PROTOCOL_HEADERS
  ${CMAKE_SOURCE_DIR}/include/fastotv/types.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/input_url.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/input_uri.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/pyfastostream.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/srt_key.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/output_url.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/output_uri.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/meta_url.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/types/ml/machine_learning.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/client.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands/commands.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/client/commands_factory.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/client/client.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/server/commands_factory.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/server/client.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/login_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/auth_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/client_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/operation_system_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/programme_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/favorite_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/interrupt_stream_time_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/recent_stream_time_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/device_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/devices_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/channel_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/epg_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/movie_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/vod_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/vods_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/catchup_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/catchups_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/content_requests_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/stream_base_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/serial_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/series_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/runtime_channel_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/catchup_generate_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/catchup_undo_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/channels_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/server_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/machine_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/project_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/content_request_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/notification_text_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/shutdown_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/ml/notification_info.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/commands_info/ml/types.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/protocol/types.h
  ${CMAKE_SOURCE_DIR}/include/fastotv/protocol/protocol.h
  ${PROTOCOL_CONFIG_GEN_PATH}
)
SET(PROTOCOL_SOURCES
  ${CMAKE_SOURCE_DIR}/src/types.cpp
  ${CMAKE_SOURCE_DIR}/src/types/pyfastostream.cpp
  ${CMAKE_SOURCE_DIR}/src/types/srt_key.cpp
  ${CMAKE_SOURCE_DIR}/src/types/input_url.cpp
  ${CMAKE_SOURCE_DIR}/src/types/input_uri.cpp
  ${CMAKE_SOURCE_DIR}/src/types/output_url.cpp
  ${CMAKE_SOURCE_DIR}/src/types/output_uri.cpp
  ${CMAKE_SOURCE_DIR}/src/types/meta_url.cpp
  ${CMAKE_SOURCE_DIR}/src/types/ml/machine_learning.cpp
  ${CMAKE_SOURCE_DIR}/src/client.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/commands.cpp
  ${CMAKE_SOURCE_DIR}/src/client/commands_factory.cpp
  ${CMAKE_SOURCE_DIR}/src/client/client.cpp
  ${CMAKE_SOURCE_DIR}/src/server/commands_factory.cpp
  ${CMAKE_SOURCE_DIR}/src/server/client.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/content_request_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/login_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/auth_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/operation_system_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/client_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/programme_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/favorite_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/interrupt_stream_time_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/recent_stream_time_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/device_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/channel_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/catchup_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/catchup_generate_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/catchup_undo_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/epg_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/movie_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/vod_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/stream_base_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/serial_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/runtime_channel_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/server_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/machine_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/project_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/notification_text_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/shutdown_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/ml/notification_info.cpp
  ${CMAKE_SOURCE_DIR}/src/commands_info/ml/types.cpp
  ${CMAKE_SOURCE_DIR}/src/protocol/types.cpp
  ${CMAKE_SOURCE_DIR}/src/protocol/protocol.cpp
)

SET(PROTOCOL_LIBRARY ${PROJECT_NAME_LOWERCASE})
SET(PROTOCOL_INCLUDE_DIRECTORIES ${COMMON_INCLUDE_DIRS})
SET(PROTOCOL_LIBRARY_LIBS ${COMMON_LIBRARIES} ${JSONC_LIBRARIES} ${PLATFORM_LIBRARIES})

ADD_LIBRARY(${PROTOCOL_LIBRARY} ${PROTOCOL_HEADERS} ${PROTOCOL_SOURCES})
TARGET_INCLUDE_DIRECTORIES(${PROTOCOL_LIBRARY}
  PRIVATE ${PROTOCOL_INCLUDE_DIRECTORIES}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
)
#SET_TARGET_PROPERTIES(${COMMON_PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${COMMON_HEADERS}")
TARGET_LINK_LIBRARIES(${PROTOCOL_LIBRARY} PRIVATE ${PROTOCOL_LIBRARY_LIBS})

INSTALL(TARGETS ${PROTOCOL_LIBRARY}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  # PUBLIC_HEADER DESTINATION include
)
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include/fastotv DESTINATION include)

IF (DEVELOPER_CHECK_STYLE)
  SET(CHECK_SOURCES_PROTOCOL ${PROTOCOL_HEADERS} ${PROTOCOL_SOURCES})
  REGISTER_CHECK_STYLE_TARGET(check_style_fastotv_cpp "${CHECK_SOURCES_PROTOCOL}")
ENDIF(DEVELOPER_CHECK_STYLE)

IF(DEVELOPER_ENABLE_TESTS)
  FIND_PACKAGE(GTest REQUIRED)
  ADD_DEFINITIONS(-DPROJECT_TEST_SOURCES_DIR="${CMAKE_SOURCE_DIR}/tests")

  SET(PROTOCOL_TEST protocol_test)
  ADD_EXECUTABLE(${PROTOCOL_TEST}
    ${CMAKE_SOURCE_DIR}/tests/test_serializer.cpp
  )
  TARGET_INCLUDE_DIRECTORIES(${PROTOCOL_TEST} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${COMMON_INCLUDE_DIR}
  )
  TARGET_LINK_LIBRARIES(${PROTOCOL_TEST}
    ${PROTOCOL_LIBRARY} gtest gtest_main
  )
ENDIF(DEVELOPER_ENABLE_TESTS)
