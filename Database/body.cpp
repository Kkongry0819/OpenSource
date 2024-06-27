#include <iostream>
#include <string>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/mysql_driver.h>
#include "jdbc/cppconn/prepared_statement.h"
#include<vector>
#include <sstream>

using namespace std;
using namespace sql;
bool isAdmin = false;
bool isLoggedIn = false;

struct ScheduleDetails {
	int scheduleId;
	int hallId;
	std::string hallName;
	int movieId;
	std::string movieName;
	double ticketPrice;
	std::string showTime;
	bool isValid() const { return scheduleId != 0; } // 简单判断是否有效
};
string join(const vector<string>& vec, const string& separator) {
	ostringstream oss;
	if (!vec.empty()) {
		auto it = vec.begin();
		oss << *it++;
		while (it != vec.end()) {
			oss << separator << *it++;
		}
	}
	return oss.str();
}
class DBHelper {
public:
	static Connection* createConnection() {
		mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
		return driver->connect("tcp://localhost:3306", "root", "123456");
	}

	static void closeConnection(Connection* con) {
		if (con != nullptr) {
			delete con;
		}
	}
};

class MovieManager {
public:
	static std::vector<std::pair<int, std::string>> getAllMovies(Connection* con) {
		std::vector<std::pair<int, std::string>> movies;
		try {
			PreparedStatement* pstmt = con->prepareStatement("SELECT movie_id, movie_name FROM movies");
			ResultSet* res = pstmt->executeQuery();

			while (res->next()) {
				int movieId = res->getInt("movie_id");
				std::string movieName = res->getString("movie_name");
				movies.emplace_back(movieId, movieName);
			}

			delete res;
			delete pstmt;
		}
		catch (const SQLException& e) {
			std::cerr << "Error getting all movies: " << e.what() << std::endl;
		}
		return movies;
	}

bool existsMovie(const string& title, Connection* con) {
	try {
		PreparedStatement* pstmt = con->prepareStatement("SELECT COUNT(*) FROM movies WHERE movie_name = ?");
		pstmt->setString(1, title);
		ResultSet* res = pstmt->executeQuery();
		res->next(); // 移动到结果集的第一行
		bool exists = res->getInt(1) > 0; // 检查计数是否大于0
		delete res;
		delete pstmt;
		return exists;
	}
	catch (const SQLException& e) {
		cerr << "Error checking movie existence: " << e.what() << endl;
		return false;
	}
}

bool addMovie(const string& title, const string& genre, const string& director, const string& actor, double rating, Connection* con) {
	try {

		PreparedStatement* pstmt = con->prepareStatement("INSERT INTO movies (movie_name, genre, director, actor, rating) VALUES (?, ?, ?, ?, ?)");
		pstmt->setString(1, title);
		pstmt->setString(2, genre);
		pstmt->setString(3, director);
		pstmt->setString(4, actor);
		pstmt->setDouble(5, rating);
		int rowsAffected = pstmt->executeUpdate();
		delete pstmt;

		return rowsAffected > 0;
	}
	catch (const SQLException& e) {
		cerr << "Error adding movie: " << e.what() << endl;
		return false;
	}
}

bool deleteMovie(const string& title, Connection* con) {
	try {
		PreparedStatement* pstmt = con->prepareStatement("DELETE FROM movies WHERE movie_name = ?");
		pstmt->setString(1, title);

		int rowsAffected = pstmt->executeUpdate();
		delete pstmt;

		return rowsAffected > 0;
	}
	catch (const SQLException& e) {
		cerr << "Error deleting movie: " << e.what() << endl;
		return false;
	}
}

bool updateMovie(const string& oldTitle, const string& newTitle, const string& newGenre, const string& newDirector, const string& newActor, double newRating, Connection* con) {
	try {

		vector<pair<string, string>> updatePairs;
		if (!newTitle.empty()) updatePairs.emplace_back("movie_name", newTitle);
		if (!newGenre.empty()) updatePairs.emplace_back("genre", newGenre);
		if (!newDirector.empty()) updatePairs.emplace_back("director", newDirector);
		if (!newActor.empty()) updatePairs.emplace_back("actor", newActor);
		if (newRating >= 0) updatePairs.emplace_back("rating", to_string(newRating));

		if (updatePairs.empty()) {
			cerr << "No fields provided for update.\n";
			return false;
		}

		string updateQuery = "UPDATE movies SET ";
		for (size_t i = 0; i < updatePairs.size(); ++i) {
			updateQuery += updatePairs[i].first + " = ?";
			if (i < updatePairs.size() - 1) updateQuery += ", ";
		}
		updateQuery += " WHERE movie_name = ?";


		PreparedStatement* pstmt = con->prepareStatement(updateQuery);
		for (size_t i = 0; i < updatePairs.size(); ++i) {
			if (updatePairs[i].first == "movie_name") {
				pstmt->setString(i + 1, updatePairs[i].second);
			}
			else if (updatePairs[i].first == "rating") {
				pstmt->setDouble(i + 1, stod(updatePairs[i].second));
			}
			else {
				pstmt->setString(i + 1, updatePairs[i].second);
			}
		}
		pstmt->setString(updatePairs.size() + 1, oldTitle); 

		int rowsAffected = pstmt->executeUpdate();
		delete pstmt;
		return rowsAffected > 0;
	}
	catch (const SQLException& e) {
		cerr << "Error updating movie: " << e.what() << endl;
		return false;
	}
}

void listMovies(Connection* con) {
	try {
		Statement* stmt = con->createStatement();
		ResultSet* res = stmt->executeQuery("SELECT * FROM movies");

		cout << "\n--- 电影菜单 ---\n";
		while (res->next()) {
			cout << "电影名: " << res->getString("movie_name") << ", 类型: " << res->getString("genre")
				<< ", 导演: " << res->getString("director") << ", 演员: " << res->getString("actor")
				<< ", 评分: " << res->getDouble("rating") << endl;
		}

		delete res;
		delete stmt;
	}
	catch (const SQLException& e) {
		cerr << "Error listing movies: " << e.what() << endl;
	}
}
};
class HallManager {
public:
	static std::vector<std::pair<int, std::string>> getAllHalls(Connection* con) {
		std::vector<std::pair<int, std::string>> halls;
		try {
			PreparedStatement* pstmt = con->prepareStatement("SELECT hall_id, hall_name FROM hall");
			ResultSet* res = pstmt->executeQuery();

			while (res->next()) {
				int hallId = res->getInt("hall_id");
				std::string hallName = res->getString("hall_name");
				halls.emplace_back(hallId, hallName);
			}

			delete res;
			delete pstmt;
		}
		catch (const SQLException& e) {
			std::cerr << "Error getting all halls: " << e.what() << std::endl;
		}
		return halls;
	}
	bool existsHall(const std::string& hallName, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement("SELECT COUNT(*) FROM hall WHERE hall_name = ?");
			pstmt->setString(1, hallName);
			ResultSet* res = pstmt->executeQuery();
			res->next();
			bool exists = res->getInt(1) > 0;
			delete res;
			delete pstmt;
			return exists;
		}
		catch (const SQLException& e) {
			std::cerr << "Error checking hall existence: " << e.what() << std::endl;
			return false;
		}
	}

	// 添加新的影厅
	bool addHall(const std::string& hallName, int capacity, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement("INSERT INTO hall (hall_name, capacity) VALUES (?, ?)");
			pstmt->setString(1, hallName);
			pstmt->setInt(2, capacity);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error adding hall: " << e.what() << std::endl;
			return false;
		}
	}

	// 删除影厅
	bool deleteHall(const std::string& hallName, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement("DELETE FROM hall WHERE hall_name = ?");
			pstmt->setString(1, hallName);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error deleting hall: " << e.what() << std::endl;
			return false;
		}
	}

	// 更新影厅信息
	bool updateHall(const std::string& oldHallName, const std::string& newHallName, int newCapacity, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement("UPDATE hall SET hall_name = ?, capacity = ? WHERE hall_name = ?");
			pstmt->setString(1, newHallName);
			pstmt->setInt(2, newCapacity);
			pstmt->setString(3, oldHallName);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error updating hall: " << e.what() << std::endl;
			return false;
		}
	}

	// 列出所有影厅
	void listHalls(Connection* con) {
		try {
			Statement* stmt = con->createStatement();
			ResultSet* res = stmt->executeQuery("SELECT * FROM hall");

			std::cout << "\n--- 影厅列表 ---\n";
			while (res->next()) {
				std::cout << "影厅ID: " << res->getInt("hall_id") << ", 影厅名称: " << res->getString("hall_name")
					<< ", 容量: " << res->getInt("capacity") << std::endl;
			}

			delete res;
			delete stmt;
		}
		catch (const SQLException& e) {
			std::cerr << "Error listing halls: " << e.what() << std::endl;
		}
	}
};
class ScheduleManager {
public:

