#ifndef FS_MAIN_WINDOW_H
#define FS_MAIN_WINDOW_H

#include <QMainWindow>
#include "path_history.h"

class QFileSystemModel;
class QSortFilterProxyModel;
class QTreeView;
class QTableView;
class QListView;
class QColumnView;
class QStackedWidget;
class QLineEdit;
class QAction;
class QListWidget;
class QLabel;
class QTextEdit;
class QToolBar;
class QToolButton;
class QWidget;
class QAbstractItemView;

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private:
    void build_ui();
    void connect_signals();
    void set_directory(const QString& path, bool add_history = true);
    void open_item(const QModelIndex& proxy_index);
    void update_history_actions();
    void apply_theme(bool dark);
    void sync_theme_with_system();
    void rebuild_breadcrumbs(const QString& path);
    void update_preview(const QModelIndex& proxy_index);
    void show_context_menu(const QPoint& position, QAbstractItemView* view);
    QModelIndex current_index_from_view(QAbstractItemView* view) const;
    QString index_path(const QModelIndex& proxy_index) const;
    void create_folder();
    void delete_selected();
    void rename_selected();

    QFileSystemModel* tree_model_{nullptr};
    QFileSystemModel* file_model_{nullptr};
    QSortFilterProxyModel* filter_model_{nullptr};

    QListWidget* favorites_list_{nullptr};
    QTreeView* tree_view_{nullptr};
    QTableView* list_view_{nullptr};
    QListView* icon_view_{nullptr};
    QColumnView* column_view_{nullptr};
    QStackedWidget* view_stack_{nullptr};

    QWidget* breadcrumb_bar_{nullptr};
    QToolBar* path_toolbar_{nullptr};

    QLineEdit* path_edit_{nullptr};
    QLineEdit* search_edit_{nullptr};

    QAction* back_action_{nullptr};
    QAction* forward_action_{nullptr};
    QAction* up_action_{nullptr};
    QAction* list_view_action_{nullptr};
    QAction* icon_view_action_{nullptr};
    QAction* column_view_action_{nullptr};
    QAction* theme_toggle_action_{nullptr};

    QLabel* preview_title_{nullptr};
    QLabel* preview_meta_{nullptr};
    QLabel* preview_image_{nullptr};
    QTextEdit* preview_text_{nullptr};
    QStackedWidget* preview_stack_{nullptr};

    path_history path_history_;
    bool dark_theme_{false};
};

#endif
