#include "common.h"

namespace {

const int ALP_SIZE = 128;
const int QUICK_SORT_THRESHOLD = 74;

std::random_device rd;
}  // namespace

std::vector<std::string> MsdRadixQuickSort(const std::vector<std::string>& s, CharCmp& cmp, int depth) {
    if (s.size() < QUICK_SORT_THRESHOLD) {
        return TernaryQuickSort(s, cmp, depth);
    }
    int n = s.size();
    std::vector<std::string> excl;
    std::vector<std::vector<std::string> > counting_buckets(ALP_SIZE);
    for (const auto& str : s) {
        if (str.size() <= depth) {
            excl.push_back(str);
        }
        counting_buckets[static_cast<int>(str[depth])].push_back(str);
    }
    std::vector<std::string> result = std::move(excl);
    for (int i = 0; i < ALP_SIZE; ++i) {
        if (counting_buckets[i].empty()) {
            continue;
        }
        auto sorted_bucket = MsdRadixQuickSort(std::move(counting_buckets[i]), cmp, depth + 1);
        result.insert(result.end(), sorted_bucket.begin(), sorted_bucket.end());
    }
    return result;
}
