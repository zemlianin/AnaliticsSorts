#include "iostream"
#include <vector>

int64_t countActions;

void selectSortAct(std::vector<int> &v) {
    int t = 0;
    int i, j, index;
    countActions++;
    for (i = 0; i < v.size() - 1; i++) {
        countActions += 2;
        countActions++;
        index = i;
        for (j = i + 1; j < v.size(); j++) {
            countActions += 3;
            countActions++;
            if (v[j] < v[index]) {
                countActions++;
                index = j;
            }
        }
        countActions++;
        if (index != i) {
            countActions++;
            int t = v[index];
            countActions++;
            v[index] = v[i];
            countActions++;
            v[i] = t;
        }
    }
}

void bubbleSortAct(std::vector<int> &v) {
    int i, j;
    for (i = 0; i < v.size() - 1; i++) {
        countActions += 2;
        for (j = 0; j < v.size() - i - 1; j++) {
            countActions += 2;
            countActions++;
            if (v[j] > v[j + 1]) {
                countActions += 3;
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

void bubbleA12SortAct(std::vector<int> &vec) {
    countActions++;
    int n = static_cast<int>(vec.size());
    countActions++;
    int t = n - 1;
    while (t != 0) {
        countActions++;
        countActions++;
        int t2 = t;
        for (int k = 0; k < t2; ++k) {
            countActions += 2;
            countActions++;
            if (vec[k] > vec[k + 1]) {
                countActions += 3;
                std::swap(vec[k], vec[k + 1]);
                countActions++;
                t = k + 1;
            }
        }
        countActions++;
        t--;
    }
}

void bubbleA1SortAct(std::vector<int> &v) {
    int i, j, k = 0;
    for (i = 0; i < v.size() - 1; i++) {
        countActions += 2;
        for (j = 0; j < v.size() - i - 1; j++) {
            countActions += 2;
            countActions++;
            if (v[j] > v[j + 1]) {
                countActions += 3;
                std::swap(v[j], v[j + 1]);
                countActions++;
                k = 1;
            }
        }
        countActions++;
        if (k == 0) {
            return;
        }
    }
}

void insertSortAct(std::vector<int> &v) {
    for (size_t j = 1; j < v.size(); j++) {
        countActions += 2;
        countActions++;
        int val = v[j];
        countActions++;
        int i = j - 1;

        while (i >= 0 && v[i] > val) {
            countActions += 2;
            countActions++;
            v[i + 1] = v[i];
            countActions++;
            i--;
        }
        countActions++;
        v[i + 1] = val;
    }
}

size_t binSearchAct(std::vector<int> vec, int val, int l, int r) {
    countActions++;
    if (r <= l) {
        countActions++;
        if (val > vec[l]) {
            countActions++;
            return l + 1;
        } else {
            return l;
        }
    }
    countActions++;
    int m = (l + r) / 2;
    countActions++;
    if (val == vec[m]) {
        countActions++;
        return m + 1;
    }
    countActions++;
    if (val > vec[m]) {
        countActions++;
        return binSearchAct(vec, val, m + 1, r);
    }
    countActions++;
    return binSearchAct(vec, val, l, m - 1);
}

void insertBinSortAct(std::vector<int> &v) {
    int i, j;
    int position;
    int elem;

    for (i = 1; i < v.size(); ++i) {
        countActions += 2;
        countActions++;
        j = i - 1;
        countActions++;
        elem = v[i];
        countActions++;
        position = static_cast<int>(binSearchAct(v, elem, 0, j));

        while (j >= position) {
            countActions++;
            v[j + 1] = v[j];
            countActions++;
            j--;
        }
        countActions++;
        v[j + 1] = elem;
    }
}

void countSortAct(std::vector<int> &vec) {
    countActions++;
    int size = static_cast<int>(vec.size());
    countActions++;
    int max_dig = 4101;
    std::vector<int> result(size);
    std::vector<int> c(max_dig + 1);

    for (int i = 0; i < size; ++i) {
        countActions += 2;
        countActions++;
        ++c[vec[i]];
    }
    for (int i = 1; i <= max_dig; ++i) {
        countActions += 2;
        countActions++;
        c[i] += c[i - 1];
    }

    for (int i = static_cast<int>(size) - 1; i >= 0; i--) {
        countActions += 3;
        countActions += 3;
        result[c[vec[i]] - 1] = vec[i];
        countActions += 1;
        c[vec[i]]--;
    }
    for (int i = 0; i < size; ++i) {
        countActions++;
        vec[i] = result[i];
    }
}

int getMaxAct(std::vector<int> &vec) {
    countActions++;
    int mx = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        countActions++;
        countActions++;
        if (vec[i] > mx) {
            countActions++;
            mx = vec[i];
        }
    }
    return mx;
}

void countSortRadixAct(std::vector<int> &vec, int razr_num) {
    countActions++;
    std::vector<int> result(vec.size());
    countActions++;
    std::vector<int> count(10);

    for (size_t i = 0; i < vec.size(); i++) {
        countActions += 2;
        countActions += 4;
        count[(vec[i] / razr_num) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        countActions += 2;
        countActions++;
        count[i] += count[i - 1];
    }

    for (int i = static_cast<int>(vec.size()) - 1; i >= 0; i--) {
        countActions += 5;
        countActions += 4;
        result[count[(vec[i] / razr_num) % 10] - 1] = vec[i];
        countActions += 3;
        count[(vec[i] / razr_num) % 10]--;
    }

    for (int i = 0; i < vec.size(); i++) {
        countActions += 2;
        countActions++;
        vec[i] = result[i];
    }
}

void radixSortAct(std::vector<int> &vec) {
    countActions += 2;
    int n = static_cast<int>(vec.size());
    countActions++;
    int m = getMaxAct(vec);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        countActions += 3;
        countSortRadixAct(vec, exp);
    }
}

void mergeAct(std::vector<int> &vec, int left, int mid, int right) {
    countActions += 2;
    int sizeSubVecOne = mid - left + 1;
    countActions++;
    int sizeSubVecTwo = right - mid;

    std::vector<int> leftArray(sizeSubVecOne);
    std::vector<int> rightArray(sizeSubVecTwo);

    for (int i = 0; i < sizeSubVecOne; i++) {
        countActions += 2;
        countActions += 2;
        leftArray[i] = vec[left + i];
    }
    for (int j = 0; j < sizeSubVecTwo; j++) {
        countActions += 3;
        rightArray[j] = vec[mid + 1 + j];
    }

    int indexOfSubVecOne = 0;
    int indexOfSubVecTwo = 0;
    int indexOfMergedVec = left;

    while (indexOfSubVecOne < sizeSubVecOne && indexOfSubVecTwo < sizeSubVecTwo) {
        countActions += 3;
        countActions += 2;
        if (leftArray[indexOfSubVecOne] <= rightArray[indexOfSubVecTwo]) {
            countActions++;
            vec[indexOfMergedVec] = leftArray[indexOfSubVecOne];
            countActions++;
            indexOfSubVecOne++;
        } else {
            countActions++;
            vec[indexOfMergedVec] = rightArray[indexOfSubVecTwo];
            countActions++;
            indexOfSubVecTwo++;
        }
        countActions++;
        indexOfMergedVec++;
    }
    countActions++;
    while (indexOfSubVecOne < sizeSubVecOne) {
        countActions += 3;
        vec[indexOfMergedVec] = leftArray[indexOfSubVecOne];
        countActions++;
        indexOfSubVecOne++;
        countActions++;
        indexOfMergedVec++;
    }
    countActions++;
    while (indexOfSubVecTwo < sizeSubVecTwo) {
        countActions += 2;
        vec[indexOfMergedVec] = rightArray[indexOfSubVecTwo];
        countActions++;
        indexOfSubVecTwo++;
        countActions++;
        indexOfMergedVec++;
    }
}


void mergeSortWithBorderAct(std::vector<int> &vec, int left, int right) {
    countActions++;
    if (left >= right) {
        return;
    }
    countActions += 4;
    auto mid = left + (right - left) / 2;
    mergeSortWithBorderAct(vec, left, mid);
    countActions++;
    mergeSortWithBorderAct(vec, mid + 1, right);
    mergeAct(vec, left, mid, right);
}

void static mergeSortAct(std::vector<int> &vec) {
    countActions += 2;
    mergeSortWithBorderAct(vec, 0, static_cast<int>(vec.size()) - 1);
}


int partitionAct(std::vector<int> &vec, int low, int high) {
    countActions += 2;
    int pivot = vec[low];
    countActions++;
    int i = (low - 1);
    for (int j = low+1; j <= high; j++) {
        countActions += 2;
        countActions++;
        if (vec[j] < pivot) {
            countActions++;
            i++;
            countActions += 3;
            std::swap(vec[i], vec[j]);
        }
    }
    countActions += 3;
    std::swap(vec[i + 1], vec[high]);
    countActions++;
    return (i + 1);
}

void quickSortWithBorderAct(std::vector<int> &vec, int left, int right) {
    countActions++;
    if (left < right) {
        countActions++;
        int pivot_index = partitionAct(vec, left, right);
        countActions++;
        quickSortWithBorderAct(vec, left, pivot_index - 1);
        countActions++;
        quickSortWithBorderAct(vec, pivot_index + 1, right);
    }
}

void quickSortAct(std::vector<int> &vec) {
    countActions+=2;
    quickSortWithBorderAct(vec, 0, static_cast<int>(vec.size()) - 1);
}

void heapifyAct(std::vector<int> &numbers, size_t n, size_t i) {
    countActions += 2;
    size_t left_child = 2 * i + 1;
    countActions += 2;
    size_t right_child = 2 * i + 2;
    countActions += 2;
    size_t largest_child = i;
    int temp;
    countActions += 2;
    if (left_child < n && numbers[left_child] > numbers[largest_child]) {
        largest_child = left_child;
    }
    countActions += 2;
    if (right_child < n && numbers[right_child] > numbers[largest_child]) {
        largest_child = right_child;
    }
    countActions++;
    if (largest_child != i) {
        countActions++;
        temp = numbers[i];
        countActions++;
        numbers[i] = numbers[largest_child];
        countActions++;
        numbers[largest_child] = temp;

        heapifyAct(numbers, n, largest_child);
    }
}

void heapSortAct(std::vector<int> &numbers) {
    countActions += 2;
    int size = static_cast<int>(numbers.size());
    for (int i = size / 2 - 1; i >= 0; i--) {
        countActions += 4;
        heapifyAct(numbers, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        countActions += 2;
        countActions++;
        int val = numbers[0];
        countActions++;
        numbers[0] = numbers[i];
        countActions++;
        numbers[i] = val;

        heapifyAct(numbers, i, 0);
    }
}

void shellSortShellSequenceAct(std::vector<int> &vec) {
    countActions += 2;
    int n = static_cast<int>(vec.size());
    for (int step = n / 2; step > 0; step /= 2) {
        countActions += 3;
        for (int i = step; i < n; i += 1) {
            countActions += 2;
            countActions++;
            int temp = vec[i];
            int j;
            for (j = i; j >= step && vec[j - step] > temp; j -= step) {
                countActions += 5;
                countActions++;
                vec[j] = vec[j - step];
            }
            countActions++;
            vec[j] = temp;
        }
    }
}

void shellSortCiuraSequenceAct(std::vector<int> &vec) {
    countActions += 3;
    int n = static_cast<int>(vec.size());
    countActions += 2;
    std::vector<int> ciura_sequence = {-1, 1, 4, 10, 23, 57, 132, 301, 701, 1750, 3937, 8853, 19930};
    countActions += n - 1;
    auto bound = std::lower_bound(ciura_sequence.begin(), ciura_sequence.end(), n - 1);
    for (auto step = bound; step != ciura_sequence.begin(); --step) {
        countActions += 2;
        for (int i = *step; i < n; i += 1) {
            countActions += 2;
            countActions++;
            int temp = vec[i];
            int j;
            for (j = i; j >= *step && vec[j - *step] > temp; j -= *step) {
                countActions += 3;
                countActions++;
                vec[j] = vec[j - *step];
            }
            countActions++;
            vec[j] = temp;
        }
    }
}


