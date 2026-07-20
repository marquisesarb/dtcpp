#include <cassert>
#include <dtcpp/finance/daycount.hpp>

bool isClose(double value1, double value2, double eps) {return (std::abs(value2-value1)<eps);}

int main() {

    using namespace dtcpp::fin;
    using namespace dtcpp;     

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
    
    return 0;
}