#pragma once 
#include <tuple>
#include <vector>
#include <set>
#include <string>
#include <optional>
#include <algorithm>

namespace dtcpp {

    namespace objects {

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

        struct TimeDelta {

            long long days_; 
            long long hours_; 
            long long minutes_; 
            long long seconds_; 
            long long milliseconds_; 
            long long microseconds_;
            long long nanoseconds_;

            struct Years { int years_; };
            struct Months { int months_; };

            long long getTotalSeconds() const {

                long long totalSeconds =
                    days_ * 86'400LL +
                    hours_ * 3'600LL +
                    minutes_ * 60LL +
                    seconds_;

                totalSeconds += microseconds_ / 1'000LL;
                totalSeconds += milliseconds_ / 1'000'000LL;
                totalSeconds += nanoseconds_  / 1'000'000'000LL;

                return totalSeconds;
            }
            
            long long getTotalMilliSeconds() const {

                long long totalMs =
                    days_ * 86'400'000LL +
                    hours_ * 3'600'000LL +
                    minutes_ * 60'000LL +
                    seconds_ * 1'000LL +
                    milliseconds_;

                totalMs += microseconds_ / 1'000LL;
                totalMs += nanoseconds_  / 1'000'000LL;

                return totalMs;
            }

            long long getTotalMicroSeconds() const {

                long long totalUs =
                    days_ * 86'400'000'000LL +
                    hours_ * 3'600'000'000LL +
                    minutes_ * 60'000'000LL +
                    seconds_ * 1'000'000LL +
                    milliseconds_ * 1'000LL +
                    microseconds_;

                totalUs += nanoseconds_ / 1'000LL;

                return totalUs;
            }

            long long getTotalNanoSeconds() const {

                return
                    days_ * 86'400'000'000'000LL +
                    hours_ * 3'600'000'000'000LL +
                    minutes_ * 60'000'000'000LL +
                    seconds_ * 1'000'000'000LL +
                    milliseconds_ * 1'000'000LL +
                    microseconds_ * 1'000LL +
                    nanoseconds_;
            }
            
            TimeDelta operator+(const TimeDelta& other) const {return {0,0,0,0,0,0,getTotalNanoSeconds()+other.getTotalNanoSeconds()}; }
            TimeDelta operator-(const TimeDelta& other) const {return {0,0,0,0,0,0,getTotalNanoSeconds()-other.getTotalNanoSeconds()}; }
            void operator+=(const TimeDelta& other) { nanoseconds_ = (nanoseconds_ + other.getTotalNanoSeconds()); } 
            void operator-=(const TimeDelta& other) { nanoseconds_ = (nanoseconds_ - other.getTotalNanoSeconds()); } 
            bool operator==(const TimeDelta& other) const { return other.getTotalNanoSeconds()==getTotalNanoSeconds(); }
            bool operator!=(const TimeDelta& other) const { return other.getTotalNanoSeconds()!=getTotalNanoSeconds(); }
            bool operator<(const TimeDelta& other) const { return other.getTotalNanoSeconds()>getTotalNanoSeconds(); }
            bool operator<=(const TimeDelta& other) const { return other.getTotalNanoSeconds()>=getTotalNanoSeconds(); }
            bool operator>=(const TimeDelta& other) const { return other.getTotalNanoSeconds()<=getTotalNanoSeconds(); }
            bool operator>(const TimeDelta& other) const { return other.getTotalNanoSeconds()<getTotalNanoSeconds(); }

                
        }; 

        class DateTime {

            public:
                DateTime(TimeZone timeZone);
                DateTime();
                DateTime(long long timestamp, EpochTimestampType type, TimeZone timeZone);
                DateTime(long long timestamp, EpochTimestampType type);
                DateTime(int year, int month, int day, int hour, int minute, int second, TimeZone timeZone);
                DateTime(int year, int month, int day, TimeZone timeZone);
                DateTime(int year, int month, int day, int hour, int minute, int second);
                DateTime(int year, int month, int day);
                DateTime(const std::string& dateString, const std::string&formatString, TimeZone timeZone);
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

                long long getTimestamp() const; 
                std::string asString(std::string dateFormat) const;
                int getYear() const; 
                int getDay() const; 
                int getMonth() const; 
                DateTime getModifiedTimestampType(EpochTimestampType type) const;
                EpochTimestampType getTimestampType() const;
                TimeZone getTimeZone() const;

                void setTimestampType(EpochTimestampType type);
                void setTimeZone(TimeZone timeZone);

            private:
                long long tmsp_; 
                std::tuple<int,int,int,int,int,int> civilTime_;
                EpochTimestampType type_; 
                TimeZone timeZone_;
                static long long _getModifiedTimestamp(long long tmsp, int hourOffset, EpochTimestampType type);
        };

        struct DatetimeSequence {

            std::set<DateTime> datetimeSequence;

            std::vector<DateTime> asVector() const {return std::vector<DateTime>(datetimeSequence.begin(), datetimeSequence.end());}

            DatetimeSequence sub(int startIndex, int endIndex) const {

                DatetimeSequence result;
                int n = size();

                startIndex = std::clamp(startIndex, 0, n);
                endIndex   = std::clamp(endIndex,   0, n);

                if (startIndex >= endIndex) return result;

                int idx = 0;
                for (auto it = datetimeSequence.begin(); it != datetimeSequence.end(); ++it, ++idx) {
                    if (idx > endIndex) break;
                    if (idx >= startIndex) result.add(*it);
                }

                return result;
            }

            DatetimeSequence sub(const DateTime& startDate, const DateTime& endDate) const {return sub(index(startDate), index(endDate));}

            std::optional<DateTime> previous(const DateTime& date) const {
                auto it = datetimeSequence.lower_bound(date);
                if (it == datetimeSequence.begin()) return std::nullopt;
                --it;
                return *it;
            }

            std::optional<DateTime> next(const DateTime& date) const {
                auto it = datetimeSequence.upper_bound(date);
                if (it == datetimeSequence.end()) return std::nullopt;
                return *it; 
            }

            std::optional<DateTime> start() const {if (datetimeSequence.empty()) return std::nullopt; return *datetimeSequence.begin();}
            std::optional<DateTime> end() const {if (datetimeSequence.empty()) return std::nullopt; return *datetimeSequence.rbegin();}
            bool isExisting(DateTime date) const {return datetimeSequence.find(date) != datetimeSequence.end();};
            int size() const { return datetimeSequence.size();}

            int index(const DateTime& date) const {

                auto it = datetimeSequence.find(date);
                if (it == datetimeSequence.end()) return -1;
                return static_cast<int>(std::distance(datetimeSequence.begin(), it));
            }

            void add(const DateTime& date) { datetimeSequence.insert(date); }
            void remove(const DateTime& date) { datetimeSequence.erase(date); }

        };
    } 
}