#include <cassert>
#include <dtcpp/timeserie.hpp>

dtcpp::TimeSerie<double> getTimeSerie() {

    std::vector<long long> timestamps = {
        1783238400000,1783260000000,1783281600000,1783303200000,1783324800000,1783346400000,
        1783368000000,1783389600000,1783411200000,1783432800000,1783454400000,1783476000000,
        1783497600000,1783519200000,1783540800000,1783562400000,1783584000000,1783605600000,
        1783627200000,1783648800000,1783670400000,1783692000000,1783713600000,1783735200000,
        1783756800000,1783778400000,1783800000000,1783821600000,1783843200000,1783864800000,
        1783886400000,1783908000000,1783929600000,1783951200000,1783972800000,1783994400000,
        1784016000000,1784037600000,1784059200000,1784080800000,1784102400000
    }; 

    std::vector<double> values = {

        62754.5,62743.5,63537.0,63053.0,61748.0,63707.0,
        63808.5,63049.5,63005.5,63790.0,63018.0,62856.5,
        61904.5,62244.5,61872.0,62979.5,62987.0,63212.5,
        63720.0,63958.5,64468.5,63908.0,63997.5,64150.5,
        64227.0,64268.0,64100.0,63871.5,64011.0,64216.0,
        63407.5,62964.5,62298.5,62240.0,62480.0,62484.5,
        63797.5,64537.5,64667.5,64542.5,65334.5
    };

    dtcpp::TimeSerie<double> ts = dtcpp::TimeSerie<double>();

    for (size_t i = 0; i<values.size();i++) {

        ts.insert(dtcpp::DateTime(timestamps[i],dtcpp::EpochTimestampType::MILLISECONDS), values[i]);
    }

    return ts; 

}

int main() {

    dtcpp::TimeSerie<double> ts = getTimeSerie();

    assert(ts[15].first.timestamp() == 1783562400000);
    assert(ts[15].second == 62979.5);

    dtcpp::TimeSerie<double> seg = ts.segment(10, 5); 

    assert(seg.size()==5);

    assert(seg[0].first.timestamp() == 1783454400000);
    assert(seg[0].second == 63018);

    assert(seg[1].first.timestamp() == 1783476000000);
    assert(seg[1].second == 62856.5);

    assert(seg[2].first.timestamp() == 1783497600000);
    assert(seg[2].second == 61904.5);

    assert(seg[3].first.timestamp() == 1783519200000);
    assert(seg[3].second == 62244.5);

    assert(seg[4].first.timestamp() == 1783540800000);
    assert(seg[4].second == 61872);


    seg.popBack();

    assert(seg.size()==4);
    assert(seg.back().first.timestamp() == 1783519200000);
    assert(seg.back().second == 62244.5);


    seg.insert(dtcpp::DateTime(1783540800000,dtcpp::EpochTimestampType::MILLISECONDS),61872); 

    assert(seg.back().first.timestamp() == 1783540800000);
    assert(seg.back().second == 61872);
    assert(seg.size()==5);

    long long tmsp = .5*(1783454400000+1783476000000);
    seg.insert(dtcpp::DateTime(tmsp,dtcpp::EpochTimestampType::MILLISECONDS),.5*(63018+62856.5));

    assert(seg[1].first.timestamp() == tmsp);
    assert(seg[1].second == .5*(63018+62856.5));
    assert(seg.size()==6);


    return 0;
    
}
