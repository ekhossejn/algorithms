#include "common.h"

// -1 if s1 <= s2, 1 if s1 > s2
std::pair<int, int> LcpCompare(const std::string& s1, const std::string& s2, int k, CharCmp& cmp) {
    int i = k;
    while (i < s1.size() && i < s2.size() && cmp(s1[i], s2[i]) == 0) {
        ++i;
    }
    if (i == s1.size()) {
        return {-1, s2.size()};
    } else if (i == s2.size()) {
        return {1, s2.size()};
    }
    if (s1[i] < s2[i]) {
        return {-1, i};
    }
    return {1, i};
}

std::vector<std::pair<std::string, int>> StringMergeSort(const std::vector<std::string>& s, int tl, int tr, CharCmp& cmp) {
    if (tl + 1 >= tr) {
        std::vector<std::pair<std::string, int>> result;
        for (int i = tl; i < tr; ++i) {
            result.emplace_back(s[i], 0);
        }
        return result;
    }
    auto result_left = StringMergeSort(s, tl, (tr + tl) / 2, cmp);
    auto result_right = StringMergeSort(s, (tr + tl) / 2, tr, cmp);
    std::vector<std::pair<std::string, int>> result;
    result.reserve(result_left.size() + result_right.size());
    int i = 0, j = 0;
    while (i < result_left.size() && j < result_right.size()) {
        if (result_left[i].second > result_right[j].second) {
            result.push_back(result_left[i]);
            ++i;
        } else if (result_left[i].second < result_right[j].second) {
            result.push_back(result_right[j]);
            ++j;
        } else {
            auto [compare_string_result, k] = LcpCompare(result_left[i].first, result_right[j].first, result_left[i].second, cmp);
            if (compare_string_result < 0) {
                result.push_back(result_left[i]);
                result_right[j].second = k;
                ++i;
            } else {
                result.push_back(result_right[j]);
                result_left[i].second = k;
                ++j;
            }
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

std::vector<std::string> StringMergeSort(const std::vector<std::string>& s, CharCmp& cmp) {
    auto result = StringMergeSort(s, 0, s.size(), cmp);
    std::vector<std::string> answer(result.size());
    for (int i = 0; i < result.size(); ++i) {
        answer[i] = result[i].first;
    }
    return answer;
}
