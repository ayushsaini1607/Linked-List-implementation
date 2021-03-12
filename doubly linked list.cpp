#include<iostream>
#include<process.h>

using namespace std;

class List;

class Node
{
    Node *prev;
    int data;
    Node *next;

    public:
      Node()
        {
            data=-1;
            prev=NULL;
            next=NULL;
        }

      Node(int d,Node *p=NULL, Node *n=NULL)
        {
            data=d;
            prev=p;
            next=n;
        }
     friend class List;
};

class List
{
    Node *start,*temp;
    public:
      List()
        {
            start=NULL;
            temp=NULL;
        }
       
      void create_list();    //done
      void display();       //done
      void insert_beg(int);   //done
      void insert_end(int);    //done
      void insert_at_pos(int,int);  //done
      int search(int);              //done
      void delete_start();          //done
      void delete_end();           //done
      void delete_at_pos(int);     //done
      void reverse();         //done
      void concat(List);    //done
};

int List::search(int data)
{
    if(start==NULL)
      {
         cout<<"\nList is empty!";
         return -1;
      }
    int pos=0;
    temp = start;
    while(temp!=NULL)
      {
          if(temp->data==data)
            return pos;
          temp=temp->next;
          pos++;
      }
    return -1;
}

void List::create_list()
{
   start=NULL;
   cout<<"\nCreating new list...";
   int n,i,data;
   cout<<"\nEnter no of nodes : ";
   cin>>n;
   if(n<=0)
    {
       cout<<"\nList not created!";
       return;
    }
    cout<<"\nEnter data : ";
    cin>>data;
    insert_beg(data);
    cout<<"\nNode added!";
    for(i=1;i<n;i++)
      {
        cout<<"\nEnter data : ";
        cin>>data;
        insert_end(data);
        cout<<"\nNode added!";
      }
    cout<<"\nList created successfully!";
}

void List::display()
{
   if(start==NULL)
     {
       cout<<"\nList is empty!";
       return;
     }
   temp=start;
   cout<<"\nList is : ";
   while(temp!=NULL)
    {
        cout<<temp->data<<"<->";
        temp=temp->next;
    }
    cout<<"NULL";
}

void List::insert_beg(int data)
{
    //prev of new node to be inserted is set to NULL and next of the new node is set to start
    Node *newnode = new Node(data,NULL,start);   

    //start now points to the newly created node
    start=newnode;
}

void List::insert_end(int data)
{
   //if list is empty, the new node to be created is the first and last and only node in the list
   if(start==NULL)
     {
       Node *newnode = new Node(data);
       start = newnode;
       return;
     }
   temp=start;
   while(temp->next!=NULL)
    {
      temp=temp->next;
    }
    Node *newnode = new Node(data,temp);
    temp->next = newnode;
}

void List::insert_at_pos(int pos, int data)
{
  if(pos<0)
    {
      cout<<"\nInvalid position!";
      return;
    }
  int i;
  temp=start;
  if(pos==0)
   {
     insert_beg(data);
     return;
   }

  //travesal through the list to reach the node after which insertion should take place
    //i<pos-1 so that temp points to the node after which insertion should take place 
  for(i=0;i<pos-1 && temp!=NULL;i++)
   {
     temp=temp->next;
   }
  
   //if not enough elements are present in the list to reach pos or list is empty
  if(temp==NULL)
    {
        cout<<"\nThere are not "<<pos<<" elements in the list!";
        return;
    }
  
  Node *newnode = new Node(data,temp,temp->next);
  /* above statement equates to
    Node *newnode=new Node(data);
    newnode->prev=temp; 
    newnode>next=temp->next  */

  temp->next = newnode;
  cout<<"\nNode inserted at position "<<pos;
}

void List::delete_start()
{
    if(start==NULL)
      {
        cout<<"\nList is empty!";
        return;
      }
    temp=start;
    start=start->next;
    if(start!=NULL)          //i.e the only node was deleted
       start->prev=NULL;
    cout<<"\nDeleted node : "<<temp->data;
    delete temp;
}

void List::delete_end()
{
    if(start==NULL)
      {
        cout<<"\nList is empty!";
        return;
      }
    temp=start;
    while(temp->next!=NULL)
      {
        temp=temp->next;
      }
    if(temp->prev!=NULL)         
         temp->prev->next=NULL;
    else                          //if there is only one node in the list
        start=NULL;
    cout<<"\nDeleted node : "<<temp->data;
    delete temp;
}

