#pragma once

#include <vector>
#include <string>
#include <random>

class StringGenerator {
    const int kMinStringLength = 10;
    const int kMaxStringLength = 200;
    const std::string kAlphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#%:;^&*()-";
public:
    StringGenerator() = default;

    std::string GenerateRandomString(int len) {
        std::string result;
        for (int i = 0; i < len; ++i) {
            result += kAlphabet[rd_() % kAlphabet.size()];
        }
        return result;
    }

    std::vector<std::string> GenerateVector(int len) {
        std::vector<std::string> result(len);
        for (int i = 0; i < len; ++i) {
            int str_len = kMinStringLength + rd_() % (kMaxStringLength - kMinStringLength + 1);
            result[i] = GenerateRandomString(str_len);
        }
        return result;
    }

    std::vector<std::string> GenerateReversedVector(int len) {
        auto result = GenerateVector(len);
        std::sort(result.begin(), result.end());
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::vector<std::string> GenereteAlmostSortedVector(int len) {
        auto result = GenerateVector(len);
        std::sort(result.begin(), result.end());
        int swap_cnt = len / 2;
        for (int i = 0; i < swap_cnt; ++i) {
            int id1 = rd_() % len;
            int id2 = rd_() % len;
            std::swap(result[id1], result[id2]);
        }
        return result;
    }

private:
    std::random_device rd_;
};
