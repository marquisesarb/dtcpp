#pragma once 
#include <algorithm>
#include <cassert>
#include <dtcpp/objects.hpp>
#include <dtcpp/toolbox.hpp>
#include <dtcpp/bizdays.hpp>

namespace dtcpp {

    namespace finance {

        enum class DayCountConvention {

            ACTUAL_360, 
            ACTUAL_365, 
            ACTUAL_364, 
            ACTUAL_ACTUAL, 
            E30_360, 
            BOND_BASIS30_360
        };

        enum class TenorType {DAYS,WEEKS,MONTHS,YEARS};

        struct Tenor {

            int value_; 
            TenorType type_;

            objects::DateTime getForwardDate(const objects::DateTime& date, int n) const {

                objects::DateTime forwardDate = date;
                n = std::max(1,n);
                switch (type_) {
                case TenorType::DAYS: forwardDate += objects::TimeDelta{n*int(value_),0,0,0,0,0,0}; break;
                case TenorType::WEEKS: forwardDate +=  objects::TimeDelta{n*7*int(value_),0,0,0,0,0,0}; break;
                case TenorType::MONTHS: forwardDate += objects::TimeDelta::Months{n*int(value_)}; break;
                case TenorType::YEARS: forwardDate += objects::TimeDelta::Years{n*int(value_)}; break;

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

            bool operator==(Tenor other) const {objects::DateTime now{};return (getForwardDate(now,1) == other.getForwardDate(now,1));}
            bool operator!=(Tenor other) const {return !operator==(other);}
            bool operator>(Tenor other) const {objects::DateTime now{};return (getForwardDate(now,1) > other.getForwardDate(now,1));}
            bool operator>=(Tenor other) const {objects::DateTime now{};return (getForwardDate(now,1) >= other.getForwardDate(now,1));}
            bool operator<=(Tenor other) const {objects::DateTime now{};return (getForwardDate(now,1) <= other.getForwardDate(now,1));}
            bool operator<(Tenor other) const {objects::DateTime now{};return (getForwardDate(now,1) < other.getForwardDate(now,1));}

        };

        static constexpr double FACTOR365 = 365.0*toolbox::dayInNanoSeconds;
        static constexpr double FACTOR366 = 366.0*toolbox::dayInNanoSeconds;
        static constexpr double FACTOR364 = 364.0*toolbox::dayInNanoSeconds;
        static constexpr double FACTOR360 = 360.0*toolbox::dayInNanoSeconds;

        inline objects::TimeDelta timeInLeapYears(const objects::DateTime& startDate, const objects::DateTime& endDate) {

            int endYear = endDate.getYear(), startYear = startDate.getYear();
            objects::TimeDelta result{0,0,0,0,0,0,0};
            if (endYear == startYear) { 
                if (toolbox::isLeapYear(endYear)) result = endDate - startDate; 
            } else {
                for (int y = startYear; y<=endYear; y++) {

                    if (!toolbox::isLeapYear(y)) continue ; 
                    
                    if (y == startYear) {

                        result += objects::DateTime(startYear+1,1,1,startDate.getTimeZone())-startDate;

                    } else if (y == endYear) {

                        result += endDate - objects::DateTime(endYear,1,1,startDate.getTimeZone());

                    } else {

                        result += objects::TimeDelta{366,0,0,0,0,0,0};
                    }
                }
            }
            
            return result;
        }

        inline double baseCount30360(const objects::DateTime& startDate, const objects::DateTime& endDate) {return 360.0*(endDate.getYear()-startDate.getYear()) + 30.0*(endDate.getMonth()-startDate.getMonth());}

        inline double yfAct360(const objects::DateTime& startDate, const objects::DateTime& endDate) {return double((endDate-startDate).getTotalNanoSeconds())/FACTOR360;}
        inline double yfAct365(const objects::DateTime& startDate, const objects::DateTime& endDate) {return double((endDate-startDate).getTotalNanoSeconds())/FACTOR365;}
        inline double yfAct364(const objects::DateTime& startDate, const objects::DateTime& endDate) {return double((endDate-startDate).getTotalNanoSeconds())/FACTOR364;}

        inline double yfActAct(const objects::DateTime& startDate, const objects::DateTime& endDate) {

            long long leap = double(timeInLeapYears(startDate, endDate).getTotalNanoSeconds());
            long long total = double((endDate-startDate).getTotalNanoSeconds()); 
            return double(leap)/FACTOR366 + double(total-leap)/FACTOR365;
        } 

        inline double yfE30_360(const objects::DateTime& startDate, const objects::DateTime& endDate) {

            int d2 = endDate.getDay(), d1 = startDate.getDay(); 
            return (baseCount30360(startDate,endDate) + (std::min(30,d2)-std::min(30,d1)))/360.0;
        }

        inline double yfBondBasis30_360(const objects::DateTime& startDate, const objects::DateTime& endDate) {

            int d2 = endDate.getDay(), d1 = startDate.getDay(); 
            d1 = std::min(30,d1);
            d2 = (d1==30) ? std::min(30,d2) : d2;
            return (baseCount30360(startDate,endDate) + (d2-d1))/360.0;
        }
        
        inline double yearFraction(const objects::DateTime& startDate, const objects::DateTime& endDate, DayCountConvention dayCountConvention) {

            switch (dayCountConvention){

                case DayCountConvention::ACTUAL_360: return yfAct360(startDate,endDate);
                case DayCountConvention::ACTUAL_365: return yfAct365(startDate,endDate);
                case DayCountConvention::ACTUAL_364: return yfAct364(startDate,endDate);
                case DayCountConvention::ACTUAL_ACTUAL: return yfActAct(startDate,endDate);
                case DayCountConvention::BOND_BASIS30_360: return yfBondBasis30_360(startDate,endDate);
                case DayCountConvention::E30_360: return yfE30_360(startDate,endDate);
                default: assert(false);

            }
        }

        inline objects::DatetimeSequence bondSchedule(
            const objects::DateTime& startDate, 
            Tenor frequencyTenor, 
            Tenor maturityTenor, 
            bizdays::BusinessDayConvention businessDayConvention, 
            bizdays::HolidayCalendar holidayCalendar, 
            bool includeStartDate, 
            bool includeMaturityDate) {

            int n = maturityTenor.getMultiple(frequencyTenor); 
            std::set<objects::DateTime> dates; 
            if (includeStartDate) dates.insert(bizdays::adjustDate(startDate, holidayCalendar, businessDayConvention));
            if (includeMaturityDate) dates.insert(bizdays::adjustDate(maturityTenor.getForwardDate(startDate, 1), holidayCalendar, businessDayConvention)); 
    
            for (int i = 0; i<n-1; i++) {

                objects::DateTime unadjustedDate = frequencyTenor.getForwardDate(startDate, i+1);
                dates.insert(bizdays::adjustDate(unadjustedDate, holidayCalendar, businessDayConvention));
            }
            return {dates};
        }
    }
}