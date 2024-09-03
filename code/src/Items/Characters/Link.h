#ifndef QT_PROGRAMMING_2024_LINK_H
#define QT_PROGRAMMING_2024_LINK_H


#include "Character.h"

class Link : public Character
{
public:
    explicit Link(QGraphicsItem *parent = nullptr, const QString &pixmapPath = ":/Items/Characters/character_body.png");
};

class CPlayer1 : public Link
{
public:
    explicit CPlayer1(QGraphicsItem *parent = nullptr);

    virtual void h_keyPress(QKeyEvent *event) override;
    virtual void h_keyRelease(QKeyEvent *event) override;
};

class CPlayer2 : public Link
{
public:
    explicit CPlayer2(QGraphicsItem *parent = nullptr);

    virtual void h_keyPress(QKeyEvent *event) override;
    virtual void h_keyRelease(QKeyEvent *event) override;
};

#endif //QT_PROGRAMMING_2024_LINK_H
