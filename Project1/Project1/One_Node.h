struct Node {

	int data;
	Node* next_ptr;
	Node();
	Node(int new_data);
};
 
class LinkedList {
private:
	Node* head;
	int lenth;
public:
	LinkedList(Node* headNode);
	void insertHead(int  next);
	const int getLength() { return lenth; }
	void showList();
	void insertTail(int newData);
	int findItem(int pos);
	void deletItem(int pos);
};