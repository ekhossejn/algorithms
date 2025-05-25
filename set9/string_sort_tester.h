#pragma once

#include "common.h"
#include "string_generator.h"

#include <chrono>
#include <fstream>
#include <map>
#include <functional>
#include <iostream>

class StringSortTester {
    template<typename SortingFunction>
    int64_t runSort(const std::vector<std::string>& s, SortingFunction sort) {
        cmp_cnt_ = 0;
        auto start_time = std::chrono::high_resolution_clock::now();
        CharCmp char_cmp(cmp_cnt_);
        sort(s, char_cmp);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        return delta.count();
    }

public:
    StringSortTester(size_t test_cnt = 20): test_cnt_(test_cnt) {}

    void RunAllTestsToCSV(const std::string& filename) {
        std::ofstream csv(filename);
        csv << "vector_type,size,algorithm,time_ns,comparisons\n";

        std::map<std::string, std::function<std::vector<std::string>(const std::vector<std::string>&, CharCmp&)>> algorithms = {
            {"MergeSort", MergeSort},
            {"QuickSort", QuickSort},
            {"StringMergeSort", StringMergeSort},
            {"TernaryQuickSort", [](const std::vector<std::string>& s, CharCmp& cmp) {
                return TernaryQuickSort(s, cmp, 0);
            }},
            {"MsdRadixSort", [](const std::vector<std::string>& s, CharCmp& cmp) {
                return MsdRadixSort(s, cmp, 0);
            }},
            {"MsdRadixQuickSort", [](const std::vector<std::string>& s, CharCmp& cmp) {
                return MsdRadixQuickSort(s, cmp, 0);
            }}
        };

        const std::vector<std::string> vector_types = {"random", "reversed", "almost_sorted"};
        StringGenerator generator;

        for (const auto& vector_type : vector_types) {
            for (int test_id = 0; test_id < test_cnt_; ++test_id) {
                std::vector<std::string> generated_vector;
                if (vector_type == "random") {
                    generated_vector = generator.GenerateVector(kMaxVectorLength);
                } else if (vector_type == "reversed") {
                    generated_vector = generator.GenerateReversedVector(kMaxVectorLength);
                } else if (vector_type == "almost_sorted") {
                    generated_vector = generator.GenereteAlmostSortedVector(kMaxVectorLength);
                } else {
                    throw std::runtime_error("Unknown vector type: " + vector_type);
                }
                for (int size = 100; size <= kMaxVectorLength; size += 100) {
                    std::cout << "Testing " << vector_type << " vector of size " << size << " (test " << test_id + 1 << "/" << test_cnt_ << ")\n";
                    std::vector<std::string> subarray(generated_vector.begin(), generated_vector.begin() + size);
                    for (const auto& [name, func] : algorithms) {
                        int64_t time_ns = runSort(subarray, func);
                        csv << vector_type << "," << size << "," << name << "," << time_ns << "," << cmp_cnt_ << "\n";
                    }
                }
            }
        }
        csv.close();
    }

    size_t test_cnt_;
    size_t cmp_cnt_ = 0;
    const int kMaxVectorLength = 3000;
};
