// CMSC 341 - Spring 2021 - Project 3
// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
  /************************
   * To be implemented
   * *********************/
  _heap = nullptr;// set the heap to nullptr at the start
  _size = 0;
  priority = priFn;// This makes priority the function that the user wants
}

RQueue::~RQueue()
{
  /************************
   * To be implemented
   * *********************/
  clear();
  priority = nullptr;// Nullptr hear as this is when the prority should be nullptr as anyother time clear is called the heap is still used
}

RQueue::RQueue(const RQueue& rhs)
{
  /************************
   * To be implemented
   * *********************/
  if(numStudents() != 0){
    clear();// clear the size if there is something in the heap
  }
  
  if(rhs.numStudents() != 0){// merge the two thing if the rhs is not empty
    priority = rhs.priority;

    merge(_heap,rhs._heap);
    _size = rhs._size;

  }
  else{
    cout<<"There is nothing to copy as the rhs is empty"<<endl;
  }
}


RQueue& RQueue::operator=(const RQueue& rhs)
{
  /************************
   * To be implemented
   * *********************/
  if(this != &rhs){// Prevent self assigment
    if(numStudents() != 0){
    clear();
    }
    
    if(rhs.numStudents() != 0){// IF heap is not empty copy everything
      priority = rhs.priority;

      merge(_heap,rhs._heap);
      _size = rhs._size;

    }
      else{
	cout<<"There is nothing to copy as the rhs is empty"<<endl;
      }
      
    
  }
  else{
    cout<<"This is self assignment and such didn't work"<<endl;
  }
  return *this;
}

void RQueue::insertStudent(const Student& input) {
  /************************
   * To be implemented
   * *********************/
  Node * node = new Node(input);// Make sa node
  merge(_heap,node);// Than merge the heap with the new node
  _size += 1;
}

Student RQueue::getNextStudent() {
  /************************
   * To be implemented
   * *********************/
  if(numStudents() != 0){
     Student  student = _heap->getStudent();;// Get the student not dynamcally allocated
     Node * temp = _heap;
     _heap = temp->_left;

     merge(_heap,temp->_right);// Merge the new heap with the right side of orgianl heap
     _size -= 1;
     delete temp;
     return student;
     }
  else{// IF heap is empty than throw this error
    throw domain_error("This heap was empty");
  }
  
  }


void RQueue::mergeWithQueue(RQueue& rhs) {
  /************************
   * To be implemented
   * *********************/
    if(this != &rhs){
      if(priority == rhs.priority){// If priority is the same for both heap
	merge(_heap, rhs._heap);// Merge the heap
	
	_size = _size + rhs._size;


	rhs._heap = nullptr;// Clear rhs
	   
    }
    else{// IF proiotiy function is different than throw the error
      throw domain_error("The priorty function is wrong");
    }
    }
    else{
      cout<<"This is self merging"<<endl;
    }
    
}

void RQueue::clear() {
  /************************
   * To be implemented
   * *********************/
  if(_size != 0){
    recursiveclear(_heap);
    _size = 0;// Turn size empty here
    _heap = nullptr;
  }
  else{// IF heap is empty than throw this error
    cout<<"This heap is empty"<<endl;
  }
}

int RQueue::numStudents() const
{
  /************************
   * To be implemented
   * *********************/
  return _size;
}

void RQueue::printStudentQueue() const {
  /************************
   * To be implemented
   * *********************/
  recusrivePrint(_heap);
}

prifn_t RQueue::getPriorityFn() const {
  /************************
   * To be implemented
   * *********************/
  return priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
  /************************
   * To be implemented
   * *********************/
 
 
  int i = 0;
  int size = _size;
  RQueue temp_heap(priFn);
  for(i = 0; i < size ; i ++){// For until the the size of the stop

   
    Student temp = getNextStudent();
    temp_heap.insertStudent(temp);
  }
 priority = priFn; 
  _heap = temp_heap._heap;
  _size = temp_heap._size;
  temp_heap._heap = nullptr;
}

// for debugging
void RQueue::dump() const
{
  if (_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(_heap);
    cout << endl;
  }
}

// for debugging
void RQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->_left);
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_right);
    cout << ")";
  }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
  sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
       << ", year: " << student.getYear() << ", major: " << student.getMajorStr() 
       << ", group: " << student.getGroupStr();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getStudent();
  return sout;
}

void RQueue::recursiveclear(Node*& node){
  if(node == nullptr){
    return;
  }
  else{// call everrything that delte it


    recursiveclear(node->_left);
    recursiveclear(node->_right);
    delete node;
    node = nullptr;
  }
}


void RQueue::merge(Node*& node,  Node*  Bnode){
  if(node == nullptr){
    node = Bnode;
    
    return;
  }

  if(Bnode == nullptr){
    return;
  }

  if(priority(node->getStudent()) <  priority(Bnode->getStudent())){
    merge(node->_left, Bnode);
  }
  else{

    Node *temp = node;
    node = Bnode;
    merge(node->_left,temp);

    Node* placer = node->_right;
    node->_right = node->_left;
    node->_left = placer;




  }
    
}

void RQueue::recusrivePrint(Node*  node) const{
  if(node == nullptr){
    return;
  }
  else{// PRint using the student no pionter as student is not dynamically allocated
    Student student = node->getStudent();
    cout<<"["<<priority(student)<<"] Student: "<< student.getName()<<" , priority: "<<student.getPriority()<<" year: "<<student.getYear()<<", major: "<<student.getMajor()<<" group: "<<student.getGroup()<<endl;
      recusrivePrint(node->_left);
      recusrivePrint(node->_right);

  }
}
