#include "DataSender.h"
#include "QDebug"

using namespace rapidjson;

void DataSender::sendData(std::vector<QString> data)
{
    Document doc;
    doc.SetObject();
    Document::AllocatorType& allocator = doc.GetAllocator();

    Value apps(rapidjson::kArrayType);
    for(QString& qstr : data)
    {
        std::string str = qstr.toStdString();
        Value app(str.c_str(), allocator);
        apps.PushBack(app, allocator);
    }

    doc.AddMember("apps", apps, allocator);

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string strSend = buffer.GetString();
    sendJsonToServerWithResponse(strSend);

}

void DataSender::sendJsonToServerWithResponse(const std::string& jsonStr)
{
    if(_url == "") throw QString("URL NOT DECLARED!!!");
    qDebug() << "JSON: " << jsonStr + "   URL: " + _url;
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        std::string responseString;

        //Отрубаем нахер поддержку сертификата, так как у нас большие потные яйца
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(nullptr, "Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());

        // Установка callback для записи ответа
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataSender::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) throw QString("Server send not OK");
        else qDebug() << "Server send OK";

        curl_easy_cleanup(curl);
    }
}

