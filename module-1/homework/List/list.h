#pragma once
#include <cstddef>
#include <iostream>


namespace task {

struct node {
    node* left;
    node* right;
    int value;

    node(): 
        left(nullptr), 
        right(nullptr) {}
    
    node(int _value): 
        left(nullptr),
        right(nullptr),
        value(_value) {}

    ~node() {}
};


class list {

public:

    list(): 
        begin(nullptr),
        end(nullptr) {}

    list(int count, const int& value = int()) {
        
        node* tmpList[count];
        for(int i = count - 1; i >= 0; i--) {
            tmpList[i] = new node(value);
            if(i < count - 1) {
                tmpList[i]->right = tmpList[i + 1];
            }
            if(i == 0) {
                break;
            }
        }
        for(int i = 1; i < count; i++) {
            tmpList[i]->left = tmpList[i - 1];
        }
        begin = tmpList[0];
        end = tmpList[count - 1];
    }

    list(const list& other) {
        if(&other == this) {
            return;
        }
        if(other.begin == nullptr) {
            begin = nullptr;
            end = nullptr;
            return;
        }
        node* cur = other.begin;
        const std::size_t otherSize = other.size();
        node* tmpList[otherSize];
        int curSize = 0;
        while(cur != nullptr) {
            tmpList[curSize] = new node(cur->value);
            cur = cur->right;
            curSize++;
        }
        for(std::size_t i = 0; i < otherSize; i++) {
            tmpList[i]->right = (i < otherSize - 1) ? tmpList[i + 1] : nullptr;
            tmpList[i]->left = (i > 0) ? tmpList[i - 1] : nullptr;
        }
        
        
        begin = tmpList[0];
        end = tmpList[otherSize - 1];
    }

    ~list() {
        node* current = begin;
        while(current != nullptr) {
            node* next = current->right;
            delete current;
            current = next;
        }
    }

    list& operator=(const list& other) {
        if(&other == this) {
            return *this;
        }
        node* current = begin;
        while(current != nullptr) {
            node* next = current->right;
            delete current;
            current = next;
        }
        begin = nullptr;
        end = nullptr;
        if(other.begin == nullptr) {
            return *this;
        }
        node* cur = other.begin;
        const std::size_t otherSize = other.size();
        node* tmpList[otherSize];
        int curSize = 0;
        while(cur != nullptr) {
            tmpList[curSize] = new node(cur->value);
            cur = cur->right;
            curSize++;
        }
        for(std::size_t i = 0; i < otherSize; i++) {
            tmpList[i]->right = (i < otherSize - 1) ? tmpList[i + 1] : nullptr;
            tmpList[i]->left = (i > 0) ? tmpList[i - 1] : nullptr;
        }
        
        
        begin = tmpList[0];
        end = tmpList[otherSize - 1];
        return *this;
    }


    int& front() {
        return begin->value;
    }

    const int& front() const {
        return begin->value;
    }

    int& back() {
        return end->value;
    }

    const int& back() const {
        return end->value;
    }


    bool empty() const {
        return (begin == nullptr);
    }

    int size() const {
        node* current = begin;
        int size = 0;
        while(current != nullptr) {
            size++;
            current = current->right;
        }
        return size;
    }

    void print() const {
        node* current = begin;
        while(current != nullptr) {
            std::cout << current->value << ' ';
            current = current->right;
        }
        std::cout << '\n';
    }

    void clear() {
        node* current = begin;
        while(current != nullptr) {
            node* next = current->right;
            delete current;
            current = next;
        }
        begin = nullptr;
        end = nullptr;
    }

    void push_back(const int& value) {
        node* tmp = new node(value);
        if(begin == nullptr) {
            begin = tmp;
            end = tmp;
            return;
        }
        tmp->left = end;
        end->right = tmp;
        end = tmp;
    }

    void pop_back() {
        if(end->left != nullptr) {
            end = end->left;
            delete end->right;
            end->right = nullptr;
        }
        else {
            delete begin;
            begin = nullptr;
            end = nullptr; 
        }
    }

