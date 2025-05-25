#include "common.h"

namespace {

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

} // namespace

std::vector<std::string> MergeSort(const std::vector<std::string>& s, int tl, int tr, CharCmp& cmp) {
    if (tl + 1 >= tr) {
        std::vector<std::string> result;
        for (int i = tl; i < tr; ++i) {
            result.push_back(s[i]);
        }
        return result;
    }
    auto result_left = MergeSort(s, tl, (tr + tl) / 2, cmp);
    auto result_right = MergeSort(s, (tr + tl) / 2, tr, cmp);
    std::vector<std::string> result;
    result.reserve(result_left.size() + result_right.size());
    int i = 0, j = 0;
    while (i < result_left.size() && j < result_right.size()) {
        int cmp_result = CompareString(result_left[i], result_right[j], cmp);
        if (cmp_result <= 0) {
            result.push_back(result_left[i]);
            ++i;
        } else {
            result.push_back(result_right[j]);
            ++j;
        }
    }
    while (i < result_left.size()) {
        result.push_back(result_left[i]);
        ++i;
    }
    while (j < result_right.size()) {
        result.push_back(result_right[j]);
        ++j;
    }
    return result;
}

std::vector<std::string> MergeSort(const std::vector<std::string>& s, CharCmp& cmp) {
    return MergeSort(s, 0, static_cast<int>(s.size()), cmp);
}
