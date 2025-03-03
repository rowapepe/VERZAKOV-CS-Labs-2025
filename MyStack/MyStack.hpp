#pragma once

namespace MyStack {
template<class INF, class FRIEND>
class ListNode {
 private:
    INF d;
    ListNode* next;
    ListNode(void) { next = nullptr; }
    friend FRIEND;
};

template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node* top;

 public:
    MyStack(void);
    MyStack(const MyStack<INF>& other);
    ~MyStack(void);
    MyStack<INF>& operator=(const MyStack<INF>& other);
    bool empty(void) const;
    bool push(INF n);
    bool pop(void);
    INF top_inf(void) const;
    static void Multipliers(int n, MyStack<INF>& stack, bool reversed);
};
}  // namespace MyStack
