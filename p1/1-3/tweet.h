#ifndef _TWEET_H
#define _TWEET_H

#include <string>
#include <ctime>
#include <iomanip>

class tweet
{
private:
	std::string text;
	int hour, min, sec;
	int year, month, day;
public:
	tweet();
	tweet(std::string text);
	~tweet();
	friend std::ostream & operator << (std::ostream & stream, const tweet & _tweet);		// Ausgabeoperator ueberladen
};

tweet::tweet()
{
}

tweet::tweet(std::string text)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	hour = ltm->tm_hour;
	min = ltm->tm_min;
	sec = ltm->tm_sec;
	year = ltm->tm_year+1900;	
	month = ltm->tm_mon+1;
	day = ltm->tm_mday;
	this->text = text;
}

tweet::~tweet()
{
}

std::ostream & operator << (std::ostream  & stream, const tweet & _tweet)
{
	stream << std::setw(2) << std::setfill('0')<<_tweet.day<<"." << std::setw(2) << std::setfill('0') <<_tweet.month<<"."<<_tweet.year<<"/" << std::setw(2) << std::setfill('0') <<_tweet.hour << ":" << std::setw(2) << std::setfill('0')<<_tweet.min << ":" << std::setw(2) << std::setfill('0') << _tweet.sec << " -> " << _tweet.text;
	return stream;
}

#endif