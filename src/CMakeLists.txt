set(target ${MP2_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_INCLUDE}/*.h*")

add_library(${target} STATIC "${hdrs}")
target_link_libraries(${target} ${LIBRARY_DEPS})
set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)