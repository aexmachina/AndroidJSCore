set(WTF_LIBRARY_TYPE STATIC)
set(WTF_OUTPUT_NAME WTFGTK)

list(APPEND WTF_SOURCES
    glib/GLibUtilities.cpp
    glib/GRefPtr.cpp
    glib/MainThreadGLib.cpp
    glib/RunLoopGLib.cpp
    glib/WorkQueueGLib.cpp
    icu/stubdata.c
)

list(APPEND WTF_LIBRARIES
    ${GLIB_GIO_LIBRARIES}
    ${GLIB_GOBJECT_LIBRARIES}
    ${GLIB_LIBRARIES}
)

list(APPEND WTF_SYSTEM_INCLUDE_DIRECTORIES
    ${GLIB_INCLUDE_DIRS}
)

