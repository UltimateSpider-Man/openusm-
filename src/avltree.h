#pragma once

template<typename T>
struct TreeNode {
    TreeNode<T> *field_0;
    TreeNode<T> *field_4;
    TreeNode<T> *field_8;
    T *m_key;
    char field_10;
};

template<typename T>
struct AvlTree {
    TreeNode<T> *field_0;
    int m_size;
    bool field_8;

    int addHelper(TreeNode<T> *, TreeNode<T> *&, TreeNode<T> *);

    void dump(TreeNode<T> *&a2, int a3);
};
