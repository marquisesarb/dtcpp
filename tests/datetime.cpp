#include <cassert>
#include <dtcpp/datetime.hpp>

void testTimestampConstructor() {
    using namespace dtcpp; 
    DateTime dt1 = DateTime(1766939320,EpochTimestampType::SECONDS); 
    
    assert(dt1.timestamp==1766939320*1'000'000'000LL);
    assert(std::get<0>(dt1.civilTime())==2025);
    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt1.asString("YYYY-MM-DD HH:MM:SS", TimeZone::UTCP1)=="2025-12-28 17:28:40 UTC+1");
    assert(dt1.asString("YYYY-MM-DD HH:MM:SS", TimeZone::UTCM6)=="2025-12-28 10:28:40 UTC-6");
}

void testCivilConstructor() {
    using namespace dtcpp; 
    DateTime dt1 = DateTime(2025,12,28,16,28,40, TimeZone::UTC); 

    assert(dt1.timestamp==1766939320*1'000'000'000LL);
    assert(std::get<0>(dt1.civilTime())==2025);


    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt1.asString("YYYY-MM-DD HH:MM:SS", TimeZone::UTCP1)=="2025-12-28 17:28:40 UTC+1");

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS", TimeZone::UTCM6)=="2025-12-28 10:28:40 UTC-6");


}

void testStringConstructor() {
    using namespace dtcpp; 
    DateTime dt1 = DateTime("2025-12-28 16:28:40", "YYYY-MM-DD HH:MM:SS", TimeZone::UTC); 

    assert(dt1.timestamp==1766939320*1'000'000'000LL);
    assert(std::get<0>(dt1.civilTime())==2025);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt1.asString("YYYY-MM-DD HH:MM:SS", TimeZone::UTCP1)=="2025-12-28 17:28:40 UTC+1");

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS", TimeZone::UTCM6)=="2025-12-28 10:28:40 UTC-6");

}

void testOperators() {
    using namespace dtcpp; 
    DateTime dt1(1625097600, EpochTimestampType::SECONDS); 
    TimeDelta delta{0, 1, 0, 0, 0, 0, 0}; 

    dt1 += delta; 
    assert(dt1.timestamp == 1625101200*1'000'000'000LL);
    dt1 -= delta; 
    assert(dt1.timestamp == 1625097600*1'000'000'000LL);

    DateTime dt2 = dt1 + delta;
    assert(dt2.timestamp == 1625101200*1'000'000'000LL); 

    DateTime dt3 = dt1 - delta;
    assert(dt3.timestamp == 1625094000*1'000'000'000LL); 

    TimeDelta diff = dt2 - dt1;
    assert(diff.totalNanoseconds == 3600*1'000'000'000LL);

    TimeDelta::Years diffYears1{1}; 
    TimeDelta::Years difffYears2{3}; 
    
    TimeDelta::Months diffMonth1{1}; 
    TimeDelta::Months diffMonth2{25}; 

    DateTime initialDate = DateTime(1767118789,EpochTimestampType::SECONDS);

    initialDate += diffYears1; 
    assert(initialDate.timestamp == 1798654789*1'000'000'000LL);
    initialDate -= diffYears1; 
    assert(initialDate.timestamp == 1767118789*1'000'000'000LL);
    initialDate += diffMonth1; 
    assert(initialDate.timestamp == 1769797189*1'000'000'000LL);
    initialDate -= diffMonth1; 
    assert(initialDate.timestamp == 1767118789*1'000'000'000LL);
    
    initialDate += difffYears2; 
    assert(initialDate.timestamp == 1861813189*1'000'000'000LL);
    initialDate -= difffYears2; 
    assert(initialDate.timestamp == 1767118789*1'000'000'000LL);
    
    initialDate += diffMonth2; 
    assert(initialDate.timestamp == 1832869189*1'000'000'000LL);
    initialDate -= diffMonth2; 
    assert(initialDate.timestamp == 1767118789*1'000'000'000LL);


    assert(dt1 == dt1);
    assert(dt1 != dt2);
    assert(dt1 < dt2);
    assert(dt2 > dt1);
    assert(dt1 <= dt2);
    assert(dt2 >= dt1);
}

int main() {

    testTimestampConstructor(); 
    testCivilConstructor();
    testStringConstructor();
    testOperators();
    return 0;
}
