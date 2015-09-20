/*
 * Copyright (C) 2015 SaEeD
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QException>
#include "chashgenerator.h"
#include "worker.h"
namespace Ui {
class MainWindow;
}
//Main window Class
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString FilePath;

private slots:
    void on_btnSelectFile_clicked();

    void on_btnGenerate_clicked();

    void on_txtInput_returnPressed();

    void getChangeFromThread(const QString &value);
    void Worker_Done();

    void on_btnGenerateAndSave_clicked();

    void on_mSlider_valueChanged(int value);

    void on_btnCancel_clicked();

    void on_btnPause_clicked();

    void on_btnResume_clicked();

private:
    Ui::MainWindow *ui;
    CHashGenerator *cHash;
    Worker *WorkerThread;

    int Word_counter=0;
};

#endif // MAINWINDOW_H
