#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <Windows.h>
using namespace std;
#define sizeTable 12000
struct info
{
    string keys;
    string value;
};
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
int binarySearch(info *arr, int l, int r, string x)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    clock_t start, end;
    start = clock();
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid].keys == x)
        {
            fsTime << "binarySearch ";
            end = clock();
            double duration = (double)(end - start);
            fsTime << " Time total:" << duration << "ms" << endl;
            fsTime.close();
            return mid;
        }
        else if (arr[mid].keys > x)
        {

            return binarySearch(arr, l, mid - 1, x);
        }
        return binarySearch(arr, mid + 1, r, x);
    }
    fsTime << "binarySearch ";
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
    return -1;
}
info *insertionSort(info *arr, int n)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsTime << "Sort array: ";
    clock_t start, end;
    start = clock();
    cout << "Loading..." << endl;
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
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
    return arr;
}
void input(fstream &fsInFile)
{
    fstream fsTest("keys.txt", ios::in);
    int size = sizeFileInput(fsTest);
    fsTest.close();
    if (size < 10)
    {
        fstream fs("keys.txt", ios::out);
        fstream fs1("value.txt", ios::out);

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
                fs1 << value << endl;
            }
        }
        fs.clear();
        fs1.clear();
        fs.close();
        fs1.close();
    }
}
void search(info *arr, int size)
{
    cout << " Enter keys search :";
    string x;
    cin >> x;
    int temp = binarySearch(arr, 0, size - 1, x);
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << "Search : " << endl;
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
void saveFileArray(info *arrFinal, int &size)
{
    ofstream ofs1("keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("keys.txt", ios::out);
    fstream fs2("value.txt", ios::out);
    for (int i = 0; i < size; i++)
    {
        fs1 << arrFinal[i].keys << endl;
        fs2 << arrFinal[i].value << endl;
    }
    fs1.close();
    fs2.close();
}
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
        if (temp1.length() > 0)
        {
            arr[i].keys = temp1;
            arr[i].value = temp2;
            i++;
        }
    }
    fs1.clear();
    fs2.clear();
    fs1.close();
    fs2.close();
    return arr;
}
void addData()
{
    int size;
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << "ADD data:" << endl;
    cout << " ADD DATA" << endl;
    string temp1;
    string temp2;
    cout << " Enter keys: ";
    cin.ignore(); // bị trôi lệnh
    getline(cin, temp1);
    cout << "Enter value: ";
    getline(cin, temp2);
    cout << endl;
    fstream fs1("keys.txt", ios::out | ios::app);
    fstream fs2("value.txt", ios::in | ios::app);
    fs1 << temp1 << endl;
    fs2 << temp2 << endl;
    fs3 << temp1 << " : " << temp2 << endl;
    fs1.close();
    fs2.close();
    fs3.close();
}
void deleteData()
{
    fstream fs3("History.txt", ios::out | ios::app);
    int size;
    cout << " Deleted DATA " << endl;
    fs3 << " Deleted DATA " << endl;
    string temp1;
    fstream fs("keys.txt", ios::in);
    cout << " Enter keys: ";
    size = sizeFileInput(fs);
    cin.ignore();
    getline(cin, temp1);
    fs3 << temp1 << " : ";
    info *arr = new info[size];
    arr = inputArr(arr, size);
    int mid = binarySearch(arr, 0, size - 1, temp1);
    if (mid >= 0)
    {
        fs3 << arr[mid].value << endl;
        swap(arr[mid], arr[size - 1]);
        size--;
        saveFileArray(arr, size);
    }
    else if (mid == -1)
    {
        cout << "Not found" << endl;
        fs3 << "Not found" << endl;
    }
    fs3.close();
    delete[] arr;
}
void editData()
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << " EDIT DATA" << endl;
    cout << " EDIT DATA" << endl;
    int size;
    string temp1;
    string temp2;
    fstream fs1("keys.txt", ios::in);
    size = sizeFileInput(fs1);
    fs1.close();
    info *arrTemp = new info[size];
    arrTemp = inputArr(arrTemp, size);
    arrTemp = insertionSort(arrTemp, size);
    cout << " Enter keys: ";
    cin.ignore(); // bị trôi lệnh
    cin >> temp1;
    fs3 << temp1 << " : " << endl;
    int mid = binarySearch(arrTemp, 0, size - 1, temp1);
    if (mid >= 0)
    {
        fs3 << " prev value: " << arrTemp[mid].value << endl;
        cout << "Enter value: ";
        cin.ignore();
        getline(cin, temp2);
        fs3 << " New value: " << temp2 << endl;
        arrTemp[mid].value = temp2;
        saveFileArray(arrTemp, size);
    }
    else
    {
        cout << " Not found " << endl;
        fs3 << " Not found" << endl;
    }
    fs3.close();
    delete[] arrTemp;
}
void process(int seletc)
{
    int size;
    if (seletc == 1)
    {
        fstream fstemp("keys.txt", ios::in);
        size = sizeFileInput(fstemp);
        fstemp.close();

        info *arr = new info[size];
        arr = inputArr(arr, size);
        arr = insertionSort(arr, size);
        search(arr, size);
        delete[] arr;
    }
    else if (seletc == 2)
    {
        addData();
    }
    else if (seletc == 3)
    {
        deleteData();
    }
    else if (seletc == 4)
    {
        editData();
    }
    // if (seletc != 1)
    // {
    //     fstream fsFinals("keys.txt", ios::in);
    //     size = sizeFileInput(fsFinals);
    //     fsFinals.close();
    //     info *arrFinal = new info[size];
    //     arrFinal = inputArr(arrFinal, size);
    //     arrFinal = insertionSort(arrFinal, size);
    //     saveFileArray(arrFinal, size);
    //     delete[] arrFinal;
    // }
}
void selection()
{
    cout << "Loading..." << endl;
    cout << " ARRAY " << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD DATA" << endl;
    cout << "3. DELETE DATA" << endl;
    cout << "4. EDIT DATA" << endl;
    cout << "5. EXIT " << endl;
    cout << " Choose your choice : ";
    int seletc;
    cin >> seletc;
    if (seletc < 5)
    {

        process(seletc);
    }
}
struct node
{
    info table;
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
int hashkeys(string str)
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
void addNode(hashtable &H, info table)
{
    node *p = new node{table, NULL};
    int num = hashkeys(table.keys);
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
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsTime << "find_node ";
    clock_t start, end;
    start = clock();
    int num = hashkeys(temp);
    node *p = H[num];
    while (p != NULL && p->table.keys != temp)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        end = clock();
        double duration = (double)(end - start);
        fsTime << " Time total:" << duration << "ms" << endl;
        fsTime.close();
        return NULL;
    }
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
    return p;
}
void loadFile(hashtable &H)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsTime << "loadFile ";
    clock_t start, end;
    start = clock();
    fstream fs1("keys.txt", ios::in);
    fstream fs2("value.txt", ios::in);
    while (!fs1.eof())
    {
        string temp1;
        string temp2;
        getline(fs1, temp1);
        getline(fs2, temp2);
        info table{temp1, temp2};
        addNode(H, table);
    }
    fs1.close();
    fs2.close();
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
}
void searchHash(hashtable &H)
{
    fstream fsH("History.txt", ios::out | ios::app);
    fsH << "ADD data" << endl;
    node *find;
    string temp;
    cout << "Enter keys: ";
    cin.ignore();
    getline(cin, temp);
    find = find_node(H, temp);
    if (find == NULL)
    {
        cout << "Not found" << endl;
        fsH << temp << " : "
            << "Not found" << endl;
    }
    else
    {
        cout << find->table.value << endl;
        fsH << temp << " : " << find->table.value << endl;
    }
    fsH.close();
}
void addDataHash(hashtable &H)
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << "ADD data:" << endl;
    info table;
    string temp1;
    string temp2;
    cout << "Enter keys: ";
    cin.ignore(); // bị trôi lệnh
    getline(cin, temp1);
    cout << "Enter values: ";
    getline(cin, temp2);
    table.keys = temp1;
    table.value = temp2;
    fs3 << temp1 << " : " << temp2 << endl;
    addNode(H, table);
}
void deleteDataHash(hashtable &H)
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << " Deleted DATA " << endl;
    node *deleteData;
    string temp1;
    cout << "Enter keys: ";
    cin.ignore();
    getline(cin, temp1);
    int index = hashkeys(temp1);
    deleteData = find_node(H, temp1);
    if (deleteData == NULL)
    {
        cout << "Don't see" << endl
             << endl;
    }
    else if (deleteData == H[index])
    {
        H[index] = H[index]->next;
        delete deleteData;
    }
    else
    {
        node *q = H[index];
        q->next = deleteData->next;
        delete deleteData;
    }
}
void editDataHash(hashtable &H)
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << " EDIT DATA" << endl;
    node *editDataHash;
    string temp1;
    cout << "Enter keys: ";
    cin.ignore();
    getline(cin, temp1);
    fs3 << temp1 << " : " << endl;
    editDataHash = find_node(H, temp1);
    if (editDataHash == NULL)
    {
        cout << "Not found" << endl
             << endl;
        fs3 << " Not found" << endl;
    }
    else
    {
        cout << "Enter value: ";
        string temp2;
        getline(cin, temp2);
        fs3 << " prev value: " << editDataHash->table.value << endl;
        editDataHash->table.value = temp2;
        fs3 << " New value: " << temp2 << endl;
    }
}
void saveDataHash(hashtable &H)
{
    ofstream ofs1("keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("keys.txt", ios::out);
    fstream fs2("value.txt", ios::out);
    for (int i = 0; i < sizeTable; i++)
    {
        node *temp = H[i];
        while (temp != NULL)
        {
            if (temp->table.keys.length() > 1)
            {
                fs1 << temp->table.keys << endl;
                fs2 << temp->table.value << endl;
            }
            temp = temp->next;
        }
        delete[] temp;
    }
    fs1.close();
    fs2.close();
}
void selectionHash(hashtable &H)
{

    cout << " HASH TABLE " << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD DATA" << endl;
    cout << "3. DELETE DATA" << endl;
    cout << "4. EDIT DATA" << endl;
    cout << " Choose your choice : ";
    int seletc;
    cin >> seletc;

    if (seletc == 1)
    {
        searchHash(H);
    }
    else if (seletc == 2)
    {
        addDataHash(H);
    }
    else if (seletc == 3)
    {
        deleteDataHash(H);
    }
    else if (seletc == 4)
    {
        editDataHash(H);
    }
    saveDataHash(H);
}
struct Node
{
    info data;
    Node *left;
    Node *right;
};

typedef Node *Tree;

Node *CreateNode(string keys, string values)
{
    Node *p = new Node;
    p->data.keys = keys;
    p->data.value = values;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void CreateTree(Tree &root)
{
    root = NULL;
}

void DestroyTree(Tree &root)
{
    if (root)
    {
        DestroyTree(root->left);
        DestroyTree(root->right);
        delete root;
    }
}

void AddNode(Tree &root, Node *node)
{
    if (root)
    {
        if (root->data.keys == node->data.keys)
        {
            return;
        }
        if (node->data.keys < root->data.keys)
        {
            AddNode(root->left, node);
        }
        else
        {
            AddNode(root->right, node);
        }
    }
    else
    {
        root = node;
    }
}

Node *FindNode(Tree root, string keys)
{
    if (root)
    {
        if (root->data.keys == keys)
        {
            return root;
        }
        if (keys < root->data.keys)
        {
            return FindNode(root->left, keys);
        }
        return FindNode(root->right, keys);
    }
    return NULL;
}

void saveDataTree(Tree root)
{
    if (root)
    {
        saveDataTree(root->left);
        cout << endl
             << root->data.keys
             << ' ';
        saveDataTree(root->right);
    }
}

void NLR(Tree root)
{
    if (root)
    {
        NLR(root->left);
        NLR(root->right);
    }
}

void LNR(Tree root)
{
    if (root)
    {
        LNR(root->left);

        LNR(root->right);
    }
}

void LRN(Tree root)
{
    if (root)
    {
        LRN(root->left);
        LRN(root->right);
    }
}

void FindAndReplace(Tree &p, Tree &tree)
{
    if (tree->left)
        FindAndReplace(p, tree->left);
    else
    {
        p->data.keys = tree->data.keys;
        p = tree;
        tree = tree->right;
    }
}

void DeleteNode(Tree &root, string x)
{
    if (root)
    {
        if (x > root->data.keys)
        {
            DeleteNode(root->right, x);
        }
        else if (x < root->data.keys)
        {
            DeleteNode(root->left, x);
        }
        else
        {
            Node *p = root;
            if (!root->left)
            {
                root = root->right;
            }
            else if (!root->right)
            {
                root = root->left;
            }
            else
            {
                FindAndReplace(p, root->right);
            }
            delete p;
        }
    }
    else
    {
        cout << endl
             << "Not found!\n";
    }
}
void processTree(Tree t, int seletc)
{
    string temps;
    if (seletc == 1)
    {
        cout << endl
             << "Input data to search: ";
        cin >> temps;
        Node *find = FindNode(t, temps);
        if (find == NULL)
        {
            cout << endl
                 << "Not find" << endl;
        }
        else
        {
            cout << endl
                 << find->data.keys << " : " << find->data.value << endl;
        }
    }
    else if (seletc == 2)
    {
        string keys;
        string values;
        cout << "Enter keys:";
        cin.ignore();
        cin >> keys;
        cout << endl
             << " Enter values: ";
        getline(cin, values);
        AddNode(t, CreateNode(keys, values));
    }
    else if (seletc == 3)
    {
        cout << endl
             << "Enter keys delete ";
        cin >> temps;
        DeleteNode(t, temps);
    }
    else if (seletc == 4)
    {
        cout << endl
             << "Input data to Edit: ";
        cin >> temps;
        Node *find = FindNode(t, temps);
        if (find == NULL)
        {
            cout << endl
                 << "Not find" << endl;
        }
        else
        {
            cout << endl
                 << " prev data : " << find->data.keys << find->data.value << endl;
            string value;
            cout << "Enter new data ";
            getline(cin, value);
            find->data.value = value;
        }
    }
}
void selectionTree()
{
    Tree t;
    CreateTree(t);
    fstream fsInFile("oxford English Dictionary.txt", ios::in);
    input(fsInFile);
    fsInFile.close();
    fstream fskeys("keys.txt", ios::in);
    fstream fsValues("value.txt", ios::in);
    while (!fskeys.eof())
    {
        string keys;
        string values;
        getline(fskeys, keys);
        getline(fsValues, values);
        AddNode(t, CreateNode(keys, values));
    }
    fskeys.close();
    fsValues.close();
    cout << " AVL TREE " << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD DATA" << endl;
    cout << "3. DELETE DATA" << endl;
    cout << "4. EDIT DATA" << endl;
    cout << "5. EXIT " << endl;
    cout << " Choose your choice : ";
    int seletc;
    cin >> seletc;
    if (seletc < 5)
    {
        processTree(t, seletc);
    }
    fstream fsSave("keys.txt",ios::out);
    saveDataTree(t);
}
int main()
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    fstream fsH("History.txt", ios::out | ios::app);
    system("color 80");
    system("cls");
    fstream fs("oxford English Dictionary.txt", ios::in);
    cout << "LAB5_20127185_Nguyen Gia Huy" << endl;
    cout << "1. Run with array" << endl;
    cout << "2. Run with  Hash Table " << endl;
    cout << "3. Run with  Tree " << endl;
    cout << "4.    Show History        " << endl;
    cout << "5.       EXIT        " << endl;
    cout << " Enter your choice: ";
    int Select;
    cin >> Select;
    if (Select == 1)
    {

        fsH << "Run with array" << endl;
        fsTime << "Run with array" << endl;
        input(fs);
        selection();
        system("pause");
        main();
    }
    else if (Select == 2)
    {
        fsH << "Run with Hash Table" << endl;
        fsTime << "Run with Hash Table" << endl;
        cout << "Loading..." << endl;
        input(fs);
        hashtable H;
        tableInitialization(H);
        loadFile(H);
        selectionHash(H);
        system("pause");
        main();
    }
    else if (Select == 3)
    {
        fsH << "Run with AVL Tree" << endl;
        fsTime << "Run with  AVL Tree" << endl;
        selectionTree();
        system("pause");
        main();
    }
    else if (Select == 4)
    {
        fstream History("History.txt", ios::in);
        while (!History.eof())
        {
            string temp;
            getline(History, temp);
            cout << temp << endl;
        }
        system("pause");
        main();
    }
    else
    {
        Beep(523, 1000);
    }
    fsTime.close();
    fsH.close();
    fs.close();
    return 0;
}