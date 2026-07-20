#pragma once 
#include <dtcpp/datetime.hpp>

namespace dtcpp::fin {

    enum class TenorType {DAYS,WEEKS,MONTHS,YEARS};

    struct Tenor {

        int value_; 
        TenorType type_;

        DateTime getForwardDate(const DateTime& date, int n) const {

            DateTime forwardDate = date;
            n = std::max(1,n);
            switch (type_) {
            case TenorType::DAYS: forwardDate += TimeDelta{n*int(value_),0,0,0,0,0,0}; break;
            case TenorType::WEEKS: forwardDate +=  TimeDelta{n*7*int(value_),0,0,0,0,0,0}; break;
            case TenorType::MONTHS: forwardDate += TimeDelta::Months{n*int(value_)}; break;
            case TenorType::YEARS: forwardDate += TimeDelta::Years{n*int(value_)}; break;

            }
            return forwardDate;
        }

        int getMultiple(const Tenor& other) const {

            if (type_ == other.type_) {

                if (other.value_ <= value_ && value_ % other.value_ == 0) {
                    return value_ / other.value_;
                }
                return 0;
            }

            if (other.type_ == TenorType::DAYS && type_  == TenorType::WEEKS) {

                int weeksInDays = 7 * value_;
                if (other.value_ <= weeksInDays && weeksInDays % other.value_ == 0) {

                    return weeksInDays / other.value_;
                }
                return 0;
            }

            if (other.type_ == TenorType::MONTHS && type_  == TenorType::YEARS) {

                int yearsInMonths = 12 * value_;
                if (other.value_ <= yearsInMonths && yearsInMonths % other.value_ == 0) {

                    return yearsInMonths / other.value_;
                }
                return 0;
            }

            if (other.type_ == TenorType::WEEKS && type_  == TenorType::DAYS) {

                int weeksInDays = 7 * other.value_;
                if (weeksInDays <= value_ && value_ % weeksInDays == 0) {

                    return value_ / weeksInDays;
                }
                return 0;
            }

            if (other.type_ == TenorType::YEARS && type_  == TenorType::MONTHS) {

                int monthsInDays = 12 * other.value_;
                if (monthsInDays <= value_ && value_ % monthsInDays == 0) {

                    return value_ / monthsInDays;
                }
                return 0;
            }

            return 0;
        }

        int getFactor(const Tenor& other) const {return other.getMultiple(*this);}

        bool operator==(Tenor other) const {DateTime now{};return (getForwardDate(now,1) == other.getForwardDate(now,1));}
        bool operator!=(Tenor other) const {return !operator==(other);}
        bool operator>(Tenor other) const {DateTime now{};return (getForwardDate(now,1) > other.getForwardDate(now,1));}
        bool operator>=(Tenor other) const {DateTime now{};return (getForwardDate(now,1) >= other.getForwardDate(now,1));}
        bool operator<=(Tenor other) const {DateTime now{};return (getForwardDate(now,1) <= other.getForwardDate(now,1));}
        bool operator<(Tenor other) const {DateTime now{};return (getForwardDate(now,1) < other.getForwardDate(now,1));}

    };

}