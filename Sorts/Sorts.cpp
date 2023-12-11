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

template <class Iter>
void do_heap(Iter begin, size_t size, size_t large, Stats& stat)
{
    size_t largest = large;
    size_t l = 2 * large + 1;
    size_t r = 2 * large + 2; 

    if (l < size && (*(begin + l) > *(begin + largest))) {
        largest = l;
        ++stat.comparison_count;
    }
    ++stat.comparison_count;
    if (r < size && (*(begin + r) > *(begin + largest))) {
        ++stat.comparison_count;
        largest = r;
    }
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

int main()
{
    std::vector<int> vect = { 99, 5, 3 , 0 ,8 ,6 , 7 , 2 ,8 ,8,2 ,6 ,72,-1,-1,-2};
    
    //std::vector<int> vect = { 99, 5,3,0,8};
    //Stats stat=heap_sort(vect.begin(), vect.end());
    //do_heap(vect.begin(), vect.end());
    heap_sort(vect.begin(), vect.end());
    for (size_t i = 0; i < vect.size(); ++i) {
        std::cout << vect[i]<<" ";
    }   
}
