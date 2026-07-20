include(CTest)

set(TESTS

    dtcpp-toolbox tests/toolbox.cpp
    dtcpp-timedelta tests/timedelta.cpp
    dtcpp-datetime tests/datetime.cpp
    dtcpp-sequence tests/sequence.cpp
    dtcpp-timeserie tests/timeserie.cpp
    dtcpp-calendars-interface tests/calendars/interface.cpp
    dtcpp-calendars-usfed tests/calendars/usfed.cpp
    dtcpp-finance-tenor tests/finance/tenor.cpp
    dtcpp-finance-daycount tests/finance/daycount.cpp
    dtcpp-finance-bondscheduler tests/finance/bondscheduler.cpp

)

while(TESTS)
    list(POP_FRONT TESTS test_name test_file)

    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE dtcpp)

    add_test(NAME ${test_name} COMMAND ${test_name})
endwhile()