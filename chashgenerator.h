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
#ifndef CHASHGENERATOR_H
#define CHASHGENERATOR_H

#include <QObject>
#include <QString>
#include <QCryptographicHash>
#include <QByteArray>
//Hash generator Class
class CHashGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CHashGenerator(QObject *parent = 0);

    QString getMD5_Hash(const QString &input);
    QString getSHA1_Hash(const QString &input);
    QString getSHA256_Hash(const QString &input);
    QString getMYSQL_Hash(const QString &input);
    QString base64_encode(const QString &input);

signals:

public slots:
};

#endif // CHASHGENERATOR_H
