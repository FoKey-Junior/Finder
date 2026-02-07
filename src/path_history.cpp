#include "../include/path_history.h"

void path_history::push(const QString& path) {
    if (index_ + 1 < entries_.size()) {
        entries_ = entries_.mid(0, index_ + 1);
    }
    entries_.push_back(path);
    index_ = entries_.size() - 1;
}

bool path_history::can_back() const noexcept {
    return index_ > 0;
}

bool path_history::can_forward() const noexcept {
    return index_ + 1 < entries_.size();
}

bool path_history::empty() const noexcept {
    return entries_.isEmpty();
}

QString path_history::back() {
    if (!can_back()) {
        return {};
    }
    index_ -= 1;
    return entries_.at(index_);
}

QString path_history::forward() {
    if (!can_forward()) {
        return {};
    }
    index_ += 1;
    return entries_.at(index_);
}
