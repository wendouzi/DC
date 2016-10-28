#add_subdirectory(res)
file (GLOB qmlRes qml.qrc)
QT5_ADD_RESOURCES(qmlResource ${qmlRes})
file (GLOB picRes pictures.qrc)
QT5_ADD_RESOURCES(picResource ${picRes})
set(SRC base64.cpp CCLogin.cpp HomePage.cpp ischedule.cpp
         main.cpp QmlPlugin.cpp Home.cpp imgcontrol.cpp
         geoshape.cpp GFimg.cpp main.cpp
         tinystr.cpp tinyxml.cpp tinyxmlerror.cpp
         tinyxmlparser.cpp   )
add_executable(testdis ${SRC} ${qmlResource} ${picResource})
target_link_libraries(testdis ${THIRD_PARTY_LIB})
