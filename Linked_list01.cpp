#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


class Node {
private:
	int Salary;
	float experience;
	string Name;
	Node* next;

public:
	Node() {
		Salary = 0;
		experience = 0.0;
		Name = "";
		next = nullptr;
	}

	Node(int Salary, float experience, string Name) {
		this->Salary = Salary;
		this->experience = experience;
		this->Name = Name;
		next = nullptr;
	}

	Node* get_next() 
	{ 
	   return next;
	}

	void set_next(Node* Next) 
	{
		next = Next;
	}

	int get_Salary() 
	{
		return Salary;
	}

	float get_experience()
	{ 
		return experience;
	}

	string get_Name()
	{ 
		return Name; 
	}

};


class linked_list {
private:
	Node* head;

	void split(Node* src, Node*& front, Node*& back) {
		if (src == nullptr || src->get_next() == nullptr) {
			front = src;
			back = nullptr;
			return;
		}
		Node* slow = src;
		Node* fast = src->get_next();
		while (fast != nullptr && fast->get_next() != nullptr) {
			slow = slow->get_next();
			fast = fast->get_next()->get_next();
		}
		front = src;
		back = slow->get_next();
		slow->set_next(nullptr);
	}

	Node* merge_by_salary(Node* a, Node* b) {
		if (!a) { return b; }
		if (!b) { return a; }
		if (a->get_Salary() <= b->get_Salary()) {
			a->set_next(merge_by_salary(a->get_next(), b));
			return a;
		}
		else {
			b->set_next(merge_by_salary(a, b->get_next()));
			return b;
		}
	}

	Node* merge_by_experience(Node* a, Node* b) {
		if (!a) { return b; }
		if (!b) { return a; }
		if (a->get_experience() <= b->get_experience()) {
			a->set_next(merge_by_experience(a->get_next(), b));
			return a;
		}
		else {
			b->set_next(merge_by_experience(a, b->get_next()));
			return b;
		}
	}

	Node* merge_by_name(Node* a, Node* b) {
		if (!a) { return b; }
		if (!b) { return a; }
		if (a->get_Name() <= b->get_Name()) {
			a->set_next(merge_by_name(a->get_next(), b));
			return a;
		}
		else {
			b->set_next(merge_by_name(a, b->get_next()));
			return b;
		}
	}

	Node* merge_sort(Node* h, int mode) {
		if (h == nullptr || h->get_next() == nullptr) { return h; }
		Node* front = nullptr;
		Node* back = nullptr;
		split(h, front, back);
		front = merge_sort(front, mode);
		back = merge_sort(back, mode);
		if (mode == 1) { return merge_by_salary(front, back); }
		else if (mode == 2) { return merge_by_experience(front, back); }
		else { return merge_by_name(front, back); }
	}

public:
	linked_list() { head = nullptr; }

	void sort_by_salary() {
		head = merge_sort(head, 1);
		cout << "List sorted by Salary.\n\n";
	}

	void sort_by_experience() {
		head = merge_sort(head, 2);
		cout << "List sorted by Experience.\n\n";
	}

	void sort_by_name() {
		head = merge_sort(head, 3);
		cout << "List sorted by Name.\n\n";
	}

	void insert_at_tail(int Salary, float experience = 0.0, string name = "") {
		Node* temp1 = new Node(Salary, experience, name);
		if (is_empty()) { head = temp1; return; }
		Node* temp = head;
		while (temp->get_next() != nullptr) { temp = temp->get_next(); }
		temp->set_next(temp1);
	}

	void insert_at_head(int Salary, float experience, string name) {
		Node* temp = new Node(Salary, experience, name);
		temp->set_next(head);
		head = temp;
	}

	void _delete(string name) {
		if (is_empty()) { return; }
		if (head->get_Name() == name) {
			Node* temp = head;
			head = head->get_next();
			delete temp;
			return;
		}
		Node* temp = head;
		while (temp->get_next() != nullptr && temp->get_next()->get_Name() != name) {
			temp = temp->get_next();
		}
		if (temp->get_next() == nullptr) {
			cout << "Data is not found in list.\n";
		}
		else {
			Node* temp1 = temp->get_next();
			temp->set_next(temp->get_next()->get_next());
			delete temp1;
		}
	}

