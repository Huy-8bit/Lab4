#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
using namespace std;
struct info
{
    string keys;
    string value;
};
int binarySearch(info *arr, int l, int r, string x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid].keys == x)
        {
            return mid;
        }
        else if (arr[mid].keys > x)
        {
            return binarySearch(arr, l, mid - 1, x);
        }
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

info *insertionSort(info *arr, int n)
{
    cout << " Run function insertionSort" << endl;
    int i, j;
    string keys;
    for (i = 1; i < n; i++)
    {
        keys = arr[i].keys;
        j = i - 1;
        while (j >= 0 && arr[j].keys > keys)
        {
            swap(arr[j], arr[j + 1]);
            j = j - 1;
        }
        arr[j + 1].keys = keys;
    }
    return arr;
}
void inPut(fstream &fsInFile)
{
    fstream fs("keys.txt", ios::out);
    fstream fs1("value.txt", ios::out);
    int size = 0;
    while (!fsInFile.eof())
    {
        string line;
        getline(fsInFile, line);
        if (line.size() > 3)
        {
            string keys;
            string value;
            stringstream ss(line);
            getline(ss, keys, ' ');
            getline(ss, value, '\n');
            fs << keys << endl;
            fs1 << keys << " :" << value << endl;
        }
    }
    fs.clear();
    fs1.clear();
    fs.close();
    fs1.close();
}
void search(info *arr, int size)
{
    cout << " Enter key search :";
    string x;
    cin >> x;
    int temp = binarySearch(arr, 0, size - 1, x);
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << x << " : ";
    if (temp > 0)
    {
        cout << arr[temp].value << endl;
        fs3 << arr[temp].value << endl;
    }
    else
    {
        cout << " Don't see it" << endl;
        fs3 << " Don't see it" << endl;
    }
    fs3.close();
}
int sizeFileInPut(fstream &fsInFile)
{
    int size = 0;
    while (!fsInFile.eof())
    {
        string temp;
        getline(fsInFile, temp);
        size++;
    }
    return size;
}
void outPut(info *arrFinal, int &size)
{
    fstream fs1("keys.txt", ios::out);
    fstream fs2("value.txt", ios::out);
    fs1.clear();
    fs1.seekg(0, ios::beg);
    fs2.clear();
    fs2.seekg(0, ios::beg);
    for (int i = 0; i < size; i++)
    {
        fs1 << arrFinal[i].keys << endl;
        fs2 << arrFinal[i].value << endl;
    }
    fs1.close();
    fs2.close();
}
info *inPutArr(info *arr, int size)
{
    fstream fs1("keys.txt", ios::in);
    fstream fs2("value.txt", ios::in);
    int i = 0;
    while (!fs1.eof())
    {
        string temp1;
        string temp2;
        getline(fs1, temp1);
        getline(fs2, temp2);
        arr[i].keys = temp1;
        arr[i].value = temp2;
        i++;
    }
    fs1.clear();
    fs2.clear();
    fs1.close();
    fs2.close();
    return arr;
}
void process(int seletc)
{
    fstream fsInFile("Oxford English Dictionary.txt", ios::in);
    int size = sizeFileInPut(fsInFile);
    fsInFile.clear();
    fsInFile.seekg(0, ios::beg);

    inPut(fsInFile);

    if (seletc == 1)
    {
        info *arr = new info[size];
        arr = inPutArr(arr, size);
        arr = insertionSort(arr, size);
        search(arr, size);
        delete[] arr;
    }
    else if (seletc == 2)
    {
        cout << " ADD DATA" << endl;
        string temp1;
        string temp2;
        cout << " Enter keys: ";
        getline(cin, temp1);
        getline(cin, temp1);
        cout << "Enter value: ";
        getline(cin, temp2);
        cout << endl;
        fstream fs1("keys.txt", ios::out | ios::app);
        fstream fs2("value.txt", ios::in | ios::app);
        fs1 << temp1 << endl;
        fs2 << temp1 << " : " << temp2 << endl;
        fs1.close();
        fs2.close();
    }
    else if (seletc == 4)
    {
        cout << " EDIT DATA" << endl;
        string temp1;
        string temp2;
        fstream fs1("keys.txt", ios::in);
        int size = sizeFileInPut(fs1);
        fs1.close();
        info *arrTemp = new info[size];
        arrTemp = insertionSort(arrTemp, size);
        cout << " Enter keys: ";
        getline(cin, temp1);

        getline(cin, temp1);
        int mid = binarySearch(arrTemp, 0, size - 1, temp1);
        if (mid >= 0)
        {
            cout << "Enter value: ";
            getline(cin, temp2);
            arrTemp[mid].value = temp2;
            outPut(arrTemp, size);
        }
        else
        {
            cout << " Not found " << endl;
        }
        delete[] arrTemp;
    }
    fstream fsFinals("keys.txt", ios::in);
    size = sizeFileInPut(fsFinals);
    fsFinals.close();
    info *arrFinal = new info[size];
    arrFinal = inPutArr(arrFinal, size);
    arrFinal = insertionSort(arrFinal, size);
    outPut(arrFinal, size);
    delete[] arrFinal;
}
void selection()
{
    cout << "LAB5_20127185_Nguyen Gia Huy" << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD DATA" << endl;
    cout << "3. DELETE DATA" << endl;
    cout << "4. EDIT DATA" << endl;
    cout << "5. EXIT " << endl;
    cout << endl
         << endl
         << " Choose your choice : ";
    int seletc;
    cin >> seletc;
    if (seletc < 5)
    {
        process(seletc);
        selection();
    }
}
int main()
{
    selection();

    system("pause");
    return 0;
}