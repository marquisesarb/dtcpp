#include <cassert>
#include <dtcpp/finance/tenor.hpp>

void testForwardDateTenor() {

    using namespace dtcpp::fin;
    using namespace dtcpp; 
    DateTime refDate(1769472000, EpochTimestampType::SECONDS);
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate,1).timestamp() == 1777248000));
    assert((Tenor{1,TenorType::DAYS}.getForwardDate(refDate,1).timestamp() == 1769558400));
    assert((Tenor{1,TenorType::WEEKS}.getForwardDate(refDate,1).timestamp() == 1770076800));
    assert((Tenor{7,TenorType::WEEKS}.getForwardDate(refDate,1).timestamp() == 1773705600));
    assert((Tenor{17,TenorType::DAYS}.getForwardDate(refDate,1).timestamp() == 1770940800));
    assert((Tenor{17,TenorType::MONTHS}.getForwardDate(refDate,1).timestamp() == 1814054400));
    assert((Tenor{3,TenorType::YEARS}.getForwardDate(refDate,1).timestamp() == 1864166400));
    assert((Tenor{18,TenorType::YEARS}.getForwardDate(refDate,1).timestamp() == 2337465600));
    DateTime refDate2(2026,1,29);
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,1) == DateTime(2026,4,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,2) == DateTime(2026,7,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,3) == DateTime(2026,10,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,4) == DateTime(2027,1,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,5) == DateTime(2027,4,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,6) == DateTime(2027,7,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,7) == DateTime(2027,10,29)));
    assert((Tenor{3,TenorType::MONTHS}.getForwardDate(refDate2,8) == DateTime(2028,1,29)));

}

void testTenorOperators() {

    using namespace dtcpp::fin;
    using namespace dtcpp; 
    assert((Tenor{7, TenorType::DAYS}==Tenor{1, TenorType::WEEKS}));
    assert((Tenor{14, TenorType::DAYS}==Tenor{2, TenorType::WEEKS}));

    assert((Tenor{15, TenorType::DAYS}>Tenor{2, TenorType::WEEKS}));
    assert((Tenor{8, TenorType::DAYS}>Tenor{1, TenorType::WEEKS}));

    assert((Tenor{1, TenorType::YEARS}<Tenor{2, TenorType::YEARS}));
    assert((Tenor{1, TenorType::YEARS}==Tenor{1, TenorType::YEARS}));

    assert((Tenor{1, TenorType::YEARS}>=Tenor{2, TenorType::MONTHS}));
    assert((Tenor{1, TenorType::YEARS}>=Tenor{1, TenorType::YEARS}));

}

void testTenorGetFactorMultiple() {

    using namespace dtcpp::fin;
    using namespace dtcpp; 
    // Months
    assert((Tenor{12,TenorType::MONTHS}.getMultiple(Tenor{3,TenorType::MONTHS}) == 4));
    assert((Tenor{12,TenorType::MONTHS}.getMultiple(Tenor{5,TenorType::MONTHS}) == 0));
    assert((Tenor{3,TenorType::MONTHS}.getMultiple(Tenor{12,TenorType::MONTHS}) == 0));
    assert((Tenor{3,TenorType::MONTHS}.getFactor(Tenor{12,TenorType::MONTHS}) == 4));
    assert((Tenor{12,TenorType::MONTHS}.getFactor(Tenor{3,TenorType::MONTHS}) == 0));
    assert((Tenor{5,TenorType::MONTHS}.getFactor(Tenor{12,TenorType::MONTHS}) == 0));

    // Days and Weeks
    assert((Tenor{14,TenorType::DAYS}.getMultiple(Tenor{1,TenorType::WEEKS}) == 2));
    assert((Tenor{17,TenorType::DAYS}.getMultiple(Tenor{1,TenorType::WEEKS}) == 0));
    assert((Tenor{4,TenorType::WEEKS}.getMultiple(Tenor{14,TenorType::DAYS}) == 2));
    assert((Tenor{1,TenorType::WEEKS}.getFactor(Tenor{14,TenorType::DAYS}) == 2));
    assert((Tenor{1,TenorType::WEEKS}.getFactor(Tenor{17,TenorType::DAYS}) == 0));
    assert((Tenor{14,TenorType::DAYS}.getFactor(Tenor{4,TenorType::WEEKS}) == 2));

    // Months and Years
    assert((Tenor{10,TenorType::YEARS}.getMultiple(Tenor{6,TenorType::MONTHS}) == 20));
    assert((Tenor{6,TenorType::MONTHS}.getMultiple(Tenor{10,TenorType::YEARS}) == 0));
    assert((Tenor{10,TenorType::YEARS}.getFactor(Tenor{6,TenorType::MONTHS}) == 0));
    assert((Tenor{6,TenorType::MONTHS}.getFactor(Tenor{10,TenorType::YEARS}) == 20));

    assert((Tenor{10,TenorType::YEARS}.getMultiple(Tenor{7,TenorType::MONTHS}) == 0));
    assert((Tenor{7,TenorType::MONTHS}.getMultiple(Tenor{10,TenorType::YEARS}) == 0));
    assert((Tenor{10,TenorType::YEARS}.getFactor(Tenor{7,TenorType::MONTHS}) == 0));
    assert((Tenor{7,TenorType::MONTHS}.getFactor(Tenor{10,TenorType::YEARS}) == 0));

}

int main() {

    testForwardDateTenor();
    testTenorOperators(); 
    testTenorGetFactorMultiple();
    return 0;


}