#include <cassert>
#include <dtcpp/timedelta.hpp>


int main() {
    dtcpp::TimeDelta delta = {1, 2, 3, 4, 500, 600, 700}; 

    long long totalNanoSeconds = delta.totalNanoseconds();
    assert(totalNanoSeconds == 93784500600700);

    delta = {0, 0, 0, 10, 0, 0, 0}; 

    assert(delta.totalNanoseconds() == 10000000000);

}
