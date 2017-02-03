#include <iostream>
#include <cstdlib>
#include <ctime>

enum Choice
{
  LEFT,
  MIDDLE,
  RIGHT,
};

inline Choice randomChoice()
{
  return static_cast<Choice>(rand() % 3);
}

inline bool randomBool()
{
  return rand() % 2;
}

class MontyHall
{
  public:

  MontyHall(Choice w = randomChoice()) : winnerDoor(w)
  {
  }

  Choice selectDoor(Choice c) const
  {
    if(winnerDoor == c)
    {
      switch(c)
      {
        case LEFT:
        return randomBool() ? MIDDLE : RIGHT;
      
        case MIDDLE:
        return randomBool() ? LEFT : RIGHT;
      
        case RIGHT:
        return randomBool() ? LEFT : MIDDLE;
      }
    }
    else
    {
      switch(c)
      {
        case LEFT:
        return winnerDoor == RIGHT ? MIDDLE : RIGHT;
      
        case MIDDLE:
        return winnerDoor == RIGHT ? LEFT : RIGHT;
      
        case RIGHT:
        return winnerDoor == MIDDLE ? LEFT : MIDDLE;
      }
    }
  }

  bool openDoor(Choice c) const
  {
    return c == winnerDoor;
  }

  private:

  const Choice winnerDoor;
};

bool playSmart(const MontyHall& mh)
{
  Choice myChoice = randomChoice();
  
  Choice hisChoice = mh.selectDoor(myChoice);

  switch(myChoice)
  {
    case LEFT:
    return mh.openDoor(hisChoice == RIGHT ? MIDDLE : RIGHT);
    
    case MIDDLE:
    return mh.openDoor(hisChoice == RIGHT ? LEFT : RIGHT);
    
    case RIGHT:
    return mh.openDoor(hisChoice == MIDDLE ? LEFT : MIDDLE);
  }
}

bool playStupid(const MontyHall& mh)
{
  Choice myChoice = randomChoice();
  
  return mh.openDoor(myChoice);
}

void serialGamer(std::string title, bool (*play)(const MontyHall&), int numDraws, bool verbose = false)
{
  int numHits = 0;
  int numMisses = 0;

  std::cout << "[" << title << "]" << std::endl;

  for(int i = 1; i <= numDraws; ++i)
  {
    MontyHall mh;

    const bool draw = play(mh);

    if(verbose)
    {
      std::cout << "Draw no " << i << " -> " << (draw ? "win" : "loose") << std::endl;
    }

    draw ? ++numHits : ++numMisses;
  }
  
  const float proba = numHits * 100.f / (numHits + numMisses);
  
  std::cout << "Number of hits   : " << numHits << std::endl;
  std::cout << "Number of misses : " << numMisses << std::endl;
  std::cout << "Probability      : " << proba << '%' << std::endl;
}

int main()
{
  srand(time(NULL));

  const int numDraws = 10000;
  const bool verbose = false;

  serialGamer("STUPID PLAYER", playStupid, numDraws, verbose);

  serialGamer("SMART PLAYER", playSmart, numDraws, verbose);

  return 0;
}