void List::delete_at_pos(int pos)
{
    if(start==NULL)
      {
        cout<<"\nList is empty!";
        return;
      }
    if(pos==0)
      {
         delete_start();
         return;
      }
     temp=start;
     for(int i=0;i<pos && temp!=NULL;i++)
       {
         temp=temp->next;
       }
     if(temp==NULL)
       {
         cout<<"\nThe position does not exist in the list!";
         return;
       }
      temp->prev->next=temp->next;
      if(temp->next!=NULL)
        temp->next->prev=temp->prev;
      else
        temp->next=NULL;
      cout<<"\nDeleted node : "<<temp->data;
      delete temp;    
}

void List::reverse()
{
    temp=start;

    //to make temp point to last node
    while(temp->next!=NULL)
      {
          temp=temp->next;
      }
    Node *link = NULL;       //temporary Node* to exchnage prev and next of each node
    start=temp;   //start now points to last node
    while(temp!=NULL)
     {
         link=temp->next;
         temp->next=temp->prev;
         temp->prev=link;         //exchanging prev and next in the above three lines
         temp=temp->next;         //moving to next node(i.e. previous node in the original list)
     }
}

void List::concat(List L1)
{
    if(L1.start==NULL)
     {
       cout<<"\nList 2 is empty! Cannot concat!";
       return;
     }
    if(start==NULL)
      {
        start = L1.start;
        return;
      }
     temp=start;
     while(temp->next!=NULL)
      {
        temp=temp->next;
      }
      temp->next=L1.start;
      L1.start->prev=temp;
}

int main()
{
    List L,L2;
    int opt,pos,data;
    while(true)
    {
        cout<<"\nCircular Linked List menu";
        cout<<"\n1.Create new List";
        cout<<"\n2.Display List";
        cout<<"\n3.Search";
        cout<<"\n4.Insert at beginning";
        cout<<"\n5.Insert at end";
        cout<<"\n6.Insert at position";
        cout<<"\n7.Delete node at start";
        cout<<"\n8.Delete node at end";
        cout<<"\n9.Delete node at position";
        cout<<"\n10.Reverse List";
        cout<<"\n11.Concatenate";
        cout<<"\n12.Exit";
        cout<<"\nEnter choice: ";
        cin>>opt;
        switch(opt)
         {
             case 1:
                L.create_list();
                break;
            
             case 2:
                L.display();
                break;
             
             case 3:
                cout<<"\nEnter data to search: ";
                cin>>data;
                pos=L.search(data);
                pos==-1?cout<<"\nData not found" : cout<<"\nData found at position "<<pos;
                break;

             case 4:
                cout<<"\nInserting element at beginning...";
                cout<<"\nEnter data: ";
                cin>>data;
                L.insert_beg(data);
                cout<<"\nNode inserted at beginning";
                break;

             case 5:
                cout<<"\nInserting element at end...";
                cout<<"\nEnter data: ";
                cin>>data;
                L.insert_end(data);
                cout<<"\nNode at inserted at end";
                break;
            
             case 6:
                cout<<"\nEnter position where to insert : ";
                cin>>pos;
                cout<<"\nEnter data: ";
                cin>>data;
                L.insert_at_pos(pos,data);
                break;

            
            case 7:
                L.delete_start();
                cout<<"\nFirst Node deleted";
                break;
            
            case 8:
               L.delete_end();
               cout<<"\nLast Node deleted";
               break;
            
            case 9:
               cout<<"\nEnter position to delete node(0 indexing) : ";
               cin>>pos;
               L.delete_at_pos(pos);
               break;
            
            case 10:
                 cout<<"\nDisplaying original list...";
                 L.display();
                 L.reverse();
                 cout<<"\nDisplaying reversed list... ";
                 L.display();
                 break; 

            case 11:
                 cout<<"\nCreating a new list to concat into first list...";
                 L2.create_list();
                 cout<<"\n\nDispalying first list :";
                 L.display();
                 cout<<"\n\nDisplaying second list";
                 L2.display();
                 L.concat(L2);
                 cout<<"\n\nDisplaying List 1 after concatenating List 2 with it :";
                 L.display();       
                 break;     

            case 12:
                 cout<<"\nManual exit";
                 exit(0);  
            
            default:
               cout<<"\nInvalid Value!";
         }
    }
    return 0;
}