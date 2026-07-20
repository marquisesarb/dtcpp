#include <vector>
#include <cassert>
#include <dtcpp/sequence.hpp>

dtcpp::TimeSequence getTimeSequence() {

    
    std::set<int> timestampsVector = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824854400,
        1840665600, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982707200,
        1998432000, 2014243200, 2029968000, 2045779200, 2061504000,
        2077315200
    };

    dtcpp::TimeSequence sequence = dtcpp::TimeSequence();
    for (int t: timestampsVector){sequence.insert(dtcpp::DateTime(t,dtcpp::EpochTimestampType::SECONDS));}
    return sequence;
}

void testBasicsTimeSequence() {

    dtcpp::TimeSequence seq = getTimeSequence(); 

    assert(seq.contains(dtcpp::DateTime(1761868800,dtcpp::EpochTimestampType::SECONDS)));
    assert(seq.contains(dtcpp::DateTime(1966896000,dtcpp::EpochTimestampType::SECONDS)));
    assert(!seq.contains(dtcpp::DateTime(1976896000,dtcpp::EpochTimestampType::SECONDS)));

    assert(seq.size()==21); 

    assert(seq.index(dtcpp::DateTime(1761868800,dtcpp::EpochTimestampType::SECONDS)) == 0);
    assert(seq.index(dtcpp::DateTime(1966896000,dtcpp::EpochTimestampType::SECONDS)) == 13);
    assert(seq.index(dtcpp::DateTime(1976896000,dtcpp::EpochTimestampType::SECONDS)) == -1);

    assert(seq.front() == dtcpp::DateTime(1761868800,dtcpp::EpochTimestampType::SECONDS));
    assert(seq.back() == dtcpp::DateTime(2077315200,dtcpp::EpochTimestampType::SECONDS));

}

void testAddRemoveDateTimeSequence() {

    dtcpp::TimeSequence sequence = getTimeSequence(); 

    dtcpp::DateTime newDt = dtcpp::DateTime(1761868800, dtcpp::EpochTimestampType::SECONDS)-dtcpp::TimeDelta{1,0,0,0,0,0,0};
    sequence.insert(newDt);
    assert(sequence.contains(newDt)==true); 
    assert(sequence.front()==newDt); 
    sequence.erase(newDt);
    assert(sequence.contains(newDt)==false); 
    assert(sequence.front()==dtcpp::DateTime(1761868800,dtcpp::EpochTimestampType::SECONDS)); 

    newDt = dtcpp::DateTime(2077315200, dtcpp::EpochTimestampType::SECONDS)+dtcpp::TimeDelta{1,0,0,0,0,0,0};
    sequence.insert(newDt);
    assert(sequence.contains(newDt)==true); 
    assert(sequence.back()==newDt); 
    sequence.erase(newDt);
    assert(sequence.contains(newDt)==false); 
    assert(sequence.back()==dtcpp::DateTime(2077315200,dtcpp::EpochTimestampType::SECONDS)); 

    newDt = dtcpp::DateTime(1761868800, dtcpp::EpochTimestampType::SECONDS)+dtcpp::TimeDelta{1,0,0,0,0,0,0};
    sequence.insert(newDt);
    assert(sequence.contains(newDt)==true); 
    assert(sequence.index(newDt)==1); 
    sequence.erase(newDt);
    assert(sequence.contains(newDt)==false); 
    assert(sequence.index(dtcpp::DateTime(1777507200,dtcpp::EpochTimestampType::SECONDS))==1); 

    newDt = dtcpp::DateTime(2077315200, dtcpp::EpochTimestampType::SECONDS)-dtcpp::TimeDelta{1,0,0,0,0,0,0};
    sequence.insert(newDt);
    assert(sequence.contains(newDt)==true); 
    assert(sequence.index(newDt)==20); 
    sequence.erase(newDt);
    assert(sequence.contains(newDt)==false); 
    assert(sequence.index(dtcpp::DateTime(2061504000,dtcpp::EpochTimestampType::SECONDS))==19); 
}

