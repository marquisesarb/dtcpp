#pragma once 
#include <dtcpp/objects.hpp>
#include <dtcpp/toolbox.hpp>

namespace dtcpp {

    namespace bizdays {

        using namespace objects;

        enum class BusinessDayConvention {
            FOLLOWING, 
            PRECEDING, 
            MODIFIED_FOLLOWING, 
            MODIFIED_PRECEDING
        };

        enum class HolidayCalendar {
            NONE, 
            WEEK_END_OFF,
            US_FEDERAL_RESERVE
        };

        inline bool isWeekEnd(const DateTime& date) {

            int wk = toolbox::getWeekDayFromCivilDate(date.getYear(),date.getMonth(),date.getDay()); 
            return (wk==6 or wk==0) ? true : false;
        }

        inline bool isChristmas(const DateTime& date) { return (date.getDay()==25 && date.getMonth()==12); }

        inline bool isNewYear(const DateTime& date) { return (date.getDay()==1 && date.getMonth()==1); }

        inline bool isMartinLutterKingDay(const DateTime& date) {

            int y = date.getYear(), m = date.getMonth(), d = date.getDay();
            if (m != 1) return false;
            if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getThirdWeekDayOfMonth(y,m,1)==d;
            else return false;
        }

        inline bool isUSWashingtonBirthday(const DateTime& date) {

            int y = date.getYear(), m = date.getMonth(), d = date.getDay();
            if (m != 2) return false;
            if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getThirdWeekDayOfMonth(y,m,1)==d;
            else return false;
        }

        inline bool isUSMemorialDay(const DateTime& date) {

            int y = date.getYear(), m = date.getMonth(), d = date.getDay();
            if (m != 5) return false;
            if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getLastWeekDayOfMonth(y,m,1)==d;
            else return false;
        }

        inline bool isUSJuneteenth(const DateTime& date) {return (date.getDay()==19 && date.getMonth()==6);}

        inline bool isUSIndependanceDay(const DateTime& date) {return (date.getDay()==4 && date.getMonth()==7);}

        inline bool isUSLaborDay(const DateTime& date) {

            int y = date.getYear(), m = date.getMonth(), d = date.getDay();
            if (m != 9) return false;
            if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getFirstWeekDayOfMonth(y,m,1)==d;
            else return false;
        }

        inline bool isUSColumbusDay(const DateTime& date) {

            int y = date.getYear(), m = date.getMonth(), d = date.getDay();
            if (m != 10) return false;
            if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getSecondWeekDayOfMonth(y,m,1)==d;
            else return false;
        }

        inline bool isUSVeteransDay(const DateTime& date) {return (date.getDay()==11 && date.getMonth()==11);}

        inline bool isThanksgivingDay(const DateTime& date) {

            int y = date.getYear(), m = date.getMonth(), d = date.getDay();
            if (m != 11) return false;
            if (toolbox::getWeekDayFromCivilDate(y,m,d) == 4) return toolbox::getFourthWeekDayOfMonth(y,m,4)==d;
            else return false;
        }

        inline bool isUSFederalReserveBusiness(const DateTime& date) {

            int m = date.getMonth(); 
            int wk = toolbox::getWeekDayFromCivilDate(date.getYear(),m,date.getDay());
            if (wk==6 or wk==0) return false; 
            if (m == 3 or m == 8 or m == 4) return true; 

            if (isChristmas(date)) return false; 
            if (isUSJuneteenth(date)) return false; 
            if (isNewYear(date)) return false; 
            if (isUSIndependanceDay(date)) return false; 
            if (isUSVeteransDay(date)) return false; 

            if (wk==1) {

                if (m==1) { if (isMartinLutterKingDay(date)) return false;}
                if (m==2) { if (isUSWashingtonBirthday(date)) return false;} 
                if (m==5) { if (isUSMemorialDay(date)) return false;} 
                if (m==9) { if (isUSLaborDay(date)) return false;} 
                if (m==10) { if (isUSColumbusDay(date)) return false;} 

            } else if (wk == 4) { if (isThanksgivingDay(date)) return false; }
            else return true;
            return true;
        }

        inline bool isBusinessDay(const DateTime& date, HolidayCalendar holidayCalendar) {

            bool result = true;
            switch (holidayCalendar) {
                case HolidayCalendar::NONE : break;
                case HolidayCalendar::WEEK_END_OFF : result = !isWeekEnd(date);break;
                case HolidayCalendar::US_FEDERAL_RESERVE: result= isUSFederalReserveBusiness(date);break;
                default: assert(false);
            }
            return result;
        }
        
        inline DateTime adjustDateFollowing(const DateTime& date, HolidayCalendar holidayCalendar) {

            DateTime newDate = date;
            while (!isBusinessDay(newDate,holidayCalendar)) { newDate += TimeDelta{1,0,0,0,0,0,0}; }
            return newDate;
        }

        inline DateTime adjustDatePreceding(const DateTime& date, HolidayCalendar holidayCalendar) {

            DateTime newDate = date;
            while (!isBusinessDay(newDate,holidayCalendar)) { newDate -= TimeDelta{1,0,0,0,0,0,0}; }
            return newDate;
        }

        inline DateTime adjustDateModPreceding(const DateTime& date, HolidayCalendar holidayCalendar) {

            DateTime modPrec = adjustDatePreceding(date, holidayCalendar); 
            if (modPrec.getMonth()== date.getMonth()) return modPrec; 
            else return adjustDateFollowing(date, holidayCalendar);
        }

        inline DateTime adjustDateModFollowing(const DateTime& date, HolidayCalendar holidayCalendar) {

            DateTime modFol = adjustDateFollowing(date, holidayCalendar); 
            if (modFol.getMonth() == date.getMonth()) return modFol; 
            else return adjustDatePreceding(date, holidayCalendar);
        }
        
        inline DateTime adjustDate(const DateTime& date, HolidayCalendar holidayCalendar, BusinessDayConvention businessDayConvention) {

            DateTime result = date;
            switch (businessDayConvention) {
                case BusinessDayConvention::FOLLOWING: result = adjustDateFollowing(date, holidayCalendar);break;
                case BusinessDayConvention::PRECEDING: result = adjustDatePreceding(date, holidayCalendar);break;
                case BusinessDayConvention::MODIFIED_FOLLOWING: result= adjustDateModFollowing(date, holidayCalendar);break;
                case BusinessDayConvention::MODIFIED_PRECEDING: result= adjustDateModPreceding(date, holidayCalendar);break;
                default: assert(false);
            }
            return result;
        }

        inline DatetimeSequence adjustDatetimeSequence(const DatetimeSequence& sequence, HolidayCalendar holidayCalendar, BusinessDayConvention businessDayConvention) {

            std::set<DateTime> initialSet = sequence.datetimeSequence; 
            std::set<DateTime> finalSet; 
            for (DateTime s : initialSet) { finalSet.insert(adjustDate(s, holidayCalendar, businessDayConvention));}
            return {finalSet};
        }
    }
}