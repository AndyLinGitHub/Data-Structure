#include <iostream>
#include <deque>
#include <algorithm>
#include <stdio.h>
using namespace std;

int main(){
    int N, M, K, element;
    deque<int>::iterator low;
    deque<int> SlidingWindow;
    deque<int> Rank_By_Index;
    cin >> N >> M >> K;
    int* array;
    array = new int[N - M + 1];
    for (int i = 0; i < M; i++){
        cin >> element;
        SlidingWindow.push_back(element);
        //array[i] = element;
        Rank_By_Index.push_back(element);
    }
    sort(Rank_By_Index.begin(), Rank_By_Index.end());
    for (int i = M; i < N; i++){
        array[i - M] = Rank_By_Index[K - 1];
        cin >> element;
        if(element != SlidingWindow.front()) {
            low = lower_bound (Rank_By_Index.begin(), Rank_By_Index.end(), SlidingWindow.front());
            Rank_By_Index.erase(low);
            SlidingWindow.pop_front();
            low = lower_bound (Rank_By_Index.begin(), Rank_By_Index.end(), element);
            Rank_By_Index.insert(low, element);
            SlidingWindow.push_back(element);
        }
    }
    array[N - M] = Rank_By_Index[K - 1];
    for (int i = 0; i < N - M + 1; i++){
        printf("%d\n", array[i]);
    }
    delete [] array;
}
