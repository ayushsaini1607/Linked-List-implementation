#include<stdio.h>
#include<stdlib.h>

struct node{
   int info;
   struct node *link;
};

struct node *create_list(struct node *start);
void display(struct node* start);
int count(struct node* start);
int search(struct node *start,int data);
struct node *addatbeg(struct node* start,int data);
struct node *addatend(struct node* start,int data);
struct node *addafter(struct node* start,int data,int item);
struct node *addbefore(struct node* start,int data,int item);
struct node *addatpos(struct node* start,int data, int pos);
struct node *del(struct node* start,int data);
struct node *reverse(struct node* start);

int main()
{
   struct node *start=NULL;
   int choice,data,pos,item;
   while(1)
    {
        printf("\n1.Create List");
        printf("\n2.Display");
        printf("\n3.Count");
        printf("\n4.Search");
        printf("\n5.Add to empty list/Add at beginning");
        printf("\n6.Add at end");
        printf("\n7.Add after node");
        printf("\n8.Add before node");
        printf("\n9.Add at position");
        printf("\n10.Delete");
        printf("\n11.Reverse");
        printf("\n12.Quit");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice)
         {
             case 1: 
                   start=create_list(start);
                   break;
              
             case 2:
                   display(start);
                   break;
                
             case 3:
                  printf("\nNo of elements in the list : %d",count(start));
                  break;
             
             case 4:
                  printf("\nEnter element to be searched: ");
                  scanf("%d",&data);
                  printf("\n%d found at position %d",data,search(start,data));
                  break;
            
             case 5:
                  printf("\nEnter the element to be inserted : ");
                  scanf("%d",&data);
                  start=addatbeg(start,data);
                  break;
             
              case 6:
                   printf("\nEnter the element to be inserted : ");
                   scanf("%d",&data);
                   start=addatend(start,data);
                   break;
              
               case 7:
                   printf("\nEnter the element to be inserted : ");
                   scanf("%d",&data);
                   printf("\nEnter element after which to insert : ");
                   scanf("%d",&item);
                   start=addafter(start,data,item);
                   break;
                
                case 8:
                    printf("\nEnter the element to be inserted : ");
                    scanf("%d",&data);
                    printf("\nEnter the element before which to insert : ");
                    scanf("%d",&item);
                    start=addbefore(start,data,item);
                    break;
                
                case 9:
                   printf("\nEnter element to be inserted : ");
                   scanf("%d",&data);
                   printf("\nEnter position : ");
                   scanf("%d",&pos);
                   start=addatpos(start,data,pos);
                   break;

                case 10:
                    printf("\nEnter the element to be inserted : ");
                    scanf("%d",&data);
                    start=del(start,data);
                    break;
                
                case 11:
                     start=reverse(start);
                     break;
                
                case 12:
                     exit(1);
                default:
                     printf("\nWrong choice\n");         
         }
    }
}


void display(struct node *start)
{
    struct node *p;
    if(start==NULL)
     {
         printf("\nEmpty List");
         return;
     }

     p=start;
     printf("\nList is : ");
     while(p!=NULL)
      {
          printf("%d\t",p->info);
          p=p->link;   
      }
}

int count(struct node *start)
{
    struct node *p;
    p=start;
    int count=0;
    while(p!=NULL)
     {
         p=p->link;
         count++;
     }
    return count;
}

int search(struct node *start, int data)
{
    struct node *p=start;
    int pos=1;
    while(p!=NULL)
      {
          if(p->info==data)
            return pos;
           pos++;
           p=p->link;
      }
    return -1;
}

struct node *reverse(struct node *start)
{
    struct node *prev,*next,*ptr;
    prev=NULL;
    ptr=start;
    while(ptr!=NULL)
     {
         next=ptr->link;
         ptr->link=prev;
         prev=ptr;
         ptr=next;
     }
    start=prev;
    return start;
}

struct node *addatbeg(struct node *start,int data)
{
    struct node *temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->info=data;
    temp->link=start;
    start=temp;
    return start;
}

struct node *addatend(struct node *start, int data)
{
    struct node *p,*temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->info=data;
    p=start;
    while(p->link!=NULL)
      p=p->link;
    p->link=temp;
    temp->link=NULL;
    return start;
}

struct node *addafter(struct node *start,int data,int item)
{
    struct node *temp,*p;
    p=start;
    while(p!=NULL)
     {
         if(p->info==item)
          {
              temp=(struct node*)malloc(sizeof(struct node));
              temp->info=data;
              temp->link=p->link;
              p->link=temp;
              return start;
          }
          p=p->link;    
     }
     printf("%d not present in list",item);
     return start;
}

struct node *addbefore(struct node *start,int data, int item)
{
    struct node *temp,*p;
    if(start==NULL)
     {
         printf("\nList is empty");
         return start;
     }
    temp=(struct node*)malloc(sizeof(struct node));
    temp->info=data;
    if(item==start->info)
     {
         temp->link=start;
         start=temp;
         return start;
     }
    p=start;
    while(p->link!=NULL)
     {
         if(p->link->info==item)
          {
              temp->link=p->link;
              p->link=temp;
              return start;
          }
          p=p->link;
     }
     printf("\n%d is not present in the list\n",item);
}

struct node *addatpos(struct node *start, int data, int pos)
{
    struct node *temp,*p;
    int i;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->info=data;
    if(pos==1)
     {
         temp->link=start;
         start=temp;
         return start;
     }
    p=start;
    for(i=1;i<pos-1 && p!=NULL;i++)
       p=p->link;
    if(p==NULL)
       printf("\nThere are less than %d elements in the list",pos);
    else
    {
        temp->link=p->link;
        p->link=temp;
    }
    return start;   
}

struct node *create_list(struct node* start)
{
    int i,n,data;
    printf("\nEnter no of nodes : ");
    scanf("%d",&n);
    if(n<=0)
      return start;
    printf("\nEnter element to be inserted : ");
    scanf("%d",&data);
    start=addatbeg(start,data);
    for(i=2;i<=n;i++) 
     {
         printf("\nEnter element to be inserted : ");
         scanf("%d",&data);
         start=addatend(start,data);
     }
    return start;
}

struct node *del(struct node *start,int data)
{
    struct node *temp,*p;
    if(start==NULL)
     {
         printf("\nList is empty");
         return start;
     }
    if(start->info==data)
     {
         temp=start;
         start=start->link;
         free(temp);
         return start;
     }
    p=start;
    while(p->link!=NULL)
      {
          if(p->link->info==data)
           {
               temp=p->link;
               p->link=temp->link;
               free(temp);
               return start;
           }
          p=p->link;
      }
    printf("\nElement not found");
    return start;
}
