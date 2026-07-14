#include <dtcpp/objects.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    namespace objects {

        DateTime::DateTime(long long timestamp, EpochTimestampType type, TimeZone timeZone): 
        tmsp_(timestamp)
        , type_(type)
        , timeZone_(timeZone){
            civilTime_ = toolbox::getCivilFromTimestamp(
                _getModifiedTimestamp(
                    timestamp
                    , -static_cast<int>(timeZone)
                    , type));
        }

        DateTime::DateTime(long long timestamp, EpochTimestampType type): 
        DateTime(timestamp,type, TimeZone::UTC) 
        {};

        DateTime::DateTime(TimeZone timeZone):
        DateTime(toolbox::nowNanoSeconds(),EpochTimestampType::NANOSECONDS, timeZone) 
        {}

        DateTime::DateTime(): DateTime(TimeZone::UTC) {}

        DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, TimeZone timeZone): 
        tmsp_(toolbox::getTimestampFromCivilDateHour(year,month,day,hour,minute,second) - static_cast<int>(timeZone)*3600LL)
        , type_(EpochTimestampType::SECONDS)
        , timeZone_(timeZone)
        , civilTime_(std::make_tuple(year,month,day,hour,minute,second))
        {}

        DateTime::DateTime(int year, int month, int day, int hour, int minute, int second): 
        DateTime(year, month, day, hour, minute, second, TimeZone::UTC) 
        {}

        DateTime::DateTime(int year, int month, int day, TimeZone timeZone): 
        DateTime(year,month,day,0,0,0,timeZone) 
        {}

        DateTime::DateTime(int year, int month, int day): 
        DateTime(year, month, day, TimeZone::UTC) 
        {}

        DateTime::DateTime(const std::string& dateString, const std::string& formatString, TimeZone timeZone)
        {
            tmsp_ = toolbox::getTimestampFromCivilDateHourString(dateString, formatString) - static_cast<int>(timeZone)*3600LL;
            type_ = EpochTimestampType::SECONDS;
            timeZone_ = timeZone;
            civilTime_ = toolbox::getCivilFromTimestamp(tmsp_+static_cast<int>(timeZone)*3600LL);
        }

        DateTime::DateTime(const std::string& dateString, const std::string& formatString): DateTime(dateString, formatString, TimeZone::UTC) {}

    } 

}