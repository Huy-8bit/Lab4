#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <ctime>

using namespace std;
#define sizeTable 10000
struct info
{
    string keys;
    string value;
};
// int binarySearch(info *arr, int l, int r, string x)
// {
//     if (r >= l)
//     {
//         int mid = l + (r - l) / 2;
//         if (arr[mid].keys == x)
//         {
//             return mid;
//         }
//         else if (arr[mid].keys > x)
//         {
//             return binarySearch(arr, l, mid - 1, x);
//         }
//         return binarySearch(arr, mid + 1, r, x);
//     }
//     return -1;
// }

// info *insertionSort(info *arr, int n)
// {
//     cout << " Run function insertionSort" << endl;
//     int i, j;
//     string keys;
//     for (i = 1; i < n; i++)
//     {
//         keys = arr[i].keys;
//         j = i - 1;
//         while (j >= 0 && arr[j].keys > keys)
//         {
//             swap(arr[j], arr[j + 1]);
//             j = j - 1;
//         }
//         arr[j + 1].keys = keys;
//     }
//     return arr;
// }
void input(fstream &fsInFile)
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
// void search(info *arr, int size)
// {
//     cout << " Enter key search :";
//     string x;
//     cin >> x;
//     int temp = binarySearch(arr, 0, size - 1, x);
//     cout << temp << endl;
//     fstream fs3("History.txt", ios::out | ios::app);
//     fs3 << x << " : ";
//     if (temp > 0)
//     {
//         cout << arr[temp].value << endl;
//         fs3 << arr[temp].value << endl;
//     }
//     else
//     {
//         cout << " Don't see it" << endl;
//         fs3 << " Don't see it" << endl;
//     }
//     fs3.close();
// }
int sizeFileInput(fstream &fsInFile)
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
// void output(info *arrFinal, int &size)
// {
//     fstream fs1("keys.txt", ios::out);
//     fstream fs2("value.txt", ios::out);
//     fs1.clear();
//     fs1.seekg(0, ios::beg);
//     fs2.clear();
//     fs2.seekg(0, ios::beg);
//     for (int i = 0; i < size; i++)
//     {
//         fs1 << arrFinal[i].keys << endl;
//         fs2 << arrFinal[i].keys << " : " << arrFinal[i].value << endl;
//     }
//     fs1.close();
//     fs2.close();
// }
info *inputArr(info *arr, int size)
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
// void addData()
// {
//     int size;
//     cout << " ADD DATA" << endl;
//     string temp1;
//     string temp2;
//     cout << " Enter keys: ";
//     cin.ignore(); // bị trôi lệnh
//     getline(cin, temp1);
//     cout << "Enter value: ";
//     getline(cin, temp2);
//     cout << endl;
//     fstream fs1("keys.txt", ios::out | ios::app);
//     fstream fs2("value.txt", ios::in | ios::app);
//     fs1 << temp1 << endl;
//     fs2 << temp1 << " : " << temp2 << endl;
//     fs1.close();
//     fs2.close();
// }
// void deleteData()
// {

//     int size;
//     cout << " Deleted DATA " << endl;
//     string temp1;
//     fstream fs("keys.txt", ios::in);
//     cout << " Enter keys: ";
//     size = sizeFileInput(fs);
//     getline(cin, temp1); // bị trôi lệnh
//     getline(cin, temp1);
//     info *arr = new info[size];
//     arr = inputArr(arr, size);
//     int mid = binarySearch(arr, 0, size - 1, temp1);
//     if (mid >= 0)
//     {
//         swap(arr[mid], arr[size - 1]);
//         size--;
//         output(arr, size);
//     }
//     else if (mid == -1)
//     {
//         cout << "Not found" << endl;
//     }
//     delete[] arr;
// }
// void editData()
// {
//     cout << " EDIT DATA" << endl;
//     int size;
//     string temp1;
//     string temp2;
//     fstream fs1("keys.txt", ios::in);
//     size = sizeFileInput(fs1);
//     fs1.close();
//     info *arrTemp = new info[size];
//     arrTemp = inputArr(arrTemp, size);
//     arrTemp = insertionSort(arrTemp, size);
//     cout << " Enter keys: ";
//     cin.ignore(); // bị trôi lệnh
//     cin >> temp1;
//     int mid = binarySearch(arrTemp, 0, size - 1, temp1);
//     cout << mid << endl;
//     if (mid >= 0)
//     {
//         cout << "Enter value: ";
//         cin.ignore();
//         getline(cin, temp2);
//         arrTemp[mid].value = temp2;
//         output(arrTemp, size);
//     }
//     else
//     {
//         cout << " Not found " << endl;
//     }
//     delete[] arrTemp;
// }

