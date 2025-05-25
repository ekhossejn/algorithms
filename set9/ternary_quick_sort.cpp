#include "common.h"

namespace {
std::mt19937 rd(179);
}

std::vector<std::string> TernaryQuickSort(const std::vector<std::string>& s, CharCmp& cmp, int depth) {
    if (s.size() <= 1) {
        return s;
    }
    int n = s.size();
    std::vector<std::string> less, equal, great, excl;
    std::vector<int> indexes;
    for (int i = 0; i < n; ++i) {
        if (s[i].size() <= depth) {
            excl.push_back(s[i]);
        } else {
            indexes.push_back(i);
        }
    }
    if (indexes.empty()) {
        return excl;
    }
    const std::string& pivot = s[indexes[rd() % indexes.size()]];
    for (const auto& str : s) {
        if (str.size() <= depth) {
            continue;
        }
        if (cmp(str[depth], pivot[depth]) < 0) {
            less.push_back(str);
        } else if (cmp(str[depth], pivot[depth]) > 0) {
            great.push_back(str);
        } else {
            equal.push_back(str);
        }
    }

    auto less_sorted = TernaryQuickSort(std::move(less), cmp, depth);
    auto equal_sorted = TernaryQuickSort(std::move(equal), cmp, depth + 1);
    auto great_sorted = TernaryQuickSort(std::move(great), cmp, depth);

    std::vector<std::string> result;
    result.reserve(less_sorted.size() + equal_sorted.size() + great_sorted.size() + excl.size());
    result.insert(result.end(), excl.begin(), excl.end());
    result.insert(result.end(), less_sorted.begin(), less_sorted.end());
    result.insert(result.end(), equal_sorted.begin(), equal_sorted.end());
    result.insert(result.end(), great_sorted.begin(), great_sorted.end());
    return result;
}

