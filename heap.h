#ifndef HEAP_H
#define HEAP_H

#include <vector>

using namespace std;
// Only assumes the key type K is totally ordered and comparable via <
template <class T, class K>
struct HeapItem {
  T item;
  K key;
};

template <class T, class K>
class BinaryHeap {
public:
  // constructor not required because the only "initialization"
  // is through the constructor of the variable "heap" which is called by default

  // return the minimum element in the heap
  HeapItem<T, K> min() const;

  // insert an item with the given key
  // if the item is already in the heap, will still insert a new copy with this key
  void insert(const T& item, const K& key);

  // pop the minimum item from the heap
  void popMin();

  // returns the number of items held in the heap
  int size() const;

private:
  // the array holding the heap
  std::vector< HeapItem<T, K> > heap;

  //  will fix the heap property at index i and recurse with its parent
  void fixHeapUp(int i);

  // will fix the heap property at index i and recurse with the child
  // that received i's item (if appropriate)
  void fixHeapDown(int i);
};


/* Returns the size of the heap
 * */
template<class T, class K>
int BinaryHeap<T, K>::size() const
{
	return this->heap.size();
}

/* Inserts an element into the heap, and then 
 * Fixes the heap so that it maintains the heap
 * property.
 * Arguments:
 * 	item (const T&): Heap item. Used to store data.
 * 	key (const K&): Heap key. Used for comparison
 * */
template <class T, class K>
void BinaryHeap<T, K>::insert(const T& item, const K& key)
{	
	// creates a HeapItem
	HeapItem<T, K> element;
	element.item = item;
	element.key = key;
	// pushes to tthe back of vector
	this->heap.push_back(element);
	int idx = this->heap.size()-1;
	// recursively fix
	this->fixHeapUp(idx);
}


/* Recursively fixes from the bottom to the root
 * Arguments:
 * 	i (int): the index to the element in the 
 * 		vector representation of the heap
 * */
template <class T, class K>
void BinaryHeap<T, K>::fixHeapUp(int i)
{
	if (i != 0)
	{
		int parent_idx = (i-1)/2;
		// swap if out of place, then recurse
		if (this->heap[i].key < this->heap[parent_idx].key)
		{
			HeapItem<T, K> item = this->heap[i];
			this->heap[i] = this->heap[parent_idx];
			this->heap[parent_idx] = item;
			this->fixHeapUp(parent_idx);
		}
	}
}


/* Removes the root of the heap, then sets new root,
 * Recursively fixing the branch.
 * */
template <class T, class K>
void BinaryHeap<T, K>::popMin()
{
	int idx = this->heap.size()-1;
	if (this->heap.size() > 0)
	{
		this->heap[0] = this->heap[idx];
		this->heap.pop_back();
		this->fixHeapDown(0);

	}
}

/* Fixes heap from the top down
 * Arguments: 
 * 	i (int): the index of an element in the 
 * 		vector representation of the heap
 * */
template <class T, class K>
void BinaryHeap<T, K>::fixHeapDown(int i)
{	
	if (2*i+2 < this->heap.size())
	{
		HeapItem<T, K> lchild = this->heap[2*i+1];
		HeapItem<T, K> rchild = this->heap[2*i+2];
		int chosen;
		// determines smaller child
		if (lchild.key < rchild.key)
		{
			chosen = 2*i+1;
		} else {
			chosen = 2*i+2;
		}
		// swap and recurse if child is smaller than parent
		if (this->heap[chosen].key < this->heap[i].key)
		{
			HeapItem<T, K> temp = this->heap[i];
			this->heap[i] = this->heap[chosen];
			this->heap[chosen] = temp;
			this->fixHeapDown(chosen);
		}
		
	}
}

/* Returns the minimum element in the heap
 * without removing it
 * Returns:
 * 	this->heap[0] (HeapItem<T, K>): the minimum heap item
 * */
template <class T, class K>
HeapItem<T, K> BinaryHeap<T, K>::min() const
{	
	return this->heap[0];
}
#endif
