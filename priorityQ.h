#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#include <unordered_map>
#include <cstdlib>

template <class t1, class t2>
class priorityQ
{
public:
    priorityQ();
    priorityQ(const priorityQ<t1, t2>&);
    const priorityQ<t1, t2>& operator=(const priorityQ<t1, t2>&);
    ~priorityQ();
    void push_back(const t1&, const t2&);
    void pop_front();
    void decrease_priority(const t1&, const t2&);
    t2 get_front_priority() const;
    t1 get_front_key() const;
    bool isEmpty() const;
private:
	struct priorityType
    {
        t1 key;
        t2 priority;
    };

    void bubbleUp(std::size_t);
    void bubbleDown(std::size_t);

    priorityType *  heapArray;
    std::size_t capacity, size;
    std::unordered_map<t1, std::size_t> itemToPQ;
};

#endif