	ScheduleDetails getScheduleDetails(int scheduleId, Connection* con) {
		ScheduleDetails details;
		try {
			// 使用JOIN来同时从schedules、halls和movies表中获取所需信息
			PreparedStatement* pstmt = con->prepareStatement(
				"SELECT s.schedule_id, s.hall_id, h.hall_name, s.movie_id, m.movie_name, s.ticket_price, s.show_time "
				"FROM schedule s "
				"INNER JOIN hall h ON s.hall_id = h.hall_id "
				"INNER JOIN movies m ON s.movie_id = m.movie_id "
				"WHERE s.schedule_id = ?");
			pstmt->setInt(1, scheduleId);
			ResultSet* res = pstmt->executeQuery();

			if (res->next()) {
				details.scheduleId = scheduleId;
				details.hallId = res->getInt("hall_id");
				details.hallName = res->getString("hall_name");
				details.movieId = res->getInt("movie_id");
				details.movieName = res->getString("movie_name");
				details.ticketPrice = res->getDouble("ticket_price");
				details.showTime = res->getString("show_time");
			}
			else {
				details.isValid(); // 如果未找到记录，isValid将返回false
			}

			delete res;
			delete pstmt;
		}
		catch (const SQLException& e) {
			std::cerr << "Error getting schedule details: " << e.what() << std::endl;
		}
		return details;
	}

