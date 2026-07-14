#include <iostream>
#include <cassert>
#include <dtcpp/toolbox.hpp>



void testCheck() {

    assert(dtcpp::toolbox::isCivilDateValid(2025,10,12)==true); 
    assert(dtcpp::toolbox::isCivilDateValid(2025,13,12)==false); 
    assert(dtcpp::toolbox::isCivilHourValid(25,30,30)==false);
    assert(dtcpp::toolbox::isCivilHourValid(23,30,30)==true);
    assert(dtcpp::toolbox::isCivilHourValid(0,1,12)==true);
    assert(dtcpp::toolbox::isCivilHourValid(0,0,12)==true);
    assert(dtcpp::toolbox::isCivilHourValid(0,0,0)==true); 
    assert(dtcpp::toolbox::isCivilDateValid(0,0,12)==false);
}

void testIsLeap() {

    assert(dtcpp::toolbox::isLeapYear(2024)); 
    assert(!dtcpp::toolbox::isLeapYear(2023)); 
}

void testDaysSinceEpoch() {

    assert(dtcpp::toolbox::getDaysSinceEpoch(1800,1,1)==-62091); 
    assert(dtcpp::toolbox::getDaysSinceEpoch(2025,7,18)==20287); 
    assert(dtcpp::toolbox::getDaysSinceEpoch(2000,12,12)==11303); 
}

void testCivilToTimestamp() {

    assert(dtcpp::toolbox::getTimestampFromCivilDateHour(1800,12,28,16,28,40)==-5333412680); 
    assert(dtcpp::toolbox::getTimestampFromCivilDateHour(2025,12,28,16,28,40)==1766939320);
    assert(dtcpp::toolbox::getTimestampFromCivilDateHour(2000,12,28,0,0,0)==977961600);  
}

void testTimestampToCivil() {

    assert(dtcpp::toolbox::getCivilFromTimestamp(-5333412680) == std::make_tuple(1800,12,28,16,28,40)); 
    assert(dtcpp::toolbox::getCivilFromTimestamp(1766939320) == std::make_tuple(2025,12,28,16,28,40)); 
    assert(dtcpp::toolbox::getCivilFromTimestamp(977961600) == std::make_tuple(2000,12,28,0,0,0)); 
}

void testStringToTimestammp() {

    assert(dtcpp::toolbox::getTimestampFromCivilDateHourString("2025-12-28 16:28:40", "YYYY-MM-DD HH:MM:SS")==1766939320);
    assert(dtcpp::toolbox::getTimestampFromCivilDateHourString("2000-12-28", "YYYY-MM-DD")==977961600); 
}

