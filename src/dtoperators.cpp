#include <dtcpp/objects.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    namespace objects {

        DateTime DateTime::operator+(const TimeDelta& other) const {

            long long tmsp = getTimestamp();
            switch(type_){
                case EpochTimestampType::SECONDS: {tmsp += other.getTotalSeconds(); break;}
                case EpochTimestampType::MILLISECONDS: {tmsp += other.getTotalMilliSeconds(); break;}
                case EpochTimestampType::MICROSECONDS: {tmsp += other.getTotalMicroSeconds(); break;}
                case EpochTimestampType::NANOSECONDS: {tmsp += other.getTotalNanoSeconds(); break;}
            }
            return DateTime(tmsp, type_, timeZone_);
        }

        DateTime DateTime::operator-(const TimeDelta& other) const {

            long long tmsp = getTimestamp();
            switch(type_){
                case EpochTimestampType::SECONDS: {tmsp -= other.getTotalSeconds(); break;}
                case EpochTimestampType::MILLISECONDS: {tmsp -= other.getTotalMilliSeconds(); break;}
                case EpochTimestampType::MICROSECONDS: {tmsp -= other.getTotalMicroSeconds(); break;}
                case EpochTimestampType::NANOSECONDS: {tmsp -= other.getTotalNanoSeconds(); break;}
            }
            return DateTime(tmsp, type_, timeZone_);
        }

        TimeDelta DateTime::operator-(const DateTime& other) const {

            long long nanoseconds = getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp() - other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp();
            return {0,0,0,0,0,0,nanoseconds};

        }

        void DateTime::operator+=(const TimeDelta& other){ 
            tmsp_ = operator+(other).getTimestamp(); 
            civilTime_ = toolbox::getCivilFromTimestamp(
                _getModifiedTimestamp(
                    tmsp_
                    , -static_cast<int>(timeZone_)
                    , type_));
        }

        void DateTime::operator-=(const TimeDelta& other){ 
            tmsp_ = operator-(other).getTimestamp(); 
            civilTime_ = toolbox::getCivilFromTimestamp(
                _getModifiedTimestamp(
                    tmsp_
                    , -static_cast<int>(timeZone_)
                    , type_));
        }

        bool DateTime::operator==(const DateTime& other) const {
            if (getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()==other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
            return false;
        }

        bool DateTime::operator<(const DateTime& other) const {
            if (getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()<other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
            return false;
        }

        bool DateTime::operator<=(const DateTime& other) const {
            if (getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()<=other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
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
                ,other.years_);
            TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
            return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
        }

        DateTime DateTime::operator-(const TimeDelta::Years& other) const {

            auto [y,m,d] = toolbox::addYearsToCivilDate(
                std::get<0>(civilTime_)
                ,std::get<1>(civilTime_)
                ,std::get<2>(civilTime_)
                ,-other.years_);
            
            TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
            return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
        }

        DateTime DateTime::operator+(const TimeDelta::Months& other) const {
        
            auto [y,m,d] = toolbox::addMonthsToCivilDate(
                std::get<0>(civilTime_)
                ,std::get<1>(civilTime_)
                ,std::get<2>(civilTime_)
                ,other.months_);
            TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
            return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
        }

        DateTime DateTime::operator-(const TimeDelta::Months& other) const {

            auto [y,m,d] = toolbox::addMonthsToCivilDate(
                std::get<0>(civilTime_)
                ,std::get<1>(civilTime_)
                ,std::get<2>(civilTime_)
                ,-other.months_);

            TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
            return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
        }

        void DateTime::operator+=(const TimeDelta::Years& other){
            tmsp_ = operator+(other).getTimestamp(); 
            civilTime_ = toolbox::getCivilFromTimestamp(
                _getModifiedTimestamp(
                    tmsp_
                    , -static_cast<int>(timeZone_)
                    , type_));
            
        }

        void DateTime::operator-=(const TimeDelta::Years& other) {
            
            tmsp_ = operator-(other).getTimestamp(); 
            civilTime_ = toolbox::getCivilFromTimestamp(
                _getModifiedTimestamp(
                    tmsp_
                    , -static_cast<int>(timeZone_)
                    , type_));
        }

        void DateTime::operator+=(const TimeDelta::Months& other) {
            
            tmsp_ = operator+(other).getTimestamp(); 
            civilTime_ = toolbox::getCivilFromTimestamp(
                _getModifiedTimestamp(
                    tmsp_
                    , -static_cast<int>(timeZone_)
                    , type_));
        }

        void DateTime::operator-=(const TimeDelta::Months& other) {
            
            tmsp_ = operator-(other).getTimestamp(); 
            civilTime_ = toolbox::getCivilFromTimestamp(
                _getModifiedTimestamp(
                    tmsp_
                    , -static_cast<int>(timeZone_)
                    , type_));
        }



    }
}