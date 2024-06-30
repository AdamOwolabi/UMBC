//Name: Queue.cpp
//Project: CMSC 202 Project 3, Spring 2024
//Author:  Adam Owolabi
//Date:    05/02/2024
//Desc: This file implements the Queue.h file details for the class
//      The Queue.h/Queue.cpp are the driver class for this project.

#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated linked list
//Note: Because the linked list is a templated class,
//      there is only ONE file (Queue.cpp)

//Templated node class
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Queue {
 public:
  // Name: Queue() Queue from a linked list - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new queue where m_head and m_tail
  //                 point to nullptr and m_size = 0
  Queue();

  // Name: ~Queue() - Destructor
  // Desc: Used to destruct a Queue
  // Preconditions: There is a Queue
  // Postconditions: Queue is deallocated (including dynamically allocated nodes)
  //                 Can just call Clear()
  ~Queue();

  // Name: Queue (Copy Constructor)
  // Preconditions: Creates a copy of existing Queue in separate memory
  //                address (deep copy)
  //                Requires one already existing Queue
  // Postconditions: Copy of existing Queue
   Queue(const Queue& m);

  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: When two Queue objects exist, sets one to equal another
  //                Requires two Queue objects
  // Postconditions: When completed, you have two Queues in
  //                 separate memory addresses with the same
  //                 number of nodes with the same values in each node
 Queue<T>& operator= (Queue& m);

  // Name: PushBack
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Queue
  // Postconditions: Adds a new node to the end of the Queue.
  void PushBack(const T& data);

  // Name: PopFront
  // Preconditions: Queue with at least one node. 
  // Postconditions: Removes first node in the queue and
  //                 returns the data in the first node
  T PopFront();
  // Name: Display
  // Preconditions: Outputs the queue.
  // Postconditions: Displays the data in each node of queue
  // Required (used only for queue testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a Queue with at least one node
  // Postconditions: Returns whatever data is pointed at by m_head -
  //                 Does NOT remove node
  T Front();

  // Name: IsEmpty
  // Preconditions: Requires a queue
  // Postconditions: Returns if the queue is empty.
  bool IsEmpty();

  // Name: GetSize
  // Preconditions: Requires a queue
  // Postconditions: Returns m_size
  int GetSize();

  // Name: Find()
  // Preconditions: Requires a queue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  int Find(T num);

  // Name: Clear

  // Preconditions: Requires a queue
  // Postconditions: Deallocates and removes all nodes in a queue. No memory leaks
  void Clear();

  // Name: At
  // Precondition: Existing Queue
  // Postcondition: Returns object from Queue at a specific location
  // Desc: Iterates to node x and returns data from Queue
  T& At(int x);

  // Name: Swap(int)
  // Preconditions: Requires a queue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Example: Swap(1) would swap the node 0 with node 1 so
  //          that node 1 would now be m_head
  // Desc: Swaps two nodes by updating the pointers (not just the value)
  // Hint: Think about the special cases! Implement before Sort
  void Swap(int);

  // Name: Sort()
  // Preconditions: Requires a queue with a minimum of 2 nodes
  //                (otherwise notifies user)
  // Postconditions: Sorts the Queue (may use overloaded < or >).
  // Desc: This is used to sort anything in the Queue assuming the
  //       < or > is overloaded
  //        Uses bubble sort and Swap function above.
  //        Ensure working with queue_test before rest of project.
  // Note: Allowed to use the break command in just this function if necessary
  void Sort();

private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Queue Class Here***********
//**********All Functions Are Required Even If Not Used for Project**************
//**********No references to anything from Movie here*****************
// Name: Queue() Queue from a linked list - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new queue where m_head and m_tail
  //                 point to nullptr and m_size = 0
template <class T> 
Queue<T>::Queue(){
      //set default values
     m_head = nullptr;
     m_tail = nullptr;
     m_size = 0;
  }

  // Name: ~Queue() - Destructor
  // Desc: Used to destruct a Queue
  // Preconditions: There is a Queue
  // Postconditions: Queue is deallocated (including dynamically allocated nodes)
  //                 Can just call Clear()
template <class T> 
Queue<T>::~Queue(){
   //just call Clear()
   Clear();
 }

  // Name: Queue (Copy Constructor)
  // Preconditions: Creates a copy of existing Queue in separate memory
  //                address (deep copy)
  //                Requires one already existing Queue
  // Postconditions: Copy of existing Queue
template <class T> 
Queue<T>::Queue(const Queue& m){
      //set default values
      m_head = nullptr;
      m_tail = nullptr;
      m_size = 0;

      //point curr to source's m_head
      Node<T> *curr = m.m_head;

      //loop through to copy data
      while(curr != nullptr){
         PushBack(curr->GetData());
         curr = curr->GetNext();
      }
  }

  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: When two Queue objects exist, sets one to equal another
  //                Requires two Queue objects
  // Postconditions: When completed, you have two Queues in
  //                 separate memory addresses with the same
  //                 number of nodes with the same values in each node
template <class T> 
Queue<T>& Queue<T>::operator=(Queue& source){
  

   //check for self assignment;s
   if(this != &source)
   {
      Clear();

      //copy for pre-existing data
      Node<T> *curr = source.m_head;
      while(curr != nullptr){
         //cout << "copying " << curr->GetData() << endl;
         PushBack(curr->GetData());
         curr = curr->GetNext();
      }
   }
   //return newl copied object
   return *this;
}

  // Name: PushBack
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Queue
  // Postconditions: Adds a new node to the end of the Queue.
template <class T> 
void Queue<T>::PushBack(const T& data){
   //create a node with data given
   Node<T> *newNode = new Node(data);

   //set curr to m_head to traverse
   Node<T> *curr = m_head;

   //set m_head if queue is empty
   if(m_size == 0){
      //make new m_head
      m_head = newNode;
      curr = m_head;
      curr->SetData(data);
      curr->SetNext(nullptr);
   } else {
      //traverse the queue until last position
      while(curr->GetNext() != nullptr){
         curr = curr->GetNext();
      }
         //push back to the last
         curr->SetNext(newNode);
         newNode->SetNext(nullptr);

         //make new node your tail
         m_tail = newNode;
   }
    m_size++;
  }

  // Name: PopFront
  // Preconditions: Queue with at least one node. 
  // Postconditions: Removes first node in the queue and
  //                 returns the data in the first node
template <class T> 
T Queue<T>::PopFront(){
   //create a templated data. to be used to return the deleted node'data
   T data;

   if(GetSize() > 1){
      //pop from the front i.e m_head;
      Node<T> *curr = m_head;
      m_head = curr->GetNext();
      data = curr->GetData();
      delete curr;
      m_size--;
      
   }
   return data;
  }

  // Name: Display
  // Preconditions: Outputs the queue.
  // Postconditions: Displays the data in each node of queue
  // Required (used only for queue testing)
  template <class T> 
  void Queue<T>:: Display(){

   //Displays the data in each node of queue
   if(GetSize() == 0){
      return;
   }else{

      //traverse
      Node <T> *curr = m_head;
      while(curr != nullptr){
         cout << curr->GetData() << endl;
         curr = curr->GetNext(); 
      } 
   }



  }
  // Name: Front
  // Preconditions: Requires a Queue with at least one node
  // Postconditions: Returns whatever data is pointed at by m_head -
  //                 Does NOT remove node
  template <class T> 
  T Queue<T>::Front(){

   //returns data in the front
   Node <T> *curr = m_head;
   if(m_head != nullptr){
      curr = m_head;
   }
   return curr->GetData();
  }

  // Name: IsEmpty
  // Preconditions: Requires a queue
  // Postconditions: Returns if the queue is empty.
  template <class T> 
  bool Queue<T>::IsEmpty(){

   //check if queue is empty and return bool
      if(m_size == 0){
         return true;
      }
   return false;
  }

  // Name: GetSize
  // Preconditions: Requires a queue
  // Postconditions: Returns m_size
template <class T> 
int Queue<T>::GetSize(){
   //return size of queue
   return m_size;

  }

  // Name: Find()
  // Preconditions: Requires a queue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
template <class T> 
int Queue<T>::Find(T num){

   //look up the index of a data


   int index = 0;
   Node <T> *curr = m_head;

   if(m_head == nullptr){
      return -1;
   }

   while(curr != nullptr){
      if(curr->GetData() == num){
         return index;
      }
      curr = curr->GetNext();
      index++;
   }
   //index = -1;
   return -1;
  }

  // Name: Clear

  // Preconditions: Requires a queue
  // Postconditions: Deallocates and removes all nodes in a queue. No memory leaks
template <class T> 
void Queue<T>::Clear(){
      //destructor 

      Node<T> *curr = m_head;
      Node<T> *next = curr;

      //loop throught queue and delete categorically 
      while(curr != nullptr){
         // m_head = curr->GetNext();
         // curr = m_head;
         // delete curr;
         // m_size--;
         //cout << "deleting node " << curr->GetData() << endl;
         next = curr->GetNext();
         delete curr;
         curr = next;

      }
      m_head = nullptr;
      m_tail = nullptr;
      m_size = 0;
      cout << "Deallocating Queue" << endl;
  }

  // Name: At
  // Precondition: Existing Queue
  // Postcondition: Returns object from Queue at a specific location
  // Desc: Iterates to node x and returns datsa from Queue
template <class T> 
T& Queue<T>::At(int x){

   //looks up the data from index
   Node <T> *curr = m_head;
   for(int i = 0; i < x; i++){
      curr = curr->GetNext();
      }
   return curr->GetData();
   //return T();     
}

  // Name: Swap(int)
  // Preconditions: Requires a queue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Example: Swap(1) would swap the node 0 with node 1 so
  //          that node 1 would now be m_head
  // Desc: Swaps two nodes by updating the pointers (not just the value)
  // Hint: Think about the special cases! Implement before Sort
template <class T> 
void Queue<T>::Swap(int index){
   int currIndex = 0;

   if(index != 0){

     //create pointeres to keep track of last 2 previous nodes and curr node
         Node <T> *curr = m_head;
         Node <T> *prev = nullptr;
         Node <T> *beforePrev = nullptr;
         //Node <T> *prevNextNode = prev->GetNext();
      while(curr != nullptr){
         //if index match, swap the nodes
         if(currIndex == index){
            //swap the nodes
            if(prev != nullptr){
               
               //update the m_nexts
               prev->SetNext(curr->GetNext());
               //cout << "Prev: swapped: " << prev->GetData();
            } 
            //make sure you connect newly swapped to fit accordingly
            curr->SetNext(prev);

            //if frist index, update m_head
            if(index == 1){
               m_head = curr;
               return;
               //if index is last node, after swapping update m_tail
            }else if(index == m_size - 1){
               //change the m_tail;
                  
                  Node<T>* curr = m_head;
                  Node<T>* prev = nullptr;
                  //cout << "In here" << endl;
                  //use a loop fro safety purposes to update pointers
                  while (curr != nullptr && curr->GetNext() != nullptr) {
                     prev = curr;
                     curr = curr->GetNext();
                  }
                  if (prev != nullptr) {
                     prev->SetNext(m_tail);  // Update next pointer of second-last node
                  }
               m_tail = prev;
               return;
            }else{
               
               //update prev'previous pointers to curr.
               beforePrev->SetNext(curr);
               return;
            }
         }
         //move the pointers upwards
         beforePrev = prev;
         prev = curr;
         curr = curr->GetNext();
         currIndex++;

   }
   
  }else{
      cout << "Can't swap the frist index" << endl;
   }
} 

  // Name: Sort()
  // Preconditions: Requires a queue with a minimum of 2 nodes
  //                (otherwise notifies user)
  // Postconditions: Sorts the Queue (may use overloaded < or >).
  // Desc: This is used to sort anything in the Queue assuming the
  //       < or > is overloaded
  //        Uses bubble sort and Swap function above.
  //        Ensure working with queue_test before rest of project.
  // Note: Allowed to use the break command in just this function if necessary
template <class T> 
void Queue<T>::Sort(){
   if(m_size >= 2){

      //bubble sort it
      for (int i = 0; i <= m_size - 1; i++) {
         for(int j = 0; j < m_size - i - 1; j++) {
               //check if it's < 
               //swap the one ahead with the back one
               if(At(j+1) < At(j)) {
                  Swap(j+1);
                  //swapped = true;
               }
         }
      }
   } else{
      cout << "You need atleast two nodes to perform sorting" << endl;
      return;
   }
  }
#endif
