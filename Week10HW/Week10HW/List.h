//----------------------------------------------------------------------------
//
//  List template class
//    Declaration and Implementation
//
//  This class provides a proxy class for Lists using the Node Template class.
//	The Node class is completely hidden from the user, as are details of 
//  pointer use.
//
//  Declaration and implementation are all included in one file, because this
//  is a template.
//
//----------------------------------------------------------------------------
//
//  Author  : Paul Zoski
//
//  Modified: JL Popyack: 5/15/4.  reformatted
//            JL Popyack: 5/25/4.  insert(n,i) corrected so that n inserted before L[i]
//            JL Popyack: 5/8/5.   minor reformatting
//
//----------------------------------------------------------------------------		

#ifndef _LIST_TEMPLATE_H_
#define _LIST_TEMPLATE_H_
	
	#include "Node.h"
	#include <cassert>
	#include <ciso646>


//----------------------------------------------------------------------------
//
//----------------------------- Class Declaration ----------------------------
//
//----------------------------------------------------------------------------

template<typename T>
class List
{
  public:
  	
	//------------------------------------------------------
	//----- Constructors -----------------------------------
	//------------------------------------------------------
				
		List();
		List(const List<T> & L); // copy constructor

	//------------------------------------------------------
	//----- Inspectors -------------------------------------
	//------------------------------------------------------

		int size() const; // the size of the list
	
	//------------------------------------------------------
	//----- Mutators ---------------------------------------
	//------------------------------------------------------

		//------------------------------------------------------
		// insertion methods
		// (add elements to list)
		//------------------------------------------------------
	
			void push_front(T n); 
				// insert element at front of list
			void push_back(T n); 
				// insert element at end of list
			bool insert(T n, int index = 0); 
				// insert element before given location in list
				// insert(n,0) inserts at front of list
				// insert(n,size) inserts at end of list
				// returns false if insertion fails
				//   e.g. trying to insert an element in
				//        location 10 when the list has 5 Nodes

			void setSize(int n);
	
		//------------------------------------------------------
		// removal methods
		// (remove elements from list)
		//------------------------------------------------------
	
			bool pop_front();
				// remove first element from list
				// returns false if list is empty
			bool pop_back();
				// remove second element from list
				// returns false if list is empty
			void clear();
				// remove all elements from list
		
		//------------------------------------------------------
		// operators (must be part of class)
		//------------------------------------------------------
		
			T operator[](int index) const; 
				// allows "inspector" variety random access to 
				// list elements.  Changing the elements
				// through this operator is a little trickier
		
			List<T> & operator=(const List<T> & L);
	
	//------------------------------------------------------
	//----- Destructor -------------------------------------
	//------------------------------------------------------
	
		~List();

  private:
	Node<T> * head_; // first node in list
	int size_; // number of nodes in lists
};



