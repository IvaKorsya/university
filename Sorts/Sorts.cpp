#include <iostream>
#include <vector>
#include <random>

size_t SIZE = 100000;

struct Stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

template<class Iter>
Stats bubble_sort(Iter begin, Iter end) {
    auto stat = Stats();
    bool swapped;
    if (std::distance(begin, end) <= 1) return stat;
    do {
        swapped = false;
        for (auto i = begin, i_next = std::next(begin); i_next != end; ++i, ++i_next) {
            if (*i > *i_next) {
                ++stat.comparison_count;
                std::swap(*i, *i_next);
                ++stat.copy_count;
                swapped = true;
            }
        }  
    } while (swapped);
    return stat;
}

template<class Iter>
void quick_sort_(Iter begin, Iter end, Stats& stat) {
    size_t size = std::distance(begin, end);
    if (size < 2) return;
    auto pivot= begin[size / 2];
    auto i = begin;
    auto j = end-1;

    while (i <= j) {
        while (*i < pivot) {
            ++stat.comparison_count;
            ++i;
        }
        ++stat.comparison_count;
        while (*j > pivot) {
            ++stat.comparison_count;
            --j;
        } 
        ++stat.comparison_count;
        if (i <= j) {
            std::swap(*i, *j); 
            ++stat.copy_count;
            ++i;
            --j;
        }   
    }
    quick_sort_(begin, j+1,stat);
    quick_sort_(i, end,stat);
}

template <class Iter>
Stats quick_sort(Iter begin, Iter end) {
    Stats stat{};
    size_t size = std::distance(begin, end);
    if (size < 2) return stat;
    quick_sort_(begin, end, stat);
    return stat;
}

template <class Iter>
void do_heap(Iter begin, size_t size, size_t large, Stats& stat)
{
    size_t largest = large;
    size_t l = 2 * large + 1;
    size_t r = 2 * large + 2; 

    if (l < size && (*(begin + l) > *(begin + largest))) largest = l;
    ++stat.comparison_count;
    if (r < size && (*(begin + r) > *(begin + largest))) largest = r;
    ++stat.comparison_count;
    if (largest !=large)
    {
       std:: swap(*(begin + large), *(begin + largest));
       ++stat.copy_count;
       do_heap(begin, size, largest,stat);
    }
}

template <class Iter>
Stats heap_sort(Iter begin,Iter end)
{
    auto size = std::distance(begin, end);
    if (size < 2) return Stats{};
    Stats stat{};
    for (int i = size / 2 - 1; i >= 0; i--) {
        do_heap(begin, size, i,stat);
    }
    for (int i = size - 1; i >= 0; i--)
    {
        std::swap(*begin, *(begin+i));
        ++stat.copy_count;
        do_heap(begin, i, 0,stat);
    }
    return stat;
}

std::vector<int> random_vector(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> vect;
    for (auto i = 0; i < size; ++i) {
        vect.push_back(gen());
    }
    return vect;
}

std::vector<int> sorted_vector(size_t size) {
    std::vector<int> vect;
    for (auto i = 0; i < size; ++i) {
        vect.push_back(i);
    }
    return vect;
}

std::vector<int> inverted_vector(size_t size) {
    std::vector<int> vect;
    for (auto i = size-1; i > 0; --i) {
        vect.push_back(i);
    }
    return vect;
}

int main()
{
    //Bubble sort, random vector
    std::cout << "bubble sort, random, size="<<SIZE << std::endl;
    size_t sum_c1 = 0, count1 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = random_vector(SIZE);
        auto stat = bubble_sort(vect.begin(), vect.end());
        sum_c1 += stat.comparison_count;
        count1 += stat.copy_count;
    }
    std::cout << sum_c1 / 100 << " " << count1 / 100 << std::endl;


    //Bubble sort, sorted vector
    std::cout << "bubble sort, sorted, size=" << SIZE << std::endl;
    size_t sum_c2 = 0, count2 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = sorted_vector(SIZE);
        auto stat = bubble_sort(vect.begin(), vect.end());
        sum_c2 += stat.comparison_count;
        count2 += stat.copy_count;
    }
    std::cout << sum_c2 / 100 << " " << count2 / 100 << std::endl;

    //Bubble sort, inv vector
    std::cout << "bubble sort, inv, size=" << SIZE << std::endl;
    size_t sum_c3 = 0, count3 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = inverted_vector(SIZE);
        auto stat = bubble_sort(vect.begin(), vect.end());
        sum_c3 += stat.comparison_count;
        count3+= stat.copy_count;
    }
    std::cout << sum_c3 / 100 << " " << count3 / 100 << std::endl;

    //Quick sort, random vector
    std::cout << "quick sort, random, size=" << SIZE << std::endl;
    size_t sum_c4 = 0, count4 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = random_vector(SIZE);
        auto stat = quick_sort(vect.begin(), vect.end());
        sum_c4 += stat.comparison_count;
        count4 += stat.copy_count;
    }
    std::cout << sum_c4 / 100 << " " << count4 / 100 << std::endl;

    //Quick sort, sorted vector
    std::cout << "quick sort, sorted, size=" << SIZE << std::endl;
    size_t sum_c5 = 0, count5 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = sorted_vector(SIZE);
        auto stat = quick_sort(vect.begin(), vect.end());
        sum_c5 += stat.comparison_count;
        count5 += stat.copy_count;
    }
    std::cout << sum_c5 / 100 << " " << count5 / 100 << std::endl;

    //Quick sort, inv vector
    std::cout << "quick sort, inv, size=" << SIZE << std::endl;
    size_t sum_c6 = 0, count6= 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = inverted_vector(SIZE);
        auto stat = quick_sort(vect.begin(), vect.end());
        sum_c6 += stat.comparison_count;
        count6 += stat.copy_count;
    }
    std::cout << sum_c6 / 100 << " " << count6 / 100 << std::endl;

    //Heap sort, random vector
    std::cout << "heap sort, random, size=" << SIZE << std::endl;
    size_t sum_c7 = 0, count7 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = random_vector(SIZE);
        auto stat = heap_sort(vect.begin(), vect.end());
        sum_c7 += stat.comparison_count;
        count7 += stat.copy_count;
    }
    std::cout << sum_c7 / 100 << " " << count7 / 100 << std::endl;

    //Heap sort, sorted vector
    std::cout << "heap sort, sorted, size=" << SIZE << std::endl;
    size_t sum_c8 = 0, count8 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = sorted_vector(SIZE);
        auto stat = heap_sort(vect.begin(), vect.end());
        sum_c8 += stat.comparison_count;
        count8 += stat.copy_count;
    }
    std::cout << sum_c8 / 100 << " " << count8 / 100 << std::endl;

    //Heap sort, inv vector
    std::cout << "heap sort, inv, size=" << SIZE << std::endl;
    size_t sum_c9 = 0, count9 = 0;
    for (auto i = 0; i < 100; ++i) {
        std::vector<int> vect = inverted_vector(SIZE);
        auto stat = heap_sort(vect.begin(), vect.end());
        sum_c9 += stat.comparison_count;
        count9 += stat.copy_count;
    }
    std::cout << sum_c9 / 100 << " " << count9 / 100 << std::endl;
}
