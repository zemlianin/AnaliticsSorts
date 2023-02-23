#include <iostream>
#include <vector>
#include <fstream>
#include "chrono"
#include "Sort.cpp"
#include "SortWithCountActions.cpp"

void output(std::vector<int> vec, std::ofstream& stream) {
    for (int i = 0; i < vec.size(); ++i) {
        stream << vec[i]<<" ";
    }
}

bool check(std::vector<int> &vec, std::vector<int> &sourceVec) {
    std::ofstream out("check.txt", std::ios::app);
    output(sourceVec,out);
    auto trueVec = sourceVec;
    out<<"|";
    output(vec,out);
    std::sort(trueVec.begin(), trueVec.end());
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != trueVec[i]) {
            out<<"::: 0"<<"\n";
            return false;
        }
    }
    out<<"::: 1"<<"\n";
    return true;
}

void (*sortFuncs[13])(std::vector<int> &) =
        {selectSort, bubbleSort, bubbleA1Sort, bubbleA12Sort, insertSort, insertBinSort, countSort, radixSort,
         mergeSort, quickSort, heapSort, shellSortCiuraSequence, shellSortShellSequence};

void (*sortFuncsWithCountAction[13])(std::vector<int> &) =
        {selectSortAct, bubbleSortAct, bubbleA1SortAct, bubbleA12SortAct, insertSortAct, insertBinSortAct, countSortAct,
         radixSortAct,
         mergeSortAct, quickSortAct, heapSortAct, shellSortCiuraSequenceAct, shellSortShellSequenceAct};

std::vector<std::pair<int, bool>> measureByTime(std::vector<std::vector<int>> &nums) {
    int countMeasuring = static_cast<int>(nums.size());
    std::vector<std::pair<int, bool>> result(13);
    for (int i = 0; i < 13; ++i) {
        result[i].second = true;
    }
    for (int i = 0; i < countMeasuring; ++i) {
        for (int j = 0; j < 13; ++j) {
            auto nums_of_test = nums[i];
            auto nums_of_test_for_check = nums[i];
            auto start = std::chrono::high_resolution_clock::now();
            sortFuncs[j](nums_of_test);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            int64_t time = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
            result[j].second = check(nums_of_test,nums_of_test_for_check) && result[j].second;
            result[j].first += time;
        }
    }
    for (int i = 0; i < 13; ++i) {
        result[i].first /= countMeasuring;
    }
    return result;
}

std::vector<std::pair<int, bool>> measureByAction(std::vector<std::vector<int>> &nums) {
    int countMeasuring = static_cast<int>(nums.size());
    std::vector<std::pair<int, bool>> result(13);
    for (int i = 0; i < 13; ++i) {
        result[i].second = true;
    }
    for (int i = 0; i < countMeasuring; ++i) {
        for (int j = 0; j < 13; ++j) {
            auto nums_of_test = nums[i];
            auto nums_of_test_fo_check = nums[i];
            countActions = 0;
            sortFuncsWithCountAction[j](nums_of_test);
            auto sum = countActions;
            result[j].second = check(nums_of_test,nums_of_test_fo_check) && result[j].second;
            result[j].first += sum;
        }
    }
    for (int i = 0; i < 13; ++i) {
        result[i].first /= countMeasuring;
    }
    return result;
}


void genVectors(std::vector<int> &vec5, std::vector<int> &vec4000,
                std::vector<int> &vecSorted, std::vector<int> &vecRevers) {
    vec5.resize(4100);
    vec4000.resize(4100);
    vecSorted.resize(4100);
    vecRevers.resize(4100);
    for (int i = 0; i < 4100; ++i) {
        vec5[i] = rand() % 6;
    }

    for (int i = 0; i < 4100; ++i) {
        vec4000[i] = rand() % 4001;
    }

    for (int i = 0; i < 4100; ++i) {
        vecSorted[i] = i;
    }
    for (int i = 0; i < 200; ++i) {
        int index1 = rand() % 4100;
        int index2 = rand() % 4100;
        int y = vecSorted[index1];
        vecSorted[index1] = vecSorted[index2];
        vecSorted[index2] = y;
    }

    for (int i = 4100 - 1; i >= 0; --i) {
        vecRevers[i] = vecRevers.size() - 1 - i;
    }
}

void outputTable(std::vector<std::vector<std::pair<int, bool>>> tableResults) {
    std::ofstream out("output.txt", std::ios::app);
    out << "\n";
    out << "\n";
    for (int i = 0; i < tableResults.size(); ++i) {
        for (int j = 0; j < 13; ++j) {
            out << tableResults[i][j].first << " " /*<< tableResults[i][j].second << " "*/;
        }
        out << "\n";
    }
    out.close();
}

std::vector<std::vector<int>> getPartVector(std::vector<std::vector<int>> &vec, int count) {
    auto num_measuring = vec.size();
    std::vector<std::vector<int>> data(num_measuring);
    for (int i = 0; i < num_measuring; ++i) {
        for (int j = 0; j < count; ++j) {
            data[i].push_back(vec[i][j]);
        }
    }
    return data;
}

int main() {
    srand(4);

    std::vector<int> v{1,2,5,1,4,9};
    quickSort(v);

    int num_measuring = 10;
    std::vector<std::vector<int>> vec5(num_measuring);
    std::vector<std::vector<int>> vec4000(num_measuring);
    std::vector<std::vector<int>> vecSorted(num_measuring);
    std::vector<std::vector<int>> vecReverse(num_measuring);
    for (int i = 0; i < num_measuring; ++i) {
        genVectors(vec5[i], vec4000[i], vecSorted[i], vecReverse[i]);
    }
    std::vector<std::vector<std::pair<int, bool>>> tableResults;
    //
    std::cout << "time/50-300, 0-5" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vec5, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "time/50-300, 0-4000" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vec4000, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "time/50-300, sorted" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vecSorted, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "time/50-300, reverse" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vecReverse, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "time/100-4100, 0-5" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vec5, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "time/100-4100, 0-4000" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vec4000, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "time/100-4100, sorted" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vecSorted, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "time/100-4100, reverse" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vecReverse, i);
        tableResults.push_back(measureByTime(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //////////////////////////////////
    std::cout << "action/50-300, 0-5" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vec5, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "action/50-300, 0-4000" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vec4000, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "action/50-300, sorted" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vecSorted, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "action/50-300, reverse" << "\n";
    for (int i = 50; i <= 300; i += 50) {
        auto data = getPartVector(vecReverse, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "action/100-4100, 0-5" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vec5, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "action/100-4100, 0-4000" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vec4000, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "action/100-4100, sorted" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vecSorted, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    //
    std::cout << "action/100-4100, reverse" << "\n";
    for (int i = 100; i <= 4100; i += 100) {
        auto data = getPartVector(vecReverse, i);
        tableResults.push_back(measureByAction(data));
    }
    outputTable(tableResults);
    tableResults.clear();
    return 0;
}