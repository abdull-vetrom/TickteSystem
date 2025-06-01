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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `departments`
--

LOCK TABLES `departments` WRITE;
/*!40000 ALTER TABLE `departments` DISABLE KEYS */;
INSERT INTO `departments` VALUES
(3,'Маркетинг'),
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
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `projects`
--

LOCK TABLES `projects` WRITE;
/*!40000 ALTER TABLE `projects` DISABLE KEYS */;
INSERT INTO `projects` VALUES
(1,'Тикет-система',1),
(7,'Ведомости',1);
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
) ENGINE=InnoDB AUTO_INCREMENT=49 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
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
(48,20,'build.ninja','ticketFiles/build.ninja','2025-05-28 01:53:30');
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
) ENGINE=InnoDB AUTO_INCREMENT=48 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
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
(47,27,1,NULL,NULL,NULL,'','2025-05-29 01:08:52','Параметр <b>Статус</b> изменился с <i>Принят в работу</i> на <b>Отложен</b>');
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
  `project_id` int NOT NULL,
  `tracker_id` int NOT NULL,
  `status_id` int NOT NULL,
  `priority_id` int NOT NULL,
  `assignee_id` int NOT NULL,
  `watcher_id` int NOT NULL,
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
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
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
(13,'000','',7,3,5,2,1,1,1,'2025-05-20',NULL,'2025-05-20 10:25:15','2025-05-20 10:25:15'),
(15,'1','',7,3,3,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:14','2025-05-20 12:08:14'),
(16,'1','',7,3,3,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:16','2025-05-20 12:08:16'),
(17,'1','',7,3,3,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:19','2025-05-20 12:08:19'),
(18,'1','',7,3,2,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:23','2025-05-28 01:32:15'),
(19,'1','',7,3,2,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:41','2025-05-20 12:08:41'),
(20,'2','',7,3,2,2,1,1,1,'2025-05-20',NULL,'2025-05-20 12:08:51','2025-05-20 12:08:51'),
(21,'фывфы','',7,3,2,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:21:16','2025-05-28 20:21:16'),
(22,'ывывыв','',7,3,2,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:21:25','2025-05-28 20:21:25'),
(23,'апапап','',7,3,5,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:21:32','2025-05-28 20:21:32'),
(24,'впапаап','',7,3,3,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:21:42','2025-05-28 20:21:42'),
(25,'валпождяпшвяаорпврапждловрапжлорвяалжорпвяжлоарпжловарпловаярплояврапжлоравяплоп','',7,3,3,2,1,1,1,'2025-05-28',NULL,'2025-05-28 20:32:45','2025-05-28 20:32:45'),
(26,'ghgh','',7,3,4,2,1,1,1,'2025-05-29',NULL,'2025-05-29 00:38:58','2025-05-29 00:38:58'),
(27,'ghhgh','',7,3,6,2,1,1,1,'2025-05-29',NULL,'2025-05-29 00:57:14','2025-05-29 01:08:52');
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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES
(1,'Тагир','Ренатович','Абдуллин','123','123','начальник',1,'Тагир Абдуллин','photos/user_1.png'),
(2,'Игорь','Сизов','Михайлович','6','6','начальник',1,'Сизов Игорь Михайлович',NULL),
(3,'5545454','545454','545454','8899','8899','распределитель',1,'545454 5545454 545454',NULL);
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

-- Dump completed on 2025-06-01  0:08:54
