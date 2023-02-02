#ifndef main_hpp
#define main_hpp

#include "ItemType.hpp"
#include "PriorityQueue.cpp"
#include <fstream>
#include <iomanip>
#include <iostream>

#define ARR_BOUND 256
static const std::string FILENAME = "data.txt";

NodeType* newNode(unsigned char ch, unsigned int wt, NodeType* left, NodeType* right)
{
    NodeType* node = new NodeType;
    
    node->ascii = ch;
    node->weight = wt;
    node->zero = left;
    node->one = right;
    
    return node;
}

std::ostream& operator<<(std::ostream& out, const NodeType& node)
{
    return (out << node.ascii << '\t' << node.weight);
}

std::string fetchFilename()
{
    std::string inputLine;
    
    std::cout << "\t1)   " << "Enter NOTHING to use default UTF-8 data file ( \"data.txt\" )" << std::endl;
    std::cout << "\t2)   " << "Provide name of .txt file to read (must be saved in 'HuffTree' directory)" << std::endl;
    std::cout << "\nDATA FILE: "; std::getline(std::cin, inputLine);
    
    std::cout << std::endl << std::endl;
    
    return ( (inputLine.size())
            ? inputLine
            : FILENAME );
}

void wait()
{
    std::cout << "\n*** Program Paused ***\n\tPress ENTER to continue...";
    std::cin.ignore();
    std::cout << "*** Program Resumed ***\n" << std::endl;
}


void loadArr(ItemType* arr, std::string filename)
{
    std::ifstream inFS;
    
    try
    {
        inFS.open(filename, std::fstream::in);

        if ( !inFS.is_open() | inFS.bad() )
        {
            throw std::runtime_error("Failed opening input data file : " + filename);
        }
        else
        {
            for(int i = 0; i < ARR_BOUND; i++) // Initialize array
            {
                arr[ i ].ascii = (char)i;
                arr[ i ].weight = 0;
            }
            
            char ch;
            
            while( inFS.get(ch) )
            {
                arr[(int)ch].weight++;
            }
            
            inFS.clear(); // Reset IO flags
            inFS.close();
            
        }
    }
    catch (const std::runtime_error& excpt)
    {
        std::cout << excpt.what() << std::endl;
    }
    
    inFS.close();
}

void printArr(ItemType* arr)
{
    int chCount = 0;
    
    std::cout << "*** Data Array Contents ***" << std::endl;
    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;
    std::cout << "      INDEX   ASCII   COUNT" << std::endl;
    std::cout << "*---------------------------------------*" << std::endl;
    
    for(int i = 0; i < ARR_BOUND; i++)
    {
        if ( arr[i].weight )
        {
            std::cout << ' ' << '\t' << i << '\t' << arr[i].ascii << '\t' << arr[i].weight << std::endl;
            chCount += arr[i].weight;
        }
    }

    std::cout << "*---------------------------------------*" << std::endl;
    std::cout << "  " << chCount << " total characters processed" << std::endl;

    std::cout << '#' << std::setw(100) << std::setfill('#') << '#' << std::endl;

}

#endif // main_hpp //
