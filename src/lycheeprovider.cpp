/*
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  SPDX-FileCopyrightText: 2022 Ignacy Kajdan <ignacy.kajdan@gmail.com>
 */

#include "lycheeprovider.h"

#include <KIO/Job>
#include <KPluginFactory>

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <random>

LycheeProvider::LycheeProvider(QObject *parent, const QVariantList &args)
    : PotdProvider(parent, args)
{
    KIO::StoredTransferJob *albumsRequestJob = KIO::storedHttpPost(QByteArray(), QUrl(m_serverUrl + QStringLiteral("/api/Albums::get")), KIO::HideProgressInfo);
    albumsRequestJob->addMetaData(QStringLiteral("accept"), QStringLiteral("application/json"));
    albumsRequestJob->addMetaData(QStringLiteral("content-type"), QStringLiteral("application/x-www-form-urlencoded"));
    albumsRequestJob->addMetaData(QStringLiteral("customHTTPHeader"), QStringLiteral("Authorization: ") + m_apiKey);

    connect(albumsRequestJob, &KIO::StoredTransferJob::finished, this, &LycheeProvider::handleFinishedAlbumsRequest);
}

QImage LycheeProvider::image() const
{
    return m_image;
}

void LycheeProvider::handleFinishedAlbumsRequest(KJob *job)
{
    KIO::StoredTransferJob *requestJob = static_cast<KIO::StoredTransferJob *>(job);
    if (requestJob->error()) {
        Q_EMIT error(this);
        return;
    }

    QJsonParseError json_error;
    QJsonDocument json_document = QJsonDocument::fromJson(requestJob->data(), &json_error);
    if (json_error.error != QJsonParseError::NoError) {
        Q_EMIT error(this);
        return;
    }

    QJsonObject json_object = json_document.object();
    QJsonArray json_array = json_object["albums"].toArray();
    foreach (const QJsonValue &json_value, json_array) {
        QJsonObject json_object = json_value.toObject();
        QString title = json_object["title"].toString();
        if (title == m_albumName) {
            m_albumId = json_object["id"].toString();
            break;
        }
    }

    QByteArray postData = ("albumID=" + m_albumId).toUtf8();
    KIO::StoredTransferJob *albumRequestJob = KIO::storedHttpPost(postData, QUrl(m_serverUrl + QStringLiteral("/api/Album::get")), KIO::HideProgressInfo);
    albumRequestJob->addMetaData(QStringLiteral("accept"), QStringLiteral("application/json"));
    albumRequestJob->addMetaData(QStringLiteral("content-type"), QStringLiteral("application/x-www-form-urlencoded"));
    albumRequestJob->addMetaData(QStringLiteral("customHTTPHeader"), QStringLiteral("Authorization: ") + m_apiKey);

    connect(albumRequestJob, &KIO::StoredTransferJob::finished, this, &LycheeProvider::handleFinishedAlbumRequest);
}

void LycheeProvider::handleFinishedAlbumRequest(KJob *job)
{
    KIO::StoredTransferJob *requestJob = static_cast<KIO::StoredTransferJob *>(job);
    if (requestJob->error()) {
        Q_EMIT error(this);
        return;
    }

    QJsonParseError json_error;
    QJsonDocument json_document = QJsonDocument::fromJson(requestJob->data(), &json_error);
    if (json_error.error != QJsonParseError::NoError) {
        Q_EMIT error(this);
        return;
    }

    QJsonObject json_object = json_document.object();
    QJsonArray json_array = json_object["photos"].toArray();
    foreach (const QJsonValue &json_value, json_array) {
        QJsonObject json_object = json_value.toObject();
        QString tags = json_object["tags"].toString();
        QStringList tagList = tags.split(',');
        bool include = true;
        if (tagList.size() > 0) {
            for (int i = 0; i < m_excludedTags.size(); i++) {
                if (tagList.contains(m_excludedTags.at(i), Qt::CaseInsensitive)) {
                    include = false;
                    break;
                }
            }
        }
        if (include) {
            m_imagesUrl.append(json_object["url"].toString());
        }
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, m_imagesUrl.size());

    auto index = uni(rng);

    const QUrl pictureUrl(m_serverUrl + QStringLiteral("/") + m_imagesUrl.at(index));

    KIO::StoredTransferJob *imageRequestJob = KIO::storedGet(pictureUrl, KIO::NoReload, KIO::HideProgressInfo);
    connect(imageRequestJob, &KIO::StoredTransferJob::finished, this, &LycheeProvider::handleFinishedImageRequest);
}

void LycheeProvider::handleFinishedImageRequest(KJob *job)
{
    KIO::StoredTransferJob *requestJob = static_cast<KIO::StoredTransferJob *>(job);
    if (requestJob->error()) {
        Q_EMIT error(this);
        return;
    }

    m_image = QImage::fromData(requestJob->data());

    if (m_image.isNull()) {
        Q_EMIT error(this);
        return;
    }

    Q_EMIT finished(this);
}

K_PLUGIN_CLASS_WITH_JSON(LycheeProvider, "lycheeprovider.json")

#include "lycheeprovider.moc"
