#ifndef DATASENDER_H
#define DATASENDER_H

#include "include/rapidjson/rapidjson.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/document.h"
#include "include/curl/curl.h"

#include <QString>
#include <string>
#include <vector>


class DataSender
{
private:
    std::string _url;

    size_t static WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
    {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
public:
    DataSender(std::string url): _url(url){};
    void sendData(std::vector<QString> data);
    void sendJsonToServerWithResponse(const std::string& jsonStr);
};

#endif // DATASENDER_H

//https://dunicewinners.ru/user_info/{mac}
//JSON содержит массив строк, который называется apps
//Игорь, это тебе српзу прокси ебашить мне похуй пускай степа тестит
