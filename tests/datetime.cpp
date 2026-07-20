#include <cassert>
#include <dtcpp/datetime.hpp>

void testTimestampConstructor() {
    using namespace dtcpp; 
    DateTime dt1 = DateTime(1766939320,EpochTimestampType::SECONDS); 
    DateTime dt2 = DateTime(1766939320,EpochTimestampType::SECONDS, TimeZone::UTCP1);
    
    assert(dt1.timestamp()==1766939320);
    assert(dt2.timestamp()==1766939320);
    assert(dt1.year()==2025);
    assert(dt2.year()==2025);
    assert(dt1.timestampType()==EpochTimestampType::SECONDS);
    assert(dt2.timestampType()==EpochTimestampType::SECONDS);
    assert(dt1.timeZone()==TimeZone::UTC);
    assert(dt2.timeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");
    assert(dt1.switchTimestampType(EpochTimestampType::MILLISECONDS).timestamp()==1766939320000);
    assert(dt1.switchTimestampType(EpochTimestampType::MILLISECONDS).timestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.timestamp()==1766939320000);
    assert(dt1.timestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");
}

void testCivilConstructor() {
    using namespace dtcpp; 
    DateTime dt1 = DateTime(2025,12,28,16,28,40); 
    DateTime dt2 = DateTime(2025,12,28,17,28,40, TimeZone::UTCP1); 

    assert(dt1.timestamp()==1766939320);
    assert(dt2.timestamp()==1766939320);
    assert(dt1.year()==2025);
    assert(dt2.year()==2025);
    assert(dt1.timestampType()==EpochTimestampType::SECONDS);
    assert(dt2.timestampType()==EpochTimestampType::SECONDS);
    assert(dt1.timeZone()==TimeZone::UTC);
    assert(dt2.timeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");
    assert(dt1.switchTimestampType(EpochTimestampType::MILLISECONDS).timestamp()==1766939320000);
    assert(dt1.switchTimestampType(EpochTimestampType::MILLISECONDS).timestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.timestamp()==1766939320000);
    assert(dt1.timestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");


}

void testStringConstructor() {
    using namespace dtcpp; 
    DateTime dt1 = DateTime("2025-12-28 16:28:40", "YYYY-MM-DD HH:MM:SS"); 
    DateTime dt2 = DateTime("2025-12-28 17:28:40", "YYYY-MM-DD HH:MM:SS", TimeZone::UTCP1); 

    assert(dt1.timestamp()==1766939320);
    assert(dt2.timestamp()==1766939320);
    assert(dt1.year()==2025);
    assert(dt2.year()==2025);
    assert(dt1.timestampType()==EpochTimestampType::SECONDS);
    assert(dt2.timestampType()==EpochTimestampType::SECONDS);
    assert(dt1.timeZone()==TimeZone::UTC);
    assert(dt2.timeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");

    assert(dt1.switchTimestampType(EpochTimestampType::MILLISECONDS).timestamp()==1766939320000);
    assert(dt1.switchTimestampType(EpochTimestampType::MILLISECONDS).timestampType()==EpochTimestampType::MILLISECONDS);
    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.timestamp()==1766939320000);
    assert(dt1.timestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");

}

void testOperators() {
    using namespace dtcpp; 
    DateTime dt1(1625097600, EpochTimestampType::SECONDS); 
    TimeDelta delta{0, 1, 0, 0, 0, 0, 0}; 

    dt1 += delta; 
    assert(dt1.timestamp() == 1625101200);
    dt1 -= delta; 
    assert(dt1.timestamp() == 1625097600);

    DateTime dt2 = dt1 + delta;
    assert(dt2.timestamp() == 1625101200); 

    DateTime dt3 = dt1 - delta;
    assert(dt3.timestamp() == 1625094000); 

    TimeDelta diff = dt2 - dt1;
    assert(diff.totalSeconds() == 3600);

    TimeDelta::Years diffYears1{1}; 
    TimeDelta::Years difffYears2{3}; 
    
    TimeDelta::Months diffMonth1{1}; 
    TimeDelta::Months diffMonth2{25}; 

    DateTime initialDate = DateTime(1767118789,EpochTimestampType::SECONDS);

    initialDate += diffYears1; 
    assert(initialDate.timestamp() == 1798654789);
    initialDate -= diffYears1; 
    assert(initialDate.timestamp() == 1767118789);
    initialDate += diffMonth1; 
    assert(initialDate.timestamp() == 1769797189);
    initialDate -= diffMonth1; 
    assert(initialDate.timestamp() == 1767118789);
    
    initialDate += difffYears2; 
    assert(initialDate.timestamp() == 1861813189);
    initialDate -= difffYears2; 
    assert(initialDate.timestamp() == 1767118789);
    
    initialDate += diffMonth2; 
    assert(initialDate.timestamp() == 1832869189);
    initialDate -= diffMonth2; 
    assert(initialDate.timestamp() == 1767118789);


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
