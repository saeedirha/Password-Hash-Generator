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

#include "chashgenerator.h"

CHashGenerator::CHashGenerator(QObject *parent) : QObject(parent)
{

}

QString CHashGenerator::getMD5_Hash(const QString &input)
{
    QByteArray bytes = input.toStdString().c_str();

    QString hash = QString( QCryptographicHash::hash( (bytes ),QCryptographicHash::Md5).toHex());
    return hash;
}

QString CHashGenerator::getSHA1_Hash(const QString &input)
{
    QByteArray bytes = input.toStdString().c_str();

    QString hash = QString( QCryptographicHash::hash( (bytes ),QCryptographicHash::Sha1).toHex());
    return hash;
}

QString CHashGenerator::getSHA256_Hash(const QString &input)
{
    QByteArray bytes = input.toStdString().c_str();

    QString hash = QString( QCryptographicHash::hash( (bytes ),QCryptographicHash::Sha256).toHex());
    return hash;
}

QString CHashGenerator::getMYSQL_Hash(const QString &input)
{
    QByteArray bytes = input.toStdString().c_str();

    QString hash = QString( QCryptographicHash::hash( (QCryptographicHash::hash( (bytes ),QCryptographicHash::Sha1) ),QCryptographicHash::Sha1).toHex() );
    return hash;
}

QString CHashGenerator::base64_encode(const QString &input)
{
    QByteArray ba;
     ba.append(input);
     return ba.toBase64();
}

