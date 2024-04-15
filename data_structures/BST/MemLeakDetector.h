// implementation took from here:
// https://stackoverflow.com/questions/29174938/googletest-and-memory-leaks


#ifndef MEM_LEAK_DETECTOR_H_
#define MEM_LEAK_DETECTOR_H_

#include "gtest/gtest.h"
#include <crtdbg.h>


class MemoryLeakDetector {
public:
    MemoryLeakDetector() {
        _CrtMemCheckpoint(&memState_);
    }

    ~MemoryLeakDetector() {
        _CrtMemState stateNow, stateDiff;
        _CrtMemCheckpoint(&stateNow);
        int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
        if (diffResult)
            reportFailure(stateDiff.lSizes[1]);
    }
private:
    void reportFailure(unsigned int unfreedBytes) {
        FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
    }
    _CrtMemState memState_;
};



#endif
