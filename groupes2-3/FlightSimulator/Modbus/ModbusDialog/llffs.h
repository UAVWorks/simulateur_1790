#ifndef LLFFS_H
#define LLFFS_H

#include "ui_llffs.h"

class LLFFS : public QWidget, private Ui::LLFFS
{
    Q_OBJECT

public:
    explicit LLFFS(QWidget *parent = 0);
};

#endif // LLFFS_H
