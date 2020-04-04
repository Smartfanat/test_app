#include "headers/project.h"
#include "headers/projectmodel.h"

namespace  {
static QString convertSecondsToHHMMSSFormat(int duration)
{
    return QString("%1:%2:%3").arg(duration/3600, 2, 10, QChar('0')).arg((duration/60)%60, 2, 10, QChar('0')).arg((duration/3600)%60, 2, 10, QChar('0'));
}
}

ProjectModel::ProjectModel(QObject *obj)
    : QAbstractListModel(obj)
{
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
    case Role::Id: return QVariant(m_list[static_cast<size_t>(index.row())]->id());
    case Role::Name: return QVariant(m_list[static_cast<size_t>(index.row())]->name());
    case Role::Active: return QVariant(m_list[static_cast<size_t>(index.row())]->active());
    case Role::Logo: return QVariant(m_list[static_cast<size_t>(index.row())]->logoUrl());
    case Role::Position: return QVariant(m_list[static_cast<size_t>(index.row())]->position());
    case Role::Watcher: return QVariant(m_list[static_cast<size_t>(index.row())]->watcher());
    case Role::SpendTimeWeek: return QVariant(convertSecondsToHHMMSSFormat(m_list[static_cast<size_t>(index.row())]->spendTimeWeek()));
    case Role::SpendTimeMonth: return QVariant(convertSecondsToHHMMSSFormat(m_list[static_cast<size_t>(index.row())]->spendTimeMonth()));
    case Role::SpendTimeAll: return QVariant(convertSecondsToHHMMSSFormat(m_list[static_cast<size_t>(index.row())]->spendTimeMonth()));
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
    roles[Role::Id] = "id";
    roles[Role::Name] = "name";
    roles[Role::Active] = "active";
    roles[Role::Logo] = "logoUrl";
    roles[Role::Position] = "position";
    roles[Role::Watcher] = "watcher";
    roles[Role::SpendTimeWeek] = "spendTimeWeek";
    roles[Role::SpendTimeMonth] = "spendTimeMonth";
    roles[Role::SpendTimeAll] = "spendTimeAll";

    return roles;
}
