#ifndef QT_PROGRAMMING_2024_IMETAL_H
#define QT_PROGRAMMING_2024_IMETAL_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>

enum METALSTATE
{
    ENORMAL,
    SHOCKING
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
    virtual QString getName() {return "";};

    virtual void beHit(QString element) {};
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

    virtual QString getName() {return "MetalNormal";};

    virtual void beHit(QString element) override;
};

class CMetalShocking: public IShockState
{
public:
    explicit CMetalShocking(IMetal* metalObj);

    virtual QString getName() {return "MetalShocking";};

    virtual void timeOut() override;
};
#endif //QT_PROGRAMMING_2024_IMETAL_H
