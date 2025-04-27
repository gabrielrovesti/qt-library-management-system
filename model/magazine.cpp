#include "magazine.h"
#include "../visitor/mediavisitor.h"

Magazine::Magazine(int id, const QString &title, const QDate &releaseDate,
                 const QString &publisher, const QString &description,
                 const QString &coverPath, const QString &issue,
                 int volume, int issueNumber, const QString &topic)
    : AbstractMedia(id, title, releaseDate, publisher, description, coverPath),
      issue(issue), volume(volume), issueNumber(issueNumber), topic(topic) {
}

QString Magazine::getIssue() const {
    return issue;
}

int Magazine::getVolume() const {
    return volume;
}

int Magazine::getIssueNumber() const {
    return issueNumber;
}

QString Magazine::getTopic() const {
    return topic;
}

void Magazine::setIssue(const QString &issue) {
    this->issue = issue;
}

void Magazine::setVolume(int volume) {
    this->volume = volume;
}

void Magazine::setIssueNumber(int issueNumber) {
    this->issueNumber = issueNumber;
}

void Magazine::setTopic(const QString &topic) {
    this->topic = topic;
}

QString Magazine::getMediaType() const {
    return "Magazine";
}

void Magazine::accept(MediaVisitor &visitor) {
    visitor.visit(*this);
}

QJsonObject Magazine::toJson() const {
    QJsonObject json = AbstractMedia::toJson();
    json["type"] = "Magazine";
    json["issue"] = issue;
    json["volume"] = volume;
    json["issueNumber"] = issueNumber;
    json["topic"] = topic;
    return json;
}

Magazine* Magazine::fromJson(const QJsonObject &json) {
    if (json["type"].toString() != "Magazine") {
        return nullptr;
    }
    
    return new Magazine(
        json["id"].toInt(),
        json["title"].toString(),
        QDate::fromString(json["releaseDate"].toString(), Qt::ISODate),
        json["publisher"].toString(),
        json["description"].toString(),
        json["coverPath"].toString(),
        json["issue"].toString(),
        json["volume"].toInt(),
        json["issueNumber"].toInt(),
        json["topic"].toString()
    );
}