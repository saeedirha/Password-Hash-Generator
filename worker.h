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
#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QFile>
#include "chashgenerator.h"
#include <QtSql>
#include <QDebug>
#include <QWaitCondition>
#include <QException>

//Worker Thread to load passwords from text file , generate hash and store them into database file
class Worker : public QThread
{
    Q_OBJECT

public:
    explicit Worker(QThread *parent = 0, const QString &PassFile ="" , const QString& DB_Filename= "Unknown");
    ~Worker();
    void run();

   volatile bool Pause , Stop=false;
    int Speed=1;
    QWaitCondition m_waiter;

    //static int counter;

signals:
    void UpdateMainGUI(const QString&);

public slots:

private:
    CHashGenerator *CHash;
    QString PassFile, DB_File;
    QMutex mutex;

    QSqlDatabase myDatabase;

    void InsertIntoDatabase(const QString &Word);

};

#endif // WORKER_H
