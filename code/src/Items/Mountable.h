//
// Created by gerw on 8/21/24.
//

#ifndef QT_PROGRAMMING_2024_MOUNTABLE_H
#define QT_PROGRAMMING_2024_MOUNTABLE_H


class Mountable {
public:
    virtual void mountToParent();

    virtual void unmount();

    [[nodiscard]] bool isMounted() const;

private:
    bool mounted{};
};


#endif //QT_PROGRAMMING_2024_MOUNTABLE_H
