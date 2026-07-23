#pragma once
#include <dtcpp/datetime.hpp>
#include <vector>
#include <utility>
#include <map>

namespace dtcpp {

    template <typename T>
    class TimeSerie {

        public: 
            TimeSerie() {}; 

            TimeSerie(const std::map<dtcpp::DateTime,T>& points) {

                for (const auto [k,v]: points) {

                    insert(k,v);
                }
            }

            std::pair<DateTime, T> operator[](size_t i) const {return std::make_pair(dateSeq[i], dataSeq[i]);}
            std::pair<DateTime, T> back() const {return std::make_pair(dateSeq.back(), dataSeq.back());}
            std::pair<DateTime, T> front() const {return std::make_pair(dateSeq.front(), dataSeq.front());}
            size_t size() const {return dateSeq.size();}
            bool isEmpty() const {return dateSeq.empty();}
            bool contains(const dtcpp::DateTime& date) {return (std::find(dateSeq.begin(), dateSeq.end(), date) != dateSeq.end());}

            size_t index(const dtcpp::DateTime& date) const {

                auto it = std::lower_bound(dateSeq.begin(), dateSeq.end(), date);
                size_t i = it - dateSeq.begin();
                return (dateSeq[i] == date) ? i : -1;
            }

            std::pair<dtcpp::DateTime, T> next(const dtcpp::DateTime& date) const {

                auto it = std::lower_bound(dateSeq.begin(), dateSeq.end(), date);
                size_t i = it - dateSeq.begin();
                return (dateSeq[i] == date) ? std::make_pair(dateSeq[i+1],dataSeq[i+1]) : std::make_pair(dateSeq[i],dataSeq[i]);
            }

            std::pair<dtcpp::DateTime, T> prev(const dtcpp::DateTime& date) const {

                auto it = std::lower_bound(dateSeq.begin(), dateSeq.end(), date);
                size_t i = it - dateSeq.begin();
                return std::make_pair(dateSeq[i-1],dataSeq[i-1]);
            }

            void popBack() {dateSeq.pop_back();dataSeq.pop_back();}
            void erase(size_t i) {dateSeq.erase(dateSeq.begin()+i); dataSeq.erase(dataSeq.begin()+i);}
            void erase(const dtcpp::DateTime& date) {size_t i = index(date); if (i!=-1) erase(i);}

            void insert(const std::pair<dtcpp::DateTime, T>& point) {

                if (dateSeq.empty()) {dateSeq.push_back(point.first); dataSeq.push_back(point.second);}
                else {
                    if (point.first < dateSeq.front()) {dateSeq.insert(dateSeq.begin(), point.first); dataSeq.insert(dataSeq.begin(),point.second);}
                    else if (point.first > dateSeq.back()) {dateSeq.push_back(point.first); dataSeq.push_back(point.second);}
                    else {
                        auto it = std::lower_bound(dateSeq.begin(), dateSeq.end(), point.first);
                        size_t i = it - dateSeq.begin();
                        if (point.first != dateSeq[i]) {

                            dateSeq.insert(dateSeq.begin() + i, point.first);
                            dataSeq.insert(dataSeq.begin() + i, point.second);
                        }
                    }
                }
                
            }

            void insert(const dtcpp::DateTime& datePoint, const T& dataPoint) {

                insert(std::make_pair(datePoint,dataPoint));
            }

            TimeSerie<T> segment(size_t startIndex, size_t n) const {

                TimeSerie<T> newts = TimeSerie<T>();
                for (size_t i = startIndex; i<startIndex+n; i++) {

                    newts.insert(std::make_pair(dateSeq[i], dataSeq[i]));
                }
                return newts;
            }

            TimeSerie<T> segment(const dtcpp::DateTime& startDate, size_t n) const {

                return segment(index(startDate),n);
            }

            TimeSerie<T> segment(const dtcpp::DateTime& startDate, const dtcpp::DateTime& endDate) const {

                size_t istart = index(startDate); 
                size_t iend = index(endDate);
                return segment(istart, iend-istart+1);
            }

            std::pair<TimeDelta,TimeDelta> minMaxTimeDelta() const {

                TimeDelta dtmax{}; 
                TimeDelta dtmin{};
                
                for (size_t i = 0; i<size();i++) {

                    if (i==0) {

                        continue; 

                    } else if (i==1) {

                        dtmax = dateSeq[i]-dateSeq[i-1];
                        dtmin = dateSeq[i]-dateSeq[i-1];

                    } else {

                        dtmax = std::max(dtmax,dateSeq[i]-dateSeq[i-1]);
                        dtmin = std::min(dtmin,dateSeq[i]-dateSeq[i-1]);

                    }
                }

                return std::make_pair(dtmin,dtmax);

            }

        private: 
            std::vector<dtcpp::DateTime> dateSeq; 
            std::vector<T> dataSeq; 

    };
}