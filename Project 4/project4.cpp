// Michael Lucas
// COP2535.DM1
// Program uses a single stack to determine whether a string read from an
// input file has balanced parentheses.

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

namespace nsm {

    /**
     * Node is the base class which holds a value, provides getter/setter member
     * functions, and some basic operation.
     *
     * @tparam T the data type of the Node's value.
     */
    template <typename T>
    class Node
    {
    protected:
        T _value; // Nodes value
    public:
        //Constructors
        Node(){}                                    //Default (empty) constructor
        Node(const T &value) { _value = value; }    //Construct a nsm::Node with a value

        // Getter & Setter
        T value() { return _value; }                // Gets the nsm::Node value
        void value(T value) { _value = value; }     // Sets the nsm::Node value

        // Operators
        bool operator==(const Node<T> &other) const // Equal to operator
        {
            return _value == other._value;
        }
        bool operator!=(const Node<T> &other) const // Not equal to operator
        {
            return _value != other._value;
        }
        Node<T>& operator=(const T &value) { _value = value; } // Assignment operator

        // Sends node to ostream
        friend std::ostream& operator<<(std::ostream &os, const Node<T> &node) {
            os << node._value;
            return os;
        }
    };

    template <typename T>
    class LinkedNode : public Node<T>
    {
    private:
        LinkedNode<T> *_next;
        LinkedNode<T> *_previous;
    public:
        LinkedNode() : Node<T>(){}
        LinkedNode(LinkedNode<T> *previous, LinkedNode<T> *next) : Node<T>() {
            _previous = previous;
            _next = next;
        }
        LinkedNode(T value) : LinkedNode<T>(value, nullptr, nullptr) {}
        LinkedNode(T value, LinkedNode<T> *previous, LinkedNode<T> *next) : Node<T>(value) {
            _previous = previous;
            _next = next;
        }

        bool hasNext() { return nullptr != _next; }
        LinkedNode<T>* next() { return _next; }
        LinkedNode<T>* next(LinkedNode<T> *next)
        {
            LinkedNode<T> *old_value = _next;
            _next = next;
            return old_value;
        }

        bool hasPrevious() { return nullptr != _previous; }
        LinkedNode<T>* previous() { return _previous; }
        LinkedNode<T>* previous(LinkedNode<T> *previous)
        {
            LinkedNode<T> *old_value = _previous;
            _previous = previous;
            return old_value;
        }

    };

    /**
     * Double-ended, sequence contatiner with dynmaic size.
     *
     * +-----------+-------+-------+-------+---------+----------+
     * |           |       |       |       |         |          |
     * |   FRONT  <->  N1 <->  N2 <->  N3 <-> ...N* <->   BACK  |
     * |           |       |       |       |         |          |
     * +-----------+-------+-------+-------+---------+----------+
     */
    template <typename T>
    class Deque
    {
    private:
        LinkedNode<T> *_front;
        LinkedNode<T> *_back;
        unsigned int _size = 0;
    public:
        Deque() {
            _front = new LinkedNode<T>{};
            _back = new LinkedNode<T>{_front, nullptr};
            _front->next(_back);
        }
        Deque(unsigned int size, const T &value) : Deque<T>() {
            for(unsigned int i = 0; i < size; ++i)
            {
                push_back(value);
            }
        }
        ~Deque()
        {
            LinkedNode<T> *n = _front;
            LinkedNode<T> *m;
            while(nullptr != n){
                m = n->next();
                delete n;
                n = m;
            }
        }

        class Iterator
        {
        private:
            LinkedNode<T> *_node;
        public:
            Iterator(LinkedNode<T> *node) { _node = node; }
            Iterator& operator--()
            {
                _node = _node->previous();
                return *this;
            }
            Iterator operator--(int)
            {
                Iterator i = *this;
                _node = _node->previous();
                return i;
            }
            Iterator& operator++()
            {
                _node = _node->next();
                return *this;
            }
            Iterator operator++(int offset)
            {
                Iterator i = *this;
                _node = _node->next();
                return i;
            }
            bool operator==(const Iterator &other) { return _node == other._node; }
            bool operator!=(const Iterator &other) { return _node != other._node; }
            T operator*() { return _node->value(); }
        };

