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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chashgenerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cHash = new CHashGenerator(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSelectFile_clicked()
{
    FilePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            ".", tr("Text files (*.txt);;All files (*.*)") );
    ui->txtPassListFile->setText(FilePath);

}

void MainWindow::on_btnGenerate_clicked()
{

  ui->lblCurrentWord->setText(ui->txtInput->text());
  ui->lblMD5->setText(cHash->getMD5_Hash(ui->txtInput->text()));
  ui->lblSha1->setText(cHash->getSHA1_Hash(ui->txtInput->text()));
  ui->lblSha256->setText(cHash->getSHA256_Hash(ui->txtInput->text()));
  ui->lblMySQL->setText(cHash->getMYSQL_Hash(ui->txtInput->text()));
  ui->lblBase64->setText(cHash->base64_encode(ui->txtInput->text()));
}

void MainWindow::on_txtInput_returnPressed()
{
    on_btnGenerate_clicked();
}

void MainWindow::getChangeFromThread(const QString &value)
{
    Word_counter++;
    ui->lblCurrentWord->setText(value);
    ui->lblMD5->setText(cHash->getMD5_Hash(value));
    ui->lblSha1->setText(cHash->getSHA1_Hash(value));
    ui->lblSha256->setText(cHash->getSHA256_Hash(value));
    ui->lblMySQL->setText(cHash->getMYSQL_Hash(value));
    ui->lblBase64->setText(cHash->base64_encode(value));
    qDebug() <<"Line number: " << Word_counter;
}

void MainWindow::on_btnGenerateAndSave_clicked()
{

    QFileInfo checkFile("Password-Hash.sqlite");

    if(checkFile.isFile())
    {
        WorkerThread = new Worker(NULL, ui->txtPassListFile->text(), "Password-Hash.sqlite");
    }else{

        QMessageBox::information(this, "Message:" , "SQLite Database file doesn't exist, It will be created now.");
        qDebug() << "[+]Creating SQLite Database File";
        QSqlDatabase myDatabase  = QSqlDatabase::addDatabase("QSQLITE");
        myDatabase.setDatabaseName("Password-Hash.sqlite");
        myDatabase.open();

        QSqlQuery qry;
        QString stmnt = "CREATE  TABLE 'main'.'HashList' ( 'ID' INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE  DEFAULT 1, 'Word' TEXT NOT NULL , 'MD5' TEXT, 'SHA1' TEXT, 'SHA256' TEXT, 'MySQL' TEXT, 'Base64' TEXT) ";

        qry.exec(stmnt);

        myDatabase.close();
        WorkerThread = new Worker(NULL, ui->txtPassListFile->text(), "Password-Hash.sqlite");

    }


    ui->btnGenerateAndSave->setEnabled(false);
    ui->btnPause->setEnabled(true);
    ui->btnResume->setEnabled(false);
    ui->btnCancel->setEnabled(true);

//    WorkerThread = new Worker(NULL, ui->txtPassListFile->text(), "D:/Password-Hash.sqlite");

    connect(WorkerThread, SIGNAL(UpdateMainGUI(QString)), this, SLOT(getChangeFromThread(QString)));
    connect(WorkerThread, SIGNAL(finished()), this, SLOT(Worker_Done()));


    WorkerThread->start();
    qDebug() << WorkerThread->currentThreadId();
}

void MainWindow::Worker_Done()
{
    if(WorkerThread->isFinished())
    {
        ui->btnGenerateAndSave->setEnabled(true);
        ui->btnPause->setEnabled(false);
        ui->btnResume->setEnabled(false);
        ui->btnCancel->setEnabled(false);
        Word_counter=0;
        ui->statusBar->showMessage("[+]Thread\'s Job has Completed!!");
        WorkerThread->deleteLater();
    }
}


void MainWindow::on_mSlider_valueChanged(int value)
{
    if(WorkerThread != NULL || WorkerThread->isRunning())
    {
        WorkerThread->Speed = value;
        qDebug()<< value;
    }else{
        return;
    }

}

void MainWindow::on_btnCancel_clicked()
{
    if(WorkerThread->isRunning())
    {
        WorkerThread->Stop = true;
        qDebug() << "[!]Stopping Worker Thread";
    }
}

void MainWindow::on_btnPause_clicked()
{
    ui->btnCancel->setEnabled(false);
    ui->btnResume->setEnabled(true);
    ui->btnPause->setEnabled(false);
    if(WorkerThread->isRunning())
    {
        WorkerThread->Pause = true;
        qDebug() << "[!]Pausing Worker Thread";
    }
}

void MainWindow::on_btnResume_clicked()
{
    ui->btnCancel->setEnabled(true);
    ui->btnPause->setEnabled(true);
    ui->btnResume->setEnabled(false);
    if(WorkerThread->isRunning())
    {
        WorkerThread->Pause = false;
        WorkerThread->m_waiter.wakeAll();
        qDebug() << "[!]Resuming Worker Thread";
    }
}
