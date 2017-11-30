#ifndef ITERATOR_H
#define ITERATOR_H

#include <queue>
using std::queue;

#include "struct.h"
#include "list.h"
#include "node.h"

class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual Term* currentItem() const = 0;
    virtual bool isDone() const = 0;
};

class DFSIterator :public Iterator {
public:
    DFSIterator(Node *et): _expressionTree(et) {}
    
    void first() {
        _index = 0;
        dfs(_expressionTree);
    }
    
    void next() {
        _dfsOrder[++_index];
    }
    
    Term * currentItem() const {
        if(_dfsOrder[_index] -> term)
            return _dfsOrder[_index] -> term;
        else {
            static string table[] = { "", ";", ",", "=" };
            return new Atom(table[_dfsOrder[_index] -> payload]);
        }
    }
    
    bool isDone() const {
        if (_index == (_dfsOrder.size() - 1))
            return true;
        else
            return false;
    }
    
private:
    void dfs(Node *treePtr) {
        if(treePtr) {
            _dfsOrder.push_back(treePtr);
            dfs(treePtr -> left);
            dfs(treePtr -> right);
        }
    }
    
    int _index;
    Node *_expressionTree;
    vector<Node *> _dfsOrder;
    
};

class BFSIterator :public Iterator {
public:
    BFSIterator(Node *et): _expressionTree(et) {}
    void first() {
        _index = 0;
        bfs(_expressionTree);
    }
    void next() {
        _bfsOrder[++_index];
    }
    Term * currentItem() const {
        if(_bfsOrder[_index] -> term)
            return _bfsOrder[_index] -> term;
        else {
            static string table[] = { "", ";", ",", "=" };
            return new Atom(table[_bfsOrder[_index] -> payload]);
        }
    }
    bool isDone() const {
        if (_index == (_bfsOrder.size() - 1))
            return true;
        else
            return false;
    }
    
private:
    void bfs(Node *treePtr) {
        queue<Node *> nodeQueue;
        
        if (!treePtr)
            return;
        nodeQueue.push(treePtr);
        
        while(nodeQueue.size()) {
            Node *frontNode = nodeQueue.front();
            nodeQueue.pop();
            if (frontNode){
                _bfsOrder.push_back(frontNode);
                if (frontNode -> left)
                    nodeQueue.push(frontNode -> left);
                if (frontNode -> right)
                    nodeQueue.push(frontNode -> right);
            }
        }
    }
    
    int _index;
    Node *_expressionTree;
    vector<Node *> _bfsOrder;
};

class NullIterator :public Iterator{
public:
    NullIterator(Term *n){}
    void first(){}
    void next(){}
    Term * currentItem() const {
        return nullptr;
    }
    bool isDone() const {
        return true;
    }
    
};

class StructIterator : public Iterator {
public:
    StructIterator(Struct *s): _index(0), _s(s) {}
    
    void first() {
        _index = 0;
    }
    
    Term* currentItem() const {
        return _s->args(_index);
    }

    bool isDone() const {
        return _index >= _s->arity();
    }
    
    void next() {
        _index++;
    }
private:
    int _index;
    Struct* _s;
};

class ListIterator :public Iterator {
public:
    ListIterator(List *list): _index(0), _list(list) {}
    
    void first() {
        _index = 0;
    }
    
    Term* currentItem() const {
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

#endif
