// Michael Lucas
// COP2535.DM1
// Demonstrate a linked list data structure which displays its contents
// forwards and in reverse.
//
//                             *i->:-(

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

/**********************************Node.h*************************************/
/**
 * Node is the base class which holds a value, provides getter/setter member
 * functions, and some basic operation.
 *
 * @tparam T the data type of the Node's value.
 */
template <typename T>           // Prefer Java's generic mooch bestest.
class Node {
protected:
    T _value;                            // The node's value
public:
    explicit Node();                     // Default (empty) constructor
    explicit Node(T);                    // Constructs a node with a value

    T& value();                          // Gets the value
    Node<T>& value(T);                   // Sets the value (fluent)

    bool operator == (const Node<T>&);   // Logical comparison operator (n1.value == n2.value)
    bool operator != (const Node<T>&);   // Logical comparison operator !(n1.value == n1.value)
    Node<T>& operator = (T);             // Assignment operator to set the node value directly
    // Sends a Node to ostream.
    friend std::ostream &operator << (std::ostream &os, const Node<T> &node)
    {
        return os << node._value;
    }
};
/*****************************************************************************/

/*******************************LinkedNode.h**********************************/
/**
 * LinkedNode class is a double linked node having a successor (next) and a
 * predecessor (previous) linked node.
 *
 * @tparam T the data type fo the Node's value.
 */
template <typename T>
class LinkedNode : public Node<T> {
private:
    LinkedNode<T> *_next;               // The nodes successor
    LinkedNode<T> *_previous;           // The nodes predecessor

public:
    //constructs
    explicit LinkedNode();                                  // Default (empty) construct; no value, successor or predecessor
    explicit LinkedNode(T, LinkedNode<T>*, LinkedNode<T>*); // Constructs a LinkedNode with a value, successor, & predecessor
    explicit LinkedNode(T);                                 // Constructs a LinkedNode with a value and null successor & predecessor

    // successor
    LinkedNode<T>* next();                                  // Gets the successor (next) node
    LinkedNode<T>* next(LinkedNode<T>*);                    // Sets the successor (next) node & returns the old successor
    bool hasNext();                                         // Indicates that the node points to successor

    // predecessor
    LinkedNode<T>* previous();                              // Gets the predecessor (previous) node
    LinkedNode<T>* previous(LinkedNode<T>*);                // Sets the predecessor (previous) node & return old predecessor
    bool hasPrevious();                                     // Indicates that the node points to a valid predecessor

    //operator
    LinkedNode<T>& operator = (T);                          // Assignment operator to set a node's value directory
};
/*****************************************************************************/

/********************************Iterator.h***********************************/
/**
 * Interator which allows bidireciton iteration of the LinkedList.
 *
 * @tparam T the Iterator's data type
 */
template <typename T>
class Iterator
{
private:
    LinkedNode<T> *_node;
public:
    Iterator(LinkedNode<T> *node);  // Constructs an iterator with its head as `node`

    //operator
    Iterator<T>& operator++();              // Post increment operation; moves forward to next node
    Iterator<T> operator++(int);            // Pre-increment operation; moves forward to next node
    Iterator<T>& operator--();              // Post decrement operation; moves backward to previous node
    Iterator<T> operator--(int);            // Pre-decrement operation; moves backward to previous node
    bool operator != (const Iterator<T>&);  // Logical not equal comparision operator
    bool operator == (const Iterator<T>&);  // Logical eual comparision operator
    T operator * ();                        // Pointer operator
};

/*****************************************************************************/

/*******************************LinkedList.h**********************************/
/**
 * LinkedList class is a series of homogeneous dynamically allocated data.
 *
 * @tparam T the type of data stored in the list.
 */
template <typename T>
class LinkedList
{
private:
    LinkedNode<T> *_head;           // The head (first) node in the list
    LinkedNode<T> *_tail;           // The tail (last) node in the list; terminating node
    std::size_t _size;              // The number of nodes in the list

