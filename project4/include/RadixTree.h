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
        Node *parent;
        Node *found = findLocation(m_head, &key, &parent);
        if (found->key.empty())
        {
            found->children[key[0]] = new Node(key, value, true);
            return;
        }
        int diff = firstDifference(found->key, key);
        std::string prefix = commonPrefix(found->key, key);

        if (diff > key.size())
        {
            // abcd then abc
            Node *shifted = new Node(found->key.substr(diff - 1), found->value, true);
            found->key = key;
            found->end = true;
            found->value = value;
            found->children[shifted->key[0]] = shifted;
            return;
        }

        // abc, abcd, abef
        if (!prefix.empty() && prefix.size() < found->key.size() && !isChildless(found))
        {
            // parent should now link to the `
            std::string above_prefix = found->key.substr(0, prefix.size()); // ab
            std::string inserted_key = key.substr(prefix.size());           // ef
            std::string trimmed_key = found->key.substr(prefix.size());     // c
            Node *new_parent = new Node(above_prefix, false);
            Node *insertion = new Node(inserted_key, value, true);
            new_parent->children[insertion->key[0]] = insertion;
            new_parent->children[trimmed_key[0]] = found;
            parent->children[new_parent->key[0]] = new_parent;
            found->key = trimmed_key;
            return;

            // std::cout << parent->key <<std::endl;
        }
        if (!prefix.empty() && prefix.size() > 1)
        {
            Node *shifted = new Node(found->key.substr(prefix.size()), found->value, true);
            Node *insertion = new Node(key.substr(prefix.size()), value, true);
            found->key = prefix;
            found->end = false;
            found->children[shifted->key[0]] = shifted;
            found->children[insertion->key[0]] = insertion;
            return;
        }
        if (found->children[key[0]] == nullptr)
        {
            found->children[key[0]] = new Node(key, value, true);
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


    bool isChildless(Node *node)
    {
        for (int i = 0; i < 128; i++)
        {
            if (node->children[i] == nullptr)
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
