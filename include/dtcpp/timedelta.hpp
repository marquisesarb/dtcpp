#pragma once

namespace dtcpp {

    class TimeDelta {
 
        public:
            TimeDelta(long long days,long long hours,long long minutes,long long seconds,long long milliseconds,long long microseconds,long long nanoseconds) {

                _totalNanoseconds = 
                    days * 86'400'000'000'000LL +
                    hours * 3'600'000'000'000LL +
                    minutes * 60'000'000'000LL +
                    seconds * 1'000'000'000LL +
                    milliseconds * 1'000'000LL +
                    microseconds * 1'000LL +
                    nanoseconds;
            }

            TimeDelta(long long nanoseconds): _totalNanoseconds(nanoseconds){}

            TimeDelta(){}

            struct Years { int years; };
            struct Months { int months; };

            TimeDelta operator+(const TimeDelta& other) const {return {totalNanoseconds()+other.totalNanoseconds()}; }
            TimeDelta operator-(const TimeDelta& other) const {return {totalNanoseconds()-other.totalNanoseconds()}; }
            void operator+=(const TimeDelta& other) { _totalNanoseconds = totalNanoseconds() + other.totalNanoseconds(); } 
            void operator-=(const TimeDelta& other) { _totalNanoseconds = (totalNanoseconds() - other.totalNanoseconds()); } 
            bool operator==(const TimeDelta& other) const { return other.totalNanoseconds()==totalNanoseconds(); }
            bool operator!=(const TimeDelta& other) const { return other.totalNanoseconds()!=totalNanoseconds(); }
            bool operator<(const TimeDelta& other) const { return other.totalNanoseconds()>totalNanoseconds(); }
            bool operator<=(const TimeDelta& other) const { return other.totalNanoseconds()>=totalNanoseconds(); }
            bool operator>=(const TimeDelta& other) const { return other.totalNanoseconds()<=totalNanoseconds(); }
            bool operator>(const TimeDelta& other) const { return other.totalNanoseconds()<totalNanoseconds(); }

            long long totalNanoseconds() const {return _totalNanoseconds;}

        private: 
            long long _totalNanoseconds;
            
    }; 

}