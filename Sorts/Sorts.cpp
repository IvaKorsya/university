#include <iostream>
#include <vector>
#include <random>

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


size_t random_pivot_ind(int max_ind) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, max_ind);
    return dist(gen);
}

int main()
{
    std::vector<int> vect = { 99, 5, 3 , 0 ,8 ,6 , 7 , 2 ,8 ,8,2 ,6 ,72,-1,-1,-2};
    //std::vector<int> vect = { 99, 5,3,0,8};
    Stats stat=quick_sort(vect.begin(), vect.end());
    std::cout << stat.copy_count<<std::endl;
    for (size_t i = 0; i < vect.size(); ++i) {
        std::cout << vect[i];
    }   
}
