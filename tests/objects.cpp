#include <iostream>
#include <cassert>
#include <dtcpp/objects.hpp>

using namespace dtcpp::objects; 

void testTimeDelta() {
    dtcpp::objects::TimeDelta delta = {1, 2, 3, 4, 500, 600, 700}; 

    long long totalSeconds = delta.getTotalSeconds();
    assert(totalSeconds == 93784); 

    long long totalMilliSeconds = delta.getTotalMilliSeconds();
    assert(totalMilliSeconds == 93784500); 

    long long totalMicroSeconds = delta.getTotalMicroSeconds();
    assert(totalMicroSeconds == 93784500600); 

    long long totalNanoSeconds = delta.getTotalNanoSeconds();
    assert(totalNanoSeconds == 93784500600700);

    delta = {0, 0, 0, 10, 0, 0, 0}; 

    assert(delta.getTotalSeconds() == 10);
    assert(delta.getTotalMilliSeconds() == 10000);
    assert(delta.getTotalMicroSeconds() == 10000000);
    assert(delta.getTotalNanoSeconds() == 10000000000);

}

void testTimestampConstructor() {
    using namespace dtcpp::objects; 
    DateTime dt1 = DateTime(1766939320,EpochTimestampType::SECONDS); 
    DateTime dt2 = DateTime(1766939320,EpochTimestampType::SECONDS, TimeZone::UTCP1);
    
    assert(dt1.getTimestamp()==1766939320);
    assert(dt2.getTimestamp()==1766939320);
    assert(dt1.getYear()==2025);
    assert(dt2.getYear()==2025);
    assert(dt1.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt2.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt1.getTimeZone()==TimeZone::UTC);
    assert(dt2.getTimeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestamp()==1766939320000);
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.getTimestamp()==1766939320000);
    assert(dt1.getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");
}

void testCivilConstructor() {
    using namespace dtcpp::objects; 
    DateTime dt1 = DateTime(2025,12,28,16,28,40); 
    DateTime dt2 = DateTime(2025,12,28,17,28,40, TimeZone::UTCP1); 

    assert(dt1.getTimestamp()==1766939320);
    assert(dt2.getTimestamp()==1766939320);
    assert(dt1.getYear()==2025);
    assert(dt2.getYear()==2025);
    assert(dt1.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt2.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt1.getTimeZone()==TimeZone::UTC);
    assert(dt2.getTimeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestamp()==1766939320000);
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.getTimestamp()==1766939320000);
    assert(dt1.getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");


}

void testStringConstructor() {
    using namespace dtcpp::objects; 
    DateTime dt1 = DateTime("2025-12-28 16:28:40", "YYYY-MM-DD HH:MM:SS"); 
    DateTime dt2 = DateTime("2025-12-28 17:28:40", "YYYY-MM-DD HH:MM:SS", TimeZone::UTCP1); 

    assert(dt1.getTimestamp()==1766939320);
    assert(dt2.getTimestamp()==1766939320);
    assert(dt1.getYear()==2025);
    assert(dt2.getYear()==2025);
    assert(dt1.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt2.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt1.getTimeZone()==TimeZone::UTC);
    assert(dt2.getTimeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");

    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestamp()==1766939320000);
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestampType()==EpochTimestampType::MILLISECONDS);
    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.getTimestamp()==1766939320000);
    assert(dt1.getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");

}