//----------------------------------------------------------------------------
//
//--------------------------- Class Implementation ---------------------------
//
//----------------------------------------------------------------------------


	//------------------------------------------------------------------------
	//----- Constructors -----------------------------------------------------
	//------------------------------------------------------------------------
		
		template<typename T>
		List<T>::List()
		{
			head_ = NULL;
			size_ = 0;
		}
		
		
		template<typename T>
		List<T>::List(const List<T> & L)
		{
			// initialize this List to empty
			size_ = 0;
			head_ = NULL;
			
			if (L.size() != 0) 
			{
			// nothing else to do if source list is empty
				Node<T> * p = L.head_;
				while( p != NULL)
				{
					push_back(p->data());
					p = p->link();
				}
			}
		}

	//------------------------------------------------------------------------
	//----- Destructor -------------------------------------------------------
	//------------------------------------------------------------------------
		
		template<typename T>
		List<T>::~List()
		{
			// Node class destructor does the work for us!
			delete head_;
		}
		
	//------------------------------------------------------------------------
	//----- Inspectors -------------------------------------------------------
	//------------------------------------------------------------------------

		template<typename T>
		int List<T>::size() const
		{
			return size_;
		}
		
		template<typename T>
		void List<T>::setSize(int n)
		{
			size_ = n;
		}
		
		//--------------------------------
		//--------insertion methods--------
		//--------------------------------
		
			template<typename T>
			void List<T>::push_front(T n)
			{
				head_ = new Node<T>(n, head_);
				++size_;
			}
			
			template<typename T>
			void List<T>::push_back(T n)
			{
				if (head_ == NULL) // the list is empty
					push_front(n); // so put it at the front
				else
				{
					Node<T> * p = head_;
					while(p->link() != NULL) // advance p to last element
						p = p->link();
					// p now points to last element in list
					// add element to end of list
					p->link(new Node<T>(n));
					++size_;
				}
			}
			
			template<typename T>
			bool List<T>::insert(T n, int index)
			{
				assert(index >= 0);
				// user asks for impossible
				if (index > size_)
					return false;
					
				// this is really an insert at the front
				if (index == 0)
				{
					push_front(n);
					return true;
				}
				
				Node<T> * p = head_; 
					// head != NULL because size > 0 here
					// if size == 0 the method has ended by now
			
				// move p to point at element #index
				int count;
//				for(count = 0; count < index; count++)
				for(count = 1; count < index; count++)  // changed: JP, 5/25/4
					p = p->link();
			
				p->link(new Node<T>(n, p->link())); // insert the new element
				++size_; //increment list size
				return true; // success!
			}
				
		//-------------------------------
		//--------removal methods--------
		//--------------------------------
		
			template<typename T>
			bool List<T>::pop_front()
			{
				if(head_ == NULL) // can't pop empty list
					return false;
			
				Node<T> * to_delete = head_; 
				head_ = head_->link(); 
					// second element is new head
					// hey! that works for 1 element lists 
					
				to_delete->link(NULL); 
					// disconnect this element from list
					// prevents accidental destruction of entire list
					
				delete to_delete;
				--size_;
			
				return true;
			}
			
			template<typename T>
			bool List<T>::pop_back()
			{
				if(head_ == NULL) // can't pop empty list
					return false;
				
				if(head_->link() == NULL) // pesky 1 item list
					return pop_front();
			
				Node<T> * to_delete = head_;
				Node<T> * prev = head_;
				while(to_delete->link() != NULL)  // find last element
				{
					prev = to_delete; // find next to last element
					to_delete = to_delete->link();
				}
				prev->link(NULL); 
					// disconnect last element
					// this element is now the last one
					
				delete to_delete; // bye-bye
				--size_;
			
				return true;
			}
			
			template<typename T>
			void List<T>::clear()
			{
				delete head_;
				head_ = NULL;
				size_ = 0;
			}
		
	//------------------------------------------------------------------------
	//----- Operators ---------------------------------------------------------
	//------------------------------------------------------------------------
		
		template<typename T>
		T List<T>::operator[](int index) const
		{
			assert(index >= 0 and index < size_); // make sure index is legal
			assert(head_ != NULL); // doesn't work for empty lists
			Node<T> * p = head_;
		
			// move p to point at element #index
			int count;
			for(count = 0; count < index; count++)
				p = p->link();

			// return value of the Node
			return p->data();
		}
		
		template<typename T>
		List<T> & List<T>::operator=(const List<T> & L)
		{
			if (this != &L) // avoids the pesky A = A error
			{
				if (head_ != NULL) // if this list is non-empty
				{
					delete head_; // delete it to ensure it's not leaked
					head_ = NULL; // reset list
					size_ = 0;    // reset list size
				}
				
				if (L.size() != 0) // nothing else to do if source list is empty
				{
					Node<T> * p = L.head_;
					while( p != NULL)
					{
						push_back(p->data());
						p = p->link();
					}
				}
			}
			
			return *this;		
		}
#endif