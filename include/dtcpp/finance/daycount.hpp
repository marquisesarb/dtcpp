#pragma once 
#include <limits>
#include <dtcpp/datetime.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp::fin {

    enum class DayCountConvention {

        ACTUAL_360, 
        ACTUAL_365, 
        ACTUAL_364, 
        ACTUAL_ACTUAL, 
        E30_360, 
        BOND_BASIS30_360
    };

    namespace yftools {

        static constexpr double FACTOR365 = 365.0*toolbox::dayInNanoSeconds;
        static constexpr double FACTOR366 = 366.0*toolbox::dayInNanoSeconds;
        static constexpr double FACTOR364 = 364.0*toolbox::dayInNanoSeconds;
        static constexpr double FACTOR360 = 360.0*toolbox::dayInNanoSeconds;

        inline TimeDelta timeInLeapYears(const DateTime& startDate, const DateTime& endDate) {

            int endYear = endDate.year(), startYear = startDate.year();
            TimeDelta result{0,0,0,0,0,0,0};
            if (endYear == startYear) { 
                if (toolbox::isLeapYear(endYear)) result = endDate - startDate; 
            } else {
                for (int y = startYear; y<=endYear; y++) {

                    if (!toolbox::isLeapYear(y)) continue ; 
                    
                    if (y == startYear) {

                        result += DateTime(startYear+1,1,1,startDate.timeZone())-startDate;

                    } else if (y == endYear) {

                        result += endDate - DateTime(endYear,1,1,startDate.timeZone());

                    } else {

                        result += TimeDelta{366,0,0,0,0,0,0};
                    }
                }
            }
            
            return result;
        }

        inline double baseCount30360(const DateTime& startDate, const DateTime& endDate) {return 360.0*(endDate.year()-startDate.year()) + 30.0*(endDate.month()-startDate.month());}

        inline double yfAct360(const DateTime& startDate, const DateTime& endDate) {return double((endDate-startDate).totalNanoseconds())/FACTOR360;}
        inline double yfAct365(const DateTime& startDate, const DateTime& endDate) {return double((endDate-startDate).totalNanoseconds())/FACTOR365;}
        inline double yfAct364(const DateTime& startDate, const DateTime& endDate) {return double((endDate-startDate).totalNanoseconds())/FACTOR364;}

        inline double yfActAct(const DateTime& startDate, const DateTime& endDate) {

            long long leap = double(timeInLeapYears(startDate, endDate).totalNanoseconds());
            long long total = double((endDate-startDate).totalNanoseconds()); 
            return double(leap)/FACTOR366 + double(total-leap)/FACTOR365;
        } 

        inline double yfE30_360(const DateTime& startDate, const DateTime& endDate) {

            int d2 = endDate.day(), d1 = startDate.day(); 
            return (baseCount30360(startDate,endDate) + (std::min(30,d2)-std::min(30,d1)))/360.0;
        }

        inline double yfBondBasis30_360(const DateTime& startDate, const DateTime& endDate) {

            int d2 = endDate.day(), d1 = startDate.day(); 
            d1 = std::min(30,d1);
            d2 = (d1==30) ? std::min(30,d2) : d2;
            return (baseCount30360(startDate,endDate) + (d2-d1))/360.0;
        }
        
    }

    inline double yearFraction(const DateTime& startDate, const DateTime& endDate, DayCountConvention dayCountConvention) {

        switch (dayCountConvention){

            case DayCountConvention::ACTUAL_360: return yftools::yfAct360(startDate,endDate);
            case DayCountConvention::ACTUAL_365: return yftools::yfAct365(startDate,endDate);
            case DayCountConvention::ACTUAL_364: return yftools::yfAct364(startDate,endDate);
            case DayCountConvention::ACTUAL_ACTUAL: return yftools::yfActAct(startDate,endDate);
            case DayCountConvention::BOND_BASIS30_360: return yftools::yfBondBasis30_360(startDate,endDate);
            case DayCountConvention::E30_360: return yftools::yfE30_360(startDate,endDate);
            default: return std::numeric_limits<double>::quiet_NaN();

        }
    }

}