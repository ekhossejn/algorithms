#include "common.h"

namespace {
std::mt19937 rd(179);

int CompareString(const std::string& s1, const std::string& s2, CharCmp& cmp) {
    int min_length = std::min(s1.size(), s2.size());
    for (int i = 0; i < min_length; ++i) {
        auto cmp_result = cmp(s1[i], s2[i]);
        if (cmp_result != 0) {
            return cmp_result;
        }
    }
    if (s1.size() < s2.size()) {
        return -1;
    } else if (s1.size() > s2.size()) {
        return 1;
    }
    return 0;
}
}  // namespace

std::vector<std::string> QuickSort(const std::vector<std::string>& s, CharCmp& cmp) {
    if (s.size() <= 1) {
        return s;
    }
    int n = s.size();
    std::vector<std::string> less, equal, great;
    const std::string& pivot = s[rd() % s.size()];
    for (const auto& str : s) {
        auto cmp_result = CompareString(str, pivot, cmp);
        if (cmp_result < 0) {
            less.push_back(str);
        } else if (cmp_result > 0) {
            great.push_back(str);
        } else {
            equal.push_back(str);
        }
    }

    auto less_sorted = QuickSort(std::move(less), cmp);
    auto great_sorted = QuickSort(std::move(great), cmp);

    std::vector<std::string> result;
    result.reserve(less_sorted.size() + equal.size() + great_sorted.size());
    result.insert(result.end(), less_sorted.begin(), less_sorted.end());
    result.insert(result.end(), equal.begin(), equal.end());
    result.insert(result.end(), great_sorted.begin(), great_sorted.end());
    return result;
}
