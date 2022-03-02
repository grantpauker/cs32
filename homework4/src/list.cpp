void listAll(std::string path, const Class *c) // two-parameter overload
{
    path += c->name();
    std::cout << path << std::endl;
    std::vector<Class*> subclasses = c->subclasses();
    for(auto sub : subclasses){
        listAll(path+"=>",sub);
    }
}
