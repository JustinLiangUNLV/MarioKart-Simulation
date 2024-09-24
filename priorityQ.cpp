#include "priorityQ.h"
#include <cstdlib>
using namespace std;

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ() : capacity(1), size(0)
{
    heapArray = new priorityType[capacity + 1]; // create an array of size 2 and intialize starting index to 1
}

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ(const priorityQ<t1, t2>& copy) 
{
    capacity = copy.capacity; // copy the capacity over from the copy object
    size = copy.size; // copy the size over from the size object

    heapArray = new priorityType[copy.capacity + 1]; // add one to have index be able to start at 1
    for(size_t i = 1; i <= size; i++) // loop through original size, index starts at 1
    {
        heapArray[i] = copy.heapArray[i]; // copy over the array indexes into the current array indexes
    }

    itemToPQ = copy.itemToPQ; // copy over the map that was created
    
}

template <class t1, class t2>
const priorityQ<t1, t2>& priorityQ<t1, t2>::operator=(const priorityQ<t1, t2>& rhs)
{
    if (this != &rhs)
    {
        //Your code goes here
        delete[] heapArray; // delete the original array first

        capacity = rhs.capacity; // copy over capacity
        size = rhs.size; // copy over the size

        heapArray = new priorityType[capacity + 1]; // create an extra index to have the starting index = 1
        for(size_t i = 1; i <= size; i++) // loop through original size of the array starting at index 1
        {
            heapArray[i] = rhs.heapArray[i]; // copy over the indexes from rhs object to heapArray
        }

        itemToPQ = rhs.itemToPQ; // copy over the map
    }

    return *this;
}

template <class t1, class t2>
priorityQ<t1, t2>::~priorityQ()
{
    delete[] heapArray; // deallocate the array
    heapArray = nullptr; // set that array to point to nothing
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
    if(size + 1 >= capacity) // size + 1 to include the 0th index is greater than or equal to capacity
    {
        capacity *= 2; // double the apacity
        priorityType* newArray = new priorityType[capacity + 1]; // create a temp pointer to hold an array with new capacity
        for(size_t i = 1; i <= size; i++) // loop til size of array starting at index 1
        {
            newArray[i] = heapArray[i]; // populate this temp array
        }
        delete[] heapArray; // delete old array
        heapArray = newArray; // set heapArray to point to temp array
        newArray = nullptr; // set temp array to nullptr
    }
    priorityType temp; // create a temp priorityType
    temp.key = key; // assign the key
    temp.priority = priority; // assign the priority
    heapArray[++size] = temp; // increment the size then assign temp to the last index of the array
    itemToPQ[key] = size; // map the key, and have that index be the last index of the heapArray
    bubbleUp(size); // call bubble up given the new size
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
    if(size > 0)
    {
        swap(heapArray[1], heapArray[size]); // move last element to root position
        itemToPQ[heapArray[1].key] = 1; // update the new front with an index of 1
        itemToPQ.erase(heapArray[size].key); // remove swapped root from the map
        size--; // decrement the size of the heapArray
        bubbleDown(1); // call bubbleDown passing in the first index
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::decrease_priority(const t1& key, const t2& priority)
{
    heapArray[itemToPQ[key]].priority = priority; // map the key to give us an index and then heapArray[index]
    //to get the object's.priority and set it to the passed in priority
    bubbleUp(itemToPQ[key]); // call bubble up given that particular index
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    return heapArray[1].priority; // return the first index's priority
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    return heapArray[1].key; // return the first index's key
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    return size == 0; // return a boolean if size is equal to 0 or not
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    while(index > 1) // case where it hits root node
    {
        size_t parent = index / 2; // calculate the parent index

        if(heapArray[parent].priority < heapArray[index].priority) // case where parent's priority is lower than children's priority
        {
            break; // break if this is the case
        }
        swap(heapArray[parent], heapArray[index]); // otherwise swap places in the heapArray
        swap(itemToPQ[heapArray[parent].key], itemToPQ[heapArray[index].key]); // swap places in the map

        index = parent; // update index to be current node's parent index
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    while(true) // infinite loop
    {
        size_t leftChild = index * 2; // left child index value
        size_t rightChild = index * 2 + 1; // right child index value
        size_t parent = index; // parent holds the passed in index
        if(leftChild > size) // case where if the leftChild is greater than the size, it means it is a leaf and it should break
        {
            break;
        }
        if(leftChild <= size && rightChild > size) // case where there is only one child
        {
            if(heapArray[parent].priority < heapArray[leftChild].priority) // if parent index's priority is less than their child's priority
            {
                break; // then break
            }
            swap(heapArray[parent], heapArray[leftChild]); // otherwise swap places in the heapArray
            swap(itemToPQ[heapArray[parent].key], itemToPQ[heapArray[leftChild].key]); // and swap places in the map
            index = leftChild; // update the index to now the leftChild's index
        }
        if(leftChild <= size && rightChild <= size) // case where there is two children
        {
            if(heapArray[leftChild].priority < heapArray[rightChild].priority) // if the left child's priority is less than the right child's priority
            {
                if(heapArray[parent].priority < heapArray[leftChild].priority) // if the parent's priority is less than the left child's priority
                {
                    break; // break out of loop
                }
                swap(heapArray[parent], heapArray[leftChild]); // otherwise swap with left child in the heapArray
                swap(itemToPQ[heapArray[parent].key], itemToPQ[heapArray[leftChild].key]); // and swap places in the map
                index = leftChild; // update the index to now the leftChild's index
            }
            else // otherwise right child's priority is less than the left child's priority
            {
                if(heapArray[parent].priority < heapArray[rightChild].priority) // if the parent's priority is less than the right child's priority
                {
                    break; // break out of loop
                }
                swap(heapArray[parent], heapArray[rightChild]); // otherwise swap with right child in the heapArray
                swap(itemToPQ[heapArray[parent].key], itemToPQ[heapArray[rightChild].key]); // and swap places in the map
                index = rightChild; // update the index to now the right child's index
            }
        }
    }
}