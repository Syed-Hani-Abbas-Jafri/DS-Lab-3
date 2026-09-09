#include <iostream>
#include <string>
using namespace std;

struct Course {
    int code;
    string classroom;
    string teacher;
    string timing;
};

int linearSearch(Course a[], int n, int key, int &c) {
    c = 0;

    for (int i = 0; i < n; i++) {
        c++;

        if (a[i].code == key)
            return i;
    }

    return -1;
}

int binarySearch(Course a[], int n, int key, int &c) {
    c = 0;

    int l = 0, h = n - 1;

    while (l <= h) {
        c++;

        int m = (l + h) / 2;

        if (a[m].code == key)
            return m;

        if (a[m].code < key)
            l = m + 1;
        else
            h = m - 1;
    }

    return -1;
}

int interpolationSearch(Course a[], int n, int key, int &c) {
    c = 0;

    int l = 0, h = n - 1;

    while (l <= h && key >= a[l].code && key <= a[h].code) {
        c++;

        if (a[l].code == a[h].code) {
            if (a[l].code == key)
                return l;

            return -1;
        }

        int p = l + ((double)(key - a[l].code) /
                     (a[h].code - a[l].code)) * (h - l);

        if (p < l)
            p = l;

        if (p > h)
            p = h;

        if (a[p].code == key)
            return p;

        if (a[p].code < key)
            l = p + 1;
        else
            h = p - 1;
    }

    return -1;
}

void sortData(Course a[], int n) {
    for (int i = 1; i < n; i++) {
        Course x = a[i];
        int j = i - 1;

        while (j >= 0 && a[j].code > x.code) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = x;
    }
}

void showResult(string name, int idx, Course a[], int c) {
    cout << name << " | Comparisons: " << c;

    if (idx != -1) {
        cout << " | Classroom: " << a[idx].classroom
             << " | Teacher: " << a[idx].teacher
             << " | Timing: " << a[idx].timing << "\n";
    }
    else {
        cout << " | Not found\n";
    }
}

int main() {
    int n;

    cout << "Classroom Timetable Search\n\n";

    cout << "Enter number of courses: ";
    cin >> n;

    while (n < 1 || n > 50) {
        cout << "Enter a number between 1 and 50: ";
        cin >> n;
    }

    Course a[50];

    for (int i = 0; i < n; i++) {
        cout << "\nCourse " << i + 1 << "\n";

        cout << "Course code: ";
        cin >> a[i].code;

        cin.ignore();

        cout << "Classroom: ";
        getline(cin, a[i].classroom);

        cout << "Teacher: ";
        getline(cin, a[i].teacher);

        cout << "Timing: ";
        getline(cin, a[i].timing);
    }

    Course sorted[50];

    for (int i = 0; i < n; i++)
        sorted[i] = a[i];

    sortData(sorted, n);

    Course uniform[50];

    int start = sorted[0].code;

    for (int i = 0; i < n; i++) {
        uniform[i] = sorted[i];
        uniform[i].code = start + i * 10;
    }

    int key;

    cout << "\nEnter course code to search: ";
    cin >> key;

    int idx, c;

    cout << "\nUnsorted Data\n";

    idx = linearSearch(a, n, key, c);
    showResult("Linear Search", idx, a, c);

    cout << "Binary Search is not applied to unsorted data.\n";
    cout << "Interpolation Search is not applied to unsorted data.\n";

    cout << "\nSorted Data\n";

    idx = linearSearch(sorted, n, key, c);
    showResult("Linear Search", idx, sorted, c);

    idx = binarySearch(sorted, n, key, c);
    showResult("Binary Search", idx, sorted, c);

    idx = interpolationSearch(sorted, n, key, c);
    showResult("Interpolation Search", idx, sorted, c);

    cout << "\nUniformly Distributed Data\n";

    int uKey;

    cout << "Uniform course codes are from "
         << uniform[0].code << " to "
         << uniform[n - 1].code << ".\n";

    cout << "Enter course code to search in uniform data: ";
    cin >> uKey;

    idx = linearSearch(uniform, n, uKey, c);
    showResult("Linear Search", idx, uniform, c);

    idx = binarySearch(uniform, n, uKey, c);
    showResult("Binary Search", idx, uniform, c);

    idx = interpolationSearch(uniform, n, uKey, c);
    showResult("Interpolation Search", idx, uniform, c);

    cout << "\nSummary\n";

    cout << "Unsorted data: Linear Search is most suitable because it does not require sorted data.\n";

    cout << "Sorted data: Binary Search is suitable because it repeatedly divides the search range.\n";

    cout << "Uniformly distributed data: Interpolation Search is most suitable because it estimates the position of the required value using its numerical range.\n";

    return 0;
}
