#include <dtcpp/datetime.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    DateTime DateTime::switchTimestampType(EpochTimestampType type) const {

        if (type == type_) return *this;

        long long value = tmsp_;
        long long from = static_cast<long long>(type_);
        long long to   = static_cast<long long>(type);

        if (from < to) value *= (to / from);
        else value /= (from / to);

        return DateTime(value, type, timeZone_);
    }

    long long DateTime::timestamp() const { return tmsp_; }

    EpochTimestampType DateTime::timestampType() const { return type_; }

    TimeZone DateTime::timeZone() const { return timeZone_; }

    std::string DateTime::asString(std::string dateFormat) const {

        int tz = static_cast<int>(timeZone_);
        std::string utcString = " UTC" + ((tz < 0) ? "-" + std::to_string(std::abs(tz)) : "+" + std::to_string(std::abs(tz)));
        auto [y,m,d,h,mi,s] = civilTime_;
        return toolbox::getCivilDateHourStringFromCivilDateHour(y,m,d,h,mi,s,dateFormat) + utcString;
    }

    void DateTime::setTimestampType(const EpochTimestampType type) {

        tmsp_ = switchTimestampType(type).timestamp(); 
        type_ = type;
    }

    void DateTime::setTimeZone(TimeZone timeZone) { 

        civilTime_ = toolbox::getCivilFromTimestamp(
            _getModifiedTimestamp(
                tmsp_
                , -static_cast<int>(timeZone)
                , type_));
        timeZone_ = timeZone; 
    }

    long long DateTime::_getModifiedTimestamp(long long tmsp, int hourOffset, EpochTimestampType type) {

        long long value = tmsp;
        long long from = static_cast<long long>(type);
        long long to   = static_cast<long long>(EpochTimestampType::SECONDS);

        if (from < to) value *= (to / from);
        else value /= (from / to);

        return value - hourOffset*3600LL;
    }

    int DateTime::year() const { return std::get<0>(civilTime_); }

    int DateTime::day() const { return std::get<2>(civilTime_); }

    int DateTime::month() const { return std::get<1>(civilTime_); }

}