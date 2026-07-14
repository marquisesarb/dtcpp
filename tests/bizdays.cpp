#include <iostream>
#include <cassert>
#include <dtcpp/bizdays.hpp>

using namespace dtcpp::bizdays;

void templateTestAdjBusinessDay(const HolidayCalendar& holiday, const BusinessDayConvention& bdc, const std::vector<int>& raw, const std::vector<int>& result) {

    for (int i = 0; i<result.size(); i++) {

        DateTime newDateTime = adjustDate(DateTime(raw[i], EpochTimestampType::SECONDS),holiday, bdc);
        assert(newDateTime.getTimestamp() == result[i]);
    }
}

void testAdjBusinessDays() {

    std::vector<int> raw = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824854400,
        1840665600, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982707200,
        1998432000, 2014243200, 2029968000, 2045779200, 2061504000,
        2077315200
    };

    std::vector<int> resultFollow = {
        1761868800, 1777507200, 1793318400, 1809043200, 1825027200,
        1840752000, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982880000,
        1998604800, 2014329600, 2030054400, 2045779200, 2061504000,
        2077315200
    };

    std::vector<int> resultPreceding = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824768000,
        1840492800, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982620800,
        1998345600, 2014070400, 2029795200, 2045779200, 2061504000,
        2077315200
    };

    std::vector<int> resultModFollow = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824768000,
        1840492800, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982620800,
        1998345600, 2014329600, 2029795200, 2045779200, 2061504000,
        2077315200
    };

    std::vector<int> resultModPreceding = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824768000,
        1840492800, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982620800,
        1998345600, 2014070400, 2029795200, 2045779200, 2061504000,
        2077315200
    };

    templateTestAdjBusinessDay(HolidayCalendar::NONE, BusinessDayConvention::FOLLOWING, raw, raw); 
    templateTestAdjBusinessDay(HolidayCalendar::WEEK_END_OFF, BusinessDayConvention::FOLLOWING, raw, resultFollow); 
    templateTestAdjBusinessDay(HolidayCalendar::WEEK_END_OFF, BusinessDayConvention::MODIFIED_FOLLOWING, raw, resultModFollow); 
    templateTestAdjBusinessDay(HolidayCalendar::WEEK_END_OFF, BusinessDayConvention::PRECEDING, raw, resultPreceding); 
    templateTestAdjBusinessDay(HolidayCalendar::WEEK_END_OFF, BusinessDayConvention::MODIFIED_PRECEDING, raw, resultModPreceding); 
}

void templateTestUSFederalCalendar(DateTime refDate, DateTime follow, DateTime preceding, DateTime modFollow, DateTime modPrec) {

    assert(isBusinessDay(refDate,HolidayCalendar::US_FEDERAL_RESERVE)==false);
    assert(adjustDate(
        refDate, HolidayCalendar::US_FEDERAL_RESERVE ,BusinessDayConvention::FOLLOWING) == follow);
    assert(adjustDate(
        refDate ,HolidayCalendar::US_FEDERAL_RESERVE ,BusinessDayConvention::PRECEDING) == preceding);
    assert(adjustDate(
        refDate, HolidayCalendar::US_FEDERAL_RESERVE, BusinessDayConvention::MODIFIED_FOLLOWING) == modFollow);
    assert(adjustDate(
        refDate, HolidayCalendar::US_FEDERAL_RESERVE, BusinessDayConvention::MODIFIED_PRECEDING) == modPrec);
}

void testUSFederalCalendar() {

    // New year
    templateTestUSFederalCalendar(DateTime(2024,1,1), DateTime(2024,1,2), DateTime(2023,12,29), DateTime(2024,1,2), DateTime(2024,1,2));
    // MLK
    templateTestUSFederalCalendar(DateTime(2024,1,15), DateTime(2024,1,16), DateTime(2024,1,12), DateTime(2024,1,16), DateTime(2024,1,12));
    // Washington Birthday
    templateTestUSFederalCalendar(DateTime(2024,2,19), DateTime(2024,2,20), DateTime(2024,2,16), DateTime(2024,2,20), DateTime(2024,2,16));
    // Memorial 
    templateTestUSFederalCalendar(DateTime(2024,5,27), DateTime(2024,5,28), DateTime(2024,5,24), DateTime(2024,5,28), DateTime(2024,5,24));
    // Juneteeth
    templateTestUSFederalCalendar(DateTime(2024,6,19), DateTime(2024,6,20), DateTime(2024,6,18), DateTime(2024,6,20), DateTime(2024,6,18));
    // Independance Day
    templateTestUSFederalCalendar(DateTime(2024,7,4), DateTime(2024,7,5), DateTime(2024,7,3), DateTime(2024,7,5), DateTime(2024,7,3));
    // Labor day 
    templateTestUSFederalCalendar(DateTime(2024,9,2), DateTime(2024,9,3), DateTime(2024,8,30), DateTime(2024,9,3), DateTime(2024,9,3));
    // Columbus day 
    templateTestUSFederalCalendar(DateTime(2024,10,14), DateTime(2024,10,15), DateTime(2024,10,11), DateTime(2024,10,15), DateTime(2024,10,11));
    // Veterans Day
    templateTestUSFederalCalendar(DateTime(2024,11,11), DateTime(2024,11,12), DateTime(2024,11,8), DateTime(2024,11,12), DateTime(2024,11,8));
    // Thanksgiving 
    templateTestUSFederalCalendar(DateTime(2024,11,28), DateTime(2024,11,29), DateTime(2024,11,27), DateTime(2024,11,29), DateTime(2024,11,27));
    // Christmas 
    templateTestUSFederalCalendar(DateTime(2024,12,25), DateTime(2024,12,26), DateTime(2024,12,24), DateTime(2024,12,26), DateTime(2024,12,24));

}

int main() {

    testAdjBusinessDays();
    testUSFederalCalendar();
    std::cout << "All tests for the module bizdays have been passed succesfully!" << std::endl;
    return 0; 
}