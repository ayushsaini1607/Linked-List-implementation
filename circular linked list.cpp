#include<iostream>
#include<process.h>

using namespace std;

class Node
{
    public:
      int data;
      Node *link;
      Node()
        {
            data=0;
            link=NULL;
        }
      Node(int d,Node *l=NULL)
       {
           data=d;
           link=l;
       }
};

class List:public Node
{
   Node *start,*temp;
   public:
      List()
       {
           start=NULL;
           temp=NULL;
       }
      void create_list();  //done
      void display();    //done
      void insert_beg(int);  //done
      void insert_end(int);   //done
      void insert_at_pos(int,int);  //done
      int search(int);       //done
      void delete_start();   //done
      void delete_end();     //done
      void delete_at_pos(int);  //done
      void reverse();
      void concat(List);  //done
      int count();   //done
};

void List::concat(List L)
{
    if(L.start==NULL)
       {
           cout<<"\nCannot concatenate! List 2 is empty!";
           return;
       }
    if(start==NULL)
      {
          start=L.start;
          return;
      }
    temp=start;
    while(temp->link!=start)
      {
          temp=temp->link;
      }
    temp->link=L.start;
    temp=L.start;
    while(temp->link!=L.start)
      {
          temp=temp->link;
      }
    temp->link=start;     
}

void List::delete_at_pos(int pos)
{
   if(start==NULL)
     {
         cout<<"\nList is empty!";
         return;
     }
   if(pos>=count() || pos<0)
     {
         cout<<"\nPosition doesn't exist in the list!";
         return;
     }
   if(pos==0)
      {
          delete_start();
          return;
      }
    if(pos==count()-1)
      {
          delete_end();
          return;
      }
   temp=start;
   //if nth node is to be deleted, temp points to (n-1)th node
   for(int i=0;i<pos-1;i++)  
     {
         temp=temp->link;       
     }                                        
    Node *q=temp->link;
    temp->link=q->link;    
    cout<<"\nDeleted Node : "<<q->data;
    delete q;   
}

void List::delete_end()
{
   if(start==NULL)
     {
         cout<<"\nList is Empty!";
         return;
     }
   Node *curr,*prev;
   curr=start;
   temp=start;
   if(curr->link==start)      //single node
     {
        delete curr;
        start=temp=NULL;
        return;
     }
    
   while(curr->link != start)
     {
       prev=curr;
       curr=curr->link;
     }  
    prev->link=curr->link;            //i.e. prev->link=start
    cout<<"\nDeleted node: "<<curr->data;
    delete curr;
}

void List::delete_start()
{
   if(start==NULL)
     {
         cout<<"\nList is empty!";
         return;
     }
   if(start->link==start)
      {
        delete start;
        start=NULL;
        return;
      }
   temp=start;
   while(temp->link!=start)
     {
         temp=temp->link;
     }
    temp->link=start->link;
    temp=start;
    start=start->link;
    delete temp;
}

int List::count()
{
    if(start==NULL)
      {
          return -1;
      }
    
    int c=1;
    temp=start;
    while(temp->link!=start)
      {
          c++;
          temp=temp->link;
      }
    return c;
}

void List::reverse()
{
  Node *forward,*curr,*back;
  forward=start;
  curr=NULL;
  while(forward->link!=start)
   {
     back=curr;
     curr=forward;
     forward=forward->link;
     curr->link=back;
   }
   back=curr;
   curr=forward;
   forward=forward->link;
   curr->link=back;
   start=curr;
   temp=start;
   while(temp->link!=NULL)
    {
      temp=temp->link;
    }
   temp->link=start;
}

void List::insert_at_pos(int pos,int data)
{
    int i;
    if(pos>count())
      {
          cout<<"\nPosition does not exist in list ";
          return;
      }
    if(pos==0)   
      {
          insert_beg(data);
          return;
      }
     temp=start;

    //travesal through the list to reach the node after which insertion should take place
    //i<pos-1 so that temp points to the node after which insertion should take place  
    for(i=0;i<pos-1;i++)   
      {
          temp=temp->link;
      }

    Node *newnode=new Node(data,temp->link);
    /* above statement equates to
    Node *newnode=new Node(data);
    newnode->link=temp->link;   */

    temp->link=newnode;   //link part of temp now holds address of newnode
    
    cout<<"\nNode inserted at position "<<pos;
}

void List::display()
{
    if(start==NULL)
      {
          cout<<"\nList is empty";
          return;
      }
    temp=start;
    cout<<"\nList is : ";
    do{
        cout<<temp->data<<"->";
        temp=temp->link;
    }while(temp!=start);
    cout<<"\b\b  ";
}

int List::search(int data)
{
   int pos=0;
   if(start==NULL)
     {
         cout<<"\nEmpty List";
         return -1;                //error values
     }
    temp=start;
    while(temp!=start)      //list traversal
     {
         if(temp->data==data)
           return pos;         //following zero indexing
         pos++;
         temp=temp->link;
     }
     return -1;             //error  values
}

void List::create_list()
{
      start=NULL;
      cout<<"\nCreating new list";
      int n,i,data;
      cout<<"\nEnter no of nodes : ";
      cin>>n;
      if(n<=0)
        {
            cout<<"\nList not created";
            return;
        }
     cout<<"\nEnter data: ";
     cin>>data;
     insert_beg(data);
     cout<<"\nNode added";
     for(i=1;i<n;i++)
         {
              cout<<"\nEnter data : ";
              cin>>data;
              insert_end(data);
              cout<<"\nNode added";
         }
}

void List::insert_beg(int data)
{
   Node *newnode=new Node(data,start);
   //cout<<"\nnewnode = "<<newnode<<"\tnewnode->link = "<<newnode->link;
   temp=start;
   if(start==NULL)
     {
         start=newnode;
         start->link=start;
         //cout<<"\n start= "<<start<<"\tstart data = "<<start->data<<"\tstart link= "<<start->link;
         return;
     }
   while(temp->link!=start)
     {
         temp=temp->link;
     }
   start=newnode;
   temp->link=start;
   //cout<<"\n start= "<<start<<"\tstart data = "<<start->data<<"\tstart link= "<<start->link;
}

void List::insert_end(int data)
{
    temp=start;
    Node* newnode=new Node(data,start);
    if(start==NULL)       //for empty list, if a new node is added the link part would be NULL, because there are no nodes ahead
      {
          start=newnode;
          start->link=start;
          return;
      }

      //traverse through the list until temp points to last node
    while(temp->link!=start)
         temp=temp->link;
    
    //the link part of earlier last node is now assigned the address of the new node
    temp->link=newnode;
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
                cout<<"\nList created successfully!";
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
                 cout<<"\nList created successfully!";
                 cout<<"\nDispalying first list :";
                 L.display();
                 cout<<"\nDisplaying second list";
                 L2.display();
                 L.concat(L2);
                 cout<<"\nDisplaying List 1 after concatenating List 2 with it :";
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