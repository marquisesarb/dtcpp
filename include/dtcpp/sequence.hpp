#pragma once
#include <dtcpp/datetime.hpp>
#include <vector>
#include <set>

namespace dtcpp {


    class TimeSequence {

        public: 

            TimeSequence(){};

            TimeSequence(const std::vector<dtcpp::DateTime>& sequence) {

                seq = std::vector<dtcpp::DateTime>(sequence.size());

                for (const dtcpp::DateTime& d: sequence) {
                    insert(d);
                }

            };

            TimeSequence(const std::set<dtcpp::DateTime>& sequence) {

                for(const dtcpp::DateTime& d: sequence) {insert(d);}   
            }

            virtual ~TimeSequence() = default;

            dtcpp::DateTime operator[](size_t i) const {return seq[i];}
            dtcpp::DateTime back() const {return seq.back();}
            dtcpp::DateTime front() const {return seq.front();}
            size_t size() const {return seq.size();}
            bool isEmpty() const {return seq.empty();}
            bool contains(const dtcpp::DateTime& date) {return (std::find(seq.begin(), seq.end(), date) != seq.end());}

            void insert(const dtcpp::DateTime& date) {

                if (seq.empty()) seq.push_back(date);
                else {
                    if (date < seq.front()) {seq.insert(seq.begin(), date);}
                    else if (date > seq.back()) {seq.push_back(date);}
                    else {
                        auto it = std::lower_bound(seq.begin(), seq.end(), date);
                        size_t i = it - seq.begin();
                        if (date != seq[i]) {

                            seq.insert(seq.begin() + i, date);
                        }
                    }
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
                size_t iend = index(endDate);
                return segment(istart, iend-istart+1);
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

        private: 
            std::vector<dtcpp::DateTime> seq; 
    };

}