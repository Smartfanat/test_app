#pragma once

#include <QObject>

class ProjectRole : public QObject
{
    Q_OBJECT

public:
    ProjectRole() : QObject() {}

    enum Role{
        Id = Qt::UserRole+1,
        Active,
        Name,
        Logo,
        Position,
        Watcher,
        SpendTimeWeek,
        SpendTimeMonth,
        SpendTimeAll
    };

    Q_ENUMS(Role)
};

