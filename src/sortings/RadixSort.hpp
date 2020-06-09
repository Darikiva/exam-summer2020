#pragma once

#include <vector>
#include <string>

namespace exam::sort {

    template<typename Item>
    class RadixSort {
    private:
        std::vector<Item> elements;
        const int SYSTEM = 10;
    private:
        Item getMax();

        void countSort(int exp);

    public:
        explicit RadixSort(std::vector<Item> elements) : elements{elements} {}

        void sort();

        std::string print();

        std::vector<Item> getElements();

        void setElements(std::vector<Item> elements_);
    };

    template<typename Item>
    Item RadixSort<Item>::getMax() {
        Item mx = elements[0];
        for (int i = 1; i < elements.size(); i++)
            if (elements[i] > mx)
                mx = elements[i];
        return mx;
    }

    template<typename Item>
    void RadixSort<Item>::countSort(int exp) {
        std::vector<Item> output;
        output.resize(elements.size());
        int i, count[SYSTEM] = {0};

        for (i = 0; i < elements.size(); i++)
            count[(elements[i] / exp) % SYSTEM]++;

        for (i = 1; i < SYSTEM; i++)
            count[i] += count[i - 1];

        for (i = elements.size() - 1; i >= 0; i--) {
            output[count[(elements[i] / exp) % SYSTEM] - 1] = elements[i];
            count[(elements[i] / exp) % SYSTEM]--;
        }

        for (i = 0; i < elements.size(); i++)
            elements[i] = output[i];
    }

    template<typename Item>
    void RadixSort<Item>::sort() {
        Item m = getMax();

        for (int exp = 1; m / exp > 0; exp *= SYSTEM)
            countSort(exp);
    }

    template<typename Item>
    std::string RadixSort<Item>::print() {
        std::string result;
        for (auto el:elements)
            result += std::to_string(el) + " ";
        result.pop_back();
        return result;
    }

    template<typename Item>
    std::vector<Item> RadixSort<Item>::getElements() {
        return elements;
    }

    template<typename Item>
    void RadixSort<Item>::setElements(std::vector<Item> elements_) {
        elements = elements_;
    }
} // namespace exam