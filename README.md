# DTCPP

DTCPP is a date/time C++17 library buit with inspirations to the python library datetime. The goal of this library is to make accessible time representation and its arithmetics, as well as defining specific objects to represent time sequence, time series and different finance appication of time (Tenor, Day Count Convention, Business Days).

## Time Delta 

The TimeDelta object (implemented [here](include/dtcpp/timedelta.hpp)) represents a time period. It can be constructed from a number: 
- days 
- hours 
- minutes 
- seconds 
- milliseconds 
- microseconds 
- nanoseconds 

```cpp 

int main() {
    // Representing of a time delta of 1 day, 2 hours, 3 minutes, 4 seconds, 500 milliseconds, 600 microseconds and 700 nanoseconds
    dtcpp::TimeDelta delta = {1, 2, 3, 4, 500, 600, 700}; 

    std::cout << delta.totalSeconds() << std::endl;
    // 93784

    std::cout << delta.totalMilliseconds() << std::endl;
    // 93784500; 

    std::cout << delta.totalMicroseconds() << std::endl;
    // 93784500600

    std::cout << delta.totalNanoseconds() << std::endl;;
    // 93784500600700
}


```

## Date Time 

The object DateTime (implemented [here](include/dtcpp/datetime.hpp)) defines time at a single point using epoch timestamp. It can be constructed from: 
- A Timestamp (in seconds, miiseconds, microseconds or nanoseconds)
- A civil date up to the seconds precision 
- A string in a specific format 
The object has also overloaded operators that allows for smooth arithmetics between DateTime objects as well as TimeDelta objects. 

```cpp 

int main() {

    DateTime dt1 = DateTime(1766939320,EpochTimestampType::SECONDS); 
    DateTime dt2 = DateTime(2025,12,28,17,28,40, TimeZone::UTCP1); 
    DateTime dt3 = DateTime("2025-12-28 16:28:40", "YYYY-MM-DD HH:MM:SS"); 

    std::cout << dt1.asString("YYYY-MM-DD HH:MM:SS") << std::endl;
    // 2025-12-28 16:28:40 UTC+0 

    std::cout << dt2.asString("YYYY-MM-DD HH:MM:SS") << std::endl;
    // 2025-12-28 17:28:40 UTC+1

    std::cout << dt3.asString("YYYY-MM-DD HH:MM:SS") << std::endl;
    // 2025-12-28 16:28:40 UTC+0 

    dt1.setTimeZone(TimeZone::UTCM6);
    std::cout << dt2.asString("YYYY-MM-DD HH:MM:SS") << std::endl;
    // 2025-12-28 10:28:40 UTC-6

    DateTime dt4 = DateTime(1625097600,EpochTimestampType::SECONDS); 
    TimeDelta delta{0, 1, 0, 0, 0, 0, 0}; 

    dt4 += delta; 
    std::cout << dt4.timestamp() << std::endl;
    // 1625101200

    dt4 -= delta; 
    std::cout << dt4.timestamp() << std::endl;
    // 1625097600


}


```


## Time Sequence 

Implementation of a time sequence representing an array of unique DateTime objects which are kept ordered. The choice of keeping the sequence as an array has been made because it allows for the following operations: 

- Indexing in $O(1)$ 
- Push back a date which is known to be greater that any existing date within the sequence is $O(1)$ using std::vector::push_back
- Inserting a date is reduced to $O(\log n)$ with binary search using std::lower_bound
- pop back is $O(1)$ using std::vector::pop_back 
- segment the sequence is $O(n)$ thanks to $O(1)$ indexing 

```cpp 

int main() {

    std::vector<int> timestampsVector = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824854400, 1840665600, 
    };

    dtcpp::TimeSequence sequence = dtcpp::TimeSequence();
    for (int t: timestampsVector){sequence.insert(dtcpp::DateTime(t,dtcpp::EpochTimestampType::SECONDS));}

    std::cout << sequence.size() << std::endl;
    // 6

    std::cout << sequence.contains(dtcpp::DateTime(1793318400,dtcpp::EpochTimestampType::SECONDS)) << std::endl;
    // 1 

    std::cout << sequence.contains(dtcpp::DateTime(1793318400-1000,dtcpp::EpochTimestampType::SECONDS)) << std::endl;
    // 0

    std::cout << sequence.front().timestamp() << std::endl;
    // 1761868800

    std::cout << sequence.prev(dtcpp::DateTime(1793318400-1000,dtcpp::EpochTimestampType::SECONDS)).timestamp() << std::endl;
    // 1777507200

    std::cout << sequence.next(dtcpp::DateTime(1793318400,dtcpp::EpochTimestampType::SECONDS)).timestamp() << std::endl;
    // 1809043200

    std::cout << sequence[1].timeestamp() << std::endl;
    // 1777507200

}

```


