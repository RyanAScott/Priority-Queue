
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <list>
#include <string>
#include <fstream>
using namespace std;

class AirportRecords {
public:
	string code;
	string name;
	string city;
	string country;
	int latitude_degree;
	int latitude_minutes;
	int latitude_seconds;
	string latitude_direction;
	int longitude_degree;
	int longitude_minutes;
	int longitude_seconds;
	string longitude_direction;
	int altitude;

	friend ostream& operator << (ostream& os, AirportRecords& r) {
		os << "(" << r.code << " " << r.name << " " << r.city << " " << r.country << " " << r.latitude_degree << " " <<
			r.latitude_minutes << " " << r.latitude_seconds << " " << r.latitude_direction << " " <<
			r.longitude_degree << " " << r.longitude_minutes << " " << r.longitude_seconds << " " <<
			r.longitude_direction << " " << r.altitude << ")";
		return os;
	}

}; // class for airport records

int heap_size = 0;
AirportRecords heaparr[17];

void Max_Heapify( int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i +2

	// If left child is larger than root
	if (l < heap_size && heaparr[l].altitude > heaparr[largest].altitude)
		largest = l;

	// if right child is larger than largest so far
	if (r < heap_size && heaparr[r].altitude > heaparr[largest].altitude)
		largest = r;

	// if largest is not root
	if (largest != i) {
		swap(heaparr[i], heaparr[largest]);

		// Recursively heapify the affected subtree
		Max_Heapify(largest);
	}// if
}// heapify


/*
Heap-Maximum (A)
--restores A
--requires: A.Heapsize > 0
--ensures: a copy of the key value at the location 1 is returned
	return A[1]
*/
AirportRecords Heap_Maximum() {
	return heaparr[0];
}

/*
Heap-Extract-Max (A)
--Updates A
--requires: A.heap-size > 0 and A satifies the max heap property
--ensures: A[1] is removed and returned and A.heap-size = #A.heap-size - 1 and
			A satisfies the max heap property
		if A.heap-size < 1 then
			error "heap underflow"
		max = A[1]
		A[1] = A[A.heap-size]
		A.heap-size = A.heap-size - 1
		Max_Heapify (A, 1)
		return max
*/


AirportRecords Heap_Extract_Max() {
	AirportRecords r;
	if (heap_size < 0){
		return r;
	}// if
	AirportRecords max = heaparr[0];
	heaparr[0] = heaparr[heap_size - 1];
	heap_size = heap_size - 1;
	Max_Heapify(0);
	return max;

}// Heap_Extract_Max


/*
Heap-Increase-Key (A, i, key)
--updates A
--requires: key > A[i] and A.heap-size > 0 and 
			A satisfies the max heap propery
--ensures: there exists a k such that A[k] = key and
			A.heap-size = heap-size[#A] and 
			A satisfies the max heap property
	if key < A[i] then
		error "new key is smaller than current key"
	A[i] = key 
	while i > 1 and A[Parent(i)] < A[i] do 
		exchange A[i] with A[Parent(i)]
		i = Parent(i)
*/

// def get help here

void Heap_Increase_Key(int i, int key) {
	if (key < heaparr[i].altitude) {
		cout << "Error: New key is smaller than current key";
	}
	heaparr[i].altitude= key;
	while (i > 0 && heaparr[(i-1) / 2].altitude < heaparr[i].altitude) {
		swap(heaparr[i], heaparr[(i-1) / 2]);
		i = (i-1) / 2;
	}
}



/*
Max-Heap-Insert (A, key)
--updates A
--requires: A satisfies the max heap property
--ensures: key is added to A and A satisfies the max heap property
	A.heap-size = A.heap-size + 1
	A[A.heap-size] = -∞
	Heap-Increase-Key (A, A.heap-size, key)
*/


void Max_Heap_Insert(int key, AirportRecords r) {
	heap_size = heap_size + 1;
	heaparr[heap_size - 1] = r;
	Heap_Increase_Key(heap_size - 1, r.altitude);
}





int main()
{
	// opening and printing values from file
	ifstream infile;
	AirportRecords r;
	int dataSize = 0;
	infile.open("air16.txt");

	if (infile.fail())
	{
		cout << "Your file didn't work.";
	}// if
	else {
		string s;
		infile >> dataSize;
		for (int i = 0; i < dataSize; i++) {
			infile >> r.code;
			infile >> r.name;
			infile >> r.city;
			infile >> r.country;
			infile >> r.latitude_degree;
			infile >> r.latitude_minutes;
			infile >> r.latitude_seconds;
			infile >> r.latitude_direction;
			infile >> r.longitude_degree;
			infile >> r.longitude_minutes;
			infile >> r.longitude_seconds;
			infile >> r.longitude_direction;
			infile >> r.altitude;
			//insert into PQ
			Max_Heap_Insert(r.altitude, r);
		}
		infile.close();
	}// else

	// Number 1: 
	cout << "Testing Heap_Maximum" << endl;
	 AirportRecords b = Heap_Maximum();
	 cout << b << endl;

	 // Number 2: 
	cout << endl;
	cout << "Testing Heap Extract Max: " << endl;
	AirportRecords a = Heap_Extract_Max();
	cout << a << endl;

	// Number 3: 
	cout << endl;
	cout << "This is before testing the Heap Increase Key function" << endl;
	cout << heaparr[7];

	Heap_Increase_Key(7, 99);
	cout << endl;
	cout << "This is after" << endl;
	cout << heaparr[7] << endl;

	// Number 4 and Number 5
	cout << endl;
	cout << "Testing Max_Heap_Insert " << endl;
	AirportRecords c;
	c.code = "NBO";
	c.name = "JomoKenyatta";
	c.city = "Nairobi";
	c.country = "Kenya";
	c.latitude_degree = 1;
	c.latitude_minutes = 19;
	c.latitude_seconds = 7;
	c.latitude_direction = "S";
	c.longitude_degree = 36;
	c.longitude_minutes = 55;
	c.longitude_seconds = 33;
	c.longitude_direction = "E";
	c.altitude = 5330;
	Max_Heap_Insert(c.altitude, c);
	AirportRecords d = Heap_Maximum();
	cout << "Newly inserted with the highest altitude: ";
	cout << d << endl;

	return 0;
}


