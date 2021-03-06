
if(WIN32)
set(GDAL_ROOT ${WORKSPACE}/../thirdparty/gdal)
else()
set(GDAL_ROOT ${WORKSPACE}/thirdparty/gdal/gdal-2.0.1)
endif()
include(cmake/FindGDAL.cmake)

message("FindQt begin")
set(CMAKE_PREFIX_PATH ${WORKSPACE}/../../Qt/Qt5.4.0/5.4/msvc2013_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5GUI)
find_package(Qt5Quick)
find_package(Qt5Qml)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5GUI_INCLUDE_DIRS})
include_directories(${Qt5Quick_INCLUDE_DIRS})
include_directories(${Qt5Qml_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5GUI_DEFINITIONS})
add_definitions(${Qt5Quick_DEFINITIONS})
add_definitions(${Qt5Qml_DEFINITIONS})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}
                    ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}
                    ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}
                    ${Qt5GUI_EXECUTABLE_COMPILE_FLAGS}
                    ${Qt5Quick_EXECUTABLE_COMPILE_FLAGS}
                    ${Qt5Qml_EXECUTABLE_COMPILE_FLAGS}
 )
set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB}
                    ${Qt5Core_LIBRARIES}
                    ${Qt5Widgets_LIBRARIES}
                    ${Qt5GUI_LIBRARIES}
                    ${Qt5Quick_LIBRARIES}
                    ${Qt5Qml_LIBRARIES}
)

message("FindQt done")




#if(UNIX)
#    set(BOOST_ROOT ${WORKSPACE}/thirdparty/boost/boost-1.53.0)
#    find_package(Boost COMPONENTS system filesystem REQUIRED)
#endif(UNIX)
#if(WIN32)
#    set(BOOST_ROOT ${WORKSPACE}/../thirdparty/boost/winboost_1_53_0)
    #find_package(Boost COMPONENTS system filesystem REQUIRED)
#    find_package(Boost REQUIRED COMPONENTS filesystem)
    #set(Boost_INCLUDE_DIR  ${WORKSPACE}/thirdparty/boost/winboost_1_53_0/include)
    #set(Boost_LIBRARIES  ${WORKSPACE}/thirdparty/boost/winboost_1_53-0/lib64-msvc-9.0)
    #  set(BOOST_ROOT C:/local)
#endif(WIN32)
#if(Boost_FOUND)
    #include_directories(${Boost_INCLUDE_DIR})
    #message(${Boost_LIBRARIES})
    #set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${Boost_LIBRARIES})
#endif()

message("thirdparty done")
