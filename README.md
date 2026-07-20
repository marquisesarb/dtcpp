# DTCPP

DTCPP is a date/time C++17 library buit from inspirations to the python library datetime. The goal of this library is to make accessible time representation and its arithmetics. 

## Time delta

The TimeDelta object (implemented [here](include/dtcpp/timedelta.hpp)) represents a time period. It can be constructed from a number: 
- days 
- hours 
- minutes 
- seconds 
- milliseconds 
- microseconds 
- nanoseconds 

```cpp 

int main() {
    // Representing of a time delta of 1 day, 2 hours, 3 minutes, 4 seconds, 500 milliseconds, 600 microseconds and 700 nanoseconds
    dtcpp::TimeDelta delta = {1, 2, 3, 4, 500, 600, 700}; 

    std::cout << delta.totalSeconds() << std::endl;
    // 93784

    std::cout << delta.totalMilliseconds() << std::endl;
    // 93784500; 

    std::cout << delta.totalMicroseconds() << std::endl;
    // 93784500600

    std::cout << delta.totalNanoseconds() << std::endl;;
    // 93784500600700
}


```

## Datetime 

The main object DateTime (implemented [here](include/dtcpp/datetime.hpp)) 


## Time Sequence 

Implementation of a time sequence representing an array of unique DateTime objects which are kept ordered. The choice of keeping the sequence as an array is: 

- Indexing is $O(1)$ for ooping through all dates 
- Push back a date which is known to be greater that any existing date within the sequence is $O(1)$ using std::vector::push_back
- Inserting a date is reduced to $O(log n)$ with binary search 
- pop back is $O(1)$ using std::vector::pop_back 
- segment the sequence is $O(n)$