    LinkedNode<T>* at(std::size_t); // Get a node at a specific location

public:
    explicit LinkedList();                   // Constructs an empty LinkedList
    ~LinkedList();                           // Destructor to delete dynamic memory

    // add/remove; fluent interface
    LinkedList<T>& append(T);               // Appends an elment to the list
    LinkedList<T>& prepend(T);              // Prepends an element to the list
    LinkedList<T>& add(T);                  // Adds a value to the list
    LinkedList<T>& add(std::size_t, T);     // Adds a value at specific location
    LinkedList<T>& replace(std::size_t, T); // Replaces a value at a specific location
    LinkedList<T>& remove(std::size_t);     // Removes the a value at a specific location


    //search member function
    int indexOf(const T&);
    bool contains(const T&);

    // iterator interface
    Iterator<T> begin();
    Iterator<T> rbegin();
    Iterator<T> end();
    Iterator<T> rend();

    // countable
    std::size_t size();                      // Gets the number of nodes in the list

    LinkedNode<T>& operator [](std::size_t); // Array subscript operator
    // Sends the list to std::ostream
    friend std::ostream& operator << (std::ostream &out, LinkedList<T> &list)
    {
        for(Iterator<T> i = list.begin(); i != list.end(); ++i)
            out << *i;
        return out;
    }
};
/*****************************************************************************/

/*******************************LinkedList.h**********************************/
/**
 * Project3 is the actual application with a driver member function.
 */
class Project3
{
private:
    LinkedList<char> _forward;  // List with characters in forward (normal) position
    LinkedList<char> _backward; // List with characters in reverse (backward) position
    std::string _filename;      // The name of the file with the data
    void read();                // member function to read characters into the linked list(s)
public:
    Project3();                 // Default construct opens (./linkedText.txt) in working directory.
    Project3(const std::string &filename); // Constructs a Project3 where data read from filename
    int driver();               // Controller
};

/*****************************************************************************/

/**********************************Node.cpp***********************************/
/**
 * Default empty construct
 */
template <typename T> Node<T>::Node(){};
/**
 * Constructs a Node with a value.
 * @tparam T The value's data type.
 * @param  value the Node's value.
 */
template <typename T> Node<T>::Node(T value) { _value = value; };

/**
 * Getter for the Node's value
 * @returns The nodes value
 */
template <typename T> T& Node<T>::value() { return _value; };
/**
 * Setter for the Nodes's value
 *
 * @tparam  T The value's data type.
 * @param   The value to set
 * @returns Returns the Node whos values was set (fluent)
 */
template <typename T> Node<T>& Node<T>::value(T value)
{
    _value = value;
    return *this;
};

/**
 * Logical == operator to check if two Node objects have the same value.
 *
 * (Node<int>{1} == Node<int>{1}) == true
 *
 * @tparam  T The data type of the Node's value
 * @param   The other Node to check for equality
 * @returns true if the this Node's value and other Node's value are equal;
 *          false otherwise.
 */
template <typename T> bool Node<T>::operator == (const Node<T> &other)
{
    return _value == other._value;
};

/**
 * Logical != operator to check if two Node object do NOT have the
 * same value.
 *
 * (Node<int>{1} != Node<int>{3}) == true
 *
 * @tparam  T The data type of the Node's value
 * @param   The other Node to check for equality
 * @returns true if this Node's value and other Node's value are NOT
 *          equal; false otherwise
 */
template <typename T> bool Node<T>::operator != (const Node<T> &other)
{
    return !(this == other);
}

/**
 * Asignment = operator to allow the Node's value to be directly assigned.
 *
 * This method calls the value setter `Node::value(T)` member function,
 * rather than directly setting the Nodes value.
 *
 * @tparam T The data type fo the Node's value
 * @param  value The new value
 */
template <typename T> Node<T>& Node<T>::operator = (T value)
{

    // Let us call the value() setter.
    // That way any sub-classes can overload the value() member function to
    // inlcude any additional funcitioanllity without having to also overload
    // the operator= member function.

    //_value = value;
    return this->value(value);
}

