#pragma once 
#include <dtcpp/calendars/interface.hpp>

namespace dtcpp {

    class USFederaReserveCalendar final : public BusinessCalendar {

        public:
            USFederaReserveCalendar() {};
            virtual bool isBusinessDay(const DateTime& referenceDate) const {
                int m = referenceDate.month(); 
                int wk = toolbox::getWeekDayFromCivilDate(referenceDate.year(),referenceDate.month(),referenceDate.day()); 
                if (wk==6 or wk==0) return false;
                if (m == 3 or m == 8 or m == 4) return true; 

                if (isChristmas(referenceDate)) return false; 
                if (isUSJuneteenth(referenceDate)) return false; 
                if (isNewYear(referenceDate)) return false; 
                if (isUSIndependanceDay(referenceDate)) return false; 
                if (isUSVeteransDay(referenceDate)) return false; 

                if (wk==1) {

                    if (m==1) { if (isMartinLutterKingDay(referenceDate)) return false;}
                    if (m==2) { if (isUSWashingtonBirthday(referenceDate)) return false;} 
                    if (m==5) { if (isUSMemorialDay(referenceDate)) return false;} 
                    if (m==9) { if (isUSLaborDay(referenceDate)) return false;} 
                    if (m==10) { if (isUSColumbusDay(referenceDate)) return false;} 

                } else if (wk == 4) { if (isThanksgivingDay(referenceDate)) return false; }
                else return true;
                return true;
            }; 

        private: 
            static bool isWeekEnd(const DateTime& referenceDate) {

                int wk = toolbox::getWeekDayFromCivilDate(referenceDate.year(),referenceDate.month(),referenceDate.day()); 
                return (wk==6 or wk==0) ? true : false;
            }

            static bool isChristmas(const DateTime& referenceDate) { return (referenceDate.day()==25 && referenceDate.month()==12); }

            static bool isNewYear(const DateTime& referenceDate) { return (referenceDate.day()==1 && referenceDate.month()==1); }

            static bool isMartinLutterKingDay(const DateTime& referenceDate) {

                int y = referenceDate.year(), m = referenceDate.month(), d = referenceDate.day();
                if (m != 1) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getThirdWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSWashingtonBirthday(const DateTime& referenceDate) {

                int y = referenceDate.year(), m = referenceDate.month(), d = referenceDate.day();
                if (m != 2) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getThirdWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSMemorialDay(const DateTime& referenceDate) {

                int y = referenceDate.year(), m = referenceDate.month(), d = referenceDate.day();
                if (m != 5) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getLastWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSJuneteenth(const DateTime& referenceDate) {return (referenceDate.day()==19 && referenceDate.month()==6);}

            static bool isUSIndependanceDay(const DateTime& referenceDate) {return (referenceDate.day()==4 && referenceDate.month()==7);}

            static bool isUSLaborDay(const DateTime& referenceDate) {

                int y = referenceDate.year(), m = referenceDate.month(), d = referenceDate.day();
                if (m != 9) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getFirstWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSColumbusDay(const DateTime& referenceDate) {

                int y = referenceDate.year(), m = referenceDate.month(), d = referenceDate.day();
                if (m != 10) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getSecondWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSVeteransDay(const DateTime& referenceDate) {return (referenceDate.day()==11 && referenceDate.month()==11);}

            static bool isThanksgivingDay(const DateTime& referenceDate) {

                int y = referenceDate.year(), m = referenceDate.month(), d = referenceDate.day();
                if (m != 11) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 4) return toolbox::getFourthWeekDayOfMonth(y,m,4)==d;
                else return false;
            }
    };

}