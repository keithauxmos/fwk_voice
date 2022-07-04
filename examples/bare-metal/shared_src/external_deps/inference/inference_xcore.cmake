
set(TOP_DIR ${CMAKE_BINARY_DIR}/fwk_voice_deps)

set(NNLIB_DIR "${TOP_DIR}/lib_nn/lib_nn")

set(TFLIB_DIR
  "${TOP_DIR}/lib_tflite_micro/lib_tflite_micro")

set(TFLITE_SRC_DIR
  "${TOP_DIR}/lib_tflite_micro/lib_tflite_micro/submodules/tflite-micro/tensorflow/lite")

set(TFLIB_SRC_DIR
  "${TFLIB_DIR}/src/tflite-xcore-kernels")


unset(LIB_NN_SOURCES)
file(GLOB_RECURSE LIB_NN_SOURCES_XCORE_XS3A ${NNLIB_DIR}/src/asm/*.S)
file(GLOB_RECURSE LIB_NN_SOURCES_C   ${NNLIB_DIR}/src/c/*.c)
file(GLOB_RECURSE LIB_NN_SOURCES_CPP ${NNLIB_DIR}/src/cpp/*.cpp)
list(APPEND LIB_NN_SOURCES ${LIB_NN_SOURCES_C} ${LIB_NN_SOURCES_CPP}) 

unset(LIB_NN_INCLUDES)
list(APPEND LIB_NN_INCLUDES ${NNLIB_DIR}/api)
list(APPEND LIB_NN_INCLUDES ${NNLIB_DIR}/..)

unset(TFLITE_SOURCES)
## tflite-micro runtime sources
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/c/common.c)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/core/api/error_reporter.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/core/api/flatbuffer_conversions.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/core/api/op_resolver.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/core/api/tensor_utils.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/kernels/kernel_util.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/kernels/internal/quantization_util.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/flatbuffer_utils.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/memory_helpers.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/micro_allocator.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/micro_error_reporter.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/micro_graph.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/micro_interpreter.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/micro_profiler.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/micro_utils.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/micro_string.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/recording_micro_allocator.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/recording_simple_memory_allocator.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/simple_memory_allocator.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/memory_planner/greedy_memory_planner.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/memory_planner/linear_memory_planner.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/schema/schema_utils.cc)
## tflite-micro operator sources
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/fully_connected_common.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/kernel_util.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/quantize_common.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/activations.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/add.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/add_n.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/arg_min_max.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/ceil.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/circular_buffer.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/comparisons.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/concatenation.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/conv.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/conv_common.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/cumsum.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/depthwise_conv.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/depthwise_conv_common.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/dequantize.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/detection_postprocess.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/elementwise.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/elu.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/floor.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/fully_connected.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/l2norm.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/logical.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/logistic.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/maximum_minimum.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/mul.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/neg.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/pack.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/pad.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/pooling.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/prelu.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/quantize.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/reduce.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/reshape.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/shape.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/resize_nearest_neighbor.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/round.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/split.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/split_v.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/squeeze.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/strided_slice.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/sub.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/svdf.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/svdf_common.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/tanh.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/unpack.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/hard_swish.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/floor_div.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/floor_mod.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/l2_pool_2d.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/leaky_relu.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/depth_to_space.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/transpose_conv.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/resize_bilinear.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/batch_to_space_nd.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/space_to_batch_nd.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/transpose.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/pooling_common.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/expand_dims.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/space_to_depth.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/circular_buffer.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/activations_common.cc)
list(APPEND TFLITE_SOURCES ${TFLITE_SRC_DIR}/micro/kernels/logistic_common.cc)

unset(TFLITE_INCLUDES)
list(APPEND TFLITE_INCLUDES  "${TFLIB_DIR}/submodules/tflite-micro")
list(APPEND TFLITE_INCLUDES  "${TFLIB_DIR}/submodules/gemmlowp")
list(APPEND TFLITE_INCLUDES  "${TFLIB_DIR}/submodules/ruy")
list(APPEND TFLITE_INCLUDES  "${TFLIB_DIR}/submodules/flatbuffers/include")

unset(TFLIB_SOURCES)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/micro_time.cc)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/../inference_engine.cc)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/xcore_bsign.cc)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/xcore_custom_options.cc)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/xcore_conv2d_v2.cc)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/xcore_error_reporter.cc)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/xcore_interpreter.cc)
list(APPEND TFLIB_SOURCES ${TFLIB_SRC_DIR}/xcore_profiler.cc)

file(GLOB_RECURSE TFLIB_SOURCES_ASM ${TFLIB_DIR}/src/*.S)

unset(TFLIB_INCLUDES)
list(APPEND TFLIB_INCLUDES ${TFLIB_DIR}/..)
list(APPEND TFLIB_INCLUDES ${TFLIB_DIR}/api)
list(APPEND TFLIB_INCLUDES ${TFLIB_DIR}/src)
list(APPEND TFLIB_INCLUDES ${TFLIB_DIR}/src/tflite-xcore-kernels)