        //iterator
        Iterator begin() { return nsm::Deque<T>::Iterator( _front->next() ); }
        Iterator end() { return nsm::Deque<T>::Iterator( _back ); }

        Iterator rbegin() { return nsm::Deque<T>::Iterator( _back->previous() ); }
        Iterator rend() { return nsm::Deque<T>::Iterator ( _front ); }

        //capacity
        unsigned int size() { return _size; }
        bool empty() { return _size == 0; }

        //element access
        T front() { return _front->next()->value(); }   // Gets the front value
        T back() { return _back->previous()->value(); } // Gets the back value

        //modifiers
        void push_back(const T& value)              // push a value to back of the deque
        {
            LinkedNode<T> *node = new LinkedNode<T>(value, _back->previous(), _back);
            _back->previous(node)->next(node);
            ++_size;
        }
        void push_front(const T& value)             // push a value to the front of the deque
        {
            LinkedNode<T> *node = new LinkedNode<T>{value, _front, _front->next()};
            _front->next(node)->previous(node);
            ++_size;
        }

        void pop_back()                             // pop an item off the back
        {
            LinkedNode<T> *node = _back->previous();
            node->previous()->next(_back);
            _back->previous(node->previous());
            delete node;
            --_size;
        }

        void pop_front()                            // pop an item off the front
        {
            LinkedNode<T> *node = _front->next();
            _front->next(node->next());
            node->next()->previous(_front);
            delete node;
            --_size;
        }

        void clear()                                // clear the deque
        {
            while(!empty()) {
                pop_back();
            }
        }
    };

    /**
     * Stack  wraps the Deque container to provide only LIFO (last-in, first-out)
     * operation.
     */
    template <typename T>
    class Stack
    {
    private:
        Deque<T> *_deque;
    public:
        explicit Stack() {
            _deque = new Deque<T>{};
        }
        explicit Stack(const Deque<T> *deque) { _deque = deque; }
        ~Stack() {
            delete _deque;
        }
        unsigned int size() { return _deque->size(); }
        bool empty() { return _deque->empty(); }
        T top() { return _deque->back(); }
        void push(const T &value) { _deque->push_back(value); }
        void pop() { _deque->pop_back(); }
    };

    /**
     * Determines if a files content constains a balanced number of parentheses.
     */
    class Project4
    {
    private:
        Stack<char> _stack{};
        std::string _filename;
        /**
         * Read's a file and pushes its content to the a stack.
         */
        void read()
        {
            std::ifstream filein;
            filein.open(_filename);
            if(!filein) {
                throw std::runtime_error("Unable to open " + _filename + "!");
            }
            char data;
            while(filein >> data) {
                _stack.push(data);
            }
            filein.close();
        }
        /**
         *
         * @return 0 the file's content contained zero or balance number of parentheses
         *        >0 the file's content contained x number more open parentheses
         *        <0 the file's content contained |x| number more closed parentheses
         */
        int balance()
        {
            int open_parentheses = 0;
            int closed_parentheses = 0;
            while(!_stack.empty()) {
                char c = _stack.top();
                _stack.pop();
                if(c == '(') {
                    ++open_parentheses;
                } else if( c == ')') {
                    ++closed_parentheses;
                }
            }
            return open_parentheses - closed_parentheses;
        }

    public:
        Project4() : Project4("./inputString.txt") {}
        Project4(const std::string &filename)
        {
            _filename = filename;
        }

        friend std::ostream& operator<<(std::ostream &os, Project4 &obj)
        {
            obj.read();
            std::string msg = "The string found in file " + obj._filename+ " has ";
            int balance = obj.balance();
            if(balance == 0) {
                os << msg + "a zero or a balanced number of parentheses!";
                return os;
            }
            msg += std::to_string(std::abs(balance)) + " ";
            if(balance < 0) {
                os << msg + "more closed `)` than open `(` parentheses!";
            } else {
                os << msg + "more open `(` than closed `)` parentheses!";
            }
            return os;
        }

        void driver() {
            std::cout << *this << std::endl;
        }
    };
}

int main()
{
    try {
        nsm::Project4 project4{};
        project4.driver();
    } catch(std::runtime_error ex) {
        std::cout << ex.what();
    }

    return 0;
}
