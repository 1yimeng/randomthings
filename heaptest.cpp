#include <iostream>
#include <vector>
#include "heap.h"

using namespace std;

int main()
{

// --------------- testing heap ------------------- //

//	BinaryHeap<int, int> h;
//	cout << "Before Insertion: " << endl;
//	h.print();
//	h.insert(42, 5);
//	cout << "After Insertion: " << endl;
//	h.print();
//	h.popMin();
//	cout << "After pop: " << endl;
//	h.print();


	BinaryHeap<int, int> h;

	vector<HeapItem<int, int> > heap;
	vector<HeapItem<int, int> > sorted;

	for(int i = 0; i < 1000000; i++)
        {
                heap.push_back({42, i});
        }
        for (int i = 0; i < heap.size(); i++)
        {
                int remain = heap.size()-i;
                int rand_idx = i + rand()%remain;
                HeapItem<int, int> temp = heap[i];
                heap[i] = heap[rand_idx];
                heap[rand_idx] = temp;
        }

	cout << "Before Sorting: " << endl;

	for (int i = 0; i < heap.size(); i++)
	{
		cout << "(" << heap[i].item << ", " << heap[i].key << ")" << endl;
	}
	cout << endl;
	
	for (int i = 0; i < heap.size(); i++)
	{
		h.insert(heap[i].item, heap[i].key);
	}
	for (int i = 0; i < heap.size(); i++)
	{
		sorted.push_back(h.min());
		h.popMin();
	}

	cout << "After Sorting: " << endl;
	for (int i = 0; i < sorted.size(); i++)
        {
                cout << "(" << sorted[i].item << ", " << sorted[i].key << ")" << endl;
        }
// ---- ------- end testing heap ------------------ //

	return 0;
}
