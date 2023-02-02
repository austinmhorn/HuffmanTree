#ifndef PriorityQueue_cpp
#define PriorityQueue_cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<unsigned char, std::string> HuffmanCode;

struct NodeType
{
    unsigned char ascii;
    unsigned int weight;
    NodeType *next, *zero, *one;
    NodeType() : ascii{'*'} {}
};

template <typename NodeType>
class PriorityQueue
{
private:
    NodeType *root;
    NodeType **envPtr;
    unsigned int nodeCount;
    void altClear(NodeType *);
    void altPrint(NodeType *, unsigned int);
    
    // Private Huffman Tree Methods //
    void altEncode(NodeType *, std::string, HuffmanCode *);
    void altDecode(NodeType *, std::string, std::basic_string<char>::size_type);
public:
    PriorityQueue();
    ~PriorityQueue();
    void clear();
    bool isThere(NodeType *);
    void push(NodeType *);
    void pop();
    void print();
    unsigned int size();
    
    // Public Huffman Tree Methods //
    void buildHuffTree();
    void printHuffTree(NodeType *, int);
    void encode(unsigned char);
    void decode(std::string);
    
    std::vector<std::string> encodings;
};

template <typename NodeType>
void PriorityQueue<NodeType>::altClear(NodeType *node)
{
    if ( node )
    {
        // Pointer to node's next node (possibly null)
        NodeType *nextNode = node->next;
        
        // Break link to next node
        node->next = nullptr;
        
        // Destroy root node
        delete node;
        
        // Attempt delete of next node
        altClear(nextNode);
    }
}

template <typename NodeType>
void PriorityQueue<NodeType>::altPrint(NodeType *node, unsigned int index)
{
    if ( node )
    {
        std::cout << '\t' << index << '\t' << *node << std::endl;
        altPrint(node->next, index+1);
    }
}

template <typename NodeType>
PriorityQueue<NodeType>::PriorityQueue()
{
    this->root = nullptr;
    this->envPtr = nullptr;
    this->nodeCount = 0;
    clear();
}

template <typename NodeType>
PriorityQueue<NodeType>::~PriorityQueue()
{
    altClear(this->root); // Deletes existing list
}

template <typename NodeType>
void PriorityQueue<NodeType>::clear()
{
    altClear(this->root);
    this->root = nullptr;
    
    this->encodings.clear();
}

template <typename NodeType>
bool PriorityQueue<NodeType>::isThere(NodeType *unit)
{
    this->envPtr = &this->root;
    
    while( *this->envPtr  &&  (*this->envPtr)->weight <= unit->weight )
        this->envPtr = &(*this->envPtr)->next;

    return *this->envPtr && (*this->envPtr)->ascii == unit->ascii;
}

template <typename NodeType>
void PriorityQueue<NodeType>::push(NodeType *unit)
{
    if ( !isThere(unit) )
    {
        try
        {
            NodeType *p = *this->envPtr;
            *this->envPtr = new NodeType;
            (*this->envPtr)->ascii = unit->ascii;
            (*this->envPtr)->weight = unit->weight;
            (*this->envPtr)->zero = unit->zero;
            (*this->envPtr)->one = unit->one;
            (*this->envPtr)->next = p;
            this->nodeCount++;
        }
        catch(const std::bad_alloc& excpt)
        {
            std::cout << "std::bad_alloc::what(): " << excpt.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Unit: <" << unit << "> already exists in PriorityQueue" << std::endl;
    }
}

template <typename NodeType>
void PriorityQueue<NodeType>::pop()
{
    if ( this->nodeCount )
    {
        this->envPtr = &this->root;
        NodeType *p = *this->envPtr;
        this->envPtr = &(*this->envPtr)->next;
        this->root = *this->envPtr;
        p->next = nullptr;
        delete p;
        this->nodeCount--;
    }
    else
    {
        std::cout << "*** This PriorityQueue is empty ***" << std::endl;
    }
}

template <typename NodeType>
void PriorityQueue<NodeType>::print()
{
    std::cout << "*** Priority Queue Linked List Contents ***" << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;
    std::cout << "      INDEX   ASCII   COUNT" << std::endl;
    std::cout << "*---------------------------------------*" << std::endl;
    
    if ( this->root )
        altPrint(this->root, 0);
    else
        std::cout << "*** This PriorityQueue is empty ***" << std::endl;

    std::cout << "*---------------------------------------*" << std::endl;
    std::cout << "  Node Count: " << this->nodeCount << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;
}

template <typename NodeType>
unsigned int PriorityQueue<NodeType>::size()
{
    return this->nodeCount;
}

template <typename NodeType>
void PriorityQueue<NodeType>::buildHuffTree()
{
    while( this->root  &&  this->root->next )
    {
        NodeType *p = new NodeType;
        p->zero = this->root;
        p->one = this->root->next;
        p->weight = p->zero->weight + p->one->weight;
        this->root = this->root->next->next;
        push( p );
    }
    
    
    std::cout << "*** Huffman Tree Contents ***\t ('*' represents an internal node)" << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;
    std::cout << "      ASCII   WEIGHT   LEVEL" << std::endl;
    std::cout << "*---------------------------------------*" << std::endl;
    
    printHuffTree(this->root, 0);
    
    std::cout << "*---------------------------------------*" << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;

}

template <typename NodeType>
void PriorityQueue<NodeType>::printHuffTree(NodeType *p, int level)
{
    if ( p )
    {
        std::cout << '\t' << p->ascii << '\t' << p->weight << '\t' << level << std::endl;
        printHuffTree(p->zero, level+1);
        printHuffTree(p->one, level+1);
    }
}

template <typename NodeType>
void PriorityQueue<NodeType>::altEncode(NodeType* parent, std::string encoding, HuffmanCode *huffCode)
{
    // Node is a nullptr OR leaf node
    if ( !parent  ||  (!parent->zero  &&  !parent->one) )
    {
        return;
    }
    // Found ASCII character at node's left child
    else if( parent->zero->ascii == huffCode->first )
    {
        encoding += "0";
        huffCode->second = encoding;
    }
    // Found ASCII character at node's right child
    else if( parent->one->ascii == huffCode->first )
    {
        encoding += "1";
        huffCode->second = encoding;
    }
    else
    {
        // Recursively search huffman tree for requested ASCII character value
        altEncode(parent->zero, encoding + "0", huffCode);
        altEncode(parent->one, encoding + "1", huffCode);
    }
}

template <typename NodeType>
void PriorityQueue<NodeType>::encode(unsigned char ch)
{
    HuffmanCode enc = std::make_pair(ch, "");
    altEncode(this->root, "", &enc);
    
    std::cout << '\t' << enc.first << '\t' << enc.second << std::endl;
    this->encodings.push_back( enc.second );
}

template <typename NodeType>
void PriorityQueue<NodeType>::altDecode(NodeType *parent, std::string encoding, std::basic_string<char>::size_type index)
{
    if ( index < encoding.size()  &&  encoding[index] == '0' )
    {
        altDecode(parent->zero, encoding, index+1);
    }
    else if ( index < encoding.size()  &&  encoding[index] == '1' )
    {
        altDecode(parent->one, encoding, index+1);
    }
    else
    {
        std::cout << "Decoded( \"" << encoding << "\" )\t->\t\'" << parent->ascii << '\'' << std::endl;
    }
}

template <typename NodeType>
void PriorityQueue<NodeType>::decode(std::string encoding)
{
    altDecode(this->root, encoding, 0);
}

#endif // PriorityQueue_cpp //