	bool showUserTickets(const std::string& username, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement(
				"SELECT t.ticket_id, m.movie_name, s.show_time, h.hall_name, t.seat "
				"FROM tickets t "
				"JOIN schedule s ON t.schedule_id = s.schedule_id "
				"JOIN movies m ON s.movie_id = m.movie_id "
				"JOIN hall h ON s.hall_id = h.hall_id "
				"JOIN users u ON t.user_id = u.userid "
				"WHERE u.username = ?");
			pstmt->setString(1, username);

			ResultSet* rs = pstmt->executeQuery();

			if (rs->next()) {
				do {
					cout << "电影票ID: " << rs->getInt("ticket_id") << "\n";
					cout << "电影名: " << rs->getString("movie_name") << "\n";
					cout << "放映时间: " << rs->getString("show_time") << "\n";
					cout << "影厅名: " << rs->getString("hall_name") << "\n";
					cout << "座位号: " << rs->getString("seat") << "\n\n";
				} while (rs->next());
			}
			else {
				return false; 
			}

			delete rs;
			delete pstmt;
		}
		catch (const SQLException& e) {
			std::cerr << "Error showing user tickets: " << e.what() << std::endl;
			return false;
		}

		return true;
	}

	bool buyTicket(int scheduleId, const std::string& username, const std::string& seat, Connection* con) {


		try {
			PreparedStatement* pstmt = con->prepareStatement(
				"INSERT INTO tickets (user_id, schedule_id, seat) "
				"SELECT userid, ?, ? FROM users WHERE username = ?");
			pstmt->setInt(1, scheduleId);
			pstmt->setString(2, seat);
			pstmt->setString(3, username);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error buying ticket: " << e.what() << std::endl;
			return false;
		}
	}

	bool withdrawTicket(int ticketId, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement("DELETE FROM tickets WHERE ticket_id = ?");
			pstmt->setInt(1, ticketId);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error withdrawing ticket: " << e.what() << std::endl;
			return false;
		}
	}


	bool addSchedule(int hallId, int movieId, double ticketPrice, const std::string& showTime, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement(
				"INSERT INTO schedule (hall_id, movie_id, ticket_price, show_time) VALUES (?, ?, ?, ?)");
			pstmt->setInt(1, hallId);
			pstmt->setInt(2, movieId);
			pstmt->setDouble(3, ticketPrice);
			pstmt->setString(4, showTime);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error adding schedule: " << e.what() << std::endl;
			return false;
		}
	}

	// 删除排期
	bool deleteSchedule(int scheduleId, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Schedule WHERE schedule_id = ?");
			pstmt->setInt(1, scheduleId);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error deleting schedule: " << e.what() << std::endl;
			return false;
		}
	}

	// 更新排期信息
	bool updateSchedule(int scheduleId, int hallId, int movieId, double ticketPrice, const std::string& newShowTime, Connection* con) {
		try {
			PreparedStatement* pstmt = con->prepareStatement(
				"UPDATE Schedule SET hall_id = ?, movie_id = ?, ticket_price = ?, show_time = ? WHERE schedule_id = ?");
			pstmt->setInt(1, hallId);
			pstmt->setInt(2, movieId);
			pstmt->setDouble(3, ticketPrice);
			pstmt->setString(4, newShowTime);
			pstmt->setInt(5, scheduleId);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			std::cerr << "Error updating schedule: " << e.what() << std::endl;
			return false;
		}
	}

	// 列出所有排期
	void listSchedules(Connection* con) {
		try {
			// 使用JOIN来同时从Schedule、Hall和Movie表中获取所需信息
			PreparedStatement* stmt = con->prepareStatement(
				"SELECT s.schedule_id, s.hall_id, h.hall_name, s.movie_id, m.movie_name, s.ticket_price, s.show_time "
				"FROM Schedule s "
				"INNER JOIN Hall h ON s.hall_id = h.hall_id "
				"INNER JOIN Movies m ON s.movie_id = m.movie_id");

			ResultSet* res = stmt->executeQuery();

			std::cout << "\n--- 排版列表 ---\n";
			while (res->next()) {
				std::cout << "排版ID: " << res->getInt("schedule_id")
					<< ", 影厅名: " << res->getString("hall_name")
					<< ", 电影名称: " << res->getString("movie_name")
					<< ", 电影票价: " << res->getDouble("ticket_price")
					<< ", 上映时间: " << res->getString("show_time") << std::endl;
			}

			delete res;
			delete stmt;
		}
		catch (const SQLException& e) {
			std::cerr << "Error listing schedules: " << e.what() << std::endl;
		}
	}
};
class UserLogin {
public:
	bool login(const string& username, const string& password, Connection*& con) {
		con = DBHelper::createConnection();
		if (con == nullptr) {
			cout << "链接数据库失败." << endl;
			return false;
		}
		con->setSchema("cinema");
		PreparedStatement* pstmt = con->prepareStatement("SELECT is_admin FROM users WHERE username = ? AND password = ?");
		pstmt->setString(1, username);
		pstmt->setString(2, password);
		ResultSet* res = pstmt->executeQuery();

		bool isLoggedIn = res->next();
		if (isLoggedIn) {
			cout << "登录成功." << endl;
			if (res->getInt("is_admin") == 1) {
				isAdmin = true;
				cout << "欢迎管理员登录!" << endl;
			}
		}
		else {
			cout << "账号或密码错误." << endl;
		}

		delete pstmt;
		if (!isLoggedIn) {
			DBHelper::closeConnection(con);
			con = nullptr;
		}
		return isLoggedIn;
	}

