#include <iostream>
#include<string>
#include<vector>
#include<sstream>
#include <fstream>
#include<algorithm>
#define SIZE 50

using namespace std;

vector<int>bloomFilter(SIZE);

void initfilter()
{
    for (int i = 0; i < SIZE; i++)
        bloomFilter[i] = 0;
    return;
}

string parseUrl(string url)
{
    int index=url.find("https://");
    if(index!=string::npos)
        url = url.substr(index + 8);

    index = url.find("http://");
    if (index != string::npos)
        url = url.substr(index + 7);

    index = url.find("www.");
    if (index == string::npos)
        url = "www." + url;

    return url;
}

int hash1(string url)
{
    int sum = 0;
    char tmp;
    for (int i = 0; i < url.size(); i++)
    {
        sum += 3*url[i]+1;
    }
    return sum % SIZE;
}

int hash2(string url)
{
    int sum = 0;
    char tmp;
    for (int i = 0; i < url.size(); i++)
    {
        sum += 3*url[i]+2;
    }
    return sum % SIZE;
}

int hash3(string url)
{
    int sum = 0;
    char tmp;
    for (int i = 0; i < url.size(); i++)
    {
        sum += 3*url[i]+3;
    }
    return sum % SIZE;
}

void display()
{
    for (auto i : bloomFilter)
        cout << i << " ";
    cout << endl;
}

void display2D()
{
    int index = 0;

    cout << "====================" << endl;
    cout << "Index\t| " << "Value" << endl;
    cout << "_______________" << endl;
    for (auto i : bloomFilter)
        cout << index++ << "\t" << "|" << " " << i << endl;
    cout << "====================" << endl;
    
    return;
}

bool checkIfPresent(string url)
{
    int index1 = hash1(url);
    int index2 = hash2(url);
    int index3 = hash3(url);

    cout << "url: " << url << endl << " hash 1: " << index1 << endl << " hash 2: " << index2 << endl << " hash 3: " << index3 << endl;
    if (bloomFilter[index1] ==1 && bloomFilter[index2] == 1 && bloomFilter[index3] == 1)
        return true;
    return false;
}

int main()
{
    initfilter();
    string url;

    std::ifstream infile("urls.txt");
    if (!infile)
        return EXIT_FAILURE;

    while (infile >> url)
    {
        url = parseUrl(url);

        int index1 = hash1(url);
        int index2 = hash2(url);
        int index3 = hash3(url);

        bloomFilter[index1] = 1;
        bloomFilter[index2] = 1;
        bloomFilter[index3] = 1;

        cout << "url: " << url << endl << " hash 1: " << index1<< endl << " hash 2: " << index2<< endl << " hash 3: " << index3 << endl;
        display();
        cout << endl<<endl<<endl;
    }
    display2D();
    
    do
    {
        cout << "Enter URL: (\"EXIT\" to quit): ";
        cin >> url;
        if ((url != "EXIT"))
        {
            url = parseUrl(url);
            checkIfPresent(url) ? cout << "WebPage returned from Cache" << endl : cout << "WebPage returned from ISP" << endl;
        }
    } while (url != "EXIT");

    return EXIT_SUCCESS;
}


//neg - www.abcd.com
// false pos- www.b.com