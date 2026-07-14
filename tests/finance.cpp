#include <iostream>
#include <cassert>
#include <dtcpp/finance.hpp>
#include <dtcpp/bizdays.hpp>
#include <dtcpp/objects.hpp>

bool isClose(double value1, double value2, double eps) {return (std::abs(value2-value1)<eps);}

void testYearFraction() {

    using namespace dtcpp::objects;
    using namespace dtcpp::finance;     

    // 25 Août 2025 21:00:00 
    DateTime referenceTime = DateTime(1756155600,EpochTimestampType::SECONDS); 
    // 14 Novembre 2026 21:00:00 
    DateTime d2 = DateTime(1794690000,EpochTimestampType::SECONDS); 
    // 18 Mai 2027 21:00:00 
    DateTime d3 = DateTime(1810674000,EpochTimestampType::SECONDS); 
    // 31 Octobre 2028 21:00:00 
    DateTime d4 = DateTime(1856638800,EpochTimestampType::SECONDS); 
    // 30 Septemmbre 2029 21:00:00 
    DateTime d5 = DateTime(1885496400,EpochTimestampType::SECONDS);

    assert(isClose(yearFraction(referenceTime,d2,DayCountConvention::ACTUAL_360),1.238888889, 1e-7));
    assert(isClose(yearFraction(referenceTime,d3, DayCountConvention::ACTUAL_360),1.752777778, 1e-7));
    assert(isClose(yearFraction(referenceTime,d4, DayCountConvention::ACTUAL_360),3.230555556, 1e-7));
    assert(isClose(yearFraction(referenceTime,d5, DayCountConvention::ACTUAL_360),4.158333333, 1e-7));

    assert(isClose(yearFraction(referenceTime,d2,DayCountConvention::ACTUAL_365),1.221917808, 1e-7));
    assert(isClose(yearFraction(referenceTime,d3,DayCountConvention::ACTUAL_365),1.728767123, 1e-7));
    assert(isClose(yearFraction(referenceTime,d4,DayCountConvention::ACTUAL_365),3.18630137, 1e-7));
    assert(isClose(yearFraction(referenceTime,d5,DayCountConvention::ACTUAL_365),4.101369863, 1e-7));

    assert(isClose(yearFraction(referenceTime,d2,DayCountConvention::ACTUAL_364),1.225274725, 1e-7));
    assert(isClose(yearFraction(referenceTime,d3,DayCountConvention::ACTUAL_364),1.733516484, 1e-7));
    assert(isClose(yearFraction(referenceTime,d4,DayCountConvention::ACTUAL_364),3.195054945, 1e-7));
    assert(isClose(yearFraction(referenceTime,d5,DayCountConvention::ACTUAL_364),4.112637363, 1e-7));

    assert(isClose(yearFraction(referenceTime,d2, DayCountConvention::BOND_BASIS30_360),1.219444444, 1e-7));
    assert(isClose(yearFraction(referenceTime,d3, DayCountConvention::BOND_BASIS30_360),1.730555556, 1e-7));
    assert(isClose(yearFraction(referenceTime,d4, DayCountConvention::BOND_BASIS30_360),3.183333333, 1e-7));
    assert(isClose(yearFraction(referenceTime,d5, DayCountConvention::BOND_BASIS30_360),4.097222222, 1e-7));

    assert(isClose(yearFraction(referenceTime,d2, DayCountConvention::E30_360),1.219444444, 1e-7));
    assert(isClose(yearFraction(referenceTime,d3, DayCountConvention::E30_360),1.730555556, 1e-7));
    assert(isClose(yearFraction(referenceTime,d4, DayCountConvention::E30_360),3.180555556, 1e-7));
    assert(isClose(yearFraction(referenceTime,d5, DayCountConvention::E30_360),4.097222222, 1e-7));

    assert(isClose(yearFraction(referenceTime,d2, DayCountConvention::ACTUAL_ACTUAL),1.221917808, 1e-7));
    assert(isClose(yearFraction(referenceTime,d3, DayCountConvention::ACTUAL_ACTUAL),1.728767123, 1e-7));
    assert(isClose(yearFraction(referenceTime-TimeDelta{0,21,0,0,0,0,0},d4-TimeDelta{0,21,0,0,0,0,0}, DayCountConvention::ACTUAL_ACTUAL),3.18402575, 1e-7));
    assert(isClose(yearFraction(referenceTime,d5, DayCountConvention::ACTUAL_ACTUAL),4.098630137, 1e-7));
    
}

