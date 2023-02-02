#include "main.hpp"

int main(void)
{
    std::cout << "\n*** START ROUTINE ***" << std::endl;
    
    ItemType* dataArr = new ItemType[ ARR_BOUND ];
    PriorityQueue<NodeType> pq;
    
    std::string filename = fetchFilename();
    
    std::cout << "\n*** Phase One: Load Data Array ***\n" << std::endl;
    wait();
    loadArr(dataArr, filename);
    printArr(dataArr);
    
    std::cout << "\n*** Phase Two: Populate Priority Queue Linked List ***\n" << std::endl;
    wait();
    
    // Insert nodes into Priority Queue
    for (unsigned int i = 0; i < ARR_BOUND; i++)
        if ( dataArr[i].weight )
            pq.push(newNode(dataArr[ i ].ascii, dataArr[ i ].weight, nullptr, nullptr));
    
    // Print Priority Queue Contents
    pq.print();
    
    std::cout << "\n*** Phase Three: Build Huffman Tree ***\n" << std::endl;
    wait();

    // Build Huffman Tree
    pq.buildHuffTree();
    
    std::cout << "\n*** Phase Four: Encode ASCII Values ***\n" << std::endl;
    wait();
    
    std::cout << "*** ASCII Huffman Encodings ***" << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;
    std::cout << "      ASCII | ENCODING" << std::endl;
    std::cout << "*---------------------------------------*" << std::endl;

    // Encode ASCII values
    for (unsigned int i = 0; i < ARR_BOUND; i++)
        if ( dataArr[i].weight )
            pq.encode(dataArr[ i ].ascii);
    
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;
    
    std::cout << "\n*** Phase Five: Decode ASCII Huffman Encodings ***\n" << std::endl;
    wait();
    
    std::cout << "*** Decoded Strings ***" << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;
    std::cout << "*---------------------------------------*" << std::endl;
    
    // Decode ASCII values
    for ( auto str : pq.encodings )
        pq.decode( str );

    std::cout << "*---------------------------------------*" << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;

    delete [] dataArr;
    
    std::cout << "\n*** END ROUTINE ***" << std::endl;

    return 0;
}
