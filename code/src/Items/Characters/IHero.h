#ifndef QT_PROGRAMMING_2024_IHERO_H
#define QT_PROGRAMMING_2024_IHERO_H

#include <map>
#include <QString>
using namespace std;

enum HEROSTATE {
    NORMAL,
    FIREING,
    ICEING,
    LIGHTNING
};

class IHero;

class IState
{
public:
    explicit IState(IHero* heroObj);

protected:
    IHero* m_HeroObj;

public:
    virtual QString GetName();
};

class IHero{
private:
    HEROSTATE m_State;
    map<HEROSTATE, IState*> m_StateMap;
protected:
    void InitState(HEROSTATE stateType);
    void AddState(HEROSTATE stateType, IState* stateObj);

    IState* GetStateObj();
    void ClearStateMap();

public:
    void SetState(HEROSTATE stateType);
};


#endif //QT_PROGRAMMING_2024_IHERO_H
