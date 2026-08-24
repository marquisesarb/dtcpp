#include <dtcpp/datetime.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    DateTime::DateTime(long long timestamp_, EpochTimestampType type): 
    _timestamp(_getModifiedTimestamp(timestamp_,type, EpochTimestampType::NANOSECONDS)){}

    DateTime::DateTime(long long timestamp_): DateTime(timestamp_,EpochTimestampType::NANOSECONDS) {};

    DateTime::DateTime(): DateTime(toolbox::nowNanoSeconds(),EpochTimestampType::NANOSECONDS) {}

    DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, TimeZone timeZone_) {

        long long tmsp = toolbox::getTimestampFromCivilDateHour(year,month,day,hour,minute,second); 
        tmsp -= static_cast<int>(timeZone_) * 3600LL;
        _timestamp = _getModifiedTimestamp(tmsp,EpochTimestampType::SECONDS, EpochTimestampType::NANOSECONDS);
    }

    DateTime::DateTime(int year, int month, int day, TimeZone timeZone_): DateTime(year,month,day,0,0,0,timeZone_) {}

    DateTime::DateTime(const std::string& dateString, const std::string& formatString, TimeZone timeZone_) {
        long long tmsp = toolbox::getTimestampFromCivilDateHourString(dateString, formatString); 
        tmsp -= static_cast<int>(timeZone_) * 3600LL;
        _timestamp = _getModifiedTimestamp(tmsp,EpochTimestampType::SECONDS, EpochTimestampType::NANOSECONDS);
    }

     DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {

        long long tmsp = toolbox::getTimestampFromCivilDateHour(year,month,day,hour,minute,second); 
        tmsp -= static_cast<int>(TimeZone::UTC) * 3600LL;
        _timestamp = _getModifiedTimestamp(tmsp,EpochTimestampType::SECONDS, EpochTimestampType::NANOSECONDS);
    }

    DateTime::DateTime(int year, int month, int day): DateTime(year,month,day,0,0,0,TimeZone::UTC) {}

    DateTime::DateTime(const std::string& dateString, const std::string& formatString) {
        long long tmsp = toolbox::getTimestampFromCivilDateHourString(dateString, formatString); 
        tmsp -= static_cast<int>(TimeZone::UTC) * 3600LL;
        _timestamp = _getModifiedTimestamp(tmsp,EpochTimestampType::SECONDS, EpochTimestampType::NANOSECONDS);
    }

}