## Time Serie 

The Time Serie obejct is a template class allowing to represent a sequence of object indexed by a DateTime object using std::pair. Very close to the implementation of TimeSequence, the TimeSerie object is implemented in two arrays to leverage $O(1)$ indexing and $O(1)$ push back inserting. Thus, such implementation allows for $O(n)$ segmenting.

`````cpp 

int main() {

    std::vector<long long> timestamps = {
        1783238400000,1783260000000,1783281600000,1783303200000,1783324800000,1783346400000,1783368000000,1783389600000
    }; 

    std::vector<double> values = {
        62754.5,62743.5,63537.0,63053.0,61748.0,63707.0,63808.5,63049.5
    };

    dtcpp::TimeSerie<double> ts = dtcpp::TimeSerie<double>();

    for (size_t i = 0; i<values.size();i++) {

        ts.insert(dtcpp::DateTime(timestamps[i],dtcpp::EpochTimestampType::MILLISECONDS), values[i]);
    }

    std::cout << ts[15].first.timestamp() << std::endl;
    // 1783562400000
     std::cout << ts[15].second << std::endl;
    // 62979.5

    dtcpp::TimeSerie<double> seg = ts.segment(2, 3); 

    std::cout << seg.size() << std::endl;
    // 3

    std::cout << seg[0].first.timestamp() << std::endl;
    // 1783281600000
     std::cout << seg[0].second << std::endl;
    // 63537.0

}

`````

## Calendars 

Implemetation of a BusinessCalendar interface which allows for checking wether a specifc date is a business day or not. Also, it has a generic method adjusting a given date for business based on one of the following business day convention: 
- Following : return next business day 
- Preceding : return last business day 
- Modified following : following method, but if following is a changing month use preceding 
- Modified preceding : preceding method, but if preceding is a changing month use following 

A new calendar must inherits from the BusinessCalendar abstract class with implemented method isBusinessDay. Implemented calendars are: 

