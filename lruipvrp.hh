#ifndef __LRUIPV_HH__
#define __LRUIPV_HH__
#include "mem/cache/replacement_policies/base.hh"
#include <string>  // Include for std::string
#include <memory>  // Include for std::shared_ptr

class LRUIPVRP : public BaseReplacementPolicy {
private:
    const int numWays;

public: 
    LRUIPVRP(const Params *p);
    void reset(const std::shared_ptr<ReplacementData>& replacementData) override;
    void touch(const std::shared_ptr<ReplacementData>& replacementData) override;
    void invalidate(const std::shared_ptr<ReplacementData>& replacementData) override;
    std::shared_ptr<ReplacementData> getVictim(const ReplacementCandidates& candidate) override;

    static const std::string type;
    static const std::string cxxClass;
};

#endif