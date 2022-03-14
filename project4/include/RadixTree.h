#ifndef RADIX_TREE_H
#define RADIX_TREE_H
#include <string>

template <typename ValueType>
class RadixTree
{
public:
    RadixTree() { m_head = new Node(); }

    ~RadixTree() { deleteNodes(m_head); }

    void insert(std::string key, const ValueType &value)
    {
        Node *parent = nullptr;
        Node *found = m_head;

        // handle root node
        if (found->children[key[0]] == nullptr)
        {
            Node *inserted = new Node(key, value, true);
            found->children[inserted->key[0]] = inserted;
            return;
        }

        while (1)
        {
            parent = found;
            found = found->children[key[0]];
            // insert the new pair directly below found node if we can
            if (found == nullptr)
            {
                Node *inserted = new Node(key, value, true);
                parent->children[inserted->key[0]] = inserted;
                return;
            }
            // given key is already in tree
            if (key == found->key)
            {
                found->end = true;
                found->value = value;
                return;
            }
            //  found key is at beggining of current key; cut it and continue
            if (key.find(found->key) == 0)
            {
                key = key.substr(found->key.size());
            }
            //  current key is at beginning of found key; cut the found key and insert the new key
            else if (found->key.find(key) == 0)
            {
                Node *inserted = new Node(key, value, true);
                found->key = found->key.substr(key.size());
                inserted->children[found->key[0]] = found;
                parent->children[inserted->key[0]] = inserted;
                return;
            }
            // current key have letters a prefix in common, but both need to be split into new nodes
            else
            {
                int diff = firstDifference(key, found->key);
                std::string prefix = found->key.substr(0, diff);
                Node *shifted = new Node(prefix, false);
                Node *inserted = new Node(key.substr(diff), value, true);
                found->key = found->key.substr(diff);
                // found->end = false;
                shifted->children[found->key[0]] = found;
                shifted->children[inserted->key[0]] = inserted;
                parent->children[shifted->key[0]] = shifted;
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
        // find the index of the first difference between 2 strings
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

    /*
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
    */
};
#endif