	int Find_Salary(string name) {
		if (is_empty()) 
		{
			return -1; 
		}
		Node* temp = head;
		while (temp != nullptr && temp->get_Name() != name) 
		{
			temp = temp->get_next();
		}
		if (temp == nullptr) { cout << "Data is not present in list.\n"; return -1; }
		return temp->get_Salary();
	}

	int Find_max_Salary() {
		if (is_empty()) { return -1; }
		Node* temp = head;
		int largest = temp->get_Salary();
		while (temp != nullptr) {
			if (temp->get_Salary() > largest) { largest = temp->get_Salary(); }
			temp = temp->get_next();
		}
		return largest;
	}

	int Find_min_Salary() {
		if (is_empty()) { return -1; }
		Node* temp = head;
		int smallest = temp->get_Salary();
		while (temp != nullptr) {
			if (temp->get_Salary() < smallest) { smallest = temp->get_Salary(); }
			temp = temp->get_next();
		}
		return smallest;
	}

	void Reverse_list(Node* h) {
		if (is_empty()) { return; }
		Node* prev = nullptr;
		Node* curr = h;
		Node* nxt = nullptr;
		while (curr != nullptr) {
			nxt = curr->get_next();
			curr->set_next(prev);
			prev = curr;
			curr = nxt;
		}
		head = prev;
	}

	void Detect_and_remove_Cycle() {
		if (is_empty()) { return; }
		Node* one = head;
		Node* two = head;
		while (two != nullptr && two->get_next() != nullptr) {
			one = one->get_next();
			two = two->get_next()->get_next();
			if (one == two) { break; }
		}
		if (one == two) {
			one = head;
			while (one->get_next() != two->get_next()) {
				one = one->get_next();
				two = two->get_next();
			}
			two->set_next(nullptr);
		}
	}

	string Find_Middle() {
		if (is_empty()) { return " "; }
		Node* one = head;
		Node* two = head;
		while (two != nullptr && two->get_next() != nullptr) {
			one = one->get_next();
			two = two->get_next()->get_next();
		}
		return one->get_Name();
	}

	void Merge_Two_Sorted_Lists(Node* head1, Node* head2) {
		Node* temp1 = head1;
		Node* temp2 = head2;
		linked_list* l3 = new linked_list();
		while (temp1 != nullptr && temp2 != nullptr) {
			if (temp1->get_Name() <= temp2->get_Name()) {
				l3->insert_at_tail(temp1->get_Salary(), temp1->get_experience(), temp1->get_Name());
				temp1 = temp1->get_next();
			}
			else {
				l3->insert_at_tail(temp2->get_Salary(), temp2->get_experience(), temp2->get_Name());
				temp2 = temp2->get_next();
			}
		}
		while (temp1 != nullptr) {
			l3->insert_at_tail(temp1->get_Salary(), temp1->get_experience(), temp1->get_Name());
			temp1 = temp1->get_next();
		}
		while (temp2 != nullptr) {
			l3->insert_at_tail(temp2->get_Salary(), temp2->get_experience(), temp2->get_Name());
			temp2 = temp2->get_next();
		}
		l3->display();
		delete l3;
	}

	void Odd_Even_Linked_List(Node* h) {
		if (h == nullptr || h->get_next() == nullptr) { return; }
		Node* odd = h;
		Node* even = h->get_next();
		Node* evenHead = even;
		while (even != nullptr && even->get_next() != nullptr) {
			odd->set_next(even->get_next());
			odd = odd->get_next();
			even->set_next(odd->get_next());
			even = even->get_next();
		}
		odd->set_next(evenHead);
	}

