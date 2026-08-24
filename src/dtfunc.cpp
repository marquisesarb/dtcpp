#include <dtcpp/datetime.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    std::string DateTime::asString(std::string dateFormat, TimeZone timeZone) const {

        int tz = static_cast<int>(timeZone);
        std::string utcString = " UTC" + ((tz < 0) ? "-" + std::to_string(std::abs(tz)) : "+" + std::to_string(std::abs(tz)));  
        auto [y,m,d,h,mi,s] = civilTime(timeZone);
        return toolbox::getCivilDateHourStringFromCivilDateHour(y,m,d,h,mi,s,dateFormat) + utcString;
    }

    std::string DateTime::asString(std::string dateFormat) const {

        return asString(dateFormat,TimeZone::UTC);
    }

    std::tuple<int,int,int,int,int,int> DateTime::civilTime(TimeZone timeZone) const {

        long long tmsp = _getModifiedTimestamp(timestamp(),  EpochTimestampType::NANOSECONDS, EpochTimestampType::SECONDS); 
        tmsp += static_cast<int>(timeZone)*3600LL;
        return toolbox::getCivilFromTimestamp(tmsp);
    }

    std::tuple<int,int,int,int,int,int> DateTime::civilTime() const {

        return civilTime(TimeZone::UTC);
    }


    long long DateTime::_getModifiedTimestamp(long long tmsp, EpochTimestampType fromType, EpochTimestampType toType) {

        long long value = tmsp;
        long long from = static_cast<long long>(fromType);
        long long to   = static_cast<long long>(toType);

        if (from < to) value *= (to / from);
        else value /= (from / to);

        return value;
    }


}