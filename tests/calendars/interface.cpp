#include <cassert>
#include <dtcpp/calendars/interface.hpp>

using namespace dtcpp;

void templateTestAdjBusinessDay(const BusinessCalendar& calendar, const BusinessDayConvention& bdc, const std::vector<int>& raw, const std::vector<int>& result) {

    for (int i = 0; i<result.size(); i++) {

        DateTime newDateTime = calendar.adjustForBusiness(DateTime(raw[i], EpochTimestampType::SECONDS), bdc);
        assert(newDateTime.timestamp() == result[i]);
    }
}

int main() {

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

    templateTestAdjBusinessDay(dtcpp::NoHolidayCalendar(), BusinessDayConvention::FOLLOWING, raw, raw); 
    templateTestAdjBusinessDay(dtcpp::WeekEndOffCalendar(), BusinessDayConvention::FOLLOWING, raw, resultFollow); 
    templateTestAdjBusinessDay(dtcpp::WeekEndOffCalendar(), BusinessDayConvention::MODIFIED_FOLLOWING, raw, resultModFollow); 
    templateTestAdjBusinessDay(dtcpp::WeekEndOffCalendar(), BusinessDayConvention::PRECEDING, raw, resultPreceding); 
    templateTestAdjBusinessDay(dtcpp::WeekEndOffCalendar(), BusinessDayConvention::MODIFIED_PRECEDING, raw, resultModPreceding); 

    return 0;
}