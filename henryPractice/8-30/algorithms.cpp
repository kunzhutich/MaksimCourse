#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> bubbleSort(vector<int>& arr) {
    bool swapped = true;
    int n = arr.size();

    while (swapped) {   
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }

        n--;
    }

    return arr;
}

vector<int> selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        int smallest = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[smallest]) {
                smallest = j;
            }
        }
        
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
    }

    return arr;
}

vector<int> insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    return arr;
}

vector<int> merge(vector<int>& left, vector<int>& right) {
    vector<int> result;
    result.reserve(left.size() + right.size());

    while (!left.empty() && !right.empty()){
        if (left[0] <= right[0]) {
            result.push_back(left[0]);
            left.erase(left.begin());
        } else {
            result.push_back(right[0]);
            right.erase(right.begin());
        }
    }

    if (!left.empty()) {
        for (int num : left){
            result.push_back(num);
        }
    }
    
    if (!right.empty()) {
        for (int num : right){
            result.push_back(num);
        }
    }

    return result;
}

vector<int> mergeSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return arr;
    }

    vector<int> half1;
    for(int i = 0; i < n/2; i++) {
        half1.push_back(arr[i]);
    }
    
    vector<int> half2;
    for(int i = n/2; i < n; i++) {
        half2.push_back(arr[i]);
    }

    half1 = mergeSort(half1);
    half2 = mergeSort(half2);

    return merge(half1, half2);
}

vector<int> qSort(vector<int>& less, vector<int>& equals, vector<int>& greater) {
    vector<int> result;
    result.reserve(less.size() + equals.size() + greater.size());

    for(int num : less) {
        result.push_back(num);
    }
    for(int num : equals) {
        result.push_back(num);
    }
    for (int num : greater) {
        result.push_back(num);
    }

    return result;
}

vector<int> quickSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return arr;
    }

    int pivot = arr[n/2];

    vector<int> less;
    vector<int> equals;
    vector<int> greater;

    for(int i = 0; i < n; i++) {
        if (arr[i] < pivot) {
            less.push_back(arr[i]);
        } else if (arr[i] == pivot) {
            equals.push_back(arr[i]);
        } else {
            greater.push_back(arr[i]);
        }
    }

    less = quickSort(less);
    greater = quickSort(greater);

    return qSort(less, equals, greater);
}

string print(const vector<int>& vector) {
    string str = "{";
    for (int i = 0; i < vector.size(); ++i) {
        str += to_string(vector[i]);
        if (i < vector.size() - 1) {
            str += ", ";
        }
    }
    str += "}";
    return str;
}

int main() {
    vector<int> vec1 = {4, 3, 7, 9, 2, 1, 8, 6, 5};
    cout << "Before vec1: " << print(vec1) << endl;
    // cout << "After vec1: " << print(bubbleSort(vec1)) << endl;
    // cout << "After vec1: " << print(selectionSort(vec1)) << endl;
    // cout << "After vec1: " << print(insertionSort(vec1)) << endl;
    // cout << "After vec1: " << print(mergeSort(vec1)) << endl;
    cout << "After vec1: " << print(quickSort(vec1)) << endl;
}