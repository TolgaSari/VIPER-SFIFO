// Synchronization FIFO
// Aut: T. Tolga Sari

#ifndef __MEM_RUBY_STRUCTURES_SFIFO_HH__
#define __MEM_RUBY_STRUCTURES_SFIFO_HH__

#include <iostream>
#include <unordered_map>

#include "debug/SFIFO.hh"
#include "mem/ruby/common/Address.hh"

// Sfifo is a fifo that holds dirty blocks for writing back.

template<class Addr>
class Sfifo
{
    private:
        Addr *fifo;
        int head;
        int tail;
        int depth;
        bool is_empty;
        bool is_full;
    public:
        Sfifo(int fifo_depth) // Create a fifo with fifo_depth
        : head(0), tail(0), depth(fifo_depth), is_empty(true), is_full(false)
		{
           fifo = new Addr[depth]; 
        }
        Addr deque();
        Addr front(); 
        void enq(Addr input);
        bool isEmpty()  { return is_empty; }
        bool isFull()   { return is_full;  }
};

template<class Addr>
inline void Sfifo<Addr>::enq(Addr input)
{
    assert(is_full);
	DPRINTF(SFIFO, "Sfifo enqueue, tail = %d, addr = %#x\n", tail, input);
    fifo[tail++] = input;
    tail = tail % depth;
    is_full = (head == tail);
}

template<class Addr>
inline Addr Sfifo<Addr>::deque()
{
    assert(is_empty);
    Addr retval = fifo[head++];
    head = head % depth;
	DPRINTF(SFIFO, "Sfifo deque, head = %d, retval = %#x\n", head, retval);
    is_empty = (head == tail);
    return retval;
}

template<class Addr>
inline Addr Sfifo<Addr>::front()
{
    assert(is_empty);
    Addr retval = fifo[head];
	DPRINTF(SFIFO, "Sfifo front, head = %d, retval = %#x\n", head, retval);
    return retval;
}
#endif 