void testForwardDateTenor() {

    using namespace dtcpp::objects;
    using namespace dtcpp::finance; 
    DateTime refDate(1769472000, EpochTimestampType::SECONDS);
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate,1).getTimestamp() == 1777248000));
    assert((Tenor{1,TenorType::DAYS}.getForwardDate(refDate,1).getTimestamp() == 1769558400));
    assert((Tenor{1,TenorType::WEEKS}.getForwardDate(refDate,1).getTimestamp() == 1770076800));
    assert((Tenor{7,TenorType::WEEKS}.getForwardDate(refDate,1).getTimestamp() == 1773705600));
    assert((Tenor{17,TenorType::DAYS}.getForwardDate(refDate,1).getTimestamp() == 1770940800));
    assert((Tenor{17,TenorType::MONTHS}.getForwardDate(refDate,1).getTimestamp() == 1814054400));
    assert((Tenor{3,TenorType::YEARS}.getForwardDate(refDate,1).getTimestamp() == 1864166400));
    assert((Tenor{18,TenorType::YEARS}.getForwardDate(refDate,1).getTimestamp() == 2337465600));
    DateTime refDate2(2026,1,29);
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,1) == DateTime(2026,4,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,2) == DateTime(2026,7,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,3) == DateTime(2026,10,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,4) == DateTime(2027,1,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,5) == DateTime(2027,4,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,6) == DateTime(2027,7,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,7) == DateTime(2027,10,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,8) == DateTime(2028,1,29)));

}

void testTenorOperators() {

    using namespace dtcpp::objects;
    using namespace dtcpp::finance; 
    assert((Tenor{7, TenorType::DAYS}==Tenor{1, TenorType::WEEKS}));
    assert((Tenor{14, TenorType::DAYS}==Tenor{2, TenorType::WEEKS}));

    assert((Tenor{15, TenorType::DAYS}>Tenor{2, TenorType::WEEKS}));
    assert((Tenor{8, TenorType::DAYS}>Tenor{1, TenorType::WEEKS}));

    assert((Tenor{1, TenorType::YEARS}<Tenor{2, TenorType::YEARS}));
    assert((Tenor{1, TenorType::YEARS}==Tenor{1, TenorType::YEARS}));

    assert((Tenor{1, TenorType::YEARS}>=Tenor{2, TenorType::MONTHS}));
    assert((Tenor{1, TenorType::YEARS}>=Tenor{1, TenorType::YEARS}));

}

void testTenorGetFactorMultiple() {

    using namespace dtcpp::objects;
    using namespace dtcpp::finance; 
    // Months
    assert((Tenor{12,TenorType::MONTHS}.getMultiple(Tenor{3,TenorType::MONTHS}) == 4));
    assert((Tenor{12,TenorType::MONTHS}.getMultiple(Tenor{5,TenorType::MONTHS}) == 0));
    assert((Tenor{3,TenorType::MONTHS}.getMultiple(Tenor{12,TenorType::MONTHS}) == 0));
    assert((Tenor{3,TenorType::MONTHS}.getFactor(Tenor{12,TenorType::MONTHS}) == 4));
    assert((Tenor{12,TenorType::MONTHS}.getFactor(Tenor{3,TenorType::MONTHS}) == 0));
    assert((Tenor{5,TenorType::MONTHS}.getFactor(Tenor{12,TenorType::MONTHS}) == 0));

    // Days and Weeks
    assert((Tenor{14,TenorType::DAYS}.getMultiple(Tenor{1,TenorType::WEEKS}) == 2));
    assert((Tenor{17,TenorType::DAYS}.getMultiple(Tenor{1,TenorType::WEEKS}) == 0));
    assert((Tenor{4,TenorType::WEEKS}.getMultiple(Tenor{14,TenorType::DAYS}) == 2));
    assert((Tenor{1,TenorType::WEEKS}.getFactor(Tenor{14,TenorType::DAYS}) == 2));
    assert((Tenor{1,TenorType::WEEKS}.getFactor(Tenor{17,TenorType::DAYS}) == 0));
    assert((Tenor{14,TenorType::DAYS}.getFactor(Tenor{4,TenorType::WEEKS}) == 2));

    // Months and Years
    assert((Tenor{10,TenorType::YEARS}.getMultiple(Tenor{6,TenorType::MONTHS}) == 20));
    assert((Tenor{6,TenorType::MONTHS}.getMultiple(Tenor{10,TenorType::YEARS}) == 0));
    assert((Tenor{10,TenorType::YEARS}.getFactor(Tenor{6,TenorType::MONTHS}) == 0));
    assert((Tenor{6,TenorType::MONTHS}.getFactor(Tenor{10,TenorType::YEARS}) == 20));

    assert((Tenor{10,TenorType::YEARS}.getMultiple(Tenor{7,TenorType::MONTHS}) == 0));
    assert((Tenor{7,TenorType::MONTHS}.getMultiple(Tenor{10,TenorType::YEARS}) == 0));
    assert((Tenor{10,TenorType::YEARS}.getFactor(Tenor{7,TenorType::MONTHS}) == 0));
    assert((Tenor{7,TenorType::MONTHS}.getFactor(Tenor{10,TenorType::YEARS}) == 0));

}

