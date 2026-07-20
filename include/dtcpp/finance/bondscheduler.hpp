#pragma once 
#include "dtcpp/datetime.hpp"
#include <dtcpp/sequence.hpp>
#include <dtcpp/finance/tenor.hpp>
#include <dtcpp/calendars/interface.hpp>

namespace dtcpp::fin {


    class BondScheduler: public TimeSequence {

        public: 
            dtcpp::DateTime startDate; 
            Tenor frequencyTenor; 
            Tenor maturityTenor; 
            BusinessDayConvention businessDayConvention; 
            std::shared_ptr<BusinessCalendar> businessCalendarPtr; 

            BondScheduler(
                const dtcpp::DateTime& startDate_, 
                Tenor frequencyTenor_, 
                Tenor maturityTenor_,
                BusinessDayConvention businessDayConvention_,
                const std::shared_ptr<BusinessCalendar>& businessCalendarPtr_): 
            TimeSequence(), startDate(startDate_), frequencyTenor(frequencyTenor_), maturityTenor(maturityTenor_), 
            businessDayConvention(businessDayConvention_), businessCalendarPtr(businessCalendarPtr_) {

                int n = maturityTenor.getMultiple(frequencyTenor); 

                for (int i = 0; i<n-1; i++) {

                    DateTime unadjustedDate = frequencyTenor.getForwardDate(startDate, i+1);
                    insert(businessCalendarPtr->adjustForBusiness(unadjustedDate, businessDayConvention));
                }
            }

            dtcpp::DateTime maturityDate() const {return businessCalendarPtr->adjustForBusiness(maturityTenor.getForwardDate(startDate, 1), businessDayConvention);}

            

    };

}