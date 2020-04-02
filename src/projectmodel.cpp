#include "headers/projectmodel.h"
#include "headers/projectroleenum.h"

namespace  {
static QString convertSecondsToHHMMSSFormat(int duration)
{
    return QString("%1:%2:%3").arg(duration/3600, 2, 10, QChar('0')).arg((duration/60)%60, 2, 10, QChar('0')).arg((duration/3600)%60, 2, 10, QChar('0'));
}
}

ProjectModel::ProjectModel(QObject *obj)
    : QAbstractListModel(obj)
{

//    Project *newProject1 = new Project;
//    newProject1->setId(10);
//    newProject1->setName("Project1");
//    newProject1->setPosition(1);
//    newProject1->setActive(true);
//    newProject1->setStarred(true);
//    m_list.push_back(newProject1);
//    Project *newProject2 = new Project;
//    newProject2->setPosition(2);
//    newProject2->setId(11);
//    newProject2->setName("Project2");
//    m_list.push_back(newProject2);
//    newProject2->setActive(true);
//    newProject2->setLogoUrl("https://data.whicdn.com/images/334374622/original.jpg");
//    Project *newProject3 = new Project;
//    newProject3->setPosition(3);
//    newProject3->setId(12);
//    newProject3->setName("Project3");
//    m_list.push_back(newProject3);
}

void ProjectModel::add(Project *newProject)
{
    beginInsertRows(QModelIndex(), static_cast<int>(m_list.size()), static_cast<int>(m_list.size()));
    m_list.push_back(newProject);
    endInsertRows();
}

void ProjectModel::clearModel()
{
    beginRemoveRows(QModelIndex(), 0, static_cast<int>(m_list.size()));
    m_list.clear();
    endRemoveRows();
}

int ProjectModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(m_list.size());
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch(role)
    {
    case ProjectRole::Role::Id: return QVariant(m_list[static_cast<size_t>(index.row())]->id());
    case ProjectRole::Role::Name: return QVariant(m_list[static_cast<size_t>(index.row())]->name());
    case ProjectRole::Role::Active: return QVariant(m_list[static_cast<size_t>(index.row())]->active());
    case ProjectRole::Role::Logo: return QVariant(m_list[static_cast<size_t>(index.row())]->logoUrl());
    case ProjectRole::Role::Position: return QVariant(m_list[static_cast<size_t>(index.row())]->position());
    case ProjectRole::Role::Watcher: return QVariant(m_list[static_cast<size_t>(index.row())]->watcher());
    case ProjectRole::Role::SpendTimeWeek: return QVariant(convertSecondsToHHMMSSFormat(m_list[static_cast<size_t>(index.row())]->spendTimeWeek()));
    case ProjectRole::Role::SpendTimeMonth: return QVariant(convertSecondsToHHMMSSFormat(m_list[static_cast<size_t>(index.row())]->spendTimeMonth()));
    case ProjectRole::Role::SpendTimeAll: return QVariant(convertSecondsToHHMMSSFormat(m_list[static_cast<size_t>(index.row())]->spendTimeMonth()));
    }

    return QVariant();
}

void ProjectModel::updateValue(int projectId, QString name, bool active, bool watcher)
{
    auto it = std::find_if(std::begin(m_list), std::end(m_list), [projectId](const Project* pr) { return pr->id() == projectId;});
    if (it == m_list.end())
    {
        return;
    }

    (*it)->setName(name);
    (*it)->setOwnerWatcher(watcher);
    (*it)->setActive(active);
}

QHash<int, QByteArray> ProjectModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ProjectRole::Role::Id] = "id";
    roles[ProjectRole::Role::Name] = "name";
    roles[ProjectRole::Role::Active] = "active";
    roles[ProjectRole::Role::Logo] = "logoUrl";
    roles[ProjectRole::Role::Position] = "position";
    roles[ProjectRole::Role::Watcher] = "watcher";
    roles[ProjectRole::Role::SpendTimeWeek] = "spendTimeWeek";
    roles[ProjectRole::Role::SpendTimeMonth] = "spendTimeMonth";
    roles[ProjectRole::Role::SpendTimeAll] = "spendTimeAll";

    return roles;
}
