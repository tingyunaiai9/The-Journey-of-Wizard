#ifndef QT_PROGRAMMING_2024_WEAPON_H
#define QT_PROGRAMMING_2024_WEAPON_H


class Weapon
{
public:
    virtual void equipToParent();
    virtual void unequip();
    [[nodiscard]] bool isEquipped() const;

    virtual void startAttack();
    virtual void stopAttack();
    [[nodiscard]] bool isAttacking() const;

private:
    bool equipped{};

    bool m_isAttacking{};
};


#endif //QT_PROGRAMMING_2024_WEAPON_H
