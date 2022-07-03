#pragma once
#include "pch.h"


class EvaluationHistory
{
public:
	explicit EvaluationHistory(int max_record_amount);
	void flush();
	void reset();
	std::string getRecord()const;
	bool hasRecord()const;
	void moveToPrevious();
	void addRecord(const std::string& record);
private:
	std::list<std::string> expression_list_;
	std::list<std::string>::iterator current_record_;
	const std::vector<std::string>::size_type max_record_amount_;
};

