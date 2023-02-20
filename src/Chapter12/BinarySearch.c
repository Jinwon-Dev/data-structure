#include <stdio.h>

int binarySearchRecursive(int values[], int start, int end, int key) {
    int ret = -1;
    int middle = 0;

    if (start <= end) {
        middle = (start + end) / 2;
        if (key == values[middle]) {
            ret = middle;
        } else if (key < values[middle]) {
            ret = binarySearchRecursive(values, start, middle - 1, key);
        } else {
            ret = binarySearchRecursive(values, middle + 1, end, key);
        }
    }

    return ret;
}

int main(int argc, const char *argv[]) {
    int key = 0;
    int index = 0;
    int ascSortedArray[] = {10, 20, 50, 60, 70, 80};

    key = 60;
    index = binarySearchRecursive(ascSortedArray, 0, 5, key);
    if (index >= 0) {
        printf("키-%d,위치-%d\n", key, index);
    } else {
        printf("키-%d,검색 실패\n", key);
    }

    key = 65;
    index = binarySearchRecursive(ascSortedArray, 0, 5, key);
    if (index >= 0) {
        printf("키-%d,위치-%d\n", key, index);
    } else {
        printf("키-%d,검색 실패\n", key);
    }

    return 0;
}
