#ifndef DEBUGLOG_H_INCLUDED
#define DEBUGLOG_H_INCLUDED

#include <fstream>
#include <vector>
#include <string>
#include <memory>


class Debug
{
	public:
		Debug();
		~Debug();

		bool openFile(std::string fileName);
		void closeFile();
		bool loadStrings(std::string fileName);
		void write(int target, std::string message, ...);
		bool write(int target, unsigned long messageId, ...);

	private:
		std::vector<std::string> m_logStrings;
		std::ofstream m_logger;
};


typedef std::shared_ptr<Debug> DebugPtr;

#endif // DEBUGLOG_H_INCLUDED