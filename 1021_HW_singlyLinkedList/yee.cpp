#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

void create_singly_linked_list();
int empty();
void addBack(int element);
void addFront(int element);
void addIndex(int index,int element);
void deleteIndex(int index);
void print();


struct node{

    int data;
    struct node *link;

};


struct node *front, *rear;

int main(){
	
    create_singly_linked_list();
	string input,substr;
    int element,index;
    stringstream ss;
    getline(cin,input);
    ss << input;
    while (1){
        ss >> substr;
        if (substr == "addBack"){
            ss >> element;
            addBack(element);
        }
        else if (substr == "addFront"){
            ss >> element;
            addFront(element);
        }
        else if (substr == "addIndex"){
            ss >> index >> element;
            addIndex(index,element);
        }
        else if (substr == "deleteIndex") {
            ss >> index;
            deleteIndex(index);
        }
        else if (substr == "exit") {
            print();
            break;
        }
    }
}

void create_singly_linked_list(){

    
    front = (struct node*) malloc(sizeof(struct node));
    rear = (struct node*) malloc(sizeof(struct node));
    front->link = NULL;
    rear->link = NULL;

}

int empty(){

    if(front->link == NULL)
        return 1;
    else
        return 0;
}

void addBack(int element){
    struct node *new_node, *prev_node, *this_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    
    new_node->data = element;
    new_node->link = NULL;

    if(empty()){
        front->link = new_node;
        rear->link = new_node;
        
    }
    else{
        
        this_node = rear->link;
        this_node->link = new_node;
        rear->link = new_node;
        
    }
    
}

void addFront(int element){

    struct node *new_node, *prev_node, *this_node;

    new_node = (struct node *)malloc(sizeof(struct node));

    new_node->data = element;
    new_node->link = NULL;

    if(empty()){
        front->link = new_node;
        rear->link = new_node;
    }
    else
    {
        this_node = front->link;
        front->link = new_node;
        new_node->link = this_node;
    }
}
void addIndex(int index,int element){
    struct node *new_node, *prev_node, *this_node;
    
    
    new_node = (struct node *) malloc(sizeof(struct node));

    new_node->data = element;
    new_node->link = NULL;
    if(empty()){
        if(index == 0){
            front->link = new_node;
            rear->link = new_node;
        }
        else{
            return;
        }
    }
    else{
        this_node = front->link;
        int counter = 0;
        if(index == 0){
                new_node->link = this_node;
                front->link = new_node;
        }
        while(this_node->link != NULL){
           prev_node = this_node;
           this_node = this_node->link;
            counter++;
            if(counter == index){
                prev_node->link = new_node;
                new_node->link = this_node;
                return;
            }  
            
        }
        if(counter+1 == index){
            this_node->link = new_node;
            rear->link = new_node;
        }   
    }
    
}
void deleteIndex(int index){
    struct node *this_node,*prev_node, *temp_node;
    int counter = 0;

    prev_node = front;
    this_node = front->link;
    if(!empty()){
        while (this_node->link != NULL){
            if(counter == index){
                temp_node = this_node;
                prev_node->link = this_node->link;
                free(temp_node);
                return;
            }
            counter++;
            prev_node = this_node;
            this_node = this_node->link;
        }
        if(counter == index){
            temp_node = this_node;
            prev_node->link = NULL;
            rear->link = prev_node;
            free(temp_node);
        }
        else
            return;
    }
    else
        return;
}
void print(){
    struct node *this_node;
    if(!empty()){
        this_node = front->link;
        while (this_node->link != NULL){
            printf("%d-->",this_node->data);
            this_node = this_node->link;
        }
        printf("%d-->null",this_node->data);
    }
    else
        printf("null");
}