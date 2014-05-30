#include <iostream>
#include <random>
#include <vector>
#include <iomanip>

class cDice {
public:
    cDice(unsigned int sides);
    
    inline unsigned int     roll();
    std::vector<double>     manyRolls(unsigned int);
    
private:
    std::default_random_engine                      mEngine;
    std::uniform_int_distribution<unsigned int>     mDist;
    unsigned int                                    mSides;
};

cDice::cDice(unsigned int sides):
mSides { sides }
{
    std::random_device dev;
    mEngine.seed(dev());
    mDist = std::uniform_int_distribution<unsigned int>(1, mSides);
}

inline unsigned int cDice::roll()
{
    return mDist(mEngine);
}

std::vector<double> cDice::manyRolls(unsigned int count)
{
    std::vector<double> ret(mSides, 0.0);
    
    for ( auto i = 0; i < count; ++i )
    {
        ++ret[roll()-1];
    }
    
    for ( double& i : ret )
    {
        i /= static_cast<double>(count) / 100.0;
    }
    
    return std::move(ret);
}

int main()
{
    cDice d(6);
    
    std::cout.precision(2);
    std::cout.setf(std::ios::fixed, std::ios::floatfield );
 
    std::cout << "# of rolls    1s      2s      3s      4s      5s      6s\n";
    std::cout << "============================================================\n";

    unsigned int count = 1;
    for ( auto i = 1; i < 7; ++i )
    {
        count *= 10;
        std::cout << count << std::setw(13-i) << " ";
        std::vector<double> results { d.manyRolls(count) };
        for ( auto& j : results )
            std::cout << std::setw(5) << j << "%  ";
        std::cout << "\n";
    }
    
    std::cout << "\n";
    
    return 0;
}