void testOperators() {
    using namespace dtcpp::objects; 
    DateTime dt1(1625097600, EpochTimestampType::SECONDS); 
    TimeDelta delta{0, 1, 0, 0, 0, 0, 0}; 

    dt1 += delta; 
    assert(dt1.getTimestamp() == 1625101200);
    dt1 -= delta; 
    assert(dt1.getTimestamp() == 1625097600);

    DateTime dt2 = dt1 + delta;
    assert(dt2.getTimestamp() == 1625101200); 

    DateTime dt3 = dt1 - delta;
    assert(dt3.getTimestamp() == 1625094000); 

    TimeDelta diff = dt2 - dt1;
    assert(diff.getTotalSeconds() == 3600);

    TimeDelta::Years diffYears1{1}; 
    TimeDelta::Years difffYears2{3}; 
    
    TimeDelta::Months diffMonth1{1}; 
    TimeDelta::Months diffMonth2{25}; 

    DateTime initialDate = DateTime(1767118789,EpochTimestampType::SECONDS);

    initialDate += diffYears1; 
    assert(initialDate.getTimestamp() == 1798654789);
    initialDate -= diffYears1; 
    assert(initialDate.getTimestamp() == 1767118789);
    initialDate += diffMonth1; 
    assert(initialDate.getTimestamp() == 1769797189);
    initialDate -= diffMonth1; 
    assert(initialDate.getTimestamp() == 1767118789);
    
    initialDate += difffYears2; 
    assert(initialDate.getTimestamp() == 1861813189);
    initialDate -= difffYears2; 
    assert(initialDate.getTimestamp() == 1767118789);
    
    initialDate += diffMonth2; 
    assert(initialDate.getTimestamp() == 1832869189);
    initialDate -= diffMonth2; 
    assert(initialDate.getTimestamp() == 1767118789);


    assert(dt1 == dt1);
    assert(dt1 != dt2);
    assert(dt1 < dt2);
    assert(dt2 > dt1);
    assert(dt1 <= dt2);
    assert(dt2 >= dt1);
}

DatetimeSequence getDateTimeSeq() {

    
    std::set<int> timestampsVector = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824854400,
        1840665600, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982707200,
        1998432000, 2014243200, 2029968000, 2045779200, 2061504000,
        2077315200
    };

    DatetimeSequence sequence = DatetimeSequence();
    for (int t: timestampsVector){sequence.add(DateTime(t,EpochTimestampType::SECONDS));}
    return sequence;
}

void testBasicsDateTimeSeq() {

    DatetimeSequence seq = getDateTimeSeq(); 

    assert(seq.isExisting(DateTime(1761868800,EpochTimestampType::SECONDS)));
    assert(seq.isExisting(DateTime(1966896000,EpochTimestampType::SECONDS)));
    assert(!seq.isExisting(DateTime(1976896000,EpochTimestampType::SECONDS)));

    assert(seq.size()==21); 

    assert(seq.index(DateTime(1761868800,EpochTimestampType::SECONDS)) == 0);
    assert(seq.index(DateTime(1966896000,EpochTimestampType::SECONDS)) == 13);
    assert(seq.index(DateTime(1976896000,EpochTimestampType::SECONDS)) == -1);

    assert(seq.start().value() == DateTime(1761868800,EpochTimestampType::SECONDS));
    assert(seq.end().value() == DateTime(2077315200,EpochTimestampType::SECONDS));

    assert(!DatetimeSequence().start().has_value());
    assert(!DatetimeSequence().end().has_value());

}

void testAddRemoveDateTimeSeq() {

    DatetimeSequence sequence = getDateTimeSeq(); 

    DateTime newDt = DateTime(1761868800, EpochTimestampType::SECONDS)-TimeDelta{1,0,0,0,0,0,0};
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(*sequence.start()==newDt); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(*sequence.start()==DateTime(1761868800,EpochTimestampType::SECONDS)); 

    newDt = DateTime(2077315200, EpochTimestampType::SECONDS)+TimeDelta{1,0,0,0,0,0,0};
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(*sequence.end()==newDt); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(*sequence.end()==DateTime(2077315200,EpochTimestampType::SECONDS)); 

    newDt = DateTime(1761868800, EpochTimestampType::SECONDS)+TimeDelta{1,0,0,0,0,0,0};
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(sequence.index(newDt)==1); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(sequence.index(DateTime(1777507200,EpochTimestampType::SECONDS))==1); 

    newDt = DateTime(2077315200, EpochTimestampType::SECONDS)-TimeDelta{1,0,0,0,0,0,0};
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(sequence.index(newDt)==20); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(sequence.index(DateTime(2061504000,EpochTimestampType::SECONDS))==19); 
}

