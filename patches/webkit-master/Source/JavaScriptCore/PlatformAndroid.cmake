SET(GCC_WTF_COMPILE_FLAGS "-D__STDC_LIMIT_MACROS=1 -DUCONFIG_ONLY_COLLATION=1 -Wno-unused-parameter")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_WTF_COMPILE_FLAGS}" )

FIND_LIBRARY( ANDROID_LOG_LIBRARY log )
FIND_LIBRARY( ANDROID_CPPSTD_LIBRARY stdc++ )

#        FIND_LIBRARY( ANDROID_ANDROID_LIBRARY android )

# Because Android has multiple architectures (e.g. armeabi, armeabi-v7a, x86)
# but doesn't have fat binaries like Darwin, nor does it use file suffixes,
# we need to override the library install path to
# put products in the correct architecture specific subdirectory.
# -DANDROID_ABI=<arch> should have been specified on cmake invocation.
set(LIB_INSTALL_DIR "lib/${ANDROID_ABI}")

list(APPEND JavaScriptCore_SOURCES
    android/JSContext.cpp
    android/JSObject.cpp
    android/JSString.cpp
    android/JSValue.cpp
)

list(APPEND LIBRARIES_JavaScriptCore
    ${ANDROID_LOG_LIBRARY}
    ${ANDROID_CPPSTD_LIBRARY}
#    ${ANDROID_ANDROID_LIBRARY}
)

list(APPEND JavaScriptCore_SYSTEM_INCLUDE_DIRECTORIES
    ${GLIB_INCLUDE_DIRS}
    ${ICU_INCLUDE_DIRS}
    ${WTF_DIR}
)

# This will copy the Android.mk used for NDK_MODULE_PATH to the correct location in the install location.
# The include/.. is a workaround/hack. If I use ${CMAKE_INSTALL_PREFIX},
# the file gets copied into $CMAKE_INSTALL_PREFIX/$CMAKE_INSTALL_PREFIX,
# e.g. ~/Source/AndroidModules/JavaScriptCore is the target 
# specified by -DCMAKE_INSTALL_PREFIX=../AndroidModules/JavaScriptCore
# and the file gets written to ~/Source/AndroidModules/JavaScriptCore/AndroidModules/JavaScriptCore
install(FILES android/Android.mk DESTINATION include/..)

