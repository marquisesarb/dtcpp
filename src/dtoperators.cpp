#include <dtcpp/datetime.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    DateTime DateTime::operator+(const TimeDelta& other) const {

        long long tmsp = timestamp();
        switch(type_){
            case EpochTimestampType::SECONDS: {tmsp += other.totalSeconds(); break;}
            case EpochTimestampType::MILLISECONDS: {tmsp += other.totalMilliseconds(); break;}
            case EpochTimestampType::MICROSECONDS: {tmsp += other.totalMicroseconds(); break;}
            case EpochTimestampType::NANOSECONDS: {tmsp += other.totalNanoseconds(); break;}
        }
        return DateTime(tmsp, type_, timeZone_);
    }

    DateTime DateTime::operator-(const TimeDelta& other) const {

        long long tmsp = timestamp();
        switch(type_){
            case EpochTimestampType::SECONDS: {tmsp -= other.totalSeconds(); break;}
            case EpochTimestampType::MILLISECONDS: {tmsp -= other.totalMilliseconds(); break;}
            case EpochTimestampType::MICROSECONDS: {tmsp -= other.totalMicroseconds(); break;}
            case EpochTimestampType::NANOSECONDS: {tmsp -= other.totalNanoseconds(); break;}
        }
        return DateTime(tmsp, type_, timeZone_);
    }

    TimeDelta DateTime::operator-(const DateTime& other) const {

        long long nanoseconds = switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp() - other.switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp();
        return {0,0,0,0,0,0,nanoseconds};

    }

    void DateTime::operator+=(const TimeDelta& other){ 
        tmsp_ = operator+(other).timestamp(); 
        civilTime_ = toolbox::getCivilFromTimestamp(
            _getModifiedTimestamp(
                tmsp_
                , -static_cast<int>(timeZone_)
                , type_));
    }

    void DateTime::operator-=(const TimeDelta& other){ 
        tmsp_ = operator-(other).timestamp(); 
        civilTime_ = toolbox::getCivilFromTimestamp(
            _getModifiedTimestamp(
                tmsp_
                , -static_cast<int>(timeZone_)
                , type_));
    }

    bool DateTime::operator==(const DateTime& other) const {
        if (switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp()==other.switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp()) return true;
        return false;
    }

    bool DateTime::operator<(const DateTime& other) const {
        if (switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp()<other.switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp()) return true;
        return false;
    }

    bool DateTime::operator<=(const DateTime& other) const {
        if (switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp()<=other.switchTimestampType(EpochTimestampType::NANOSECONDS).timestamp()) return true;
        return false;
    }

    bool DateTime::operator!=(const DateTime& other) const { return operator==(other) ? false : true; } 

    bool DateTime::operator>=(const DateTime& other) const { return operator<(other) ? false : true; }

    bool DateTime::operator>(const DateTime& other) const { return operator<=(other) ? false : true; }

    DateTime DateTime::operator+(const TimeDelta::Years& other) const {
    
        auto [y,m,d] = toolbox::addYearsToCivilDate(
            std::get<0>(civilTime_)
            ,std::get<1>(civilTime_)
            ,std::get<2>(civilTime_)
            ,other.years);
        TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
        return DateTime(y,m,d,timeZone_).switchTimestampType(type_) + dt;
    }

    DateTime DateTime::operator-(const TimeDelta::Years& other) const {

        auto [y,m,d] = toolbox::addYearsToCivilDate(
            std::get<0>(civilTime_)
            ,std::get<1>(civilTime_)
            ,std::get<2>(civilTime_)
            ,-other.years);
        
        TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
        return DateTime(y,m,d,timeZone_).switchTimestampType(type_) + dt;
    }

    DateTime DateTime::operator+(const TimeDelta::Months& other) const {
    
        auto [y,m,d] = toolbox::addMonthsToCivilDate(
            std::get<0>(civilTime_)
            ,std::get<1>(civilTime_)
            ,std::get<2>(civilTime_)
            ,other.months);
        TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
        return DateTime(y,m,d,timeZone_).switchTimestampType(type_) + dt;
    }

    DateTime DateTime::operator-(const TimeDelta::Months& other) const {

        auto [y,m,d] = toolbox::addMonthsToCivilDate(
            std::get<0>(civilTime_)
            ,std::get<1>(civilTime_)
            ,std::get<2>(civilTime_)
            ,-other.months);

        TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
        return DateTime(y,m,d,timeZone_).switchTimestampType(type_) + dt;
    }

    void DateTime::operator+=(const TimeDelta::Years& other){
        tmsp_ = operator+(other).timestamp(); 
        civilTime_ = toolbox::getCivilFromTimestamp(
            _getModifiedTimestamp(
                tmsp_
                , -static_cast<int>(timeZone_)
                , type_));
        
    }

    void DateTime::operator-=(const TimeDelta::Years& other) {
        
        tmsp_ = operator-(other).timestamp(); 
        civilTime_ = toolbox::getCivilFromTimestamp(
            _getModifiedTimestamp(
                tmsp_
                , -static_cast<int>(timeZone_)
                , type_));
    }

    void DateTime::operator+=(const TimeDelta::Months& other) {
        
        tmsp_ = operator+(other).timestamp(); 
        civilTime_ = toolbox::getCivilFromTimestamp(
            _getModifiedTimestamp(
                tmsp_
                , -static_cast<int>(timeZone_)
                , type_));
    }

    void DateTime::operator-=(const TimeDelta::Months& other) {
        
        tmsp_ = operator-(other).timestamp(); 
        civilTime_ = toolbox::getCivilFromTimestamp(
            _getModifiedTimestamp(
                tmsp_
                , -static_cast<int>(timeZone_)
                , type_));
    }



}