#include "../include/MainWindow.h"

#include <QAbstractItemView>
#include <QAction>
#include <QApplication>
#include <QGuiApplication>
#include <QColumnView>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QMenu>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QSortFilterProxyModel>
#include <QSplitter>
#include <QStackedWidget>
#include <QSet>
#include <QTableView>
#include <QTextEdit>
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QUrl>
#include <QVBoxLayout>
#include <QKeySequence>
#include <QStyleHints>

namespace {
constexpr int kIconViewIndex = 0;
constexpr int kListViewIndex = 1;
constexpr int kColumnViewIndex = 2;
constexpr int kPreviewImageIndex = 0;
constexpr int kPreviewTextIndex = 1;
constexpr int kPreviewInfoIndex = 2;

QString readable_size(qint64 bytes) {
    constexpr qint64 KB = 1024;
    constexpr qint64 MB = KB * 1024;
    constexpr qint64 GB = MB * 1024;
    constexpr qint64 TB = GB * 1024;

    if (bytes >= TB) return QString::number(bytes / static_cast<double>(TB), 'f', 1) + " TB";
    if (bytes >= GB) return QString::number(bytes / static_cast<double>(GB), 'f', 1) + " GB";
    if (bytes >= MB) return QString::number(bytes / static_cast<double>(MB), 'f', 1) + " MB";
    if (bytes >= KB) return QString::number(bytes / static_cast<double>(KB), 'f', 1) + " KB";
    return QString::number(bytes) + " B";
}

bool is_text_file(const QString& ext) {
    static const QStringList kTextExt{
        "txt","md","json","cpp","h","hpp","c","cc","m","mm","py","js","ts",
        "css","html","xml","yaml","yml","ini","log","sh","rs","go"
    };
    return kTextExt.contains(ext.toLower());
}

bool is_image_file(const QString& ext) {
    static const QStringList kImageExt{"png","jpg","jpeg","bmp","gif","tiff","heic"};
    return kImageExt.contains(ext.toLower());
}
}  // namespace

MainWindow::MainWindow() {
    build_ui();
    connect_signals();

    const QString home_path = QDir::homePath();
    set_directory(home_path, true);
    tree_view_->expand(tree_model_->index(home_path));
}

