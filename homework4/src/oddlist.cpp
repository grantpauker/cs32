void removeOdd(std::list<int> &l)
{
    auto it = l.begin();
    while (it != l.end())
    {
        if ((*it % 2) != 0)
        {
            it = l.erase(it);
        }
        else
        {
            it++;
        }
    }
}