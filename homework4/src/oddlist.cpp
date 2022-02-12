void removeOdd(std::list<int> &li)
{
   for(auto it = li.begin(); it != li.end(); it++){
       if((*it % 2) == 1){
           it = li.erase(it);
       }
   }
}