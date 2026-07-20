#include <cassert>
#include <dtcpp/calendars/usfed.hpp>

void templateTestUSFederalCalendar(dtcpp::DateTime refDate, dtcpp::DateTime follow, dtcpp::DateTime preceding, dtcpp::DateTime modFollow, dtcpp::DateTime modPrec) {

    dtcpp::USFederaReserveCalendar calendar = dtcpp::USFederaReserveCalendar();
    assert(calendar.isBusinessDay(refDate)==false);
    assert(calendar.adjustForBusiness(refDate,dtcpp::BusinessDayConvention::FOLLOWING) == follow);
    assert(calendar.adjustForBusiness(refDate ,dtcpp::BusinessDayConvention::PRECEDING) == preceding);
    assert(calendar.adjustForBusiness(refDate, dtcpp::BusinessDayConvention::MODIFIED_FOLLOWING) == modFollow);
    assert(calendar.adjustForBusiness(refDate, dtcpp::BusinessDayConvention::MODIFIED_PRECEDING) == modPrec);
}

int main() {

    // New year
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,1,1), dtcpp::DateTime(2024,1,2), dtcpp::DateTime(2023,12,29), dtcpp::DateTime(2024,1,2), dtcpp::DateTime(2024,1,2));
    // MLK
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,1,15), dtcpp::DateTime(2024,1,16), dtcpp::DateTime(2024,1,12), dtcpp::DateTime(2024,1,16), dtcpp::DateTime(2024,1,12));
    // Washington Birthday
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,2,19), dtcpp::DateTime(2024,2,20), dtcpp::DateTime(2024,2,16), dtcpp::DateTime(2024,2,20), dtcpp::DateTime(2024,2,16));
    // Memorial 
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,5,27), dtcpp::DateTime(2024,5,28), dtcpp::DateTime(2024,5,24), dtcpp::DateTime(2024,5,28), dtcpp::DateTime(2024,5,24));
    // Juneteeth
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,6,19), dtcpp::DateTime(2024,6,20), dtcpp::DateTime(2024,6,18), dtcpp::DateTime(2024,6,20), dtcpp::DateTime(2024,6,18));
    // Independance Day
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,7,4), dtcpp::DateTime(2024,7,5), dtcpp::DateTime(2024,7,3), dtcpp::DateTime(2024,7,5), dtcpp::DateTime(2024,7,3));
    // Labor day 
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,9,2), dtcpp::DateTime(2024,9,3), dtcpp::DateTime(2024,8,30), dtcpp::DateTime(2024,9,3), dtcpp::DateTime(2024,9,3));
    // Columbus day 
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,10,14), dtcpp::DateTime(2024,10,15), dtcpp::DateTime(2024,10,11), dtcpp::DateTime(2024,10,15), dtcpp::DateTime(2024,10,11));
    // Veterans Day
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,11,11), dtcpp::DateTime(2024,11,12), dtcpp::DateTime(2024,11,8), dtcpp::DateTime(2024,11,12), dtcpp::DateTime(2024,11,8));
    // Thanksgiving 
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,11,28), dtcpp::DateTime(2024,11,29), dtcpp::DateTime(2024,11,27), dtcpp::DateTime(2024,11,29), dtcpp::DateTime(2024,11,27));
    // Christmas 
    templateTestUSFederalCalendar(dtcpp::DateTime(2024,12,25), dtcpp::DateTime(2024,12,26), dtcpp::DateTime(2024,12,24), dtcpp::DateTime(2024,12,26), dtcpp::DateTime(2024,12,24));

    return 0;
}