/*****************************************************************************/

/******************************LinkedNode.cpp*********************************/
/**
 * Defualt (empty) construct, which constructs a LinkedNode with no value or
 * successor (next).
 *
 * @tparam T The LinkedNode's data type.
 */
template <typename T> LinkedNode<T>::LinkedNode() : Node<T>() {
    _next = nullptr;
    _previous = nullptr;
};

/**
 * Constructs a LinkedNode with a value and no successor (next).
 *
 * @tparam T the LinkedNode's data type.
 * @param  The LinkedNode's initial value.
 */
template <typename T> LinkedNode<T>::LinkedNode(T value) : LinkedNode<T>(value, nullptr, nullptr) {};
/**
 * Constructs a LinkedNode with a value and successor (next).
 *
 * @tparam T the LinkedNode's data type.
 * @param  The LinkedNode's initial value.
 * @param  The LinkedNode's successor (next).
 */
template <typename T> LinkedNode<T>::LinkedNode(T value, LinkedNode<T> *previous, LinkedNode<T> *next) : Node<T>(value) {
    _previous = previous;
    _next = next;
}

/**
 * This is an iterator interface to check if the LinkedNode has a sucessor. It would
 * have been more common to name this member function `hasNext()`. Nonetheless, it
 * indicate whether the LinkedNode has a successor (next).
 *
 * @tparam T the LinkedNodes data type.
 * @returns true if the LinkedNode has a successor (next); false otherwise.
 */
template <typename T> bool LinkedNode<T>::hasNext() {
    return _next != nullptr;
};

/**
 * This is the other element to an iterator interface to get the LinkedNode's successor.
 * It would have been more common to name this member funciton `next()`. Nonetheless,
 * it will get the LinkedNode's successor or a nullprt if it doesn't have one.
 *
 * @tparam  T the LinkedNodes data type.
 * @returns A pointer to the LinkedNode's successor (next).
 */
template <typename T> LinkedNode<T>* LinkedNode<T>::next() { return _next; };

/**
 * Sets the LinkedNode's sucessor (next).
 *
 * @tparam  T the LinkedNodes data type
 * @returns The pointer to the LinkedNode's old successor.
 */
template <typename T> LinkedNode<T>* LinkedNode<T>::next(LinkedNode<T> *next)
{
    LinkedNode<T> *old_value = _next;
    _next = next;
    return old_value;
};

/**
 * Gets the LinkedNode's predecessor (previous)
 *
 * @tparam T the LinkedNodes data type.
 * @returns The pointer to the LinkedNode's predecessor.
 */
template <typename T> LinkedNode<T>* LinkedNode<T>::previous() { return _previous; };


/**
 * Sets the LinkedNode's predecessor (previous).
 *
 * @tparam T the LinkedNodes data type
 * @returns The pointer to the LinkedNode's old predecessor
 */
template <typename T> LinkedNode<T>* LinkedNode<T>::previous(LinkedNode<T> *previous)
{
    LinkedNode<T> *old_value = _previous;
    _previous = previous;
    return old_value;
}

/**
 * Indicates whether the LinkedNode has a predecessor.
 *
 * @tparam T the LinkedNode data type
 * @returns true if the LinkedNode contains a predecessor.
 */
template <typename T> bool LinkedNode<T>::hasPrevious() { return _next != nullptr; }

/**
 * Assignment = operator so the LinkedNode's value can be directly assigned.
 *
 * @see Node<T>::operator=(T)
 * @tparam T the LinkedNode's data type
 * @param  The value assinged to this LinkedNode
*/
template <typename T> LinkedNode<T>& LinkedNode<T>::operator= (T value)
{
    Node<T>::operator=(value); // delegate to the Node::operator=
    return *this;
}

/*****************************************************************************/

/*******************************Iterator.cpp**********************************/
/**
 * Constructs an iterator for traversing a LinkedNode.
 */
template <typename T> Iterator<T>::Iterator(LinkedNode<T> *node)
{
    _node = node;
};

