-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Mar 31, 2019 at 01:37 PM
-- Server version: 10.1.38-MariaDB
-- PHP Version: 7.3.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `canteen`
--

-- --------------------------------------------------------

--
-- Table structure for table `products`
--

CREATE TABLE `products` (
  `product_id` int(3) NOT NULL,
  `product_name` varchar(127) NOT NULL,
  `product_price` float NOT NULL,
  `product_quantity` int(3) NOT NULL,
  `product_type` int(1) NOT NULL,
  `product_state` int(1) NOT NULL,
  `product_start_time` int(2) NOT NULL,
  `product_end_time` int(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `products`
--

INSERT INTO `products` (`product_id`, `product_name`, `product_price`, `product_quantity`, `product_type`, `product_state`, `product_start_time`, `product_end_time`) VALUES
(3, 'Idly(2 nos.)', 30, 10, 1, 1, 7, 10),
(4, 'Vada(2 nos.)', 30, 12, 1, 1, 7, 10),
(5, 'Pongal', 40, 15, 1, 1, 8, 10),
(6, 'Upma', 30, 8, 1, 1, 7, 9),
(7, 'Puffs', 12, 20, 1, 1, 10, 12),
(8, 'Samosa', 15, 15, 1, 1, 10, 11),
(9, 'Tea cake', 14, 10, 1, 1, 10, 12),
(10, 'Milk Bikis', 10, 20, 0, 1, 7, 19),
(11, 'Veg. Biriyani', 30, 25, 1, 1, 12, 14),
(12, 'Chapathi', 30, 30, 1, 1, 12, 14),
(13, 'Poori Masala', 40, 15, 1, 1, 12, 14),
(14, 'Variety Rice', 35, 24, 1, 1, 12, 14),
(15, 'Fresh Juice', 25, 30, 1, 1, 10, 15),
(16, 'Kavins Milk Shake', 25, 50, 0, 1, 7, 19),
(17, 'Tropicana', 20, 40, 0, 1, 7, 19),
(18, 'Plain Dosa', 30, 30, 1, 1, 16, 18),
(19, 'Ghee Dosa', 40, 25, 1, 1, 16, 18),
(20, 'Masala Dosa', 45, 20, 1, 1, 16, 18),
(21, 'Chocolate Cake', 20, 13, 1, 1, 16, 18),
(22, 'Sandwich', 25, 20, 1, 1, 15, 17);

-- --------------------------------------------------------

--
-- Table structure for table `sales`
--

CREATE TABLE `sales` (
  `sale_id` int(3) NOT NULL,
  `product_id` int(3) NOT NULL,
  `product_name` varchar(55) NOT NULL,
  `customer_id` int(3) NOT NULL,
  `product_quantity` int(3) NOT NULL,
  `product_price` float NOT NULL,
  `amount_paid` float NOT NULL,
  `order_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sales`
--

INSERT INTO `sales` (`sale_id`, `product_id`, `product_name`, `customer_id`, `product_quantity`, `product_price`, `amount_paid`, `order_date`) VALUES
(2, 2, 'Burger', 13, 6, 50, 300, '2000-03-12'),
(3, 2, 'Burger', 13, 1, 50, 50, '2000-03-12'),
(4, 2, 'Burger', 13, 3, 50, 150, '2000-07-26'),
(5, 2, 'Burger', 13, 3, 50, 150, '2003-07-23');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `user_id` int(3) NOT NULL,
  `user_name` varchar(255) NOT NULL,
  `user_password` varchar(255) NOT NULL,
  `user_type` int(1) NOT NULL,
  `user_first_name` varchar(31) NOT NULL,
  `user_last_name` varchar(31) NOT NULL,
  `user_age` int(3) NOT NULL,
  `user_address` varchar(127) NOT NULL,
  `user_wallet_balance` int(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`user_id`, `user_name`, `user_password`, `user_type`, `user_first_name`, `user_last_name`, `user_age`, `user_address`, `user_wallet_balance`) VALUES
(10, 'administrator', 'password', 0, 'Administrator', 'Admin', 18, '5th Avenue', 0),
(14, 'arjun', 'password', 1, 'Arjun', 'Ashok', 18, 'ABCD Ramnagar', 100),
(15, 'baalavignesh', 'password', 1, 'Baalavignesh', 'A', 18, 'ZXCVBNM', 100),
(16, 'rajesh', 'cplusplus', 1, 'Rajesh', 'Guru', 23, 'Road 1, Cbe', 100);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`product_id`);

--
-- Indexes for table `sales`
--
ALTER TABLE `sales`
  ADD PRIMARY KEY (`sale_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`user_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `products`
--
ALTER TABLE `products`
  MODIFY `product_id` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT for table `sales`
--
ALTER TABLE `sales`
  MODIFY `sale_id` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `user_id` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
