#pragma once 
#include <dtcpp/datetime.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    enum class BusinessDayConvention {
        FOLLOWING, 
        PRECEDING, 
        MODIFIED_FOLLOWING, 
        MODIFIED_PRECEDING
    };

    class BusinessCalendar {

        public:
            BusinessCalendar(){};
            virtual ~BusinessCalendar() = default; 

            virtual bool isBusinessDay(const DateTime& referenceDate) const = 0; 

            DateTime adjustForBusiness(const DateTime& referenceDate, BusinessDayConvention businessDayConvention) const {

                DateTime result = referenceDate;
                switch (businessDayConvention) {
                    case BusinessDayConvention::FOLLOWING: return adjustDateFollowingConvention(referenceDate);
                    case BusinessDayConvention::PRECEDING: return adjustDatePrecedingConvention(referenceDate);
                    case BusinessDayConvention::MODIFIED_FOLLOWING: return adjustDateModifiedFollowingConvention(referenceDate);
                    case BusinessDayConvention::MODIFIED_PRECEDING: return adjustDateModifiedPrecedingConvention(referenceDate);
                }
                return result;
            }

        private:

            DateTime adjustDateFollowingConvention(const DateTime& referenceDate) const {

                DateTime newDate = referenceDate;
                while (!isBusinessDay(newDate)) { newDate += TimeDelta{1,0,0,0,0,0,0}; }
                return newDate;
            }

            DateTime adjustDatePrecedingConvention(const DateTime& referenceDate) const {

                DateTime newDate = referenceDate;
                while (!isBusinessDay(newDate)) { newDate -= TimeDelta{1,0,0,0,0,0,0}; }
                return newDate;
            }

            DateTime adjustDateModifiedPrecedingConvention(const DateTime& referenceDate) const {

                DateTime modPrec = adjustDatePrecedingConvention(referenceDate); 
                if (modPrec.month()== referenceDate.month()) return modPrec; 
                else return adjustDateFollowingConvention(referenceDate);
            }

            DateTime adjustDateModifiedFollowingConvention(const DateTime& referenceDate) const {

                DateTime modFol = adjustDateFollowingConvention(referenceDate); 
                if (modFol.month() == referenceDate.month()) return modFol; 
                else return adjustDatePrecedingConvention(referenceDate);
            }
    };

    class NoHolidayCalendar final: public BusinessCalendar {

        public:
            NoHolidayCalendar(){};
            virtual bool isBusinessDay(const DateTime& referenceDate) const {return true;}; 
    };

    class WeekEndOffCalendar final: public BusinessCalendar {

        public:
            WeekEndOffCalendar(){};
            virtual bool isBusinessDay(const DateTime& referenceDate) const {
                int wk = toolbox::getWeekDayFromCivilDate(referenceDate.year(),referenceDate.month(),referenceDate.day()); 
                return (wk==6 or wk==0) ? false : true;
            }; 
    };
    

}