
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
        
        // iterate over elements. F -> void(T&)
        template <typename F>
        void foreach(const F& fn) {
            for (auto&& it : *this)
                fn(it);
        }

        // iterate over elements with index. F -> void(T&, int)
        template <typename F>
        void foreachi(const F& fn) {
            int i(0);
            for (auto&& it : *this)
                fn(it, i++);
        }

        void remove_index_swap(std::size_t index) {
            const std::size_t sz = vector_t::size();
            if (index < sz-1)
                (*this)[index] = (*this)[sz - 1];   // Swap last item into index.
            vector_t::pop_back(); // size--
        }

        void remove_swap(const T &val)
        {
            auto it = std::find(vector_t::begin(), vector_t::end(), val);
            BQ_ASSERT(it != this->end());
            remove_index_swap(std::distance(vector_t::begin(), it));
        }
    };
    
} // namespace bq