- No holiday calendar : dummy calendar with no holidays 
- week end off calendar : calendar where week end (saturday and sunday) are off days 
- US Federal reserve calendar (define [here](https://www.frbservices.org/about/holiday-schedules))

```cpp 
int main() {

    dtcpp::USFederaReserveCalendar calendar = dtcpp::USFederaReserveCalendar();
    dtcpp::DateTime refDate(2024,1,15); 


    std::cout << calendar.isBusinessDay(refDate) << std::endl;
    // 0 
    std::cout << calendar.adjustForBusiness(refDate,dtcpp::BusinessDayConvention::FOLLOWING).timestamp() << std::endl;
    // 1705363200
    std::cout << calendar.adjustForBusiness(refDate ,dtcpp::BusinessDayConvention::PRECEDING).timestamp() << std::endl;
    // 1705017600
    std::cout << calendar.adjustForBusiness(refDate, dtcpp::BusinessDayConvention::MODIFIED_FOLLOWING).timestamp() << std::endl;
    // 1705363200
    std::cout << calendar.adjustForBusiness(refDate, dtcpp::BusinessDayConvention::MODIFIED_PRECEDING).timestamp() << std::endl;
    // 1705017600
}


```

## Financial applications 

### Tenor object 

A Tenor object represents a period "forward" in time which can be expressed in days, weeks, months or years. The Tenor object have overloaded operators for comparaison whih is based on the respective forward date calculated. 

```cpp 

int main() {

    dtcpp::DateTime refDate(1769472000, dtcpp::EpochTimestampType::SECONDS);
    std::cout << dtcpp::fin::Tenor{3,dtcpp::fin::TenorType::MONTHS}.getForwardDate(refDate,1) << std::endl; 
    // 1777248000

    std::cout << (dtcpp::fin::Tenor{7, dtcpp::fin::TenorType::DAYS}==dtcpp::fin::Tenor{1, dtcpp::fin::TenorType::WEEKS}) << std::endl;
    // 1
    std::cout << (dtcpp::fin::Tenor{14, dtcpp::fin::TenorType::DAYS}==dtcpp::fin::Tenor{2, dtcpp::fin::TenorType::WEEKS}) << std::endl;
    // 1 
    std::cout << (dtcpp::fin::Tenor{8, dtcpp::fin::TenorType::DAYS}>dtcpp::fin::Tenor{1, dtcpp::fin::TenorType::WEEKS}) << std::endl;
    // 1
    std::cout << (dtcpp::fin::Tenor{15, dtcpp::fin::TenorType::DAYS}>dtcpp::fin::Tenor{2, dtcpp::fin::TenorType::WEEKS}) << std::endl;
    // 1 
}

```

### Day count conventions

Day count convention are widely used in financial markets to expressed how the year fraction is calcullated between two dates. We refer to the wiki page for more informations: https://en.wikipedia.org/wiki/Day_count_convention . The followings conventions are implemented: 
- ACT/360 
- ACT/365 
- ACT/364 
- ACT/ACT 
- 30E/360 
- 30E/360 Bond Basis 

```cpp

int main() {

    // 25 Août 2025 21:00:00 
    dtcpp::DateTime referenceTime = dtcpp::DateTime(1756155600,dtcpp::EpochTimestampType::SECONDS); 
    // 14 Novembre 2026 21:00:00 
    dtcpp::DateTime forwardTime = dtcpp::DateTime(1794690000,dtcpp::EpochTimestampType::SECONDS); 

    std::cout << dtcpp::fin::yearFraction(referenceTime,forwardTime,DayCountConvention::ACTUAL_360) << std::endl;
    // 1.238888889
    std::cout << dtcpp::fin::yearFraction(referenceTime,forwardTime, DayCountConvention::ACTUAL_365) << std::endl;
    // 1.221917808
    std::cout << dtcpp::fin::yearFraction(referenceTime,forwardTime, DayCountConvention::ACTUAL_364) << std::endl;
    // 1.225274725
    std::cout << dtcpp::fin::yearFraction(referenceTime,forwardTime, DayCountConvention::BOND_BASIS30_360) << std::endl;
    // 1.219444444
    std::cout << dtcpp::fin::yearFraction(referenceTime,forwardTime, DayCountConvention::E30_360) << std::endl;
    // 1.219444444
    std::cout << dtcpp::fin::yearFraction(referenceTime,forwardTime, DayCountConvention::ACTUAL_ACTUAL) << std::endl;
    // 1.221917808

}
```

### Bond scheduler 

The bond scheduler inherits from the time sequence object. It represents the coupon date scheduling based on both the frequency and maturity tenors of a bond (or any other instrument with frequent cash flows such as swaps or structured products). The coupon dates are then adjusted from both the business day convention and the holiday calendar. 

```cpp

int main() {

    dtcpp::fin::Tenor tenorFreq{3,dtcpp::fin::TenorType::MONTHS};
    dtcpp::fin::Tenor tenorMaturity{5,dtcpp::fin::TenorType::YEARS};
    dtcpp::DateTime startDate(2026,1,30);
    std::shared_ptr<dtcpp::NoHolidayCalendar> hcal = std::make_shared<dtcpp::NoHolidayCalendar>(); 
    dtcpp::BusinessDayConvention bdconv = dtcpp::BusinessDayConvention::FOLLOWING; 

    dtcpp::fin::BondScheduler schedule(startDate,tenorFreq,tenorMaturity, bdconv, hcal);
    std::cout << schedule.size() << std::endl;
    // 19
    std::cout << schedule[7].timestamp() << std::endl;
    // 1832803200
    std::cout << schedule[12].timestamp() << std::endl;
    // 1872201600
    std::cout << schedule[13].timestamp() << std::endl;
    // 1880064000
    std::cout << schedule.startDate.timestamp() << std::endl;
    // 1769731200
    std::cout << schedule.maturityDate().timestamp() << std::endl;
    // 1927497600
}

```

