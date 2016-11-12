

set(SRC geoshape.cpp GFimg.cpp main.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp   )
add_executable(testdis ${SRC})
target_link_libraries(testdis ${THIRD_PARTY_LIB})

set(SRCextract geoshape GFimg.cpp testextract.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp   )
add_executable(extract ${SRCextract})
target_link_libraries(extract ${THIRD_PARTY_LIB})
#set(parSRC parsexml.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp)
#add_executable(par ${parSRC})
#target_link_libraries(par ${THIRD_PARTY_LIB})
set(UISRC file_chooser.cpp geoshape.cpp GFimg.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp        )
add_executable(gf_1 ${UISRC})
target_link_libraries(gf_1 ${THIRD_PARTY_LIB})
