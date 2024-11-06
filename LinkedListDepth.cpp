        #include <iostream>
        #include <stack>
        #include <cassert>
        #include <string>
        using namespace std;
        
        using ItemType = string;
        
        struct Node {
            ItemType value;
            Node *next;
        };
        
        class LinkedList {
            
        private:
            Node *head;
            
        public:
            
              // default constructor
            LinkedList() : head(nullptr) { }
            
              // copy constructor
            LinkedList(const LinkedList& rhs);
            
              // Destroys all the dynamically allocated memory
              // in the list.
            ~LinkedList();
            
              // assignment operator
            const LinkedList& operator=(const LinkedList& rhs);
            
              // Inserts val at the front of the list
            void insertToFront(const ItemType &val);
            
              // Prints the LinkedList
            void printList() const;
            
              // Sets item to the value at position i in this
              // LinkedList and return true, returns false if 
              // there is no element i
            bool get(int i, ItemType& item) const;
            
              // Reverses the LinkedList
            void reverseList();
            
              // Prints the LinkedList in reverse order
            void printReverse() const;
            
              // Appends the values of other onto the end of this
              // LinkedList.
            void append(const LinkedList &other);
            
              // Exchange the contents of this LinkedList with the other one.
            void swap(LinkedList &other);
            
              // Returns the number of items in the Linked List.
            int size() const;
        };
        
        LinkedList::LinkedList(const LinkedList& rhs){
          if(rhs.head == nullptr){
            head = nullptr;
            return;
          }
          head = new Node;
          head -> value = rhs.head->value;
          head -> next = nullptr;

          Node *newCopy = head;

          for(Node *currentRhsPos = rhs.head -> next; currentRhsPos != nullptr; currentRhsPos = currentRhsPos -> next){
              Node *temp = new Node;
              temp -> value = currentRhsPos->value;
              temp -> next = nullptr;

              newCopy -> next = temp;
              newCopy = temp;
          }
            
        }
        LinkedList::~LinkedList(){
            for(Node *h = head; h != nullptr; h = h -> next){
                delete h;
            }
            head = nullptr;
        }
        const LinkedList& LinkedList::operator=(const LinkedList& rhs){
            if(this == &rhs){
              return *this;
            }
            while(head != nullptr){
              Node *temp = head;
              head = head -> next; 
              delete temp;
            }
            if(rhs.head == nullptr){
              head = nullptr;
              return *this;
            }
            head = new Node;
            head -> value = rhs.head -> value;
            head -> next = nullptr;
            Node* current = head;

            for (Node* h = rhs.head->next; h != nullptr; h = h->next) {
              current->next = new Node;
              current -> next -> value = h->value;
              current ->next ->next = nullptr;
              current = current->next;
            }

            return *this;
            }
        void LinkedList::insertToFront(const ItemType &val){
            Node *temp = new Node;
            temp -> value = val;
            temp -> next = head;
            head = temp;
        }
        void LinkedList::printList()const{
            for(Node *h = head; h != nullptr; h = h -> next){;
                cout << h->value << " ";
            }
            cout << endl;
        }
        bool LinkedList::get(int i, ItemType& item) const{
            int idx = 0;
            Node *h = head;
            for(; h != nullptr && idx < i; h = h ->next){
                idx++;
            }
            if(h == nullptr){
                return false;
            }
            item = h -> value;
            return true;
        }
        void LinkedList::reverseList(){
            Node* prev = nullptr;
            Node* current = head;
            Node* next = nullptr;

            while (current != nullptr) {
              next = current->next;  
              current->next = prev;  
              prev = current;      
              current = next;     
            }
            head = prev;  
        }
        void LinkedList::printReverse() const{
          stack <ItemType> list;

          for(Node *h = head; h != nullptr; h = h -> next){
              list.push(h->value);
          }
          while(!list.empty()){
              cout << list.top() << " ";
              list.pop();
          }
          cout << endl;
        }
        void LinkedList::append(const LinkedList &other){
            if(other.head == nullptr){
              return;
            }
            Node *endList = head;
            while(endList -> next != nullptr){
              endList = endList -> next;
            }
            for(Node *h = other.head; h != nullptr; h = h -> next){
                endList -> next = new Node;
                endList = endList -> next;
                endList -> value = h -> value;
                endList -> next = nullptr;
            }
            

        }
        void LinkedList::swap(LinkedList &other){
          Node *temp = head;
          head = other.head;
          other.head = temp;
        }
        int LinkedList::size() const{
            int count = 0;
            for(Node *h = head; h != nullptr; h = h -> next){
                count++;
            }
            return count;
        }

int main(){
    LinkedList h,l;
    h.insertToFront("Yo");
    h.insertToFront("No");
    l.insertToFront("Yes");
    l = h;
    l.printList();
    //Linked List Works.
    return 0;
}