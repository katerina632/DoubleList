#include <iostream>
using namespace std;

template <class T>
class List
{
private:	
	struct Node
	{
		T value;	
		Node* next;	
		Node* prev;
	};

	Node* head;	
	Node* tail; 

	int size;	
public:
	List() : head(nullptr), tail(nullptr), size(0) { }

	~List() {
		DeleteAll();
	}

	List(const List& other)
	{	
		head = tail = nullptr;
		size = 0;		
		
		Node* temp = other.head;
		
		while (temp != 0)
		{			
			AddToTail(temp->value);
			temp = temp->next;
		}		
	}	

	List( List&&other)
	{
		size = other.size;
		head = other.head;
		tail = other.tail;

		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;

	}

	List& operator = (const List& other)
	{		
		if (this == &other)
			return *this;
		
		this->DeleteAll(); 

		Node* temp = other.head;

		while (temp != 0)
		{
			AddToTail(temp->value);
			temp = temp->next;
		}

		return *this;
	}

	List& operator=(List&& other) {
	
		if (this == &other)
			return *this;

		this->DeleteAll();

		size = other.size;
		head = other.head;
		tail = other.tail;

		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;		

		return *this;
	}

	bool IsEmpty() const
	{
		return size == 0;
	}

	int GetCount() const
	{
		return size;
	}

	
	void AddToHead(T value)
	{	
		Node* newElem = new Node;		
		newElem->value = value;		
		newElem->next = head;		
		newElem->prev = nullptr;
		
		if (IsEmpty())
		{			
			head = tail = newElem;
		}
		
		else
		{		
			head->prev = newElem;			
			head = newElem;
		}
		++size; 
	}
	
	void AddToTail(T value)
	{		
		Node* newElem = new Node;		
		newElem->value = value;		
		newElem->next = nullptr;		
		newElem->prev = tail;
		
		if (IsEmpty())
		{			
			head = tail = newElem;
		}		
		else
		{			
			tail->next = newElem;			
			tail = newElem;
		}
		++size; 
	}
	
	void DeleteHead()
	{		
		if (IsEmpty()) return;
		
		Node* temp = head->next;		
		delete head;
		
		if (temp == nullptr)
		{			
			head = tail = nullptr;
		}		
		else
		{			
			temp->prev = nullptr;			
			head = temp;
		}
		--size;
	}
	
	void DeleteTail()
	{		
		if (IsEmpty()) return;
		
		if (head->next == nullptr)
		{			
			delete head;			
			head = tail = nullptr;
		}		
		else
		{			
			Node* temp = tail->prev;			
			delete temp->next;			
			temp->next = nullptr;
			
			tail = temp;
		}
		--size; 
	}
	
	void Add(T value, int pos)
	{
		if (pos <= 0 || pos > size + 1) return;

		if (pos == 1)
		{
			AddToHead(value);
			return;
		}
		if (pos == size + 1)
		{
			AddToTail(value);
			return;
		}

		Node* newElem = new Node;
		newElem->value = value;
		Node* current;

		if (pos <= size / 2)
		{			
			current = head;
			int i = 1;
			while (i < pos)
			{				
				current = current->next;
				i++;
			}
		}
		else
		{
			
			current = tail;
			int i = 1;
			while (i <= size - pos)
			{				
				current = current->prev;
				i++;
			}
		}		

		newElem->prev = current->prev;
		current->prev->next = newElem;

		current->prev = newElem;
		newElem->next = current;

		++size; 
	}

	
	void Delete(int pos)
	{
		if (pos <= 0 || pos > size) return;

		if (pos == 1)
		{
			DeleteHead();
			return;
		}
		if (pos == size)
		{
			DeleteTail();
			return;
		}

		Node* current;

		if (pos <= size / 2)
		{
			current = head;
			int i = 1;
			while (i < pos)
			{
				current = current->next;
				i++;
			}
		}
		else
		{

			current = tail;
			int i = 1;
			while (i <= size - pos)
			{
				current = current->prev;
				i++;
			}
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;

		--size; 
	}

	void DeleteAll() {
		while (!IsEmpty())
			DeleteHead();
	}

	void Print() const
	{
		for (Node* current = head; current != nullptr; current = current->next)
		{			
			cout << current->value << ", ";
		}
	}

	List operator + (const List& other)
	{			
		List result = *this;
		Node* temp = other.head;
		
		while (temp != 0)
		{
			result.AddToTail(temp->value);
			temp = temp->next;
		}
		return result;
	}	

	List operator - ()
	{
		List result;
		Node* temp = head;		
		while (temp != 0)
		{
			result.AddToHead(temp->value);
			temp = temp->next;
		}
		return result;
	}

	T Find(T data)   
	{
		Node* current = head;
		for (int i = 0; i < size; i++)
		{
			if (current->value == data)
			{
				return i;
			}
			current = current->next;
		}
		return -1; 
	} 

	T Replace(T oldValue, T newValue)
	{
		Node* current = head;
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (current->value == oldValue)
			{
				current->value = newValue;
				count++;
			}
			current = current->next;
		}
		return count;
	}

};

int main()
{
	List<int> ls;

	ls.AddToHead(10);
	ls.AddToHead(15);
	ls.AddToHead(5);
	ls.AddToHead(20);

	ls.Print(); cout << endl;

	//cout << ls.Find(10) << endl;;
	//ls.DeleteHead();
	//ls.AddToTail(777);

	//////////////////////

	//ls.Print(); cout << endl;

	//ls.DeleteTail();
	//ls.DeleteTail();

	//ls.Print(); cout << endl;

	//ls.AddToHead(10);
	//ls.AddToHead(15);
	//ls.AddToHead(5);
	//ls.AddToHead(20);

	//ls.Print(); cout << endl;

	//ls.DeleteHead();
	//ls.AddToTail(777);

	//ls.Print(); cout << endl;

	//ls.DeleteTail();
	//ls.DeleteTail();

	//ls.Print(); cout << endl;

	//ls.AddToHead(55);
	//ls.AddToHead(33);

	//ls.AddToTail(990);
	//ls.AddToTail(676);

	//ls.Print(); cout << endl;

	//ls.Add(3, 3);
	//ls.Add(7, 7);

	//ls.Print(); cout << endl;

	//ls.Delete(3);
	//ls.Print(); cout << endl;

	//ls.Delete(7);
	//ls.Print(); cout << endl;

	return 0;
}