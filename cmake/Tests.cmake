enable_testing()

foreach(test_file bizdays finance objects toolbox)
    add_executable(dtcpptests-${test_file} tests/${test_file}.cpp)
    target_link_libraries(dtcpptests-${test_file} dtcpp)
    add_test(NAME ${test_file} COMMAND dtcpptests-${test_file})
endforeach()

