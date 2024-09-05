#include <sys/utsname.h>
#include <unistd.h>

#include <iostream>
#include <array>

int main() {
	{
		std::array<char, 255> hostname;
		auto res = gethostname(hostname.data(), hostname.size());
		if (res == 0) {
			std::cout << hostname.data() << std::endl;
		}
	}

	{
		std::array<char, 255> username;
		auto res = getlogin_r(username.data(), username.size());
		if (res == 0) {
			std::cout << username.data() << std::endl;
		} else {
			std::cout << "Не удалось получить логин пользователя: error code " << res << std::endl;
		}
	}

	{
		utsname uname_res;
		auto res = uname(&uname_res);
		if (res == 0) {
			std::cout << uname_res.release << std::endl;
		}
	}

	{
		auto res = sysconf(_SC_ARG_MAX);
		std::cout << "The maximum length of the arguments to the exec(3) family of functions: " << res << std::endl;

		res = sysconf(_SC_CHILD_MAX);
		std::cout << "The maximum number of simultaneous processes per user ID: " << res << std::endl;

		res = sysconf(_SC_HOST_NAME_MAX);
		std::cout << "Maximum length of a hostname: " << res << std::endl;
	}

	{
		time_t current_time = time(nullptr);
		std::cout << "Текущее время: " << current_time << std::endl;

		struct tm* lt = localtime(&current_time);
		std::cout << "Текущий час: " << lt->tm_hour << std::endl;

		struct tm* gt = gmtime(&current_time);
		std::cout << "Текщий час (UTC): " << gt->tm_hour << std::endl;
	}

	{
		uid_t current_UID = getuid();
		std::cout << "UID пользователя, запустившего процесс: " << current_UID << std::endl;

		pid_t current_PID = getpid();
		std::cout << "PID (текущий процесс): " << current_PID << std::endl;

		gid_t current_GID = getgid();
		std::cout << "Group ID пользователя, запустившего процесс: " << current_GID << std::endl;

		std::array<char, 255> dir;
		auto res = getcwd(dir.data(), dir.size());
		if (res != nullptr) {
			std::cout << "Абсолютный путь текущей директории: " << dir.data() << std::endl;
		} else {
			std::cout << "Не удалось получить абсолютный путь текущей директории";
		}
	}
}