void testTimestampToString() {

    assert(dtcpp::toolbox::getCivilDateHourStringFromTimestamp(1766939320, "YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40");
    assert(dtcpp::toolbox::getCivilDateHourStringFromTimestamp(977961600, "YYYY-MM-DD")=="2000-12-28"); 

}

void testWeekDayFromTimestamp() {
    assert(dtcpp::toolbox::getWeekDayFromTimestamp(977961600)==4); 
    assert(dtcpp::toolbox::getWeekDayFromTimestamp(978134400)==6); 
    assert(dtcpp::toolbox::getWeekDayFromTimestamp(977702400)==1); 
}

void testWeekDayFromCivilDate() {
    assert(dtcpp::toolbox::getWeekDayFromCivilDate(2000,12,28)==4); 
    assert(dtcpp::toolbox::getWeekDayFromCivilDate(2000,12,30)==6); 
    assert(dtcpp::toolbox::getWeekDayFromCivilDate(2000,12,25)==1); 
}

void testNthWeekDayInMonth() {

    assert(dtcpp::toolbox::getFirstWeekDayOfMonth(2025,9,2)==2); 
    assert(dtcpp::toolbox::getSecondWeekDayOfMonth(2025,9,2)==9); 
    assert(dtcpp::toolbox::getThirdWeekDayOfMonth(2025,9,2)==16); 
    assert(dtcpp::toolbox::getFourthWeekDayOfMonth(2025,9,2)==23); 
    assert(dtcpp::toolbox::getLastWeekDayOfMonth(2025,9,2)==30); 

    assert(dtcpp::toolbox::getFirstWeekDayOfMonth(2025,9,3)==3); 
    assert(dtcpp::toolbox::getSecondWeekDayOfMonth(2025,9,3)==10); 
    assert(dtcpp::toolbox::getThirdWeekDayOfMonth(2025,9,3)==17); 
    assert(dtcpp::toolbox::getFourthWeekDayOfMonth(2025,9,3)==24); 
    assert(dtcpp::toolbox::getLastWeekDayOfMonth(2025,9,3)==24); 

    assert(dtcpp::toolbox::getFirstWeekDayOfMonth(2025,9,1)==1); 
    assert(dtcpp::toolbox::getSecondWeekDayOfMonth(2025,9,1)==8); 
    assert(dtcpp::toolbox::getThirdWeekDayOfMonth(2025,9,1)==15); 
    assert(dtcpp::toolbox::getFourthWeekDayOfMonth(2025,9,1)==22); 
    assert(dtcpp::toolbox::getLastWeekDayOfMonth(2025,9,1)==29); 
}

void testAddYears() {

    assert(dtcpp::toolbox::addYearsToCivilDate(2025,3,15,3)==std::make_tuple(2028,3,15)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(2025,3,15,-3)==std::make_tuple(2022,3,15)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(2024,2,29,1)==std::make_tuple(2025,2,28)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(2024,2,29,-1)==std::make_tuple(2023,2,28)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(1997,8,15,28)==std::make_tuple(2025,8,15)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(2025,8,15,-28)==std::make_tuple(1997,8,15)); 
}

void testAddMonths() {

    assert(dtcpp::toolbox::addMonthsToCivilDate(2025,12,29,2)==std::make_tuple(2026,2,28)); 
    assert(dtcpp::toolbox::addMonthsToCivilDate(2025,12,29,26)==std::make_tuple(2028,2,29)); 
    assert(dtcpp::toolbox::addMonthsToCivilDate(2025,3,2,4)==std::make_tuple(2025,7,2)); 
    assert(dtcpp::toolbox::addMonthsToCivilDate(2025,3,2,12)==std::make_tuple(2026,3,2)); 
    
    assert(dtcpp::toolbox::addMonthsToCivilDate(2026,3,1,-2)==std::make_tuple(2026,1,1)); 
    assert(dtcpp::toolbox::addMonthsToCivilDate(2028,2,29,-26)==std::make_tuple(2025,12,29)); 
    assert(dtcpp::toolbox::addMonthsToCivilDate(2025,7,2,-4)==std::make_tuple(2025,3,2)); 
    assert(dtcpp::toolbox::addMonthsToCivilDate(2026,3,2,-12)==std::make_tuple(2025,3,2)); 
}

void testConsistencyAddMonthYear() {

    assert(dtcpp::toolbox::addYearsToCivilDate(2025,3,15,3)==dtcpp::toolbox::addMonthsToCivilDate(2025,3,15,3*12)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(2025,3,15,-3)==dtcpp::toolbox::addMonthsToCivilDate(2025,3,15,-3*12)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(2025,3,15,-1)==dtcpp::toolbox::addMonthsToCivilDate(2025,3,15,-1*12)); 
    assert(dtcpp::toolbox::addYearsToCivilDate(2025,3,15,1)==dtcpp::toolbox::addMonthsToCivilDate(2025,3,15,1*12)); 
}

int main() {

    testCheck();
    testIsLeap();
    testDaysSinceEpoch();
    testTimestampToCivil();
    testCivilToTimestamp();
    testStringToTimestammp();
    testTimestampToString();
    testWeekDayFromTimestamp();
    testWeekDayFromCivilDate();
    testNthWeekDayInMonth();
    testAddYears();
    testAddMonths();
    testConsistencyAddMonthYear();
    std::cout << "All tests for the toolbox module have been passed succesfully!" << std::endl; 
    return 0;
}