void MainWindow::build_ui() {
    setWindowTitle("Finder");
    resize(1320, 820);

    tree_model_ = new QFileSystemModel(this);
    tree_model_->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    tree_model_->setRootPath(QDir::rootPath());

    file_model_ = new QFileSystemModel(this);
    file_model_->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    file_model_->setRootPath(QDir::homePath());

    filter_model_ = new QSortFilterProxyModel(this);
    filter_model_->setSourceModel(file_model_);
    filter_model_->setFilterKeyColumn(0);
    filter_model_->setFilterCaseSensitivity(Qt::CaseInsensitive);

    favorites_list_ = new QListWidget(this);
    favorites_list_->setSelectionMode(QAbstractItemView::SingleSelection);
    favorites_list_->setAlternatingRowColors(true);
    favorites_list_->setMinimumHeight(180);
    favorites_list_->setSpacing(2);
    favorites_list_->setUniformItemSizes(true);

    auto add_favorite = [this](const QString& label, const QString& path) {
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, path);
        favorites_list_->addItem(item);
    };
    add_favorite("Home", QDir::homePath());
    add_favorite("Desktop", QDir::homePath() + "/Desktop");
    add_favorite("Documents", QDir::homePath() + "/Documents");
    add_favorite("Downloads", QDir::homePath() + "/Downloads");
    add_favorite("Applications", "/Applications");

    tree_view_ = new QTreeView(this);
    tree_view_->setModel(tree_model_);
    tree_view_->setRootIndex(tree_model_->index(QDir::rootPath()));
    tree_view_->setHeaderHidden(true);
    tree_view_->setAnimated(true);
    tree_view_->setUniformRowHeights(true);
    tree_view_->setExpandsOnDoubleClick(true);

    auto* left_panel = new QWidget(this);
    auto* left_layout = new QVBoxLayout(left_panel);
    left_layout->setContentsMargins(8, 8, 8, 8);
    left_layout->setSpacing(6);
    left_layout->addWidget(new QLabel("Favorites", left_panel));
    left_layout->addWidget(favorites_list_);
    left_layout->addWidget(new QLabel("Folders", left_panel));
    left_layout->addWidget(tree_view_);

    list_view_ = new QTableView(this);
    list_view_->setModel(filter_model_);
    list_view_->setSelectionBehavior(QAbstractItemView::SelectRows);
    list_view_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    list_view_->setSortingEnabled(true);
    list_view_->horizontalHeader()->setStretchLastSection(true);
    list_view_->verticalHeader()->setVisible(false);
    list_view_->setShowGrid(false);
    list_view_->setAlternatingRowColors(true);
    list_view_->setDragDropMode(QAbstractItemView::DragDrop);
    list_view_->setDragEnabled(true);
    list_view_->setAcceptDrops(true);
    list_view_->setDefaultDropAction(Qt::MoveAction);
    list_view_->setColumnWidth(0, 320);
    list_view_->setColumnWidth(1, 120);
    list_view_->setColumnWidth(2, 140);

    icon_view_ = new QListView(this);
    icon_view_->setModel(filter_model_);
    icon_view_->setViewMode(QListView::IconMode);
    icon_view_->setIconSize(QSize(72, 72));
    icon_view_->setResizeMode(QListView::Adjust);
    icon_view_->setMovement(QListView::Static);
    icon_view_->setSpacing(14);
    icon_view_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    icon_view_->setDragDropMode(QAbstractItemView::DragDrop);
    icon_view_->setDragEnabled(true);
    icon_view_->setAcceptDrops(true);
    icon_view_->setDefaultDropAction(Qt::MoveAction);

    column_view_ = new QColumnView(this);
    column_view_->setModel(filter_model_);
    column_view_->setResizeGripsVisible(true);
    column_view_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    column_view_->setDragDropMode(QAbstractItemView::DragDrop);
    column_view_->setDragEnabled(true);
    column_view_->setAcceptDrops(true);
    column_view_->setDefaultDropAction(Qt::MoveAction);

    view_stack_ = new QStackedWidget(this);
    view_stack_->addWidget(icon_view_);
    view_stack_->addWidget(list_view_);
    view_stack_->addWidget(column_view_);
    view_stack_->setCurrentIndex(kListViewIndex);

    preview_title_ = new QLabel("No selection", this);
    preview_title_->setStyleSheet("font-weight: 600;");
    preview_meta_ = new QLabel(this);
    preview_meta_->setWordWrap(true);

    preview_image_ = new QLabel(this);
    preview_image_->setAlignment(Qt::AlignCenter);
    preview_image_->setMinimumHeight(180);

    preview_text_ = new QTextEdit(this);
    preview_text_->setReadOnly(true);

    auto* preview_info = new QWidget(this);
    auto* preview_info_layout = new QVBoxLayout(preview_info);
    preview_info_layout->addWidget(preview_title_);
    preview_info_layout->addWidget(preview_meta_);
    preview_info_layout->addStretch();

    preview_stack_ = new QStackedWidget(this);
    preview_stack_->addWidget(preview_image_);
    preview_stack_->addWidget(preview_text_);
    preview_stack_->addWidget(preview_info);
    preview_stack_->setCurrentIndex(kPreviewInfoIndex);

    auto* preview_panel = new QWidget(this);
    auto* preview_layout = new QVBoxLayout(preview_panel);
    preview_layout->setContentsMargins(8, 8, 8, 8);
    preview_layout->addWidget(new QLabel("Preview", preview_panel));
    preview_layout->addWidget(preview_stack_);

    auto* main_splitter = new QSplitter(this);
    main_splitter->addWidget(left_panel);
    main_splitter->addWidget(view_stack_);
    main_splitter->addWidget(preview_panel);
    main_splitter->setStretchFactor(1, 1);
    main_splitter->setSizes({260, 820, 240});
    setCentralWidget(main_splitter);

    auto* nav_toolbar = addToolBar("Navigation");
    nav_toolbar->setMovable(false);

    back_action_ = nav_toolbar->addAction("Back");
    forward_action_ = nav_toolbar->addAction("Forward");
    up_action_ = nav_toolbar->addAction("Up");
    nav_toolbar->addSeparator();

    path_edit_ = new QLineEdit(this);
    path_edit_->setPlaceholderText("Path");
    path_edit_->setMinimumWidth(340);
    nav_toolbar->addWidget(path_edit_);

    nav_toolbar->addSeparator();
    search_edit_ = new QLineEdit(this);
    search_edit_->setPlaceholderText("Search");
    search_edit_->setMinimumWidth(220);
    nav_toolbar->addWidget(search_edit_);

    nav_toolbar->addSeparator();
    list_view_action_ = nav_toolbar->addAction("List");
    icon_view_action_ = nav_toolbar->addAction("Icons");
    column_view_action_ = nav_toolbar->addAction("Columns");

    nav_toolbar->addSeparator();
    theme_toggle_action_ = nav_toolbar->addAction("Theme: System");
    theme_toggle_action_->setCheckable(true);
    theme_toggle_action_->setEnabled(false);

    path_toolbar_ = addToolBar("Path");
    path_toolbar_->setMovable(false);
    breadcrumb_bar_ = new QWidget(this);
    auto* breadcrumb_layout = new QHBoxLayout(breadcrumb_bar_);
    breadcrumb_layout->setContentsMargins(6, 2, 6, 2);
    breadcrumb_layout->setSpacing(4);
    path_toolbar_->addWidget(breadcrumb_bar_);

    sync_theme_with_system();

    auto* delete_shortcut = new QAction(this);
    delete_shortcut->setShortcut(QKeySequence::Delete);
    addAction(delete_shortcut);
    connect(delete_shortcut, &QAction::triggered, this, [this]() { delete_selected(); });

    auto* rename_shortcut = new QAction(this);
    rename_shortcut->setShortcut(Qt::Key_Return);
    addAction(rename_shortcut);
    connect(rename_shortcut, &QAction::triggered, this, [this]() { rename_selected(); });
}

