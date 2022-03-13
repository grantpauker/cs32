#ifndef RADIX_TREE_H2
#define RADIX_TREE_H2
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>

template <typename ValueType>
class RadixTree
{
public:
    RadixTree() { m_head = new Node(); }

    ~RadixTree() { deleteNodes(m_head); }

    std::string commonPrefix(std::string a, std::string b)
    {
        int diff = firstDifference(a, b);
        return a.substr(0, diff);
    }

    void insert(std::string key, const ValueType &value)
    {
        std::string original_key = key;
        Node *parent = nullptr;
        Node *found = findLocation(m_head, &key, &parent);

        // root node (1)
        if (found->key.empty())
        {
            found->children[key[0]] = new Node(key, value, true);
            return;
        }
        // replace current node (4)
        if (found->key == key || key == "")
        {
            found->value = value;
            found->end = true;
            return;
        }
        int diff = firstDifference(found->key, key);

        // insert single node below current (5)
        if (found->children[key[0]] == nullptr && (diff == 0 || diff > found->key.size())) // TODO why diff > statement
        {
            found->children[key[0]] = new Node(key, value, true);
            return;
        }
        if (isChildless(found))
        {
            // shift current node down and insert one node (6)
            if (diff > key.size())
            { 
                Node *shifted = new Node(found->key.substr(diff - 1), found->value, true);
                found->key = key;
                found->value = value;
                found->end = true;
                found->children[shifted->key[0]] = shifted;
                return;
            }
            // shift current node down and insert two nodes (2)
            else
            {
                std::string prefix = found->key.substr(0, diff);
                Node *shifted = new Node(found->key.substr(diff), found->value, true);
                Node *inserted = new Node(key.substr(diff), value, true);
                found->key = prefix;
                found->end = false;
                found->children[shifted->key[0]] = shifted;
                found->children[inserted->key[0]] = inserted;
                return;
            }
        }
        else
        {
            // shift current node up and insert one node (7)
            if (diff > key.size())
            { // TODO check if should be <=
                Node *inserted = new Node(key, value, true);
                found->key = found->key.substr(diff - 1);
                found->end = false; // TODO is this needed?
                inserted->children[found->key[0]] = found;
                parent->children[inserted->key[0]] = inserted;
            }
            // shift current node up and insert two nodes (4)
            else
            {
                std::string prefix = found->key.substr(0, diff);
                Node *shifted = new Node(prefix, false);
                Node *inserted = new Node(key.substr(diff), value, true);
                found->key = found->key.substr(diff);
                found->end = false;
                shifted->children[found->key[0]] = found;
                shifted->children[inserted->key[0]] = inserted;
                parent->children[shifted->key[0]] = shifted;
                return;
            }
        }
    }

    ValueType *search(std::string key) const
    {
        Node *found = search(m_head, key);
        if (found == nullptr)
        {
            return nullptr;
        }
        return &(found->value);
    }
    void print()
    {
        print(m_head, "");
    }

private:
    struct Node
    {
        Node() : children()
        {
            end = false;
        }
        Node(std::string key, bool end) : children(), key(key), end(end) {}
        Node(std::string key, ValueType value, bool end) : children(), key(key), value(value), end(end) {}

        std::string key;
        ValueType value;
        bool end;
        Node *children[128];
    };
    Node *m_head;

    void print(Node *cur, std::string prefix)
    {
        if (cur == nullptr)
        {
            return;
        }
        if (cur == m_head)
        {
            std::cout << "ROOT" << std::endl;
        }
        else
        {

            std::cout << prefix << cur->key << (cur->end ? "#" : "") << std::endl;
        }
        for (auto c : cur->children)
        {
            print(c, prefix + ".");
        }
    }

    bool isChildless(Node *node)
    {
        for (int i = 0; i < 128; i++)
        {
            if (node->children[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }

    void deleteNodes(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        for (int i = 0; i < 128; i++)
        {
            if (node->children[i] == nullptr)
            {
                return;
            }
            deleteNodes(node->children[i]);
            delete node->children[i];
        }
    }

    int firstDifference(std::string a, std::string b) const
    {
        int i = 0;
        for (; i < std::min(a.size(), b.size()); i++)
        {
            if (a[i] != b[i])
            {
                i--;
                break;
            }
        }
        return i + 1;
    }

    Node *findLocation(Node *cur, std::string *key, Node **parent) const
    {
        char c = (*key)[0];
        if (cur->children[c] == nullptr)
        {
            return cur;
        }
        *parent = cur;
        cur = cur->children[c];

        if (*key == cur->key && cur->end)
        {
            return cur;
        }
        if (firstDifference(*key, cur->key) < std::min(key->size(), cur->key.size()))
        {
            return cur;
        }
        if (key->rfind(cur->key, 0) == 0)
        {
            *key = key->substr(cur->key.size());
            return findLocation(cur, key, parent);
        }
        return cur;
    }

    Node *search(Node *cur, std::string key) const
    {
        char c = key[0];
        if (cur->children[c] == nullptr)
        {
            return nullptr;
        }
        cur = cur->children[c];

        if (key == cur->key && cur->end)
        {
            return cur;
        }
        if (key.find(cur->key, 0) == 0)
        {
            return search(cur, key.substr(cur->key.size()));
        }
        return nullptr;
    }
};
#endif
