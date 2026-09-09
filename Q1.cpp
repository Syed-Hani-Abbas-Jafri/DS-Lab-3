#include <iostream>
#include <string>
using namespace std;

struct Activity {
    string name;
    int time;
};

void bubbleSort(Activity a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].time < a[j + 1].time)
                swap(a[j], a[j + 1]);
        }
    }
}

void selectionSort(Activity a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int p = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j].time > a[p].time)
                p = j;
        }

        swap(a[i], a[p]);
    }
}

void insertionSort(Activity a[], int n) {
    for (int i = 1; i < n; i++) {
        Activity x = a[i];
        int j = i - 1;

        while (j >= 0 && a[j].time < x.time) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = x;
    }
}

void shellSort(Activity a[], int n) {
    for (int g = n / 2; g > 0; g /= 2) {
        for (int i = g; i < n; i++) {
            Activity x = a[i];
            int j = i;

            while (j >= g && a[j - g].time < x.time) {
                a[j] = a[j - g];
                j -= g;
            }

            a[j] = x;
        }
    }
}

void combSort(Activity a[], int n) {
    int g = n;
    bool changed = true;

    while (g != 1 || changed) {
        g = (g * 10) / 13;

        if (g < 1)
            g = 1;

        changed = false;

        for (int i = 0; i + g < n; i++) {
            if (a[i].time < a[i + g].time) {
                swap(a[i], a[i + g]);
                changed = true;
            }
        }
    }
}

void show(Activity a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i].name;

        if (i != n - 1)
            cout << ", ";
    }

    cout << "\n";
}

void timeInfo(Activity a[], int n) {
    char ch;

    cout << "How much time? (y/n): ";
    cin >> ch;

    if (ch != 'y' && ch != 'Y')
        return;

    cin.ignore();

    string key;

    cout << "Enter activity name: ";
    getline(cin, key);

    for (int i = 0; i < n; i++) {
        if (a[i].name == key) {
            cout << "Time spent on " << key << ": "
                 << a[i].time << " hours\n";
            return;
        }
    }

    cout << "Activity not found\n";
}

void runSort(int ch, Activity a[], int n) {
    Activity b[50];

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    string name;

    if (ch == 1) {
        bubbleSort(b, n);
        name = "Bubble Sort";
    }
    else if (ch == 2) {
        selectionSort(b, n);
        name = "Selection Sort";
    }
    else if (ch == 3) {
        insertionSort(b, n);
        name = "Insertion Sort";
    }
    else if (ch == 4) {
        shellSort(b, n);
        name = "Shell Sort";
    }
    else if (ch == 5) {
        combSort(b, n);
        name = "Comb Sort";
    }
    else {
        return;
    }

    cout << "\n" << name << " result:\n";
    show(b, n);
    timeInfo(b, n);
}

void sortMenu(Activity a[], int n) {
    int ch;

    cout << "\n1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "4. Shell Sort\n";
    cout << "5. Comb Sort\n";
    cout << "6. Select Multiple\n";
    cout << "7. All\n";
    cout << "Choice: ";
    cin >> ch;

    if (ch >= 1 && ch <= 5) {
        runSort(ch, a, n);
    }
    else if (ch == 6) {
        int k;

        cout << "How many algorithms? ";
        cin >> k;

        for (int i = 0; i < k; i++) {
            int x;

            cout << "Enter algorithm number (1-5): ";
            cin >> x;

            runSort(x, a, n);
        }
    }
    else if (ch == 7) {
        for (int i = 1; i <= 5; i++)
            runSort(i, a, n);
    }
}

int linearSearch(Activity a[], int n, string key, int &c) {
    c = 0;

    for (int i = 0; i < n; i++) {
        c++;

        if (a[i].name == key)
            return i;
    }

    return -1;
}

int binarySearch(Activity a[], int n, string key, int &c) {
    c = 0;

    int l = 0;
    int h = n - 1;

    while (l <= h) {
        c++;

        int m = (l + h) / 2;

        if (a[m].name == key)
            return m;

        if (a[m].name < key)
            l = m + 1;
        else
            h = m - 1;
    }

    return -1;
}

int interpolationSearch(Activity a[], int n, int key, int &c) {
    c = 0;

    int l = 0;
    int h = n - 1;

    while (l <= h && key >= a[l].time && key <= a[h].time) {
        c++;

        if (a[l].time == a[h].time) {
            if (a[l].time == key)
                return l;

            return -1;
        }

        int p = l + ((double)(key - a[l].time) /
                     (a[h].time - a[l].time)) * (h - l);

        if (p < l)
            p = l;

        if (p > h)
            p = h;

        if (a[p].time == key)
            return p;

        if (a[p].time < key)
            l = p + 1;
        else
            h = p - 1;
    }

    return -1;
}

