#include <iostream>
#include <stdio.h>
#define ITERATORS_AMOUNT 10
#define MAX_INPUT_SIZE 4
#define BEG "BEG"
#define END "END"

using namespace std;

struct Element {
    unsigned long long int number;
    Element* next;
    Element* prev;
    Element() {
        next = nullptr;
        prev = nullptr;
        number = NULL;
    }
};
struct List {
    List() {
        first = nullptr;
        last = nullptr;
        isListEmpty = true;
        for (int i = 0; i < ITERATORS_AMOUNT; i++) {
            iterators[i] = nullptr;
        }
    }
    Element* first;
    Element* last;
    bool isListEmpty;
    Element* iterators[ITERATORS_AMOUNT];
    void addAfter(Element* element, unsigned long long int number);
    void addBefore(Element* element, unsigned long long int number);
    void initIterator(Element* element, int number);
    void moveIteratorUp(Element* element, int number);
    void moveIteratorDown(Element* element, int number);
    void removeElement(Element* element);
    void printElement(char whichElements[MAX_INPUT_SIZE]);
    void deleteList() ;

};

void List::addAfter(Element* element, unsigned long long int number) {
    Element* newElement = new Element;
    if (!isListEmpty == false) {
        first = newElement;
        last = newElement;
        first->number = number;
        last->number = number;
        isListEmpty = false;
    }
    else {
        if (element->next == nullptr) {
            element->next = newElement;
            newElement->prev = element;
            last = newElement;
        }
        else {
            newElement->prev = element;
            newElement->next = element->next;
            newElement->prev->next = newElement;
            newElement->next->prev = newElement;
        }
        newElement->number = number;
    }
    
}
void List::addBefore(Element* element, unsigned long long int number) {
    Element* newElement = new Element;
    if (!isListEmpty == false) {
        first = newElement;
        last = newElement;
        first->number = number;
        last->number = number;
        isListEmpty = false;
    }
    else {
        if (element->prev == nullptr) {
            element->prev = newElement;
            newElement->next = element;
            first = newElement;
        }
        else {
            newElement->next = element;
            newElement->prev = element->prev;
            newElement->next->prev = newElement;
            newElement->prev->next = newElement;
        }
        newElement->number = number;
    }

}
void List::initIterator(Element* element, int number) {
    iterators[number] = element;
}
void List::moveIteratorUp(Element* element, int number) {
    if (element->next == nullptr) {
        iterators[number] = last;
    }
    else {
        iterators[number] = element->next;
    }
}
void List::moveIteratorDown(Element* element, int number) {
    if (element->prev == nullptr) {
        iterators[number] = first;
    }
    else {
        iterators[number] = element->prev;
    }
}
void List::removeElement(Element* element) {
    if (element->next == nullptr && element->prev == nullptr) {
        for (int i = 0; i < ITERATORS_AMOUNT; i++) {
            iterators[i] = nullptr;
        }
        first = nullptr;
        last = nullptr;
        delete element;
        isListEmpty = true;
    }
    else {
        for (int i = 0; i < ITERATORS_AMOUNT; i++) {
            if (iterators[i] == element) {
                if (iterators[i]->next == nullptr) {
                    iterators[i] = last;
                    iterators[i] = element->prev;
                    element->prev->next = nullptr;
                }
                else {
                    iterators[i] = element->next;
                }
            }
        }
        if (element->next == nullptr) {
            last = element->prev;
            last->next = nullptr;
        }
        else if (element->prev == nullptr) {
            first = element->next;
            first->prev = nullptr;
        }
        else {
            element->prev->next = element->next;
            element->next->prev = element->prev;
        }
        delete element;
    }
    
}
void List::printElement(char whichElements[MAX_INPUT_SIZE]) {
    if (first == nullptr) {
        return;
    }
    else {
        if (!strcmp("ALL", whichElements)) {
            Element* temp = first;
            bool find = true;
            do {
                if (temp->next == nullptr) {
                    cout << temp->number << endl;
                    find = false;
                }
                else {
                    cout << temp->number << " ";
                    temp = temp->next;
                }
            } while (find);
        }
        else {
            cout << iterators[(int)whichElements[0] - 48]->number << endl;
        }
    }
    
}
void List::deleteList() {
    if (isListEmpty) {
        return;
    }
    else {
        Element* temp = first;
        Element* temp_next;
        while (temp->next != nullptr) {
            temp_next = temp->next;
            delete temp;
            temp = temp_next;
        }
    }
    for (int i = 0; i < ITERATORS_AMOUNT; i++) {
        iterators[i] = nullptr;
    }
    
}

int main() {
    List* list = new List;
    char instruction;
    char instruction2;
    unsigned long long int number;
    char position[MAX_INPUT_SIZE];
    while (cin >> instruction) {
        switch (instruction) {
        case 'A':
            cin >> instruction2;
            cin >> position;
            cin >> number;
            if (!strcmp(BEG, position)) {
                list->addAfter(list->first, number);
            }
            else if (!strcmp(END, position)) {
                list->addAfter(list->last, number);
            }
            else {
                list->addAfter(list->iterators[(int)position[0] - 48], number);
            }
            break;
        case '.':
            cin >> instruction2;
            cin >> position;
            cin >> number;
            if (!strcmp(BEG, position)) {
                list->addBefore(list->first, number);
            }
            else if (!strcmp(END, position)) {
                list->addBefore(list->last, number);
            }
            else {
                list->addBefore(list->iterators[(int)position[0] - 48], number);
            }
            break;
        case 'I':
            cin >> instruction2;
            break;
        case 'i':
            cin >> number;
            cin >> position;
            if (!strcmp(BEG, position)) {
                list->initIterator(list->first,(int)number);
            }
            else if (!strcmp(END, position)) {
                list->initIterator(list->last, (int)number);
            }
            else {
                list->initIterator(list->iterators[(int)position[0] - 48], (int)number);
            }
            break;
        case '+':
            cin >> number;
            list->moveIteratorUp(list->iterators[number], (int)number);
            break;
        case '-':
            cin >> number;
            list->moveIteratorDown(list->iterators[number], (int)number);
            break;
        case 'R':
            cin >> position;
            if (!strcmp(BEG, position)) {
                list->removeElement(list->first);
            }
            else if (!strcmp(END, position)) {
                list->removeElement(list->last);
            }
            else {
                list->removeElement(list->iterators[(int)position[0] - 48]);
            }
            break;
        case 'P':
            cin >> position;
            list->printElement(position);
            break;
        default:
            break;
        }
    }
    list->deleteList();
    delete list;
    return 0;
}