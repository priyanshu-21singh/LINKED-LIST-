#include <iostream>

class Node {
public:
    int data;
    Node* next;
    // constructor initializers..
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
//Destructor to prevent memory leaks...
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            //Before deleting the current node, the destructor stores the pointer to the next node in a temporary variable next
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(int index, int value) {
        if (index < 0 || index > size) {
            std::cout << "Index out of space\n";
            return;
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            if (size == 0) {
                tail = head;
            }
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
        ++size;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of space\n";
            return;
        }
        Node* toDelete = head;
        if (index == 0) {
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            toDelete = current->next;
            current->next = toDelete->next;
            if (current->next == nullptr) {
                tail = current;
            }
        }
        delete toDelete;
        --size;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void rotateRight(int k) {
        if (size <= 1 || k % size == 0) return;
        k = k % size;
        Node* current = head;
        for (int i = 0; i < size - k - 1; ++i) {
            current = current->next;
        }
        Node* newHead = current->next;
        current->next = nullptr;
        tail->next = head;
        head = newHead;
        current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        tail = current;
    }

    void reverse() {
        if (size <= 1) return;
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        tail = head;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    

    void append(int value) {
        Node* newNode = new Node(value);
        if (tail != nullptr) {
            tail->next = newNode;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        ++size;
    }

    void prepend(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (size == 0) {
            tail = head;
        }
        ++size;
    }

    void merge(LinkedList& other) {
        if (other.isEmpty()) return;
        if (isEmpty()) {
            head = other.head;
            tail = other.tail;
        } else {
            tail->next = other.head;
            tail = other.tail;
        }
        size += other.size;
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    void interleave(LinkedList& other) {
        Node* p1 = head;
        Node* p2 = other.head;
        Node* p1Next = nullptr;
        Node* p2Next = nullptr;
        while (p1 != nullptr && p2 != nullptr) {
            p1Next = p1->next;
            p2Next = p2->next;
            p1->next = p2;
            if (p1Next != nullptr) {
                p2->next = p1Next;
            }
            p1 = p1Next;
            p2 = p2Next;
        }
        if (p1 == nullptr && p2 != nullptr) {
            tail->next = p2;
            tail = other.tail;
        }
        size += other.size;
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    int getMiddle() const {
        if (isEmpty()) {
            std::cout << "List is empty\n";
            return -1;
        }
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    }

    int indexOf(int value) const {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            ++index;
        }
        return -1;
    }

    void split(int index, LinkedList& list1, LinkedList& list2) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of bounds\n";
            return;
        }
        list1 = LinkedList();
        list2 = LinkedList();
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            list1.append(current->data);
            current = current->next;
        }
        while (current != nullptr) {
            list2.append(current->data);
            current = current->next;
        }
    }

    void printList() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    std::cout << "Original List: ";
    list.printList();

    list.insert(2, 99);
    std::cout << "After inserting 99 at index 2: ";
    list.printList();

    list.remove(3);
    std::cout << "After removing element at index 3: ";
    list.printList();

    std::cout << "List size: " << list.getSize() << std::endl;
    std::cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl;

    list.rotateRight(2);
    std::cout << "After rotating right by 2: ";
    list.printList();

    list.reverse();
    std::cout << "After reversing the list: ";
    list.printList();

    list.prepend(100);
    std::cout << "After prepending 100: ";
    list.printList();

    LinkedList otherList;
    otherList.append(6);
    otherList.append(7);
    otherList.append(8);

    list.merge(otherList);
    std::cout << "After merging with another list: ";
    list.printList();

    LinkedList list1, list2;
    list.split(3, list1, list2);
    std::cout << "After splitting at index 3: \n";
    std::cout << "List 1: ";
    list1.printList();
    std::cout << "List 2: ";
    list2.printList();

    std::cout << "Middle element: " << list.getMiddle() << std::endl;
    std::cout << "Index of 99: " << list.indexOf(99) << std::endl;

    return 0;
}
