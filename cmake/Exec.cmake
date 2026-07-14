add_executable(dtcpp-toolbox ${CMAKE_CURRENT_SOURCE_DIR}/tests/toolbox.cpp)
target_link_libraries(dtcpp-toolbox PUBLIC dtcpp)

add_executable(dtcpp-objects ${CMAKE_CURRENT_SOURCE_DIR}/tests/objects.cpp)
target_link_libraries(dtcpp-objects PUBLIC dtcpp)

add_executable(dtcpp-finance ${CMAKE_CURRENT_SOURCE_DIR}/tests/finance.cpp)
target_link_libraries(dtcpp-finance PUBLIC dtcpp)

add_executable(dtcpp-bizdays ${CMAKE_CURRENT_SOURCE_DIR}/tests/bizdays.cpp)
target_link_libraries(dtcpp-bizdays PUBLIC dtcpp)