// void process(int seletc)
// {
//     int size;
//     fstream fsTemp("keys.txt", ios::in);
//     size = sizeFileInput(fsTemp);
//     if (size < 100)
//     {
//         fstream fsInFile("Oxford English Dictionary.txt", ios::in);
//         input(fsInFile);
//     }
//     fsTemp.close();

//     if (seletc == 1)
//     {

//         info *arr = new info[size];
//         arr = inputArr(arr, size);
//         arr = insertionSort(arr, size);
//         search(arr, size);
//         delete[] arr;
//     }
//     else if (seletc == 2)
//     {
//         addData();
//     }
//     else if (seletc == 3)
//     {
//         deleteData();
//     }
//     else if (seletc == 4)
//     {
//         editData();
//     }
//     fstream fsFinals("keys.txt", ios::in);
//     size = sizeFileInput(fsFinals);
//     fsFinals.close();
//     info *arrFinal = new info[size];
//     arrFinal = inputArr(arrFinal, size);
//     arrFinal = insertionSort(arrFinal, size);
//     output(arrFinal, size);
//     delete[] arrFinal;
// }

// void selection()
// {
//     cout << "LAB5_20127185_Nguyen Gia Huy" << endl;
//     cout << "1. SEARCH" << endl;
//     cout << "2. ADD DATA" << endl;
//     cout << "3. DELETE DATA" << endl;
//     cout << "4. EDIT DATA" << endl;
//     cout << "5. EXIT " << endl;
//     cout << endl
//          << endl
//          << " Choose your choice : ";
//     int seletc;
//     cin >> seletc;
//     if (seletc < 5)
//     {
//         process(seletc);
//         selection();
//     }
// }

int main()
{
    //selection();
    // fstream fs1("oxford English Dictionary.txt",ios::in);
    // input(fs1);

    // fs.close();

    return 0;
}
struct node
{
    string temp;
    node *next;
};
typedef node *hashtable[sizeTable];

void tableInitialization(hashtable &H)
{
    for (int i = 0; i < sizeTable; i++)
    {
        H[i] = NULL;
    }
}
int hashKeys(string str)
{
    //abcde
    long sum = 0, mul = 1;
    for (int i = 0; i < str.length(); i++)
    {
        mul = (i % 4 == 0) ? 1 : mul * 256;
        sum += str.at(i) * mul;
    }
    return (int)(abs(sum) % sizeTable);
}
void addNode(hashtable &H, string temp1)
{
    node *p = new node{temp1, NULL};
    int num = hashKeys(temp1);
    if (H[num] == NULL)
    {
        H[num] = p;
    }
    else
    {
        node *q = H[num];
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = p;
    }
}
node *find_node(hashtable &H, string temp)
{
    int num = hashKeys(temp);
    node *p = H[num];
    while (p != NULL && p->temp != temp)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return NULL;
    }
    return p;
}
void search(hashtable &H)
{
    node *find;
    string temp;
    cout << "Enter: ";
    getline(cin,temp);
    
}
void loadFile(hashtable &H)
{
    fstream fs("keys.txt", ios::in);
    while (!fs.eof())
    {
        string temp1;
        getline(fs, temp1);
        addNode(H, temp1);
    }
    fs.close();
}
