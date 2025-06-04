#include <iostream>
#include <vmime/vmime.hpp>
#include <vmime/platforms/windows/windowsHandler.hpp>
#include <vmime/utility/outputStreamStringAdapter.hpp>
#include <vmime/text.hpp>
#include <vmime/charsetConverter.hpp>
#include <memory>
#include <QDebug>
#include <QString>
#include "mycertverifier.h"
#include <vmime/text.hpp>
#include <vmime/charsetConverter.hpp>
#include <memory>         // std::dynamic_pointer_cast
#include <QString>

void testMail()
{
    try {
        // Установка обработчика для Windows
        vmime::platform::setHandler<vmime::platforms::windows::windowsHandler>();

        // Создание сессии
        vmime::shared_ptr<vmime::net::session> session = vmime::net::session::create();

        // Настройка параметров подключения
        vmime::utility::url url("imaps://imap.mail.ru:993");

        // Учетные данные
        const std::string username = "ticket_system@mail.ru";
        const std::string password = "uKRATnFXaiGAfo81kbcV";

        // Получение хранилища
        vmime::shared_ptr<vmime::net::store> store = session->getStore(url);

        // Установка учетных данных
        store->setProperty("auth.username", username);
        store->setProperty("auth.password", password);

        // Отключение проверки сертификатов
        store->setProperty("connection.tls", true);
        store->setProperty("connection.tls.required", true);
        store->setProperty("connection.tls.verification", true);

        // Подключение к серверу
        auto verifier = std::make_shared<myCertVerifier>("C:/msys64/home/Hp/certs/cert.pem");
        store->setCertificateVerifier(verifier);
        store->connect();

        // Получение папки
        vmime::shared_ptr<vmime::net::folder> folder = store->getFolder(vmime::net::folder::path("INBOX"));
        folder->open(vmime::net::folder::MODE_READ_ONLY);

        // Получение количества сообщений
        // Получаем общее количество сообщений
        const int count = folder->getMessageCount();
        std::cout << "Всего сообщений: " << count << std::endl;

        if (count > 0) {
            const int messagesToFetch = std::min(count, 5);

            // Получаем список сообщений
            vmime::net::messageSet mset = vmime::net::messageSet::byNumber(1, messagesToFetch);
            std::vector<vmime::shared_ptr<vmime::net::message>> messages = folder->getMessages(mset);

            // Указываем, что загружаем только заголовки
            vmime::net::fetchAttributes attrs;
            attrs.add(vmime::net::fetchAttributes::ENVELOPE);

            // Загружаем указанные данные
            folder->fetchMessages(messages, attrs);

            for (size_t i = 0; i < messages.size(); ++i) {
                try {
                    vmime::shared_ptr<vmime::net::message> msg = messages[i];
                    vmime::shared_ptr<const vmime::header> hdr = msg->getHeader();
                    vmime::shared_ptr<const vmime::headerField> subj = hdr->findField("Subject");

                    if (subj) {
                        vmime::shared_ptr<const vmime::headerFieldValue> value = subj->getValue();
                        std::shared_ptr<const vmime::text> txt = std::dynamic_pointer_cast<const vmime::text>(value);

                        if (txt) {
                            QString decoded = QString::fromStdString(txt->getConvertedText(vmime::charsets::UTF_8));
                            qDebug() << (i + 1) << ". Тема:" << decoded;
                        } else {
                            qDebug() << (i + 1) << ". Тема: (не удалось декодировать)";
                        }
                    } else {
                        qDebug() << (i + 1) << ". Тема: (отсутствует)";
                    }
                } catch (const vmime::exception& e) {
                    qDebug() << "Ошибка при обработке сообщения #" << (i + 1) << ": " << e.what();
                }
            }
        }


        // Закрытие соединения
        folder->close(false);
        store->disconnect();
    }
    catch (const vmime::exception& e) {
        std::cerr << "Ошибка VMime: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }
}
