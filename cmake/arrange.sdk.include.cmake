message("arrange.sdk.include.cmake")

set(DESTDIR ${CMAKE_BINARY_DIR})
set(SRCDIR ${CMAKE_SOURCE_DIR})
message("${SRCDIR} -> ${DESTDIR} ${CMAKE_CURRENT_SOURCE_DIR}")


 #Organize the SDK header files
 set(sdk_include_path "${CMAKE_BINARY_DIR}/include")
 message("sdk_include_path: ${sdk_include_path}")
 file(MAKE_DIRECTORY "${sdk_include_path}")

file(GLOB_RECURSE sdk_include_files "sdk/export.h")
file(COPY ${sdk_include_files} DESTINATION "${sdk_include_path}")

#  # Sdk-sdk header files
#  file(MAKE_DIRECTORY "${sdk_include_path}/sdk")
#  file(GLOB_RECURSE sdk_include_files "sdk/*.h")
#  file(COPY ${sdk_include_files} DESTINATION "${sdk_include_path}/sdk")
#  # Sdk-utility header files
#  file(MAKE_DIRECTORY "${sdk_include_path}/utility")
#  file(GLOB_RECURSE utility_include_files "utility/*.h" "utility/*.hpp")
#  file(COPY ${utility_include_files} DESTINATION "${sdk_include_path}/utility")
#  # Sdk-base header files
#  file(MAKE_DIRECTORY "${sdk_include_path}/base")
#  file(GLOB_RECURSE base_include_files "base/system.h" "base/app_config.h" "base/easylogging*.h")
#  file(COPY ${base_include_files} DESTINATION "${sdk_include_path}/base")
#  # Sdk-network header files
#  file(MAKE_DIRECTORY "${sdk_include_path}/network")
#  file(GLOB_RECURSE network_include_files "network/message.h" "network/circle_buffer.h")
#  file(COPY ${network_include_files} DESTINATION "${sdk_include_path}/network")
#  # Sdk-actor header files
#  file(MAKE_DIRECTORY "${sdk_include_path}/actor")
#  file(GLOB_RECURSE actor_include_files "actor/actor.h")
#  file(COPY ${actor_include_files} DESTINATION "${sdk_include_path}/actor")

#  # Library-yaml header files
#  file(COPY "./libraries/yaml-cpp/include/yaml-cpp" DESTINATION "${sdk_include_path}/")

# # Library-openssl header files
# file(COPY "./libraries/openssl-cmake/include/openssl" DESTINATION "${sdk_include_path}/")
# file(COPY "./libraries/openssl-cmake/include/crypto" DESTINATION "${sdk_include_path}/")
# file(COPY "./libraries/openssl-cmake/include/internal" DESTINATION "${sdk_include_path}/")
# file(COPY "${CMAKE_BINARY_DIR}/src/libraries/openssl-cmake/include/openssl/opensslconf.h" DESTINATION "${sdk_include_path}/openssl/")

#  # Library-zlib header files
#  file(MAKE_DIRECTORY "${sdk_include_path}/zlib")
#  file(GLOB_RECURSE zlib_include_files "libraries/zlib/*.h")
#  file(COPY ${zlib_include_files} DESTINATION "${sdk_include_path}/zlib")
