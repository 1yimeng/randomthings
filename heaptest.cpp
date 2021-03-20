#include <iostream>
#include <vector>
#include "heap.h"

using namespace std;

int main()
{

// --------------- testing heap ------------------- //

	BinaryHeap<int, int> h;
	h.insert(42, 12345);
	h.insert(42, 12346);
	h.insert(42, 12347);
	h.insert(42, 12348);
	h.insert(42, 12349);
	h.print();









// ------------ end testing heap ------------------ //

	return 0;
}
