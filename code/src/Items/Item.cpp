#include "Item.h"

#include <QDebug>

#include "./Armors/IcebreakerArmor.h"

const QPointF Item::GRAVITY = (QPointF(0, 0.004));

Item::Item(QGraphicsItem *parent, const QString &pixmapPath) :
    QGraphicsItem(parent)
{
    if (pixmapPath != "") {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(pixmapPath), this);
    }
}

Item* CItemFactory::NewItem(QString strItem)
{
    QString item_name;
    item_name = strItem.toUpper();
    qDebug() << item_name;

    // A = Armor, H = Head Equipment, L = Leg Equipment
    // F = Fire, I = Ice, L = Lighting

    if (item_name == "AI")
    {
        return new IcebreakerArmor();
    }
    else if (item_name == "AF")
    {
        /* code */
    }
    else
    {
        return nullptr;
    }

    return nullptr;
}