	bool registerUser(const string& username, const string& password, const string& email, const string& phonenumber, bool isAdmin = false) {
		Connection* con = DBHelper::createConnection();
		if (con == nullptr) {
			cout << "链接数据库失败." << endl;
			return false;
		}
		if (con != nullptr) {
			con->setSchema("cinema");
		}
		try {
			PreparedStatement* pstmt = con->prepareStatement("INSERT INTO users (username, password, email, phonenumber, is_admin) VALUES (?, ?, ?, ?, ?)");
			pstmt->setString(1, username);
			pstmt->setString(2, password);
			pstmt->setString(3, email);
			pstmt->setString(4, phonenumber);
			pstmt->setInt(5, isAdmin ? 1 : 0);

			int rowsAffected = pstmt->executeUpdate();
			delete pstmt;
			DBHelper::closeConnection(con);

			return rowsAffected > 0;
		}
		catch (const SQLException& e) {
			cerr << "Error registering user: " << e.what() << endl;
			DBHelper::closeConnection(con);
			return false;
		}
	}

	void logout(Connection*& con) {
		DBHelper::closeConnection(con);
		con = nullptr;
		cout << "登出成功." << endl;
	}
};
void adminInterface(Connection* con) {
	cout << "\n--- 管理员菜单 ---\n";
	cout << "1. 电影管理\n";
	cout << "2. 影厅管理\n";
	cout << "3. 排班管理\n";
	cout << "4. 用户管理（维护中）\n";
	cout << "5. 登出\n";
	int adminChoice;
	cin >> adminChoice;

	switch (adminChoice) {
	case 1: {
		cout << "\n--- 电影管理 ---\n";
		cout << "1. 新增电影\n";
		cout << "2. 下架电影\n";
		cout << "3. 更新电影信息\n";
		cout << "4. 列出所有电影\n";
		int movieChoice;
		cin >> movieChoice;

		switch (movieChoice) {
		case 1: {

			string title, genre, director, actor;
			double rating;
			cout << "输入电影名称: ";
			cin >> title;
			cout << "输入电影类型: ";
			cin >> genre;
			cout << "输入导演名: ";
			cin >> director;
			cout << "输入演员名: ";
			cin >> actor;
			cout << "输入评分: ";
			cin >> rating;
			MovieManager MovieManger;
			if (MovieManger.addMovie(title, genre, director, actor, rating, con)) { // 通过对象实例调用addMovie
				cout << "电影添加成功!\n";
			}
			break;
		}
		case 2: {
			cout << "输入要删除电影的名称: ";
			string titleToDelete;
			cin >> titleToDelete;
			MovieManager MovieManger;
			if (MovieManger.deleteMovie(titleToDelete, con)) {
				cout << "电影删除成功!\n";
			}
			else {
				cout << "删除失败，请检查后再尝试删除.\n";
			}
			break;
		}
		case 3: {
			cout << "输入要更改电影的原名称: ";
			string oldTitle;
			cin >> oldTitle;
			MovieManager MovieManager;
			if (!MovieManager.existsMovie(oldTitle, con)) {
				cout << "该电影未查询到.\n";
				break;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Enter the new title (leave blank to keep unchanged): ";
			string newTitle = oldTitle; 
			getline(cin, newTitle);
			if (!newTitle.empty() && newTitle != oldTitle) {
				oldTitle = newTitle; 
			}

			cout << "输入新类型，键入ENTER以跳过: ";
			string newGenre;
			getline(cin, newGenre);

			cout << "输入新导演，键入ENTER以跳过:";
			string newDirector;
			getline(cin, newDirector);

			cout << "输入新演员，键入ENTER以跳过: ";
			string newActor;
			getline(cin, newActor);

			cout << "输入新评分，键入ENTER以跳过:";
			string ratingStr;
			getline(cin, ratingStr);
			double newRating = -1; 
			if (!ratingStr.empty()) {
				newRating = stod(ratingStr);
			}


			if (MovieManager.updateMovie(oldTitle, newTitle, newGenre, newDirector, newActor, newRating, con)) {
				cout << "电影更改成功\n";
			}
			else {
				cout << "更改电影失败，请检查后再次尝试更改.\n";
			}
			break;
		}

		case 4: {
			MovieManager MovieManger;
			MovieManger.listMovies(con);
			break;
		}
		default:
			cout << "非法的电影管理选择，检查后再次输入.\n";
			break;
		}
		break;
	}
	case 2:
	{
		cout << "\n--- 影厅管理 ---\n";
		cout << "1. 新增影厅\n";
		cout << "2. 删除影厅\n";
		cout << "3. 更新影厅\n";
		cout << "4. 列出所有影厅\n";
		int hallChoice;
		cin >> hallChoice;

		switch (hallChoice) {
		case 1: {
			string hallName;
			int capacity;
			cout << "输入影厅名: ";
			cin >> hallName;
			cout << "输入容量: ";
			cin >> capacity;
			HallManager hallManager; 
			if (hallManager.addHall(hallName, capacity, con)) {
				cout << "影厅添加成功!\n";
			}
			break;
		}
		case 2: {
			cout << "输入要删除的影厅名称: ";
			string hallNameToDelete;
			cin >> hallNameToDelete;
			HallManager hallManager;
			if (hallManager.deleteHall(hallNameToDelete, con)) {
				cout << "删除影厅成功!\n";
			}
			else {
				cout << "删除影厅失败，请尝试后重新输入.\n";
			}
			break;
		}
		case 3: {
			cout << "输入要更新的影厅的名称 ";
			string oldHallName;
			cin >> oldHallName;
			HallManager hallManager;
			if (!hallManager.existsHall(oldHallName, con)) {
				cout << "找不到对应的影厅\n";
				break;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入新的名称，输入空格以跳过: ";
			string newHallName = oldHallName;
			getline(cin, newHallName); 

			cout << "输入新的容量，输入空格以跳过: ";
			string capacityStr;
			getline(cin, capacityStr);
			int newCapacity = -1; 
			if (!capacityStr.empty()) {
				newCapacity = stoi(capacityStr);
			}

			if (newCapacity >= 0 && !newHallName.empty() && newHallName != oldHallName) {
				hallManager.updateHall(oldHallName, newHallName, newCapacity, con);
				cout << "影厅更新成功!\n";
			}
			else if (!newCapacity && newHallName == oldHallName) {
				cout << "没有发现更改.\n";
			}
			else {
				cout << "更新失败，请检查再进行尝试.\n";
			}
			break;
		}
		case 4: {
			HallManager hallManager;
			hallManager.listHalls(con);
			break;
		}
		default:
			cout << "非法的影厅管理输入.\n";
			break;
		}
		break;
	}
	case 3: {
		ScheduleManager scheduleManager;
		MovieManager MovieManager;
		HallManager HallManager;
		cout << "\n--- 排班管理 ---\n";
		cout << "1. 新增排班\n";
		cout << "2. 删除排班\n";
		cout << "3. 更新排班\n";
		cout << "4. 列出所有的排班\n";
		int scheduleChoice;
		std::vector<std::pair<int, std::string>> movies = MovieManager.getAllMovies(con);
		std::vector<std::pair<int, std::string>> halls = HallManager.getAllHalls(con);
		cin >> scheduleChoice;

		switch (scheduleChoice) {
		case 1: {
			// Add schedule
			int hallId, movieId;
			double ticketPrice;
			std::string showTime;
			std::cout << "选择一个影厅:\n";
			for (size_t i = 0; i < halls.size(); ++i) {
				std::cout << i + 1 << ". " << halls[i].second << "\n";
			}
			int selectedHallIndex;
			std::cin >> selectedHallIndex; // 用户输入影厅序号
			hallId = halls[selectedHallIndex - 1].first; // 获取对应ID
			std::cout << "选择一部电影:\n";
			for (size_t i = 0; i < movies.size(); ++i) {
				std::cout << i + 1 << ". " << movies[i].second << "\n";
			}
			int selectedMovieIndex;
			std::cin >> selectedMovieIndex; // 用户输入电影序号
			movieId = movies[selectedMovieIndex - 1].first; // 获取对应ID
			cout << "输入票价: ";
			cin >> ticketPrice;
			cout << "输入上映时间 (YYYY-MM-DD HH:MM:SS): ";
			cin >> showTime;

			if (scheduleManager.addSchedule(hallId, movieId, ticketPrice, showTime, con)) {
				cout << "排班添加成功!\n";
			}
			break;
		}
		case 2: {

			cout << "输入要删除的排班ID: ";
			int scheduleIdToDelete;
			cin >> scheduleIdToDelete;
			if (scheduleManager.deleteSchedule(scheduleIdToDelete, con)) {
				cout << "排班删除成功!\n";
			}
			else {
				cout << "删除失败，请检查后再尝试删除.\n";
			}
			break;
		}
		
		case 3: {

			int scheduleIdToUpdate;
			scheduleManager.listSchedules(con);
			cout << "请输入要修改的排班ID: ";
			cin >> scheduleIdToUpdate;


			ScheduleDetails currentSchedule = scheduleManager.getScheduleDetails(scheduleIdToUpdate, con);
			if (!currentSchedule.isValid()) {
				cout << "该排班没有查询到.\n";
				break;
			}

			cout << "当前排班详情:\n";
			cout << "影厅名称: " << currentSchedule.hallName << "\n";
			cout << "电影名称: " << currentSchedule.movieName << "\n";
			cout << "电影票价: " << currentSchedule.ticketPrice << "\n";
			cout << "上映时间: " << currentSchedule.showTime << "\n";

			int newHallId = currentSchedule.hallId;
			int newMovieId = currentSchedule.movieId;
			double newTicketPrice = currentSchedule.ticketPrice;
			string newShowTime = currentSchedule.showTime;

			cout << "输入新的影厅号: ";
			string input;
			int newHallIndex = -1;
			getline(cin >> ws, input);
			if (input == "") { // 明确检查用户是否直接按了Enter键
				newHallIndex = 0; 
			}
			else {
				try {
					newHallIndex = std::stoi(input);
					if (newHallIndex > 0 && newHallIndex <= static_cast<int>(halls.size())) {
						newHallId = halls[newHallIndex - 1].first;
					}
					else {
						cout << "非法的影厅号.\n";
						newHallIndex = 0; // 如果输入无效，但用户想要保持不变，则修正为有效输入的逻辑处理
					}
				}
				catch (const std::invalid_argument&) {
					cout << "非法输入.\n";
					newHallIndex = 0; 
				}
			}

			cout << "输入新的电影号: ";
			getline(cin >> ws, input);
			int newMovieIndex = -1; 
			if (input == "") { 
				newMovieIndex = 0; 
			}		
			else{
				try {
					newMovieIndex = std::stoi(input);
					if (newMovieIndex > 0 && newMovieIndex <= static_cast<int>(movies.size())) {
						newMovieId = movies[newMovieIndex - 1].first;
					}
					else {
						cout << "非法的电影号.\n";
						newMovieIndex = 0; // 如果输入无效，但用户想要保持不变，则修正为有效输入的逻辑处理
					}
				}
				catch (const std::invalid_argument&) {
					cout << "非法输入.\n";
					newMovieIndex = 0; // 同样，如果转换失败，认为用户想要保持不变
				}
			}


			cout << "输入新的电影票价: ";
			input.clear();
			getline(cin >> ws, input);
			if (!input.empty()) {
				try {
					newTicketPrice = std::stod(input);
				}
				catch (const std::invalid_argument&) {
					cout << "非法的价格.\n";
				}
			}

			cout << "输入新的上映时间 (YYYY-MM-DD HH:MM:SS) or press enter to keep unchanged: ";
			getline(cin >> ws, newShowTime);

			if (newHallId != currentSchedule.hallId || newMovieId != currentSchedule.movieId ||
				newTicketPrice != currentSchedule.ticketPrice || newShowTime != currentSchedule.showTime) {
				if (scheduleManager.updateSchedule(scheduleIdToUpdate, newHallId, newMovieId, newTicketPrice, newShowTime, con)) {
					cout << "排班修改成功!\n";
				}
				else {
					cout << "排班修改失败，请检查后再输入.\n";
				}
			}
			else {
				cout << "排班没有修改.\n";
			}
			break;
		}
		case 4: {
			scheduleManager.listSchedules(con);
			break;
		}

		default:
			cout << "非法的排班管理输入.\n";
			break;
		}
		break;
	}
	case 5:
	{
		UserLogin loginHelper;
		loginHelper.logout(con);
		isLoggedIn = false;
		isAdmin = false;
		system("cls");
		break;
	}
	}
}

void userInterface(Connection* con, const string& username) {
	cout << "\n--- 欢迎, " << username << "! ---\n";
	cout << "1. 查看排班列表\n";
	cout << "2. 买票\n";
	cout << "3. 退票\n";
	cout << "4. 列出我买的票\n";
	cout << "5. 登出\n";
	int userChoice;
	ScheduleManager scheduleManager;
	cin >> userChoice;

	switch (userChoice) {
	case 1:
		cout << "正在查看排班列表...\n";
		scheduleManager.listSchedules(con);
		break;
	case 2: {
		cout << "买票系统...\n";
		scheduleManager.listSchedules(con);
		int selectedScheduleId;
		string seat;
		cout << "输入你想买的票的排班ID: ";
		cin >> selectedScheduleId;
		cout << "输入座位号: ";
		cin >> seat;
		if (scheduleManager.buyTicket(selectedScheduleId, username, seat, con)) {
			cout << "购票成功!\n";
		}
		else {
			cout << "购票失败.\n";
		}
		break;
	}
	case 3: {
		cout << "退票系统...\n";
		cout << "输入想要退票的电影票ID: ";
		int ticketId;
		cin >> ticketId;
		if (scheduleManager.withdrawTicket(ticketId, con)) {
			cout << "退票成功!\n";
		}
		else {
			cout << "退票失败.\n";
		}
		break;
	}
	case 4: {
		cout << "你的购票:\n";
		if (!scheduleManager.showUserTickets(username, con)) {
			cout << username << "没有购入任何票\n";
		}
		break;
	}
	case 5:
		cout << "登出...\n";
		return; 
	default:
		cout << "非法的输入\n";
		break;
	}
}

int main() {
	Connection* con = nullptr;
	string username, password;


	while (true) {
		if (!isLoggedIn) {
			cout << "\n--- 电影票务管理系统 ---\n";
			cout << "1. 登录\n";
			cout << "2. 注册\n";
			cout << "3. 退出\n";
			int choice;
			cin >> choice;

			switch (choice) {
			case 1: {
				cout << "输入用户名: ";
				cin >> username;
				cout << "输入密码: ";
				cin >> password;

				UserLogin loginHelper;
				isLoggedIn = loginHelper.login(username, password, con);
				if (isLoggedIn) {
					// 根据用户类型跳转到对应的界面
					PreparedStatement* pstmt = con->prepareStatement("SELECT is_admin FROM users WHERE username = ?");
					pstmt->setString(1, username);
					ResultSet* res = pstmt->executeQuery();
					if (res->next()) {
						if (res->getInt("is_admin") == 1) {
							adminInterface(con);
						}
						else {
							userInterface(con, username);
						}
					}
					delete pstmt;
				}
				break;
			}
			case 2: {
				string username, password, email, phonenumber;
				char userType;
				cout << "输入用户名: ";
				cin >> username;
				cout << "输入密码: ";
				cin >> password;
				cout << "输入邮箱: ";
				cin >> email;
				cout << "输入手机号码: ";
				cin >> phonenumber;
				cout << "是否注册为管理员? (y/n): ";
				cin >> userType;

				UserLogin regHelper;
				bool isAdmin = userType == 'y' || userType == 'Y';
				if (regHelper.registerUser(username, password, email, phonenumber, isAdmin)) {
					cout << "注册成功!" << endl;
				}
				else {
					cout << "注册失败，请联系维护人员." << endl;
				}
				break;
			}
			case 3: {
				return 0;
			}
			default: {
				cout << "非法输入.\n";
				break;
			}
			}
		}
		else {
			// 用户已登录
			cout << "\n--- 电影票务管理系统 ---\n";
			if (isAdmin) {
				cout << "1. 管理员面板\n"; // 提供给管理员的选项
			}
			else {
				cout << "1. 用户面板\n"; // 提供给普通用户的选项
			}
			cout << "2. 登出\n";
			cout << "3. 退出\n";
			int choice;
			cin >> choice;

			switch (choice) {
			case 1: {
				if (isAdmin) {
					adminInterface(con);
				}
				else {
					userInterface(con, username);
				}
				break;
			}
			case 2: {
				UserLogin loginHelper;
				loginHelper.logout(con);
				isLoggedIn = false;
				isAdmin = false;
				system("cls");
				break;
			}
			case 3: {
				return 0;
			}
			default: {
				cout << "非法输入.\n";
				break;
			}
			}
		}
	}

	return 0;
}