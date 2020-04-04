#pragma once

#include <QAbstractListModel>
class Project;

class ProjectModel : public QAbstractListModel
{
    Q_OBJECT
public:
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

    ProjectModel(QObject *obj = nullptr);

    void add(Project *newProject);

    void clearModel();

    int rowCount(const QModelIndex& ) const;

    QVariant data(const QModelIndex& index, int role) const;

    void updateValue(int projectId, QString name, bool active, bool watcher);

    QHash<int, QByteArray> roleNames() const;

private:
    std::vector<Project*> m_list;
};
