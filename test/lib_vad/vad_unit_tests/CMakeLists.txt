
if( NOT ${Python3_FOUND} )
  message(FATAL_ERROR "Python3 not found for running . ") 
endif()

#copy conftest.py in the build directory since pytest_collect_file only collects tests from the directory tree where conftest.py is present
configure_file( conftest.py conftest.py COPYONLY ) 

if (NOT DEFINED TESTS_SPEEDUP_FACTOR)
    set (TESTS_SPEEDUP_FACTOR 1)
endif()
message( STATUS "Unit tests speedup factor ${TESTS_SPEEDUP_FACTOR}" )

## Sources
# audio_test_tools (old test_wav_vad)
set( AUDIO_TEST_TOOLS_PATH ${TEST_ONLY_DEPS_ROOT}/audio_test_tools/audio_test_tools )
list( APPEND AUDIO_TEST_TOOLS_SOURCES ${AUDIO_TEST_TOOLS_PATH}/src/testing.xc ${AUDIO_TEST_TOOLS_PATH}/src/floating_fft.xc)

## LIB_AI for unit test comparison
file( GLOB_RECURSE LIB_AI_SOURCES_C  ${TEST_ONLY_DEPS_ROOT}/lib_ai/lib_ai/src/*.c )
file( GLOB_RECURSE LIB_AI_SOURCES_XC  ${TEST_ONLY_DEPS_ROOT}/lib_ai/lib_ai/src/*.xc )
file( GLOB_RECURSE LIB_AI_SOURCES_ASM  ${TEST_ONLY_DEPS_ROOT}/lib_ai/lib_ai/src/*.S )
## cmake doesn't recognize .S files as assembly by default
set_source_files_properties(LIB_AI_SOURCES_ASM  PROPERTIES LANGUAGE ASM)

set( LIB_AI_SOURCES  ${LIB_AI_SOURCES_C} ${LIB_AI_SOURCES_XC} ${LIB_AI_SOURCES_ASM})
set( LIB_AI_INCLUDES ${TEST_ONLY_DEPS_ROOT}/lib_ai/lib_ai/api/ ${TEST_ONLY_DEPS_ROOT}/lib_ai/lib_ai/src/ ${XCORE_SDK_PATH}/modules/utils/api)

#old lib_vad for comparison
set( LIB_OLD_VAD_SOURCES ${TEST_ONLY_DEPS_ROOT}/lib_vad/lib_vad/src/vad_mel_compute.xc)

## executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Set unity runner generate script
set( GEN_RUNNER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/generate_unity_runner.py )

# Create directory for runner files
set( RUNNERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/src.runners )
file( MAKE_DIRECTORY ${RUNNERS_DIR} )

file( GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c )

# For every source file in vad_unit_tests/src
foreach( testfile ${TEST_SOURCES} )
    # Get test name
    #cmake_path( GET testfile STEM TESTNAME )
    get_filename_component(TESTNAME ${testfile} NAME_WLE)
    
    # Create runner file directory
    file( MAKE_DIRECTORY ${RUNNERS_DIR}/${TESTNAME} )

    #########
    ## Create runner file
    set( RUNNER_FILE ${RUNNERS_DIR}/${TESTNAME}/${TESTNAME}_Runner.c )
    set( GEN_RUNNER_SCRIPT_BYPRODUCTS ${RUNNER_FILE} )

    unset(GEN_RUNNER_SCRIPT_ARGS) 
    list(APPEND GEN_RUNNER_SCRIPT_ARGS --project-root ${UNITY_PATH}/.. )
    list(APPEND GEN_RUNNER_SCRIPT_ARGS --source-file ${testfile} )
    list(APPEND GEN_RUNNER_SCRIPT_ARGS --runner-file ${RUNNER_FILE})

    ## Add command to generate runner file
    add_custom_command(
        OUTPUT ${RUNNER_FILE}
        COMMAND ${Python3_EXECUTABLE} ${GEN_RUNNER_SCRIPT} ${GEN_RUNNER_SCRIPT_ARGS}
        COMMENT "Generating VAD runner" )
    
    if (${testfile} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR}/src/test_compare_mel_compute.c )
        set(EXTRA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/for_mel_test/)
    endif()

    ######################################
    ## Add a build target
   add_executable(fwk_voice_${TESTNAME})

    target_sources(fwk_voice_${TESTNAME}
        PRIVATE
            ${testfile}
            ${RUNNER_FILE}
            ${AUDIO_TEST_TOOLS_SOURCES}
            ${LIB_AI_SOURCES}
            ${LIB_OLD_VAD_SOURCES})


    target_include_directories(fwk_voice_${TESTNAME}
        PRIVATE
            src
            ${LIB_DSP_PATH}/lib_dsp/api #Can't figure out why this is needed when fwk_voice_test_deps::lib_dsp is already being linked.
            ${AUDIO_TEST_TOOLS_PATH}/api
            ${LIB_AI_INCLUDES}
            ${EXTRA_INCLUDES}
        )

    target_link_libraries(fwk_voice_${TESTNAME} 
        PUBLIC
            fwk_voice_test_deps::lib_dsp
            fwk_voice::vad
            fwk_voice::test::shared::test_utils
            fwk_voice::test::shared::unity
            )

    if(${CMAKE_SYSTEM_NAME} STREQUAL XCORE_XS3A)
        target_compile_options(fwk_voice_${TESTNAME}
            PRIVATE 
                "-DUNITY_SUPPORT_64"
                "-Wno-xcore-fptrgroup"
                "-report"
                "-DSPEEDUP_FACTOR=${TEST_SPEEDUP_FACTOR}")

        target_link_options(fwk_voice_${TESTNAME}
            PRIVATE
                "-target=${XCORE_TARGET}")
    else()
        target_link_libraries(fwk_voice_${TESTNAME} m)
    endif()
endforeach()

