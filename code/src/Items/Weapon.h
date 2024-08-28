#ifndef QT_PROGRAMMING_2024_WEAPON_H
#define QT_PROGRAMMING_2024_WEAPON_H


class Weapon
{
public:
    virtual void equipToParent();

    virtual void unequip();

    [[nodiscard]] bool isEquipped() const;

private:
    bool equipped{};
};


#endif //QT_PROGRAMMING_2024_WEAPON_H
