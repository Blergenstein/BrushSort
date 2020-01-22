#ifndef  BRUSHSORT_H
#define  BRUSHSORT_H
/*
MIT License

Copyright (c) 2020 Jeremy H. Cook

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

About this software:
BrushSort is a sorting algorithm that Frankensteined two other algorithms to
create a faster algorithm.  It does NOT sort in a stable fashion, which means
equal values may be swapped around, that terminology is very bad, so click here
for a better description:
https://en.wikipedia.org/wiki/Sorting_algorithm#Stability

BrushSort was created by combining CombSort and InsertionSort.

I had the idea for this algorithm after watching Comb sort using the Sound
of Sorting program from: http://panthema.net/2013/sound-of-sorting/
While watching the Comb sort, I noticed that data gets reasonably sorted and
that an Insertion sort would work well after a few passes with Comb.

Only 4 counting variables are needed, along with a single element to allow
for swapping values around.

Only the initial use of the call stack is needed to use BrushSort.

It is possible to remove one or two of the counting variables, but these
prevent a number of addition/subtraction calculations so keeping them should
make the algorithm faster.

Using the largest data type that your CPU can handle for AmountTypes may
increase performance at the cost of more RAM; although, with padding it may
take up the same amount of RAM even if it is only supposed to use a smaller
type.

It should compile for both C and C++.  Keep in mind when using C, you will
need to define VariableType and AmountType both to work with your program.  It
will throw compiler errors if you don't.

Usually works great on random data for the most part.  For sorted, mostly
sorted, reverse sorted, and mostly similar data, see Possible Pitfalls below.

There are some tweakable values in the code, they've been marked as such in
the comments of the code.

Examples
C Usage Example:
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

C Usage Example:
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

C++ Usage Example:
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

*/
#ifdef  __cplusplus
  //First is Greater Than Second, Return 1.
  template <class VariableType>
  static inline bool f_gt_s_rt_1(VariableType &frst, VariableType &scnd)
    {
      return frst > scnd;
    }

  #define NULLVALUE nullptr

  template <class VariableType, class  AmountType>
  void BrushSort( 
                  VariableType *array, 
                  AmountType    amount, 
                  bool        (*f_gt_s_rt_one)(VariableType &, VariableType &) 
                             = &f_gt_s_rt_1
                )
#else
  #define VariableType Type_Of_Variable_Required
  #define AmountType   Integer_Type_Required

  /*First is Greater Than Second, Return 1.*/
  #define f_gt_s_rt_one(Fst, Sec) (Fst > Sec)

  #define NULLVALUE NULL

  void BrushSort( VariableType *array, AmountType amount)
#endif
    {
      /*Ensure there's something to do.*/
      if(amount || array == NULLVALUE)
        {
          /*
            These can be 1, 2, 4, or 8 bytes.
            Current walks through the arrays.
          */
          AmountType     current;
          /*Forward should always be past current's position.*/
          AmountType     forward;
          /*Backwrd will be used later.*/
          AmountType     backwrd;
          /*Temporary swapspace.*/
          VariableType   swapspc;
          /*
            Anything less than 32 should just go through the insertion sort
            below.
          */
          if(amount > 32)
            {
              /*Total__ holds the distance between current and forward.*/
              AmountType total__ = amount;
              /*
                Total__ being greater than 24 is tweakable, but generally this
                is resonable-ish.
                While total__ is a resonable distance:
              */
              while(total__ > 24)
                {
                  /*
                    If it weren't for the bit restrictions, it would have been
                    preferred to avoid the conversion to, then from a float for
                    the next statement.  Casting the value to a double might
                    speed things up.
                    This is tweakable, but 3.8 is usually a good number to use.
                    Reduce total__ by itself divided by just under four.
                  */
                  total__ -= total__ / 3.8;
                  /*Ensure current is set to the front of the array.*/
                  current  = 0;
                  /*Ensure forward is set to where total__ is right now.*/
                  forward  = total__;
                  /*
                    Forward is incremented by one each step, so the following 
                    should be safe.
                    By not using <, this function can handle sizes of arrays at
                    the bit limit.  In other words, to handle an array of 255
                    bytes, 8 bit counters can be used.
                    While forward is not equal to amount:
                  */
                  while(forward != amount)
                    {
                      /*
                        If the current value is larger than the forward value,
                        swap them.
                      */
                      if(f_gt_s_rt_one(array[current], array[forward]))
                        {
                          swapspc        = array[current];
                          array[current] = array[forward];
                          array[forward] = swapspc;
                        };
                      /*
                        Increment both current and forward to keep them in
                        sync.
                      */
                      current += 1;
                      forward += 1;
                    };
                };
            };
          /*
            Set current to the second location in the array.
            Loop while current is not equal to amount.
            Increment by one each loop.
          */
          for(current = 1; current != amount; current += 1)
            {
              /*
                Setting this here saves two of the three subtraction
                calculations below.
                Set backwrd to current's position minus one.
              */
              backwrd = current - 1;
              /*
                If current's position is greater than or equal to the position
                before it, then there's no sense in doing anything below, save
                some nanoseconds and move on.
              */
              if(f_gt_s_rt_one(array[backwrd], array[current]))
                {
                  /*Set forward to current's position.*/
                  forward = current;
                  /*Save current's value for later use.*/
                  swapspc = array[current];
                  /*Do all of these:*/
                  do
                    {
                      /*Move whatever is in backwrd forward one place.*/
                      array[forward] = array[backwrd];
                      /*Decrease forward and backward one.*/
                      forward -= 1;
                      backwrd -= 1;
                      /*
                        While forward is not zero, and while the saved value in
                        swapspc is less than backwrd.
                      */
                    } while(forward && f_gt_s_rt_one(array[backwrd], swapspc));
                  /*Set forward's position to what was saved in swapspc.*/
                  array[forward] = swapspc;
                };
            };
        };
    }

#ifndef  __cplusplus
  #undef VariableType
  #undef AmountType
#endif

#endif//BRUSHSORT_H