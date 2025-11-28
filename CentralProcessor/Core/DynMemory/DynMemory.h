#ifndef MY_VECTOR_H
#define MY_VECTOR_0

#include <string>
using std::string;
#include <stdexcept>
#include <cstring>

/**
 * @class DynMemory
 * @brief A dynamic memory management class that provides a vector-like interface.
 * @tparam T The type of elements stored in the vector.
 */
template<typename T>
class DynMemory {
private:
    /**
     * @var ar
     * @brief The underlying array of elements.
     */
    T *ar = nullptr;

    /**
     * @var csize
     * @brief The current size of the vector.
     */
    size_t csize = 0;

    /**
     * @var msize
     * @brief The maximum size of the vector.
     */
    size_t msize = 0;

    /**
     * @brief Destroys the underlying array and resets the vector.
     */
    void kill() ;

    /**
     * @brief Resizes the underlying array to the specified size.
     * @param new_msize The new maximum size of the vector.
     * @return A pointer to the resized array.
     */
    T *resize(size_t new_msize) &;

    /**
     * @brief Controls the memory usage of the vector by resizing the array if necessary.
     * @return A pointer to the resized array.
     */
    T *memcontrol() &;

public:
    /**
     * @brief Constructs an empty vector.
     */
    DynMemory(): csize(0)
                 , msize(0)
                 , ar(nullptr) {
    };

    /**
     * @brief Destroys the vector and releases the underlying memory.
     */
    

    ~DynMemory() {
        kill();
    }
    

    /**
     * @brief Returns the current size of the vector.
     * @return The current size of the vector.
     */
    size_t size() const &;

    /**
     * @brief Adds an element to the end of the vector.
     * @param elem The element to add.
     */
    void push_back(T elem) &;

    /**
     * @brief Removes the last element from the vector.
     */
    void pop_back() &;

    /**
     * @brief Checks if the vector is empty.
     * @return True if the vector is empty, false otherwise.
     */
    bool empty() const &;

    /**
     * @brief Returns a constant reference to the element at the specified index.
     * @param i The index of the element to retrieve.
     * @return A constant reference to the element at the specified index.
     */
    const T &operator [](size_t i) const;

    /**
     * @brief Returns a reference to the element at the specified index.
     * @param i The index of the element to retrieve.
     * @return A reference to the element at the specified index.
     */
    T &operator [](size_t i);
    /**
     * @brief Returns a constant reference to the element at the specified index.
     * @param i The index of the element to retrieve.
     * @return A constant reference to the element at the specified index.
     */
    const T &operator [](int64_t i) const;

    /**
     * @brief Returns a reference to the element at the specified index.
     * @param i The index of the element to retrieve.
     * @return A reference to the element at the specified index.
     */
    T &operator [](int64_t i);

    /**
     * @brief Returns a constant reference to the element at the specified index.
     * @param i The index of the element to retrieve.
     * @return A constant reference to the element at the specified index.
     */
    const T &operator [](int i) const;

    /**
     * @brief Returns a reference to the element at the specified index.
     * @param i The index of the element to retrieve.
     * @return A reference to the element at the specified index.
     */
    T &operator [](int i);

    /**
     * @class Iterator
     * @brief An iterator class for the DynMemory class.
     */
    DynMemory(int64_t length) {
        ar = new T[length * 2 + 1];
        msize = length * 2 + 1;
        csize = length;
        void * ptr = ar;
        std::fill(ar, ar + msize, 0);
        //std::memset(ptr, 0, msize * sizeof(T));
        /*
        for (int64_t i = 0; i < length; i++) {
            ar[i] = 0;
        }
        */
    }
    DynMemory(const DynMemory & other) {
        csize = other.csize;
        msize = other.msize;
        ar = new T[msize];
        std::copy(other.ar, other.ar + msize, ar);
    }
    DynMemory& operator=(const DynMemory& other) {
        if (this != &other) {
            if (other.ar != nullptr) {
                if (ar != nullptr) {
                    delete []ar;
                }
                csize = other.csize;
                msize = other.msize;
                ar = new T[msize];
                std::copy(other.ar, other.ar + msize, ar);
            }
        }
        return *this;
    }
    class Iterator {
    private:
        /**
         * @var place
         * @brief A pointer to the current element.
         */
        T *place = nullptr;

