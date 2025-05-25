**Запуск программы**
rm -rf results.csv && g++ -o run_tests ./merge_sort.cpp ./quick_sort.cpp ./ternary_quick_sort.cpp ./msd_radix_sort.cpp ./msd_radix_quick_sort.cpp ./string_merge_sort.cpp ./run_tests.cpp -std=c++20 && ./run_tests

**Парсинг в графики**
python3 ./parse.py