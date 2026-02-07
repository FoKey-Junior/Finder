#ifndef FS_PATH_HISTORY_H
#define FS_PATH_HISTORY_H

#include <QStringList>

class path_history {
public:
    void push(const QString& path);
    [[nodiscard]] bool can_back() const noexcept;
    [[nodiscard]] bool can_forward() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    QString back();
    QString forward();

private:
    QStringList entries_;
    int index_{-1};
};

#endif
