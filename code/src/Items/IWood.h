#ifndef QT_PROGRAMMING_2024_IWOOD_H
#define QT_PROGRAMMING_2024_IWOOD_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QGraphicsPixmapItem>

class Map;

enum WOODSTATE
{
    FNORMAL,
    BURNED,
    BURNING,
    BURNOUT
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
    virtual QString getName() {return "";}

    virtual bool isBurn() {return false;}
    virtual bool isOut() {return false;}
    virtual void beHit(QString element) {};
    virtual void beTrans(QString element) {};
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

    virtual QString getName() override {return "WoodNormal";}

    virtual void beHit(QString element) override;
    virtual void beTrans(QString element) override;
};

class CWoodBurned: public IBurnState
{
public:
    explicit CWoodBurned(IWood* woodObj);

    virtual QString getName() override {return "WoodBurned";}

    virtual void timeOut() override;
};

class CWoodBurning: public IBurnState
{
public:
    explicit CWoodBurning(IWood* woodObj);

    virtual QString getName() override {return "WoodBurning";}

    virtual bool isBurn() override {return true;}
    virtual void timeOut() override;
};

class CWoodBurnout: public IBurnState
{
public:
    explicit CWoodBurnout(IWood* woodObj);

    virtual QString getName() override {return "WoodBurnout";}

    virtual bool isOut() override {return true;}
};

class CWood: public IWood
{
    Q_OBJECT

protected:
    CWoodNormal* m_woodNormal = nullptr;
    CWoodBurned* m_woodBurned = nullptr;
    CWoodBurning* m_woodBurning = nullptr;
    CWoodBurnout* m_woodBurnout = nullptr;

    QGraphicsPixmapItem* m_burningPicture = nullptr; // the picture be burning

public slots:
    void onTimeOut() override;

public:
    void initStateObjs();
    void uninitStateObjs();

public:
    bool isBurn();
    bool isOut();

    void beHit(QString element);
    void beTrans(QString element);

    virtual void e_stopBurning() override;
};

#endif //QT_PROGRAMMING_2024_IWOOD_H
