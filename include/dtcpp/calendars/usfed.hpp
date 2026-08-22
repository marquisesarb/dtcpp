#pragma once 
#include <dtcpp/calendars/interface.hpp>

namespace dtcpp {

    class USFederaReserveCalendar final : public BusinessCalendar {

        public:
            USFederaReserveCalendar() {};
            virtual bool isBusinessDay(const DateTime& referenceDate) const {
                std::tuple<int,int,int,int,int,int> civilTime_ = referenceDate.civilTime();
                int y = std::get<0>(civilTime_), m = std::get<1>(civilTime_),d = std::get<2>(civilTime_);
                int wk = toolbox::getWeekDayFromCivilDate(y,m,d); 
                if (wk==6 or wk==0) return false;
                if (m == 3 or m == 8 or m == 4) return true; 

                if (isChristmas(m,d)) return false; 
                if (isUSJuneteenth(m,d)) return false; 
                if (isNewYear(m,d)) return false; 
                if (isUSIndependanceDay(m,d)) return false; 
                if (isUSVeteransDay(m,d)) return false; 

                if (wk==1) {

                    if (m==1) { if (isMartinLutterKingDay(y,m,d)) return false;}
                    if (m==2) { if (isUSWashingtonBirthday(y,m,d)) return false;} 
                    if (m==5) { if (isUSMemorialDay(y,m,d)) return false;} 
                    if (m==9) { if (isUSLaborDay(y,m,d)) return false;} 
                    if (m==10) { if (isUSColumbusDay(y,m,d)) return false;} 

                } else if (wk == 4) { if (isThanksgivingDay(y,m,d)) return false; }
                else return true;
                return true;
            }; 

        private: 

            static bool isChristmas(int m, int d) { return (d==25 && m==12); }

            static bool isNewYear(int m, int d) { return (d==1 && m==1); }

            static bool isMartinLutterKingDay(int y, int m, int d) {

                if (m != 1) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getThirdWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSWashingtonBirthday(int y, int m, int d) {

                if (m != 2) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getThirdWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSMemorialDay(int y, int m, int d) {

                if (m != 5) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getLastWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSJuneteenth(int m, int d) {return (d==19 && m==6);}

            static bool isUSIndependanceDay(int m, int d) {return (d==4 && m==7);}

            static bool isUSLaborDay(int y, int m, int d) {

                if (m != 9) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getFirstWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSColumbusDay(int y, int m, int d) {

                if (m != 10) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 1) return toolbox::getSecondWeekDayOfMonth(y,m,1)==d;
                else return false;
            }

            static bool isUSVeteransDay(int m, int d) {return (d==11 && m==11);}

            static bool isThanksgivingDay(int y, int m, int d) {

                if (m != 11) return false;
                if (toolbox::getWeekDayFromCivilDate(y,m,d) == 4) return toolbox::getFourthWeekDayOfMonth(y,m,4)==d;
                else return false;
            }
    };

}