#include "iostream"
#include <vector>

void selectSort(std::vector<int> &v) {
    int t = 0;
    int i, j, index;
    for (i = 0; i < v.size() - 1; i++) {
        index = i;
        for (j = i + 1; j < v.size(); j++) {
            if (v[j] < v[index]) {
                index = j;
            }
        }

        if (index != i) {
            int t = v[index];
            v[index] = v[i];
            v[i] = t;
        }
    }
}

void bubbleSort(std::vector<int> &v) {
    int i, j;
    for (i = 0; i < v.size() - 1; i++) {
        for (j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

void bubbleA12Sort(std::vector<int> &vec) {
    int n = static_cast<int>(vec.size());
    int t = n - 1;
    while (t != 0) {
        int t2 = t;
        for (int k = 0; k < t2; ++k) {
            if (vec[k] > vec[k + 1]) {
                std::swap(vec[k], vec[k + 1]);
                t = k + 1;
            }
        }
        t--;
    }
}

void bubbleA1Sort(std::vector<int> &v) {
    int i, j, k = 0;
    for (i = 0; i < v.size() - 1; i++) {
        for (j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                k = 1;
            }
        }
        if (k == 0) {
            return;
        }
    }
}

void insertSort(std::vector<int> &v) {
    for (size_t j = 1; j < v.size(); j++) {
        int val = v[j];
        int i = j - 1;

        while (i >= 0 && v[i] > val) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = val;
    }
}

size_t binSearch(std::vector<int> vec, int val, int l, int r) {
    if (r <= l) {
        if (val > vec[l]) {
            return l + 1;
        } else {
            return l;
        }
    }

    int m = (l + r) / 2;

    if (val == vec[m]) {
        return m + 1;
    }

    if (val > vec[m]) {
        return binSearch(vec, val, m + 1, r);
    }
    return binSearch(vec, val, l, m - 1);
}

void insertBinSort(std::vector<int> &v) {
    int i, j;
    int position;
    int elem;

    for (i = 1; i < v.size(); ++i) {
        j = i - 1;
        elem = v[i];

        position = static_cast<int>(binSearch(v, elem, 0, j));

        while (j >= position) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = elem;
    }
}

void countSort(std::vector<int> &vec) {
    int size = static_cast<int>(vec.size());
    int max_dig = 4101;
    std::vector<int> result(size);
    std::vector<int> c(max_dig + 1);

    for (int i = 0; i < size; ++i) {
        ++c[vec[i]];
    }
    for (int i = 1; i <= max_dig; ++i) {
        c[i] += c[i - 1];
    }

    for (int i = static_cast<int>(size) - 1; i >= 0; i--) {
        result[c[vec[i]] - 1] = vec[i];
        c[vec[i]]--;
    }
    for (int i = 0; i < size; ++i) {
        vec[i] = result[i];
    }
}

int getMax(std::vector<int> &vec) {
    int mx = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > mx) {
            mx = vec[i];
        }
    }
    return mx;
}

void countSortRadix(std::vector<int> &vec, int razr_num) {
    std::vector<int> result(vec.size());
    std::vector<int> count(10);

    for (size_t i = 0; i < vec.size(); i++) {
        count[(vec[i] / razr_num) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = static_cast<int>(vec.size()) - 1; i >= 0; i--) {
        result[count[(vec[i] / razr_num) % 10] - 1] = vec[i];
        count[(vec[i] / razr_num) % 10]--;
    }

    for (int i = 0; i < vec.size(); i++) {
        vec[i] = result[i];
    }
}

void radixSort(std::vector<int> &vec) {
    int n = static_cast<int>(vec.size());
    int m = getMax(vec);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSortRadix(vec, exp);
    }
}

