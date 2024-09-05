#ifndef QT_PROGRAMMING_2024_IWOOD_H
#define QT_PROGRAMMING_2024_IWOOD_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>

class Map;

enum WOODSTATE
{
    FNORMAL,
    BURNED,
    BURNING
};

class IWood;

class IBurnState: public QObject
{
public:
    explicit IBurnState(IWood* woodObj);
    virtual ~IBurnState();

protected:
    IWood* m_woodObj = nullptr;
    QTimer* m_timeout = nullptr;

public:
    virtual QString getName() {return "";};

    virtual void beHit(QString element) {};
    virtual void timeOut() {};
};

class IWood: public QObject
{
    Q_OBJECT

private:
    WOODSTATE m_State;
    QMap<WOODSTATE, IBurnState*> m_StateMap;

protected:
    void initState(WOODSTATE stateType);
    void addState(WOODSTATE stateType, IBurnState* stateObj);

    IBurnState* getStateObj();
    void clearStateMap();

public:
    void setState(WOODSTATE stateType);

public slots:
    virtual void onTimeOut() {};

public:
    virtual void e_startBurning() {};
    virtual void e_stopBurning() {};

signals:
    void burnOut(Map* map);
};

class CWoodNormal: public IBurnState
{
public:
    explicit CWoodNormal(IWood* woodObj);

    virtual QString getName() {return "WoodNormal";};

    virtual void beHit(QString element) override;
};

class CWoodBurned: public IBurnState
{
public:
    explicit CWoodBurned(IWood* woodObj);

    virtual QString getName() {return "WoodBurned";};
};

class CWoodBurning: public IBurnState
{
public:
    explicit CWoodBurning(IWood* woodObj);

    virtual QString getName() {return "WoodBurning";};

    virtual void timeOut() override;
};

#endif //QT_PROGRAMMING_2024_IWOOD_H
