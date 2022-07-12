#include "pch.h"
#include "EvaluationHistory.h"

EvaluationHistory::EvaluationHistory(const int max_record_amount)
	:max_record_amount_(max_record_amount)
{
	current_record_ = expression_list_.end();
}

void EvaluationHistory::flush()
{
	expression_list_.clear();
	current_record_ = expression_list_.end();
}

void EvaluationHistory::reset()
{
	current_record_ = expression_list_.begin();
}

std::string EvaluationHistory::getRecord() const
{
	return *current_record_;
}

bool EvaluationHistory::hasRecord() const
{
	return current_record_ != expression_list_.end();
}

void EvaluationHistory::moveToPrevious()
{
	++current_record_;
}

void EvaluationHistory::addRecord(const std::string& record)
{
	expression_list_.push_front(record);
	if(expression_list_.size() > max_record_amount_)
	{
		expression_list_.pop_back();
		reset();
	}
}

