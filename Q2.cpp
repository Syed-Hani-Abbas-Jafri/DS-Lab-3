#include <iostream>
#include <string>
using namespace std;

struct Position {
    string name;
    int rank;
};

const string aReason =
    "Academia provides opportunities to explore research, develop deeper "
    "knowledge, and contribute new ideas.";

const string iReason =
    "Industry provides opportunities to build practical software, solve "
    "real-world problems, and gain professional experience.";

int lin(Position a[], int n, int k, int &c) {
    c = 0;

    for (int i = 0; i < n; i++) {
        c++;

        if (a[i].rank == k)
            return i;
    }

    return -1;
}

int bin(Position a[], int n, int k, int &c) {
    c = 0;

    int l = 0, h = n - 1;

    while (l <= h) {
        c++;

        int m = (l + h) / 2;

        if (a[m].rank == k)
            return m;

        if (a[m].rank < k)
            l = m + 1;
        else
            h = m - 1;
    }

    return -1;
}

int inter(Position a[], int n, int k, int &c) {
    c = 0;

    int l = 0, h = n - 1;

    while (l <= h && k >= a[l].rank && k <= a[h].rank) {
        c++;

        if (a[l].rank == a[h].rank) {
            if (a[l].rank == k)
                return l;

            return -1;
        }

        int p = l + ((double)(k - a[l].rank) /
                     (a[h].rank - a[l].rank)) * (h - l);

        if (a[p].rank == k)
            return p;

        if (a[p].rank < k)
            l = p + 1;
        else
            h = p - 1;
    }

    return -1;
}

void sortData(Position a[], int n) {
    for (int i = 1; i < n; i++) {
        Position x = a[i];
        int j = i - 1;

        while (j >= 0 && a[j].rank > x.rank) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = x;
    }
}

void inputRank(Position a[], int n) {
    bool u[10] = {false};

    for (int i = 0; i < n; i++) {
        int r;

        while (true) {
            cout << "Rank for " << a[i].name << " (1-" << n << "): ";
            cin >> r;

            if (r < 1 || r > n) {
                cout << "Invalid rank.\n";
            }
            else if (u[r]) {
                cout << "Rank already used.\n";
            }
            else {
                a[i].rank = r;
                u[r] = true;
                break;
            }
        }
    }
}

int main() {
    cout << "   Academia vs Industry Ranker\n";
    int p;
    cout << "1. Academia\n";
    cout << "2. Industry\n";
    cout << "Choice: ";
    cin >> p;

    while (p != 1 && p != 2) {
        cout << "Enter 1 or 2: ";
        cin >> p;
    }

    string in[9] = {
        "AI Engineer",
        "Software Engineer",
        "Data Scientist",
        "Machine Learning Engineer",
        "DevOps Engineer",
        "Data Engineer",
        "Cybersecurity Engineer",
        "Project Manager",
        "Cloud Engineer"
    };

    string ac[5] = {
        "University Professor/Lecturer",
        "Research Scientist",
        "Research Assistant",
        "PhD Researcher",
        "Academic Researcher"
    };

    Position x[9];
    int n;

    if (p == 1) {
        n = 5;

        for (int i = 0; i < n; i++)
            x[i] = {ac[i], 0};

        cout << "\nYou selected: Academia\n";
    }
    else {
        n = 9;

        for (int i = 0; i < n; i++)
            x[i] = {in[i], 0};

        cout << "\nYou selected: Industry\n";
    }

    char q;

    cout << "Do you want to know the reason? (y/n): ";
    cin >> q;

    if (q == 'y' || q == 'Y') {
        if (p == 1)
            cout << "Reason: " << aReason << "\n";
        else
            cout << "Reason: " << iReason << "\n";
    }

    cin.ignore();

    string myReason;

    cout << "\nWrite one line explaining your choice:\n";
    getline(cin, myReason);

    cout << "Your reason: " << myReason << "\n\n";

    inputRank(x, n);

    Position s[9];

    for (int i = 0; i < n; i++)
        s[i] = x[i];

    sortData(s, n);

    cout << "\nYour ranking:\n";

    for (int i = 0; i < n; i++)
        cout << s[i].rank << ". " << s[i].name << "\n";

    int k;

    cout << "\nEnter rank to search (1-" << n << "): ";
    cin >> k;

    while (k < 1 || k > n) {
        cout << "Invalid rank. Enter again: ";
        cin >> k;
    }

    int z, c;

    z = lin(x, n, k, c);
    cout << "\nLinear Search: ";

    if (z != -1)
        cout << x[z].name << " | Comparisons: " << c << "\n";
    else
        cout << "Not found\n";

    z = bin(s, n, k, c);
    cout << "Binary Search: ";

    if (z != -1)
        cout << s[z].name << " | Comparisons: " << c << "\n";
    else
        cout << "Not found\n";

    z = inter(s, n, k, c);
    cout << "Interpolation Search: ";

    if (z != -1)
        cout << s[z].name << " | Comparisons: " << c << "\n";
    else
        cout << "Not found\n";

    cout << "\nThank you!\n";

    return 0;
}