	void display() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << "Name: " << temp->get_Name() << " | Salary: " << temp->get_Salary() << " | Experience: " << temp->get_experience() << endl;
			temp = temp->get_next();
		}
		cout << endl;
	}

	void saveToCSV(const string& filename, bool append = false) {
		ofstream file(filename, append ? ios::app : ios::out);
		if (!file.is_open()) { cout << "Error: Could not open " << filename << "\n"; return; }
		if (!append) { file << "Name,Salary,Experience\n"; }
		Node* temp = head;
		while (temp != nullptr) {
			file << temp->get_Name() << "," << temp->get_Salary() << "," << temp->get_experience() << "\n";
			temp = temp->get_next();
		}
		file.close();
		cout << "Data saved to " << filename << "\n\n";
	}

	Node* get_head()
	{
		return head;
	}

	void set_head(Node* h) 
	{ 
		head = h;
	}

	bool is_empty() 
	{
		return head == nullptr;
	}

	~linked_list() {
		Node* temp = head;
		while (temp != nullptr) {
			Node* next = temp->get_next();
			delete temp;
			temp = next;
		}
	}
};

int main() {
	linked_list l1;

	l1.insert_at_tail(39344, 1.2, "Ali");
	l1.insert_at_tail(46206, 1.4, "Ahmed");
	l1.insert_at_tail(37732, 1.6, "Sara");
	l1.insert_at_tail(43526, 2.1, "Zainab");
	l1.insert_at_tail(39892, 2.3, "Hassan");
	l1.insert_at_tail(56643, 3.0, "Fatima");
	l1.insert_at_tail(60151, 3.1, "Khalid");
	l1.insert_at_tail(54446, 3.3, "Noor");
	l1.insert_at_tail(64446, 3.3, "Yousuf");
	l1.insert_at_tail(57190, 3.8, "Aisha");
	l1.insert_at_tail(63219, 4.0, "Shan");
	l1.insert_at_tail(55795, 4.1, "Bilal");
	l1.insert_at_tail(56958, 4.1, "Mariam");
	l1.insert_at_tail(57082, 4.2, "Usman");
	l1.insert_at_tail(61112, 4.6, "Hina");
	l1.insert_at_tail(67939, 5.0, "Tariq");
	l1.insert_at_tail(66030, 5.2, "Sana");
	l1.insert_at_tail(83089, 5.4, "Imran");
	l1.insert_at_tail(81364, 6.0, "Rabia");
	l1.insert_at_tail(93941, 6.1, "Kamran");
	l1.insert_at_tail(91739, 6.9, "Sadia");
	l1.insert_at_tail(98274, 7.2, "Faisal");
	l1.insert_at_tail(101303, 8.0, "Amna");
	l1.insert_at_tail(113813, 8.3, "Zubair");
	l1.insert_at_tail(109432, 8.8, "Layla");
	l1.insert_at_tail(105583, 9.1, "Omer");
	l1.insert_at_tail(116970, 9.6, "Nimra");
	l1.insert_at_tail(112636, 9.7, "Saad");
	l1.insert_at_tail(122392, 10.4, "Zubair Khan");
	l1.insert_at_tail(121873, 10.6, "Layla Hassan");

	l1.saveToCSV("dataset.csv");

	cout << "=== Sorted by Salary ===\n";
	l1.sort_by_salary();
	l1.display();

	cout << "=== Sorted by Experience ===\n";
	l1.sort_by_experience();
	l1.display();

	cout << "=== Sorted by Name ===\n";
	l1.sort_by_name();
	l1.display();

	cout << "Middle employee : " << l1.Find_Middle() << endl;
	cout << "Max Salary      : " << l1.Find_max_Salary() << endl;
	cout << "Min Salary      : " << l1.Find_min_Salary() << endl;
	cout << "Ali's Salary    : " << l1.Find_Salary("Ali") << endl << endl;

	linked_list l2;
	int salary;
	float experience;
	string name;

	for (int i = 0; i < 2; i++) {
		cout << "Enter name: "; cin >> name;
		cout << "Enter salary: "; cin >> salary;
		cout << "Enter experience: "; cin >> experience;
		l2.insert_at_tail(salary, experience, name);
	}

	cout << "\nMerged sorted list:\n";
	l1.Merge_Two_Sorted_Lists(l1.get_head(), l2.get_head());

	l1.Reverse_list(l1.get_head());
	cout << "Reversed list:\n";
	l1.display();

	l1.Odd_Even_Linked_List(l1.get_head());
	cout << "Odd-Even rearranged list:\n";
	l1.display();

	l1.saveToCSV("updated_dataset.csv");

	system("pause");
	return 0;
}