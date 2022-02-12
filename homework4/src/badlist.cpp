void removeBad(std::list<Movie *> &li)
{
   for(auto it = li.begin(); it != li.end(); it++){
       if((*it)->rating() < 50){
           delete *it;
           it = li.erase(it);
       }
   }
}