// CMSC 341 - Spring 2021 - Project 3
// driver.cpp: sample driver for the RQueue class.

#include "rqueue.h"
using namespace std;
// Priority functions compute an integer priority for a student. Internal
// computations may be floating point, but must return an integer.

int priorityFn1(const Student &tudent);
int priorityFn2(const Student &student);

int main() {

  cout<<"Testing contructor and see if everything is set properly"<<endl;
  
  RQueue queue1(priorityFn1);
  RQueue queue2(priorityFn1);    
    if(queue1.numStudents() == 0){
    cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }

  if(queue1.getPriorityFn() == priorityFn1){
  cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }

  cout<<"Testing the insert function now"<<endl;

  // Testing one thing that get inserted
  
  Student student1("Sam",1,1,1,1);
  queue1.insertStudent(student1);


  if(queue1.numStudents() == 1){
    cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }

  cout<<"Testing clear now"<<endl;
  queue1.clear();
  // Testing if when a single thing is clear the num is 0 and the priority doesn't get changes
   if(queue1.numStudents() == 0){
    cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }

  if(queue1.getPriorityFn() == priorityFn1){
  cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }
  cout<<"Expected output : This heap is empty"<<endl;
   queue1.clear();

   cout<<"Testing mutlple insertation"<<endl;
   
  Student student2("Liz",5,1,2,0);
  Student student3("Nick",2,0,0,0);
  Student student4("Eva",4,3,2,1);

  queue1.insertStudent(student3);
  queue1.insertStudent(student2);
  queue1.insertStudent(student4);

  //Testing num should be 3
  if(queue1.numStudents() == 3){
    cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }

  cout<<"Testing clear with multiple nodes"<<endl;
  // The get num student and priotirtFn get tested too
  queue1.clear();
    if(queue1.numStudents() == 0){
      cout<<"Passed"<<endl;
    }
    else{
      cout<<"Failed"<<endl;
    }
    
    if(queue1.getPriorityFn() == priorityFn1){
      cout<<"Passed"<<endl;
    }
    else{
      cout<<"Failed"<<endl;
    }
    queue1.insertStudent(student3);
  queue1.insertStudent(student2);
  queue1.insertStudent(student4);
  cout<<"Testing printStudentQueue()"<<endl;
  queue1.clear();
  // Testing to see of thing got repeated
  cout<<"Queue with one thing"<<endl;
  queue1.insertStudent(student3);

  queue1.printStudentQueue();
  cout<<"Queue with two things"<<endl;

    queue1.insertStudent(student2);
   queue1.printStudentQueue();

   cout<<"Queue with three things"<<endl;
     queue1.insertStudent(student4);

     queue1.printStudentQueue();

     cout<<"New queue with foru things"<<endl;
   queue1.insertStudent(student1);
   queue1.printStudentQueue();

     cout<<"Testing the change priority thing"<<endl;
     // Getstudent worked as the set priotiy thing worked
     queue1.setPriorityFn(priorityFn2);
     queue1.printStudentQueue();

     if(queue1.numStudents() == 0){
	 cout<<"Failed"<<endl;
    }
    else{
      cout<<"Passed"<<endl;
    }


     cout<<"Testing getstudent"<<endl;
     // see if something got removed and if tis the right one
     queue1.printStudentQueue();

     queue1.getNextStudent();

     if(queue1.numStudents() == 3){
       cout<<"Passed"<<endl;
     }
     else{
       cout<<"Failed"<<endl;
     }
     queue1.printStudentQueue();

     // testing the error thing for when the getnextstudne thas ntohing left
     
     queue1.getNextStudent();
     queue1.getNextStudent();
     queue1.getNextStudent();

   cout<<"Testing the numstudent to 0"<<endl;
   if(queue1.numStudents() != 0){
       cout<<"Failed"<<endl;
    }
    else{
      cout<<"Passed"<<endl;
    }


   // testing the domain error
   //queue1.getNextStudent();
   /*
   RQueue queue1(priorityFn1);
  RQueue queue2(priorityFn1);
   */

   // Testing the assigment opertor
   queue2 = queue1;

   if(queue2.numStudents() == 0){
    cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }

  if(queue2.getPriorityFn() == priorityFn1){
  cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }
  // testing self assigment
  cout<<"Expected output : This is self assigment"<<endl;
  queue2 = queue2;

  // copy opertor
  /*
not sure right way to test copy opertor
  cout<<"Testing copy opertor"<<endl;
  RQueue queue3(queue2);

  

   if(queue3.numStudents() == 0){
    cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }

  if(queue3.getPriorityFn() == priorityFn1){
  cout<<"Passed"<<endl;
  }
  else{
    cout<<"Failed"<<endl;
  }
  */
  
  cout<<"Testing the merge with queue"<<endl;
  queue1.clear();
  queue2.clear();

  // Testing one node merging
  queue1.setPriorityFn(priorityFn2);
  queue2.setPriorityFn(priorityFn2);

  queue1.insertStudent(student1);
  queue2.insertStudent(student2);

  queue1.mergeWithQueue(queue2);



  return 0;
}

int priorityFn1(const Student&student) {
  //priority value is determined based on some criteria
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  int priority = student.getYear() + student.getMajor() + student.getGroup();
  return priority;
}

int priorityFn2(const Student&student) {
  //priority is determined by an officer in registrar office
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  return student.getPriority();
}
