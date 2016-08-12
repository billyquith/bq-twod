
#pragma once

#include <bqutil/config.hpp>
#include <vector>
#include <functional>

namespace bq {

    template <typename T>
    class vector : public std::vector<T>
    {
    public:
        typedef typename std::vector<T> vector_t;
        
        vector() = default;
        vector(std::size_t initSize) : vector_t(initSize) {}

        std::size_t append(const T& val) {
            this->push_back(val);
            return this->size() - 1;    // return index
        }

        void remove(const T& val) {
            auto it = std::find(this->begin(), this->end(), val);
            BQ_ASSERT(it != vector_t::end());
            this->erase(it);
        }
        
        typename vector_t::iterator find(const T& val) {
            return std::find(vector_t::begin(), vector_t::end(), val);
        }
        
        int indexOf(const T& val) {
            auto it = find(val);
            return it == vector_t::end() ? -1 : std::distance(vector_t::begin(), it);
        }
        
        void foreach(std::function<void(T&)> fn) {
            for (auto&& i : *this)
                fn(i);
        }

//        void remove_unordered_index(size_t index) {
//            const size_t sz = this->size();
//            if (sz > 1) {
//                (*this)[index] = (*this)[sz - 1];   // Swap last item into index.
//            }
//            this->pop_back(); // size--
//        }

//        void remove_unordered(const TYPE &val)
//        {
//            typename Parent::iterator it = std::find(this->begin(), this->end(), val);
//            GU_LIB_ASSERT(it != this->end());
//            remove_unordered_index(static_cast<size_t>(it - this->begin()));
//        }
    };
    
} // namespace bq

