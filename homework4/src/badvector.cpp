void removeBad(std::vector<Movie *> &v)
{
    auto it = v.begin();
    while (it != v.end())
    {
        if ((*it)->rating() < 50)
        {
            delete *it;
            it = v.erase(it);
        }
        else
        {
            it++;
        }
    }
}