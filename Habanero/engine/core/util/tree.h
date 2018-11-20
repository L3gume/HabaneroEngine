#pragma once
#ifndef TREE_H
#define TREE_H

#include <vector>
#include <memory>
#include <type_traits>

// Only allow trivially destructible types
template<typename T>
struct TTreeNode {
    // Constructors
    TTreeNode(T _data) : m_data(std::move(_data)), m_parent(nullptr) {}
    TTreeNode(T _data, std::shared_ptr<TTreeNode<T>> _parent)
        : m_data(std::move(_data)), m_parent(std::make_shared(_parent)) {}
    // Destructor
    ~TTreeNode() = default;
    
    void addChild(const T& _data) {
        m_children.emplace_back(std::make_shared<TTreeNode<T>>(_data));
    }
    
    std::vector<std::shared_ptr<TTreeNode<T>>> getChildren() { return m_children; }
    
    inline std::shared_ptr<TTreeNode<T>> parent() { return m_parent; }
    inline void setData(const T& _data) { m_data = _data; }
    inline T& getData() { return m_data; }
    
private:
    T m_data;
    std::shared_ptr<TTreeNode<T>> m_parent;
    std::vector<std::shared_ptr<TTreeNode<T>>> m_children;
};

template<typename T>
class TTree {
public:
    TTree(const T& _data) : m_root(TTreeNode<T>(_data)) {}
    ~TTree() = default;
    
    TTreeNode<T>& root() { return m_root; }
private:
    TTreeNode<T> m_root;
};

#endif
