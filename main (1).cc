// Zhenrui Huang
// 2019/11/13
// CS3610
// Project4

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int partition(vector<int>& list, int l, int r) {
    int mid=(l+r)/2;
    int index;
    int pivot;
    int tem;
    index = l;
    pivot = list[mid];
    swap(list[mid],list[l]);
    for(int i= l+1; i<=r; i++) {

        if (list[i]<pivot) {

            index++;
            swap(list[index],list[i]);

        }
    }
    swap(list[index],list[l]);
    return index;
}


void quicksort(vector<int>& list, int l, int r) {

    if(l>=r)
        return;
    int Loc;
    if (l < r)
    {
        Loc = partition(list, l, r);
        quicksort(list, l, Loc - 1);
        quicksort(list, Loc + 1, r);
    }
}



void multiway_merge(vector<vector<int> >& k_lists, vector<int>& s_list) {


    priority_queue<int, vector<int>, greater<int> > minheap;
    s_list.clear();
    for(int x=0; x<k_lists.size(); ++x) {

        minheap.push(k_lists[x][0]);
        k_lists[x].erase(k_lists[x].begin());
    }
    int smal;
    int small;
    while(smal != -1) {

        smal = -1;
        for(int i = 0; i < k_lists.size(); i++) {

            if(!k_lists[i].empty()){
                smal = k_lists[i][0];
                small = i;
            }
        }

        for(int j = 0; j < k_lists.size(); j++) {

            if(!k_lists[j].empty()) {

                if(k_lists[j][0] < smal) {

                    smal = k_lists[j][0];
                    small = j;
                }
            }

        }
        if(smal != -1) {

            minheap.push(smal);
            k_lists[small].erase(k_lists[small].begin());
        }
    }
    while(!minheap.empty()) {
        s_list.push_back(minheap.top());
        minheap.pop();
    }
}


int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);

  for (int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
  cout << endl;
}