void MainWindow::connect_signals() {
    connect(favorites_list_, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        const QString path = item->data(Qt::UserRole).toString();
        set_directory(path, true);
    });

    connect(tree_view_, &QTreeView::clicked, this, [this](const QModelIndex& index) {
        const QString path = tree_model_->filePath(index);
        set_directory(path, true);
    });

    auto open_handler = [this](const QModelIndex& index) {
        open_item(index);
    };

    connect(list_view_, &QTableView::doubleClicked, this, open_handler);
    connect(icon_view_, &QListView::doubleClicked, this, open_handler);
    connect(column_view_, &QColumnView::doubleClicked, this, open_handler);

    auto preview_handler = [this](const QItemSelection& selection) {
        if (!selection.indexes().isEmpty()) {
            update_preview(selection.indexes().front());
        }
    };

    connect(list_view_->selectionModel(), &QItemSelectionModel::selectionChanged, this, preview_handler);
    connect(icon_view_->selectionModel(), &QItemSelectionModel::selectionChanged, this, preview_handler);
    connect(column_view_->selectionModel(), &QItemSelectionModel::selectionChanged, this, preview_handler);

    connect(path_edit_, &QLineEdit::returnPressed, this, [this]() {
        set_directory(path_edit_->text(), true);
    });

    connect(search_edit_, &QLineEdit::textChanged, this, [this](const QString& text) {
        filter_model_->setFilterFixedString(text);
    });

    connect(back_action_, &QAction::triggered, this, [this]() {
        if (history_index_ > 0) {
            history_index_ -= 1;
            set_directory(history_.at(history_index_), false);
        }
    });

    connect(forward_action_, &QAction::triggered, this, [this]() {
        if (history_index_ + 1 < history_.size()) {
            history_index_ += 1;
            set_directory(history_.at(history_index_), false);
        }
    });

    connect(up_action_, &QAction::triggered, this, [this]() {
        const QString current = file_model_->rootPath();
        QDir dir(current);
        if (dir.cdUp()) {
            set_directory(dir.absolutePath(), true);
        }
    });

    connect(list_view_action_, &QAction::triggered, this, [this]() {
        view_stack_->setCurrentIndex(kListViewIndex);
    });

    connect(icon_view_action_, &QAction::triggered, this, [this]() {
        view_stack_->setCurrentIndex(kIconViewIndex);
    });

    connect(column_view_action_, &QAction::triggered, this, [this]() {
        view_stack_->setCurrentIndex(kColumnViewIndex);
    });

    connect(qGuiApp->styleHints(), &QStyleHints::colorSchemeChanged, this, [this]() {
        sync_theme_with_system();
    });

    auto context_handler = [this](const QPoint& pos) {
        auto* view = qobject_cast<QAbstractItemView*>(sender());
        if (view) show_context_menu(pos, view);
    };

    list_view_->setContextMenuPolicy(Qt::CustomContextMenu);
    icon_view_->setContextMenuPolicy(Qt::CustomContextMenu);
    column_view_->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(list_view_, &QWidget::customContextMenuRequested, this, context_handler);
    connect(icon_view_, &QWidget::customContextMenuRequested, this, context_handler);
    connect(column_view_, &QWidget::customContextMenuRequested, this, context_handler);
}