void testBondScheduler() {

    using namespace dtcpp::objects; 
    using namespace dtcpp::finance; 
    Tenor tenorFreq{3,TenorType::MONTHS};
    Tenor tenorMaturity{5,TenorType::YEARS};
    dtcpp::objects::DateTime startDate(2026,1,30);
    dtcpp::bizdays::HolidayCalendar hcal = dtcpp::bizdays::HolidayCalendar::NONE; 
    dtcpp::bizdays::BusinessDayConvention bdconv = dtcpp::bizdays::BusinessDayConvention::FOLLOWING; 

    dtcpp::objects::DatetimeSequence schedule = dtcpp::finance::bondSchedule(startDate, tenorFreq,tenorMaturity, bdconv, hcal, false, false); 
    assert(schedule.size() == 19);
    assert(schedule.asVector()[7] == DateTime(2028,1,30)); 
    assert(schedule.asVector()[12] == DateTime(2029,4,30));
    assert(schedule.asVector()[13] == DateTime(2029,7,30));

    schedule = dtcpp::finance::bondSchedule(startDate, tenorFreq,tenorMaturity, bdconv, hcal, true, false); 
    assert(schedule.size() == 20);
    assert(schedule.asVector()[0] == startDate); 
    assert(schedule.asVector()[8] == DateTime(2028,1,30)); 
    assert(schedule.asVector()[13] == DateTime(2029,4,30));
    assert(schedule.asVector()[14] == DateTime(2029,7,30));

    schedule = dtcpp::finance::bondSchedule(startDate, tenorFreq,tenorMaturity, bdconv, hcal, true, true); 
    assert(schedule.size() == 21);
    assert(schedule.asVector()[0] == startDate); 
    assert(schedule.asVector()[8] == DateTime(2028,1,30)); 
    assert(schedule.asVector()[13] == DateTime(2029,4,30));
    assert(schedule.asVector()[14] == DateTime(2029,7,30));
    assert(schedule.asVector()[20] == DateTime(2031,1,30));

    tenorFreq = {7,TenorType::MONTHS};
    schedule = dtcpp::finance::bondSchedule(startDate, tenorFreq,tenorMaturity, bdconv, hcal, true, true);
    assert(schedule.size() == 2);

    schedule = dtcpp::finance::bondSchedule(startDate, tenorFreq,tenorMaturity, bdconv, hcal, true, false);
    assert(schedule.size() == 1);

    schedule = dtcpp::finance::bondSchedule(startDate, tenorFreq,tenorMaturity, bdconv, hcal, false, false);
    assert(schedule.size() == 0);
}

int main() {
    
    testForwardDateTenor();
    testTenorOperators();
    testTenorGetFactorMultiple();
    testBondScheduler();
    testYearFraction(); 
    std::cout << "All tests for the finance module have been passed successfully!" << std::endl;

}