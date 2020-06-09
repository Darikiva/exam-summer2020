//
// Created by Snegovsky Vlad on 09.06.2020.
//

#ifndef EXAM_SUMMER2020_BUCKETSORT_H
#define EXAM_SUMMER2020_BUCKETSORT_H

#include <vector>
#include <thread>

template<typename T>
class parallelBucketSort{
    static void sortArr(std::vector<T> &b){
        sort(b.begin(), b.end());
    }

public:
    void bucketSort(std::vector<T>& arr){
        std::vector<T> b[arr.size()];

        for (int i = 0; i < arr.size(); i++)
        {
            int bi = arr.size()*arr[i];
            b[bi].push_back(arr[i]);
        }

        size_t thread_count = std::thread::hardware_concurrency();
        if (arr.size() > thread_count){
            for (int i = thread_count; i < arr.size() + thread_count; i += thread_count){
                std::vector<std::thread> threads;
                threads.reserve(thread_count);
                if (i + thread_count == arr.size())
                    thread_count = arr.size() - i - 1;
                for(int j = 0; j < thread_count; j++) {
                    threads.emplace_back(sortArr, std::ref(b[j]));
                }
                for(auto& th : threads) {
                    th.join();
                }
            }
        }

        for (int i = 0; i < arr.size(); i++)
            sort(b[i].begin(), b[i].end());

        int index = 0;
        for (int i = 0; i < arr.size(); i++)
            for (int j = 0; j < b[i].size(); j++)
                arr[index++] = b[i][j];
    }
};

#endif //EXAM_SUMMER2020_BUCKETSORT_H