    public:
        /**
         * @brief Returns a reference to the current element.
         * @return A reference to the current element.
         */
        T &operator *() &;

        /**
         * @brief Returns a constant reference to the current element.
         * @return A constant reference to the current element.
         */
        const T &operator*() const &;

        /**
         * @brief Constructs an iterator from a pointer to an element.
         * @param set A pointer to an element.
         */
        Iterator(T *set);

        /**
         * @brief Constructs a default iterator.
         */
        Iterator(): place(nullptr) {
        };

        /**
         * @brief Copy constructor.
         * @param set An iterator to copy.
         */
        Iterator(const Iterator &set) {
            place = set.place;
        }

        /**
         * @brief Post-increment operator.
         * @return A reference to the iterator.
         */
        Iterator &operator++(int);

        /**
         * @brief Pre-increment operator.
         * @return A reference to the iterator.
         */
        Iterator &operator++();

        /**
         * @brief Post-decrement operator.
         * @return A reference to the iterator.
         */
                Iterator &operator--(int);

        /**
         * @brief Pre-decrement operator.
         * @return A reference to the iterator.
         */
        Iterator &operator--();

        /**
         * @brief Equality operator.
         * @param it An iterator to compare.
         * @return True if the iterators are equal, false otherwise.
         */
        bool operator ==(const Iterator &it) const &;

        /**
         * @brief Inequality operator.
         * @param it An iterator to compare.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator !=(const Iterator &it) const & {
            return !(*this == it);
        }

        /**
         * @brief Addition operator.
         * @param mv The number of elements to move.
         * @return An iterator pointing to the new position.
         */
        Iterator operator +(size_t mv) const &;

        /**
         * @brief Subtraction operator.
         * @param mv The number of elements to move.
         * @return An iterator pointing to the new position.
         */
        Iterator operator -(size_t mv) const &;

        /**
         * @brief Subtraction operator.
         * @param it An iterator to subtract.
         * @return The distance between the iterators.
         */
        size_t operator -(Iterator &it) const &;

        /**
         * @brief Subtraction operator.
         * @param it An iterator to subtract.
         * @return The distance between the iterators.
         */
        size_t operator -(Iterator it);

        /**
         * @brief Returns a pointer to the current element.
         * @return A pointer to the current element.
         */
        T *get() const & {
            return place;
        }

        /**
         * @brief Less-than operator.
         * @param it An iterator to compare.
         * @return True if the current iterator is less than the other iterator, false otherwise.
         */
        bool operator <(Iterator const &) const &;
    };

    /**
     * @brief Returns an iterator pointing to the beginning of the vector.
     * @return An iterator pointing to the beginning of the vector.
     */
    Iterator begin() const &;

    /**
     * @brief Returns an iterator pointing to the end of the vector.
     * @return An iterator pointing to the end of the vector.
     */
    Iterator end() const &;

    /**
     * @brief Removes the element at the specified iterator position.
     * @param it An iterator pointing to the element to remove.
     * @return An iterator pointing to the new position.
     */
    Iterator remove(Iterator it) &;
};

template<typename T>
size_t DynMemory<T>::size() const & {
    return csize;
}


template<typename T>
void DynMemory<T>::kill() {
    if (ar != nullptr && msize != 0) {
        delete [] ar;
        ar = nullptr;
    }
}


template<typename T>
T *DynMemory<T>::resize(size_t new_msize) & {
    if (ar != nullptr) {
        T *new_ptr = new T[new_msize];
        std::copy(ar, ar + csize, new_ptr);
        delete []ar;
        ar = new_ptr;
    }
    return ar;
}


template<typename T>
size_t DynMemory<T>::Iterator::operator-(DynMemory<T>::Iterator it) {
    return abs(this->place - it.place);
}


template<typename T>
T *DynMemory<T>::memcontrol() & {
    if (csize >= msize) {
        ar = resize(msize * 2);
        msize *= 2;
    } else if (csize * 2 < msize && csize != 0) {
        ar = resize(msize / 2);
        msize /= 2;
    }
    return ar;
}

template<typename T>
void DynMemory<T>::push_back(T elem) & {
    if (this->ar == nullptr) {
        csize = 0;
        msize = 1;
        ar = new T[msize];
    }
    ar = memcontrol();
    ar[csize++] = elem;
}