/**
 * Advance the iterator to the next node.
 */
template <typename T> Iterator<T>& Iterator<T>::operator ++ ()
{
    _node = _node->next();
    return *this;
};

/**
 * Decrement the iterator to the previous node.
 */
template <typename T> Iterator<T>& Iterator<T>::operator -- ()
{
    _node = _node->previous();
    return *this;
};

/**
 * Increment the iterator to the next node.
 */
template <typename T> Iterator<T> Iterator<T>::operator ++ (int value)
{
    Iterator<T> i = *this;
    ++*this;
    return i;
};

/**
 * Decrement the iterator to the previous node.
 */
template <typename T> Iterator<T> Iterator<T>::operator -- (int value)
{
    Iterator<T> i = *this;
    --*this;
    return i;
};

/**
 * Logical operator to compair to Iterator objects
 */
template <typename T> bool Iterator<T>::operator != (const Iterator<T> &other)
{
    return _node != other._node;
};

/**
 * Logical operator to compair to Iterator objects
 */
template <typename T> bool Iterator<T>::operator == (const Iterator<T> &other)
{
    return !(this == other);
}

/**
 * Pointer operator to get the Iterators current node's value.
 */
template <typename T> T Iterator<T>::operator * ()
{
    return _node->value();
};

/*****************************************************************************/


/******************************LinkedList.cpp*********************************/
/**
 * Default (empty) LinkedList construct.
 *
 * @tparam T the LinkedList's data type.
 */
template <typename T> LinkedList<T>::LinkedList() {
    _head = nullptr;
    _tail = new LinkedNode<T>{};
    _size = 0;
};

/**
 * Deconstructor to free up dynamically allocated memory.
 */
template <typename T> LinkedList<T>::~LinkedList()
{
    LinkedNode<T> *n = _head;
    LinkedNode<T> *m;
    while(nullptr != n){
        m = n->next();
        delete n;
        n = m;
    }
};

/**
 * Removes a node for a specific position.
 */
template <typename T> LinkedList<T>& LinkedList<T>::remove(std::size_t offset)
{
    LinkedNode<T> *node = at(offset);

    LinkedNode<T> *previous = node->previous();
    LinkedNode<T> *next = node->next();

    previous->next(next);
    next->previous(previous);

    delete node;
    --_size;
    return *this;
};

/**
 * Replaces a node at a specific position.
 *
 * Creates a new node, inserts it into the list, and removes the one previously located
 * at that position.
 *
 */
template <typename T> LinkedList<T>& LinkedList<T>::replace(std::size_t offset, T value)
{
    add(offset, value);
    remove(offset + 1);
    return *this;
};

/**
 * Gets a node at a particular location.
 */
template <typename T> LinkedNode<T>* LinkedList<T>::at(std::size_t offset)
{
    if(offset > _size) {
        throw std::out_of_range{"Out of Range: Invalid offset "
                                + std::to_string(offset) + "."};
    }

    LinkedNode<T> *node = _head;
    std::size_t key = 0;
    while(key != offset && node && node->hasNext()) {
        node = node->next();
        ++key;
    }
    return node;
}

/**
 * Appends a node to the end of the list.
 */
template <typename T> LinkedList<T>& LinkedList<T>::append(T value)
{
    LinkedNode<T> *last = _tail->previous();
    LinkedNode<T> *node = new LinkedNode<T>(value, last, _tail);
    _tail->previous(node);
    if(nullptr == last) { //size = 0
        _head = node;
    } else {
        last->next(node); // new node is the old last nodes next
    }
    ++_size;
    return *this;
};

/**
 * Prepends a node to the begining of the list.
 */
template <typename T> LinkedList<T>& LinkedList<T>::prepend(T value)
{
    // its an empty list
    if(_head == nullptr) {
        return append(value);
    }

    // not an empty list
    LinkedNode<T> *node = new LinkedNode<T>(value, nullptr, _head);
    _head = node;
    ++_size;
    return *this;
};

