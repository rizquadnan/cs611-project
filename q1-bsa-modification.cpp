#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

bool check(string *arr, int n)
{
    int i, j;
    bool result = true;
    ;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                result = false;
                break;
            }
        }

        // IF no two elements were swapped
        // by inner loop, then break
        if (result)
        {
            return result;
        }
    }

    return result;
}

void swap(string *a, string *b)
{
    string t = *a;
    *a = *b;
    *b = t;
}

int partition(string arr[], int low, int high)
{
    srand(time(0));
    int random = low + rand() % (high - low);
    swap(&arr[random], &arr[high]);

    string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(string arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void insertionSort(string *arr, int l, int h)
{
    string key;
    int i, j;
    for (i = l; i < h; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void quickSortRc(string *A, int l, int h)
{
    if (l < h)
    {
        /* Partitioning index */
        int p = partition(A, l, h);
        quickSortRc(A, l, p - 1);
        quickSortRc(A, p + 1, h);
    }
}

void driver(string inFile, int threshold)
{
    string myText;
    ifstream myReadFile(inFile);
    // ofstream myFile(outFile);

    vector<string> datas;

    // create ascii table with empty value for counter
    int asciiSize = 128;
    int **markers = new int *[asciiSize];

    for (size_t looper = 0; looper < asciiSize; looper++)
    {
        markers[looper] = new int[3]{0};
    }

    // put textfile data to vector
    // this step should not be timed
    while (getline(myReadFile, myText))
    {
        datas.push_back(myText);
    }

    myReadFile.close();

    int arrSize = datas.size();
    string *newArr = new string[arrSize];
    string *inlineArr = new string[arrSize];

    // convert vector to array
    // this step should not be timed
    for (size_t looper = 0; looper < arrSize; looper++)
    {
        newArr[looper] = datas[looper];
    }

    // start counting each word by the first letter
    auto begin1 = chrono::high_resolution_clock::now();
    for (size_t looper = 0; looper < arrSize; looper++)
    {
        markers[int(newArr[looper][0])][1] += 1;
    }

    // add begin and end for each array
    for (size_t looper = 0; looper < asciiSize; looper++)
    {

        if (looper == 0)
        {
            markers[looper][0] = 0;
            markers[looper][1] = markers[looper][1];
        }
        else
        {
            markers[looper][0] = markers[looper - 1][1];
            markers[looper][1] = markers[looper][0] + markers[looper][1];
        }
    }

    for (size_t looper = 0; looper < arrSize; looper++)
    {
        int ascii = int(newArr[looper][0]);
        int start = markers[ascii][0];
        int count = start + markers[ascii][2];
        inlineArr[count] = newArr[looper];
        markers[ascii][2] += 1;
    }

    // for (size_t looper = 0; looper < arrSize; looper++) {
    //     cout << "looper: " << looper << endl;
    //     cout << "inlineArr[looper]: " << inlineArr[looper] << endl;
    //     cout << "" << endl;
    // }

    auto end1 = chrono::high_resolution_clock::now();
    // cout << "Data preparation:" << chrono::duration<double>(end1 - begin1).count() << endl;
    // cout << chrono::duration<double>(end1 - begin1).count() << endl;

    auto begin2 = chrono::high_resolution_clock::now();
    for (size_t looper = 0; looper < asciiSize; looper++)
    {
        int begin = markers[looper][0];
        int end = markers[looper][1];
        int counter = markers[looper][2];

        if (counter >= threshold)
        {
            quickSort(inlineArr, begin, end - 1);
            // quickSortRc(inlineArr, begin, end - 1);
        }
        else if (counter > 0)
        {
            insertionSort(inlineArr, begin + 1, end);
        }
    }
    auto end2 = chrono::high_resolution_clock::now();

    bool checker = true;

    checker = check(inlineArr, arrSize);

    if (checker)
    {
        // cout << "Data sorting:" << chrono::duration<double>(end2 - begin2).count() << endl;
        cout << chrono::duration<double>(end2 - begin2).count() << endl;
        // cout << "Total time:" << chrono::duration<double>(end2 - begin1).count() << endl;
    }
    else
    {
        cout << "Data error" << endl;
    }

    // for (size_t looper = 0; looper < arrSize; looper++)
    // {
    //     myFile << inlineArr[looper] << endl;
    // }

    // // myFile.close();
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout << "Please provide the maximum threshold to apply insertion sort" << endl;
        return 1;
    }

    cout << "Gutenberg" << endl;
    cout << "Insertion Sort Threshold: " << argv[1] << endl;
    cout << "2.3m" << endl;
    for (size_t i = 0; i < 3; i++)
    {
        driver("./datasets/GutenbergWordsFile.txt", atoi(argv[1]));
    }
    // cout << "1k" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("./datasets/1k.txt");
    // }
    // cout << "10k" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("./datasets/10k.txt");
    // }
    // cout << "100k" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("./datasets/100k.txt");
    // }
    // cout << "1m" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("./datasets/1m.txt");
    // }
    // cout << "2m" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("../2m.txt");
    // }
    // cout << "3m" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("../3m.txt");
    // }
    // cout << "10m" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("../10m.txt");
    // }

    // system("pause");
}