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
	bool isValid() const { return scheduleId != 0; } // ���ж��Ƿ���Ч
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
		res->next(); // �ƶ���������ĵ�һ��
		bool exists = res->getInt(1) > 0; // �������Ƿ����0
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

		cout << "\n--- ��Ӱ�˵� ---\n";
		while (res->next()) {
			cout << "��Ӱ��: " << res->getString("movie_name") << ", ����: " << res->getString("genre")
				<< ", ����: " << res->getString("director") << ", ��Ա: " << res->getString("actor")
				<< ", ����: " << res->getDouble("rating") << endl;
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

	// ����µ�Ӱ��
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

	// ɾ��Ӱ��
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

	// ����Ӱ����Ϣ
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

	// �г�����Ӱ��
	void listHalls(Connection* con) {
		try {
			Statement* stmt = con->createStatement();
			ResultSet* res = stmt->executeQuery("SELECT * FROM hall");

			std::cout << "\n--- Ӱ���б� ---\n";
			while (res->next()) {
				std::cout << "Ӱ��ID: " << res->getInt("hall_id") << ", Ӱ������: " << res->getString("hall_name")
					<< ", ����: " << res->getInt("capacity") << std::endl;
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
			// ʹ��JOIN��ͬʱ��schedules��halls��movies���л�ȡ������Ϣ
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
				details.isValid(); // ���δ�ҵ���¼��isValid������false
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
					cout << "��ӰƱID: " << rs->getInt("ticket_id") << "\n";
					cout << "��Ӱ��: " << rs->getString("movie_name") << "\n";
					cout << "��ӳʱ��: " << rs->getString("show_time") << "\n";
					cout << "Ӱ����: " << rs->getString("hall_name") << "\n";
					cout << "��λ��: " << rs->getString("seat") << "\n\n";
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

	// ɾ������
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

	// ����������Ϣ
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

	// �г���������
	void listSchedules(Connection* con) {
		try {
			// ʹ��JOIN��ͬʱ��Schedule��Hall��Movie���л�ȡ������Ϣ
			PreparedStatement* stmt = con->prepareStatement(
				"SELECT s.schedule_id, s.hall_id, h.hall_name, s.movie_id, m.movie_name, s.ticket_price, s.show_time "
				"FROM Schedule s "
				"INNER JOIN Hall h ON s.hall_id = h.hall_id "
				"INNER JOIN Movies m ON s.movie_id = m.movie_id");

			ResultSet* res = stmt->executeQuery();

			std::cout << "\n--- �Ű��б� ---\n";
			while (res->next()) {
				std::cout << "�Ű�ID: " << res->getInt("schedule_id")
					<< ", Ӱ����: " << res->getString("hall_name")
					<< ", ��Ӱ����: " << res->getString("movie_name")
					<< ", ��ӰƱ��: " << res->getDouble("ticket_price")
					<< ", ��ӳʱ��: " << res->getString("show_time") << std::endl;
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
			cout << "�������ݿ�ʧ��." << endl;
			return false;
		}
		con->setSchema("cinema");
		PreparedStatement* pstmt = con->prepareStatement("SELECT is_admin FROM users WHERE username = ? AND password = ?");
		pstmt->setString(1, username);
		pstmt->setString(2, password);
		ResultSet* res = pstmt->executeQuery();

		bool isLoggedIn = res->next();
		if (isLoggedIn) {
			cout << "��¼�ɹ�." << endl;
			if (res->getInt("is_admin") == 1) {
				isAdmin = true;
				cout << "��ӭ����Ա��¼!" << endl;
			}
		}
		else {
			cout << "�˺Ż��������." << endl;
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
			cout << "�������ݿ�ʧ��." << endl;
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
		cout << "�ǳ��ɹ�." << endl;
	}
};
void adminInterface(Connection* con) {
	cout << "\n--- ����Ա�˵� ---\n";
	cout << "1. ��Ӱ����\n";
	cout << "2. Ӱ������\n";
	cout << "3. �Ű����\n";
	cout << "4. �û�����ά���У�\n";
	cout << "5. �ǳ�\n";
	int adminChoice;
	cin >> adminChoice;

	switch (adminChoice) {
	case 1: {
		cout << "\n--- ��Ӱ���� ---\n";
		cout << "1. ������Ӱ\n";
		cout << "2. �¼ܵ�Ӱ\n";
		cout << "3. ���µ�Ӱ��Ϣ\n";
		cout << "4. �г����е�Ӱ\n";
		int movieChoice;
		cin >> movieChoice;

		switch (movieChoice) {
		case 1: {

			string title, genre, director, actor;
			double rating;
			cout << "�����Ӱ����: ";
			cin >> title;
			cout << "�����Ӱ����: ";
			cin >> genre;
			cout << "���뵼����: ";
			cin >> director;
			cout << "������Ա��: ";
			cin >> actor;
			cout << "��������: ";
			cin >> rating;
			MovieManager MovieManger;
			if (MovieManger.addMovie(title, genre, director, actor, rating, con)) { // ͨ������ʵ������addMovie
				cout << "��Ӱ��ӳɹ�!\n";
			}
			break;
		}
		case 2: {
			cout << "����Ҫɾ����Ӱ������: ";
			string titleToDelete;
			cin >> titleToDelete;
			MovieManager MovieManger;
			if (MovieManger.deleteMovie(titleToDelete, con)) {
				cout << "��Ӱɾ���ɹ�!\n";
			}
			else {
				cout << "ɾ��ʧ�ܣ�������ٳ���ɾ��.\n";
			}
			break;
		}
		case 3: {
			cout << "����Ҫ���ĵ�Ӱ��ԭ����: ";
			string oldTitle;
			cin >> oldTitle;
			MovieManager MovieManager;
			if (!MovieManager.existsMovie(oldTitle, con)) {
				cout << "�õ�Ӱδ��ѯ��.\n";
				break;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Enter the new title (leave blank to keep unchanged): ";
			string newTitle = oldTitle; 
			getline(cin, newTitle);
			if (!newTitle.empty() && newTitle != oldTitle) {
				oldTitle = newTitle; 
			}

			cout << "���������ͣ�����ENTER������: ";
			string newGenre;
			getline(cin, newGenre);

			cout << "�����µ��ݣ�����ENTER������:";
			string newDirector;
			getline(cin, newDirector);

			cout << "��������Ա������ENTER������: ";
			string newActor;
			getline(cin, newActor);

			cout << "���������֣�����ENTER������:";
			string ratingStr;
			getline(cin, ratingStr);
			double newRating = -1; 
			if (!ratingStr.empty()) {
				newRating = stod(ratingStr);
			}


			if (MovieManager.updateMovie(oldTitle, newTitle, newGenre, newDirector, newActor, newRating, con)) {
				cout << "��Ӱ���ĳɹ�\n";
			}
			else {
				cout << "���ĵ�Ӱʧ�ܣ�������ٴγ��Ը���.\n";
			}
			break;
		}

		case 4: {
			MovieManager MovieManger;
			MovieManger.listMovies(con);
			break;
		}
		default:
			cout << "�Ƿ��ĵ�Ӱ����ѡ�񣬼����ٴ�����.\n";
			break;
		}
		break;
	}
	case 2:
	{
		cout << "\n--- Ӱ������ ---\n";
		cout << "1. ����Ӱ��\n";
		cout << "2. ɾ��Ӱ��\n";
		cout << "3. ����Ӱ��\n";
		cout << "4. �г�����Ӱ��\n";
		int hallChoice;
		cin >> hallChoice;

		switch (hallChoice) {
		case 1: {
			string hallName;
			int capacity;
			cout << "����Ӱ����: ";
			cin >> hallName;
			cout << "��������: ";
			cin >> capacity;
			HallManager hallManager; 
			if (hallManager.addHall(hallName, capacity, con)) {
				cout << "Ӱ����ӳɹ�!\n";
			}
			break;
		}
		case 2: {
			cout << "����Ҫɾ����Ӱ������: ";
			string hallNameToDelete;
			cin >> hallNameToDelete;
			HallManager hallManager;
			if (hallManager.deleteHall(hallNameToDelete, con)) {
				cout << "ɾ��Ӱ���ɹ�!\n";
			}
			else {
				cout << "ɾ��Ӱ��ʧ�ܣ��볢�Ժ���������.\n";
			}
			break;
		}
		case 3: {
			cout << "����Ҫ���µ�Ӱ�������� ";
			string oldHallName;
			cin >> oldHallName;
			HallManager hallManager;
			if (!hallManager.existsHall(oldHallName, con)) {
				cout << "�Ҳ�����Ӧ��Ӱ��\n";
				break;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�����µ����ƣ�����ո�������: ";
			string newHallName = oldHallName;
			getline(cin, newHallName); 

			cout << "�����µ�����������ո�������: ";
			string capacityStr;
			getline(cin, capacityStr);
			int newCapacity = -1; 
			if (!capacityStr.empty()) {
				newCapacity = stoi(capacityStr);
			}

			if (newCapacity >= 0 && !newHallName.empty() && newHallName != oldHallName) {
				hallManager.updateHall(oldHallName, newHallName, newCapacity, con);
				cout << "Ӱ�����³ɹ�!\n";
			}
			else if (!newCapacity && newHallName == oldHallName) {
				cout << "û�з��ָ���.\n";
			}
			else {
				cout << "����ʧ�ܣ������ٽ��г���.\n";
			}
			break;
		}
		case 4: {
			HallManager hallManager;
			hallManager.listHalls(con);
			break;
		}
		default:
			cout << "�Ƿ���Ӱ����������.\n";
			break;
		}
		break;
	}
	case 3: {
		ScheduleManager scheduleManager;
		MovieManager MovieManager;
		HallManager HallManager;
		cout << "\n--- �Ű���� ---\n";
		cout << "1. �����Ű�\n";
		cout << "2. ɾ���Ű�\n";
		cout << "3. �����Ű�\n";
		cout << "4. �г����е��Ű�\n";
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
			std::cout << "ѡ��һ��Ӱ��:\n";
			for (size_t i = 0; i < halls.size(); ++i) {
				std::cout << i + 1 << ". " << halls[i].second << "\n";
			}
			int selectedHallIndex;
			std::cin >> selectedHallIndex; // �û�����Ӱ�����
			hallId = halls[selectedHallIndex - 1].first; // ��ȡ��ӦID
			std::cout << "ѡ��һ����Ӱ:\n";
			for (size_t i = 0; i < movies.size(); ++i) {
				std::cout << i + 1 << ". " << movies[i].second << "\n";
			}
			int selectedMovieIndex;
			std::cin >> selectedMovieIndex; // �û������Ӱ���
			movieId = movies[selectedMovieIndex - 1].first; // ��ȡ��ӦID
			cout << "����Ʊ��: ";
			cin >> ticketPrice;
			cout << "������ӳʱ�� (YYYY-MM-DD HH:MM:SS): ";
			cin >> showTime;

			if (scheduleManager.addSchedule(hallId, movieId, ticketPrice, showTime, con)) {
				cout << "�Ű���ӳɹ�!\n";
			}
			break;
		}
		case 2: {

			cout << "����Ҫɾ�����Ű�ID: ";
			int scheduleIdToDelete;
			cin >> scheduleIdToDelete;
			if (scheduleManager.deleteSchedule(scheduleIdToDelete, con)) {
				cout << "�Ű�ɾ���ɹ�!\n";
			}
			else {
				cout << "ɾ��ʧ�ܣ�������ٳ���ɾ��.\n";
			}
			break;
		}
		
		case 3: {

			int scheduleIdToUpdate;
			scheduleManager.listSchedules(con);
			cout << "������Ҫ�޸ĵ��Ű�ID: ";
			cin >> scheduleIdToUpdate;


			ScheduleDetails currentSchedule = scheduleManager.getScheduleDetails(scheduleIdToUpdate, con);
			if (!currentSchedule.isValid()) {
				cout << "���Ű�û�в�ѯ��.\n";
				break;
			}

			cout << "��ǰ�Ű�����:\n";
			cout << "Ӱ������: " << currentSchedule.hallName << "\n";
			cout << "��Ӱ����: " << currentSchedule.movieName << "\n";
			cout << "��ӰƱ��: " << currentSchedule.ticketPrice << "\n";
			cout << "��ӳʱ��: " << currentSchedule.showTime << "\n";

			int newHallId = currentSchedule.hallId;
			int newMovieId = currentSchedule.movieId;
			double newTicketPrice = currentSchedule.ticketPrice;
			string newShowTime = currentSchedule.showTime;

			cout << "�����µ�Ӱ����: ";
			string input;
			int newHallIndex = -1;
			getline(cin >> ws, input);
			if (input == "") { // ��ȷ����û��Ƿ�ֱ�Ӱ���Enter��
				newHallIndex = 0; 
			}
			else {
				try {
					newHallIndex = std::stoi(input);
					if (newHallIndex > 0 && newHallIndex <= static_cast<int>(halls.size())) {
						newHallId = halls[newHallIndex - 1].first;
					}
					else {
						cout << "�Ƿ���Ӱ����.\n";
						newHallIndex = 0; // ���������Ч�����û���Ҫ���ֲ��䣬������Ϊ��Ч������߼�����
					}
				}
				catch (const std::invalid_argument&) {
					cout << "�Ƿ�����.\n";
					newHallIndex = 0; 
				}
			}

			cout << "�����µĵ�Ӱ��: ";
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
						cout << "�Ƿ��ĵ�Ӱ��.\n";
						newMovieIndex = 0; // ���������Ч�����û���Ҫ���ֲ��䣬������Ϊ��Ч������߼�����
					}
				}
				catch (const std::invalid_argument&) {
					cout << "�Ƿ�����.\n";
					newMovieIndex = 0; // ͬ�������ת��ʧ�ܣ���Ϊ�û���Ҫ���ֲ���
				}
			}


			cout << "�����µĵ�ӰƱ��: ";
			input.clear();
			getline(cin >> ws, input);
			if (!input.empty()) {
				try {
					newTicketPrice = std::stod(input);
				}
				catch (const std::invalid_argument&) {
					cout << "�Ƿ��ļ۸�.\n";
				}
			}

			cout << "�����µ���ӳʱ�� (YYYY-MM-DD HH:MM:SS) or press enter to keep unchanged: ";
			getline(cin >> ws, newShowTime);

			if (newHallId != currentSchedule.hallId || newMovieId != currentSchedule.movieId ||
				newTicketPrice != currentSchedule.ticketPrice || newShowTime != currentSchedule.showTime) {
				if (scheduleManager.updateSchedule(scheduleIdToUpdate, newHallId, newMovieId, newTicketPrice, newShowTime, con)) {
					cout << "�Ű��޸ĳɹ�!\n";
				}
				else {
					cout << "�Ű��޸�ʧ�ܣ������������.\n";
				}
			}
			else {
				cout << "�Ű�û���޸�.\n";
			}
			break;
		}
		case 4: {
			scheduleManager.listSchedules(con);
			break;
		}

		default:
			cout << "�Ƿ����Ű��������.\n";
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
	cout << "\n--- ��ӭ, " << username << "! ---\n";
	cout << "1. �鿴�Ű��б�\n";
	cout << "2. ��Ʊ\n";
	cout << "3. ��Ʊ\n";
	cout << "4. �г������Ʊ\n";
	cout << "5. �ǳ�\n";
	int userChoice;
	ScheduleManager scheduleManager;
	cin >> userChoice;

	switch (userChoice) {
	case 1:
		cout << "���ڲ鿴�Ű��б�...\n";
		scheduleManager.listSchedules(con);
		break;
	case 2: {
		cout << "��Ʊϵͳ...\n";
		scheduleManager.listSchedules(con);
		int selectedScheduleId;
		string seat;
		cout << "�����������Ʊ���Ű�ID: ";
		cin >> selectedScheduleId;
		cout << "������λ��: ";
		cin >> seat;
		if (scheduleManager.buyTicket(selectedScheduleId, username, seat, con)) {
			cout << "��Ʊ�ɹ�!\n";
		}
		else {
			cout << "��Ʊʧ��.\n";
		}
		break;
	}
	case 3: {
		cout << "��Ʊϵͳ...\n";
		cout << "������Ҫ��Ʊ�ĵ�ӰƱID: ";
		int ticketId;
		cin >> ticketId;
		if (scheduleManager.withdrawTicket(ticketId, con)) {
			cout << "��Ʊ�ɹ�!\n";
		}
		else {
			cout << "��Ʊʧ��.\n";
		}
		break;
	}
	case 4: {
		cout << "��Ĺ�Ʊ:\n";
		if (!scheduleManager.showUserTickets(username, con)) {
			cout << username << "û�й����κ�Ʊ\n";
		}
		break;
	}
	case 5:
		cout << "�ǳ�...\n";
		return; 
	default:
		cout << "�Ƿ�������\n";
		break;
	}
}

int main() {
	Connection* con = nullptr;
	string username, password;


	while (true) {
		if (!isLoggedIn) {
			cout << "\n--- ��ӰƱ�����ϵͳ ---\n";
			cout << "1. ��¼\n";
			cout << "2. ע��\n";
			cout << "3. �˳�\n";
			int choice;
			cin >> choice;

			switch (choice) {
			case 1: {
				cout << "�����û���: ";
				cin >> username;
				cout << "��������: ";
				cin >> password;

				UserLogin loginHelper;
				isLoggedIn = loginHelper.login(username, password, con);
				if (isLoggedIn) {
					// �����û�������ת����Ӧ�Ľ���
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
				cout << "�����û���: ";
				cin >> username;
				cout << "��������: ";
				cin >> password;
				cout << "��������: ";
				cin >> email;
				cout << "�����ֻ�����: ";
				cin >> phonenumber;
				cout << "�Ƿ�ע��Ϊ����Ա? (y/n): ";
				cin >> userType;

				UserLogin regHelper;
				bool isAdmin = userType == 'y' || userType == 'Y';
				if (regHelper.registerUser(username, password, email, phonenumber, isAdmin)) {
					cout << "ע��ɹ�!" << endl;
				}
				else {
					cout << "ע��ʧ�ܣ�����ϵά����Ա." << endl;
				}
				break;
			}
			case 3: {
				return 0;
			}
			default: {
				cout << "�Ƿ�����.\n";
				break;
			}
			}
		}
		else {
			// �û��ѵ�¼
			cout << "\n--- ��ӰƱ�����ϵͳ ---\n";
			if (isAdmin) {
				cout << "1. ����Ա���\n"; // �ṩ������Ա��ѡ��
			}
			else {
				cout << "1. �û����\n"; // �ṩ����ͨ�û���ѡ��
			}
			cout << "2. �ǳ�\n";
			cout << "3. �˳�\n";
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
				cout << "�Ƿ�����.\n";
				break;
			}
			}
		}
	}

	return 0;
}