void MainWindow::set_directory(const QString& path, bool add_history) {
    QFileInfo info(path);
    if (!info.exists() || !info.isDir()) {
        return;
    }

    const QString absolute_path = info.absoluteFilePath();
    file_model_->setRootPath(absolute_path);
    const QModelIndex source_root = file_model_->index(absolute_path);
    const QModelIndex proxy_root = filter_model_->mapFromSource(source_root);

    list_view_->setRootIndex(proxy_root);
    icon_view_->setRootIndex(proxy_root);
    column_view_->setRootIndex(proxy_root);
    path_edit_->setText(absolute_path);
    rebuild_breadcrumbs(absolute_path);

    const QModelIndex tree_index = tree_model_->index(absolute_path);
    if (tree_index.isValid()) {
        tree_view_->setCurrentIndex(tree_index);
    }

    if (add_history) {
        if (history_index_ + 1 < history_.size()) {
            history_ = history_.mid(0, history_index_ + 1);
        }
        history_.push_back(absolute_path);
        history_index_ = history_.size() - 1;
    }

    update_history_actions();
}

void MainWindow::apply_theme(bool dark) {
    dark_theme_ = dark;
    if (theme_toggle_action_) {
        theme_toggle_action_->setChecked(dark);
    }
    if (dark) {
        setStyleSheet(
            "QMainWindow { background: #1d1f24; }"
            "QToolBar { background: #23262c; border: none; spacing: 6px; }"
            "QListWidget, QTreeView, QTableView, QListView, QColumnView { background: #1f2329; color: #e6e6e6; }"
            "QLineEdit { background: #2b2f36; color: #f2f2f2; border: 1px solid #3a404a; border-radius: 6px; padding: 4px 6px; }"
            "QLabel { color: #e6e6e6; }"
            "QHeaderView::section { background: #2b2f36; color: #e6e6e6; border: none; }"
            "QListWidget::item:selected, QTreeView::item:selected, QTableView::item:selected, QListView::item:selected {"
            "  background: #3d4a5c; color: #ffffff; }"
        );
    } else {
        setStyleSheet(
            "QMainWindow { background: #f2f2f2; }"
            "QToolBar { background: #f4f4f4; border: none; spacing: 6px; }"
            "QListWidget, QTreeView, QTableView, QListView, QColumnView { background: #fbfbfb; color: #1f1f1f; }"
            "QLineEdit { background: white; border: 1px solid #d7d7d7; border-radius: 6px; padding: 4px 6px; }"
            "QLabel { color: #2b2b2b; }"
            "QHeaderView::section { background: #f0f0f0; color: #1f1f1f; border: none; }"
            "QListWidget::item:selected, QTreeView::item:selected, QTableView::item:selected, QListView::item:selected {"
            "  background: #c9dcff; color: #0e2a4d; }"
        );
    }
}

void MainWindow::sync_theme_with_system() {
    const Qt::ColorScheme scheme = qGuiApp->styleHints()->colorScheme();
    const bool system_dark = scheme == Qt::ColorScheme::Dark;
    apply_theme(system_dark);
}

