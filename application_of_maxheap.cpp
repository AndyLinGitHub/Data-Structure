// A C++ program to find k'th smallest element in a stream 
#include<iostream>
#include<climits>
#include <deque>
using namespace std;

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
class MaxHeap
{
    int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of max heap
    int heap_size; // Current number of elements in min heap
public:
    MaxHeap(int a[], int size); // Constructor
    void buildHeap();
    void MaxHeapify(int i); //To maxheapify subtree rooted with index i
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
    int extractMax(); // extracts root (maximum) element
    int getMax()	 { return harr[0]; }

    // to replace root with new node x and heapify() new root
    void replaceMax(int x) { harr[0] = x; MaxHeapify(0); }
};

MaxHeap::MaxHeap(int a[], int size)
{
    heap_size = size;
    harr = a; // store address of array
}

void MaxHeap::buildHeap()
{
    int i = (heap_size - 1)/2;
    while (i >= 0)
    {
        MaxHeapify(i);
        i--;
    }
}

// Method to remove maximum element (or root) from max heap
int MaxHeap::extractMax()
{
    if (heap_size == 0)
        return INT_MAX;

    // Store the minimum value.
    int root = harr[0];

    // If there are more than 1 items, move the last item to root
    // and call heapify.
    if (heap_size > 1)
    {
        harr[0] = harr[heap_size-1];
        MaxHeapify(0);
    }
    heap_size--;

    return root;
}

// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void MaxHeap::MaxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int biggest = i;
    if (l < heap_size && harr[l] > harr[i])
        biggest = l;
    if (r < heap_size && harr[r] > harr[biggest])
        biggest = r;
    if (biggest != i)
    {
        swap(&harr[i], &harr[biggest]);
        MaxHeapify(biggest);
    }
}

// A utility function to swap two elements
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to return k'th largest element from input stream
void kthSmallest(int k, int M, deque<int>& W)
{
    // count is total no. of elements in stream seen so far
    int count = 0; // x is for new element

    // Create a min heap of size k
    int *arr = new int[k];
    MaxHeap mh(arr, k);


    for (int c = 0; c < M; ++c)
    {
        // Take next element from stream
        //x = W.at(count);
        // Nothing much to do for first k-1 elements
        if (count < k-1)
        {
            arr[count] = W.at(count);
            count++;
        }

        else
        {
            // If this is k'th element, then store it
            // and build the heap created above
            if (count == k-1)
            {
                arr[count] = W.at(count);
                mh.buildHeap();
            }

            else
            {
                // If next element is greater than
                // k'th largest, then replace the root
                if (W.at(count) < mh.getMax())
                    mh.replaceMax(W.at(count)); // replaceMin calls
                // heapify()
            }

            // Root of heap is k'th largest element
            count++;
        }
    }
    cout << mh.getMax() << endl;
    delete [] arr;
}

// Driver program to test above methods
int main()
{
    int N, M, K, element;
    deque<int> Sliding_Window;
    cin >> N >> M >> K;
    //cout << "N is " << N << endl;
    //cout << "M is " << M << endl;
    //cout << "K is " << K << endl;
    for(int i = 0; i < M; i++) {
        cin >> element;
        Sliding_Window.push_back(element);
    }
    kthSmallest(K, M, Sliding_Window);

    for(int i = M; i < N; i++) {
        cin >> element;
        Sliding_Window.pop_front();
        Sliding_Window.push_back(element);
        kthSmallest(K, M, Sliding_Window);
    }

    return 0;
} 
