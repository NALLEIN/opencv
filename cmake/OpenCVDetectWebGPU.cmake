ocv_clear_vars(HAVE_WEBGPU)
ocv_clear_vars(DAWN_METAL)
if(WITH_WEBGPU)
  set(WEBGPU_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/3rdparty/include/webgpu/include")
  set(WEBGPU_LIBRARIES "${PROJECT_SOURCE_DIR}/3rdparty/include/webgpu/lib")
endif()

try_compile(VALID_WEBGPU
      "${OpenCV_BINARY_DIR}"
      "${OpenCV_SOURCE_DIR}/cmake/checks/webgpu.cpp"
      CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${WEBGPU_INCLUDE_DIRS}" "-DLINK_LIBRARIES:STRING=${WEBGPU_LIBRARIES}"
      OUTPUT_VARIABLE TRY_OUT
      )
if(NOT ${VALID_WEBGPU})
  message(WARNING "Can't use WebGPU-Dawn")
  return()
endif()
message(AUTHOR_WARNING "Use Dawn for native WebGPU")

set(HAVE_WEBGPU 1)
if(APPLE)
  set(DAWN_METAL 1)
endif()

if(NOT EMSCRIPTEN AND HAVE_WEBGPU)
  include_directories(${WEBGPU_INCLUDE_DIRS})
  link_directories(${WEBGPU_LIBRARIES})
  link_libraries(dawn_proc dawn_native dawn_wire)
endif() 