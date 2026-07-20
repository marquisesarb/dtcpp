#pragma once

namespace dtcpp {

    struct TimeDelta {

        long long days; 
        long long hours; 
        long long minutes; 
        long long seconds; 
        long long milliseconds; 
        long long microseconds;
        long long nanoseconds;

        struct Years { int years; };
        struct Months { int months; };

        long long totalSeconds() const {

            long long totalSeconds =
                days * 86'400LL +
                hours * 3'600LL +
                minutes * 60LL +
                seconds;

            totalSeconds += microseconds / 1'000LL;
            totalSeconds += milliseconds / 1'000'000LL;
            totalSeconds += nanoseconds  / 1'000'000'000LL;

            return totalSeconds;
        }
        
        long long totalMilliseconds() const {

            long long totalMs =
                days * 86'400'000LL +
                hours * 3'600'000LL +
                minutes * 60'000LL +
                seconds * 1'000LL +
                milliseconds;

            totalMs += microseconds / 1'000LL;
            totalMs += nanoseconds  / 1'000'000LL;

            return totalMs;
        }

        long long totalMicroseconds() const {

            long long totalUs =
                days * 86'400'000'000LL +
                hours * 3'600'000'000LL +
                minutes * 60'000'000LL +
                seconds * 1'000'000LL +
                milliseconds * 1'000LL +
                microseconds;

            totalUs += nanoseconds / 1'000LL;

            return totalUs;
        }

        long long totalNanoseconds() const {

            return
                days * 86'400'000'000'000LL +
                hours * 3'600'000'000'000LL +
                minutes * 60'000'000'000LL +
                seconds * 1'000'000'000LL +
                milliseconds * 1'000'000LL +
                microseconds * 1'000LL +
                nanoseconds;
        }
        
        TimeDelta operator+(const TimeDelta& other) const {return {0,0,0,0,0,0,totalNanoseconds()+other.totalNanoseconds()}; }
        TimeDelta operator-(const TimeDelta& other) const {return {0,0,0,0,0,0,totalNanoseconds()-other.totalNanoseconds()}; }
        void operator+=(const TimeDelta& other) { nanoseconds = (nanoseconds + other.totalNanoseconds()); } 
        void operator-=(const TimeDelta& other) { nanoseconds = (nanoseconds - other.totalNanoseconds()); } 
        bool operator==(const TimeDelta& other) const { return other.totalNanoseconds()==totalNanoseconds(); }
        bool operator!=(const TimeDelta& other) const { return other.totalNanoseconds()!=totalNanoseconds(); }
        bool operator<(const TimeDelta& other) const { return other.totalNanoseconds()>totalNanoseconds(); }
        bool operator<=(const TimeDelta& other) const { return other.totalNanoseconds()>=totalNanoseconds(); }
        bool operator>=(const TimeDelta& other) const { return other.totalNanoseconds()<=totalNanoseconds(); }
        bool operator>(const TimeDelta& other) const { return other.totalNanoseconds()<totalNanoseconds(); }

            
    }; 

}