#pragma once

template<typename T>
class CSimpleSortedArray {
public:
    // Member variables
    TSGrowableArray<T> m_array;
    uint32_t m_count = 0;
    uint32_t m_maxcount = 0;
    uint32_t m_iterator = 0;

    // Member functions
    T& operator[](uint32_t index) {
        return this->m_array[index];
    }
    uint32_t Count() {
        return this->m_count;
    }
    void Insert(T element) {
        if (this->m_count == this->m_maxcount) {
            this->m_maxcount += 8;
            this->m_array.SetCount(this->m_maxcount);
        }

        uint32_t index = 0;

        // Search for appropriate insertion index based on priority
        for (int32_t i = 0; i < this->m_count; i++) {
            if (element->priority > this->m_array[i]->priority) {
                index = i;
                break;
            }

            if (i == this->m_count - 1) {
                index = i + 1;
                break;
            }
        }

        // Shift any elements after insertion index ahead by 1
        for (int32_t s = this->m_count; s > index; s--) {
            this->m_array[s] = this->m_array[s - 1];
        }

        this->m_array[index] = element;

        if (index < this->m_iterator) {
            this->m_iterator++;
        }

        this->m_count++;
    }
    void Remove(uint32_t index) {
        // Shift any elements after removal index back by 1
        for (int32_t s = index; s < this->m_count - 1; s++) {
            this->m_array[s] = this->m_array[s + 1];
        }

        if (index < this->m_iterator) {
            this->m_iterator--;
        }

        this->m_count--;

        if (this->m_maxcount - this->m_count > 8) {
            this->m_maxcount -= 8;
            this->m_array.SetCount(this->m_maxcount);
        }
    }
};



