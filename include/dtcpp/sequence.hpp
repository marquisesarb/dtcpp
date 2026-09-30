#pragma once
#include <dtcpp/datetime.hpp>
#include <vector>

namespace dtcpp {

    class TimeSequence {

        public: 

            TimeSequence(){};

            virtual ~TimeSequence() = default;

            dtcpp::DateTime operator[](size_t i) const {return seq[i];}

            dtcpp::DateTime back() const {return seq.back();}

            dtcpp::DateTime front() const {return seq.front();}

            size_t size() const {return seq.size();}

            bool empty() const {return seq.empty();}

            bool contains(const dtcpp::DateTime& date) {return (std::find(seq.begin(), seq.end(), date) != seq.end());}

            void insert(const dtcpp::DateTime& date) {

                //if (seq.empty()) seq.push_back(date);
                //else {
                //    if (date < seq.front()) {seq.insert(seq.begin(), date);}
                //    else if (date > seq.back()) {seq.push_back(date);}
                //    else {
                //        auto it = std::lower_bound(seq.begin(), seq.end(), date);
                //        size_t i = it - seq.begin();
                //        if (date != seq[i]) {

                //            seq.insert(seq.begin() + i, date);
                //        }
                //    }
                //}

                auto it = std::lower_bound(seq.begin(), seq.end(), date);
                if (!seq.empty() && date != *it) {

                    seq.insert(it, date);

                } else if (seq.empty()) {

                    seq.push_back(date);
                }
                
            }

            void erase(size_t i) {seq.erase(seq.begin()+i);}

            void erase(const dtcpp::DateTime& date) {size_t i = index(date); if (i!=-1) erase(i);}

            void popBack() {seq.pop_back();}

            TimeSequence segment(size_t startIndex, size_t n) const {

                TimeSequence newts = TimeSequence();
                for (size_t i = startIndex; i<startIndex+n; i++) {

                    newts.insert(seq[i]);
                }
                return newts;
            }

            TimeSequence segment(const dtcpp::DateTime& startDate, size_t n) const {

                return segment(index(startDate),n);
            }

            TimeSequence segment(const dtcpp::DateTime& startDate, const dtcpp::DateTime& endDate) const {

                size_t istart = index(startDate); 
                TimeSequence newts = TimeSequence(); 
                for (size_t i = istart; i<seq.size(); i++) {

                    if (seq[i]<=endDate) newts.insert(seq[i]);
                    else break;
                }
                return newts;

            }

            size_t index(const dtcpp::DateTime& date) const {

                auto it = std::lower_bound(seq.begin(), seq.end(), date);
                size_t i = it - seq.begin();
                return (seq[i] == date) ? i : -1;
            }

            dtcpp::DateTime next(const dtcpp::DateTime& date) const {

                auto it = std::lower_bound(seq.begin(), seq.end(), date);
                size_t i = it - seq.begin();
                return (seq[i] == date) ? seq[i+1] : seq[i];
            }

            dtcpp::DateTime prev(const dtcpp::DateTime& date) const {

                auto it = std::lower_bound(seq.begin(), seq.end(), date);
                size_t i = it - seq.begin();
                return seq[i-1];
            }

            std::pair<TimeDelta,TimeDelta> minMaxTimeDelta() const {

                TimeDelta dtmax{}; 
                TimeDelta dtmin{};
                
                for (size_t i = 1; i<size();i++) {

                    dtmax = (i==1) ? seq[i]-seq[i-1] : std::max(dtmax,seq[i]-seq[i-1]);
                    dtmin = (i==1) ? seq[i]-seq[i-1] : std::min(dtmin,seq[i]-seq[i-1]);

                }

                return std::make_pair(dtmin,dtmax);

            }

        protected: 
            std::vector<dtcpp::DateTime> seq; 
    };

}