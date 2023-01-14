#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <queue>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <functional>

struct Node
{
    Node(char ch, std::uint64_t value)
    : _ch (ch)
    , _value ( value )
    {}

    char _ch;
    std::uint64_t _value{};
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

void checkParams(const int argc)
{
    if (argc < 2)
    {
        throw(std::runtime_error{"Please pass path param to file to encode"});
    }
}

std::vector<char> readFromFile(const std::string& fileName)
{
    std::ifstream inputFile { fileName };

    if (!inputFile.is_open())
    {
        std::stringstream error;
        error << fileName << " file wasn't opened\n";
        throw std::runtime_error{ error.str() };
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string bufferStr { buffer.str() };

    return std::vector<char>{ bufferStr.begin(), bufferStr.end() };
}

std::uint64_t countCharInBuffer(const std::vector<char>& buffer, char ch)
{
    return std::count(buffer.begin(), buffer.end(), ch);
}

std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, std::function<bool(std::shared_ptr<Node>&, std::shared_ptr<Node>&)>>  encodeAscii(std::vector<char> buffer)
{
    auto compare { []( std::shared_ptr<Node>& first, std::shared_ptr<Node>& second){ return first->_value > second->_value; } };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, std::function<bool(std::shared_ptr<Node>&, std::shared_ptr<Node>&)>> priorityQueue(compare);

    while (!buffer.empty())
    {
        char ch { buffer[0] };
        priorityQueue.emplace(std::make_shared<Node>( Node { ch, countCharInBuffer(buffer, ch) } ));
        buffer.erase(std::remove(buffer.begin(), buffer.end(), ch), buffer.end());
    }

    return priorityQueue;
}

std::uint64_t evaluateNode(std::shared_ptr<Node>& node)
{
    if (node == nullptr)
    {
        return 0;
    }

    std::uint64_t result{};

    if (node->left != nullptr)
    {
        result += node->left->_value;

        if (node->left->_ch != 0)
        {
            result += evaluateNode(node->left);
        }
    }
    if (node->right != nullptr)
    {
        result += node->right->_value;

        if (node->right->_ch != 0)
        {
            result += evaluateNode(node->right);
        }
    }

    return result;
}

std::shared_ptr<Node> createBtree( std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, std::function<bool(std::shared_ptr<Node>&, std::shared_ptr<Node>&)>> priorityQueue )
{
    while (!priorityQueue.size() != 1)
    {
        std::shared_ptr<Node> currNode { priorityQueue.top() };
        priorityQueue.pop();

        if (currNode->left == nullptr && currNode->_ch != 0)
        {
            currNode->left = std::make_shared<Node>(*currNode);
            currNode->_ch = 0;
            currNode->_value = evaluateNode(currNode);
        }

        if (currNode->right == nullptr && !priorityQueue.empty())
        {
            currNode->right = priorityQueue.top();
            priorityQueue.pop();
        }

        if (currNode->left && currNode->right && currNode->_ch != 0)
        {
            std::shared_ptr<Node> newNode;
            newNode->left = currNode;
            newNode->_value = evaluateNode(newNode);
            priorityQueue.emplace(currNode);
            continue;
        }

        priorityQueue.emplace(currNode);
    }

    return priorityQueue.top();
}

int main(int argc, char** argv)
{
    try
    {
        checkParams(argc);
        createBtree( encodeAscii(readFromFile(argv[1])) );
    }
    catch (const std::exception &exception)
    {
        std::cout << "Program finished with an error: " << exception.what() << std::endl;
    }
}
