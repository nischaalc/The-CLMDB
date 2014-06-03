//----------------------------------------------------------------------------
//
//  Node template class
//    Declaration and Implementation
//
//  This class provides a generalized "Node" type for use with linked lists.
//	A Node has a "data object" property and a link property.
//	The data object has a generic type T.
//	The link points to another Node.
//
//  Declaration and implementation are all included in one file, because this
//  is a template.
//
//----------------------------------------------------------------------------
//
//  Author:  Paul Zoski
//
//  Modified: JL Popyack: 5/15/4 - reformatted
//	          JL Popyack: 5/22/8 - changed LIST_DEBUG to static
//
//----------------------------------------------------------------------------		

#ifndef _NODE_TEMPLATE_H_
#define _NODE_TEMPLATE_H_


//----------------------------------------------------------------------------
//
//----------------------------- Global Variables -----------------------------
//
//----------------------------------------------------------------------------

	static bool LIST_DEBUG = true; 
		// displays extra output when debugging
		// set this to false for production level code
	


//----------------------------------------------------------------------------
//
//----------------------------- Class Declaration ----------------------------
//
//----------------------------------------------------------------------------

template<typename T>
class Node
{
  public:
  	
		//------------------------------------------------------
		//----- Constructors -----------------------------------
		//------------------------------------------------------
			
			Node();
			Node(T d, Node<T> * l = NULL);
			
		//------------------------------------------------------
		//----- Inspectors -------------------------------------
		//------------------------------------------------------
			  	
			T data() const;
			Node<T> * link() const;
			  	
		//------------------------------------------------------
		//----- Mutators ---------------------------------------
		//------------------------------------------------------
				  	
			void data(T d);
				// assigns new value to Node
				
			void link(Node<T> * l); 
				// points this Node to a different one
				// CAUTION! Potentially dangerous method -  
				// may cause trailing Nodes to be leaked
				  	
		//------------------------------------------------------
		//----- Destructor -------------------------------------
		//------------------------------------------------------
				
			~Node();
			
  private:
	Node<T> * link_;
	T data_;
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
		Node<T>::Node() 
		{
			link_ = NULL;
		    data_ = T(); // this statement assumes the existence of  
		                 // a default constructor for template class T
		}
		
		template<typename T>
		Node<T>::Node(T d, Node<T> * l)
		{
			link_ = l;
			data_ = d;
		}
		
	//------------------------------------------------------------------------
	//----- Destructor -------------------------------------------------------
	//------------------------------------------------------------------------
		
		template<typename T>
		Node<T>::~Node()
		{
			// avoid memory leaks by deleting the rest of the list
			if (link_ != NULL)
				delete link_;
		}
		
	//------------------------------------------------------------------------
	//----- Inspectors -------------------------------------------------------
	//------------------------------------------------------------------------
		
		template<typename T>
		T Node<T>::data() const
		{
			return data_;
		}
		
		template<typename T>
		Node<T>* Node<T>::link() const
		{
			return link_;
		}
		
	//------------------------------------------------------------------------
	//----- Mutators ---------------------------------------------------------
	//------------------------------------------------------------------------

		template<typename T>
		void Node<T>::data(T d)
		{
			data_ = d;
		}
		
		template<typename T>
		void Node<T>::link(Node<T> * l)
		{
			link_ = l;
		}
		
#endif