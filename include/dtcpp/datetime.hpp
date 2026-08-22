#pragma once 
#include <dtcpp/timedelta.hpp>
#include <string>

namespace dtcpp {

    enum class EpochTimestampType {

        SECONDS = 1, 
        MILLISECONDS = 1000, 
        MICROSECONDS = 1000000, 
        NANOSECONDS = 1000000000 
    };

    enum class TimeZone {

        UTC = 0, 
        UTCM1 = -1, UTCP1 = 1,
        UTCM2 = -2, UTCP2 = 2,
        UTCM3 = -3, UTCP3 = 3,
        UTCM4 = -4, UTCP4 = 4,
        UTCM5 = -5, UTCP5 = 5,
        UTCM6 = -6, UTCP6 = 6,
        UTCM7 = -7, UTCP7 = 7,
        UTCM8 = -8, UTCP8 = 8,
        UTCM9 = -9, UTCP9 = 9,
        UTCM10 = -10, UTCP10 = 10,
        UTCM11 = -11, UTCP11 = 11,
        UTCM12 = -12, UTCP12 = 12,
        UTCP13 = 13,
        UTCP14 = 14,
        
    };

    class DateTime {

        public:
            long long timestamp; 

            DateTime();
            DateTime(long long timestamp_, EpochTimestampType type);
            DateTime(long long timestamp_);
            DateTime(int year, int month, int day, int hour, int minute, int second, TimeZone timeZone_);
            DateTime(int year, int month, int day, TimeZone timeZone_);
            DateTime(const std::string& dateString, const std::string& formatString, TimeZone timeZone_); 
            DateTime(int year, int month, int day, int hour, int minute, int second);
            DateTime(int year, int month, int day);
            DateTime(const std::string& dateString, const std::string& formatString); 
            ~DateTime(){};

            DateTime operator+(const TimeDelta& other) const; 
            DateTime operator-(const TimeDelta& other) const; 
            TimeDelta operator-(const DateTime& other) const; 
            void operator+=(const TimeDelta& other); 
            void operator-=(const TimeDelta& other); 
            bool operator==(const DateTime& other) const; 
            bool operator!=(const DateTime& other) const; 
            bool operator<(const DateTime& other) const; 
            bool operator<=(const DateTime& other) const; 
            bool operator>=(const DateTime& other) const; 
            bool operator>(const DateTime& other) const; 
            DateTime operator+(const TimeDelta::Years& other) const; 
            DateTime operator-(const TimeDelta::Years& other) const; 
            DateTime operator+(const TimeDelta::Months& other) const; 
            DateTime operator-(const TimeDelta::Months& other) const; 
            void operator+=(const TimeDelta::Years& other); 
            void operator-=(const TimeDelta::Years& other); 
            void operator+=(const TimeDelta::Months& other); 
            void operator-=(const TimeDelta::Months& other); 

            std::string asString(std::string dateFormat, TimeZone timeZone) const;
            std::tuple<int,int,int,int,int,int> civilTime(TimeZone timeZone) const;
            std::string asString(std::string dateFormat) const;
            std::tuple<int,int,int,int,int,int> civilTime() const;

        private:
            static long long _getModifiedTimestamp(long long tmsp, EpochTimestampType fromType, EpochTimestampType toType);
    };

}