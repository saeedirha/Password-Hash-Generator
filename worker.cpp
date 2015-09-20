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

#include "worker.h"
Worker::Worker(QThread *parent, const QString &PassFile, const QString& DB_Filename)
    : QThread(parent), PassFile(PassFile), DB_File(DB_Filename)
{
    myDatabase = QSqlDatabase::addDatabase("QSQLITE");
    myDatabase.setDatabaseName(DB_File);

    QFileInfo checkFile(DB_File);

    if(checkFile.isFile())
    {
            if(myDatabase.open())
                qDebug() <<  "Connected to Database File!";
    }else{
        qDebug() << "[!]Cannot Connect to Database File!";
    }

    CHash = new CHashGenerator(this);

}
Worker::~Worker()
{
    myDatabase.close();
    delete CHash;
    qDebug() << "[*]Destroying Worker Thread Resources: done!";
}

void Worker::run()
{
    qDebug() << "Starting Thread:" << PassFile << " Database: " << DB_File;
    QString line;

    QFile file(PassFile);
    if(!file.exists())
    {
       qDebug() <<"Error Accessing file.";
        return;
    }
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() <<"Error Accessing file.";
        return;
    }

    QTextStream input(&file);
    while(!input.atEnd())
    {
        line = input.readLine();

        mutex.lock();

        msleep(1*Speed);
       // qDebug() << "Speed is: " << Speed;
       // mutex.unlock();
        if(this->Stop == true)
        {
            qDebug() <<"[!]Thread Canceled";
            mutex.unlock();
            break;
        }
        if(this->Pause == true)
        {
            qDebug() <<"[!]Thread Paused.";
           m_waiter.wait(&mutex);

        }
        mutex.unlock();
        InsertIntoDatabase(line);
        emit UpdateMainGUI(line);
    }
    qDebug() <<"End of Word List file!";

}

//Inserting hash into Database
void Worker::InsertIntoDatabase(const QString &Word)
{

    if(!myDatabase.isOpen())
    {
        qDebug() << "Connection to Database is lost! :(";
        return;
    }
    QSqlQuery qry;

    qry.exec("INSERT INTO 'HashList' ( 'Word' ,'MD5', 'SHA1', 'SHA256', 'MySQL', 'Base64' ) VALUES ( '"
             + Word + "',"
             + "'" + CHash->getMD5_Hash(Word) +"'," +
             + "'" + CHash->getSHA1_Hash(Word) +"'," +
             + "'" + CHash->getSHA256_Hash(Word) +"'," +
             + "'" + CHash->getMYSQL_Hash(Word) +"'," +
             + "'" + CHash->base64_encode(Word)
             + "' )" );

}
