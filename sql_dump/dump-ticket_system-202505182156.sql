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
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `projects`
--

LOCK TABLES `projects` WRITE;
/*!40000 ALTER TABLE `projects` DISABLE KEYS */;
INSERT INTO `projects` VALUES
(1,'Тикет-система',1),
(4,'привет',1),
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
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ticket_files`
--

LOCK TABLES `ticket_files` WRITE;
/*!40000 ALTER TABLE `ticket_files` DISABLE KEYS */;
INSERT INTO `ticket_files` VALUES
(27,3,'CMakeCache.txt','ticketFiles/CMakeCache.txt','2025-05-18 21:54:25'),
(28,3,'aida64.exe','ticketFiles/aida64.exe','2025-05-18 21:55:15'),
(29,3,'chrome.exe','ticketFiles/chrome.exe','2025-05-18 21:55:43');
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
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ticket_history`
--

LOCK TABLES `ticket_history` WRITE;
/*!40000 ALTER TABLE `ticket_history` DISABLE KEYS */;
INSERT INTO `ticket_history` VALUES
(12,2,1,NULL,NULL,NULL,'fvdfgdfgdfgdfgdfgdfg','2025-05-18 17:41:37','Параметр <b>Название</b> изменился с <i>66767</i> на <b>7878</b><br>Параметр <b>Статус</b> изменился с <i>На исполнении</i> на <b>Завершён</b><br>Параметр <b>Приоритет</b> изменился с <i>Высокий</i> на <b>Немедленный</b><br>Параметр <b>Назначена</b> изменился с <i>Сизов Игорь Михайлович</i> на <b>Тагир Абдуллин</b><br>Параметр <b>Наблюдатель</b> изменился с <i>Тагир Абдуллин</i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Трекер</b> изменился с <i>Ошибка</i> на <b>Разработка</b>'),
(13,2,1,NULL,NULL,NULL,'Ебать, пиздато так-то получается','2025-05-18 17:42:08','Параметр <b>Название</b> изменился с <i>7878</i> на <b>00000000</b><br>Параметр <b>Статус</b> изменился с <i>Завершён</i> на <b>На исполнении</b><br>Параметр <b>Приоритет</b> изменился с <i>Немедленный</i> на <b>Низкий</b><br>Параметр <b>Назначена</b> изменился с <i>Тагир Абдуллин</i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Наблюдатель</b> изменился с <i>Сизов Игорь Михайлович</i> на <b>Тагир Абдуллин</b><br>Параметр <b>Трекер</b> изменился с <i>Разработка</i> на <b>Ошибка</b>'),
(14,2,1,NULL,NULL,NULL,'','2025-05-18 17:42:41','Параметр <b>Приоритет</b> изменился с <i>Низкий</i> на <b>Высокий</b>'),
(15,2,1,NULL,NULL,NULL,'','2025-05-18 19:59:01','Параметр <b>Трекер</b> изменился с <i>Ошибка</i> на <b>Поддержка</b>'),
(16,2,1,NULL,NULL,NULL,'','2025-05-18 20:29:37','Параметр <b>Трекер</b> изменился с <i>Поддержка</i> на <b>Разработка</b>'),
(17,2,1,NULL,NULL,NULL,'','2025-05-18 20:45:55','Параметр <b>Статус</b> изменился с <i>На исполнении</i> на <b>Отложен</b><br>Параметр <b>Наблюдатель</b> изменился с <i>Тагир Абдуллин</i> на <b>Сизов Игорь Михайлович</b>'),
(18,3,1,NULL,NULL,NULL,'','2025-05-18 21:55:43','Параметр <b>Название</b> изменился с <i>цуаываываыва</i> на <b>fdgdfgfg</b><br>Параметр <b>Статус</b> изменился с <i>Завершён</i> на <b>На исполнении</b><br>Параметр <b>Приоритет</b> изменился с <i>Высокий</i> на <b>Немедленный</b><br>Параметр <b>Наблюдатель</b> изменился с <i>Тагир Абдуллин</i> на <b>Сизов Игорь Михайлович</b><br>Параметр <b>Трекер</b> изменился с <i>Ошибка</i> на <b>Поддержка</b>');
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
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tickets`
--

LOCK TABLES `tickets` WRITE;
/*!40000 ALTER TABLE `tickets` DISABLE KEYS */;
INSERT INTO `tickets` VALUES
(1,'8888','123',1,1,2,1,2,2,1,'2025-05-10',NULL,'2025-05-10 13:15:42','2025-05-18 16:34:11'),
(2,'00000000','123',1,1,6,2,2,2,1,'2025-05-10','.ninja_log;fstec_certificate_mp_vm_a6e42d1d6e.pdf;КР_ПАСЗИ_Абдуллин_Т_Р_КС_22_03.pdf;Курсовая ПАСЗИ.docx;TicketSystem.exe;CMakeLists.txt;QT Expert PRO - Таблица тикетов с сеткой.pdf','2025-05-10 13:18:16','2025-05-18 20:45:55'),
(3,'fdgdfgfg','ывавыававававава',1,2,2,1,1,2,1,'2025-05-10',NULL,'2025-05-10 13:20:44','2025-05-18 21:55:43'),
(4,'wdqdwq','wqdqwdw',7,3,4,2,1,1,1,'2025-05-18',NULL,'2025-05-18 05:00:43','2025-05-18 15:26:32');
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
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES
(1,'Тагир','Ренатович','Абдуллин','123','123','начальник',1,'Тагир Абдуллин','photos/user_1.png'),
(2,'Игорь','Сизов','Михайлович','6','6','начальник',1,'Сизов Игорь Михайлович',NULL);
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

-- Dump completed on 2025-05-18 21:56:29
