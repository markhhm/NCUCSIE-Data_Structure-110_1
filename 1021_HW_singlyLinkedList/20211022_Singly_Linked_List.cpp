#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class Node
{
	public:
	    long long int data;
	    Node *next;
	    Node() {}
};
int getsize(Node *head)
{
	int size=0;
	
	while(head != NULL)
	{
		size++;
		
		head = head->next;
	}
	return size;
}
void addBack(long long int num, Node **head)
{
	Node *before = *head;
	
	Node *temp = new Node();
	temp->data = num;
	temp->next = NULL;
	
	if(*head == NULL)
	{
		*head = temp;
	}
	else
	{
		while(before->next != NULL)
		{
			before = before->next;
		}
		
		before->next = temp;
	}
}
void addFront(long long int num, Node **head)
{
	Node *temp = new Node();
	temp->data = num;
	temp->next = *head;
	
	*head = temp;
}
void addIndex(long long int index, long long int num, Node **head)
{
	Node *before = *head;
	
	for(long long int i=0; i<=index; i++)
	{
		if(getsize(*head) < index)
		{
			//cout << "getsize:" << getsize(*head) << ", i:" << i << endl;
			break;
		}
		
		if(index == 0)
		{
			addFront(num, head);
			
			break;
		}
		else if(index == i)
		{
			Node *temp = new Node();
			temp->data = num;
			temp->next = before->next;
			
			before->next = temp;
		}
		else if(i == getsize(*head)-1)
		{
			addBack(num, head);
			break;
		}
		else if(before->next == NULL)
		{
			//Malicious input
			
			/*if(index == i + 1)
			{
				//addBack(num, head);
			}*/
			
			break;
		}
		else if(index - i > 1)
		{
			before = before->next;
		}
	}
}
void deleteIndex(long long int num, Node **head)
{
	Node *before = *head;
	
	for(long long int i=0; i<=num; i++)
	{
		if(num == 0)
		{
			if(*head != NULL)
				*head = (*head)->next;
				
			break;
		}
		else if(before->next == NULL)
		{
			//Malicious input
			break;
		}
		else if(num - i == 1)
		{
			continue;
		}
		else if(i == num)
		{
			before->next = before->next->next;
		}
		else
		{
			before = before->next;
		}
	}
}
void spilt(Node **head)
{
	string word;
	
	while (1) 
    {
    	int num, index;
    	
    	cin >> word;
    	
        if(word == "addBack")
        {
        	cin >> num;
        	addBack(num, head);
		}	
		else if(word == "addFront")
		{
			cin >> num;
			addFront(num, head);
		}
		else if(word == "addIndex")
		{
			cin >> index;
			cin >> num;
			addIndex(index, num, head);
		}
		else if(word == "deleteIndex")
		{
			cin >> num;
			deleteIndex(num, head);
		}
		else if(word == "exit")
			break;
		else
		{
			//Malicious input
			break;
		}
    }
}
void print(Node *head)
{
	while(head != NULL)
	{
		cout << head->data << "-->" ;
		
		head = head->next;
	}
	
	if(head != NULL)
		cout << head->data << "-->null" << endl; // last element
	else
		cout << "null" << endl;
}
int main()
{
	string input;
	Node *head = NULL;
		
	//getline(cin, input);

	spilt(&head);
	
	print(head);
	
	return 0;
}
