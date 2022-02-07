#include <iostream>
#include <string>
#include <cassert>

class StringList
{
  public:
    StringList(std::string text);
    // You may declare other member functions for your test code to call
    void eraseThrees();
    void print();
  private:
    struct Node
    {
      char  value;
      Node* next;
      Node(char v, Node* n) : value(v), next(n) {}
    };
    Node* head;  // points to first Node in the list
};

StringList::StringList(std::string text)
{
    //  For example, StringList s("heap"); creates s containing
    //  a list with values  'h'  'e'  'a'  'p'
  head = nullptr;
  for (int k = text.size(); k > 0; k--)
    head = new Node(text[k-1], head);
}

void StringList::print(){
    Node *it = head;
    while(it != nullptr){
        std::cout << it->value;
        it = it->next;
    }
    std::cout << std::endl;
}

// You may implement other member functions here for test purposes,
// but you will not turn them in as part of your submission.

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE eraseThrees IMPLEMENTATION

void StringList::eraseThrees(){
    int i = 1;
    Node *it = head;
    while(it != nullptr){
        if(i%2 == 0){ 
            if(it->next == nullptr){
                return;
            }
            Node *tmp = it->next;
            it->next = tmp->next;
            delete tmp;
        }
        if(it->next == nullptr){
            return;
        }
        it = it->next;
        i++;
    }
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE eraseThrees IMPLEMENTATION

int main(int argc, char *argv[])
{
  std::string c = argv[1];
  StringList x(c);
  x.eraseThrees();
  x.print();
  // You might put some code here for test purposes, e.g., to verify
  // that x now contains  't'  'r'  'a'  'c'  'e'  'r'
  // You might run some other tests.
  std::cout << "Program finished" << std::endl;
}