    void push_front(const int& value) {
        node* tmp = new node(value);
        if(begin == nullptr) {
            begin = tmp;
            end = tmp;
            return;
        }
        tmp->right = begin;
        begin->left = tmp;
        begin = tmp; 
        
    }

    void pop_front() {
        if(begin->right != nullptr) {
            begin = begin->right;
            delete begin->left;
            begin->left = nullptr;
        }
        else {
            delete begin;
            begin = nullptr;
            end = nullptr;
        }
    }

    void resize(int count) {
        int sz = size();
        while(count < sz) {
            pop_back();
            sz--;
        }
        while(sz < count) {
            push_back(0);
            sz++;
        }
    }

    void swap(list& other) {
        std::swap(begin, other.begin);
        std::swap(end, other.end);
    }

    void remove(const int& value) {
        int tmpValue = value;
        node* cur = begin;
        if(cur == nullptr) {
            begin = nullptr;
            end = nullptr;
            return;
        }
        cur = cur->right;
        while(cur != end && cur != nullptr) {
            node* next = cur->right;
            if(cur->value == tmpValue) {
                cur->left->right = cur->right;
                cur->right->left = cur->left;
                delete cur;
                cur = next;
            }
            else {
                cur = next;
            }
            
        }
        reassign(tmpValue);
    }

    void unique() {
        node* cur = begin;
        while(cur != nullptr) {
            node* next = cur->right;
            if(cur->left != nullptr && cur->left->value == cur->value) {
                cur->left->right = cur->right;
                if(cur->right != nullptr) {
                    cur->right->left = cur->left;
                }
                delete cur;
                cur = next;
            }
            else {
                cur = next;
            }
            
        }
    }

    void sort() {
        int listSize = size();
        mergeSort(begin, end, listSize);
    }

private:

    node* begin = nullptr;
    node* end = nullptr;

    void swap(node*& a, node*& b) {
        std::swap(a->value, b->value);
    }

    void mergeSort(node* left, node* right, int curSize) {
        if(right == left) {
            return;
        }
        if(right == left->right) {
            if(left->value > right->value) {
                swap(left, right);
            }
            return;
        }
        node* curNode = left;
        int cur = 1;
        while(cur <= curSize / 2) {
            curNode = curNode->right;
            cur++;
        }
        
        mergeSort(left, curNode->left, curSize / 2);
        mergeSort(curNode, right, curSize - curSize / 2);
        merge(left, curNode, right, curSize);
    }

    void merge(node* left, node* curNode, node* right, int curSize) {
        node* pointer1 = left;
        node* pointer2 = curNode;
        int newSegment[curSize];
        int i = 0;
        while(pointer1 != curNode && pointer2 != right->right) {
            if(pointer1->value > pointer2->value) {
                newSegment[i] = pointer2->value;
                pointer2 = pointer2->right;
            }
            else {
                newSegment[i] = pointer1->value;
                pointer1 = pointer1->right;
            }
            i++;
        }
        while(pointer1 != curNode) {
            newSegment[i] = pointer1->value;
            pointer1 = pointer1->right;
            i++;
        }
        while(pointer2 != right->right) {
            newSegment[i] = pointer2->value;
            pointer2 = pointer2->right;
            i++;
        }
        int j = 0;
        node* start = left;
        while(start != right->right) {
            start->value = newSegment[j];
            start = start->right;
            j++;
        }
    }

    void reassign(int tmpValue) {
        if(begin != nullptr && begin->value == tmpValue) {
            if(begin->right != nullptr) {
                begin = begin->right;
                delete begin->left;
                begin->left = nullptr;
            }
            else {
                delete begin;
                begin = nullptr;
                end = nullptr;
            }
        }
        if(end != nullptr && end->value == tmpValue) {
            if(end->left != nullptr) {
                end = end->left;
                delete end->right;
                end->right = nullptr;
            }
            else {
                delete begin;
                begin = nullptr;
                end = nullptr;
            }
        }
    }
};

}  // namespace task