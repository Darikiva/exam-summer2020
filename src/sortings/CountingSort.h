//
// Created by Snegovsky Vlad on 09.06.2020.
//

#ifndef EXAM_SUMMER2020_COUNTINGSORT_H
#define EXAM_SUMMER2020_COUNTINGSORT_H

#include <vector>
#include <thread>

template<typename T>
class parallelCountingSort{
    std::vector<std::vector<T>> divideArray(size_t num, std::vector<T> array){
        std::vector<std::vector<T>> result;
        size_t length = array.size() / num;
        size_t remain = array.size() % num;
        size_t begin = 0;
        size_t end = 0;

        for (size_t i = 0; i < std::min(num, array.size()); i++) {
            end += (remain > 0) ? (length + ((remain--) != 0)) : length;
            result.emplace_back(array.begin() + begin, array.begin() + end);
            begin = end;
        }

        return result;
    }
    static void countElements(std::vector<T> temp, std::vector<T> &count, T min){
        for(int i = 0; i < temp.size(); i++)
            count[temp[i]-min]++;
    }

public:
    void countSort(std::vector <T>& arr){
        T max = *max_element(arr.begin(), arr.end());
        T min = *min_element(arr.begin(), arr.end());
        T range = max - min + 1;

        std::vector<T> count(range), output(arr.size());

        size_t thread_count = std::thread::hardware_concurrency();
        std::vector<std::vector<T>> vectors = divideArray(thread_count, arr);
        std::vector<std::thread> threads;
        threads.reserve(vectors.size());
        for(auto & vec : vectors) {
            threads.emplace_back(countElements, vec, std::ref(count), min);
        }
        for(auto& th : threads) {
            th.join();
        }

        for(int i = 1; i < count.size(); i++)
            count[i] += count[i-1];

        for(int i = arr.size()-1; i >= 0; i--)
        {
            output[ count[arr[i]-min] -1 ] = arr[i];
            count[arr[i]-min]--;
        }

        for(int i=0; i < arr.size(); i++)
            arr[i] = output[i];
    }
};

#endif //EXAM_SUMMER2020_COUNTINGSORT_H
