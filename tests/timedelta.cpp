#include <cassert>
#include <dtcpp/timedelta.hpp>


int main() {
    dtcpp::TimeDelta delta = {1, 2, 3, 4, 500, 600, 700}; 

    long long totalSeconds = delta.totalSeconds();
    assert(totalSeconds == 93784); 

    long long totalMilliSeconds = delta.totalMilliseconds();
    assert(totalMilliSeconds == 93784500); 

    long long totalMicroSeconds = delta.totalMicroseconds();
    assert(totalMicroSeconds == 93784500600); 

    long long totalNanoSeconds = delta.totalNanoseconds();
    assert(totalNanoSeconds == 93784500600700);

    delta = {0, 0, 0, 10, 0, 0, 0}; 

    assert(delta.totalSeconds() == 10);
    assert(delta.totalMilliseconds() == 10000);
    assert(delta.totalMicroseconds() == 10000000);
    assert(delta.totalNanoseconds() == 10000000000);

}
