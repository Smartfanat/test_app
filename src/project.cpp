#include "headers/project.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    mItems.append({ QString("Name1"), QString("Logo"), 1, 1, true });
    mItems.append({ QString("Name2"), QString("Logo"), 1, 1, true });
}

QVector<Project> ToDoList::items() const
{
    return mItems;
}

bool ToDoList::setItemAt(int index, const Project &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const Project &oldItem = mItems.at(index);
    if (item.m_id == oldItem.m_id)
        return false;

    mItems[index] = item;
    return true;
}

void ToDoList::appendItem()
{
    emit preItemAppended();

    Project item;
    item.m_name = "";
    mItems.append(item);

    emit postItemAppended();
}

void ToDoList::removeCompletedItems()
{
}
