#include "sorter.h"
#include "timer.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <ranges>
#include <tgmath.h>
using namespace std;

//Sorter methods
void Sorter::fill(int count, string file_name)
{
    //places the first count words from the file named 
    //file_name into this vector
    ifstream in(file_name);
    for (std::string string_word; (in >> string_word) && count > 0 ; --count){
       vec.push_back(string_word);
    }
    in.close();
}
void  Sorter::print(ostream & out)
{
    for(string word: vec)
    {
        out<<word<<" ";
    }
}
bool Sorter::verify_sorted()
{
    if(!vec.empty())
    {
        string prev = vec.at(0);
        for(int i=1; i<vec.size(); i++)
        {
            if(prev > vec.at(i))
            {
                return false;
            }
            prev = vec.at(i);
        }
    }
    return true;
}
//INSERTION SORT
void InsertionSorter::insertionsort(vector<string>& vec, int low, int high)
{
    for (unsigned int index = low+1; index<= high; index++) {

        string currentvalue = vec[index];
        int position = index;

        while (position>low && vec[position-1]>currentvalue) {
            vec[position] = vec[position-1];
            position--;
        }

        vec[position] = currentvalue;
    }

}
void InsertionSorter::sort()
{
    if(vec.size()>0)
    {
        InsertionSorter::insertionsort(vec, 0, vec.size()-1);
    }
}
//QuickSorter
string QuickSorter::select_pivot(vector<string>& vec, int low, int high)
{
     int mid = low+ (high-low) / 2;
    if(vec[mid] < vec[low])
    {
        swap(vec.at(low), vec.at(mid));
    }
    if(vec[high] < vec[low])
    {
        swap(vec.at(low), vec.at(high));
    }
    if(vec[mid] < vec[high])
    {
        swap(vec.at(mid), vec.at(high));
    }
    return vec[high];
}
int  QuickSorter::partition(vector<string>& vec, int low, int high)
{
    string pivot = select_pivot(vec, low, high);
    for(int j = low; j < high; j++)
    {
        if(vec[j] <= pivot)
        {
            swap(vec[low], vec[j]);
            ++low;
        }
    }
    swap(vec[low], vec[high]);
    return low;
}
void  QuickSorter::quicksort(vector<string>& vec, int low, int high)
{
    if(low < high)
    {
        int pivot_index = partition(vec, low, high);
        quicksort(vec, low, pivot_index-1);
        quicksort(vec, pivot_index+1, high);
    }

}
void  QuickSorter::sort()
{
    QuickSorter::quicksort(vec, 0, vec.size()-1);
}

//HeapSorter
void HeapSorter::heapify(vector<string>& vec, int high, int root)
{
    int largest = root;
    int left = 2 * root +1;
    int right = 2 * root +2;
    //left child larger than root
    if(left < high && vec[left] > vec[largest])
    {
        largest = left;
    }
    //right child is larger than largest so far
    if(right < high && vec[right] > vec[largest])
    {
        largest = right;
    }
    //if largest is not root
    if(largest != root)
    {
        swap(vec[root], vec[largest]);
        heapify(vec, high, largest); //omly take one path - the largest
    }
}
void HeapSorter::heapsort(vector<string>& vec, int low, int high)
{
    //Build max heap 
    for(int root = ((high) /2)-1; root >= low; --root)
    {
        heapify(vec, high + 1, root);
    }
    //extract elements from heap one by one
    for(int end = high; end >= low; --end)
    {
        swap(vec[low], vec[end]);
        heapify(vec, end, low);
    }

}
void HeapSorter::sort() 
{
    heapsort(vec, 0, vec.size()-1);
}

//IntroSorter
void IntroSorter::introsort_util(vector<string>& arr, int low, int high, int depth_limit)
{
    if(high - low < 11)
    {
        InsertionSorter::insertionsort(arr, low, high);
        return;
    }
    if(depth_limit == 0)
    {
        HeapSorter::heapsort(arr, low, high);
        return;
    }
    //quicksort
    int p = QuickSorter::partition(arr, low, high);
    introsort_util(arr, low, p-1, depth_limit-1);
    introsort_util(arr, p+1, high, depth_limit-1);
}
void IntroSorter::introsort(vector<string>& vec, int low, int high)
{
    int depth_limit = 2 * log(high-low);
    introsort_util(vec, low, high, depth_limit);

}
void IntroSorter::sort()
{
    introsort(vec, 0, vec.size()-1);
}
//STLSorter
void STLSorter::sort()
{
    std::ranges::sort(this->vec);
}
//StableSorter
void StableSorter::sort()
{
    std::stable_sort(vec.begin(), vec.end());
}
//ShellSorter
void ShellSorter::gapInsertionSort(vector<string> & avector, int start, int gap)
{
    int sz = avector.size();
    for(int i = start + gap; i <sz ; i += gap)
    {
        string currentvalue = avector[i];
        int position = i;

        while(position >= gap && avector[position - gap] > currentvalue)
        {
            avector[position] = avector[position - gap];
            position -= gap;
        }
        avector[position] = currentvalue;
    }
}
 void ShellSorter::shellSort(vector<string> & avector)
{
    int subvectorcount = avector.size() / 2; //cuts vector by half
    while(subvectorcount > 0) {
        for(int startposition = 0; startposition < subvectorcount; startposition++)
            gapInsertionSort(avector, startposition, subvectorcount);
            subvectorcount = subvectorcount / 2;
    }
}
void ShellSorter::sort()
{
    shellSort(vec);
}
//NON CLASS FUNCTIONS
ostream & operator << (ostream & out, Sorter & L)
{
     //output operator
    L.print(out);
    return out;
}
void error(string word, string msg)
{
    //print error message
    cout<<"ERROR: "<<word<<" "<<msg<<endl;
}
void measure_partition(int k, string file_name, Sorter & L)
{
    Timer t;
    double eTime;
    int limit = k * NWORDS/10;
    L.fill(limit, file_name);
    t.start();
    L.sort();
    t.elapsedUserTime(eTime);
    cout<<limit<<" : ";
    cout<<eTime << endl;
}
void measure_partitions(string file_name, Sorter & L)
{
    cout << L.name << endl;
    for(int K = 1; K <= 10; ++K)
    {
        cout<<"\t\tTime = ";
        measure_partition(K, file_name, L);
    }
}
void measure_sorters(string input_file)
{
    InsertionSorter IS;
    measure_partitions(input_file, IS);
    
    QuickSorter QS;
    measure_partitions(input_file, QS);
    
    HeapSorter HS;
    measure_partitions(input_file, HS);
    
    IntroSorter ITS;
    measure_partitions(input_file, ITS);
    
    STLSorter STS;
    measure_partitions(input_file, STS);
    
    StableSorter SBS;
    measure_partitions(input_file, SBS);
    
    ShellSorter SHS;
    measure_partitions(input_file, SHS);
}