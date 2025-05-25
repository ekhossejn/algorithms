#pragma once
#include <vector>
#include <string>
#include <random>

struct CharCmp {
    CharCmp(size_t& cmp_cnt): cmp_cnt(cmp_cnt) {}

    int operator()(char c1, char c2) {
        ++cmp_cnt;
        return static_cast<int>(c1) - static_cast<int>(c2);
    }

    size_t& cmp_cnt;
};


std::vector<std::string> MergeSort(const std::vector<std::string>& s, CharCmp& cmp);

std::vector<std::string> StringMergeSort(const std::vector<std::string>& s, CharCmp& cmp);

std::vector<std::string> QuickSort(const std::vector<std::string>& s, CharCmp& cmp);

std::vector<std::string> TernaryQuickSort(const std::vector<std::string>& s, CharCmp& cmp, int depth = 0);

std::vector<std::string> MsdRadixSort(const std::vector<std::string>& s, CharCmp& cmp, int depth = 0);

std::vector<std::string> MsdRadixQuickSort(const std::vector<std::string>& s, CharCmp& cmp, int depth = 0);