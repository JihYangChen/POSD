#ifndef ITERATOR_H
#define ITERATOR_H

#include <queue>
using std::queue;

#include "struct.h"
#include "list.h"
#include "node.h"

template <class T>
class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual T currentItem() const = 0;
    virtual bool isDone() const = 0;
};

template <class T>
class NullIterator :public Iterator<T>{
public:
    NullIterator(T n){}

    void first(){}
    
    void next(){}
    
    T currentItem() const{
        return nullptr;
    }
    
    bool isDone() const{
        return true;
    }
    
};

template <class T>
class StructIterator :public Iterator<T> {
public:
    friend class Struct;
    void first() {
        _index = 0;
    }
    
    T currentItem() const {
        return _s->args(_index);
    }
    
    bool isDone() const {
        return _index >= _s->arity();
    }
    
    void next() {
        _index++;
    }
private:
    StructIterator(T s): _index(0), _s(dynamic_cast<Struct*>(s)) {}
    int _index;
    Struct* _s;
};

template <class T>
class ListIterator :public Iterator<T> {
public:
    ListIterator(T list): _index(0), _list(dynamic_cast<List *>(list)) {}
    
    void first() {
        _index = 0;
    }
    
    T currentItem() const {
        return _list->args(_index);
    }
    
    bool isDone() const {
        return _index >= _list->arity();
    }
    
    void next() {
        _index++;
    }
private:
    int _index;
    List* _list;
};

template <class T>
class DFSIterator :public Iterator<T> {
public:
    DFSIterator(T root): _index(0), _rootNode(root) {}
    
    void first() {
        _dfsResults.clear();
        DFS(_rootNode);
        _index = 1;
    }
    
    T currentItem() const {
        return _dfsResults[_index];
    }
    
    bool isDone() const {
        return _index >= _dfsResults.size() - 1;
    }
    
    void next() {
        _index++;
    }
    
private:
    void DFS(T node) {
        _dfsResults.push_back(node);
        
        Iterator<T> *it = node -> createIterator();
        for (it->first(); !(it->isDone()); it->next())
            DFS(it -> currentItem());
    }
    
    int _index;
    T _rootNode;
    std::vector<T> _dfsResults;
};

template <class T>
class BFSIterator :public Iterator<T> {
public:
    BFSIterator(T root): _index(0), _rootNode(root) {}
    
    void first() {
        _bfsResults.clear();
        BFS();
        _index = 1;
    }
    
    T currentItem() const {
        return _bfsResults[_index];
    }
    
    bool isDone() const {
        return _index >= _bfsResults.size() - 1;
    }
    
    void next() {
        _index++;
    }
    
private:
    void BFS() {
        queue<T> q;
        q.push(_rootNode);
        
        while(!q.empty()) {
            T frontNode = q.front();
            q.pop();
            _bfsResults.push_back(frontNode);
            
            Iterator<T> *it = frontNode -> createIterator();
            for (it->first(); !(it->isDone()); it->next())
                q.push(it -> currentItem());
        }
    }
    
    int _index, tmp = 0;
    T _rootNode;
    std::vector<T> _bfsResults;
};

#endif
