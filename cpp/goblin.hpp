// A Goblin

#include <string>

class Goblin
{
public:
    enum { Peon, Worker, Builder, Supervisor, Master };
    Goblin(const std::string& = "(none)", int rank = Peon);
    const std::string& Name() const;
    int Rank() const;
private:
    std::string m_name;
    int m_rank;
};

