# BrushSort
BrushSort is a sorting algorithm that Frankensteined two other algorithms to
create a faster algorithm.  It does NOT sort in a stable fashion, which means
equal values may be swapped around, [that terminology is very bad, so click here
for a better
description](https://en.wikipedia.org/wiki/Sorting_algorithm#Stability).

About this software:
*   BrushSort was created by combining CombSort and InsertionSort.

*   I had the idea for this algorithm after watching Comb sort using the Sound
 of Sorting program from: http://panthema.net/2013/sound-of-sorting/
 While watching the Comb sort, I noticed that data gets reasonably sorted and
 that an Insertion sort would work well after a few passes with Comb.

*   Only 4 counting variables are needed, along with a single element to allow
 for swapping values around.

*   Only the initial use of the call stack is needed to use BrushSort.

*   It is possible to remove one or two of the counting variables, but these
 prevent a number of addition/subtraction calculations so keeping them should
 make the algorithm faster.

*   Using the largest data type that your CPU can handle for AmountTypes may
 increase performance at the cost of more RAM; although, with padding it may
 take up the same amount of RAM even if it is only supposed to use a smaller
 type.
  
*   It should compile for both C and C++.  Keep in mind when using C, you will
 need to define VariableType and AmountType both to work with your program.  It
 will throw compiler errors if you don't.
  
*   Usually works great on random data for the most part.  For sorted, mostly
 sorted, reverse sorted, and mostly similar data, see Possible Pitfalls below.

*   There are some tweakable values in the code, they've been marked as such in
 the comments of the code.

# Examples
C Usage Example:
```
  //Change VariableType and AmountType below to the appropriate values, (char, 
  //float, int, etc).
  #define VariableType double
  #define AmountType   unsigned int

  //Array to hold things.
  double values[100];

  //Do stuff to the array here.

  //Sort everything.
  BrushSort(values, sizeof(values));
  //Sort the first 20 items.
  BrushSort(values, 20);//Must be equal to or less than the size of the array.
```


C Usage Example:
```
  //Change VariableType and AmountType below to the appropriate values, (char, 
  //float, int, etc).
  #define VariableType uint64_t
  #define AmountType   uint64_t

  //A place to hold the size of the array.
  int amount = 10000;
  uint64_t *values = (uint64_t*)malloc(amount * sizeof(uint64_t));
  
  //Do stuff to the array here.
  
  //Sort everything.
  BrushSort(values, amount);
  //Sort the second half of items.
  BrushSort(&values[amount >> 1], amount >> 1);
```
  
C++ Usage Example:
```
  //Arrays of things.
  unsigned short things[100000];
  float          floaty[200];
  sint16_t       amount;
  
  //Do stuff to the arrays here.
  
  amount = sizeof(floaty);
  //Sort everything in floaty.
  BrushSort(floaty, amount);
  amount = sizeof(things);
  //Sort 1,696 values in things since amount can only hold a maximum value of: 
  //32,767 before it overflows.  It's undefined behavior by the C\C++ standards.
  BrushSort(things, amount);
  //Sort everything since the previous line was insane.
  BrushSort(things, sizeof(things));
```

# Testing
For testing, I limited the algorithms tested against BrushSort.  For the most
part, only Heap, Shell, Smooth, and Wiki sort were tested alongside of
BrushSort.  On average with random data, BrushSort tends to be 90% of the speed
of its fastest competitor; all four competitors were tested with the same data,
and the fastest speed was compared to BrushSort's speed.

Reasons for choosing only: Heap, Shell, Smooth, and Wiki:
1.  They were on the Wikipedia page:
 [Sorting Algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm).
2.  Their RAM usage was: 1, (does not include counting variables or call stack
 usage).
3.  Their time complexity was sane; I tested BrushSort and the others with
 arrays of over 1 billion in size, I'm not waiting for Bubble, Cocktail, or
Insertion to sort that many out.

# Possible Pitfalls
*   All of the tests I've been performing have been synthetic so far.  The
amount of data in the arrays has been between 0 and 1,073,741,824.

*   The data source for each test has simply been a value from `rand();` going
 into a holder array, which then would be copied into an array for each
algorithm to sort.  To clarify, they each sorted the same data.

*   Sorted, mostly sorted, or arrays with mostly the same values are wicked,
 tricksy, **FALSE**......  Okay, maybe not, but BrushSort doesn't handle them as
 well as other algorithms.