void testNextPreviousDateTimeSequence() {

   dtcpp::TimeSequence sequence = getTimeSequence(); 

    // 1) first datetime of the sequence 
    dtcpp::DateTime referenceDt = dtcpp::DateTime(1761868800, dtcpp::EpochTimestampType::SECONDS);
    assert(sequence.next(referenceDt) == dtcpp::DateTime(1777507200, dtcpp::EpochTimestampType::SECONDS));

    // 2) after last datetime of the sequence 
    referenceDt = dtcpp::DateTime(2077315200, dtcpp::EpochTimestampType::SECONDS) + dtcpp::TimeDelta{1,0,0,0,0,0,0};
    assert(sequence.prev(referenceDt) == dtcpp::DateTime(2077315200, dtcpp::EpochTimestampType::SECONDS));

    // 3) before first datetime of the sequence 
    referenceDt = dtcpp::DateTime(1761868800, dtcpp::EpochTimestampType::SECONDS) - dtcpp::TimeDelta{1,0,0,0,0,0,0};
    assert(sequence.next(referenceDt) == dtcpp::DateTime(1761868800, dtcpp::EpochTimestampType::SECONDS));

    // 4) Non-existing datetime in-bewteen
    int intermTimestamp = 1958084800;
    referenceDt = dtcpp::DateTime(intermTimestamp, dtcpp::EpochTimestampType::SECONDS);
    assert(sequence.next(referenceDt) == dtcpp::DateTime(1966896000, dtcpp::EpochTimestampType::SECONDS));
    assert(sequence.prev(referenceDt) == dtcpp::DateTime(1951084800, dtcpp::EpochTimestampType::SECONDS));

    // 5) Exact datetime in-bewteen
    referenceDt = dtcpp::DateTime(1951084800, dtcpp::EpochTimestampType::SECONDS);
    assert(sequence.next(referenceDt) == dtcpp::DateTime(1966896000, dtcpp::EpochTimestampType::SECONDS));
    assert(sequence.prev(referenceDt) == dtcpp::DateTime(1935273600, dtcpp::EpochTimestampType::SECONDS));

    // 6) last datetime of the sequence 
    referenceDt = dtcpp::DateTime(2077315200, dtcpp::EpochTimestampType::SECONDS);
    assert(sequence.prev(referenceDt) ==dtcpp:: DateTime(2061504000, dtcpp::EpochTimestampType::SECONDS));
}

void testTemplateSubDateTimeSequence(const std::vector<dtcpp::DateTime>& test, const dtcpp::TimeSequence& seq) {

    assert(seq.size() == test.size());

    for (size_t i = 0; i<test.size(); i++) {

        assert(test[i]==seq[i]);
    }


}

void testSubDateTimeSeq() {

    dtcpp::TimeSequence sequence = getTimeSequence(); 

    dtcpp::TimeSequence subSeq1 = sequence.segment(1,3); 
    std::vector<dtcpp::DateTime> subSeqTest1 = {
        dtcpp::DateTime(1777507200, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1793318400, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1809043200, dtcpp::EpochTimestampType::SECONDS)
    };

    testTemplateSubDateTimeSequence(subSeqTest1,subSeq1);

    
    dtcpp::TimeSequence subSeq2 = sequence.segment(dtcpp::DateTime(1919548800, dtcpp::EpochTimestampType::SECONDS),dtcpp::DateTime(1982707200, dtcpp::EpochTimestampType::SECONDS)); 
    std::vector<dtcpp::DateTime> subSeqTest2 = {
        dtcpp::DateTime(1919548800, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1935273600, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1951084800, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1966896000, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1982707200, dtcpp::EpochTimestampType::SECONDS)
    };
    testTemplateSubDateTimeSequence(subSeqTest2,subSeq2);


    dtcpp::TimeSequence subSeq3 = sequence.segment(dtcpp::DateTime(1919548800, dtcpp::EpochTimestampType::SECONDS),5); 
    std::vector<dtcpp::DateTime> subSeqTest3 = {
        dtcpp::DateTime(1919548800, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1935273600, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1951084800, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1966896000, dtcpp::EpochTimestampType::SECONDS), 
        dtcpp::DateTime(1982707200, dtcpp::EpochTimestampType::SECONDS)
    };
    testTemplateSubDateTimeSequence(subSeqTest3,subSeq3);

    dtcpp::TimeSequence subSeq4 = sequence.segment(dtcpp::DateTime(1982707200, dtcpp::EpochTimestampType::SECONDS),dtcpp::DateTime(1919548800, dtcpp::EpochTimestampType::SECONDS)); 
    assert(subSeq4.size() == 0);
}


int main() {

    testBasicsTimeSequence(); 
    testAddRemoveDateTimeSequence();
    testNextPreviousDateTimeSequence(); 
    testSubDateTimeSeq();
    return 0; 
}