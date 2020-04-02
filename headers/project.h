#pragma once

#include <QObject>

struct Project : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString logoUrl READ logoUrl WRITE setLogoUrl)
    Q_PROPERTY(QString uid READ uid WRITE setUid)
    Q_PROPERTY(int position READ position WRITE setPosition)
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(bool active READ active WRITE setActive)
    Q_PROPERTY(bool isOwnerWatcher READ watcher WRITE setOwnerWatcher)
    Q_PROPERTY(int spendTimeWeek READ spendTimeWeek WRITE setSpendTimeWeek)
    Q_PROPERTY(int spendTimeMonth READ spendTimeMonth WRITE setSpendTimeMonth)
    Q_PROPERTY(int spendTimeAll READ spendTimeAll WRITE setSpendTimeAll)

public:
    Project(QObject *parent = nullptr) : QObject(parent) {}
    bool operator==(const Project* other) const {
        return id() == other->id();
    }
    bool watcher() const
    {
        return m_isOwnerWatcher;
    }

    int spendTimeWeek() const
    {
        return m_spendTimeWeek;
    }

    int spendTimeMonth() const
    {
        return m_spendTimeMonth;
    }

    int spendTimeAll() const
    {
        return m_spendTimeAll;
    }

public slots:
    void dump() {}

    QString name() const
    {
        return m_name;
    }

    QString uid() const
    {
        return m_uid;
    }

    QString logoUrl() const
    {
        return m_logoUrl;
    }

    int position() const
    {
        return m_position;
    }

    int id() const
    {
        return m_id;
    }

    bool active() const
    {
        return m_active;
    }

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
    }

    void setLogoUrl(QString logoUrl)
    {
        m_logoUrl = logoUrl;
    }

    void setUid(QString uid)
    {
        m_uid = uid;
    }

    void setPosition(int position)
    {
        m_position = position;
    }

    void setId(int id)
    {
        m_id = id;
    }

    void setActive(bool active)
    {
        m_active = active;
    }

    void setOwnerWatcher(bool isOwnerWatcher)
    {
        m_isOwnerWatcher = isOwnerWatcher;
    }

    void setSpendTimeWeek(int spendTimeWeek)
    {
        m_spendTimeWeek = spendTimeWeek;
    }

    void setSpendTimeMonth(int spendTimeMonth)
    {
        m_spendTimeMonth = spendTimeMonth;
    }

    void setSpendTimeAll(int spendTimeAll)
    {
        m_spendTimeAll = spendTimeAll;
    }

private:
    QString m_name;
    QString m_uid;
    QString m_logoUrl;
    int m_position = 0;
    int m_id = 0;
    bool m_active = false;
    bool m_isOwnerWatcher = false;
    int m_spendTimeWeek = 0;
    int m_spendTimeMonth = 0;
    int m_spendTimeAll = 0;
};