void searchActivity(Activity a[], int n) {
    cin.ignore();

    string key;

    cout << "\nEnter activity to search: ";
    getline(cin, key);

    Activity b[50];

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (b[j].name > b[j + 1].name)
                swap(b[j], b[j + 1]);
        }
    }

    int ch;

    cout << "\n1. Linear Search\n";
    cout << "2. Binary Search\n";
    cout << "3. Interpolation Search\n";
    cout << "4. All\n";
    cout << "5. Any Two\n";
    cout << "Choice: ";
    cin >> ch;

    int idx, c;

    if (ch == 1) {
        idx = linearSearch(a, n, key, c);

        cout << "Linear Search: ";

        if (idx != -1)
            cout << "Preference found: " << a[idx].name
                 << " | Comparisons: " << c << "\n";
        else
            cout << "Not found | Comparisons: " << c << "\n";

        if (idx != -1)
            timeInfo(a, n);
    }

    else if (ch == 2) {
        idx = binarySearch(b, n, key, c);

        cout << "Binary Search: ";

        if (idx != -1)
            cout << "Preference found: " << b[idx].name
                 << " | Comparisons: " << c << "\n";
        else
            cout << "Not found | Comparisons: " << c << "\n";

        if (idx != -1)
            timeInfo(b, n);
    }

    else if (ch == 3) {
        int t;

        cout << "Enter time to search for interpolation search: ";
        cin >> t;

        Activity u[50];

        for (int i = 0; i < n; i++)
            u[i] = a[i];

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (u[j].time > u[j + 1].time)
                    swap(u[j], u[j + 1]);
            }
        }

        idx = interpolationSearch(u, n, t, c);

        cout << "Interpolation Search: ";

        if (idx != -1)
            cout << "Preference found: " << u[idx].name
                 << " | Comparisons: " << c << "\n";
        else
            cout << "Not found | Comparisons: " << c << "\n";
    }

    else if (ch == 4) {
        idx = linearSearch(a, n, key, c);

        cout << "Linear Search: ";

        if (idx != -1)
            cout << "Preference found: " << a[idx].name
                 << " | Comparisons: " << c << "\n";
        else
            cout << "Not found | Comparisons: " << c << "\n";

        idx = binarySearch(b, n, key, c);

        cout << "Binary Search: ";

        if (idx != -1)
            cout << "Preference found: " << b[idx].name
                 << " | Comparisons: " << c << "\n";
        else
            cout << "Not found | Comparisons: " << c << "\n";

        if (idx != -1)
            timeInfo(b, n);

        cout << "Interpolation Search requires a numeric key such as time.\n";
    }

    else if (ch == 5) {
        for (int i = 0; i < 2; i++) {
            int x;

            cout << "Enter technique number (1-3): ";
            cin >> x;

            if (x == 1) {
                idx = linearSearch(a, n, key, c);
                cout << "Linear Search: ";

                if (idx != -1)
                    cout << "Preference found: " << a[idx].name
                         << " | Comparisons: " << c << "\n";
                else
                    cout << "Not found | Comparisons: " << c << "\n";
            }

            else if (x == 2) {
                idx = binarySearch(b, n, key, c);
                cout << "Binary Search: ";

                if (idx != -1)
                    cout << "Preference found: " << b[idx].name
                         << " | Comparisons: " << c << "\n";
                else
                    cout << "Not found | Comparisons: " << c << "\n";
            }

            else if (x == 3) {
                cout << "Interpolation Search requires a numeric key such as time.\n";
            }
        }
    }
}

void mostTime(Activity a[], int n) {
    int p = 0;

    for (int i = 1; i < n; i++) {
        if (a[i].time > a[p].time)
            p = i;
    }

    cout << "\nYou usually spend the most time on: "
         << a[p].name << "\n";

    char ch;

    cout << "How much time? (y/n): ";
    cin >> ch;

    if (ch == 'y' || ch == 'Y') {
        cout << "Total time spent on "
             << a[p].name << ": "
             << a[p].time << " hours\n";
    }
}

void searchMenu(Activity a[], int n) {
    int ch;

    cout << "\n1. Search for Activity\n";
    cout << "2. Find Activity with Most Time\n";
    cout << "3. Exit\n";
    cout << "Choice: ";
    cin >> ch;

    if (ch == 1)
        searchActivity(a, n);
    else if (ch == 2)
        mostTime(a, n);
}

int main() {
    int n;

    cout << "Daily Time Investment Analyzer\n\n";

    cout << "Enter number of activities (minimum 7): ";
    cin >> n;

    while (n < 7 || n > 50) {
        cout << "Enter a number between 7 and 50: ";
        cin >> n;
    }

    Activity a[50];

    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nActivity " << i + 1 << " name: ";
        getline(cin, a[i].name);

        cout << "Time spent (hours): ";
        cin >> a[i].time;

        cin.ignore();
    }

    int ch;

    do {
        cout << "\n1. Sorting\n";
        cout << "2. Searching and Time Analysis\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1)
            sortMenu(a, n);
        else if (ch == 2)
            searchMenu(a, n);

    } while (ch != 3);

    return 0;
}
