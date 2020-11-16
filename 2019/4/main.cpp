#include <iostream>
#include <string>
#include <vector>

using namespace std; 

const int R1 = 235741;
const int R2 = 706948;

vector<int> integerToArray(int x)
{
    vector<int> arr;
    while (true)
    {
    arr.insert(arr.begin(), x % 10);
    x /= 10;
    if (x == 0)
        return arr;
    }
}

bool has_double_digits(int number) {
    vector<int> arr = integerToArray(number);
    return arr[0] == arr[1] && arr[1] != arr[2]
        || arr[1] == arr[2] && arr[0] != arr[1] && arr[2] != arr[3]
        || arr[2] == arr[3] && arr[1] != arr[2] && arr[3] != arr[4]
        || arr[3] == arr[4] && arr[2] != arr[3] && arr[4] != arr[5]
        || arr[4] == arr[5] && arr[3] != arr[4];
}

bool increasing_digits(int number) {
    vector<int> arr = integerToArray(number);
    return arr[0] <= arr[1] 
        && arr[1] <= arr[2]
        && arr[2] <= arr[3]
        && arr[3] <= arr[4]
        && arr[4] <= arr[5];
}

bool test(int number, int r1, int r2) {
    if (number < r1) {
        return false;
    }
    if (number > r2) {
        return false;
    }
    if (!has_double_digits(number)) {
        return false;
    }
    if (!increasing_digits(number)) {
        return false;
    }
    return true;
}

int main() {
    assert(test(223450, 0, INT_MAX) == false);
    assert(test(123789, 0, INT_MAX) == false);
    assert(increasing_digits(123456) == true);
    assert(increasing_digits(123454) == false);
    assert(test(112233, 0, INT_MAX) == true);
    assert(test(123444, 0, INT_MAX) == false);
    assert(test(111122, 0, INT_MAX) == true);

    int valid = 0;
    for (int i = R1; i <= R2; i++) {
        if (test(i, R1, R2)) {
            valid++;
        }
    }

    std::cout << valid << std::endl;
    return 0;
}