/**
 * Add a node to the list. Alias for LinedList<T>::append(T)
 */
template <typename T> LinkedList<T>& LinkedList<T>::add(T value)
{
    return prepend(value);
};

/**
 * Adds a not to the list at a specific location.
 *
 * The lists size is increased by one.
 *
 */
template <typename T> LinkedList<T>& LinkedList<T>::add(std::size_t offset, T value)
{    
    // prepend
    if(0 == offset) {
        prepend(value);
    }

    //append
    if(_size == offset) {
        append(value);
    }

    // everything in between
    LinkedNode<T> *node = at(offset); // should never get nullptr
    LinkedNode<T> *new_node = new LinkedNode<T>(value, node->previous(), node);
    node->previous()->next(new_node)->previous(new_node);
    ++_size;
    return *this;
};

/**
 * Gets the iterator's begining node.
 */
template <typename T> Iterator<T> LinkedList<T>::begin()
{
    return Iterator<T>{_head};
}

/**
 * Gets the reverse iterator begining node.
 */
template <typename T> Iterator<T> LinkedList<T>::rbegin()
{
    return Iterator<T>(_tail->previous());
}

/**
 * Gets the iterator's ending node.
 */
template <typename T> Iterator<T> LinkedList<T>::end()
{
    return Iterator<T>{_tail};
};

/**
 * Gets the reverse iterator's ending node.
 */
template <typename T> Iterator<T> LinkedList<T>::rend()
{
    return Iterator<T>(nullptr);
}

/**
 * Gets the lists size; (e.g. The number of nodes found in the list)
 */
template <typename T> std::size_t LinkedList<T>::size()
{
    return _size;
}

/**
 * Gets the offset (subscript) of the first occurance of a value.
 *
 * LinkedList<T>::indexOf(const T&) will return -1 if the value
 * is not found.
 */
template <typename T> int LinkedList<T>::indexOf(const T &value)
{
    int key = 0;
    for(const T val : *this) {
        if(value == val)
        {
            return key;
        }
        ++key;
    }
    return -1;
}

/**
 * Indicates whether the list contains a value.
 */
template <typename T> bool LinkedList<T>::contains(const T &value)
{
    return indexOf(value) != -1;
}

/**
 * Array subscript operator to access a list value using [int];
 */
template <typename T> LinkedNode<T>& LinkedList<T>::operator [] (std::size_t offset)
{
    return *at(offset);
};

/*****************************************************************************/

/*******************************Project3.cpp**********************************/

/**
 * Constructs a Project3 object with the data found in ./linedText.txt file.
 */
Project3::Project3() : Project3("./linkedText.txt") {};

/**
 * Constructs a Project3 object with data from argument `filename`.
 * @param filename
 */
Project3::Project3(const std::string &filename)
{
    _forward = LinkedList<char>{};
    _backward = LinkedList<char>{};
    _filename = filename;
};

/**
 * Reads the data from a file into two LinkedLists.
 */
void Project3::read()
{
    char value;
    std::ifstream infile;
    infile.open(_filename);
    if(!infile) {
        throw std::runtime_error("Unable to open file " + _filename + "!");
    }
    while(infile >> value)
    {
        _forward.append(value);     // adds the character `value` to the begining of the list
        _backward.prepend(value);   // adds the character `value` to the end of the list
    }
    infile.close();
};

/**
 * Controller to display applicatoins output to std::cout.
 * @return
 */
int Project3::driver()
{
   try {
        read();
        std::cout << "--- Project 3 ---" << std::endl;
        std::cout << "FORWARD:  " << _forward << std::endl;
        std::cout << "BACKWARD: " << _backward << std::endl;
        std::cout << "Thank you, have a nice day! :-)" << std::endl;
    }  catch (std::runtime_error err) {
        std::cerr << err.what() << std::endl;
        return 404;
    }
    return 0;
};

/*****************************************************************************/

int main()
{
    system("cls");
    Project3 app{};
    return app.driver();
    system("pause");
};


