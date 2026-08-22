#include <dtcpp/datetime.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    DateTime DateTime::operator+(const TimeDelta& other) const {

        return DateTime(timestamp+other.totalNanoseconds);
    }

    DateTime DateTime::operator-(const TimeDelta& other) const {

        return DateTime(timestamp-other.totalNanoseconds);
    }

    TimeDelta DateTime::operator-(const DateTime& other) const {

        return {timestamp-other.timestamp};
    }

    void DateTime::operator+=(const TimeDelta& other){ 
        timestamp += other.totalNanoseconds;
    }

    void DateTime::operator-=(const TimeDelta& other){ 
        timestamp -= other.totalNanoseconds;
    }

    bool DateTime::operator==(const DateTime& other) const {
        return (timestamp==other.timestamp);
    }

    bool DateTime::operator<(const DateTime& other) const {
        return (timestamp<other.timestamp);
    }

    bool DateTime::operator<=(const DateTime& other) const {
        return (timestamp<=other.timestamp);
    }

    bool DateTime::operator!=(const DateTime& other) const {
        return (timestamp!=other.timestamp);
    }

    bool DateTime::operator>(const DateTime& other) const {
        return (timestamp>other.timestamp);
    }

    bool DateTime::operator>=(const DateTime& other) const {
        return (timestamp>=other.timestamp);
    }

    DateTime DateTime::operator+(const TimeDelta::Years& other) const {
    
        std::tuple<int,int,int,int,int,int> civilTime_ = civilTime();
        auto [y,m,d] = toolbox::addYearsToCivilDate(
            std::get<0>(civilTime_)
            ,std::get<1>(civilTime_)
            ,std::get<2>(civilTime_)
            ,other.years);
        TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), TimeZone::UTC);
        return DateTime(y,m,d,TimeZone::UTC) + dt;
    }

    DateTime DateTime::operator-(const TimeDelta::Years& other) const {

        TimeDelta::Years other2{-other.years};
        return operator+(other2);
    }

    DateTime DateTime::operator+(const TimeDelta::Months& other) const {
    
        std::tuple<int,int,int,int,int,int> civilTime_ = civilTime();
        auto [y,m,d] = toolbox::addMonthsToCivilDate(
            std::get<0>(civilTime_)
            ,std::get<1>(civilTime_)
            ,std::get<2>(civilTime_)
            ,other.months);
        TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), TimeZone::UTC);
        return DateTime(y,m,d,TimeZone::UTC) + dt;
    }

    DateTime DateTime::operator-(const TimeDelta::Months& other) const {

        TimeDelta::Months other2{-other.months};
        return operator+(other2);
    }

    void DateTime::operator+=(const TimeDelta::Years& other){
        timestamp = operator+(other).timestamp;         
    }

    void DateTime::operator-=(const TimeDelta::Years& other) {
        timestamp = operator-(other).timestamp;   
    }

    void DateTime::operator+=(const TimeDelta::Months& other){
        timestamp = operator+(other).timestamp;         
    }

    void DateTime::operator-=(const TimeDelta::Months& other) {
        timestamp = operator-(other).timestamp;   
    }




}