void merge(std::vector<int> &vec, int left, int mid, int right) {
    int sizeSubVecOne = mid - left + 1;
    int sizeSubVecTwo = right - mid;

    std::vector<int> leftArray(sizeSubVecOne);
    std::vector<int> rightArray(sizeSubVecTwo);

    for (int i = 0; i < sizeSubVecOne; i++) {
        leftArray[i] = vec[left + i];
    }
    for (int j = 0; j < sizeSubVecTwo; j++) {
        rightArray[j] = vec[mid + 1 + j];
    }

    int indexOfSubVecOne = 0;
    int indexOfSubVecTwo = 0;
    int indexOfMergedVec = left;

    while (indexOfSubVecOne < sizeSubVecOne && indexOfSubVecTwo < sizeSubVecTwo) {
        if (leftArray[indexOfSubVecOne] <= rightArray[indexOfSubVecTwo]) {
            vec[indexOfMergedVec] = leftArray[indexOfSubVecOne];
            indexOfSubVecOne++;
        } else {
            vec[indexOfMergedVec] = rightArray[indexOfSubVecTwo];
            indexOfSubVecTwo++;
        }
        indexOfMergedVec++;
    }

    while (indexOfSubVecOne < sizeSubVecOne) {
        vec[indexOfMergedVec] = leftArray[indexOfSubVecOne];
        indexOfSubVecOne++;
        indexOfMergedVec++;
    }

    while (indexOfSubVecTwo < sizeSubVecTwo) {
        vec[indexOfMergedVec] = rightArray[indexOfSubVecTwo];
        indexOfSubVecTwo++;
        indexOfMergedVec++;
    }
}


void mergeSortWithBorder(std::vector<int> &vec, int left, int right) {
    if (left >= right) {
        return;
    }
    auto mid = left + (right - left) / 2;
    mergeSortWithBorder(vec, left, mid);
    mergeSortWithBorder(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

void static mergeSort(std::vector<int> &vec) {
    mergeSortWithBorder(vec, 0, static_cast<int>(vec.size()) - 1);
}


int partition(std::vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] < pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quickSortWithBorder(std::vector<int> &vec, int left, int right) {
    if (left < right) {
        int pivot_index = partition(vec, left, right);
        quickSortWithBorder(vec, left, pivot_index - 1);
        quickSortWithBorder(vec, pivot_index + 1, right);
    }
}

void quickSort(std::vector<int> &vec) {
    quickSortWithBorder(vec, 0, static_cast<int>(vec.size()) - 1);
}

void heapify(std::vector<int> &numbers, size_t n, size_t i) {
    size_t left_child = 2 * i + 1;
    size_t right_child = 2 * i + 2;
    size_t largest_child = i;
    int temp;
    if (left_child < n && numbers[left_child] > numbers[largest_child]) {
        largest_child = left_child;
    }
    if (right_child < n && numbers[right_child] > numbers[largest_child]) {
        largest_child = right_child;
    }
    if (largest_child != i) {
        temp = numbers[i];
        numbers[i] = numbers[largest_child];
        numbers[largest_child] = temp;

        heapify(numbers, n, largest_child);
    }
}

void heapSort(std::vector<int> &numbers) {
    int size = static_cast<int>(numbers.size());

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(numbers, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        int val = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = val;

        heapify(numbers, i, 0);
    }
}

void shellSortShellSequence(std::vector<int> &vec) {
    int n = static_cast<int>(vec.size());
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i += 1) {
            int temp = vec[i];
            int j;
            for (j = i; j >= step && vec[j - step] > temp; j -= step) {
                vec[j] = vec[j - step];
            }
            vec[j] = temp;
        }
    }
}

void shellSortCiuraSequence(std::vector<int> &vec) {
    int n = static_cast<int>(vec.size());
    std::vector<int> ciura_sequence = {-1, 1, 4, 10, 23, 57, 132, 301, 701, 1750, 3937, 8853, 19930};
    auto bound = std::lower_bound(ciura_sequence.begin(), ciura_sequence.end(), n - 1);
    for (auto step = bound; step != ciura_sequence.begin(); --step) {
        for (int i = *step; i < n; i += 1) {
            int temp = vec[i];
            int j;
            for (j = i; j >= *step && vec[j - *step] > temp; j -= *step) {
                vec[j] = vec[j - *step];
            }
            vec[j] = temp;
        }
    }
}


