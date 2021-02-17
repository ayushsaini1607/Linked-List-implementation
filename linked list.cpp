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
      void create_list();
      void display();
      void insert_beg(int);
      void insert_end(int);
      void insert_at_pos(int,int);
      void insert_after(int);
      int search(int);
      void delete_start();
      void delete_end();
      void delete_at_pos(int);
      void delete_by_data(int);
      void reverse();
      void concat(List);
};

void List::reverse()
{
    Node *forward,*curr,*back;
    curr=start;
    back=NULL;
    while(curr!=NULL)
     {
       forward=curr->link;
       curr->link=back;
       back=curr;
       curr=forward;
     }
     start=back;
}

void List::concat(List L2)
{
   if(L2.start==NULL)
     {
       cout<<"\nCannot conactenate lists. Passed list is empty!";
       return;
     }
   if(start==NULL)         //if list1 is empty, then list2 can be added to list1 i.e. start of list2 can be assigned to start of list1
    {
      start=L2.start;
      return;
    } 

   temp=start;
   while(temp->link!=NULL)
    {
      temp=temp->link;
    }
    temp->link=L2.start;   
}

void List::delete_at_pos(int pos)
{
   if(start==NULL)
     {
         cout<<"\nList is empty!";
         return;
     }
   temp=start;
   if(pos==0)
      {
          delete_start();
          return;
      }
   for(int i=0;i<pos-1 && temp->link!=NULL;i++)  //if nth node is to be deleted, temp points to (n-1)th node
     {
         temp=temp->link;
     }                                        
    if(temp->link==NULL)                 
      {                                  
          cout<<"\nThe position does not exist in the list!";
          return;
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
   temp=start;
   while(temp->link->link!=NULL)
    {
        temp=temp->link;
    }
   cout<<"\nDeleted Node: "<<temp->link->data;
   delete(temp->link);
   temp->link=NULL;
}

void List::delete_start()
{
   if(start==NULL)
     {
         cout<<"\nList is empty!";
         return;
     }
   temp=start;
   start=start->link;
   cout<<"Node deleted : "<<temp->data;
   delete temp;
}

void List::delete_by_data(int data)
{
    int pos=search(data);
    if(pos==-1)
      {
          cout<<"\nData not found";
          return;
      }
    delete_at_pos(pos);
}

void List::create_list()
{
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
     /* for(i=1;i<=n;i++)
       {
           cout<<"\nEnter data: ";
           cin>>x;
           Node *newnode=new Node(x); 
           if(start==NULL)
             {
                 insert_beg()
             }
           else
             {
                 temp->link=newnode;
                 temp=newnode;
             }
           cout<<"\nNode created";
       }  */
}

void List::display()
{
    if(start==NULL)
      {
          cout<<"\nList is empty";
          return;
      }
    temp=start;
    cout<<"\nList is: ";
    while(temp!=NULL)
     {
         cout<<temp->data<<"->";
         temp=temp->link;
     }
     cout<<"NULL";
}

void List::insert_beg(int data)
{
   temp=start;
   
   //assign the earlier value of start to link part of the new node
   //i.e. newnode->link=start; (this is done using the constructor)
   Node* newnode=new Node(data,start);   

   //Now newnode should mark the beginning of the list      
   start=newnode;
}

void List::insert_end(int data)
{
    temp=start;
    Node* newnode=new Node(data);
    if(start==NULL)       ///for empty list, if a new node is added the link part would be NULL, because there are no nodes ahead
      {
          start=newnode;
          return;
      }

      //traverse through the list until temp points to last node
    while(temp->link!=NULL)
         temp=temp->link;
    
    //the link part of earlier last node is now assigned the address of the new node
    temp->link=newnode;
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
    while(temp!=NULL)      //list traversal
     {
         if(temp->data==data)
           return pos;         //following zero indexing
         pos++;
         temp=temp->link;
     }
     return -1;             //error  values
}

void List::insert_after(int data)
{
    int pos=search(data),d;         //pos holds the position where data is found 
    if(pos==-1)
      {
          cout<<"\nData not found";
          return;
      }
    cout<<"\nEnter data to insert: ";
    cin>>d;
    insert_at_pos(pos+1,d);          //new data is to be inserted after the position where old data was found, so pos+1
}

void List::insert_at_pos(int pos,int data)
{
    int i;
    temp=start;
    if(pos==0)   
      {
          insert_beg(data);
      }

    //travesal through the list to reach the node after which insertion should take place
    //i<pos-1 so that temp points to the node after which insertion should take place  
    for(i=0;i<pos-1 && temp!=NULL;i++)   
      {
          temp=temp->link;
      }
    
    //if not enough elements are present in the list to reach pos or list is empty
    if(temp==NULL)
      {
          cout<<"\nThere are not "<<pos<<" elements in the list!";
          return;
      }

    Node *newnode=new Node(data,temp->link);
    /* above statement equates to
    Node *newnode=new Node(data);
    newnode->link=temp->link;   */

    temp->link=newnode;   //link part of temp now holds address of newnode
    cout<<"\nNode inserted at position "<<pos;
}

int main()
{
    List L,L2;
    int opt,pos,data;
    while(true)
    {
        cout<<"\nLinked List menu";
        cout<<"\n1.Create new List";
        cout<<"\n2.Display List";
        cout<<"\n3.Search";
        cout<<"\n4.Insert at beginning";
        cout<<"\n5.Insert at end";
        cout<<"\n6.Insert at position";
        cout<<"\n7.Search for data in list and add data after that node";
        cout<<"\n8.Delete node at start";
        cout<<"\n9.Delete node at end";
        cout<<"\n10.Delete node at position";
        cout<<"\n11.Search for data in list and delete that node";
        cout<<"\n12.Reverse List";
        cout<<"\n13.Concatenate";
        cout<<"\n14.Exit";
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
                cout<<"\nEnter data to search: ";
                cin>>data;
                L.insert_after(data);
                break;
            
            case 8:
                L.delete_start();
                cout<<"\nFirst Node deleted";
                break;
            
            case 9:
               L.delete_end();
               cout<<"\nLast Node deleted";
               break;
            
            case 10:
               cout<<"\nEnter position to delete node(0 indexing) : ";
               cin>>pos;
               L.delete_at_pos(pos);
               break;
            
            case 11:
               cout<<"\nEnter data to be deleted : ";
               cin>>data;
               L.delete_by_data(data);
               break;
            
            case 12:
                 cout<<"\nDisplaying original list...";
                 L.display();
                 L.reverse();
                 cout<<"\nDisplaying reversed list... ";
                 L.display();
                 break;

            case 13:
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

            case 14:
                 cout<<"\nManual exit";
                 exit(0);
            
            default:
               cout<<"\nInvalid Value!";
         }
    }
    return 0;
}