void testNextPreviousDateTimeSeq() {

    DatetimeSequence sequence = getDateTimeSeq(); 

    // 1) first datetime of the sequence 
    DateTime referenceDt = DateTime(1761868800, EpochTimestampType::SECONDS);
    assert(sequence.next(referenceDt).value() == DateTime(1777507200, EpochTimestampType::SECONDS));
    assert(!sequence.previous(referenceDt).has_value());

    // 2) after last datetime of the sequence 
    referenceDt = DateTime(2077315200, EpochTimestampType::SECONDS) + TimeDelta{1,0,0,0,0,0,0};
    assert(!sequence.next(referenceDt).has_value());
    assert(sequence.previous(referenceDt).value() == DateTime(2077315200, EpochTimestampType::SECONDS));

    // 3) before first datetime of the sequence 
    referenceDt = DateTime(1761868800, EpochTimestampType::SECONDS) - TimeDelta{1,0,0,0,0,0,0};
    assert(sequence.next(referenceDt).value() == DateTime(1761868800, EpochTimestampType::SECONDS));
    assert(!sequence.previous(referenceDt).has_value());

    // 4) Non-existing datetime in-bewteen
    int intermTimestamp = 1958084800;
    referenceDt = DateTime(intermTimestamp, EpochTimestampType::SECONDS);
    assert(sequence.next(referenceDt).value() == DateTime(1966896000, EpochTimestampType::SECONDS));
    assert(sequence.previous(referenceDt).value() == DateTime(1951084800, EpochTimestampType::SECONDS));

    // 5) Exact datetime in-bewteen
    referenceDt = DateTime(1951084800, EpochTimestampType::SECONDS);
    assert(sequence.next(referenceDt).value() == DateTime(1966896000, EpochTimestampType::SECONDS));
    assert(sequence.previous(referenceDt).value() == DateTime(1935273600, EpochTimestampType::SECONDS));

    // 6) last datetime of the sequence 
    referenceDt = DateTime(2077315200, EpochTimestampType::SECONDS);
    assert(!sequence.next(referenceDt).has_value());
    assert(sequence.previous(referenceDt).value() == DateTime(2061504000, EpochTimestampType::SECONDS));
}

void testSubDateTimeSeq() {

    DatetimeSequence sequence = getDateTimeSeq(); 

    DatetimeSequence subSeq1 = sequence.sub(1,3); 
    std::set<DateTime> subSeqTest1 = {
        DateTime(1777507200, EpochTimestampType::SECONDS), 
        DateTime(1793318400, EpochTimestampType::SECONDS), 
        DateTime(1809043200, EpochTimestampType::SECONDS)
    };
    assert(subSeq1.datetimeSequence == subSeqTest1);

    DatetimeSequence subSeq2 = sequence.sub(DateTime(1919548800, EpochTimestampType::SECONDS),DateTime(1982707200, EpochTimestampType::SECONDS)); 
    std::set<DateTime> subSeqTest2 = {
        DateTime(1919548800, EpochTimestampType::SECONDS), 
        DateTime(1935273600, EpochTimestampType::SECONDS), 
        DateTime(1951084800, EpochTimestampType::SECONDS), 
        DateTime(1966896000, EpochTimestampType::SECONDS), 
        DateTime(1982707200, EpochTimestampType::SECONDS)
    };
    assert(subSeq2.datetimeSequence == subSeqTest2);

    DatetimeSequence subSeq3 = sequence.sub(2,1); 
    assert(subSeq3.size() == 0);

    DatetimeSequence subSeq4 = sequence.sub(DateTime(1982707200, EpochTimestampType::SECONDS),DateTime(1919548800, EpochTimestampType::SECONDS)); 
    assert(subSeq4.size() == 0);
}


int main() {

    testTimeDelta(); 
    testTimestampConstructor(); 
    testCivilConstructor();
    testStringConstructor();
    testOperators();
    testBasicsDateTimeSeq(); 
    testAddRemoveDateTimeSeq(); 
    testNextPreviousDateTimeSeq(); 
    testSubDateTimeSeq();
    std::cout << "All tests for the objects module have been passed!" << std::endl; 
    return 0;
}