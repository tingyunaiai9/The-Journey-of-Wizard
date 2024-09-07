#ifndef QT_PROGRAMMING_2024_IMETAL_H
#define QT_PROGRAMMING_2024_IMETAL_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QGraphicsPixmapItem>

enum METALSTATE
{
    ENORMAL,
    SHOCKED,
    SHOCKING,
    SHOCKOUT
};

class IMetal;

class IShockState: public QObject
{
public:
    explicit IShockState(IMetal* metalObj);
	virtual ~IShockState();

protected:
    IMetal* m_metalObj;
	QTimer* m_timeout = nullptr;

public:
    virtual QString getName() {return "";}

    virtual bool isShock() {return false;}
    virtual void beHit(QString element) {};
    virtual void beTrans(QString element) {};
    virtual void timeOut() {};
};

class IMetal: public QObject
{
    Q_OBJECT

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

public slots:
    virtual void onTimeOut() {};

public:
    virtual void e_startShocking() {};
    virtual void e_stopShocking() {};
};

class CMetalNormal: public IShockState
{
public:
    explicit CMetalNormal(IMetal* metalObj);

    virtual QString getName() {return "MetalNormal";}

    virtual void beHit(QString element) override;
    virtual void beTrans(QString element) override;
};

class CMetalShocked: public IShockState
{
public:
    explicit CMetalShocked(IMetal* metalObj);

    virtual QString getName() {return "MetalShocked";}

    virtual void timeOut() override;
};

class CMetalShocking: public IShockState
{
public:
    explicit CMetalShocking(IMetal* metalObj);

    virtual QString getName() {return "MetalShocking";}

    virtual bool isShock() override {return true;}
    virtual void timeOut() override;
};

class CMetalShockout: public IShockState
{
public:
    explicit CMetalShockout(IMetal* metalObj);

    virtual QString getName() {return "MetalShockout";}
    virtual void timeOut() override;
};

class CMetal: public IMetal
{
    Q_OBJECT

protected:
    CMetalNormal* m_metalNormal = nullptr;
    CMetalShocked* m_metalShocked = nullptr;
    CMetalShocking* m_metalShocking = nullptr;
    CMetalShockout* m_metalShockout = nullptr;

    QGraphicsPixmapItem* m_shockingPicture = nullptr; // the picture be shocking

public slots:
    void onTimeOut() override;

public:
    void initStateObjs();
    void uninitStateObjs();

public:
    bool isShock();

    void beHit(QString element);
    void beTrans(QString element);

    virtual void e_stopShocking() override;
};

#endif //QT_PROGRAMMING_2024_IMETAL_H