void MainWindow::open_item(const QModelIndex& proxy_index) {
    const QString path = index_path(proxy_index);
    const QFileInfo info(path);
    if (info.isDir()) {
        set_directory(path, true);
        return;
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::update_history_actions() {
    back_action_->setEnabled(history_index_ > 0);
    forward_action_->setEnabled(history_index_ + 1 < history_.size());
}

void MainWindow::rebuild_breadcrumbs(const QString& path) {
    auto* layout = qobject_cast<QHBoxLayout*>(breadcrumb_bar_->layout());
    if (!layout) return;

    QLayoutItem* child = nullptr;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QString current;
    const QStringList parts = QDir::toNativeSeparators(path).split('/', Qt::SkipEmptyParts);
    QPushButton* root_button = new QPushButton("/", breadcrumb_bar_);
    root_button->setFlat(true);
    connect(root_button, &QPushButton::clicked, this, [this]() { set_directory("/", true); });
    layout->addWidget(root_button);

    for (const QString& part : parts) {
        current += "/" + part;
        auto* btn = new QPushButton(part, breadcrumb_bar_);
        btn->setFlat(true);
        connect(btn, &QPushButton::clicked, this, [this, current]() { set_directory(current, true); });
        layout->addWidget(btn);
    }

    layout->addStretch();
}

void MainWindow::update_preview(const QModelIndex& proxy_index) {
    const QString path = index_path(proxy_index);
    const QFileInfo info(path);

    preview_title_->setText(info.fileName());
    preview_meta_->setText(info.isDir()
        ? "Folder"
        : QString("%1 • %2").arg(readable_size(info.size()), info.lastModified().toString("yyyy-MM-dd HH:mm")));

    if (info.isDir()) {
        preview_stack_->setCurrentIndex(kPreviewInfoIndex);
        return;
    }

    const QString ext = info.suffix();
    if (is_image_file(ext)) {
        QPixmap pix(path);
        if (!pix.isNull()) {
            preview_image_->setPixmap(pix.scaled(260, 260, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            preview_stack_->setCurrentIndex(kPreviewImageIndex);
            return;
        }
    }

    if (is_text_file(ext)) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            const QByteArray data = file.read(200 * 1024);
            preview_text_->setPlainText(QString::fromUtf8(data));
            preview_stack_->setCurrentIndex(kPreviewTextIndex);
            return;
        }
    }

    preview_stack_->setCurrentIndex(kPreviewInfoIndex);
}

void MainWindow::show_context_menu(const QPoint& position, QAbstractItemView* view) {
    QMenu menu(this);
    const QModelIndex clicked_index = view->indexAt(position);
    if (clicked_index.isValid()) {
        view->setCurrentIndex(clicked_index);
    }

    QAction* open_action = menu.addAction("Open");
    QAction* rename_action = menu.addAction("Rename");
    QAction* delete_action = menu.addAction("Delete");
    menu.addSeparator();
    QAction* new_folder_action = menu.addAction("New Folder");

    QAction* chosen = menu.exec(view->viewport()->mapToGlobal(position));
    if (!chosen) return;

    if (chosen == open_action) {
        open_item(current_index_from_view(view));
    } else if (chosen == rename_action) {
        rename_selected();
    } else if (chosen == delete_action) {
        delete_selected();
    } else if (chosen == new_folder_action) {
        create_folder();
    }
}

QModelIndex MainWindow::current_index_from_view(QAbstractItemView* view) const {
    if (!view) return {};
    return view->currentIndex();
}

QString MainWindow::index_path(const QModelIndex& proxy_index) const {
    if (!proxy_index.isValid()) return {};
    const QModelIndex source_index = filter_model_->mapToSource(proxy_index);
    return file_model_->filePath(source_index);
}

void MainWindow::create_folder() {
    const QString base = file_model_->rootPath();
    QString new_name = "New Folder";
    QDir dir(base);
    if (dir.exists(new_name)) {
        int suffix = 2;
        while (dir.exists(QString("New Folder %1").arg(suffix))) {
            suffix += 1;
        }
        new_name = QString("New Folder %1").arg(suffix);
    }

    if (dir.mkdir(new_name)) {
        const QModelIndex source = file_model_->index(base + "/" + new_name);
        const QModelIndex proxy = filter_model_->mapFromSource(source);
        QAbstractItemView* view = qobject_cast<QAbstractItemView*>(view_stack_->currentWidget());
        if (view) {
            view->setCurrentIndex(proxy);
            view->edit(proxy);
        }
    }
}

void MainWindow::delete_selected() {
    QAbstractItemView* view = qobject_cast<QAbstractItemView*>(view_stack_->currentWidget());
    if (!view) return;
    const QModelIndexList selected = view->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) return;

    QSet<QString> paths;
    for (const QModelIndex& idx : selected) {
        if (idx.column() != 0) continue;
        const QString path = index_path(idx);
        if (!path.isEmpty()) paths.insert(path);
    }
    if (paths.isEmpty()) return;

    const QString text = paths.size() == 1
        ? QString("Delete \"%1\"?").arg(QFileInfo(*paths.begin()).fileName())
        : QString("Delete %1 items?").arg(paths.size());

    if (QMessageBox::question(this, "Delete", text) != QMessageBox::Yes) return;

    for (const QString& path : paths) {
        QFileInfo info(path);
        if (info.isDir()) {
            QDir dir(path);
            dir.removeRecursively();
        } else {
            QFile::remove(path);
        }
    }
}

void MainWindow::rename_selected() {
    QAbstractItemView* view = qobject_cast<QAbstractItemView*>(view_stack_->currentWidget());
    if (!view) return;
    const QModelIndex proxy = view->currentIndex();
    if (!proxy.isValid()) return;
    view->edit(proxy);
}
