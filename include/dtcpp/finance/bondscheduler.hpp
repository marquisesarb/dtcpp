#pragma once 
#include "dtcpp/datetime.hpp"
#include <dtcpp/sequence.hpp>
#include <dtcpp/finance/tenor.hpp>
#include <dtcpp/calendars/interface.hpp>

namespace dtcpp::fin {


    class BondScheduler: public TimeSequence {

        public: 
            BondScheduler(
                const DateTime& startDate_, 
                Tenor frequencyTenor_, 
                Tenor maturityTenor_,
                BusinessDayConvention businessDayConvention_,
                const std::shared_ptr<BusinessCalendar>& businessCalendarPtr_): 
            TimeSequence(), _startDate(startDate_), _frequencyTenor(frequencyTenor_), _maturityTenor(maturityTenor_), 
            _businessDayConvention(businessDayConvention_), _businessCalendarPtr(businessCalendarPtr_) {

                int n = _maturityTenor.getMultiple(_frequencyTenor); 

                for (int i = 0; i<n-1; i++) {

                    DateTime unadjustedDate = _frequencyTenor.getForwardDate(_startDate, i+1);
                    insert(_businessCalendarPtr->adjustForBusiness(unadjustedDate, _businessDayConvention));
                }
            }

            DateTime maturityDate() const {return _businessCalendarPtr->adjustForBusiness(_maturityTenor.getForwardDate(_startDate, 1), _businessDayConvention);}
            DateTime startDate() const {return _startDate;}
            Tenor frequencyTenor() const {return _frequencyTenor;}
            Tenor maturityTenor() const {return _maturityTenor;}
            BusinessDayConvention businessDayConvention() const {return _businessDayConvention;}
            std::shared_ptr<BusinessCalendar> businessCalendarPtr() const {return _businessCalendarPtr;}

        private:
            DateTime _startDate; 
            Tenor _frequencyTenor; 
            Tenor _maturityTenor; 
            BusinessDayConvention _businessDayConvention; 
            std::shared_ptr<BusinessCalendar> _businessCalendarPtr; 

    };

}