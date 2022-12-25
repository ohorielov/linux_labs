#pragma once

struct BaseNode {
    char ch;
    int priority;

    BaseNode(char ch, int priority)
    {
        this->ch = ch;
        this->priority = priority;
    }
    BaseNode(BaseNode* node) : BaseNode(node->ch, node->priority) {}
    virtual ~BaseNode() {}
};