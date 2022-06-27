/*
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  SPDX-FileCopyrightText: 2022 Ignacy Kajdan <ignacy.kajdan@gmail.com>
 */

#ifndef LYCHEEPROVIDER_H
#define LYCHEEPROVIDER_H

#include <plasma/potdprovider/potdprovider.h>

#include <QImage>

class KJob;

class LycheeProvider : public PotdProvider
{
    Q_OBJECT

public:
    LycheeProvider(QObject *parent, const QVariantList &args);
    QImage image() const override;

private:
    void handleFinishedAlbumsRequest(KJob *job);
    void handleFinishedAlbumRequest(KJob *job);
    void handleFinishedImageRequest(KJob *job);
    QImage m_image;
    QStringList m_imagesUrl = {};
    QString m_serverUrl = QStringLiteral("https://lychee.example.com");
    QString m_apiKey = QStringLiteral("qwerty1234567890");
    QString m_albumName = QStringLiteral("Wallpapers");
    QString m_albumId;
    QStringList m_excludedTags = {"Low Resolution"};
};

#endif // LYCHEEPROVIDER_H
