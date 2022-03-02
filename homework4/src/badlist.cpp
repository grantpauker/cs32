void removeBad(std::list<Movie *> &l)
{
    auto it = l.begin();
    while (it != l.end())
    {
        if ((*it)->rating() < 50)
        {
            delete *it;
            it = l.erase(it);
        }
        else
        {
            it++;
        }
    }
}