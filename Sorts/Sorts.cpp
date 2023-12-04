#include <iostream>
#include <vector>

template<class Iter>
void bubble_sort(Iter begin, Iter end) {
    bool swapped;
    if ((end-begin) <= 1) return;
    do {
        swapped = false;
        for (auto i = begin, i_next = std::next(begin); i_next != end; ++i, ++i_next) {
            if (*i > *i_next) {
                std::swap(*i, *i_next);
                swapped = true;
            }
            
        }
        
    } while (swapped);
}

int main()
{
    std::vector<int> vect = { 99, 5, 7, 3 };
    bubble_sort(vect.begin(), vect.end());
    for (size_t i = 0; i < vect.size(); ++i) {
        std::cout << vect[i];
    }   
}
