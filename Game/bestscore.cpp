#include "bestscore.h"

int bestscore::get_bestscore()
{
    std::ifstream file("bestscore.txt");
    int bs;
    file>>bs;
    file.close();
    return bs;
}

void bestscore::update_bestscore(int score)
{
    int best = get_bestscore();
    std::ofstream file("bestscore.txt");
    file<<std::max(best,score);
    file.close();
}
void bestscore::reset_bestscore(){
    std::ofstream file("bestscore.txt");
    file<<0;
    file.close();
}
