#include <stdio.h>
#include <stdlib.h>


typedef struct NodeStruct Node;
struct NodeStruct{
           int data;
           Node *next;
           };
      
      
Node *createNode(char n){
         Node *newNode;
         newNode=(Node*)malloc(sizeof(Node));
         newNode->data=n;
         newNode->next=NULL;
         return newNode;
         }
Node *insertAtHead(Node *top,int n){
         Node *newNode;
         newNode =createNode(n);
         newNode->next=top;
         top=newNode;
         return top;
         }
             
void print(Node *largeInt,FILE*out){
           Node *curr;
           Node *current;
           curr=largeInt;
           current=NULL;
           while (curr!=NULL){
                 current=insertAtHead(current,curr->data);
                 curr=curr->next;
                 }
                 while (current!=NULL){
                         fprintf(out,"%d",current->data);
                         current=current->next;
                 }

    }
                        
Node *storeLargeInt(char intString []){
            Node *top;
        	top=NULL;
            int *c;
            c=(int*)malloc(sizeof(int));
            *c=0;
            while((intString [*c])!='\0'){                                	
                   top=insertAtHead(top, (intString [*c]-'0'));
                    (*c)++;
            }  
                 return top;
            }
            
Node * addLargeInt(Node *largeInt1, Node *largeInt2){
     Node * curr;
     Node * cur;
     Node* top3;
     curr = largeInt1;
     cur = largeInt2;
     top3=NULL;
     int *carry,  *sum;
     sum=(int*)malloc(sizeof(int));
     carry=(int*)malloc(sizeof(int));
     *carry=0;
     while(curr!=NULL && cur!=NULL){  
          *sum=(curr->data + cur->data + *carry)%10;
          top3=insertAtHead(top3, *sum);
          *carry=(curr->data + cur->data +*carry) /10;  
          curr=curr->next;
          cur=cur->next;
     }
     
      if(curr==NULL){
           while(cur!=NULL){
                *sum=(cur->data+*carry)%10;
                 top3=insertAtHead(top3, *sum);
                 *carry=(cur->data+*carry) /10;  
                 cur=cur->next;
               }
           }
     if(cur==NULL){
            while(curr!=NULL){
                 *sum=(curr->data+*carry)%10;
                 top3=insertAtHead(top3, *sum);
                 *carry=( curr->data+*carry) /10;  
                 curr=curr->next;
               }
           }
           
     if(*carry>0)
                top3=insertAtHead(top3, *carry);  
                return top3;
      }  
void formatPrint(Node *largeInt1, Node *largeInt2, Node *largeIntSum,FILE *out){  
    Node *top4;
    top4=largeIntSum;   
    print(largeInt1,out);
    fprintf(out," + ");
    print(largeInt2,out);
    fprintf(out," = ");
    while(top4!=NULL){
           fprintf(out,"%d",top4->data);
           top4=top4->next;
    }                  
    fprintf(out,"\n\n");
    }
    
Node * addLargeInt1(int a, Node *largeInt2){
     int curr;
     Node * cur;
     Node* top3;
     cur = largeInt2;
     top3=NULL;
     int carry, sum, temp;
     sum=0;
     carry=0;
  
	if(cur==NULL){
           
                 sum=a;
                 top3=insertAtHead(top3, sum);
               
      }

     while(cur!=NULL && a != 0){  
     		temp  = a%10;
          sum=(temp + cur->data + carry)%10; 
         top3=insertAtHead(top3, sum);
         carry=(temp + cur->data + carry)/10;  
          cur=cur->next;
          a = a/10;
     }  
	  
     if(carry == 1)
                top3=insertAtHead(top3, 1);  
                return top3;
      }  
void formatPrint1(int a, Node *largeInt2, Node *largeIntSum,FILE *out){  
    Node *top4;
    top4=largeIntSum;      
    fprintf(out,"%d",a);
    fprintf(out," + ");
    print(largeInt2,out);
    fprintf(out," = ");
    while(top4!=NULL){
           fprintf(out,"%d",top4->data);
           top4=top4->next;
    }                  
    fprintf(out,"\n\n");
    }  	                   
int main(){
	FILE *in=fopen("input.txt","r");
	FILE *out=fopen("output.txt","w");
    Node *top1;
	top1=NULL;
	Node *top2;
	top2=NULL; 
	Node *sum1;
	sum1=NULL;
	Node *sum2=NULL;
	Node *top3=NULL;
	char a[50];
	char b[50];
	char c;
	int n;
	char g[50];
	 while(!feof(in)) 
	{
	fscanf(in,"%c",&c);
	if(c=='A'){
	fscanf(in,"%s",&a);
	fscanf(in,"%s",&b);
    top1=storeLargeInt(a);
    top2=storeLargeInt(b);
    sum1=addLargeInt(top1,top2);
    formatPrint(top1,top2,sum1,out);
}
    if(c=='B'){
	fscanf(in,"%d",&n);
	fscanf(in,"%s",&g);
	top3=storeLargeInt(g);
    sum2=addLargeInt1(n,top3);
    formatPrint1(n,top3,sum2,out);
}
}
fclose(in);
fclose(out);

	system("pause");
	return 0;	
}
