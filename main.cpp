#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---------------------- FUNCTION DECLARATIONS ----------------------
void countingSortStable(vector<int>& arr);
void countingSortNonStable(vector<int>& arr);
void countingSortDigit(vector<int>& arr, int exp);
void radixSortLSD(vector<int>& arr);
void bucketSort(vector<float>& arr);
void pigeonholeSort(vector<int>& arr);

vector<int> generateRandomIntArray(int n, int minVal, int maxVal);
vector<int> generateSortedIntArray(int n, int minVal, int maxVal);
vector<int> generateReverseSortedIntArray(int n, int minVal, int maxVal);
vector<int> generateManyDuplicatesArray(int n, int minVal, int maxVal);
vector<float> generateRandomFloatArray(int n);

template <typename Func>
long long measureTimeMs(Func f);

void runIntExperiment(const vector<int>& base, const string& label);


// ---------------------- STABLE COUNTING SORT -----------------------
void countingSortStable(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    vector<int> output(arr.size());

    for (int num : arr)
        count[num - minVal]++;

    for (int i = 1; i < range; ++i)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; --i) {
        int idx = arr[i] - minVal;
        output[count[idx] - 1] = arr[i];
        count[idx]--;
    }

    arr = output;
}


// -------------------- NON-STABLE COUNTING SORT ---------------------
void countingSortNonStable(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);

    for (int num : arr)
        count[num - minVal]++;

    int index = 0;
    for (int i = 0; i < range; ++i) {
        while (count[i]-- > 0)
            arr[index++] = i + minVal;
    }
}


// ----------------- RADIX SORT DIGIT COUNTING SORT ------------------
void countingSortDigit(vector<int>& arr, int exp) {
    vector<int> output(arr.size());
    int count[10] = {0};

    for (int num : arr)
        count[(num / exp) % 10]++;

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}


// --------------------------- LSD RADIX SORT -------------------------
void radixSortLSD(vector<int>& arr) {
    if (arr.empty()) return;

    int maxNum = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxNum / exp > 0; exp *= 10)
        countingSortDigit(arr, exp);
}


// ---------------------------- BUCKET SORT ---------------------------
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 0) return;

    vector<vector<float>> buckets(n);

    for (float num : arr) {
        int idx = (int)(num * n);
        if (idx == n) idx = n - 1;
        buckets[idx].push_back(num);
    }

    for (int i = 0; i < n; ++i)
        sort(buckets[i].begin(), buckets[i].end());

    int index = 0;
    for (int i = 0; i < n; ++i)
        for (float num : buckets[i])
            arr[index++] = num;
}


// --------------------------- PIGEONHOLE SORT ------------------------
void pigeonholeSort(vector<int>& arr) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<vector<int>> holes(range);

    for (int num : arr)
        holes[num - minVal].push_back(num);

    int index = 0;
    for (int i = 0; i < range; ++i)
        for (int num : holes[i])
            arr[index++] = num;
}


// ----------------------- DATA GENERATION HELPERS --------------------
vector<int> generateRandomIntArray(int n, int minVal, int maxVal) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    return arr;
}

vector<int> generateSortedIntArray(int n, int minVal, int maxVal) {
    vector<int> arr = generateRandomIntArray(n, minVal, maxVal);
    sort(arr.begin(), arr.end());
    return arr;
}

vector<int> generateReverseSortedIntArray(int n, int minVal, int maxVal) {
    vector<int> arr = generateSortedIntArray(n, minVal, maxVal);
    reverse(arr.begin(), arr.end());
    return arr;
}

vector<int> generateManyDuplicatesArray(int n, int minVal, int maxVal) {
    vector<int> pool = {minVal, (minVal + maxVal)/2, maxVal};
    vector<int> arr(n);

    for (int i = 0; i < n; ++i)
        arr[i] = pool[rand() % 3];
    return arr;
}

vector<float> generateRandomFloatArray(int n) {
    vector<float> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = (float)rand() / RAND_MAX;
    return arr;
}


// ------------------------- TIMING WRAPPER ---------------------------
template <typename Func>
long long measureTimeMs(Func f) {
    auto start = chrono::steady_clock::now();
    f();
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// -------------------------- EXPERIMENT DRIVER -----------------------
void runIntExperiment(const vector<int>& base, const string& label) {
    cout << "\n=== Scenario: " << label << " ===\n";

    auto a1 = base;
    cout << "Stable Counting Sort:      "
         << measureTimeMs([&]() { countingSortStable(a1); }) << " ms\n";

    auto a2 = base;
    cout << "Non-Stable Counting Sort:  "
         << measureTimeMs([&]() { countingSortNonStable(a2); }) << " ms\n";

    auto a3 = base;
    cout << "LSD Radix Sort:            "
         << measureTimeMs([&]() { radixSortLSD(a3); }) << " ms\n";

    auto a4 = base;
    cout << "Pigeonhole Sort:           "
         << measureTimeMs([&]() { pigeonholeSort(a4); }) << " ms\n";
}


// ------------------------------ MAIN --------------------------------
int main() {
    srand(time(nullptr));

    int n = 100000;
    int minVal = 0;
    int maxVal = 1000;

    auto randomArr  = generateRandomIntArray(n, minVal, maxVal);
    auto sortedArr  = generateSortedIntArray(n, minVal, maxVal);
    auto reverseArr = generateReverseSortedIntArray(n, minVal, maxVal);
    auto dupArr     = generateManyDuplicatesArray(n, minVal, maxVal);

    runIntExperiment(randomArr,  "Random");
    runIntExperiment(sortedArr,  "Already Sorted");
    runIntExperiment(reverseArr, "Reverse Sorted");
    runIntExperiment(dupArr,     "Many Duplicates");

    int nf = 100000;
    auto floatArr = generateRandomFloatArray(nf);

    cout << "\n=== Scenario: Random Floats (Bucket Sort) ===\n";
    cout << "Bucket Sort:               "
         << measureTimeMs([&]() { bucketSort(floatArr); }) << " ms\n";

    return 0;
}
