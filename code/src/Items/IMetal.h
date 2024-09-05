#ifndef QT_PROGRAMMING_2024_IMETAL_H
#define QT_PROGRAMMING_2024_IMETAL_H

#include <QObject>
#include <QMap>
#include <QString>

enum METALSTATE
{
    NORMAL,
    SHOCKING,
    SHOCKOUT
};

class IMetal;

class IShockState: public QObject
{
public:
    explicit IShockState(IMetal* metalObj);

protected:
    IMetal* m_metalObj;

public:
    virtual QString getName() {return "";};

};

class IMetal: public QObject
{
private:
    METALSTATE m_State;
    QMap<METALSTATE, IShockState*> m_StateMap;

protected:
    void initState(METALSTATE stateType);
    void addState(METALSTATE stateType, IShockState* stateObj);

    IShockState* getStateObj();
    void clearStateMap();

public:
    void setState(METALSTATE stateType);
};

#endif //QT_PROGRAMMING_2024_IMETAL_H