template<typename T>
void DynMemory<T>::pop_back() & {
    if (ar == nullptr || csize == 0)
        throw std::runtime_error("EmptyArray");
    csize--;
    ar = memcontrol();
}


template<typename T>
const T &DynMemory<T>::operator [](size_t i) const {
    if (i >= csize) {
        string err = "List_index_out_of_range";
        throw std::runtime_error(err);
    }
    return (this->ar)[i];
}


template<typename T>
T &DynMemory<T>::operator [](size_t i) {
    if (i >= csize) {
        string err = "List_index_out_of_range";
        throw std::runtime_error(err);
    }
    return (this->ar)[i];
}

template<typename T>
const T &DynMemory<T>::operator [](int64_t i) const {
    if (i >= csize || i< 0) {
        string err = "List_index_out_of_range";
        throw std::runtime_error(err);
    }
    return (this->ar)[i];
}


template<typename T>
T &DynMemory<T>::operator [](int64_t i) {
    if (i >= csize || i < 0) {
        string err = "List_index_out_of_range";
        throw std::runtime_error(err);
    }
    return (this->ar)[i];
}


template<typename T>
const T &DynMemory<T>::operator [](int i) const {
    if (i < 0 || static_cast<size_t>(i) >= csize) {
        string err = "List_index_out_of_range";
        throw std::runtime_error(err);
    }
    return (this->ar)[i];
}


template<typename T>
T &DynMemory<T>::operator [](int i) {
    if (i < 0 || static_cast<size_t>(i) >= csize) {
        string err = "List_index_out_of_range";
        throw std::runtime_error(err);
    }
    return (this->ar)[i];
}


template<typename T>
bool DynMemory<T>::empty() const & {
    return ar == nullptr || csize == 0;
}

template<typename T>
T &DynMemory<T>::Iterator::operator *() & {
    if (place == nullptr) throw std::runtime_error("EmptyArray");
    return *place;
}


template<typename T>
const T &DynMemory<T>::Iterator::operator*() const & {
    if (place == nullptr) throw std::runtime_error("EmptyArray");
    return *place;
}

template<typename T>
typename DynMemory<T>::Iterator &DynMemory<T>::Iterator::operator ++(int) {
    place++;
    return *this;
}

template<typename T>
typename DynMemory<T>::Iterator &DynMemory<T>::Iterator::operator ++() {
    place++;
    return *this;
}

template<typename T>
typename DynMemory<T>::Iterator &DynMemory<T>::Iterator::operator --(int) {
    place--;
    return *this;
}

template<typename T>
typename DynMemory<T>::Iterator &DynMemory<T>::Iterator::operator --() {
    place--;
    return *this;
}

template<typename T>
bool DynMemory<T>::Iterator::operator==(const DynMemory<T>::Iterator &it) const & {
    return it.place == place;
}


template<typename T>
DynMemory<T>::Iterator::Iterator(T *set) {
    place = set;
}

template<typename T>
typename DynMemory<T>::Iterator DynMemory<T>::end() const & {
    Iterator it(ar + csize);
    return it;
}

template<typename T>
typename DynMemory<T>::Iterator DynMemory<T>::begin() const & {
    Iterator it(ar);
    return it;
}

template<typename T>
typename DynMemory<T>::Iterator DynMemory<T>::Iterator::operator+(size_t mv) const & {
    Iterator it(place + mv);
    return it;
}



template<typename T>
typename DynMemory<T>::Iterator DynMemory<T>::Iterator::operator-(size_t mv) const & {
    Iterator it(place - mv);
    return it;
}

template<typename T>
typename DynMemory<T>::Iterator DynMemory<T>::remove(DynMemory<T>::Iterator it) & {
    if (it == this->end() - 1) {
        csize--;
    } else {
        for (DynMemory<T>::Iterator i = it; i < this->end(); i++) {
            *i = *(i + 1);
        }
    }
    (this->csize)--;
    size_t dist = it - (this->begin());
    ar = memcontrol();
    return this->begin() + (dist - 1);
}


template<typename T>
size_t DynMemory<T>::Iterator::operator-(DynMemory<T>::Iterator &it) const & {
    return abs(place - it.place);
}


template<typename T>
bool DynMemory<T>::Iterator::operator<(const DynMemory<T>::Iterator &it) const & {
    return this->place < it.place;
}

#endif
