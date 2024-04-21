#include "mem/cache/replacement_policies/lru.ipv.hh"
#include "mem/cache/replacement_policies/replacement_data.hh"
#include <cassert>
#include <algorithm>
#include <memory> // Ensure this is included for std::shared_ptr

const std::string LRUIPVRP::type = "LRUIPVRP";
const std::string LRUIPVRP::cxxClass = "gem5::LRUIPVRP";

LRUIPVRP::LRUIPVRP(const Params *p) : BaseReplacementPolicy(p), numWays(p->numWays) {
    ipv.resize(numWays);
    std::fill(ipv.begin(), ipv.end(), 0);
}

void LRUIPVRP::reset(const std::shared_ptr<ReplacementData>& replacementData) {
    auto data = std::static_pointer_cast<LRUReplData>(replacementData);
    data->lastTouchTick = curTick();
    data->ipvIndex = 0;
}

void LRUIPVRP::touch(const std::shared_ptr<ReplacementData>& replacementData) {
    auto data = std::static_pointer_cast<LRUReplData>(replacementData);
    data->lastTouchTick = curTick();
    if (data->ipvIndex < ipv.size() - 1) {
        data->ipvIndex++;
    }
}

void LRUIPVRP::invalidate(const std::shared_ptr<ReplacementData>& replacementData) {
    auto data = std::static_pointer_cast<LRUReplData>(replacementData);
    data->ipvIndex = 0; 
}

std::shared_ptr<ReplacementData> LRUIPVRP::getVictim(const ReplacementCandidates& candidates) {
    assert(!candidates.empty());

    auto victim = std::min_element(candidates.begin(), candidates.end(),
        [](const std::shared_ptr<ReplacementData>& a, const std::shared_ptr<ReplacementData>& b) {
            return std::static_pointer_cast<LRUReplData>(a)->ipvIndex < std::static_pointer_cast<LRUReplData>(b)->ipvIndex;
        });

    if (victim != candidates.end()) {
        return *victim;
    }
    return nullptr;
}