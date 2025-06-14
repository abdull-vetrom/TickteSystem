/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-11.7.2-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: ticket_system
-- ------------------------------------------------------
-- Server version	8.0.42

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `departments`
--

DROP TABLE IF EXISTS `departments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `departments` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `departments`
--

LOCK TABLES `departments` WRITE;
/*!40000 ALTER TABLE `departments` DISABLE KEYS */;
INSERT INTO `departments` VALUES
(3,'Маркетинг'),
(4,'Отдел первой линии'),
(1,'Отдел разработки'),
(2,'Поддержка');
/*!40000 ALTER TABLE `departments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `priorities`
--

DROP TABLE IF EXISTS `priorities`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `priorities` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `priorities`
--

LOCK TABLES `priorities` WRITE;
/*!40000 ALTER TABLE `priorities` DISABLE KEYS */;
INSERT INTO `priorities` VALUES
(2,'Высокий'),
(1,'Немедленный'),
(4,'Низкий'),
(3,'Средний');
/*!40000 ALTER TABLE `priorities` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `processed_emails`
--

DROP TABLE IF EXISTS `processed_emails`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `processed_emails` (
  `id` int NOT NULL AUTO_INCREMENT,
  `uid` varchar(255) COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uid` (`uid`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `processed_emails`
--

LOCK TABLES `processed_emails` WRITE;
/*!40000 ALTER TABLE `processed_emails` DISABLE KEYS */;
INSERT INTO `processed_emails` VALUES
(22,'1'),
(23,'2'),
(24,'3'),
(25,'4'),
(26,'5'),
(27,'6');
/*!40000 ALTER TABLE `processed_emails` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `projects`
--

DROP TABLE IF EXISTS `projects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `projects` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `department_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `department_id` (`department_id`),
  CONSTRAINT `projects_ibfk_1` FOREIGN KEY (`department_id`) REFERENCES `departments` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `projects`
--

LOCK TABLES `projects` WRITE;
/*!40000 ALTER TABLE `projects` DISABLE KEYS */;
INSERT INTO `projects` VALUES
(1,'Тикет-система',1),
(7,'Ведомости',1),
(16,'123',1),
(17,'ТЕСТ',1);
/*!40000 ALTER TABLE `projects` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `statuses`
--

DROP TABLE IF EXISTS `statuses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `statuses` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `statuses`
--

LOCK TABLES `statuses` WRITE;
/*!40000 ALTER TABLE `statuses` DISABLE KEYS */;
INSERT INTO `statuses` VALUES
(3,'Завершён'),
(2,'На исполнении'),
(4,'На распределении'),
(5,'Обратная связь'),
(6,'Отложен'),
(1,'Принят в работу');
/*!40000 ALTER TABLE `statuses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ticket_files`
--

DROP TABLE IF EXISTS `ticket_files`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `ticket_files` (
  `id` int NOT NULL AUTO_INCREMENT,
  `ticket_id` int NOT NULL,
  `file_name` varchar(255) COLLATE utf8mb4_general_ci NOT NULL,
  `relative_path` text COLLATE utf8mb4_general_ci NOT NULL,
  `uploaded_at` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `ticket_id` (`ticket_id`),
  CONSTRAINT `ticket_files_ibfk_1` FOREIGN KEY (`ticket_id`) REFERENCES `tickets` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=57 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ticket_files`
--

LOCK TABLES `ticket_files` WRITE;
/*!40000 ALTER TABLE `ticket_files` DISABLE KEYS */;
INSERT INTO `ticket_files` VALUES
(27,3,'CMakeCache.txt','ticketFiles/CMakeCache.txt','2025-05-18 21:54:25'),
(28,3,'aida64.exe','ticketFiles/aida64.exe','2025-05-18 21:55:15'),
(29,3,'chrome.exe','ticketFiles/chrome.exe','2025-05-18 21:55:43'),
(30,4,'cmake_install.cmake','ticketFiles/cmake_install.cmake','2025-05-19 10:11:42'),
(31,4,'Тема 8-3 задание студентам.docx','ticketFiles/Тема 8-3 задание студентам.docx','2025-05-20 09:33:50'),
(32,13,'cmake_install.cmake','ticketFiles/cmake_install.cmake','2025-05-20 10:25:15'),
(33,13,'qtcsettings.cmake','ticketFiles/qtcsettings.cmake','2025-05-20 10:25:15'),
(34,13,'.ninja_deps','ticketFiles/.ninja_deps','2025-05-20 10:25:15'),
(35,4,'Тест 3 (Триггеры)_ просмотр попытки _ edu.gubkin.ru.pdf','ticketFiles/Тест 3 (Триггеры)_ просмотр попытки _ edu.gubkin.ru.pdf','2025-05-28 01:27:49'),
(36,4,'Тест 3 (Триггеры)_ просмотр попытки _ edu.gubkin.ru.pdf','ticketFiles/Тест 3 (Триггеры)_ просмотр попытки _ edu.gubkin.ru.pdf','2025-05-28 01:28:23'),
(37,4,'Тест 1 (PL_SQL начало, функции)_ просмотр попытки _ edu.gubkin.ru.pdf','ticketFiles/Тест 1 (PL_SQL начало, функции)_ просмотр попытки _ edu.gubkin.ru.pdf','2025-05-28 01:28:23'),
(38,4,'qtcsettings.cmake','ticketFiles/qtcsettings.cmake','2025-05-28 01:30:43'),
(39,4,'CMakeCache.txt','ticketFiles/CMakeCache.txt','2025-05-28 01:30:56'),
(40,4,'.ninja_log','ticketFiles/.ninja_log','2025-05-28 01:31:17'),
(41,4,'.ninja_deps','ticketFiles/.ninja_deps','2025-05-28 01:31:17'),
(42,4,'Абдуллин_ТР_ЛР1_КС-22-03_СЯиТП.pdf','ticketFiles/Абдуллин_ТР_ЛР1_КС-22-03_СЯиТП.pdf','2025-05-28 01:31:17'),
(43,4,'Абдуллин_ТР_КС-22-03_СЯиТП_Презентация.pptx','ticketFiles/Абдуллин_ТР_КС-22-03_СЯиТП_Презентация.pptx','2025-05-28 01:31:17'),
(44,18,'Абдуллин_ТР_ЛР2_КС-22-03_СЯиТП.pdf','ticketFiles/Абдуллин_ТР_ЛР2_КС-22-03_СЯиТП.pdf','2025-05-28 01:32:09'),
(45,19,'build.ninja','ticketFiles/build.ninja','2025-05-28 01:43:52'),
(46,16,'.ninja_deps','ticketFiles/.ninja_deps','2025-05-28 01:48:59'),
(47,12,'.ninja_deps','ticketFiles/.ninja_deps','2025-05-28 01:51:08'),
(48,20,'build.ninja','ticketFiles/build.ninja','2025-05-28 01:53:30'),
(56,33,'cmake_install.cmake','ticketFiles/cmake_install.cmake','2025-06-04 17:13:03');
/*!40000 ALTER TABLE `ticket_files` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ticket_history`
--

DROP TABLE IF EXISTS `ticket_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `ticket_history` (
  `id` int NOT NULL AUTO_INCREMENT,
  `ticket_id` int NOT NULL,
  `user_id` int NOT NULL,
  `field_name` varchar(50) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `old_value` text COLLATE utf8mb4_general_ci,
  `new_value` text COLLATE utf8mb4_general_ci,
  `comment` text COLLATE utf8mb4_general_ci,
  `changed_at` datetime DEFAULT CURRENT_TIMESTAMP,
  `changes_summary` text COLLATE utf8mb4_general_ci,
  PRIMARY KEY (`id`),
  KEY `ticket_id` (`ticket_id`),
  KEY `user_id` (`user_id`),
  CONSTRAINT `ticket_history_ibfk_1` FOREIGN KEY (`ticket_id`) REFERENCES `tickets` (`id`),
  CONSTRAINT `ticket_history_ibfk_2` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=64 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ticket_history`
--

LOCK TABLES `ticket_history` WRITE;
/*!40000 ALTER TABLE `ticket_history` DISABLE KEYS */;
INSERT INTO `ticket_history` VALUES
(23,4,1,NULL,NULL,NULL,'','2025-05-19 10:36:33','Параметр <b>Название</b> изменился с <i>wdqdwq</i> на <b>Жопа</b><br>Параметр <b>Статус</b> изменился с <i>На исполнении</i> на <b>Завершён</b><br>Параметр <b>Приоритет</b> изменился с <i>Немедленный</i> на <b>Высокий</b><br>Параметр <b>Наблюдатель</b> изменился с <i>Сизов Игорь Михайлович</i> на <b>Тагир Абдуллин</b>'),
(24,4,1,NULL,NULL,NULL,'','2025-05-19 10:36:44','Параметр <b>Название</b> изменился с <i>Жопа</i> на <b>Яйца</b>'),
(25,4,1,NULL,NULL,NULL,'вдладлоавопдлавопавпдшло','2025-05-19 10:37:03',NULL),
(26,4,1,NULL,NULL,NULL,'654654навпрукп54кп','2025-05-19 10:37:24','Параметр <b>Приоритет</b> изменился с <i>Высокий</i> на <b>Немедленный</b><br>Параметр <b>Наблюдатель</b> изменился с <i>Тагир Абдуллин</i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Трекер</b> изменился с <i>Разработка</i> на <b>Поддержка</b>'),
(27,4,1,NULL,NULL,NULL,'','2025-05-19 10:44:54','Параметр <b>Статус</b> изменился с <i>Завершён</i> на <b>На исполнении</b><br>Параметр <b>Приоритет</b> изменился с <i>Немедленный</i> на <b>Высокий</b><br>Параметр <b>Наблюдатель</b> изменился с <i>Сизов Игорь Михайлович</i> на <b>Тагир Абдуллин</b>'),
(34,20,1,NULL,NULL,NULL,'в.далрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявапдалрпявагрпляварплояваорплоявап','2025-05-28 00:19:00',NULL),
(35,20,1,NULL,NULL,NULL,'ывлоа рыгва рывг ышгв лгы гыв алгыва лгывр алыгвп шыгв палгывп алывг ывшн ывшпшвы шгвы плггывп нывп нВЫПлгп лпы пвып ыглвп лгывп лгыгп гыпв лжгывлг пылгп ылвгп вылгп лыгвг плвып лгыгвп лгвылгп лгывп гывп выгп ывлгп вылгп ыв пвылгп вылгп лгывгп ывлгп шгышп лгывп лгывгп лгыгвп лывп дывп ывп ыдвшп дышгвмЫШВИсЦДУШЫИ ыпв ышпд гыврмд ыдвшим ывм иы м','2025-05-28 00:22:41',NULL),
(36,4,1,NULL,NULL,NULL,'','2025-05-28 01:28:23','Параметр <b>Наблюдатель</b> изменился с <i>Тагир Абдуллин</i> на <b>Сизов Игорь Михайлович</b>'),
(37,4,1,NULL,NULL,NULL,'','2025-05-28 01:30:43','Параметр <b>Трекер</b> изменился с <i>Поддержка</i> на <b>Разработка</b><br>Файл <a href=\'qtcsettings.cmake\'>qtcsettings.cmake</a> добавлен'),
(38,4,1,NULL,NULL,NULL,'','2025-05-28 01:30:56','Файл <a href=\'CMakeCache.txt\'>CMakeCache.txt</a> добавлен'),
(39,4,1,NULL,NULL,NULL,'','2025-05-28 01:31:17','Файл <a href=\'.ninja_log\'>.ninja_log</a> добавлен<br>Файл <a href=\'.ninja_deps\'>.ninja_deps</a> добавлен<br>Файл <a href=\'Абдуллин_ТР_ЛР1_КС-22-03_СЯиТП.pdf\'>Абдуллин_ТР_ЛР1_КС-22-03_СЯиТП.pdf</a> добавлен<br>Файл <a href=\'Абдуллин_ТР_КС-22-03_СЯиТП_Презентация.pptx\'>Абдуллин_ТР_КС-22-03_СЯиТП_Презентация.pptx</a> добавлен'),
(40,18,1,NULL,NULL,NULL,'','2025-05-28 01:32:09','Файл <a href=\'Абдуллин_ТР_ЛР2_КС-22-03_СЯиТП.pdf\'>Абдуллин_ТР_ЛР2_КС-22-03_СЯиТП.pdf</a> добавлен'),
(41,18,1,NULL,NULL,NULL,'','2025-05-28 01:32:15','Параметр <b>Статус</b> изменился с <i>Завершён</i> на <b>На исполнении</b>'),
(42,19,1,NULL,NULL,NULL,'','2025-05-28 01:43:52','Файл <a href=\'build.ninja\'>build.ninja</a> добавлен'),
(43,16,1,NULL,NULL,NULL,'','2025-05-28 01:48:59','Файл <a href=\'.ninja_deps\'>.ninja_deps</a> добавлен'),
(44,12,1,NULL,NULL,NULL,'','2025-05-28 01:51:08','Файл <a href=\'.ninja_deps\'>.ninja_deps</a> добавлен'),
(45,20,1,NULL,NULL,NULL,'','2025-05-28 01:53:31','Файл <a href=\'build.ninja\'>build.ninja</a> добавлен'),
(46,27,1,NULL,NULL,NULL,'','2025-05-29 00:57:38','Параметр <b>Статус</b> изменился с <i>Отложен</i> на <b>Принят в работу</b>'),
(47,27,1,NULL,NULL,NULL,'','2025-05-29 01:08:52','Параметр <b>Статус</b> изменился с <i>Принят в работу</i> на <b>Отложен</b>'),
(48,23,1,NULL,NULL,NULL,'','2025-06-01 11:18:45','Параметр <b>Назначена</b> изменился с <i>Тагир Абдуллин</i> на <b>Рабович Раб</b>'),
(49,23,1,NULL,NULL,NULL,'','2025-06-01 11:19:12','Параметр <b>Наблюдатель</b> изменился с <i>Тагир Абдуллин</i> на <b>Сизов Игорь Михайлович</b>'),
(55,13,1,NULL,NULL,NULL,'','2025-06-03 00:45:06','Параметр <b>Статус</b> изменился с <i>Обратная связь</i> на <b>Завершён</b>'),
(56,27,1,NULL,NULL,NULL,'','2025-06-03 00:45:17','Параметр <b>Статус</b> изменился с <i>Отложен</i> на <b>Завершён</b>'),
(57,26,1,NULL,NULL,NULL,'','2025-06-03 00:49:38','Параметр <b>Назначена</b> изменился с <i>Абд Тагир </i> на <b>1 1 1</b>'),
(58,26,10,NULL,NULL,NULL,'','2025-06-03 00:49:58','Параметр <b>Статус</b> изменился с <i>На распределении</i> на <b>Завершён</b>'),
(59,55,11,NULL,NULL,NULL,'','2025-06-04 23:42:26','Параметр <b>Статус</b> изменился с <i>На распределении</i> на <b>Обратная связь</b><br>Параметр <b>Приоритет</b> изменился с <i></i> на <b>Высокий</b><br>Параметр <b>Назначена</b> изменился с <i>распр2 распр распр3</i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Наблюдатель</b> изменился с <i></i> на <b>Рабович Раб</b><br>Параметр <b>Трекер</b> изменился с <i></i> на <b>Ошибка</b>'),
(60,22,1,NULL,NULL,NULL,'','2025-06-10 17:15:43','Параметр <b>Статус</b> изменился с <i>На исполнении</i> на <b>Завершён</b>'),
(61,50,11,NULL,NULL,NULL,'','2025-06-10 18:01:56','Параметр <b>Статус</b> изменился с <i>На распределении</i> на <b>Завершён</b>'),
(62,52,11,NULL,NULL,NULL,'','2025-06-10 18:36:53','Параметр <b>Статус</b> изменился с <i>На распределении</i> на <b>На исполнении</b><br>Параметр <b>Приоритет</b> изменился с <i></i> на <b>Высокий</b><br>Параметр <b>Назначена</b> изменился с <i>распр2 распр распр3</i> на <b>Абдулл Тагир Ренатович</b><br>Параметр <b>Наблюдатель</b> изменился с <i></i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Трекер</b> изменился с <i></i> на <b>Ошибка</b>'),
(63,53,11,NULL,NULL,NULL,'','2025-06-10 18:37:25','Параметр <b>Статус</b> изменился с <i>На распределении</i> на <b>На исполнении</b><br>Параметр <b>Приоритет</b> изменился с <i></i> на <b>Высокий</b><br>Параметр <b>Назначена</b> изменился с <i>распр2 распр распр3</i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Наблюдатель</b> изменился с <i></i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Трекер</b> изменился с <i></i> на <b>Ошибка</b>');
/*!40000 ALTER TABLE `ticket_history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tickets`
--

DROP TABLE IF EXISTS `tickets`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `tickets` (
  `id` int NOT NULL AUTO_INCREMENT,
  `title` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `description` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci,
  `project_id` int DEFAULT NULL,
  `tracker_id` int DEFAULT NULL,
  `status_id` int NOT NULL,
  `priority_id` int DEFAULT NULL,
  `assignee_id` int NOT NULL,
  `watcher_id` int DEFAULT NULL,
  `creator_id` int NOT NULL,
  `start_date` date DEFAULT NULL,
  `attachment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL,
  `created_at` datetime DEFAULT CURRENT_TIMESTAMP,
  `updated_at` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `project_id` (`project_id`),
  KEY `tracker_id` (`tracker_id`),
  KEY `status_id` (`status_id`),
  KEY `priority_id` (`priority_id`),
  KEY `assignee_id` (`assignee_id`),
  KEY `watcher_id` (`watcher_id`),
  KEY `creator_id` (`creator_id`),
  CONSTRAINT `tickets_ibfk_1` FOREIGN KEY (`project_id`) REFERENCES `projects` (`id`) ON DELETE CASCADE,
  CONSTRAINT `tickets_ibfk_2` FOREIGN KEY (`tracker_id`) REFERENCES `trackers` (`id`),
  CONSTRAINT `tickets_ibfk_3` FOREIGN KEY (`status_id`) REFERENCES `statuses` (`id`),
  CONSTRAINT `tickets_ibfk_4` FOREIGN KEY (`priority_id`) REFERENCES `priorities` (`id`),
  CONSTRAINT `tickets_ibfk_5` FOREIGN KEY (`assignee_id`) REFERENCES `users` (`id`),
  CONSTRAINT `tickets_ibfk_6` FOREIGN KEY (`watcher_id`) REFERENCES `users` (`id`),
  CONSTRAINT `tickets_ibfk_7` FOREIGN KEY (`creator_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=56 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tickets`
--

LOCK TABLES `tickets` WRITE;
/*!40000 ALTER TABLE `tickets` DISABLE KEYS */;
INSERT INTO `tickets` VALUES
(1,'8888','123',1,1,2,1,2,2,1,'2025-05-10',NULL,'2025-05-10 13:15:42','2025-05-18 16:34:11'),
(2,'00000000','123',1,1,6,2,2,2,1,'2025-05-10','.ninja_log;fstec_certificate_mp_vm_a6e42d1d6e.pdf;КР_ПАСЗИ_Абдуллин_Т_Р_КС_22_03.pdf;Курсовая ПАСЗИ.docx;TicketSystem.exe;CMakeLists.txt;QT Expert PRO - Таблица тикетов с сеткой.pdf','2025-05-10 13:18:16','2025-05-18 20:45:55'),
(3,'666','ывавыававававава',1,2,1,2,2,2,1,'2025-05-10',NULL,'2025-05-10 13:20:44','2025-05-19 10:03:58'),
(4,'Яйца','wqdqwdw',7,1,2,2,1,2,1,'2025-05-18',NULL,'2025-05-18 05:00:43','2025-05-28 01:30:43'),
(9,'вавав','',7,3,3,1,1,1,1,'2025-05-20',NULL,'2025-05-20 00:29:30','2025-05-20 00:29:30'),
(10,'ывыв','',7,3,3,2,1,1,1,'2025-05-20','C:/Users/Hp/Documents/GitHub/BMPZ/study/ВУЦ/2 семестр пеныч/penych.docx','2025-05-20 09:34:41','2025-05-20 09:34:41'),
(11,'6666666666','',7,3,3,2,1,1,1,'2025-05-20','C:/Users/Hp/Documents/GitHub/BMPZ/study/ВУЦ/2 семестр пеныч/Тема 9-1 задание студентам.docx','2025-05-20 09:34:52','2025-05-20 09:34:52'),
(12,'6666','',7,3,3,3,1,1,1,'2025-05-20',NULL,'2025-05-20 09:55:34','2025-05-20 09:55:34'),
(13,'000','',7,3,3,2,1,1,1,'2025-05-20',NULL,'2025-05-20 10:25:15','2025-06-03 00:45:06'),
(15,'1','',7,3,3,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:14','2025-05-20 12:08:14'),
(16,'1','',7,3,3,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:16','2025-05-20 12:08:16'),
(17,'1','',7,3,3,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:19','2025-05-20 12:08:19'),
(18,'1','',7,3,2,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:23','2025-05-28 01:32:15'),
(19,'1','',7,3,2,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:41','2025-05-20 12:08:41'),
(20,'2','',7,3,2,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:51','2025-05-20 12:08:51'),
(21,'фывфы','',7,3,2,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:21:16','2025-05-28 20:21:16'),
(22,'ывывыв','',7,3,3,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:21:25','2025-06-10 17:15:43'),
(23,'апапап','',7,3,5,2,4,2,1,'2025-05-28',NULL,'2025-05-28 20:21:32','2025-06-01 11:19:12'),
(24,'впапаап','',7,3,3,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:21:42','2025-05-28 20:21:42'),
(25,'валпождяпшвяаорпврапждловрапжлорвяалжорпвяжлоарпжловарпловаярплояврапжлоравяплоп','',7,3,3,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:32:45','2025-05-28 20:32:45'),
(26,'ghgh','',7,3,3,2,10,1,1,'2025-05-29',NULL,'2025-05-29 00:38:58','2025-06-03 00:49:58'),
(27,'ghhgh','',7,3,3,2,1,1,1,'2025-05-29',NULL,'2025-05-29 00:57:14','2025-06-03 00:45:17'),
(29,'1','',16,3,3,2,1,1,1,'2025-06-01',NULL,'2025-06-01 17:02:27','2025-06-01 17:02:27'),
(30,'888','',16,3,3,2,1,1,1,'2025-06-01',NULL,'2025-06-01 17:15:33','2025-06-01 17:15:33'),
(31,'dfdef #macan','',16,3,2,2,1,1,1,'2025-06-03',NULL,'2025-06-03 01:21:50','2025-06-03 01:21:50'),
(32,'123 #123','',16,3,2,2,1,1,1,'2025-06-03',NULL,'2025-06-03 19:18:24','2025-06-03 19:18:24'),
(33,'неенгенгене','апрапапрапрапраа',16,1,5,1,1,1,1,'2025-06-04',NULL,'2025-06-04 17:13:03','2025-06-04 17:13:03'),
(50,'Первое письмо на почте','Отправитель: welcome@e.mail.ru\n\nКак любимая конфета — сразу хочется открыть\r\n\r\nЛого: https://mail.ru/?utm_source=gmailer_mkt&utm_medium=email&utm_campaign=welcome_email_new_1&utm_term=logo_1\r\n\r\nЭто сервисы для повседневных задач. Расскажем про Почту, Облако, Календарь и Заметки в четырёх письмах. Это первое — с чего начать\r\n \r\nписьма из всех сервисов — в Почте\r\nСоберите всё из Gmail, Яндекса и других ящиков Mail, чтобы не переключаться между приложениями\r\nСобрать письма: https://e.mail.ru/settings/collector/?utm_source=gmailer_mkt&utm_medium=email&utm_campaign=welcome_email_new_1 \r\n  \r\nвкладки — по порядку\r\nЭто страница в Mail, где живут новости, погода и другая информация. Её можно настроить: поменять местами разделы новостей и виджетыРасставьте сервисы в приложении так, чтобы точно было удобно\r\n \r\nСобрать свою Главную: https://mail.ru/?settings=1&utm_source=gmailer_mkt&utm_medium=email&utm_campaign=welcome_email_new_1Расставить вкладки: https://mail.ru/?settings=1&utm_source=gmailer_mkt&utm_medium=email&utm_campaign=welcome_email_new_1 \r\n \r\n  \r\nудобный вход с VK ID\r\nС технологией VK ID можно войти в Почту, Облако и другие сервисы Mail по QR-коду, отпечатку, номеру телефона и коду\r\nНастроить вход с VK ID: https://id.vk.com/account/#/security \r\n \r\nа ещё — подписка Mail Space\r\nБез неё в Облаке 8 ГБ, а с ней 128 ГБ или больше. И рекламы совсем нет, и файлы большие можно загружать \r\nПопробовать за 1 ₽: https://cloud.mail.ru/promo/quota/?action=request-payment&amp%3BproductId=W128G1m_welcome_2022_single_quota_cloud&utm_campaign=welcome_email_new_1 \r\n30 дней за 1 ₽, далее — 149 ₽ в месяц\r\n \r\nВсё, что нужно: Почта, Облако, Календарь и Заметки — в одном приложении   \r\n  \r\nРассказываем полезное, команда Mail\r\nСледите за нашими новостями в блоге Mail: https://blog.mail.ru/?utm_source=gmailer_mkt&utm_medium=email&utm_campaign=welcome_email_new_1 и социальных сетях\r\nВК: https://vk.com/mailru : https://ok.ru/emailru Скачайте и установите приложение Mail \r\nОК: https://trk.mail.ru/c/ohhqm9  : https://trk.mail.ru/c/ihohko7  : https://trk.mail.ru/c/ihohko7   \r\n\r\nВы получили это письмо, потому что являетесь пользователем сервиса Mail на основании пользовательского соглашения: https://help.mail.ru/legal/terms/mail/ua/?utm_source=gmailer_mkt&utm_medium=email&utm_campaign=welcome_email_new_1\r\n \r\nОтписаться: https://e.mail.ru/mailer/subscriptions?unsubscribe_jwt_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJsZXR0ZXJfaWQiOjI3MzcyLCJ0ZXN0aW5nIjowLCJwb3N0X3R5cGUiOiJDIiwiZW1haWwiOiJ0aWNrZXRfc3lzdGVtQG1haWwucnUiLCJwb3N0X2lkIjoyMjQsInNlbmRfdXVpZCI6ImJhNDM1OWVjLTkxOGYtNGMzOS04NTZkLWIwN2RkMmU1MmYyZCIsImxhbmd1YWdlIjoicnUifQ.xe5vG0VWysgD0WMPGF2Lkdt3zPSf8xgGJWQPnsdwj98     Служба поддержки: https://help.mail.ru/mail/?utm_source=trigger&utm_medium=email&utm_campaign=welcome1\r\n \r\nЛого: https://mail.ru/?utm_source=gmailer_mkt&utm_medium=email&utm_campaign=welcome_email_new_1&utm_term=logo_2',NULL,NULL,3,NULL,11,NULL,11,'2025-06-04',NULL,'2025-06-04 20:37:47','2025-06-10 18:01:56'),
(51,'Ansjja','Отправитель: goga.sizov.04@mail.ru\n\n\n\n\nDbdhdbbdhddhhd\n\nОтправлено из мобильной Почты Mail\n',NULL,NULL,4,NULL,11,NULL,11,'2025-06-04',NULL,'2025-06-04 20:37:47','2025-06-04 23:37:47'),
(52,'Вход с нового устройства в аккаунт','Отправитель: security@id.mail.ru\n\nВход с нового устройства в аккаунт\r\n\r\nЕсли вы этого не делали, измените пароль, чтобы обезопасить аккаунт. \r\nИзменить пароль: https://account.mail.ru/security/password?open-change-password=1&utm_medium=ltr\r\n\r\n\r\nВремя: 4 июня, 11:22\r\nУстройство:  Microsoft Windows 10, Thunderbird, Москва, Россия \r\nСписок устройств: https://account.mail.ru/user/garage?utm_medium=ltr\r\n\r\nУзнайте, как защитить аккаунт, на нашем сайте по безопасности: https://security.mail.ru/\r\n\r\n ---\r\n\r\nС наилучшими пожеланиями, команда Почты Mail.ru \r\n \r\nВы получили это письмо, потому что являетесь пользователем Mail на основании Пользовательского соглашения: https://help.mail.ru/legal/terms/mail\r\n\r\nCopyright 2025 VK, Москва — Все права защищены. \r\n\r\nСлужба поддержки: https://help.mail.ru/\r\nMail ID: https://id.mail.ru/\r\n\r\n[@mail]',NULL,3,2,2,1,2,11,'2025-06-04',NULL,'2025-06-04 20:37:47','2025-06-10 18:36:53'),
(53,'Апр','Отправитель: goga.sizov.04@mail.ru\n\n\n\nПлалалаьаььаьа\n\n\nОтправлено из мобильной Почты Mail\n',NULL,3,2,2,2,2,11,'2025-06-04',NULL,'2025-06-04 20:37:47','2025-06-10 18:37:25'),
(54,'Бултых','Отправитель: nevelsonn@gmail.com\n\nРабочая система\r\n\r\n',NULL,NULL,4,NULL,11,NULL,11,'2025-06-04',NULL,'2025-06-04 20:37:47','2025-06-04 23:37:47'),
(55,'Задание','Отправитель: dstreltsov98@gmail.com\n\nНужно разослать всем выговор и снять 300 баллов рейтинга\r\n',NULL,3,5,2,2,4,11,'2025-06-04',NULL,'2025-06-04 20:37:47','2025-06-04 23:42:26');
/*!40000 ALTER TABLE `tickets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trackers`
--

DROP TABLE IF EXISTS `trackers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `trackers` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trackers`
--

LOCK TABLES `trackers` WRITE;
/*!40000 ALTER TABLE `trackers` DISABLE KEYS */;
INSERT INTO `trackers` VALUES
(3,'Ошибка'),
(2,'Поддержка'),
(1,'Разработка');
/*!40000 ALTER TABLE `trackers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id` int NOT NULL AUTO_INCREMENT,
  `first_name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `middle_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL,
  `last_name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `password` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `role` enum('распределитель','начальник','работник') CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `department_id` int NOT NULL,
  `full_name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL,
  `photo_path` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `email` (`email`),
  KEY `department_id` (`department_id`),
  CONSTRAINT `users_ibfk_1` FOREIGN KEY (`department_id`) REFERENCES `departments` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES
(1,'Тагир','Ренатович','Абдулл','123','a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3','начальник',1,'Абдулл Тагир Ренатович','photos/user_1.png'),
(2,'Игорь','Сизов','Михайлович','@qwert','1411242b2139f9fa57a802e1dc172e3e1ca7655ac2d06d83b22958951072261b','начальник',1,'Сизов Игорь Михайлович',NULL),
(3,'5545454','545454','545454','8899','9800a8677d99e5f6968d7357e44006388b09d3b6a8676d0f930fbaa63d02330d','распределитель',4,'545454 5545454 545454',NULL),
(4,'Раб',NULL,'Рабович','11','4fc82b26aecb47d2868c4efbe3581732a3e7cbcc6c2efb32062c08170a05eeb8','работник',1,'Рабович Раб','photos/user_4.png'),
(6,'владимир','владимирович','павловский','@lol','8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92','распределитель',4,'павловский владимир владимирович',NULL),
(7,'амр','амр','амр','@fgrtg','99f11d0264b3d072974cbbf6964b6fd2cf9e8d0f7a02f1a3ce5e39a8c083888b','распределитель',4,'амр амр амр',NULL),
(10,'1','1','1','@123','96cae35ce8a9b0244178bf28e4966c2ce1b8385723a96a6b838858cdd6ca0a1e','работник',1,'1 1 1',NULL),
(11,'распр','распр3','распр2','@1233','932f3c1b56257ce8539ac269d7aab42550dacf8818d075f0bdf1990562aae3ef','распределитель',4,'распр2 распр распр3',NULL),
(12,'Лущеко','Павлович','Евгений','@lush','8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92','распределитель',1,'Евгений Лущеко Павлович',NULL);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'ticket_system'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2025-06-14 16:00:19
