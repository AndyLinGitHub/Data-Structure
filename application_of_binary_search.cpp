#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int BinarySearch(deque<int>& SW, deque<int>& RI,int& E, int& temp, int& tempV){
    int left = 0;
    int right = SW.size() - 1;
    int mid = 0;
    if (E > RI.back()) {
        RI.push_back(E);
        SW.push_back(E);
        return 0;
    }
    else if (E < RI.front()) {
        RI.push_front(E);
        SW.push_back(E);
        return 0;
    }
    if (E > tempV) {
        left = temp;
    }
    else {
        right = temp;
    }
    while (left <= right) {
        mid = left + (right - left)/ 2;
        if (RI[mid] > E)
        {
            right = mid - 1;
        }
        else if (RI[mid] < E)
        {
            left = mid + 1;
        }
        else
        {
            RI.insert(RI.begin() + mid, E);
            SW.push_back(E);
            break;
        }
        if (left > right){
            RI.insert(RI.begin() + left, E);
            SW.push_back(E);
            break;
        }

    }
}

int BinarySearch(deque<int>& RI, int& E){
    int left = 0;
    int right = RI.size() - 1;
    int mid = 0;
    while (left <= right) {
        mid = left + (right - left)/ 2;
        if (RI[mid] > E)
        {
            right = mid - 1;
        }
        else if (RI[mid] < E)
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
        if (left > right){
            return 0;
        }

    }
}

int main(){
    int N, M, K, element;
    int temp, tempV;
    deque<int> SlidingWindow;
    deque<int> Rank_By_Index;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++){
        cin >> element;
        SlidingWindow.push_back(element);
        Rank_By_Index.push_back(element);
    }
    sort(Rank_By_Index.begin(), Rank_By_Index.end());
    for (int i = M; i < N; i++){
        cout << Rank_By_Index[K - 1] << endl;
        cin >> element;
        temp = BinarySearch(Rank_By_Index, SlidingWindow.front());
        tempV = SlidingWindow.front();
        if(element != SlidingWindow.front()) {
            Rank_By_Index.erase(Rank_By_Index.begin() + temp);
            SlidingWindow.pop_front();
            BinarySearch(SlidingWindow, Rank_By_Index, element, temp, tempV);
        }
    }
    cout << Rank_By_Index[K - 1];
}
